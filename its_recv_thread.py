# -*- coding: utf-8 -*-
from PyQt4 import QtCore
import logging
import ctypes, datetime
import time, os
import telnetlib
import requests
import platform
import re
import subprocess
from xml.etree import ElementTree as ET

os.path.abspath('.')
from ctypes import *
import its_xlsx

iServerPort = 0
iClientPort = 6699
iWnd = 0

cProxy = ""
pcProductID = ""
iPort = c_int(3000)


logger = logging.getLogger('threads')
recv_flag = 1  # 接收线程的全局变量，负责给打印线程提供是否结束的标志
recv_start = 0  # 开始接收线程打开的标志

dict_brand = {}
dict_brand_sub = {}


# 继承 QThread 类
class RecvThread(QtCore.QThread):
	"""docstring for BigWorkThread"""
	# 声明一个信号，同时返回一个list，同理什么都能返回啦
	finishSignal = QtCore.pyqtSignal(list)

	# 构造函数里增加形参
	def __init__(self, args, parent=None):
		super(RecvThread, self).__init__(parent)
		# 储存参数
		self.flag_t = 1
		self.args = args
		self.mutex = QtCore.QMutex()
		self.stopped = False

	def stop(self,a):
		global recv_flag
		recv_flag = int(a)  # stop异常终止了接收线程
		self.flag_t = 0
		try:
			self.mutex.unlock()
			self.stopped = True
		finally:
			self.mutex.unlock()

	# 重写 run() 函数，在里面干大事。
	def run(self):  # 返回0是xml出现问题，返回
		# 大事
		if self.flag_t == 1:
			try:
				xml_c = XML_GET()
				dict_list = xml_c.get_xx('./resourse/mmyr.xml')
				global dict_brand
				dict_brand = dict_list[0]
				global dict_brand_sub
				dict_brand_sub = dict_list[1]
			except:
				logger.exception('err with xml:')
				self.finishSignal.emit([1])
				return
			do_recv = Dll(self.args)
			xlsxname_back = do_recv.Do_ITS()  # 返回值是excel的存储路径和名字
			logger.debug('One file over with : %s' % xlsxname_back)
			self.finishSignal.emit(xlsxname_back)
		else:
			self.finishSignal.emit([5])


recv_plate = []  # 接收线程的车牌list，负责给打印线程提供需要打印的车牌
path_old_dll = os.getcwd()  # 获取当前目录，方便后续切换回根目录使用


class XML_GET(object):
	def __init__(self, parent=None):
		"""
		初始化
		"""
		pass

	def get_xx(self, xml_path):
		tree = ET.parse(xml_path)
		root = tree.getroot()
		makers = root.findall('maker')
		dict_makers = {}
		dict_id_model = {}
		for maker in makers:
			dict_model = {}
			maker_id = maker.get('id')
			ss = maker.findall("model")
			for model in ss:
				madel_id = model.get('id')
				model_name = model.get('name')
				dict_model[madel_id] = model_name
			maker_name = maker.get('name')
			dict_makers[maker_id] = maker_name
			dict_id_model[maker_id] = dict_model
		return [dict_makers, dict_id_model]


