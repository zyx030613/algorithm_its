//FTPPage.cpp : implementation file
//

#include "stdafx.h"
#include "FTPPage.h"

// CLS_FTPPage dialog

IMPLEMENT_DYNAMIC(CLS_FTPPage, CDialog)

CLS_FTPPage::CLS_FTPPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_FTPPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_FTPPage::~CLS_FTPPage()
{
}

void CLS_FTPPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FTP_SNAPSHOT_ENABLE, m_cboEnable);
	DDX_Control(pDX, IDC_EDIT_FTP_QVALUE, m_edtQValue);
	DDX_Control(pDX, IDC_EDIT_FTP_INTERVAL, m_edtInterval);
	DDX_Control(pDX, IDC_EDIT_FTP_PICSIZE, m_edtPictureSize);
	DDX_Control(pDX, IDC_BUTTON_FTP_SNAPSHOT, m_btnSnapShot);
	DDX_Control(pDX, IDC_CHECK_LINKSEND_ENABLE, m_chkLinkSendEnable);
	DDX_Control(pDX, IDC_CHECK_EMAIL, m_chkEmail);
	DDX_Control(pDX, IDC_CHECK_FTP, m_chkFtp);
	DDX_Control(pDX, IDC_CHECK_TIMESEND_ENABLE, m_chkTimeSendEnable);
	DDX_Control(pDX, IDC_COMBO_TIMESEND_FILETYPE, m_cboTimeSendFileType);
	DDX_Control(pDX, IDC_DATETIMEPICKER__TIMESEND_FILETYPE, m_dtcTimeSend);
	DDX_Control(pDX, IDC_BUTTON_TIMESEND, m_btnTimeSend);
	DDX_Control(pDX, IDC_EDIT_FTP_ADDR, m_edtAddr);
	DDX_Control(pDX, IDC_EDIT_FTP_PORT, m_edtPort);
	DDX_Control(pDX, IDC_EDIT_FTP_PATH, m_edtPath);
	DDX_Control(pDX, IDC_EDIT_FTP_USER, m_edtUser);
	DDX_Control(pDX, IDC_EDIT_FTP_PASSWORD, m_edtPassword);
	DDX_Control(pDX, IDC_EDIT_FTP_USAGE, m_edtUsage);
	DDX_Control(pDX, IDC_BUTTON_FTP_UPDATE, m_btnUpdate);
}


BEGIN_MESSAGE_MAP(CLS_FTPPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_FTP_SNAPSHOT, &CLS_FTPPage::OnBnClickedButtonFtpSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_LINKSEND, &CLS_FTPPage::OnBnClickedButtonLinksend)
	ON_BN_CLICKED(IDC_BUTTON_TIMESEND, &CLS_FTPPage::OnBnClickedButtonTimesend)
	ON_BN_CLICKED(IDC_BUTTON_FTP_UPDATE, &CLS_FTPPage::OnBnClickedButtonFtpUpdate)
END_MESSAGE_MAP()


// CLS_FTPPage message handlers

BOOL CLS_FTPPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtQValue.SetLimitText(5);
	m_edtInterval.SetLimitText(6);
	m_edtPictureSize.SetLimitText(6);

	m_cboTimeSendFileType.AddString("Both");
	m_cboTimeSendFileType.AddString("Video");
	m_cboTimeSendFileType.AddString("Picture");

	m_edtAddr.SetLimitText(63);
	m_edtPort.SetLimitText(5);
	m_edtPath.SetLimitText(63);
	m_edtUser.SetLimitText(63);
	m_edtPassword.SetLimitText(63);
	m_edtUsage.SetLimitText(5);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_FTPPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	
	UI_UpdateSnapShot();
	UI_UpdateLinkSend();
	UI_UpdateTimeSend();
	UI_UpdateFtpUpdate();
}

