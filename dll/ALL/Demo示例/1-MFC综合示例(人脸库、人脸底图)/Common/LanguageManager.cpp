#include "StdAfx.h"
#include "LanguageManager.h"

CLS_LanguageManager* CLS_LanguageManager::s_pInstance = NULL;
CLS_LanguageManager::CLS_LanguageManager(void)
{
	m_wLanguage = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
}

CLS_LanguageManager::~CLS_LanguageManager(void)
{

}

CLS_LanguageManager* CLS_LanguageManager::Instance()
{
	if (NULL == s_pInstance)
	{
		s_pInstance = new CLS_LanguageManager();
	}
	return s_pInstance;
}

void CLS_LanguageManager::Destroy()
{
	if (s_pInstance)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

void CLS_LanguageManager::SetLanguage( int _iLanguage )
{
	switch(_iLanguage)
	{
	case 0:
		{
			m_wLanguage = MAKELANGID(LANG_CHINESE_SIMPLIFIED,SUBLANG_CHINESE_SIMPLIFIED);
		}
		break;
	default:
		{
			m_wLanguage = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
		}
		break;
	}
}

CString CLS_LanguageManager::GetText( unsigned int _uIDResource )
{
	CString strText;
	strText.LoadString(NULL,_uIDResource,m_wLanguage);
	return strText;
}

BOOL CLS_LanguageManager::SetText( HWND _hDlg,int _iIDDlgItem,unsigned int _uIDResource )
{
	CString strText;
	BOOL bRet = strText.LoadString(NULL,_uIDResource,m_wLanguage);
	if (bRet)
	{
		bRet = ::SetDlgItemText(_hDlg,_iIDDlgItem,strText);
	}
	return bRet;
}

BOOL CLS_LanguageManager::SetText( CWnd* pWnd,unsigned int _uIDResource )
{
	CString strText;
	BOOL bRet = strText.LoadString(NULL,_uIDResource,m_wLanguage);
	if (bRet && pWnd)
	{
		pWnd->SetWindowText(strText);
	}
	return bRet;
}