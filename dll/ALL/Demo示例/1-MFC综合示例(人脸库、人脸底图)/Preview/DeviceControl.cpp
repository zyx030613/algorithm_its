#include "stdafx.h"
#include "DeviceControl.h"
#include <cstring>

CLS_DeviceControl::CLS_DeviceControl()
{
	m_pfGetControlCode = NULL;
	m_hInst = NULL;
	memset(m_cDeviceType,0,sizeof(m_cDeviceType));
}
//-------------------------------------------------------------------------------

CLS_DeviceControl::~CLS_DeviceControl()
{
	if(m_hInst)
	{
		FreeLibrary(m_hInst);
		m_hInst = NULL;
	}
}
//-------------------------------------------------------------------------------

int CLS_DeviceControl::Initialize(char* _pcDevictType)//动态加载与设备类型对应的dll文件
{
	if (strlen(_pcDevictType) <= 0)
	{
		return -1;
	}

	if (0 == strcmp(_pcDevictType,m_cDeviceType))
	{
		return 1;
	}

	m_cDeviceType[0] = '\0';
	if (m_hInst)//如果正在使用m_hInst，将其释放
	{
		FreeLibrary(m_hInst);
		m_hInst = NULL;
	}

	CString strDllFileName;//得到与设备对应的dll文件名
	strDllFileName.Format(_T("DeviceDll\\%s.dll"),_pcDevictType);	
	m_hInst = LoadLibrary(strDllFileName);//重新加载dll动态库
	if (NULL == m_hInst)//如果加载失败退出
	{
		
		return -1;
	}
	
	m_pfGetControlCode = (pfGetControlCode)GetProcAddress(m_hInst,"GetControlCode");//得到GetControlCode函数
	if(NULL == m_pfGetControlCode)
	{
		return -1;
	}
	strcpy_s(m_cDeviceType,sizeof(m_cDeviceType),_pcDevictType);
	return 0;
}

//根据设备类型_DevType和动作码_iActionCode，修改控制参数_cParam
int CLS_DeviceControl::GetCtrlCode(char* _pcDevictType,int _iActionCode,CONTROL_PARAM* _cParam)
{
	int iRet = Initialize(_pcDevictType);	
	if (iRet < 0)
	{
		return iRet;
	}	
	iRet = m_pfGetControlCode(_iActionCode,_cParam);
	if ( iRet == 1)
	{
		return 0;
	}
	else
	{
		return -1;
	}	
}