void CLS_FTPPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_FTPPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_SNAPSHOT,IDS_CONFIG_FTP_SNAPSHOT);
	SetDlgItemTextEx(IDC_STATIC_FTP_SNAPSHOT_ENABLE,IDS_CONFIG_FTP_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_FTP_QVALUE,IDS_CONFIG_FTP_QVALUE);
	SetDlgItemTextEx(IDC_STATIC_FTP_INTERVAL,IDS_FTP_TIMEVAL);
	SetDlgItemTextEx(IDC_STATIC_FTP_PICSIZE,IDS_CONFIG_FTP_PICTURESIZE);
	SetDlgItemTextEx(IDC_BUTTON_FTP_SNAPSHOT,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_LINKSEND,IDS_CONFIG_FTP_LINKSEND);
	SetDlgItemTextEx(IDC_CHECK_LINKSEND_ENABLE,IDS_CONFIG_FTP_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_LINKMETHOD,IDS_CONFIG_FTP_LINKMETHOD);
	SetDlgItemTextEx(IDC_BUTTON_LINKSEND,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_TIMESEND,IDS_CONFIG_FTP_TIMESEND);
	SetDlgItemTextEx(IDC_CHECK_TIMESEND_ENABLE,IDS_CONFIG_FTP_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_TIMESEND_FILETYPE,IDS_CONFIG_FTP_FILETYPE);
	SetDlgItemTextEx(IDC_BUTTON_TIMESEND,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_FTP_UPDATE,IDS_CONFIG_FTP_UPDATE);
	SetDlgItemTextEx(IDC_STATIC_FTP_ADDR,IDS_CONFIG_FTP_ADDR);
	SetDlgItemTextEx(IDC_STATIC_FTP_PORT,IDS_CONFIG_FTP_PORT);
	SetDlgItemTextEx(IDC_STATIC_FTP_PATH,IDS_CONFIG_FTP_PATH);
	SetDlgItemTextEx(IDC_STATIC_FTP_USER,IDS_CONFIG_FTP_USER);
	SetDlgItemTextEx(IDC_STATIC_FTP_PASSWORD,IDS_CONFIG_FTP_PASSWORD);
	SetDlgItemTextEx(IDC_STATIC_FTP_USAGE,IDS_CONFIG_FTP_USAGE);
	SetDlgItemTextEx(IDC_BUTTON_FTP_UPDATE,IDS_SET);

	InsertString(m_cboEnable,0,IDS_CONFIG_FTP_SNAPSHOT_DISABLE);
	InsertString(m_cboEnable,1,IDS_CONFIG_FTP_SNAPSHOT_ENABLE_TIME);
	InsertString(m_cboEnable,2,IDS_CONFIG_FTP_SNAPSHOT_LINKAGESEND);
	InsertString(m_cboEnable,3,IDS_CONFIG_FTP_SNAPSHOT_MUTI_LINKAGESEND);

}

void CLS_FTPPage::OnBnClickedButtonFtpSnapshot()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	FTP_SNAPSHOT ftpSnapshot = {0};
	ftpSnapshot.iChannel = m_iChannelNo;
	ftpSnapshot.iEnable = m_cboEnable.GetCurSel();
	ftpSnapshot.iQValue = GetDlgItemInt(IDC_EDIT_FTP_QVALUE);
	ftpSnapshot.iInterval = GetDlgItemInt(IDC_EDIT_FTP_INTERVAL);
	ftpSnapshot.iPictureSize = GetDlgItemInt(IDC_EDIT_FTP_PICSIZE);
	//if(ftpSnapshot.iInterval < 5)
	//{
	//	MessageBox(GetTextEx(IDS_CONFIG_FTP_MESSAGEINTERVAL), GetTextEx(IDS_CONFIG_PROMPT), MB_OK + MB_TOPMOST);
	//	return;
	//}
	int iRet = NetClient_SetFTPUploadConfig(m_iLogonID, FTP_CMD_SET_SNAPSHOT, &ftpSnapshot, sizeof(ftpSnapshot));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpSnapshot));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpSnapshot));
	}
}

BOOL CLS_FTPPage::UI_UpdateSnapShot()
{
	if (m_iLogonID < 0)
		return FALSE;

    FTP_SNAPSHOT ftpSnapshot = {0};
	ftpSnapshot.iChannel = m_iChannelNo;
	int iRet = NetClient_GetFTPUploadConfig(m_iLogonID, FTP_CMD_GET_SNAPSHOT, &ftpSnapshot, sizeof(ftpSnapshot));
	if (0 == iRet)
	{
		m_cboEnable.SetCurSel(ftpSnapshot.iEnable);
		SetDlgItemInt(IDC_EDIT_FTP_QVALUE, ftpSnapshot.iQValue);
		SetDlgItemInt(IDC_EDIT_FTP_INTERVAL, ftpSnapshot.iInterval);
		SetDlgItemInt(IDC_EDIT_FTP_PICSIZE, ftpSnapshot.iPictureSize);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpSnapshot));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpSnapshot));
	}
	return TRUE;
}

void CLS_FTPPage::OnBnClickedButtonLinksend()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	FTP_LINKSEND ftpLinkSend = {0};
	ftpLinkSend.iChannel = m_iChannelNo;
	if (BST_CHECKED == m_chkLinkSendEnable.GetCheck())
	{
		ftpLinkSend.iEnable = 1;
	}
	else
	{
		ftpLinkSend.iEnable = 0;
	}
	if (BST_CHECKED == m_chkFtp.GetCheck() && BST_UNCHECKED == m_chkEmail.GetCheck())
	{
		ftpLinkSend.iMethod = 0x1;	
	}
	else if (BST_UNCHECKED == m_chkFtp.GetCheck() && BST_CHECKED == m_chkEmail.GetCheck())
	{
		ftpLinkSend.iMethod = 0x2;
	}
	else if (BST_CHECKED == m_chkFtp.GetCheck() && BST_CHECKED == m_chkEmail.GetCheck())
	{
		ftpLinkSend.iMethod = 0x3;
	}
	int iRet = NetClient_SetFTPUploadConfig(m_iLogonID, FTP_CMD_SET_LINKSEND, &ftpLinkSend, sizeof(ftpLinkSend));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpLinkSend));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpLinkSend));
	}
}

