// OSDPage.cpp : implementation file
//

#include "stdafx.h"
#include "LanguagePage.h"


// CLS_LanguagePage dialog

IMPLEMENT_DYNAMIC(CLS_LanguagePage, CDialog)

CLS_LanguagePage::CLS_LanguagePage(CWnd* pParent /*=NULL*/)
: CLS_BasePage(CLS_LanguagePage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_LanguagePage::~CLS_LanguagePage()
{
}

void CLS_LanguagePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CURLANGUAGE, m_cboCurLanguage);
	DDX_Control(pDX, IDC_BUTTON_CURLANGUAGE, m_btnCurLanguage);
	DDX_Control(pDX, IDC_COMBO_TIMEZONE, m_cboTimeZone);
	DDX_Control(pDX, IDC_BUTTON_TIMEZONE, m_btnTimeZone);
}


BEGIN_MESSAGE_MAP(CLS_LanguagePage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_CURLANGUAGE, &CLS_LanguagePage::OnBnClickedButtonCurlanguage)
	ON_BN_CLICKED(IDC_BUTTON_TIMEZONE, &CLS_LanguagePage::OnBnClickedButtonTimezone)
END_MESSAGE_MAP()


// CLS_LanguagePage message handlers

BOOL CLS_LanguagePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_cboTimeZone.AddString("GMT-12:00");
	m_cboTimeZone.AddString("GMT-11:00");
	m_cboTimeZone.AddString("GMT-10:00");
	m_cboTimeZone.AddString("GMT-09:00");
	m_cboTimeZone.AddString("GMT-08:00");
	m_cboTimeZone.AddString("GMT-07:00");
	m_cboTimeZone.AddString("GMT-06:00");
	m_cboTimeZone.AddString("GMT-05:00");
	m_cboTimeZone.AddString("GMT-04:00");
	m_cboTimeZone.AddString("GMT-03:00");
	m_cboTimeZone.AddString("GMT-02:00");
	m_cboTimeZone.AddString("GMT-01:00");
	m_cboTimeZone.AddString("GMT ");
	m_cboTimeZone.AddString("GMT+01:00");
	m_cboTimeZone.AddString("GMT+02:00");
	m_cboTimeZone.AddString("GMT+03:00");
	m_cboTimeZone.AddString("GMT+04:00");
	m_cboTimeZone.AddString("GMT+05:00");
	m_cboTimeZone.AddString("GMT+06:00");
	m_cboTimeZone.AddString("GMT+07:00");
	m_cboTimeZone.AddString("GMT+08:00");
	m_cboTimeZone.AddString("GMT+09:00");
	m_cboTimeZone.AddString("GMT+10:00");
	m_cboTimeZone.AddString("GMT+11:00");
	m_cboTimeZone.AddString("GMT+12:00");
	m_cboTimeZone.AddString("GMT+13:00");
	
	UI_UpdateDialog();
	
	m_cboCurLanguage.SetCurSel(0);
	return TRUE;
}

void CLS_LanguagePage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
// 	if (m_iLogonID == _iLogonID)
// 	{
// 		return;
// 	}
	m_iLogonID = _iLogonID;

	UI_UpdateLanguage();
	UI_UpdateTimeZone();
}

void CLS_LanguagePage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

BOOL CLS_LanguagePage::UI_UpdateLanguage()
{
	if (m_iLogonID < 0)
		return FALSE;

	m_cboCurLanguage.ResetContent();
	st_NVSLanguageList _pStrctLanguageList = {0};
	int iRet = NetClient_GetLanguageList(m_iLogonID, &_pStrctLanguageList);
	if (0 == iRet)
	{
		for (int i=0; i<_pStrctLanguageList.iCount; i++)
		{
			m_cboCurLanguage.AddString(_pStrctLanguageList.cLanguage[i]);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanguageList(%d)",m_iLogonID);
	}

	char cLanguage[LANGUAGE_NAME_LENGTH] = {0};
	iRet = NetClient_GetCurLanguage(m_iLogonID,cLanguage);
	if (0 == iRet)
	{
		m_cboCurLanguage.SelectString(-1,cLanguage);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCurLanguage(%d,%s)",m_iLogonID,cLanguage);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCurLanguage(%d,%s)",m_iLogonID,cLanguage);
	}
	
	return TRUE;
}

BOOL CLS_LanguagePage::UI_UpdateTimeZone()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iTimeZone;
	CString strTimeZone;
	int iRet = NetClient_GetTimeZone(m_iLogonID, &iTimeZone);
	if (0 == iRet)
	{
		if(iTimeZone >= -12 && iTimeZone <= 13)
		{
		m_cboTimeZone.GetLBText(iTimeZone+12, strTimeZone);
		m_cboTimeZone.SelectString(-1, (LPCTSTR)strTimeZone);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetTimeZone(%d,%d)",m_iLogonID,iTimeZone);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetTimeZone(%d,%d)",m_iLogonID,iTimeZone);
	}

	return TRUE;
}

void CLS_LanguagePage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_CURLANGUAGE, IDS_CONFIG_CURLANGUAGE);
	SetDlgItemTextEx(IDC_STATIC_TIMEZONE, IDS_CONFIG_TIMEZONE);
	SetDlgItemTextEx(IDC_BUTTON_CURLANGUAGE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_TIMEZONE, IDS_SET);
}

void CLS_LanguagePage::OnBnClickedButtonCurlanguage()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	CString strCurLanguage;
	m_cboCurLanguage.GetWindowText(strCurLanguage);
	if (strCurLanguage.IsEmpty())
	{
		return;
	}
	int iRet = NetClient_SetCurLanguage(m_iLogonID, (LPSTR)(LPCSTR)strCurLanguage);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCurLanguage(%d,%s)",m_iLogonID,(LPSTR)(LPCSTR)strCurLanguage);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCurLanguage(%d,%s)",m_iLogonID,(LPSTR)(LPCSTR)strCurLanguage);
	}
}

void CLS_LanguagePage::OnBnClickedButtonTimezone()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iTimeZone = m_cboTimeZone.GetCurSel() - 12;
	int iRet = NetClient_SetTimeZone(m_iLogonID, iTimeZone);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetTimeZone(%d,%d)",m_iLogonID,iTimeZone);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetTimeZone(%d,%d)",m_iLogonID,iTimeZone);
	}
}


