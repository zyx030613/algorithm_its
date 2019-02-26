# -*- coding: utf-8 -*-

import logging
import time, os
os.path.abspath('.')
import xml.dom.minidom
from xml.etree import ElementTree as ET
#<?xml version="1.0" encoding="UTF-8"?>


class XML_GET():
	def __init__(self, parent=None):
		"""
		初始化
		"""
		self.times = 1
		self.flag_forcgi = 1
	def get_xx(self, ):
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
			</roadList>
		</RoadWay >
		"""
		#tree = ET.parse(xml_path)
		tree =  ET.fromstring(ss)
		text_num = tree.findall("roadList/roadPara/roadNum")
		text_enable = tree.findall("roadList/roadPara/enable")
		dict_num_enable = {}
		for i,j  in zip(text_num,text_enable):
			i.text = '3'
			print i
			print j.text
			#dict_num_enable[i.text] = j.text
		#print dict_num_enable
		print ss


		#root = tree.getroot()
		#makers = root.findall('RoadWay')
		#dict_makers = {}

		#dict_id_model = {}

		#maker_id = makers.get('id')



		'''
		#time_start = time.time()
		for maker in makers:
			dict_model = {}
			maker_id = maker.get('id')      #maker id
			print maker_id
			ss=maker.findall("model")



			maker_name = maker.get('name')
			dict_makers[maker_id] = maker_name
			dict_id_model[maker_id] = dict_model
			print dict_makers
			print dict_id_model
			time.sleep(10)
		print dict_makers                # 有key可以获取到value，即可返回一个车辆品牌
		print dict_id_model
		return [dict_makers, dict_id_model]
		'''
		#time_end = time.time()
		#print time_end-time_start

		#print makers.find("model").attrib.get("id")






		#makers = root.findall('maker')[1].attrib.get("name")
		#print makers.find("model").attrib.get("id")
		#print root.findall('./maker')[1].attrib.get("name")


		#f = open(xml_path, 'r').read()
		#root = ET.fromstring(f)
		#print root
		#root.iter('test')
		# 获取总suite数
		# value_test=i.attrib.get('name')
		#suite_zong_com = './suite/suite/suite'
		#suite_zong_nums = root.findall(suite_zong_com)


#xml_p = './resourse/mmyr.xml'
#xml_p = ss
x = XML_GET()
x.get_xx()