BOOL CLS_FTPPage::UI_UpdateLinkSend()
{
	if (m_iLogonID < 0)
		return FALSE;

	FTP_LINKSEND ftpLinkSend = {0};
	ftpLinkSend.iChannel = m_iChannelNo;
	m_chkLinkSendEnable.SetCheck(BST_UNCHECKED);
	m_chkFtp.SetCheck(BST_UNCHECKED);
	m_chkEmail.SetCheck(BST_UNCHECKED);
	int iRet = NetClient_GetFTPUploadConfig(m_iLogonID, FTP_CMD_GET_LINKSEND, &ftpLinkSend, sizeof(ftpLinkSend));
	if (0 == iRet)
	{
		if (1 == ftpLinkSend.iEnable)
		{
			m_chkLinkSendEnable.SetCheck(BST_CHECKED);
		}
		if (0x1 == (ftpLinkSend.iMethod & 0x1))
		{
			m_chkFtp.SetCheck(BST_CHECKED);
		}
		if (0x2 == (ftpLinkSend.iMethod & 0x2))
		{
			m_chkEmail.SetCheck(BST_CHECKED);
		}
		if (0x3 == (ftpLinkSend.iMethod & 0x3))
		{
			m_chkFtp.SetCheck(BST_CHECKED);
			m_chkEmail.SetCheck(BST_CHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpLinkSend));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpLinkSend));
	}
	return TRUE;
}

void CLS_FTPPage::OnBnClickedButtonTimesend()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	FTP_TIMEDSEND ftpTimedSend = {0};
	ftpTimedSend.iChannel = m_iChannelNo;
	if (BST_CHECKED == m_chkTimeSendEnable.GetCheck())
	{
		ftpTimedSend.iEnable = 1;
	}
	else
	{
		ftpTimedSend.iEnable = 0;
	}
	ftpTimedSend.iFileType = m_cboTimeSendFileType.GetCurSel();
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	m_dtcTimeSend.GetTime(&sysTime);
	ftpTimedSend.iHour = sysTime.wHour;
	ftpTimedSend.iMinute = sysTime.wMinute;
	ftpTimedSend.iSecond = sysTime.wSecond;
	int iRet = NetClient_SetFTPUploadConfig(m_iLogonID, FTP_CMD_SET_TIMEDSEND, &ftpTimedSend, sizeof(ftpTimedSend));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpTimedSend));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpTimedSend));
	}
}

BOOL CLS_FTPPage::UI_UpdateTimeSend()
{
	if (m_iLogonID < 0)
		return FALSE;

    FTP_TIMEDSEND ftpTimedSend = {0};
 	ftpTimedSend.iChannel = m_iChannelNo;
 	m_chkTimeSendEnable.SetCheck(BST_UNCHECKED);
    int iRet = NetClient_GetFTPUploadConfig(m_iLogonID, FTP_CMD_GET_TIMEDSEND, &ftpTimedSend, sizeof(ftpTimedSend));
 	if (0 == iRet)
 	{
 		if (1 == ftpTimedSend.iEnable)
 		{
 			m_chkLinkSendEnable.SetCheck(BST_CHECKED);
 		}
		m_cboTimeSendFileType.SetCurSel(ftpTimedSend.iFileType);
 		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpTimedSend));
 	}
 	else
 	{
 		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpTimedSend));
 	}
	return TRUE;
}

void CLS_FTPPage::OnBnClickedButtonFtpUpdate()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	FTP_UPDATE ftpUpdate = {0};
	GetDlgItemText(IDC_EDIT_FTP_ADDR, ftpUpdate.cFtpAddr, 64);
	ftpUpdate.iPort = GetDlgItemInt(IDC_EDIT_FTP_PORT);
	GetDlgItemText(IDC_EDIT_FTP_PATH, ftpUpdate.cFileName, 64);
	GetDlgItemText(IDC_EDIT_FTP_USER, ftpUpdate.cUserName, 64);
	GetDlgItemText(IDC_EDIT_FTP_PASSWORD, ftpUpdate.cPassword, 64);
	ftpUpdate.iUsage = GetDlgItemInt(IDC_EDIT_FTP_USAGE);
	int iRet = NetClient_SetFTPUploadConfig(m_iLogonID, FTP_CMD_SET_UPDATE, &ftpUpdate, sizeof(ftpUpdate));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
}

BOOL CLS_FTPPage::UI_UpdateFtpUpdate()
{
	if (m_iLogonID < 0)
		return FALSE;

	FTP_UPDATE ftpUpdate = {0};
	int iRet = NetClient_GetFTPUploadConfig(m_iLogonID, FTP_CMD_GET_UPDATE, &ftpUpdate, sizeof(ftpUpdate));
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_FTP_ADDR, ftpUpdate.cFtpAddr);
		SetDlgItemInt(IDC_EDIT_FTP_PORT, ftpUpdate.iPort);
		SetDlgItemText(IDC_EDIT_FTP_PATH, ftpUpdate.cFileName);
		SetDlgItemText(IDC_EDIT_FTP_USER, ftpUpdate.cUserName);
		SetDlgItemText(IDC_EDIT_FTP_PASSWORD, ftpUpdate.cPassword);
		SetDlgItemInt(IDC_EDIT_FTP_USAGE, ftpUpdate.iUsage);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
	return TRUE;
}
