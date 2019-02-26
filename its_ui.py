# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '1.ui'
#
# Created: Fri Jun 16 15:47:56 2017
#      by: PyQt4 UI code generator 4.10.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
# from PyQt4.phonon import Phonon
import sys
from os import path

try:
	_fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
	def _fromUtf8(s):
		return s

try:
	_encoding = QtGui.QApplication.UnicodeUTF8


	def _translate(context, text, disambig):
		return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
	def _translate(context, text, disambig):
		return QtGui.QApplication.translate(context, text, disambig)


class Ui_MainWindow(object):
	def resourse_path(self, relative_path):
		if hasattr(sys, "_MEIPASS"):
			base_path = sys._MEIPASS
		else:
			base_path = path.abspath(".")
		return path.join(base_path, relative_path)

	def setupUi(self, MainWindow):
		MainWindow.setObjectName(_fromUtf8("MainWindow"))
		MainWindow.resize(900, 500)
		# model =QtGui.QDirModel
		self.font = "font: 9pt \"微软雅黑\";"
		MainWindow.setWindowFlags(QtCore.Qt.WindowMinimizeButtonHint)
		# MainWindow.setFixedSize(MainWindow.width(), MainWindow.height())
		palett1 = QtGui.QPalette()
		palett1.setBrush(QtGui.QPalette.Background,
						 QtGui.QBrush(QtGui.QPixmap(self.resourse_path('resourse/background.png').decode('gb2312'))))
		MainWindow.setAutoFillBackground(True)
		MainWindow.setPalette(palett1)

		icon = QtGui.QIcon()
		icon.addPixmap(QtGui.QPixmap(self.resourse_path('resourse/title.png').decode('gb2312')), QtGui.QIcon.Normal,
					   QtGui.QIcon.Off)
		MainWindow.setWindowIcon(icon)

		self.centralwidget = QtGui.QWidget(MainWindow)
		self.centralwidget.setObjectName(_fromUtf8("centralwidget"))

		self.widget = QtGui.QWidget(self.centralwidget)
		self.widget.setGeometry(QtCore.QRect(20, 10, 860, 460))
		self.widget.setObjectName(_fromUtf8("widget"))
		# self.widget.setVisible(False)
		self.gridLayout = QtGui.QGridLayout(self.widget)
		self.gridLayout.setMargin(0)
		# self.gridLayout.setSpacing(0)
		self.gridLayout.setHorizontalSpacing(15)
		self.gridLayout.setVerticalSpacing(10)
		self.gridLayout.setObjectName(_fromUtf8("gridLayout"))

		#########第一行
		self.label = QtGui.QLabel(self.widget)
		self.label.setObjectName(_fromUtf8("label"))
		self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
		self.lineEdit = QtGui.QLineEdit(self.widget)
		self.lineEdit.setObjectName(_fromUtf8("lineEdit"))
		self.gridLayout.addWidget(self.lineEdit, 0, 1, 1, 1)
		# self.pushButton = QtGui.QPushButton(self.widget)
		# self.pushButton.setObjectName(_fromUtf8("pushButton"))
		# self.gridLayout.addWidget(self.pushButton, 0, 2, 1, 1)
		self.pushButton_read = QtGui.QPushButton(self.widget)
		self.pushButton_read.setObjectName(_fromUtf8("pushButton_read"))
		self.gridLayout.addWidget(self.pushButton_read, 0, 2, 1, 1)
		# 卡口识别率勾选框
		self.checkBox_kakou = QtGui.QCheckBox(self.widget)
		# self.checkBox_kakou.setGeometry(QtCore.QRect(296, 430, 90, 21))
		self.checkBox_kakou.setObjectName(_fromUtf8("checkBox_kakou"))
		self.gridLayout.addWidget(self.checkBox_kakou, 0, 6, 1, 1)
		# 卡口识别率间隔
		self.label_cgi_delay = QtGui.QLabel(self.widget)
		self.label_cgi_delay.setObjectName(_fromUtf8("label_cgi_delay"))
		self.gridLayout.addWidget(self.label_cgi_delay, 0, 7, 1, 1)
		self.lineEdit_cgi_delay = QtGui.QLineEdit(self.widget)
		self.lineEdit_cgi_delay.setObjectName(_fromUtf8("lineEdit_cgi_delay"))
		self.gridLayout.addWidget(self.lineEdit_cgi_delay, 0, 8, 1, 1)
		self.lineEdit_cgi_delay.setEnabled(False)





		# ip
		self.label_ip = QtGui.QLabel(self.widget)
		self.label_ip.setObjectName(_fromUtf8("label_ip"))
		self.gridLayout.addWidget(self.label_ip, 0, 3, 1, 1)
		self.lineEdit_ip = QtGui.QLineEdit(self.widget)
		self.lineEdit_ip.setObjectName(_fromUtf8("lineEdit_ip"))
		self.gridLayout.addWidget(self.lineEdit_ip, 0, 4, 1, 2)

		# 树形
		# self.dirModel = QtGui.QDirModel(self)
		self.dirModel = QtGui.QFileSystemModel(self)
		self.dirModel.setNameFilters(['*.sdv','*.jpg'])
		self.dirModel.setNameFilterDisables(False)
		# 左侧树形
		self.tree_left = QtGui.QTreeView()
		self.gridLayout.addWidget(self.tree_left, 1, 0, 10, 3)

		# 设置根节点的名称
		# self.root.setText(0, 'Protocol')

		#self.tree_left.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAsNeeded)
		#self.tree_left.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)

		self.tree_left.setModel(self.dirModel)
		self.tree_left.setColumnWidth(0, 300)
		#self.tree_left.hideColumn(1)
		self.tree_left.hideColumn(2)
		self.tree_left.hideColumn(3)

		# 用户名
		self.label_user = QtGui.QLabel(self.widget)
		self.label_user.setObjectName(_fromUtf8("label_user"))
		self.gridLayout.addWidget(self.label_user, 1, 3, 1, 1)
		self.lineEdit_user = QtGui.QLineEdit(self.widget)
		self.lineEdit_user.setObjectName(_fromUtf8("lineEdit_user"))
		self.gridLayout.addWidget(self.lineEdit_user, 1, 4, 1, 2)
		# 密码
		self.label_passwd = QtGui.QLabel(self.widget)
		self.label_passwd.setObjectName(_fromUtf8("label_passwd"))
		self.gridLayout.addWidget(self.label_passwd, 1, 6, 1, 1)
		self.lineEdit_passwd = QtGui.QLineEdit(self.widget)
		self.lineEdit_passwd.setObjectName(_fromUtf8("lineEdit_passwd"))
		self.gridLayout.addWidget(self.lineEdit_passwd, 1, 7, 1, 2)
		# Tel用户名
		self.label_tel_user = QtGui.QLabel(self.widget)
		self.label_tel_user.setObjectName(_fromUtf8("label_tel_user"))
		self.gridLayout.addWidget(self.label_tel_user, 2, 3, 1, 1)
		self.lineEdit_tel_user = QtGui.QLineEdit(self.widget)
		self.lineEdit_tel_user.setObjectName(_fromUtf8("lineEdit_tel_user"))
		self.gridLayout.addWidget(self.lineEdit_tel_user, 2, 4, 1, 2)
		# Tel密码
		self.label_tel_passwd = QtGui.QLabel(self.widget)
		self.label_tel_passwd.setObjectName(_fromUtf8("label_tel_passwd"))
		self.gridLayout.addWidget(self.label_tel_passwd, 2, 6, 1, 1)
		self.lineEdit_tel_passwd = QtGui.QLineEdit(self.widget)
		self.lineEdit_tel_passwd.setObjectName(_fromUtf8("lineEdit_tel_passwd"))
		self.gridLayout.addWidget(self.lineEdit_tel_passwd, 2, 7, 1, 2)

		# 超时及接收
		# self.label_timeout = QtGui.QLabel(self.widget)
		# self.label_timeout.setObjectName(_fromUtf8("label_timeout"))
		# self.gridLayout.addWidget(self.label_timeout, 3, 6, 1, 1)
		# self.lineEdit_timeout = QtGui.QLineEdit(self.widget)
		# self.lineEdit_timeout.setObjectName(_fromUtf8("lineEdit_request"))
		# self.gridLayout.addWidget(self.lineEdit_timeout, 3, 7, 1, 2)
		# self.lineEdit_timeout.setValidator(QtGui.QIntValidator(1,1000,self))        # 超时限制为1-1000s

		# 临时区
		##############################################################################################
		# self.pushButton_hebing = QtGui.QPushButton(self.widget)
		# self.pushButton_hebing.setObjectName(_fromUtf8("pushButton_hebing"))
		# self.gridLayout.addWidget(self.pushButton_hebing, 3, 3, 1, 1)




		##############################################################################################
		# 加入列表
		self.pushButton_recv = QtGui.QPushButton(self.widget)
		self.pushButton_recv.setObjectName(_fromUtf8("pushButton_recv"))
		self.gridLayout.addWidget(self.pushButton_recv, 3, 3, 1, 1)

		# 树形获取文字
		self.label_purpose = QtGui.QLabel(self.widget)
		self.label_purpose.setObjectName(_fromUtf8("label_purpose"))
		self.gridLayout.addWidget(self.label_purpose, 4, 3, 1, 1)

		self.lineEdit_purpose = QtGui.QTextEdit(self.widget)
		self.lineEdit_purpose.setObjectName(_fromUtf8("lineEdit_purpose"))
		self.gridLayout.addWidget(self.lineEdit_purpose, 3, 4, 3, 5)

		self.pushButton_purpose = QtGui.QPushButton(self.widget)
		self.pushButton_purpose.setObjectName(_fromUtf8("pushButton_purpose"))
		self.gridLayout.addWidget(self.pushButton_purpose, 5, 3, 1, 1)

		# 命令字符串显示位置
		self.textBrowser_log = QtGui.QTextBrowser(self.widget)
		self.textBrowser_log.setObjectName(_fromUtf8("textBrowser_log"))
		self.gridLayout.addWidget(self.textBrowser_log, 6, 3, 3, 3)

		self.listview_result = QtGui.QListWidget(self.widget)
		self.listview_result.setObjectName(_fromUtf8("listview_result"))
		self.gridLayout.addWidget(self.listview_result, 6, 6, 3, 3)
		# 结果显示位置
		# self.textBrowser_result = QtGui.QTextBrowser(self.widget)
		# self.textBrowser_result.setObjectName(_fromUtf8("textBrowser_result"))
		# self.gridLayout.addWidget(self.textBrowser_result, 7, 6, 2, 3)

		# 手动合并记录
		self.label_man = QtGui.QLabel(self.widget)
		self.label_man.setObjectName(_fromUtf8("label_man"))
		self.gridLayout.addWidget(self.label_man, 10, 3, 1, 1)
		self.lineEdit_man = QtGui.QLineEdit(self.widget)
		self.lineEdit_man.setObjectName(_fromUtf8("lineEdit_man"))
		self.gridLayout.addWidget(self.lineEdit_man, 10, 4, 1, 3)
		self.pushButton_man_browse = QtGui.QPushButton(self.widget)
		self.pushButton_man_browse.setObjectName(_fromUtf8("pushButton_man_browse"))
		self.gridLayout.addWidget(self.pushButton_man_browse, 10, 7, 1, 1)
		self.pushButton_man_do = QtGui.QPushButton(self.widget)
		self.pushButton_man_do.setObjectName(_fromUtf8("pushButton_man_do"))
		self.gridLayout.addWidget(self.pushButton_man_do, 10, 8, 1, 1)

		# 右侧table
		self.table_right = QtGui.QTableWidget(self.widget)
		self.gridLayout.addWidget(self.table_right, 1, 2, 2, 6)
		self.table_right.setColumnCount(6)
		self.table_right.setRowCount(17)
		self.table_right.setHorizontalHeaderLabels([u'参数字段', u'参数类型', u'参数值', u'参数名', u'参数说明'])
		# self.table_right.setColumnWidth(0, 25)
		self.table_right.setColumnWidth(0, 80)
		self.table_right.setColumnWidth(1, 60)
		self.table_right.setColumnWidth(2, 80)
		self.table_right.setColumnWidth(3, 100)
		self.table_right.setColumnWidth(4, 220)
		self.table_right.setVerticalHeaderLabels(
			['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16'])
		for i in range(0, 17):
			self.table_right.setRowHeight(i, 20)
		self.table_right.setVisible(False)

		'''
        # 右侧响应table
        self.table_right_mid = QtGui.QTableWidget(self.widget)
        self.gridLayout.addWidget(self.table_right_mid, 4, 3, 1, 5)
        self.table_right_mid.setColumnCount(5)
        self.table_right_mid.setRowCount(17)
        self.table_right_mid.setHorizontalHeaderLabels([u'参数字段', u'参数类型', u'参数值', u'参数名', u'参数说明'])
        # self.table_right.setColumnWidth(0, 25)
        self.table_right_mid.setColumnWidth(0, 80)
        self.table_right_mid.setColumnWidth(1, 60)
        self.table_right_mid.setColumnWidth(2, 80)
        self.table_right_mid.setColumnWidth(3, 100)
        self.table_right_mid.setColumnWidth(4, 220)
        self.table_right_mid.setVerticalHeaderLabels(
            ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16'])
        for i in range(0, 17):
            self.table_right_mid.setRowHeight(i, 20)
        '''

		MainWindow.setCentralWidget(self.centralwidget)
		self.statusbar = QtGui.QStatusBar(MainWindow)
		self.statusbar.setObjectName(_fromUtf8("statusbar"))
		MainWindow.setStatusBar(self.statusbar)

		self.retranslateUi(MainWindow)
		# self.changemain(MainWindow)
		QtCore.QMetaObject.connectSlotsByName(MainWindow)

	def changemain_old(self, MainWindow1):
		MainWindow1.resize(640, 320)

	def changemain(self, MainWindow):
		MainWindow.resize(640, 600)
		# MainWindow.
		# self.widget2.setVisible(True)

	def retranslateUi(self, MainWindow):
		MainWindow.setWindowTitle(_translate("MainWindow", "算法自动化测试工具V1.0", None))

		# 第一行
		self.label.setText(_translate("MainWindow", "资源地址", None))
		self.lineEdit.setText(_translate("MainWindow", "\\\\192.168.16.136", None))
		# self.pushButton.setText(_translate("MainWindow", "浏览", None))
		self.pushButton_read.setText(_translate("MainWindow", "读取", None))
		self.checkBox_kakou.setText(_translate("MainWindow", "卡口识别率", None))
		self.label_cgi_delay.setText(_translate("MainWindow", "间隔(毫秒)", None))
		self.lineEdit_cgi_delay.setText(_translate("MainWindow", "1000", None))

		self.label_ip.setText(_translate("MainWindow", "设备IP", None))
		self.lineEdit_ip.setText(_translate("MainWindow", "192.168.16.133", None))

		# 第二行
		self.label_user.setText(_translate("MainWindow", "用户名", None))
		self.lineEdit_user.setText(_translate("MainWindow", "Admin", None))
		self.label_passwd.setText(_translate("MainWindow", "密码", None))
		self.lineEdit_passwd.setText(_translate("MainWindow", "1111", None))

		# 第三行
		self.label_tel_user.setText(_translate("MainWindow", "Tel帐号", None))
		self.lineEdit_tel_user.setText(_translate("MainWindow", "root", None))
		self.label_tel_passwd.setText(_translate("MainWindow", "Tel密码", None))
		self.lineEdit_tel_passwd.setText(_translate("MainWindow", "nvsS3", None))

		# 第四行
		# self.label_timeout.setText(_translate("MainWindow", "超时", None))
		# self.lineEdit_timeout.setText(_translate("MainWindow", "120", None))

		# self.pushButton_hebing.setText(_translate("MainWindow", "合并", None))

		# 第五行
		self.pushButton_recv.setText(_translate("MainWindow", "加入列表", None))
		# 第六行
		self.label_purpose.setText(_translate("MainWindow", "测试资源列表", None))
		# 第七行
		self.pushButton_purpose.setText(_translate("MainWindow", "启动测试", None))

		# 第十行
		self.label_man.setText(_translate("MainWindow", "手动生成", None))
		self.lineEdit_man.setText(_translate("MainWindow", "输入或选择路径", None))
		self.pushButton_man_browse.setText(_translate("MainWindow", "浏览", None))
		self.pushButton_man_do.setText(_translate("MainWindow", "生成", None))
		# self.config_read()