# 辅助类：负责调用sdk的类
class Dll(object):
	"""
	目前抓拍到的内容取了：
	抓拍时间、车牌号码 car_plate 、车道名称、违法代码、车辆品牌、车辆子品牌、车辆类型、车身颜色、是否打电话、
	主驾驶安全带、主驾驶遮阳板、副驾驶遮阳板、纸巾盒、挂坠、主驾驶性别、副驾驶性别。

	"""

	def __init__(self, args):
		self.args_pro = args
		self.ip_its = self.args_pro[0]
		self.user_its = self.args_pro[1]
		self.passwd_its = self.args_pro[2]
		self.tel_user_its = self.args_pro[3]
		self.tel_passwd_its = self.args_pro[4]
		self.recv_timeout_its = self.args_pro[5]
		if len(self.args_pro) == 7:
			self.video_path = self.args_pro[6]
		else:
			pass

	def Setup(self, ip, user, passwd, workmode=0):
		#plat_64 = platform.architecture()
		#logger.debug(plat_64)
		#if '64' in plat_64[0]:
		#	dll_path = path_old_dll + '\\dll\\'
		#else:
		#	dll_path = path_old_dll + '\\dll_32\\'
		dll_path = path_old_dll + '\\dll\\'
		os.chdir(dll_path)  # setup 时进dll目录
		logger.debug('path after chdir is : %s' %os.getcwd())
		self.ip = ip
		self.cIP = c_char_p(self.ip)
		self.cUserName = c_char_p(user)
		self.cPassword = c_char_p(passwd)

		self.dll = ctypes.windll.LoadLibrary('NVSSDK.dll')
		# 定义轻量级以及重量级登录方式
		workmode_set = self.dll.NetClient_SetSDKWorkMode
		workmode_set.argtypes = [ctypes.c_int]
		work_back = workmode_set(workmode)
		# 定义登录
		dllTest = self.dll.NetClient_Startup_V4
		dllTest.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
		# 发送SDK初始化
		nSet = dllTest(iServerPort, iClientPort, iWnd)
		time.sleep(0.5)
		pass

	def Logon(self):
		# 登录
		dllLogOn = self.dll.NetClient_Logon
		# dllLogOn.argtypes = [c_char_p,c_char_p,c_char_p,c_char_p,c_char_p,c_int]
		# 发送登录信息
		self.dllGetSet = 1  # 登录状态，0是登录成功，默认写了1
		for i in range(0, 30):
			self.dllLogOnSet = dllLogOn(cProxy, self.cIP, self.cUserName, self.cPassword, pcProductID, iPort)
			time.sleep(1)
			dllLogOn.restype = ctypes.c_int
			logger.info('Logon id is: %s' % self.dllLogOnSet)
			# print (dllLogOn.restype())
			dllGetLogonStatus = self.dll.NetClient_GetLogonStatus
			dllGetLogonStatus.argtypes = [c_int]
			self.dllGetSet = dllGetLogonStatus(self.dllLogOnSet)  # 登录成功这个会变成0
			time.sleep(0.5)
			self.id = self.dllLogOnSet
			logger.info('Logon Status is: %s' % self.dllGetSet)
			if self.dllGetSet != 0:
				time.sleep(3.5)
			else:
				break
		logger.info('logon id is : %s' % self.dllGetSet)
		if self.dllGetSet == 0:
			return self.dllLogOnSet
		else:
			return None

	def LogOff(self, id):
		dllLogoff = self.dll.NetClient_Logoff
		dllLogoff.restype = ctypes.c_int
		dllLogoff_post = dllLogoff(id)
		logger.debug('log off state is : %s' % dllLogoff_post)
		dll_clean_up = self.dll.NetClient_Cleanup
		back_clean_up = dll_clean_up()
		logger.debug('clean up state is: %s' %back_clean_up)

		return dllLogoff_post

	def TelnetOpen(self, id):
		try:
			dllChangeTel = self.dll.NetClient_SetCommonEnable
			dllChangeTel.restype = ctypes.c_int
			dllTelSet = dllChangeTel(id, 0x12014, 0x7FFFFFFF, 1)
			return dllTelSet
		except Exception as e:
			# print (Exception, e)
			logging.debug('Tel open err: %s ' % e)
			return None

	def Open_tel(self, ):
		ip = self.ip_its
		user = self.user_its
		passwd = self.passwd_its
		# port_in = 3001
		logon_id = 0
		try:
			self.Setup(ip, user, passwd, )
			logon_id = self.Logon()
			for i in range(0, 5):  # 登录失败则登录5次
				if logon_id == None:
					logon_id = self.Logon()
					time.sleep(2)
				else:
					break
			if logon_id != None:
				id_output = 'Logon id is: ' + str(logon_id)
				logging.debug('Open tel with %s ok! ' % id_output)
				try:
					self.telnet_state = self.TelnetOpen(logon_id)
					for j in range(0, 10):
						if self.telnet_state == None:
							self.telnet_state = self.TelnetOpen(logon_id)
						else:
							break
					logger.debug('tel open state back : %s' % self.telnet_state)
					if int(self.telnet_state) == 0:
						logging.debug('Dll Log: Telnet open Successed ! ')
					else:
						logging.info('Dll Log Err: Telnet open Failed !!')
				except Exception as err_telnet:
					logging.debug('Error with open tel : %s' % err_telnet)
			else:
				logging.info('Dll Log Err: Logon Failed, Check PLS.%s' % ip)
				self.telnet_state = 4
				return self.telnet_state
		except Exception as err:
			logging.debug('Error with Setup or logon : %s' % err)
		finally:
			# os.chdir(self.path_old_dll)        #开启telnet后回到原始目录
			return self.telnet_state

	# 交通图片流接收
	# @timeout(20)
	def ITSPicStream(self, ):
		logger.debug('its starting ! pwd is : %s' % os.getcwd())
		global recv_flag
		recv_flag = 1
		# 拼excel存储路径和图片存储路径
		now = datetime.datetime.now()
		localtime_z = now.strftime('%Y%m%d')
		localtime_min = now.strftime('%Y%m%d%H%M')
		if os.path.isdir(self.video_path):
			self.video_name = (os.path.split(self.video_path)[-1])
		else:
			self.video_name = os.path.splitext((os.path.split(self.video_path)[-1]))[0]
		self.path_dst = '..\\.\\Result\\' + localtime_min + '_' + self.video_name + '.xlsx'  # name从视频地址的名字获取;这个路径不能随便
		file_dir = '..\\.\\Result\\' + localtime_z + '\\' + self.ip + '\\'
		# pic_path = '.\\'+ localtime_z + '\\'+ self.ip +' \\'
		if not os.path.exists(file_dir):
			os.makedirs(file_dir)

		recv_id = [0]  # 接收线程的id好号，用来停止接收用
		stop_flag = [0]  # 停止接收使用的计数器，用来统计间隔了多少秒没有记录用的

		# 所有字典
		dict_car_type = {0: '未知车型', 1: '两厢轿车', 2: '轿车', 3: '轿跑', 4: '小型轿车', 5: '微型轿车', 6: 'MPV', 7: 'SUV', 8: '大型客车',
						 9: '中型客车', 10: '面包车', 11: '微型面包车', 12: '大货车', 13: '中型货车', 14: '油罐车', 15: '吊车', 16: '渣土车',
						 17: '小货车', 18: '皮卡', 19: '微卡', 20: '二轮车', 21: '三轮车', 22: '行人', 23: '车牌挂偏', 24: '车牌检测',
						 25: '车头', 26: '车尾', 27: '车灯', 28: 'SUV/MPV', 29: '挂车', 30: '未知车型', }

		dict_car_color = {0: '白色', 1: '红色', 2: '黄色', 3: '黄色', 4: '蓝色', 5: '绿色', 6: '绿色', 7: '紫色', 8: '粉色', 9: '黑色',
						  10: '红色', 11: '黄色', 12: '黄色', 13: '灰色', 14: '黄色', 15: '蓝色', 16: '蓝色', 17: '绿色', 18: '绿色',
						  19: '白色', 20: '绿色', 21: '青色', 22: '黄色', 23: '红色', 24: '蓝色', 25: '蓝色', 26: '灰色', 27: '紫色',
						  28: '紫色', 29: '棕色', 30: '棕色', 31: '棕色', 99: '未知'}

		dict_bool = {0: '否', 1: '是'}
		dict_bool_safe_belt = {0: '是', 1: '否'}
		dict_sex = {0: '未知', 1: '男', 2: '女'}

		# 初始化excel类，并打开路径下的excel，准备接下来写入使用
		try:
			XLS = its_xlsx.XLS_WRITE()
			XLS.open_xlsx(self.path_dst)
		except:
			logger.exception('err with xls open: ')
			return 2

		def _xls_do(result_list):
			XLS.wirte_its_in(result_list)

		# 所有结构体定义
		class RECT(Structure):
			_fields_ = [('left', c_int), ('top', c_int), ('right', c_int), ('bottom', c_int)]

		class RECT_S(Structure):
			_fields_ = [('left', c_short), ('top', c_short), ('right', c_short), ('bottom', c_short)]

		class STRCT_BRAND(Structure):
			_fields_ = [('uiBrandType', c_uint), ('uiSubBrand', c_uint), ('uiSubBrandYearStart', c_uint),
						('uiSubBrandYearEnd', c_uint), ('stRectLogo', RECT), ('uiConfid', c_uint)]

		class PicTime(Structure):  # 4*8 = 32 bytes
			_fields_ = [('uiyear', c_uint), ('uimonth', c_uint), ('uiday', c_uint), ('uiweek', c_uint),
						('uihour', c_uint), ('uiminute', c_uint), ('uisecond', c_uint), ('uimill', c_uint)]

		class PicData(Structure):  # 32 +4 + 8 =44
			_fields_ = [('pictime', PicTime), ('idatalen', c_int), ('pcPicData', (POINTER(c_char)))]

		class ItsPicStream(Structure):
			_fields_ = [('istructlen', c_int), ('ichannelid', c_int), ('cplate', c_char * 32), ('iplatecolor', c_int),
						('iPlateType', c_int), ('icarcolor', c_int), ('tplaterange', RECT), ('icharnum', c_int),
						('icharconfid', c_int * 12), ('iplateconfid', c_int), ('irecordnum', c_int),
						('fspeed', c_float), ('idirection', c_int), ('ialarmtype', c_int), ('ccameraip', c_char * 16),
						('iredbegin', c_int), ('iredend', c_int), ('ipiccount', c_int), ('isize', c_int),
						('ptPicData', POINTER(PicData)), ('ptPicData2', POINTER(PicData)),
						('ptPicData3', POINTER(PicData)), ('ptPicData4', POINTER(PicData)),
						('ptPicData5', POINTER(PicData)), ('ptPicData6', POINTER(PicData)),
						('ptPicData7', POINTER(PicData)), ('ptPicData8', POINTER(PicData)), ('iPlatCount', c_int),
						('ptPlatData', POINTER(PicData)), ('iFaceCount', c_int), ('ptFaceData', POINTER(PicData)),
						('ptFaceData2', POINTER(PicData)), ('ptFaceData3', POINTER(PicData)), ('iPreset', c_int),
						('iArea', c_int), ('cFileName', c_char * 32), ('lCarSerialNum', c_long), ('iPictureNum', c_int),
						('iPicType', c_int), ('iPlatePicLen', c_int), ('iFacePicNum', c_int),
						('cChannelName', c_char * 64), ('cChannelDirection', c_char * 64), ('cCrossingID', c_char * 64),
						('cCrossingName', c_char * 64), ('iCarRegionNum', c_int), ('tCarRegion', RECT),
						('iTargetType', c_int), ('iFacePicLen', c_int * 3), ('iRecordAttr', c_int),
						('iLinkageChannelNo', c_int), ('iLinkageNo', c_int), ('cLinkageCameraIP', c_char * 16),
						('iVehicleBrand', c_int), ('tFaceRegion', RECT_S), ('iAlgIllgalType', c_int),
						('iAlarmCode', c_int), ('sMergePicNum', c_short), ('sMergeType', c_short),
						('sMergePercent', c_short), ('sMergeOSDSize', c_short), ('sMergeOSDType', c_short),
						('sSingleOSDSize', c_short), ('sSingleOSDType', c_short), ('sOriginalImgWidth', c_short),
						('sOriginalImgHeight', c_short), ('tVehicleRegion', RECT_S), ('tCopilotRegion', RECT_S),
						('cCaptureTimeEx2', c_char * 40), ('iCaptureLenEx2', c_int * 5),
						('cUserDefChannelID', c_char * 64), ('sBodyOfCarLeight', c_short),
						('cSecurityCode', c_char * 288), ('iSpeedPercent', c_int),
						('cLinkPanoramaCapUUID', c_char * 128), ('iRedBeginTimeMS', c_int), ('iRedEndTimeMS', c_int),
						('iIPDCapType', c_int), ('cAlarmCode', c_char * 16), ('iCarFeatures', c_int * 2),
						('stBrandInfo', STRCT_BRAND), ('iMainDriverSex', c_int), ('iCopilpt', c_int),
						('iNewTargetType', c_int), ('iRealImgWidth', c_int), ('iRealImgHeight', c_int)]

		PICTIME = PicTime()  # 抓拍时间结构体实例化
		PICDATA = PicData()  # 抓拍图片结构体实例化
		PICDATA.pictime = PICTIME
		SNAPPICSTREAM = ItsPicStream()  # 抓拍结果大结构体实例化
		rect = RECT()  # 图片区域实例化
		SNAPPICSTREAM.tplaterange = rect
		SNAPPICSTREAM.tCarRegion = rect
		rect_s = RECT_S()  # short图片区域实例化
		SNAPPICSTREAM.tFaceRegion = rect_s
		SNAPPICSTREAM.tVehicleRegion = rect_s
		SNAPPICSTREAM.tCopilotRegion = rect_s
		strct_brand = STRCT_BRAND()  # 车辆信息，包括车辆品牌等实例化
		SNAPPICSTREAM.stBrandInfo = strct_brand
		iCarFeatures_ARR = (c_int * 2)  # 车辆附加信息，包括安全带，遮挡，纸巾盒等的数组
		iCarFeatures_array = iCarFeatures_ARR()
		SNAPPICSTREAM.iCarFeatures = iCarFeatures_array

		SNAPPICSTREAM.isize = sizeof(PICDATA)
		SNAPPICSTREAM.ptPicData = pointer(PICDATA)  # 8个大图指针占位，目前只对第一张图片进行了存储
		SNAPPICSTREAM.ptPicData2 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData3 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData4 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData5 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData6 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData7 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData8 = pointer(PICDATA)
		SNAPPICSTREAM.ptPlatData = pointer(PICDATA)  # 人脸图片3个指针占位，目前未使用
		SNAPPICSTREAM.ptFaceData2 = pointer(PICDATA)
		SNAPPICSTREAM.ptFaceData3 = pointer(PICDATA)

		# 回调函数处理
		def picstream(uiRecvID, lCommand, pvBuf, iBufLen, pvUser):
			stop_flag[0] = 0
			recv_id[0] = uiRecvID  # 图片流ID，用来结束接收用的
			cardetail = pvBuf.contents
			# 车辆信息获取
			road_id = cardetail.ichannelid  # 车道号
			car_plate = cardetail.cplate  # 车牌号
			car_color = dict_car_color[cardetail.icarcolor]  # 车身颜色
			illegal_code = cardetail.iAlarmCode  # 违法代码
			if cardetail.stBrandInfo.uiBrandType != 0:
				car_brand = dict_brand[str(cardetail.stBrandInfo.uiBrandType)]  # 车辆品牌
				car_brand_pro = dict_brand_sub[str(cardetail.stBrandInfo.uiBrandType)][
					str(cardetail.stBrandInfo.uiSubBrand)]  # 车辆子品牌
			else:
				car_brand = '未知'
				car_brand_pro = '未知'
			car_type = dict_car_type[cardetail.iNewTargetType]  # 车辆类型
			# 对车辆附加属性进行二进制分析，按位处理
			if pvBuf.contents.iCarFeatures[0] != 0:
				carfeat_bin = list((bin(cardetail.iCarFeatures[0])[2:]).zfill(12))  # 对返回的数字取二进制，去掉开头的0b字样，变成纯二进制list
				main_safe_belt = dict_bool_safe_belt[int(carfeat_bin[-1])]
				do_phone = dict_bool[int(carfeat_bin[-2])]
				main_sun = dict_bool[int(carfeat_bin[-3])]  ## 主驾驶遮阳板
				sub_sun = dict_bool[int(carfeat_bin[-4])]  # 副驾驶遮阳板
				pendant = dict_bool[int(carfeat_bin[-7])]  # 挂坠
				paper_box = dict_bool[int(carfeat_bin[-8])]  # 纸巾盒
			else:
				main_safe_belt = '是'
				do_phone = '否'
				main_sun = '否'
				sub_sun = '否'
				pendant = '否'
				paper_box = '否'
			main_sex = dict_sex[cardetail.iMainDriverSex]  # 主驾驶性别
			sub_sex = dict_sex[cardetail.iCopilpt]  # 副驾驶性别
			recv_plate.append(car_plate)
			if len(recv_plate) > 20:
				recv_plate.pop(0)
			pic_len = cardetail.ptPicData.contents.idatalen  # 图片长度
			pic_time = cardetail.ptPicData.contents.pictime  # 抓拍时间
			logger.debug('##################################')
			# 从pcPicData这个字符串指针的地址，到字符串长度结束的字符，拿出来，就是图片数据
			sss = string_at(addressof(cardetail.ptPicData.contents.pcPicData.contents), pic_len)
			# 拼下图片名称的时间, 去掉了一个uweek
			time_year = '20' + str(pic_time.uiyear)
			time_mill = (str(pic_time.uimill)).zfill(3)
			time_list = [time_year, str(pic_time.uimonth), str(pic_time.uiday), str(pic_time.uihour),
						 str(pic_time.uiminute), str(pic_time.uisecond), time_mill]
			time_middle = time_list[1:-1]
			time_middle_back = []
			for tt in time_middle:
				if len(tt) < 2:
					tt = tt.zfill(2)
				time_middle_back.append(tt)
			time_middle_back.insert(0, time_list[0])
			time_middle_back.append(time_list[-1])
			del time_middle
			time_str = ''.join(time_list)
			del time_list
			time_over = '-'.join(time_middle_back)

			# 文件名给保存图片使用，图片路径给excel写入图片路径使用。
			file_name = file_dir + '/' + time_str + '_' + str(road_id) + '_' + car_plate + '.jpg'
			pic_path = '.\\' + localtime_z + '\\' + self.ip + '\\' + time_str + '_' + str(
				road_id) + '_' + car_plate + '.jpg'
			with open(file_name, 'wb') as f:
				f.write(sss)
			result_list = []
			result_list.insert(0, str(cardetail.ccameraip))  # 相机ip
			result_dict = {}
			result_dict['snap_time'] = time_over
			result_dict['cplate'] = car_plate
			result_dict['road_num'] = road_id
			result_dict['alarm_code'] = illegal_code  # 违法代码
			result_dict['car_brand'] = car_brand
			result_dict['car_brand_pro'] = car_brand_pro
			result_dict['car_type'] = car_type
			result_dict['car_color'] = car_color
			result_dict['do_phone'] = do_phone
			result_dict['main_safe_belt'] = main_safe_belt
			result_dict['main_sun'] = main_sun
			result_dict['sub_sun'] = sub_sun
			result_dict['paper_box'] = paper_box
			result_dict['pendant'] = pendant
			result_dict['main_sex'] = main_sex
			result_dict['sub_sex'] = sub_sex
			result_dict['pic_path'] = '=HYPERLINK("' + pic_path + '","' + pic_path + '")'
			result_list.append(result_dict)
			_xls_do(result_list)
			del result_list
			# 读了地址，没调出来。这是调的车牌。
			# address_pic_len = addressof(pvBuf)
			# cplate = string_at(address_pic_len+32+32+4,32)
			# print 'address : %s' %cplate
			return lCommand

		# 回调定义及初始化
		PIC_NOTIFY = WINFUNCTYPE(c_int, c_uint, c_int, POINTER(ItsPicStream), c_int, c_void_p)  # (picstream)
		self._picst_do = PIC_NOTIFY(picstream)  # 创建回调函数

		class NetPicPara(Structure):
			_fields_ = [('istructlen', c_int), ('ichannel', c_int), ('cbkPicStreamNotify', PIC_NOTIFY),
						('pvuser', c_void_p)]
		len_netpicpara = sizeof(NetPicPara)
		NETPIC = NetPicPara()
		NETPIC.istructlen = sizeof(NETPIC)
		NETPIC.ichannel = 0
		NETPIC.cbkPicStreamNotify = self._picst_do  # 结构体中的回调 函数赋值：回调的指针
		NETPIC.pvuser = None
		netpic_pointer = pointer(NETPIC)
		startrec = self.dll.NetClient_StartRecvNetPicStream
		back = c_int(0)
		back_id = ctypes.POINTER(ctypes.c_int)(back)
		startrec.argtypes = [c_int, POINTER(NetPicPara), c_int, POINTER(c_int)]
		get_startrec_post = startrec(self.id, netpic_pointer, len_netpicpara, back_id)

		global recv_start
		recv_start = 1  # 1代表接收线程已经开启成功
		while 1:
			time.sleep(1)
			stop_flag[0] = stop_flag[0] + 1
			logger.debug('ITS RECV TIMEOUT: %s' % stop_flag[0])
			if 20 > stop_flag[0] > 5 and stop_flag[0] % 5 == 0:
				XLS.save_xlsx()
			if stop_flag[0] >= 600:               #ping失效或者超过10分钟没记录，就停止。
				recv_flag = 0
			if recv_flag == 0:  # stop_flag[0] >= int(self.recv_timeout_its):
				XLS.save_xlsx()
				back_stop = self.Stop_ITSPicStream(recv_id[0])
				logger.debug('Stop RECV is : %s' % back_stop)
				try:
					self.LogOff(self.id)
				except:
					logger.exception('Logoff ex! ')
				break
			elif recv_flag == 2:
				try:
					self.LogOff(self.id)
				except:
					logger.exception('Logoff ex! ')
				return 5
		return self.path_dst  # 超时后，返回excel存储路径

	def ITSPicStream22(self, ):
		logger.debug('its starting ! pwd is : %s' % os.getcwd())
		global recv_flag
		recv_flag = 1
		# 拼excel存储路径和图片存储路径
		now = datetime.datetime.now()
		localtime_z = now.strftime('%Y%m%d')
		localtime_min = now.strftime('%Y%m%d%H%M')
		if os.path.isdir(self.video_path):
			self.video_name = (os.path.split(self.video_path)[-1])
		else:
			self.video_name = os.path.splitext((os.path.split(self.video_path)[-1]))[0]
		self.path_dst = '..\\.\\Result\\' + localtime_min + '_' + self.video_name + '.xlsx'  # name从视频地址的名字获取;这个路径不能随便
		file_dir = '..\\.\\Result\\' + localtime_z + '\\' + self.ip + '\\'
		# pic_path = '.\\'+ localtime_z + '\\'+ self.ip +' \\'
		if not os.path.exists(file_dir):
			os.makedirs(file_dir)

		recv_id = [0]  # 接收线程的id好号，用来停止接收用
		stop_flag = [0]  # 停止接收使用的计数器，用来统计间隔了多少秒没有记录用的

		# 所有字典
		dict_car_type = {0: '未知车型', 1: '两厢轿车', 2: '轿车', 3: '轿跑', 4: '小型轿车', 5: '微型轿车', 6: 'MPV', 7: 'SUV', 8: '大型客车',
						 9: '中型客车', 10: '面包车', 11: '微型面包车', 12: '大货车', 13: '中型货车', 14: '油罐车', 15: '吊车', 16: '渣土车',
						 17: '小货车', 18: '皮卡', 19: '微卡', 20: '二轮车', 21: '三轮车', 22: '行人', 23: '车牌挂偏', 24: '车牌检测',
						 25: '车头', 26: '车尾', 27: '车灯', 28: 'SUV/MPV', 29: '挂车', 30: '未知车型', }

		dict_car_color = {0: '白色', 1: '红色', 2: '黄色', 3: '黄色', 4: '蓝色', 5: '绿色', 6: '绿色', 7: '紫色', 8: '粉色', 9: '黑色',
						  10: '红色', 11: '黄色', 12: '黄色', 13: '灰色', 14: '黄色', 15: '蓝色', 16: '蓝色', 17: '绿色', 18: '绿色',
						  19: '白色', 20: '绿色', 21: '青色', 22: '黄色', 23: '红色', 24: '蓝色', 25: '蓝色', 26: '灰色', 27: '紫色',
						  28: '紫色', 29: '棕色', 30: '棕色', 31: '棕色', 99: '未知'}

		dict_bool = {0: '否', 1: '是'}
		dict_bool_safe_belt = {0: '是', 1: '否'}
		dict_sex = {0: '未知', 1: '男', 2: '女'}

		# 初始化excel类，并打开路径下的excel，准备接下来写入使用
		try:
			XLS = its_xlsx.XLS_WRITE()
			XLS.open_xlsx(self.path_dst)
		except:
			logger.exception('err with xls open: ')
			return 2

		def _xls_do(result_list):
			XLS.wirte_its_in(result_list)

		# 所有结构体定义
		class RECT(Structure):
			_fields_ = [('left', c_int), ('top', c_int), ('right', c_int), ('bottom', c_int)]

		class RECT_S(Structure):
			_fields_ = [('left', c_short), ('top', c_short), ('right', c_short), ('bottom', c_short)]

		class STRCT_BRAND(Structure):
			_fields_ = [('uiBrandType', c_uint), ('uiSubBrand', c_uint), ('uiSubBrandYearStart', c_uint),
						('uiSubBrandYearEnd', c_uint), ('stRectLogo', RECT), ('uiConfid', c_uint)]

		class PicTime(Structure):  # 4*8 = 32 bytes
			_fields_ = [('uiyear', c_uint), ('uimonth', c_uint), ('uiday', c_uint), ('uiweek', c_uint),
						('uihour', c_uint), ('uiminute', c_uint), ('uisecond', c_uint), ('uimill', c_uint)]

		class PicData(Structure):  # 32 +4 + 8 =44
			_fields_ = [('pictime', PicTime), ('idatalen', c_int), ('pcPicData', (POINTER(c_char)))]

		class ItsPicStream(Structure):
			_fields_ = [('istructlen', c_int), ('ichannelid', c_int), ('cplate', c_char * 32), ('iplatecolor', c_int),
						('iPlateType', c_int), ('icarcolor', c_int), ('tplaterange', RECT), ('icharnum', c_int),
						('icharconfid', c_int * 12), ('iplateconfid', c_int), ('irecordnum', c_int),
						('fspeed', c_float), ('idirection', c_int), ('ialarmtype', c_int), ('ccameraip', c_char * 16),
						('iredbegin', c_int), ('iredend', c_int), ('ipiccount', c_int), ('isize', c_int),
						('ptPicData', POINTER(PicData))]

		PICTIME = PicTime()  # 抓拍时间结构体实例化
		PICDATA = PicData()  # 抓拍图片结构体实例化
		PICDATA.pictime = PICTIME
		SNAPPICSTREAM = ItsPicStream()  # 抓拍结果大结构体实例化
		rect = RECT()  # 图片区域实例化
		SNAPPICSTREAM.tplaterange = rect
		SNAPPICSTREAM.tCarRegion = rect
		rect_s = RECT_S()  # short图片区域实例化
		SNAPPICSTREAM.tFaceRegion = rect_s
		SNAPPICSTREAM.tVehicleRegion = rect_s
		SNAPPICSTREAM.tCopilotRegion = rect_s
		strct_brand = STRCT_BRAND()  # 车辆信息，包括车辆品牌等实例化
		SNAPPICSTREAM.stBrandInfo = strct_brand
		iCarFeatures_ARR = (c_int * 2)  # 车辆附加信息，包括安全带，遮挡，纸巾盒等的数组
		iCarFeatures_array = iCarFeatures_ARR()

		SNAPPICSTREAM.isize = sizeof(PICDATA)
		SNAPPICSTREAM.ptPicData = pointer(PICDATA)  # 8个大图指针占位，目前只对第一张图片进行了存储

		# 回调函数处理
		def picstream(uiRecvID, lCommand, pvBuf, iBufLen, pvUser):
			stop_flag[0] = 0
			recv_id[0] = uiRecvID  # 图片流ID，用来结束接收用的
			cardetail = pvBuf.contents
			# 车辆信息获取
			road_id = cardetail.ichannelid  # 车道号
			car_plate = cardetail.cplate  # 车牌号
			car_color = dict_car_color[cardetail.icarcolor]  # 车身颜色
			# illegal_code = cardetail.iAlarmCode  # 违法代码
			# 一次打印 车牌，车辆品牌，车辆子品牌
			logger.error('car plate: %s' % car_plate)

			recv_plate.append(car_plate)
			if len(recv_plate) > 8:
				recv_plate.pop(0)

			pic_len = cardetail.ptPicData.contents.idatalen  # 图片长度
			pic_time = cardetail.ptPicData.contents.pictime  # 抓拍时间
			logger.debug('##################################')
			# 从pcPicData这个字符串指针的地址，到字符串长度结束的字符，拿出来，就是图片数据
			sss = string_at(addressof(cardetail.ptPicData.contents.pcPicData.contents), pic_len)
			# 拼下图片名称的时间, 去掉了一个uweek
			time_year = '20' + str(pic_time.uiyear)
			time_mill = (str(pic_time.uimill)).zfill(3)
			time_list = [time_year, str(pic_time.uimonth), str(pic_time.uiday), str(pic_time.uihour),
						 str(pic_time.uiminute), str(pic_time.uisecond), time_mill]
			time_middle = time_list[1:-1]
			time_middle_back = []
			for tt in time_middle:
				if len(tt) < 2:
					tt = tt.zfill(2)
				time_middle_back.append(tt)
			time_middle_back.insert(0, time_list[0])
			time_middle_back.append(time_list[-1])
			del time_middle
			time_str = ''.join(time_list)
			del time_list
			time_over = '-'.join(time_middle_back)

			# 文件名给保存图片使用，图片路径给excel写入图片路径使用。
			file_name = file_dir + '/' + time_str + '_' + str(road_id) + '_' + car_plate + '.jpg'
			pic_path = '.\\' + localtime_z + '\\' + self.ip + '\\' + time_str + '_' + str(
				road_id) + '_' + car_plate + '.jpg'
			with open(file_name, 'wb') as f:
				f.write(sss)

			result_list = []
			result_list.insert(0, str(cardetail.ccameraip))  # 相机ip
			result_dict = {}
			result_dict['snap_time'] = time_over
			result_dict['cplate'] = car_plate
			result_dict['road_num'] = road_id
			result_dict['alarm_code'] = 0  # 违法代码
			result_dict['car_brand'] = 0
			result_dict['car_brand_pro'] = 0
			result_dict['car_type'] = 0
			result_dict['car_color'] = car_color
			result_dict['do_phone'] = 0
			result_dict['main_safe_belt'] = 0
			result_dict['main_sun'] = 0
			result_dict['sub_sun'] = 0
			result_dict['paper_box'] = 0
			result_dict['pendant'] = 0
			result_dict['main_sex'] = 0
			result_dict['sub_sex'] = 0
			result_dict['pic_path'] = '=HYPERLINK("' + pic_path + '","' + pic_path + '")'
			result_list.append(result_dict)
			_xls_do(result_list)
			del result_list
			# 读了地址，没调出来。这是调的车牌。
			# address_pic_len = addressof(pvBuf)
			# cplate = string_at(address_pic_len+32+32+4,32)
			# print 'address : %s' %cplate
			return lCommand

		# 回调定义及初始化
		PIC_NOTIFY = WINFUNCTYPE(c_int, c_uint, c_int, POINTER(ItsPicStream), c_int, c_void_p)  # (picstream)
		self._picst_do = PIC_NOTIFY(picstream)  # 创建回调函数

		class NetPicPara(Structure):
			_fields_ = [('istructlen', c_int), ('ichannel', c_int), ('cbkPicStreamNotify', PIC_NOTIFY),
						('pvuser', c_void_p)]

		len_netpicpara = sizeof(NetPicPara)
		NETPIC = NetPicPara()
		NETPIC.istructlen = sizeof(NETPIC)
		NETPIC.ichannel = 0
		NETPIC.cbkPicStreamNotify = self._picst_do  # 结构体中的回调 函数赋值：回调的指针
		NETPIC.pvuser = None
		netpic_pointer = pointer(NETPIC)
		startrec = self.dll.NetClient_StartRecvNetPicStream

		back = c_int(0)
		back_id = ctypes.POINTER(ctypes.c_int)(back)
		startrec.argtypes = [c_int, POINTER(NetPicPara), c_int, POINTER(c_int)]
		get_startrec_post = startrec(self.id, netpic_pointer, len_netpicpara, back_id)

		global recv_start
		recv_start = 1  # 1代表接收线程已经开启成功

		while 1:
			time.sleep(1)
			stop_flag[0] = stop_flag[0] + 1
			logger.debug('ITS RECV TIMEOUT: %s' % stop_flag[0])
			if 20 > stop_flag[0] > 5 and stop_flag[0] % 5 == 0:
				XLS.save_xlsx()
			elif stop_flag[0] >= int(self.recv_timeout_its):
				XLS.save_xlsx()
				back_stop = self.Stop_ITSPicStream(recv_id[0])
				logger.debug('Stop RECV is : %s' % back_stop)
				if back_stop != 0:
					try:
						self.LogOff(self.id)
					except:
						logger.exception('Logoff ex! ')
				recv_flag = 0
				break
		return self.path_dst  # 超时后，返回excel存储路径

	# 停止接收交通图片流
	def Stop_ITSPicStream(self, recvid):
		Stoprec = self.dll.NetClient_StopRecvNetPicStream
		Stoprec.argtypes = [c_uint]
		get_stoprec_post = Stoprec(recvid)
		return get_stoprec_post

	# 全帧获取，用来获取帧的，暂时没用上，勿删
	def FullFrame(self):
		time_now = datetime.datetime.now()
		localtime_z = time_now.strftime('%Y%m%d%H%M%S')
		startrecv_id, recv_status = self.GetVideoStart(self.id, 0, 0)

		def picstream(uiRecvID, ulStreamType, cData, iLen, iUser, iUserData):
			sss = string_at(addressof(cData), iLen)
			file_name = 'D:/cc/' + localtime_z + '.txt'
			with open(file_name, 'wb') as ff:
				ff.write(sss)
			time.sleep(3)
			return 1

		PIC_NOTIFY = WINFUNCTYPE(c_int, c_uint, c_uint, POINTER(c_ubyte), c_int, c_int, c_void_p)  # (picstream)

		self._picst_do_2 = PIC_NOTIFY(picstream)  # 创建回调函数
		# ss= pointer(PIC_NOTIFY)

		back = c_void_p()
		back_id = ctypes.POINTER(ctypes.c_void_p)(back)

		startrec = self.dll.NetClient_SetFullStreamNotify_V4

		startrec.argtypes = [c_int, PIC_NOTIFY, c_void_p]
		get_startrec_post = startrec(startrecv_id, self._picst_do_2, back_id)
		while 1:
			time.sleep(1)
		# print get_startrec_post
		# return get_startrec_post

	# 交通图片流执行
	def Do_ITS(self, ):
		"""
		:return:包括：1：xml打开失败（在父线程中被调用，不在这）；2：excel打开失败；3：接收函数出现错误；4：logon失败；5: 异常停止
		正常执行完毕时返回excel的路径。
		"""
		global recv_start
		global recv_flag
		recv_flag = 1
		try:
			os.chdir(path_old_dll)
			self.Setup(self.ip_its, self.user_its, self.passwd_its)
			idid = self.Logon()
		except:
			os.chdir(path_old_dll)  # 登录有问题，使用完毕就切换回去
			logger.exception('err with dll logon:')
			return [4]
		if idid != None:
			# tel线程已初始化dll，尝试能否直接使用
			time.sleep(2)
			try:
				its_back = self.ITSPicStream()
			except:
				os.chdir(path_old_dll)  # 接收函数失败后返回初始目录
				return [3]
			if its_back == 2:  # 返回2代表excel打开失败了
				recv_flag = 0
				recv_start = 0
				os.chdir(path_old_dll)  # 打开excel失败后返回初始目录
				return [2]
			elif its_back == 5:  # 异常终止了
				os.chdir(path_old_dll)
				recv_start = 0
				return [5]
			else:
				os.chdir(path_old_dll)  # 跑完一个excel后，回到原目录，方便下一次跑
				recv_start = 0
				return [self.path_dst]
		else:
			os.chdir(path_old_dll)  # 登录失败时，返回初始目录
			return [4]  # 返回4代表logon失败了

