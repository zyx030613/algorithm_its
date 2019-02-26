# coding=utf-8
"""
design:zyx
date:20170802
"""
import ctypes, datetime
import time, os
import logging
from xml.etree import ElementTree as ET
os.path.abspath('.')
from ctypes import *
import its_xlsx
import win32gui

iServerPort = 0
iClientPort = 6699
iWnd = 0

cProxy = ""
# ctypes.POINTER(c_char("/0")*2)
# cProxyn =cProxy()
# cIP = c_char_p(b'192.168.18.138')
# cUserName = c_char_p(b'Admin')
# cUserName1 = cUserName
# cPassword = c_char_p(b'1111')
pcProductID = ""
iPort = c_int(3000)

#logger = logging.getLogger('connect')

class XML_GET():
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
			ss=maker.findall("model")
			for model in ss:
				madel_id = model.get('id')
				model_name = model.get('name')
				dict_model[madel_id] = model_name
			maker_name = maker.get('name')
			dict_makers[maker_id] = maker_name
			dict_id_model[maker_id] = dict_model
		return [dict_makers, dict_id_model]

xml_c = XML_GET()
dict_list = xml_c.get_xx('./resourse/mmyr.xml')
dict_brand = dict_list[0]
dict_brand_sub = dict_list[1]

# if __name__ == '__main__':
class Dll():
	def __init__(self):
		pass

	def Setup(self, dll_path, ip, user, passwd, workmode=0):
		os.chdir(dll_path)
		print os.getcwd()
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
		# print(dllTest)
		dllTest.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
		# _iServerPort,ctypes.c_int_iClientPort,ctypes.c_int_iWnd
		# dllTest.Serverport = ctypes.c_int_iServerPort
		# 发送SDK初始化
		nSet = dllTest(iServerPort, iClientPort, iWnd)
		time.sleep(0.5)
		pass

	def Logon(self):
		# 登录
		dllLogOn = self.dll.NetClient_Logon
		# dllLogOn.argtypes = [c_char_p,c_char_p,c_char_p,c_char_p,c_char_p,c_int]
		# 发送登录信息
		self.dllLogOnSet = dllLogOn(cProxy, self.cIP, self.cUserName, self.cPassword, pcProductID, iPort)
		time.sleep(1)
		dllLogOn.restype = ctypes.c_int
		print 'Logon id is: ', self.dllLogOnSet
		# print (dllLogOn.restype())
		dllGetLogonStatus = self.dll.NetClient_GetLogonStatus
		dllGetLogonStatus.argtypes = [c_int]
		dllGetSet = dllGetLogonStatus(self.dllLogOnSet)
		time.sleep(0.5)
		self.id = self.dllLogOnSet
		print 'Logon Status is: ', dllGetSet, u'(0和1都正常)'
		if dllGetSet == 0:
			return self.dllLogOnSet
		else:
			return None

	def LogOff(self, id):
		dllLogoff = self.dll.NetClient_Logoff
		dllLogoff.restype = ctypes.c_int
		dllLogoff_post = dllLogoff(id)
		print 'log off state is :', dllLogoff_post
		return dllLogoff_post






	# 交通图片流接收
	# @timeout(20)

	def ITSPicStream(self, ):
		now = datetime.datetime.now()
		localtime_z = now.strftime('%Y%m%d')
		localtime_min = now.strftime('%Y%m%d%H%M')
		self.video_path = 'E:\Pycharm\Learn_pachong\pc_qiubai\Practice\zhihui\Result\\201807051535_傍晚.xlsx'
		self.video_name = (os.path.splitext((os.path.split(self.video_path)[-1]))[0])
		self.path_dst = '..\\.\\Result\\' + localtime_min + '_' + self.ip + '.xlsx'     #ip在初始化sdk时指定;这个路径不能随便
		file_dir = '..\\.\\Result\\' + localtime_z + '\\' + self.ip +'\\'
		#pic_path = '.\\'+ localtime_z + '\\'+ self.ip +' \\'
		if not os.path.exists(file_dir):
			os.makedirs(file_dir)
		recv_id = [0]
		stop_flag = [0]
		recv_plate = []
		dict_car_type = {0: '未知车型', 1: '两厢轿车', 2: '轿车', 3: '轿跑', 4: '小型轿车', 5: '微型轿车', 6: 'MPV',
						 7: 'SUV', 8: '客车', 9: '中型客车', 10: '面包车', 11: '微型面包车', 12: '大货车',
						 13: '中型货车', 14: '车尾-油罐车', 15: '车尾-吊车',16: '车尾-渣土车', 17: '微型面包车', 18: '大货车',
						 }

		dict_car_color = {0:'白色', 1:'红色',2:'黄色', 3:'黄色',4:'蓝色', 5:'绿色',6:'绿色', 7:'紫色',8:'粉色',
						  9:'黑色',10:'红色', 11:'黄色',12:'黄色', 13:'灰色',14:'黄色',15:'蓝色', 16:'蓝色',
						  17:'绿色', 18:'绿色',19:'白色',20:'绿色', 21:'青色',22:'黄色', 23:'红色',24:'蓝色',
						  25: '蓝色', 26: '灰色', 27: '紫色', 28: '紫色', 29: '棕色', 30: '棕色', 31: '棕色', 99: '未知'}

		dict_bool = {0: '否', 1:'是'}
		dict_sex = {0: '未知', 1: '男', 2: '女'}
		XLS = its_xlsx.XLS_WRITE()
		XLS.open_xlsx(self.path_dst)

		def _xls_do(result_list):
			XLS.wirte_its_in(result_list)

		class RECT(Structure):
			_fields_ = [('left', c_int), ('top', c_int), ('right', c_int), ('bottom', c_int)]

		class RECT_S(Structure):
			_fields_ = [('left', c_short), ('top', c_short), ('right', c_short), ('bottom', c_short)]

		class STRCT_BRAND(Structure):
			_fields_ = [('uiBrandType', c_uint), ('uiSubBrand', c_uint), ('uiSubBrandYearStart', c_uint), ('uiSubBrandYearEnd', c_uint),
						('stRectLogo', RECT), ('uiConfid', c_uint)]


		class PicTime(Structure):  # 4*8 = 32 bytes
			_fields_ = [('uiyear', c_uint), ('uimonth', c_uint), ('uiday', c_uint), ('uiweek', c_uint),
						('uihour', c_uint), ('uiminute', c_uint), ('uisecond', c_uint), ('uimill', c_uint)]

		class PicData(Structure):  # 32 +4 + 8 =44
			_fields_ = [('pictime', PicTime), ('idatalen', c_int), ('pcPicData', (POINTER(c_char)))]

		#iFacePicLen_array = (c_int*3)()
		#cCaptureTimeEx2_array = ((c_char*5)*8)()
		#iCaptureLenEx2_array = (c_int*5)()
		#cSecurityCode_array = ((c_char*8)*36)()

		class ItsPicStream(Structure):
			_fields_ = [('istructlen', c_int), ('ichannelid', c_int), ('cplate', c_char * 32), ('iplatecolor', c_int),
						('iPlateType', c_int), ('icarcolor', c_int), ('tplaterange', RECT), ('icharnum', c_int),
						('icharconfid', c_int * 12), ('iplateconfid', c_int), ('irecordnum', c_int),
						('fspeed', c_float), ('idirection', c_int), ('ialarmtype', c_int), ('ccameraip', c_char * 16),
						('iredbegin', c_int), ('iredend', c_int), ('ipiccount', c_int), ('isize', c_int),
						('ptPicData', POINTER(PicData)),('ptPicData2', POINTER(PicData)),('ptPicData3', POINTER(PicData)),('ptPicData4', POINTER(PicData)),
						('ptPicData5', POINTER(PicData)),('ptPicData6', POINTER(PicData)),('ptPicData7', POINTER(PicData)),('ptPicData8', POINTER(PicData)),
						('iPlatCount', c_int), ('ptPlatData', POINTER(PicData)), ('iFaceCount', c_int), ('ptFaceData', POINTER(PicData)),
						('ptFaceData2', POINTER(PicData)),('ptFaceData3', POINTER(PicData)),
						('iPreset', c_int), ('iArea', c_int), ('cFileName', c_char * 32), ('lCarSerialNum', c_long),
						('iPictureNum', c_int), ('iPicType', c_int), ('iPlatePicLen',c_int), ('iFacePicNum', c_int),
						('cChannelName', c_char*64), ('cChannelDirection', c_char*64), ('cCrossingID', c_char*64),
						('cCrossingName', c_char*64), ('iCarRegionNum', c_int), ('tCarRegion', RECT), ('iTargetType', c_int),
						('iFacePicLen', c_int*3), ('iRecordAttr', c_int), ('iLinkageChannelNo', c_int), ('iLinkageNo', c_int),
						('cLinkageCameraIP', c_char*16), ('iVehicleBrand', c_int), ('tFaceRegion', RECT_S),('iAlgIllgalType', c_int),
						('iAlarmCode', c_int), ('sMergePicNum', c_short), ('sMergeType', c_short), ('sMergePercent',c_short),
						('sMergeOSDSize', c_short), ('sMergeOSDType', c_short), ('sSingleOSDSize', c_short), ('sSingleOSDType', c_short),
						('sOriginalImgWidth',c_short), ('sOriginalImgHeight',c_short), ('tVehicleRegion', RECT_S), ('tCopilotRegion', RECT_S),
						('cCaptureTimeEx2', c_char*40), ('iCaptureLenEx2', c_int*5), ('cUserDefChannelID', c_char*64),
						('sBodyOfCarLeight', c_short), ('cSecurityCode', c_char*288), ('iSpeedPercent',c_int), ('cLinkPanoramaCapUUID', c_char*128),
						('iRedBeginTimeMS', c_int),('iRedEndTimeMS', c_int), ('iIPDCapType', c_int), ('cAlarmCode', c_char*16),
						('iCarFeatures', c_int*2), ('stBrandInfo', STRCT_BRAND), ('iMainDriverSex', c_int), ('iCopilpt', c_int),
						('iNewTargetType', c_int), ('iRealImgWidth',c_int), ('iRealImgHeight',c_int)]
		PICTIME = PicTime()
		PICDATA = PicData()
		PICDATA.pictime = PICTIME
		SNAPPICSTREAM = ItsPicStream()
		rect = RECT()
		SNAPPICSTREAM.tplaterange = rect
		SNAPPICSTREAM.tCarRegion = rect
		rect_s =RECT_S()
		SNAPPICSTREAM.tFaceRegion = rect_s
		SNAPPICSTREAM.tVehicleRegion = rect_s
		SNAPPICSTREAM.tCopilotRegion = rect_s
		strct_brand = STRCT_BRAND()
		SNAPPICSTREAM.stBrandInfo = strct_brand

		iCarFeatures_ARR = (c_int*2)
		iCarFeatures_array = iCarFeatures_ARR()
		SNAPPICSTREAM.iCarFeatures = iCarFeatures_array




		SNAPPICSTREAM.isize = sizeof(PICDATA)

		SNAPPICSTREAM.ptPicData = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData2 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData3 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData4 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData5 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData6 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData7 = pointer(PICDATA)
		SNAPPICSTREAM.ptPicData8 = pointer(PICDATA)

		SNAPPICSTREAM.ptPlatData = pointer(PICDATA)
		SNAPPICSTREAM.ptFaceData = pointer(PICDATA)
		SNAPPICSTREAM.ptFaceData2 = pointer(PICDATA)
		SNAPPICSTREAM.ptFaceData3 = pointer(PICDATA)


		def picstream(uiRecvID, lCommand, pvBuf, iBufLen, pvUser):
			stop_flag[0] = 0

			road_id = pvBuf.contents.ichannelid      # 车道号
			recv_id[0] = uiRecvID                       # 图片流ID，用来结束接收用的

			#recv_plate[0] = car_plate


			pic_len = pvBuf.contents.ptPicData.contents.idatalen    # 图片长度
			pic_time = pvBuf.contents.ptPicData.contents.pictime    # 抓拍时间
			print '##################################'
			#print ('with picdata: %s' % pvBuf.contents.ptPicData.contents)
			print ('with iPlatCount: %s' %pvBuf.contents.iPlatCount)
			print ('with iFaceCount: %s' % pvBuf.contents.iFaceCount)
			print ('with iPreset: %s' % pvBuf.contents.iPreset)
			print ('with cFileName: %s' % pvBuf.contents.cFileName)
			print ('with cChannelDirection: %s' % pvBuf.contents.cChannelDirection.decode('gbk'))
			#print ('with stBrandInfo  : %s' % pvBuf.contents.stBrandInfo.uiBrandType)
			#print ('电话with iAlgIllgalType  : %s' % pvBuf.contents.iAlgIllgalType)
			#print bin(pvBuf.contents.iAlgIllgalType)
			#print len(bin(pvBuf.contents.iAlgIllgalType))
			print ('with iAlarmCode  : %s' % pvBuf.contents.iAlarmCode)
			print ('with iCarFeatures  : %s' % pvBuf.contents.iCarFeatures[0])
			print ('with iCarFeatures 1  : %s' % pvBuf.contents.iCarFeatures[1])
			#iCarFeatures
			print ('with iRealImgWidth : %s' % pvBuf.contents.iRealImgWidth)
			print ('with iRealImgHeight : %s' % pvBuf.contents.iRealImgHeight)

			car_plate = pvBuf.contents.cplate  # 车牌号
			car_color_key = pvBuf.contents.icarcolor  # 车身颜色编号
			car_color = dict_car_color[car_color_key]
			illegal_code = pvBuf.contents.iAlarmCode  # 违法代码
			if pvBuf.contents.stBrandInfo.uiBrandType != 0:
				car_brand = dict_brand[str(pvBuf.contents.stBrandInfo.uiBrandType)]  # 车辆品牌
				car_brand_pro = dict_brand_sub[str(pvBuf.contents.stBrandInfo.uiBrandType)][str(pvBuf.contents.stBrandInfo.uiSubBrand)]  # 车辆子品牌
			else:
				car_brand = '未知'
				car_brand_pro = '未知'
			car_type = dict_car_type[pvBuf.contents.iNewTargetType]  # 车辆类型
			# if pvBuf.contents.iAlgIllgalType != 0:
			# 	do_phone_key = int((bin(pvBuf.contents.iAlgIllgalType))[-2])  # 接打电话
			# 	do_phone = dict_bool[do_phone_key]
			# 	main_safe_belt_key = int((bin(pvBuf.contents.iAlgIllgalType))[-1])  # 主驾驶安全带
			# 	main_safe_belt = dict_bool[main_safe_belt_key]
			# else:
			# 	do_phone = '否'
			# 	main_safe_belt = '否'

			if pvBuf.contents.iCarFeatures[0] != 0:
				carfeat_bin = list((bin(pvBuf.contents.iCarFeatures[0])[2:]).zfill(12))        #对返回的数字取二进制，去掉开头的0b字样，变成纯二进制list
				main_safe_belt = dict_bool[int(carfeat_bin[-1])]
				do_phone = dict_bool[int(carfeat_bin[-2])]
				main_sun = dict_bool[int(carfeat_bin[-3])]                           ## 主驾驶遮阳板
				sub_sun = dict_bool[int(carfeat_bin[-4])]                             # 副驾驶遮阳板
				pendant = dict_bool[int(carfeat_bin[-7])]                             # 挂坠
				paper_box = dict_bool[int(carfeat_bin[-8])]                           # 纸巾盒
			else:
				main_safe_belt = '否'
				do_phone = '否'
				main_sun = '否'  ## 主驾驶遮阳板
				sub_sun = '否' # 副驾驶遮阳板
				pendant = '否'  # 挂坠
				paper_box = '否'  # 纸巾盒
			print 'sex with main: %s' %pvBuf.contents.iMainDriverSex
			print 'sex with sub : %s' %pvBuf.contents.iCopilpt
			main_sex = dict_sex[pvBuf.contents.iMainDriverSex]  # 主驾驶性别
			sub_sex = dict_sex[pvBuf.contents.iCopilpt]  # 副驾驶性别
			recv_plate.append(car_plate)
			if len(recv_plate) > 10:
				recv_plate.pop(0)


			# 从pcPicData这个字符串指针的地址，到字符串长度结束的字符，拿出来，就是图片数据
			sss = string_at(addressof(pvBuf.contents.ptPicData.contents.pcPicData.contents), pic_len)
			# 拼下图片名称的时间
			time_list = [str(pic_time.uiyear), str(pic_time.uimonth), str(pic_time.uiday), str(pic_time.uiweek),
						 str(pic_time.uihour), str(pic_time.uiminute), str(pic_time.uisecond), str(pic_time.uimill)]
			time_str = ''.join(time_list)
			time_str_mao = ':'.join(time_list)
			#文件名给保存图片使用，图片路径给excel写入图片路径使用。
			file_name = file_dir + '/' + time_str + '_' + str(road_id) + '_' + car_plate + '.jpg'
			pic_path = '.\\'+ localtime_z + '\\'+ self.ip +' \\' + time_str + '_' + str(road_id) + '_' + car_plate + '.jpg'
			with open(file_name, 'wb') as f:
				f.write(sss)

			result_list = []
			result_list.insert(0, str(pvBuf.contents.ccameraip))    #相机ip
			result_dict = {}
			result_dict['snap_time'] = time_str_mao
			result_dict['cplate'] = car_plate
			result_dict['road_num'] = road_id
			result_dict['alarm_code'] = illegal_code                  #违法代码
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

		while 1:
			time.sleep(1)
			stop_flag[0] = stop_flag[0] + 1
			print stop_flag
			self.re_plate = recv_plate         #需要加入qt线程的信号，来发出这个list，是一个最多10个元素的list
			if 20 > stop_flag[0] > 5:
				XLS.save_xlsx()
			elif stop_flag[0] >= 20:
				XLS.save_xlsx()
				back_stop = self.Stop_ITSPicStream(recv_id[0])
				self.re_plate[0] = back_stop    #停止时，将车牌list第一位置为0，再发一个结束信号，读第一个是0，则抓拍超时120s了。
				break
		return 1




	# 停止接收交通图片流
	def Stop_ITSPicStream(self, recvid):
		Stoprec = self.dll.NetClient_StopRecvNetPicStream
		Stoprec.argtypes = [c_uint]
		get_stoprec_post = Stoprec(recvid)
		return get_stoprec_post

	# 连接视频
	def GetVideoStart(self, id, chn, istream, iflag=0):
		self.dll_StartRecv = self.dll.NetClient_StartRecv_V4

		class CLIENTINFO(Structure):
			_fields_ = [('m_iServerID', c_int), ('m_iChannelNo', c_int), ('m_cNetFile', c_char * 255),
						('m_cRemoteIP', c_char * 16), ('m_iNetMode', c_int), ('m_iTimeout', c_int), ('m_iTTL', c_int),
						('m_iBufferCount', c_int), ('m_iDelayNum', c_int), ('m_iDelayTime', c_int),
						('m_iStreamNO', c_int), ('m_iFlag', c_int), ('m_iPosition', c_int), ('m_iSpeed', c_int)]

		cltInfo = CLIENTINFO()
		client_pointer = pointer(cltInfo)

		cltInfo.m_iServerID = int(id)
		cltInfo.m_iChannelNo = int(chn)
		# cltInfo.m_cNetFile = ''  #
		# cltInfo.m_cRemoteIP = ''  #
		cltInfo.m_iNetMode = 1
		# cltInfo.m_iTimeout = 0   #
		# cltInfo.m_iTTL = 0    #
		# cltInfo.m_iBufferCount = 0  #
		# cltInfo.m_iDelayNum = 0  #
		# cltInfo.m_iDelayTime = 0  #
		cltInfo.m_iStreamNO = int(istream)
		cltInfo.m_iFlag = int(iflag)  #
		# cltInfo.m_iPosition = 0  #
		# cltInfo.m_iSpeed = 0  #


		# client_pointer=byref(client)
		# client_pointer = pointer(client)
		print sizeof(CLIENTINFO)
		# print CLIENTINFO()
		# print client_pointer.contents
		# print isinstance(string_at(addressof(client_pointer)),'utf-8')

		# 定义C里面使用的回调函数
		# chuidiao=WINFUNCTYPE(ctypes.c_uint,ctypes.c_char_p,ctypes.c_int,ctypes.c_int)
		# c_huidiao =chuidiao(hanshu_c)
		# huidiao = 0

		# ctypes.c_void_p
		i_userdata = -1
		back = c_uint()
		back_id = ctypes.POINTER(ctypes.c_uint)(back)
		self.dll_StartRecv.argtypes = [POINTER(ctypes.c_uint), POINTER(CLIENTINFO), c_int, c_int]
		self.dll_StartRecv.restype = c_int
		self.dll_StartRecv_post = self.dll_StartRecv(back_id, client_pointer, 0, i_userdata)
		# self.dll_StartCap(id)
		print back.value
		print self.dll_StartRecv_post
		# time.sleep(1)
		# print addressof(self.dll_StartRecv_post)
		# a = GetLastError()
		return back.value, self.dll_StartRecv_post

	###连接视频参数未调通，只能做视频通断
	def GetVideo(self, recv, win):
		class RECT(Structure):
			_fields_ = [('left', c_int), ('top', c_int), ('right', c_int), ('bottom', c_int)]

		rect_new = RECT()
		rect_new.left = 0
		rect_new.top = 0
		rect_new.right = 0
		rect_new.bottom = 0


		#import iii_start
		win = win32gui.FindWindow("QWidget", "python")
		print 'get win is : %s' %win


		self.getvideo = self.dll.NetClient_StartPlay
		# self.getvideo.argtypes = [c_uint,c_int,RECT,c_uint]
		#print 'recv is: %s' % recv
		self.getvideo_post = self.getvideo(recv, win, rect_new, 0)
		b = GetLastError()
		print 'Error code is', b
		print self.getvideo_post




	def Capture(self):
		#NetClient_CaptureBmpPic

		pathnow = os.getcwd() + '\\dll\\'
		self.Setup(pathnow, '192.168.16.131', 'admin', '1111')
		self.id = self.Logon()
		time.sleep(3)

		time_now = datetime.datetime.now()
		localtime_z = time_now.strftime('%Y%m%d%H%M%S')
		file_name = 'D:/cc/' + localtime_z + '.bmp'
		link_id ,link_back= self.GetVideoStart(self.id, 0, 0)
		print 'link id is : %s' %link_id
		self.GetVideo(link_id,0)



		#i_userdata = -1
		back = c_uint(link_id)
		#back_id = (ctypes.c_uint)(back)

		file_name_char = c_char_p(file_name)
		#back_id = ctypes.POINTER(ctypes.c_uint)(back)


		self.dll_StartRecv.argtypes = [c_uint, c_char_p]

		self.capt = self.dll.NetClient_CaptureBmpPic
		capt_post = self.capt(back,file_name_char)
		print 'capt post is : %s' %capt_post






	# 全帧获取，用来获取帧的，暂时没用上，勿删
	def FullFrame(self):
		pathnow = os.getcwd() + '\\dll\\'
		x.Setup(pathnow, '192.168.16.131', 'admin', '1111')
		self.id = x.Logon()
		time.sleep(3)


		time_now = datetime.datetime.now()
		#localtime_z = time_now.strftime('%Y%m%d%H%M%S')
		startrecv_id, recv_status = self.GetVideoStart(self.id, 0, 0)

		def picstream(uiRecvID, ulStreamType, cData, iLen, iUser, iUserData):
			print 'iLen: %s' % iLen
			sss = string_at(addressof(cData), iLen)
			# print sss
			if int(iLen)>100000:
				localtime_z = time_now.strftime('%Y%m%d%H%M%S')
				file_name = 'D:/cc/' + localtime_z + '.jpg'
				with open(file_name, 'wb') as ff:
					ff.write(sss)
				time.sleep(3)
				return 1
			else:
				return 0

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

	# 交通突图片流执行
	def Do_ITS(self, host, user, user_passwd,):


		pathnow = os.getcwd() + '\\dll\\'
		self.Setup(pathnow, host, user, user_passwd)
		idid = self.Logon()
		time.sleep(3)
		# try:
		self.ITSPicStream()
		return [self.path_dst]


#x = Dll()
#x.Do_ITS('192.168.18.138', 'admin', 'Admin123') #, path_dst='F:\\result_z.xlsx'
#x.Capture()



