# coding=utf-8

# -*- coding: utf-8 -*-

import os,requests
#s = os.path.exists('\\192.168.18.136')


def change_road():
	"""
	根据发送过来的当前执行的目录名字，来确定要抓拍哪个车道，其他车道模拟抓拍都会置为false
	先get，然后把所有true替换成false，再正则找到文件夹对应的路径，true
	"""
	#cgi_do = cgi_order
	data1 = ''
	ip_add = 'http://' + '192.168.16.131' + '/CGI/ITS/SimTrigger/RoadWay/channel/1'
	head = {'Accept': 'application/xml, text/xml, */*; q=0.01',
				 'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
				 'Content-Type': 'application/xml;charset=utf-8', 'Accept-Encoding': 'gzip,deflate,sdch',
				 'Accept-Language': 'zh-CN,zh;q=0.8', 'X-Requested-With': 'XMLHttpRequest'}



	#self._cgi_make('/CGI/ITS/SimTrigger/RoadWay/channel/1')
	p_get = requests.get(ip_add, headers=head, auth=('admin', '1111'), data=data1,
						 timeout=1)
	#logger.debug('cgi send back code is : %s' % p_get.status_code)
	get_xml = p_get.text
	print repr(get_xml)


change_road()










'''
import os

video_path = 'E:\Pycharm\Learn_pachong\pc_qiubai\Practice\zhihui\Result\\201807051535_傍晚.xlsx'
#video_path = 'E:\Pycharm\Learn_pachong\pc_qiubai\Practice\zhihui\Result'
#video_path = 'E:\Pycharm\Learn_pachong\pc_qiubai\Practice\zhihui\Result\\20180710\\192.168.18.138'
#video_name = str(os.path.splitext(str(os.path.split(video_path)[-1]))[0])
#video_name = str(os.path.split(video_path)[-1])

if os.path.isdir(video_path):
	video_name = str(os.path.split(video_path)[-1])
else:
	video_name = str(os.path.splitext(str(os.path.split(video_path)[-1]))[0])
print video_name
'''


'''
import re, os


path_pic_now = 'D:\cc\dd_1'

if os.path.isdir(path_pic_now):
	video_name = os.path.split(path_pic_now)[-1]
else:
	pass#video_name = os.path.splitext(os.path.split(path_pic_now)[-1])[0]

num = int(video_name.split('_')[-1])
#print num22,type(num22)


ss = """
<RoadWay>
	<roadList>
		<roadPara>
			<roadNum>1</roadNum >
			<enable>true</enable>
		</roadPara>
		<roadPara>
			<roadNum>2</roadNum >
			<enable>false</enable>
		</roadPara>
		<roadPara>
			<roadNum>3</roadNum >
			<enable>true</enable>
		</roadPara>
	</roadList>
</RoadWay >
"""
#num = 2

ss = ss.replace('true','false')
nums = re.compile(r'<roadNum>'+str(num)+'</roadNum >.*?<enable>(.*?)</enable>', re.S)
mid_res = re.findall(nums, ss)
print mid_res
sss = nums.subn('<roadNum>'+str(num)+'</roadNum ><enable>true</enable>', ss)
print sss
#txt_all=ss.sub('<roadNum>'+str(num)+'</roadNum >.*?<enable>'+enab+'</enable>', '\g<enab>',ss)
#print txt_all
'''



	#print dirpath
	#print dirnames
	#print files

	#for file in files:
		#fname = os.path.join(dirpath, file)


#print listdir(path)
'''

	class KThread(threading.Thread):
		"""A subclass of threading.Thread, with a kill()
		method.
	
		Come from:
		Kill a thread in Python:
		http://mail.python.org/pipermail/python-list/2004-May/260937.html
		"""
	
		def __init__(self, *args, **kwargs):
			threading.Thread.__init__(self, *args, **kwargs)
			self.killed = False
	
		def start(self):
			"""Start the thread."""
			self.__run_backup = self.run
			self.run = self.__run  # Force the Thread to install our trace.
			threading.Thread.start(self)
	
		def __run(self):
			"""Hacked run function, which installs the
			trace."""
			sys.settrace(self.globaltrace)
			self.__run_backup()
			self.run = self.__run_backup
	
		def globaltrace(self, frame, why, arg):
			if why == 'call':
				return self.localtrace
			else:
				return None
	
		def localtrace(self, frame, why, arg):
			if self.killed:
				if why == 'line':
					raise SystemExit()
			return self.localtrace
	
		def kill(self):
			self.killed = True
	
	
	class Timeout(Exception):
		"""function run timeout"""
	
	
	def timeout(seconds):
		"""超时装饰器，指定超时时间
		若被装饰的方法在指定的时间内未返回，则抛出Timeout异常"""
	
		def timeout_decorator(func):
			"""真正的装饰器"""
	
			def _new_func(oldfunc, result, oldfunc_args, oldfunc_kwargs):
				result.append(oldfunc(*oldfunc_args, **oldfunc_kwargs))
	
			def _(*args, **kwargs):
				result = []
				new_kwargs = {  # create new args for _new_func, because we want to get the func return val to result list
					'oldfunc': func, 'result': result, 'oldfunc_args': args, 'oldfunc_kwargs': kwargs}
				thd = KThread(target=_new_func, args=(), kwargs=new_kwargs)
				thd.start()
				thd.join(seconds)
				alive = thd.isAlive()
				thd.kill()  # kill the child thread
				if alive:
					raise Timeout(u'function run too long, timeout %d seconds.' % seconds)
				else:
					return result[0]
	
			_.__name__ = func.__name__
			_.__doc__ = func.__doc__
			return _
	
		return timeout_decorator
'''