time_delay = 1.0
# 线程：打印线程
class BackThread(QtCore.QThread):
	"""docstring for BigWorkThread"""
	# 声明一个信号，同时返回一个list，同理什么都能返回啦
	HelpSignal = QtCore.pyqtSignal(list)

	# 构造函数里增加形参
	def __init__(self, parent=None):
		super(BackThread, self).__init__(parent)
		# 储存参数
		self.flag_back = 1
		self.mutex = QtCore.QMutex()
		self.stopped = False
		global time_delay
		time_delay = 1.0
		#self.delay = 1000.0/1000

	def stop(self):
		self.flag_back = 0
		try:
			self.mutex.unlock()
			self.stopped = True
		finally:
			self.mutex.unlock()

	def run(self):
		logger.debug('flag back is :%s' % self.flag_back)
		while self.flag_back:
			if self.flag_back:
				time.sleep(time_delay)
				self.send_plate = recv_plate[:]
				self.send_cgi = cgi_back[:]
				self.HelpSignal.emit([self.send_plate, self.send_cgi])
				del recv_plate[:]
				del cgi_back[:]
			else:
				break


# 线程：发送视频或文件夹地址 的线程
class TelThread(QtCore.QThread):
	"""docstring for BigWorkThread"""
	# 声明一个信号，同时返回一个list，同理什么都能返回啦
	filenameSignal = QtCore.pyqtSignal(list)
	openSignal = QtCore.pyqtSignal(list)
	recvstartSignal = QtCore.pyqtSignal(list)
	finishSignal = QtCore.pyqtSignal(list)
	logSignal = QtCore.pyqtSignal(str)

	# ss_flag = 1

	# 构造函数里增加形参
	def __init__(self, args, parent=None):
		super(TelThread, self).__init__(parent)
		# 储存参数
		self.flag_tel = 1
		self.mutex = QtCore.QMutex()
		self.args = args
		self.stopped = False

	def stop(self):
		self.flag_tel = 0
		try:
			self.mutex.unlock()
			self.stopped = True
		finally:
			self.mutex.unlock()

	def run(self):
		for video_path in self.args[-1]:
			self.formdata_path = video_path.replace('.sdv','')+'.box'
			self.logSignal.emit(u'开始导入设备参数...')
			self.importcgi = ImportThread(self.args,self.formdata_path)
			if self.importcgi.code == '200':
				self.logSignal.emit(u'导入设备参数成功，等待重启...')
				time.sleep(20)
				self.filenameSignal.emit([video_path])
				logger.debug('tel todo : %s' % self.args[-1])
				if self.flag_tel == 1:
					time.sleep(4)
					for re_wait in range(0, 1600):  # 等待开始接收线程，开启后播放视频
						if recv_start == 0:
							time.sleep(0.1)
						else:
							break
					if recv_start == 1:  # 如果接收线程顺利开启，再继续，否则结束
						self.recvstartSignal.emit(['recv start ok'])
						# 开始播放视频或卡口文件夹
						# 开始读取标准文件A1的时间
						'''
						video_dir = os.path.split(video_path)[0]
						if os.path.isdir(video_path):
							video_name = os.path.split(video_path)[-1]
						else:
							video_name = os.path.splitext(os.path.split(video_path)[-1])[0]
						excel_std = video_dir + '\\' + video_name + '.xlsx'
		
						try:
							XLS_tmp = its_xlsx.XLS_WRITE()
							XLS_tmp.open_xlsx(excel_std)
							old_time = XLS_tmp.read_its_xlsx()                #old time 是读取的，需要处理成
						except:
							logger.exception('err with xls open: ')
						'''

						do_recv = Gettel(self.args)
						run_back = do_recv.telnet_do(video_path)  # 返 回值是excel的存储路径和名字
						logger.info('Open tel over ! back status :%s' % run_back)
						self.openSignal.emit([run_back, video_path])  # 返回到主程序，开启接收进程，然后睡3秒等待全局变量生效，再检测
						while self.flag_tel:  # 结束标志不出现，则一直跑
							if recv_flag != 0:
								time.sleep(1)
							else:
								logger.debug('recv_flag should 0 now : %s' % recv_flag)
								break
							#logger.info('recv_flag: %s' %recv_flag)
						time.sleep(2)  # 这两秒：保存excel文件（每秒检测一次）
					else:
						break
			else:
				self.openSignal.emit([2, video_path])  # 返回到主程序，开启接收进程，然后睡3秒等待全局变量生效，再检测
			if video_path == self.args[-1][-1]:
				logger.debug('TelThread :now file is last one ,sleep 10.')
				time.sleep(10)
			else:
				logger.debug('TelThread :now file is not last one ,sleep 30.')
				time.sleep(30)  # 睡10秒，此时第一个接收线程已结束了，开始第二个之前，给文件对比10秒钟
			continue
		self.finishSignal.emit([1])


