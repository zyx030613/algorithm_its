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

int CLS_DeviceControl::Initialize(char* _pcDevictType)//��̬�������豸���Ͷ�Ӧ��dll�ļ�
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
	if (m_hInst)//�������ʹ��m_hInst�������ͷ�
	{
		FreeLibrary(m_hInst);
		m_hInst = NULL;
	}

	CString strDllFileName;//�õ����豸��Ӧ��dll�ļ���
	strDllFileName.Format(_T("DeviceDll\\%s.dll"),_pcDevictType);	
	m_hInst = LoadLibrary(strDllFileName);//���¼���dll��̬��
	if (NULL == m_hInst)//�������ʧ���˳�
	{
		
		return -1;
	}
	
	m_pfGetControlCode = (pfGetControlCode)GetProcAddress(m_hInst,"GetControlCode");//�õ�GetControlCode����
	if(NULL == m_pfGetControlCode)
	{
		return -1;
	}
	strcpy_s(m_cDeviceType,sizeof(m_cDeviceType),_pcDevictType);
	return 0;
}

//�����豸����_DevType�Ͷ�����_iActionCode���޸Ŀ��Ʋ���_cParam
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