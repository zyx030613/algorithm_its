# -*- coding: utf-8 -*-
""" 
Tools to test ITS.
date:2018-7-3
Detail:

self.lineEdit           # 获取文件后面的输入框，路径
self.pushButton         # 浏览按钮
self.pushButton_read    # 读取按钮，手动输入地址的情况下点读取来更新树形
self.lineEdit_ip        # ip输入框
self.lineEdit_user      # 用户名输入框
self.lineEdit_passwd    # 密码输入框
self.lineEdit_tel_user  # telnet帐号输入框
self.lineEdit_tel_passwd# telnet密码输入框
self.lineEdit_timeout   # 接收超时输入框
self.pushButton_purpose # 加入视频地址列表的按钮
self.pushButton_recv    # 接收视频的按钮

Flow:
1、输入需要读取的路径
2、输入设备ip，帐号，密码，telnet帐号，telnet密码
3、根据视频中最大车牌间隔修改这个值，需要大于最大车牌间隔
4、点击开始接收，在超时时间内会一直等待
5、选择左侧视频，点击后会生成视频地址，点击按钮会让设备开始播放视频
6、接收结束后，分析结果

"""

import datetime, os, errno, logging.config
from PyQt4.QtCore import pyqtSignature, SIGNAL, QObject
from PyQt4.QtGui import QMainWindow, QFileDialog
from PyQt4.QtGui import QMessageBox
from sys import argv, exit
from its_ui import Ui_MainWindow
import PyQt4.QtGui
import win32api
from its_Dev_info import DevInfo_Get

def log_file_make():
	### 日志定义
	now = datetime.datetime.now()
	local_sec = now.strftime('%Y-%m-%d %H:%M:%S') + '\n'
	log_file = './log/logger_its.log'
	if not os.path.exists(log_file):
		try:
			with open(log_file, 'w') as ccc:
				ccc.write(local_sec)
		except OSError as exc:
			if exc.errno == errno.EEXIST and os.path.isfile(log_file):
				with open(log_file, 'w') as ccc:
					ccc.write(local_sec)
				pass
			else:
				raise
	else:
		with open(log_file, 'a') as ccc:
			ccc.write(local_sec)


log_file_make()
logging.config.fileConfig("logging_its.conf")  # 采用配置文件
logger = logging.getLogger("itsmain")

import its_recv_thread  # logger之后才有句柄，此时调用线程文件才能使用线程中的logger将日志传上来
import its_Alg_Analysis as iAA