tn = telnetlib.Telnet()  # 初始化telnet


# 辅助类：负责开启telnet的类
class Gettel():
	def __init__(self, args, parent=None):
		now = datetime.datetime.now()
		self.to_dir = os.getcwd()
		# self.localtime_day = now.strftime('%Y%m%d')
		# self.localtime_hour = now.strftime('%Y%m%d%H')
		# self.localtime_min = now.strftime('%Y%m%d%H%M')
		# self.localtime_sec = now.strftime('%Y%m%d%H%M%S')
		self.args_pro = args
		self.ip_its = self.args_pro[0]
		self.user_its = self.args_pro[1]
		self.passwd_its = self.args_pro[2]
		self.tel_user_its = self.args_pro[3]
		self.tel_passwd_its = self.args_pro[4]
		self.recv_timeout_its = self.args_pro[5]

	# 登录
	def log_on(self, host, user, passwd):
		self.ip = host
		try:
			tn.open(host)
			if 'ogin' in tn.read_until(b"ogin: ", 20):
				tn.write(user.encode('ascii') + b"\n")
			else:
				logger.error('Tel Log Err: no user')
				return False
			if 'assword' in tn.read_until(b"assword: ", 5):
				try:
					tn.write(passwd.encode('ascii') + b"\n")
					ex_back = tn.expect(['\$', '#'], 5)
					if ex_back[0] != -1:
						time.sleep(1)
						logger.info('Tel Log: telnet logon is ok.')
						return True
					else:
						return False
				except Exception as passwdfail:
					logger.error('Tel Log Err: passwd fail : %s ' % passwdfail)
			else:
				logger.error('Tel Log Err: no passwd')
				return False
		except:
			logger.exception('Tel on Exception')
			return False

	# 开telnet
	def _open_tel_net(self, ip, user, passwd, tel_user, tel_passwd, recv_timeout):
		sock_get = Dll([ip, user, passwd, tel_user, tel_passwd, recv_timeout])
		back_num = 1
		try:
			for i in range(2):
				back_sock_str = sock_get.Open_tel()
				logger.info('open tel back is: %s' % back_sock_str)
				if int(back_sock_str) == 0:
					back_num = 0
					break
				elif int(back_sock_str) == 4:
					break
				else:
					time.sleep(1)
					continue
			return back_num
		except:
			logger.exception('Exception')
			return 1

	# # 线程主函数
	def telnet_do(self, video_path):
		host = self.ip_its
		user = self.user_its
		passwd = self.passwd_its
		tel_user = self.tel_user_its
		tel_passwd = self.tel_passwd_its
		time_out = self.recv_timeout_its
		self.log_status = self.log_on(host, tel_user, tel_passwd)  # 直接登录，失败则发送开启telnet
		if self.log_status == False:
			tel_back = self._open_tel_net(host, user, passwd, tel_user, tel_passwd, time_out)
			logger.info('open tel back valueis : %s' % tel_back)
			if tel_back == 0:
				for i in range(0, 5):
					self.log_status_two = self.log_on(host, tel_user, tel_passwd)
					if self.log_status_two == True:
						break
					else:
						logger.error('Tel failed, time is : %s' % i)
						time.sleep(2)
						continue
			else:
				logger.error('Tel open failed!')
				return 0
		else:
			pass
		start_back = 0
		if self.log_status == True or self.log_status_two == True:
			start_back = self.start_video(video_path)
		else:
			pass
		return start_back

	def start_video(self, videopath):  # 需要改成发送路径的指令    以及返回值判断
		key_word = 'nfs'
		path_pro = '/nvs/autotest'
		# 建目录
		order_mkdir = 'mkdir ' + path_pro
		tn.write(order_mkdir.encode('ascii') + b"\n")
		tn_back = tn.expect(['\$', '#'], 5)
		video_path = videopath.replace('\\', '/')
		nfs_index = video_path.find(key_word)
		if nfs_index != -1:
			try:
				logger.info('nfs index : %s' % nfs_index)
				# 挂载
				gx_ip = video_path[2:nfs_index - 1]
				logger.info('gx ip : %s' % gx_ip)
				order_nfs = 'mount -t nfs -o intr,nolock,rsize=1024,wsize=1024 ' + gx_ip + ':/home/' + key_word + '/ ' + path_pro + ' &'
				logger.debug('order nfs : %s' % order_nfs)
				tn.write(order_nfs.encode('ascii') + b"\n")
				tn_back = tn.expect(['\$', '#'], 5)
				time.sleep(3)
				# 执行
				len_index = len(key_word)
				video_sub_path = video_path[nfs_index + len_index:]
				logger.error('with video sub path is : %s' % video_sub_path)
				# path_pro = '/nvs/autotest'
				video_abs_path = path_pro + video_sub_path  # 得到绝对路径，给执行使用。
				if os.path.isfile(videopath):
					order_start_video = 'cd /nvs;./print_ctrl -rp ' + video_abs_path
				else:
					order_start_video = 'cd /nvs;./print_ctrl -pp ' + video_abs_path
				logger.debug('start video order : %s' % order_start_video)
				tn.write(order_start_video.encode('ascii') + b"\n")
				tn_back = tn.expect(['\$', '#'], 5)
				time.sleep(1)
				logger.debug('order start video back : %s' % tn_back[2])
				if tn_back[0] != -1 and 'err' not in tn_back[2] and 'denied' not in tn_back[2]:
					return 1
				else:
					return 0
			except:
				logger.exception('err with send video path:')
				return 0
		else:
			return 0


