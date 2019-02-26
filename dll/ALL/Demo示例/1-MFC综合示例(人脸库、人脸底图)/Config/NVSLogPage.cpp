// NVSLogPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "NVSLogPage.h"


// CLS_NVSLogPage dialog

IMPLEMENT_DYNAMIC(CLS_NVSLogPage, CDialog)

CLS_NVSLogPage::CLS_NVSLogPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_NVSLogPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_NVSLogPage::~CLS_NVSLogPage()
{
}

void CLS_NVSLogPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CFG_LOGNVS_LOGLEVEL, m_edtLogLevel);
	DDX_Control(pDX, IDC_EDIT_CFG_LOGNVS_LOGFILESIZE, m_edtLogfileSize);
	DDX_Control(pDX, IDC_EDIT_LOG_DVR_LOGINFO, m_edtLogInfo);
}


BEGIN_MESSAGE_MAP(CLS_NVSLogPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOGNVS_LOGFILESET, &CLS_NVSLogPage::OnBnClickedButtonNVSLogSet)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOGNVS_REFRESH, &CLS_NVSLogPage::OnBnClickedButtonLogNVSRefresh)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOGNVS_CLEARLOGFILE, &CLS_NVSLogPage::OnBnClickedButtonLogNVSClearLogfile)
	ON_BN_CLICKED(IDC_BUTTON_CFG_NVS_CLEARCURRENTFILE, &CLS_NVSLogPage::OnBnClickedButtonCfgNvsClearcurrentfile)
END_MESSAGE_MAP()


void CLS_NVSLogPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		return;
	}
	UI_UpdateNVSLogList();
	UI_UpdateNVSLogInfo();
}

void CLS_NVSLogPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

// CLS_NVSLogPage message handlers

BOOL CLS_NVSLogPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtLogLevel.SetLimitText(15);
	m_edtLogfileSize.SetLimitText(15);
	SetDlgItemInt(IDC_EDIT_CFG_LOGNVS_LOGLEVEL, 10);
	SetDlgItemInt(IDC_EDIT_CFG_LOGNVS_LOGFILESIZE, 64);
	m_edtLogInfo.SetWindowText("No Logfiles!");///////
	UI_UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_NVSLogPage::OnBnClickedButtonNVSLogSet()
{
	// TODO: Add your control notification handler code here
	int iLevel = -1;
	int iSize = 0;
	iLevel = GetDlgItemInt(IDC_EDIT_CFG_LOGNVS_LOGLEVEL);
	iSize = GetDlgItemInt(IDC_EDIT_CFG_LOGNVS_LOGFILESIZE);
	if (iSize < 8 || iSize > 512)
	{
		AddLog(LOG_TYPE_FAIL,"","Filesize must between (8KB~512KB)!LogonID(%d)",m_iLogonID);
		return;
	}
	int iRet = NetClient_LogFileSetProperty(m_iLogonID, iLevel, iSize);
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","LogFileSetProperty Error!LogonID(%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","LogFileSetProperty Success!LogonID(%d)",m_iLogonID);
	}
}

void CLS_NVSLogPage::OnBnClickedButtonLogNVSRefresh()
{
	// TODO: Add your control notification handler code here
	m_edtLogInfo.SetWindowText("");
	int iRet = NetClient_LogFileDownload(m_iLogonID);
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","LogFileDownload Error!LogonID(%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","LogFileDownload Success!LogonID(%d)",m_iLogonID);
	}
}

void CLS_NVSLogPage::OnBnClickedButtonLogNVSClearLogfile()
{
	// TODO: Add your control notification handler code here
	int iRet = NetClient_LogFileClear(m_iLogonID);
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","LogFileClear Error!LogonID(%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","LogFileClear Success!LogonID(%d)",m_iLogonID);
	}
	m_edtLogInfo.SetWindowText("");
}

void CLS_NVSLogPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_CFG_LOGNVS_LOGLEVEL, IDS_CFG_LOG_NVS_LOGLEVEL );
	SetDlgItemTextEx(IDC_STATIC_CFG_LOGNVS_LOGFILESIZE, IDS_CFG_LOG_NVS_LOGFILESIZE);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOGNVS_LOGFILESET, IDS_CFG_LOG_NVS_SET);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOGNVS_REFRESH, IDS_CFG_LOG_NVS_REFRESH);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOGNVS_CLEARLOGFILE, IDS_CFG_LOG_NVS_CLEAR);
	SetDlgItemTextEx(IDC_BUTTON_CFG_NVS_CLEARCURRENTFILE, IDS_CFG_LOG_NVS_CURRENTLOG); 
}

void CLS_NVSLogPage::UI_UpdateNVSLogList()
{
	int iLen = 0;
	const int iLogFileSize = 1024*1024;
	static auto_ptr<char> pcBuf (new char [iLogFileSize]);
	memset(pcBuf.get(), 0, iLogFileSize);
	m_edtLogInfo.Clear();
	if(0 == NetClient_LogFileGetDetails(m_iLogonID, pcBuf.get(), &iLen))
	{
		if(iLen)
			m_edtLogInfo.SetWindowText(pcBuf.get());
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","LogFileGetDetails Error!(%d)",m_iLogonID);
	}
}

void CLS_NVSLogPage::UI_UpdateNVSLogInfo()
{
	int iLevel, iSize;
	if(0 == NetClient_LogFileGetProperty(m_iLogonID, &iLevel, &iSize))
	{
		SetDlgItemInt(IDC_EDIT_CFG_LOGNVS_LOGLEVEL, iLevel);
		SetDlgItemInt(IDC_EDIT_CFG_LOGNVS_LOGFILESIZE, iSize);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","LogFileGetProperty Error!(%d)",m_iLogonID);
	}
}

void CLS_NVSLogPage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser )
{
	int iType = LOWORD(_wParam);
	if (WCM_LOGFILE_FINISHED == iType)
	{
		UI_UpdateNVSLogList();
	}
}

void CLS_NVSLogPage::OnBnClickedButtonCfgNvsClearcurrentfile()
{
	// TODO: Add your control notification handler code here
	m_edtLogInfo.SetWindowText("");
}