class MainWindow(QMainWindow, Ui_MainWindow):
	""" 
	None
	"""
	def __init__(self, parent=None):
		""" 
		初始化界面
		"""
		QMainWindow.__init__(self, parent)
		self.setupUi(self)  # 使用QMainWindow来初始化setupUI

		self.tree_left.selectionModel().selectionChanged.connect(self.on_root_clicked)
		QObject.connect(self.pushButton_recv, SIGNAL("clicked()"), self.add_paths)
		QObject.connect(self.pushButton_read, SIGNAL("clicked()"), self.add_tree)
		#QObject.connect(self.pushButton, SIGNAL("clicked()"), self.setpath)
		QObject.connect(self.pushButton_purpose, SIGNAL("clicked()"), self.isKakou)
		QObject.connect(self.pushButton_man_browse, SIGNAL("clicked()"), self.manfilepath)
		QObject.connect(self.pushButton_man_do, SIGNAL("clicked()"), self.analysis_report)
		#QObject.connect(self.pushButton_hebing, SIGNAL("clicked()"), self.Result_name_show)
		QObject.connect(self.listview_result, SIGNAL('doubleClicked(QModelIndex)'), self._openxls)
		QObject.connect(self.checkBox_kakou, SIGNAL("clicked()"), self.isJenkins)
		try:
			self.config_read()
		except:
			logger.exception('found its_devinfo.ini err: ')
			self.text_show(u'读取配置文件错误，请检查文件内容及格式UTF8无DOM！')
			self._stop_all()
	# 临时合并报告的按钮
	# 注意合并前，必须跑完一次接收，或者不进任何已有线程，否则路径会在dll中。
	# 视频的路径： self.path_pic_now， 从\\192.168.18.136\GX\ITS_PIC\傍晚.sdv 取最后一个
	# 跑完接收之后，excel的路径是：self.xlsx_in_path
	# 返回的excel路径：    ..\.\Result\201807051535_傍晚.xlsx
	# QObject.connect(self.pushButton_hebing, SIGNAL("clicked()"), self.)

	# 主程序入口
	def isKakou(self):
		"""
		初始化了勾选的值。
		判断重启是否勾选，勾选是2，不勾选是0.
		卡口识别率，需要调用一个新线程，发送抓拍指令
		"""
		self.kakou = int(self.checkBox_kakou.checkState())
		# 获取视频列表，对列表进行循环发送
		ss = str(self.lineEdit_purpose.toPlainText().toLocal8Bit()).decode('gb2312')
		self.video_paths = ss.split('\n')
		if self.kakou == 2:  # 如果是卡口，而且输入的路径是个文件，则直接打印失败，不调用
			kakou_with_file = 0
			for i in self.video_paths:
				if os.path.isfile(i):
					logger.debug('mode kakou with file here: %s' % i)
					kakou_with_file = 1  # 有文件，则置为1，直接结束循环，不是文件，则下一次循环
					break
				else:
					continue
			if kakou_with_file == 1:
				self.text_show(u'列表中有问题，卡口识别率仅支持文件夹！')
				self._stop_all()
			else:
				self.send_path_tel()
		elif self.kakou != 2:  # 抓拍率模式，如果列表中有文件夹，则失败
			video_with_dir = 0
			for j in self.video_paths:
				if not os.path.isfile(j):
					logger.debug('video mode with dir here: %s' % j)
					video_with_dir = 1  # 有文件，则置为1，直接结束循环，不是文件，则下一次循环
					break
				else:
					continue
			if video_with_dir == 1:
				self.text_show(u'列表中有问题，抓拍率仅支持文件！')
				self._stop_all()
			else:
				self.send_path_tel()

	###################################################
	# 发送地址模块
	# 处理树形中被选中项写入视频地址
	@pyqtSignature("")
	def on_root_clicked(self, ):
		# TODO :将共享目录翻译成nfs目录
		pathSelected = self.dirModel.filePath(self.tree_left.selectedIndexes()[0])
		path_encode = str(pathSelected.toLocal8Bit()).decode('gb2312')
		self.path_encode = path_encode.replace('/', '\\')  # 暂时翻译成了双斜杠，需要根据nfs需要的格式再改

	# self.lineEdit_purpose.setText(path_encode)
	# 需要翻译成nfs挂载后的形式，然后调用telnet设备输入程序

	# 加入列表按钮
	def add_paths(self):
		self.lineEdit_purpose.append(self.path_encode)

	# 发送telnet视频地址的函数，需要补充
	def send_path_tel(self):
		self._all_start()
		self.get_info()
		self.pushButton_purpose.setEnabled(False)
		self.tel_send = its_recv_thread.TelThread(
			[self.ip, self.user, self.passwd, self.tel_user, self.tel_passwd, self.recv_timeout, self.video_paths])
		self.tel_send.logSignal.connect(self.text_show)
		self.pingthread = its_recv_thread.PingThread(self.ip)
		self.pingthread.rebootSignal.connect(self.text_show)
		if self.kakou != 2:
			self.tel_send.openSignal.connect(self.DoSendTel)                      # 视频发送成功后，打印发送成功
			# self.tel_send.recvstartSignal.connect(self.DoStartRecv)
			self.tel_send.finishSignal.connect(self.DoStopVideo)
		else:
			self.tel_send.openSignal.connect(self.DoSendTel_cgi)                  # 图片地址发送成功后，开始cgi抓拍
			self.tel_send.finishSignal.connect(self.DoStopVideo_cgi)
		self.tel_send.filenameSignal.connect(self.DoVideopath)  # 开tel开始前，先把视频路径返回来
		self.tel_send.recvstartSignal.connect(self.DoStartRecv)     # 开telnet前，接收线程启动成功
		try:
			self.tel_send.start()
		except Exception as eee:
			logger.error('Err with send path tel: %s') % eee
			self.tel_send.stop()
			self.DoStopVideo(2)

	# 开启telnet和发送命令是否成功的显示
	def DoSendTel(self, backv):
		# self.path_pic_now = backv[1]
		if backv[0] == 1:
			self.text_show(u'视频地址发送成功 ！')
			self.pingthread.start()
		elif backv[0] == 2:
			self.text_show(u'设备参数导入失败 ！')
			self.text_show(backv[1])
		else:
			self.text_show(u'视频地址发送失败，请检查！')
			try:
				self.DoStopVideo(2)
			except:
				logger.exception('err with stop all:')

	# 流程：进循环，发送回视频文件名称，开启接收线程，循环等待4秒，然后每0.1秒检测一次接收线程，线程开启后，打印开始接收。然后发送地址给telnet，开始播放视频。
	# 打印顺序：1、正开启接收线程 2、开始接收 3、视频地址发送成功 4、开始模拟抓拍
	def DoVideopath(self, back_videopath):
		self.path_pic_now = back_videopath[0]  # 得到当前发送给设备的目录路径
		self.text_show(u'正在开启接收线程， wait a moment ！')
		self.recv_start()  # 开启telnet信号成功收到后，telnet线程会睡3秒，等待接收线程开启

	# 接收线程开启后，全局变量 recv_start 会变成1，然后返回信号，这里打印开始接收后，就可以接收了。
	# 初始化sdk需要近2s，开启接收线程需要2s左右。卡口模拟抓拍会睡6s，也就是再过2s就会发抓拍了。
	def DoStartRecv(self, startback):
		del startback
		self.text_show(u'开始接收！')

	# 全部线程执行完毕
	def DoStopVideo(self, a=0):
		try:
			self.text_show(u'全部结束 ！')
			self.tel_send.stop()
			self._stop_all()
			self.recv.stop(int(a))
			self.rows_check.stop()
		except Exception as eee:
			logger.error('err with stop all : %s' % eee)

	# 卡口识别率的地址发送结果显示
	def DoSendTel_cgi(self, backv):
		self.path_pic_now = backv[1]                            # 得到当前发送给设备的目录路径
		if backv[0] == 1:
			self.text_show(u'卡口目录发送成功 ！')
			try:
				self.cgi_start()                                # 开启接收线程后，cgi会睡5秒，然后开发
				self.pingthread.start()
			except:
				logger.exception('err with cigstart or pingthread:')
				self.tel_send.stop()
				self._stop_all()
				self.recv.stop(0)
				self.rows_check.stop()
		elif backv[0] == 2:
			self.text_show(u'设备参数导入失败 ！')
			self.text_show(backv[1])
		else:
			self.text_show(u'卡口目录送失败，请检查！')
			try:
				self.tel_send.stop()
				self._stop_all()
				self.recv.stop(2)
				self.rows_check.stop()
			except:
				logger.exception('err with stop all:')

	# 卡口识别率全部线程结束
	def DoStopVideo_cgi(self, ):
		try:
			self.text_show(u'全部结束 ！')
			self.tel_send.stop()
			self._stop_all()
			self.recv.stop(0)
			self.rows_check.stop()
			self.cgi_send.stop()
		except Exception as eee:
			logger.error('err with stop all : %s' % eee)

	###################################################
	# 预处理模块
	# 处理树形的根目录，读取按钮使用
	def add_tree(self):
		self.rd_path = str(self.lineEdit.text().toLocal8Bit()).decode('gb2312')
		#self.dirModel.refresh()
		self.dirModel.setRootPath('')
		#self.dirModel.rootDirectory()

		self.tree_left.setRootIndex(self.dirModel.index(self.rd_path))

	# 处理树形的目录，浏览按钮使用
	def setpath(self):
		s = QFileDialog.getExistingDirectory()
		self.lineEdit.setText(str(s.toLocal8Bit()).decode('gb2312'))
		self.get_pro_data()

	# 获取目录下文件夹及文件
	def get_pro_data(self):
		self.rd_path = str(self.lineEdit.text().toLocal8Bit()).decode('gb2312')
		if self.rd_path != '':
			self.add_tree()
		else:
			logger.debug('no path now .')

	# 获取IP等内容
	def get_info(self):
		self.ip = str(self.lineEdit_ip.text())
		self.user = str(self.lineEdit_user.text())
		self.passwd = str(self.lineEdit_passwd.text())
		self.tel_user = str(self.lineEdit_tel_user.text())
		self.tel_passwd = str(self.lineEdit_tel_passwd.text())
		self.cgi_delay = str(self.lineEdit_cgi_delay.text())
		#recv_timeout_sub = int(self.lineEdit_timeout.text())
		#if recv_timeout_sub < 20:
			#recv_timeout_sub = 20
			#self.lineEdit_timeout.setText('20')
		#self.recv_timeout = str(recv_timeout_sub)
		self.recv_timeout = 120

	###################################################
	# 接收模块

	# 开始接收
	def recv_start(self):   # 注意调用stop时，异常是发2，正常结束发0
		self.back_ora = []  # 初始化一个列表，与收到的进行对比，只能放这，因为每次点击都要接新的，不能用上一次的结果
		self.get_info()
		self.recv = its_recv_thread.RecvThread(
			[self.ip, self.user, self.passwd, self.tel_user, self.tel_passwd, self.recv_timeout, self.path_pic_now])
		self.recv.finishSignal.connect(self.DoFinishEmit)

		self.rows_check = its_recv_thread.BackThread()
		self.rows_check.HelpSignal.connect(self.DoEmitMsg)
		try:
			self.pushButton_recv.setEnabled(False)
			self._all_start()
			self.recv.start()
			self.rows_check.start()
		except Exception as eee:
			logger.error('err with recv start : %s' % eee)
			self._stop_all()
			self.recv.stop(2)
			self.rows_check.stop()
			self.text_show(u'接收线程出现错误，请查看日志文件！')

	# 接收完毕时的处理
	def DoFinishEmit(self, telback_values):
		# 这里进行excel表的对比，传入值是["'..\\.\\Result\\' + localtime_min + '_' + self.ip + '.xlsx' "] excel 路径
		self.xlsx_in_path = telback_values[0]
		self.recv.stop(0)
		self.rows_check.stop()
		logger.debug('recv  back is : %s' %self.xlsx_in_path)
		if self.xlsx_in_path == 1:
			logger.error('xml back : %s' % self.xlsx_in_path)
			self.text_show(u'车辆品牌xml获取问题，请查看日志！')
		elif self.xlsx_in_path == 2:
			logger.error('excel open : %s' % self.xlsx_in_path)
			self.text_show(u'Excel 打开存在问题，请查看日志！')
		elif self.xlsx_in_path == 3:
			logger.error('itsstream open : %s' % self.xlsx_in_path)
			self.text_show(u'接收函数异常，请查看日志！')
		elif self.xlsx_in_path == 4:
			logger.error('logon open : %s' % self.xlsx_in_path)
			self.text_show(u'Logon 存在问题，请查看日志！')
		elif self.xlsx_in_path == 5:
			logger.error('click stop or other reason stop recv : %s' % self.xlsx_in_path)
			self.text_show(u'接收被终止，请查看日志！')
		else:
			logger.debug('excel name back : %s' % self.xlsx_in_path)
			self.text_show(u'接收完毕，将进行对比！')
			try:
				self.start_alg_analysis()
			except:
				logger.exception('err with alg:')
				self.text_show(u'结果分析线程出现问题，请查看日志！')

	# 接收过程中的处理
	def DoEmitMsg(self, back_value):
		logger.debug('MSG DO with back value : %s' % back_value)
		if len(back_value[1]) > 1:  # CGI返回表 默认是空，当执行cgi线程后，才会写入内容
			m = back_value[1]  # CGI返回的列表
			if int(m[1]) == 200:
				if int(m[0]) == 0:
					icode_show = u'当前发送：车道, 成功.'
				else:
					icode_show = u'当前发送：' + str(m[0]) + u', 成功.'
			else:
				if int(m[0]) == 0:
					icode_show = u'当前发送：车道, ' + u', 失败！ 错误码：' + str(m[1])
					self._stop_all()
					self.recv.stop(2)
					self.rows_check.stop()
					self.pingthread.stop()
				else:
					icode_show = u'当前发送：' + str(m[0]) + u', 失败！ 错误码：' + str(m[1])
			self.text_show(icode_show)
		for i in back_value[0]:
			if str(i) != '0':  # 超时的返回值不打印
				if i == 'np':
					plate = u'接收：未知'
				else:
					plate = u'接收：' + i.decode('gbk')
				self.text_show(plate)

	###################################################
	# 模拟抓拍
	# CGI发送模拟抓拍初始化函数
	def cgi_start(self):
		path_now = self.path_pic_now
		self.cgi_send = its_recv_thread.CgiThread([self.ip, self.user, self.passwd, self.cgi_delay, path_now])
		self.cgi_send.finishSignal.connect(self.DoCgiPic)
		try:
			self.cgi_send.start()
		except Exception as eee:
			logger.error('err with cgi send, %s' % eee)
			self.text_show(u'模拟抓拍发送线程出现问题，请查看日志！')

	# 处理模拟抓拍发送完毕后的结束信号
	def DoCgiPic(self, inin):
		cgi_over_show = u'模拟抓拍发送完毕.共计：' + str(inin[0])
		self.text_show(cgi_over_show)

	########################################################
	# 文件生成块
	# 分析和生成结果
	def start_alg_analysis(self):
		# 调用excel分析比对模块
		self.video_dir = os.path.split(self.path_pic_now)[0]
		if os.path.isdir(self.path_pic_now):
			self.video_name = os.path.split(self.path_pic_now)[-1]
		else:
			self.video_name = os.path.splitext(os.path.split(self.path_pic_now)[-1])[0]
		self.excel_std = self.video_dir + '\\' + self.video_name + '.xlsx'
		self.excel_test = self.xlsx_in_path[3:]
		self.exceltest_dir = os.path.split(self.excel_test)[0]
		self.exceltest_name = os.path.splitext(os.path.split(self.excel_test)[-1])[0]
		self.excel_report = self.exceltest_dir + '\\' + self.exceltest_name + '_report.xlsx'
		self.startalgThread = iAA.Alg_Interface_Thread(self.excel_std, self.excel_test, self.excel_report, 1,self.kakou)
		# 信号关联函数
		self.startalgThread.finishSignal.connect(self.Result_name_show)
		self.startalgThread.errSignal.connect(self.text_show)
		self.startalgThread.start()

	def analysis_report(self):
		# 分析结果手动修改后再次分析使用
		self.excel_report = str(self.lineEdit_man.text().toLocal8Bit()).decode('gb2312')
		logger.debug(self.excel_report)
		self.startalgThread = iAA.Alg_Interface_Thread('', '', self.excel_report, 0,self.kakou)
		# 信号关联函数
		self.startalgThread.finishSignal.connect(self.Result_name_show)
		self.startalgThread.errSignal.connect(self.text_show)
		self.startalgThread.start()

	# 手动生成文件使用
	def manfilepath(self):
		"""
		选择手动生成的文件用的
		:return: None
		"""
		s = QFileDialog.getOpenFileName(self, "Open file dialog", "/", "Excel files(*.xlsx)")
		if s != '':
			self.lineEdit_man.setText(str(s.toLocal8Bit()).decode('gb2312'))

	# 显示合成后的结果，点击直接打开，目前是单选模式
	# ExtendedSelection 按住ctrl多选, SingleSelection 单选 MultiSelection 点击多选 ContiguousSelection 鼠标拖拉多选
	def Result_name_show(self, namelist):
		self.result_name = namelist[0]
		self.curreportlist = [unicode(self.listview_result.item(x).text()) for x in range(self.listview_result.count())]
		if self.result_name not in self.curreportlist:		#如果列表中没有要生成的报告名称
			self.listview_result.addItem(self.result_name)
		self.listview_result.setSelectionMode(PyQt4.QtGui.QAbstractItemView.SingleSelection)
		self.text_show(u'报告已生成！')

	def _openxls(self, ):
		self.report_current = unicode(self.listview_result.currentItem().text())
		self.lineEdit_man.setText(self.report_current)
		try:
			win32api.ShellExecute(0, 'open', self.report_current, '', '', 1)
		except:
			self.text_show(u'打开excel失败，请手动到Result目录下打开!')
			logger.exception('err with open result excel: ')

	# 封了一遍打印
	def text_show(self, inin):
		self.textBrowser_log.append(inin)

	def isJenkins(self):
		"""
		初始化了勾选的值。
		判断重启是否勾选，勾选是2，不勾选是0.
		然后根据是否勾选来确定左下角的用例执行间隔是否点亮。不勾选时点亮
		"""
		if self.checkBox_kakou.checkState() ==2:
			self.lineEdit_cgi_delay.setDisabled(False)
		else:
			self.lineEdit_cgi_delay.setDisabled(True)



	def config_read(self):
		"""
		读配置文件，调用读取文件的函数
		:return: dict 组成的list,现在只有一个设备，取了0.
		"""
		dev_path = './its_devinfo.ini'
		if os.path.exists(dev_path):
			self.Dev_t = DevInfo_Get()
			config_get = self.Dev_t.read_cfile()[0]
			host = config_get['ip']
			self.lineEdit_ip.setText(host)
			server_host = config_get['serverip']
			self.lineEdit.setText(server_host)
			passwd_admin = config_get['passwd']
			self.lineEdit_passwd.setText(passwd_admin)
			teluser = config_get['teluser']
			self.lineEdit_tel_user.setText(teluser)
			telpasswd = config_get['telpasswd']
			self.lineEdit_tel_passwd.setText(telpasswd)
		else:
			logger.error('found its_devinfo.ini err: ')
			pass

	# 全部界面置灰，除了按钮
	def _all_start(self):
		self.lineEdit.setEnabled(False)
		#self.pushButton.setEnabled(False)
		self.pushButton_read.setEnabled(False)
		self.lineEdit_ip.setEnabled(False)
		self.lineEdit_user.setEnabled(False)
		self.lineEdit_passwd.setEnabled(False)
		self.lineEdit_tel_user.setEnabled(False)
		self.lineEdit_tel_passwd.setEnabled(False)
		#self.lineEdit_timeout.setEnabled(False)
		self.pushButton_purpose.setEnabled(False)

	# 全部按钮激活
	def _stop_all(self):
		self.lineEdit.setEnabled(True)
		#self.pushButton.setEnabled(True)
		self.pushButton_read.setEnabled(True)
		self.lineEdit_ip.setEnabled(True)
		self.lineEdit_user.setEnabled(True)
		self.lineEdit_passwd.setEnabled(True)
		self.lineEdit_tel_user.setEnabled(True)
		self.lineEdit_tel_passwd.setEnabled(True)
		#self.lineEdit_timeout.setEnabled(True)
		self.pushButton_purpose.setEnabled(True)
		self.pushButton_recv.setEnabled(True)

	# 重写关闭函数，防止打包后关软件报错
	def closeEvent(self, event):
		result = QMessageBox.question(self, "Confirm ...", "Sure to exit ?", QMessageBox.Yes | QMessageBox.No)
		event.ignore()
		if result == QMessageBox.Yes:
			event.accept()


if __name__ == '__main__':
	app = PyQt4.QtGui.QApplication(argv)
	dlg = MainWindow()
	dlg.show()
	exit(app.exec_())