cgi_back = []  # 第一个元素是当前发送的个数，第二个元素是当前发送的返回码


# 线程：负责发送模拟抓拍的线程
class CgiThread(QtCore.QThread):
	"""
	需要的参数：
	服务器目录，设备ip，用户名，密码, 目录
	"""
	finishSignal = QtCore.pyqtSignal(list)

	# 构造函数里增加形参
	def __init__(self, args, parent=None):
		super(CgiThread, self).__init__(parent)
		# 储存参数
		self.flag_cgi = 1
		self.mutex = QtCore.QMutex()
		self.stopped = False
		self.filenum = 0
		self.args_cgi = args
		self.ip_cgi = self.args_cgi[0]
		self.user_cgi = self.args_cgi[1]
		self.passwd_cgi = self.args_cgi[2]

		self.delay = float(self.args_cgi[3])/1000      # 改成float是为了得到带精度的除法，单位毫秒，所以除以1000
		global time_delay
		time_delay = self.delay
		self.path_cgi = self.args_cgi[-1]  # 目录列表

	def stop(self):
		self.flag_cgi = 0
		try:
			self.mutex.unlock()
			self.stopped = True
		finally:
			self.mutex.unlock()

	def run(self):
		if self.flag_cgi == 1:
			self.times = 0
			logger.debug('into cgi send thread.')
			time.sleep(1)
			self.put_res()
		self.finishSignal.emit([self.times])
		logger.debug('out cgi send thread.')

	def _get_filenums(self):
		for lists in os.listdir(self.path_cgi):
			sub_path = os.path.join(self.path_cgi, lists)
			if os.path.isfile(sub_path):
				if 'Thumbs' not in sub_path:
					self.filenum = self.filenum + 1
		logger.debug('file nums is : %s' % self.filenum)
		return self.filenum

	def _cgi_make(self, cgi_order, data1=''):
		cgi_do = cgi_order
		self.data1 = data1
		self.ip_add = 'http://' + self.ip_cgi + cgi_do
		self.head = {'Accept': 'application/xml, text/xml, */*; q=0.01',
					 'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
					 'Content-Type': 'application/xml;charset=utf-8', 'Accept-Encoding': 'gzip,deflate,sdch',
					 'Accept-Language': 'zh-CN,zh;q=0.8', 'X-Requested-With': 'XMLHttpRequest'}

	def _change_road(self):
		"""
		根据发送过来的当前执行的目录名字，来确定要抓拍哪个车道，其他车道模拟抓拍都会置为false
		先get，然后把所有true替换成false，再正则找到文件夹对应的路径，true
		"""
		self._cgi_make('/CGI/ITS/SimTrigger/RoadWay/channel/1')
		p_get = requests.get(self.ip_add, headers=self.head, auth=(self.user_cgi, self.passwd_cgi), data=self.data1,
							 timeout=1)
		logger.debug('road cgi get back code is : %s' % p_get.status_code)
		get_xml = p_get.text
		if os.path.isdir(self.path_cgi):
			video_name = os.path.split(self.path_cgi)[-1]
		else:
			logger.error('path is not dir, out of road send ! %s' % self.path_cgi)
			# cgi_back.insert(0, 0)        # 当第一位是0，代表road发送有问题了
			# cgi_back.insert(1, 0)
			return 0

		num = int(video_name.split('_')[-1])
		get_xml = get_xml.replace('true', 'false')
		nums = re.compile(r'<roadNum>' + str(num) + '</roadNum>.*?<enable>(.*?)</enable>', re.S)
		put_xml = nums.subn('<roadNum>' + str(num) + '</roadNum >\r\n<enable>true</enable>', get_xml)
		self._cgi_make('/CGI/ITS/SimTrigger/RoadWay/channel/1', data1=put_xml[0])
		p_put = requests.put(self.ip_add, headers=self.head, auth=(self.user_cgi, self.passwd_cgi), data=self.data1,
							 timeout=1)
		logger.debug('road cgi send back code is : %s' % p_put.status_code)
		cgi_back.insert(0, 0)
		cgi_back.insert(1, p_put.status_code)
		return 1

	def put_res(self):
		road_back = 0  # 默认是0，不跑cgi发送。
		try:
			road_back = self._change_road()  # 先改抓拍哪个车道
		except:
			logger.exception('err with road send:')
		if road_back == 1:
			time.sleep(1)
			self.times = 0  # 发送抓拍最小是1，当是0时，代表发送模拟抓拍车道的设置状态
			self._cgi_make('/CGI/ITS/Channels/1/SnapShot/Type/0')
			for i in range(0, int(self._get_filenums())):
				try:
					p1 = requests.put(self.ip_add, headers=self.head, auth=(self.user_cgi, self.passwd_cgi),
									  data=self.data1, timeout=1)
					logger.debug('cgi send back code is : %s' % p1.status_code)
					p1_code = p1.status_code
					# if p1_code != 200:  # 如果cgi发失败了，重试3次，并加入重试的最终结果到全局list，成功则直接添加到全局list
					# 	logger.info('Cgi status code wrong, is : %s, retry 3 times.' % p1_code)
					# 	for q in range(0, 1):  # 失败会重发，尝试3次。成功了就不发了。3次都失败，就少一条记录了。
					# 		p2 = requests.put(self.ip_add, headers=head, auth=(user, passwd), data=data1, timeout=1)
					# 		p2_code = p2.status_code
					# 		cgi_back.insert(0, self.times + 1)
					# 		cgi_back.insert(1, p2_code)
					# 		logger.info('Cgi retry: back code is: %s' % p2_code)
					# 		time.sleep(1)
					# 		if p2_code == 200:
					# 			break
					# 		else:
					# 			continue
					# else:
					cgi_back.insert(1, p1_code)
					self.times += 1
					cgi_back.insert(0, self.times)
				except Exception as err_cgi1:
					logger.error('Err with cgi send! %s' % err_cgi1)

				time.sleep(self.delay)
			time.sleep(20)
			# 发重启
			self._cgi_make('/ISAPI/System/reboot')
			try:
				p3 = requests.put(self.ip_add, headers=self.head, auth=(self.user_cgi, self.passwd_cgi),
								  data=self.data1, timeout=1)
				if p3.status_code != 200:
					requests.put(self.ip_add, headers=self.head, auth=(self.user_cgi, self.passwd_cgi), data=self.data1,
								 timeout=1)
			except:
				logger.exception('cgi reboot with: ')
		else:  # 可能是0，可能None。0是对文件夹路径取最后一位错误，None是发送Road异常了。
			cgi_back.insert(0, 0)
			cgi_back.insert(1, 0)


		# x = Gettel(['192.168.18.134', 'admin', '1111', 'root', 'nvsS3', '50'])
		# x.telnet_do()
		# [self.ip, self.user, self.passwd, self.tel_user, self.tel_passwd, self.recv_timeout])


		# x = CgiThread(['192.168.18.138', 'admin', 'Admin123', 'E:\GX\ITS_PIC'])
		# x.put_res()


