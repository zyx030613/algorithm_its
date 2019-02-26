// Config/SOPage.cpp : implementation file
//

#include "stdafx.h"
#include "SOPage.h"

// CLS_SOPage dialog

IMPLEMENT_DYNAMIC(CLS_SOPage, CDialog)

CLS_SOPage::CLS_SOPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_SOPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_SOPage::~CLS_SOPage()
{
}

void CLS_SOPage::DoDataExchange(CDataExchange* pDX)
{
	 CLS_BasePage::DoDataExchange(pDX);
	 DDX_Control(pDX, IDC_COMBO_CONFIG_SO, m_cboPlatformSO);
}


BEGIN_MESSAGE_MAP(CLS_SOPage,  CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_SO_RUN, &CLS_SOPage::OnBnClickedButtonSoRun)
	ON_BN_CLICKED(IDC_BUTTON_SO_STOP, &CLS_SOPage::OnBnClickedButtonSoStop)
END_MESSAGE_MAP()

void CLS_SOPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	UI_UpdatePlatformApp();
}

void CLS_SOPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}
// CLS_SOPage message handlers

BOOL CLS_SOPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_SOPage::OnBnClickedButtonSoRun()
{
	// TODO: Add your control notification handler code here
	int iLogonID = m_iLogonID;
	if (iLogonID < 0)
		return;

	TPlatformApp pa = {0};
	CString cstrSO;
	m_cboPlatformSO.GetWindowText(cstrSO);
	strcpy_s(pa.cName[0], sizeof(pa.cName[0]), (LPCSTR)(LPCTSTR)cstrSO+3);
	if (strlen(pa.cName[0]) == 0)
		return;
	pa.iState[0] = 1;
	int iRet = NetClient_SetPlatformApp(iLogonID, PLATFORM_CMD_SET_RUN, &pa, sizeof(pa));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetPlatformApp[RUN](%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetPlatformApp[RUN](%d)",m_iLogonID);
		Sleep(100);
		UI_UpdatePlatformApp();
	}
}

void CLS_SOPage::OnBnClickedButtonSoStop()
{
	// TODO: Add your control notification handler code here
	int iLogonID = m_iLogonID;
	if (iLogonID < 0)
		return;

	TPlatformApp pa = {0};
	CString cstrSO;
	m_cboPlatformSO.GetWindowText(cstrSO);
	strcpy_s(pa.cName[0], sizeof(pa.cName[0]), (LPCSTR)(LPCTSTR)cstrSO+3);
	if (strlen(pa.cName[0]) == 0)
		return;
	int iRet = NetClient_SetPlatformApp(iLogonID, PLATFORM_CMD_SET_RUN, &pa, sizeof(pa));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetPlatformApp[STOP](%d)",m_iLogonID);
	}    
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetPlatformApp[STOP](%d)",m_iLogonID);
		Sleep(100);
		UI_UpdatePlatformApp();
	}
}

bool CLS_SOPage::UI_UpdatePlatformApp()
{
	int iLogonID = m_iLogonID;
	if (iLogonID < 0)
		return false;

	TPlatformApp pa = {0};
	int iRet = NetClient_GetPlatformApp(iLogonID, PLATFORM_CMD_GET_LIST, &pa, sizeof(pa));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[GetPlatformApp] failed(%d)",m_iLogonID);
		return false;
	}

	m_cboPlatformSO.ResetContent();
	char cName[256] = {0};
	for (int i = 0; i < MAX_PLATFORM_COUNT; ++i)
	{
		if (strlen(pa.cName[i]) == 0)
			continue;

		memset(cName, 0, sizeof(cName));
		sprintf_s(cName, sizeof(cName), "%d--%s", pa.iState[i], pa.cName[i]);
		m_cboPlatformSO.AddString(cName);
	}
	m_cboPlatformSO.SetCurSel(0);

	return true;
}

void CLS_SOPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_BUTTON_SO_RUN,IDS_CFG_SO_RUN);
	SetDlgItemTextEx(IDC_BUTTON_SO_STOP,IDS_CFG_SO_STOP);
	SetDlgItemTextEx(IDC_BTN_TEST,IDS_LOG_TEST);
}