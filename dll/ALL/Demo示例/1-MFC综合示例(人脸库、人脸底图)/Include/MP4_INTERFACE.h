#pragma once

#include "NetClientTypes.h"

typedef void       td_MP4FileHandle;

namespace MP4_INTERFACE
{
	extern	HINSTANCE hMP4;
	extern	HRESULT	LoadMp4Dll();

	/************************************************* 
	  函数名称: MP4_ConvertSdvToMp4
	  功能描述: 用于将SDV 文件转换成标准MP4 文件
	  输入参数: _pcSrcFilePath ，源SDV 文件路径
	  输入参数: _pcDstFilePath ，目标待生成的MP4 文件路径
	  输出参数:
	  返    回：0为成功  -1为失败
	*************************************************/
	typedef int (__cdecl * MP4_ConvertSdvToMp4)(const char* _pcSrcFilePath, char* _pcDstFilePath);
	extern MP4_ConvertSdvToMp4 TMP4_ConvertSdvToMp4;
}