class PingThread(QtCore.QThread):
	# 用于检测设备网络情况
	rebootSignal = QtCore.pyqtSignal(str)

	def __init__(self, devip):
		'''
        :param devip: 要ping的IP地址
        '''
		super(PingThread, self).__init__()
		self.flag_ping = 1
		self.devip = devip
		self.mutex = QtCore.QMutex()

	# self.run()

	def stop(self):
		self.flag_ping = 0
		try:
			self.mutex.unlock()
			self.stopped = True
		finally:
			self.mutex.unlock()

	def run(self):
		while self.flag_ping:
			self.recv_num = self.pingresult(self.devip)
			if self.recv_num <= 2:  # 如果ping的4个包中，收到的小于等于2个
				global recv_flag
				recv_flag = 0
				self.rebootSignal.emit(u'检测到设备网络断开！')
				return
			else:
				pass

	def pingresult(self, ip):
		self.p = subprocess.Popen(['ping.exe', ip], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
								  stderr=subprocess.PIPE, shell=True)
		self.out = self.p.stdout.read()
		self.out = unicode(self.out, 'gbk')
		try:
			self.recv_num = int(re.findall(u'已接收 = (.)', self.out)[0])
			return self.recv_num
		except:
			logger.exception(u'未获取到ping包数量！')
			return 0


