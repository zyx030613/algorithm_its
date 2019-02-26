
#include "stdafx.h"
#include "LogManager.h"
#include "NetClientTypes.h"
#include <share.h>


CLS_LogManager* CLS_LogManager::s_pInstance = NULL;
CLS_LogManager::CLS_LogManager()
{
	m_plvLog = NULL;
	m_pfLog = NULL;
	m_uCaps = LOG_CAP_ALL&~LOG_CAP_WRITE_FILE;
	memset(m_cFileName,0,sizeof(m_cFileName));
	strcpy_s(m_cFileName,sizeof(m_cFileName),"nvssdk.log");
}

CLS_LogManager::~CLS_LogManager()
{
	if (m_pfLog)
	{
		fclose(m_pfLog);
		m_pfLog = NULL;
	}

	m_plvLog = NULL;
}

CLS_LogManager* CLS_LogManager::Instance()
{
	if (NULL == s_pInstance)
	{
		s_pInstance = new CLS_LogManager();
	}
	return s_pInstance;
}

void CLS_LogManager::Destroy()
{
	if (s_pInstance)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

int CLS_LogManager::SetFileName( char* _pcFileName,int _iLen)
{
	if (NULL == _pcFileName || _iLen <= 0 || _iLen >= MAX_PATH)
	{
		return -1;
	}

	strcpy_s(m_cFileName,_iLen+1,_pcFileName);
	if (m_pfLog)
	{
		fclose(m_pfLog);
		m_pfLog = NULL;
	}
	return 0;
}

int CLS_LogManager::SetLogCaps( unsigned int _uRemove,unsigned int _uAdd)
{
	m_uCaps &= (~_uRemove);
	m_uCaps |= _uAdd;
	return 0;
}

void CLS_LogManager::AddLog( int _iLogType,const char* _pcHost, const char* _pcLogInfo ,int _iLastError)
{
	CString strLogType;
	CString strErrInfo;

	switch(_iLogType)
	{
	case LOG_TYPE_SUCC:
		if (0 == (m_uCaps & LOG_CAP_SUCC))
		{
			return;
		}
		strLogType.Format(_T("%s"),_T("SUCC"));
		break;
	case LOG_TYPE_FAIL:
		if (0 == (m_uCaps & LOG_CAP_FAIL))
		{
			return;
		}
		strLogType.Format(_T("%s"),_T("FAIL"));
		strErrInfo.Format("0x%08x",_iLastError);
		break;
	case LOG_TYPE_MSG:
		if (0 == (m_uCaps & LOG_CAP_MSG))
		{
			return;
		}
		strLogType.Format(_T("%s"),_T("MSG"));
		break;
	default:
		strLogType.Format(_T("%d"),_iLogType);
		break;
	}
	
	CTime  cTime = CTime::GetCurrentTime();
	CString strTime = cTime.Format("%Y-%m-%d %H:%M:%S");
	CString strDevInfo(_pcHost);
	CString strLogInfo(_pcLogInfo);
	CString strMsg;

	if (m_plvLog && (m_uCaps & LOG_CAP_ADD_LIST))
	{
		if (m_plvLog->GetItemCount() >= 5000 )
		{
			m_plvLog->DeleteAllItems();
		}	

		m_plvLog->InsertItem(0,strTime);
		m_plvLog->SetItemText(0,1,strLogType);
		m_plvLog->SetItemText(0,2,strLogInfo);
		m_plvLog->SetItemText(0,3,strDevInfo);
		m_plvLog->SetItemText(0,4,strErrInfo);
	}
	
	strMsg.Format(_T("%s  %s  %s   %s  %s\r\n"),strTime,strLogType,strDevInfo,strLogInfo,strErrInfo);
	if (m_uCaps & LOG_CAP_WRITE_FILE)
	{
		if (NULL == m_pfLog)
		{
			m_pfLog = _fsopen(m_cFileName, "w+b", _SH_DENYNO);
		}
		if (m_pfLog)
		{
			fwrite((LPCSTR)(LPCTSTR)strMsg, 1, strMsg.GetLength(), m_pfLog);
		}
	}
	if (m_uCaps & LOG_CAP_OUTPUT_STRING)
	{
		OutputDebugString(strMsg);
	}
}
