# -*- coding: utf-8 -*-
import os
import datetime
import ConfigParser
import logging
logger = logging.getLogger('Devinfo')


class DevInfo_Get():
	def __init__(self):
		self.config_name = 'its_devinfo.ini'
		self.path_now = os.getcwd()
		if not '/' in self.config_name:
			self.path_txt = os.path.join(self.path_now,self.config_name)
		elif '/' in self.config_name:
			self.path_txt=self.config_name
		#修改所有时长为0

	def uptime_zero(self):
		cf = ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs_df = cf.sections()
		for s in secs_df:
			cf.set(s, 'uptime', '0')
		with open(self.path_txt, "w+") as f:
			cf.write(f)

	def trade_zero(self):
		cf = ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs_df = cf.sections()
		for s in secs_df:
			cf.set(s, 'trade', '[]')
		with open(self.path_txt, "w+") as f:
			cf.write(f)

	def read_file_one(self,devname):
		cf =ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs = cf.sections()
		out_list=[]
		if devname in secs:
			kvs = cf.items(devname)
			#devtype = cf.get('dev1','devtype')
			dict_yuan=dict(kvs)
			out_list.append(dict_yuan)
		return out_list

	def read_cfile(self):
		now = datetime.datetime.now()
		localtime_z = now.strftime('%Y%m%d%H%M%S')
		self.localtime = localtime_z
		cf =ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs = cf.sections()
		out_list = []
		for section in secs:
			kvs = cf.items(section)
			#devtype = cf.get('dev1','devtype')
			dict_yuan=dict(kvs)
			out_list.append(dict_yuan)
		return out_list

	def del_sec(self,sec):
		cf = ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs = cf.sections()
		if sec in secs:
			try:
				cf.remove_section(sec)
				with open(self.path_txt, "w+") as f:
					cf.write(f)
				return 0
			except:
				logger.exception('del sec ex:')
				#logger.warning('del section err with: %s' %eee)
				return 1
		else:
			return 1



	def write_uptime(self,dev_ip,uptime):
		cf = ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs = cf.sections()
		sec_name = ''
		for i in secs:
			devtype_get=''
			devtype_get = cf.get(i,'ip')
			if str(dev_ip) == str(devtype_get):
				sec_name=i
				break
			else:
				pass

		if sec_name in secs:
			uptime_get = cf.get(sec_name,'uptime')
		else:
			uptime_get=0
		logger.info( 'Old time is: %s' %uptime_get)
		logger.info( 'New time is: %s' %uptime)
		if float(uptime_get)<float(uptime):
			try:
				cf.set(sec_name, 'uptime', uptime)
				with open(self.path_txt, "w+") as f:
					cf.write(f)
				return 0
			except:
				logger.exception('write uptime ex:')
				return 1
		elif float(uptime_get)>=float(uptime):
			try:
				cf.set(sec_name, 'uptime', uptime)
				with open(self.path_txt, "w+") as f:
					cf.write(f)
			except:
				logger.exception('write uptime ex2:')
			finally:
				return 1

	def write_trade(self,dev_ip,trade):
		cf = ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs = cf.sections()
		sec_name = ''
		for i in secs:
			devtype_get=''
			devtype_get = cf.get(i,'ip')
			if str(dev_ip) == str(devtype_get):
				sec_name=i
				break
			else:
				pass
		if sec_name in secs:
			trade_get = cf.get(sec_name, 'trade')
		else:
			trade_get = 0
		logger.info('Old pids is: %s' %trade_get)
		logger.info('New pids is: %s' % trade)
		trade=str(trade)
		#logger.info('pids str is: %s' % trade)
		if trade_get == trade and trade_get!='[]' and trade != '[None]':
			return 0
		elif trade_get != trade and trade_get == '[]' and trade != '[]' and trade != '[None]':
			try:
				cf.set(sec_name, 'trade', trade)
				with open(self.path_txt, "w+") as f:
					cf.write(f)
			except:
				logger.exception('write trade ex:')
			finally:
				return 0
		elif trade_get != trade and trade_get != '[]' and trade != '[]' and trade != '[None]':
			try:
				cf.set(sec_name, 'trade', trade)
				with open(self.path_txt, "w+") as f:
					cf.write(f)
			except:
				logger.exception('write trade ex2:')
			finally:return 1
		elif trade == '[None]':
			return 3
		elif trade == '[]':
			try:
				cf.set(sec_name, 'trade', trade)
				with open(self.path_txt, "w+") as f:
					cf.write(f)
			except:
				logger.exception('write trade ex3:')
			finally:return 1
		else:
			return 2

	def write_cfile(self,sec_name,devtype_value,ip_value,passwd_value,port_value,teluser_value,telpasswd_value,
					signalckdir_value,signalkeyword_value,configckdir_value,configkeyword_value):

		cf =ConfigParser.ConfigParser()
		cf.read(self.path_txt)
		secs = cf.sections()
		if sec_name in secs:
			pass
		else:
			try:
				cf.add_section(sec_name)
			except Exception as eee:
				logger.error('add section err with: %s' %eee)
				return 1
		try:
			cf.set(sec_name,'devtype',devtype_value)
			cf.set(sec_name,'ip',ip_value)
			cf.set(sec_name, 'passwd', passwd_value)
			cf.set(sec_name, 'port', port_value)
			cf.set(sec_name, 'teluser', teluser_value)
			cf.set(sec_name, 'telpasswd', telpasswd_value)
			cf.set(sec_name, 'signalckdir', signalckdir_value)
			cf.set(sec_name, 'signalkeyword', signalkeyword_value)
			cf.set(sec_name, 'configckdir', configckdir_value)
			cf.set(sec_name, 'configkeyword', configkeyword_value)
			with open(self.path_txt,"w+") as f:
				cf.write(f)
			return 0
		except Exception as eee:
			logger.error('add item err with: %s' % eee)
			return 1


#x=DevInfo_Get()
#x.read_file_one('dev3')
#x.read_cfile()