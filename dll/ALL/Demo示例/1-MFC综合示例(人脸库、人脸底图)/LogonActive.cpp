// LogonActive.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "LogonActive.h"


// CLS_LogonActive dialog

IMPLEMENT_DYNAMIC(CLS_LogonActive, CDialog)

CLS_LogonActive::CLS_LogonActive(PDEVICE_INFO _pDevice,CWnd* _pParent)
	: CDialog(CLS_LogonActive::IDD, _pParent)
{
	if (_pDevice)
	{
		m_iMode = 1;
		memcpy_s(&m_tDevice,sizeof(DEVICE_INFO),_pDevice,sizeof(DEVICE_INFO));
	}
	else
	{
		m_iMode = 0;
		memset(&m_tDevice,0,sizeof(m_tDevice));
		m_tDevice.iPort = 3000;
		strcpy_s(m_tDevice.cIP,sizeof(m_tDevice.cIP),"192.168.16.81");
		strcpy_s(m_tDevice.cUserName,sizeof(m_tDevice.cUserName),"Admin");
		strcpy_s(m_tDevice.cPassword,sizeof(m_tDevice.cPassword),"1111");
		strcpy_s(m_tDevice.cNvsName,sizeof(m_tDevice.cNvsName),"NVSS");
		strcpy_s(m_tDevice.cAccontName,sizeof(m_tDevice.cAccontName),"QQ");
		strcpy_s(m_tDevice.cAccontPasswd,sizeof(m_tDevice.cAccontPasswd),"QQQQ");
	}
}

CLS_LogonActive::~CLS_LogonActive()
{
}

void CLS_LogonActive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_LogonActive, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CLS_LogonActive::OnBnClickedBtnLogon)
END_MESSAGE_MAP()


// CLS_LogonActive message handlers

BOOL CLS_LogonActive::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemTextEx(IDC_STATIC_IP,IDS_LOGON_IP);
	SetDlgItemTextEx(IDC_STATIC_PROXY,IDS_LOGON_PROXY);
	SetDlgItemTextEx(IDC_STATIC_ID,IDS_LOGON_ID);
	SetDlgItemTextEx(IDC_STATIC_PORT,IDS_LOGON_PORT);
	SetDlgItemTextEx(IDC_STATIC_USERNAME,IDS_LOGON_USERNAME);
	SetDlgItemTextEx(IDC_STATIC_PASSWORD,IDS_LOGON_PASSWORD);

	SetDlgItemTextEx(IDC_STATIC_NVS_NAME,IDS_MNG_NVS_NAME);
	SetDlgItemTextEx(IDC_STATIC_DSM_ACCNAME,IDS_MNG_ACT_DSM_NAME);
	SetDlgItemTextEx(IDC_STATIC_DSM_ACCPWD,IDS_MNG_ACT_DSM_PWD);

	SetDlgItemTextEx(IDC_BTN_OK,IDS_OK);

	SetDlgItemText(IDC_EDIT_IP,m_tDevice.cIP);
	SetDlgItemText(IDC_EDIT_PROXY,m_tDevice.cProxy);
	SetDlgItemText(IDC_EDIT_ID,m_tDevice.cID);
	SetDlgItemInt(IDC_EDIT_PORT,m_tDevice.iPort);
	SetDlgItemText(IDC_EDIT_USERNAME,m_tDevice.cUserName);
	SetDlgItemText(IDC_EDIT_PASSWORD,m_tDevice.cPassword);
	SetDlgItemText(IDC_EDIT_NVS_NAME,m_tDevice.cNvsName);
	SetDlgItemText(IDC_EDIT_DSM_ACCNAME,m_tDevice.cAccontName);
	SetDlgItemText(IDC_EDIT_DSM_ACCPWD,m_tDevice.cAccontPasswd);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_IP);
	pEdit->SetLimitText(15);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PROXY);
	pEdit->SetLimitText(15);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ID);
	pEdit->SetLimitText(63);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PORT);
	pEdit->SetLimitText(5);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	pEdit->SetLimitText(15);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
	pEdit->SetLimitText(15);

	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NVS_NAME);
	pEdit->SetLimitText(15);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_DSM_ACCNAME);
	pEdit->SetLimitText(15);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_DSM_ACCPWD);
	pEdit->SetLimitText(15);

	if (0 == m_iMode)
	{
		SetWindowTextEx(IDS_LOGON_ADD_DEVICE);
	}
	else
	{
		SetWindowTextEx(IDS_LOGON_LOGON_DEVICE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_LogonActive::OnDestroy()
{
	CDialog::OnDestroy();

}

void CLS_LogonActive::OnBnClickedBtnLogon()
{
	GetDlgItemText(IDC_EDIT_IP,m_tDevice.cIP,sizeof(m_tDevice.cIP));
	GetDlgItemText(IDC_EDIT_PROXY,m_tDevice.cProxy,sizeof(m_tDevice.cProxy));
	GetDlgItemText(IDC_EDIT_ID,m_tDevice.cID,sizeof(m_tDevice.cID));
	m_tDevice.iPort = GetDlgItemInt(IDC_EDIT_PORT);
	GetDlgItemText(IDC_EDIT_USERNAME,m_tDevice.cUserName,sizeof(m_tDevice.cUserName));
	GetDlgItemText(IDC_EDIT_PASSWORD,m_tDevice.cPassword,sizeof(m_tDevice.cPassword));
	GetDlgItemText(IDC_EDIT_NVS_NAME,m_tDevice.cNvsName,sizeof(m_tDevice.cNvsName));
	GetDlgItemText(IDC_EDIT_DSM_ACCNAME,m_tDevice.cAccontName,sizeof(m_tDevice.cAccontName));
	GetDlgItemText(IDC_EDIT_DSM_ACCPWD,m_tDevice.cAccontPasswd,sizeof(m_tDevice.cAccontPasswd));
	if(strlen(m_tDevice.cID) <= 0)
	{
		AddLog(LOG_TYPE_MSG,"","factory id is empty!");
		return;
	}

	if(strlen(m_tDevice.cUserName) <= 0)
	{
		AddLog(LOG_TYPE_MSG,"","user name is empty!");
		return;
	}

	if(strlen(m_tDevice.cPassword) <= 0)
	{
		AddLog(LOG_TYPE_MSG,"","user password is empty!");
		return;
	}

	OnOK();
}