class ImportThread():
	# 用于导入相机参数
	def __init__(self, args,formdata_filename):
		'''
		
		:param devip: 设备ip
		:param user: 登录用户名
		:param passwd: 登录密码
		:param paramsdir: 参数文件路径
		'''
		# super(ImportThread, self).__init__()
		self.args = args
		self.devip = self.args[0]
		self.user = self.args[1]
		self.passwd = self.args[2]
		self.formdata_filename = formdata_filename
		self.head = {'Accept': 'application/xml, text/xml, */*; q=0.01',
					 'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
					'Accept-Encoding': 'gzip,deflate,sdch',
					 'Accept-Language': 'zh-CN,zh;q=0.8', 'X-Requested-With': 'XMLHttpRequest'}
		self.formdata_name = 'FILE0'
		self.formdata_contenttype = 'application/octet-stream'
		self.cginame = '/CGI/FileUpload/configData/import'
		self.timeout = 10
		self.code = ''
		self.start_run()

	def start_run(self):
		self.url = 'http://'+self.devip+self.cginame
		self.auth = (self.user,self.passwd)
		self.import_cgi()


	def import_cgi(self):
		self.session = requests.session()
		self.session.auth = self.auth
		self.session.headers = self.head
		try:
			self.files = {
				self.formdata_name: (os.path.basename(self.formdata_filename), open(self.formdata_filename, 'rb'),
									 self.formdata_contenttype)
			}
		except:
			logger.error('Not Find File:%s'%self.formdata_filename)
			return
		for i in range(10):		#最大请求次数
			try:
				self.respons = self.session.post(self.url, files=self.files, timeout=self.timeout)
			except:
				logger.exception('import params err:')
				time.sleep(3)
			else:
				self.code = str(self.respons.status_code)
				if self.code == '200':
					break
				else:
					time.sleep(3)
