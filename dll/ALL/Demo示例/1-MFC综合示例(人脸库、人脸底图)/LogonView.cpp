// LogonView.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "LogonView.h"


// CLS_LogonView dialog

IMPLEMENT_DYNAMIC(CLS_LogonView, CDialog)

CLS_LogonView::CLS_LogonView(PDEVICE_INFO _pDevice,CWnd* _pParent)
	: CDialog(CLS_LogonView::IDD, _pParent)
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
//#ifdef _DEBUG
		//strcpy_s(m_tDevice.cIP,sizeof(m_tDevice.cIP),"10.30.21.180");
		strcpy_s(m_tDevice.cIP,sizeof(m_tDevice.cIP),"192.168.16.81");
		strcpy_s(m_tDevice.cUserName,sizeof(m_tDevice.cUserName),"Admin");
		strcpy_s(m_tDevice.cPassword,sizeof(m_tDevice.cPassword),"1111");
//#endif
	}
}

CLS_LogonView::~CLS_LogonView()
{
}

void CLS_LogonView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_LogonView, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_OK, &CLS_LogonView::OnBnClickedBtnLogon)
	ON_MESSAGE(DM_GETDEFID,&CLS_LogonView::OnGetDefID)
END_MESSAGE_MAP()


// CLS_LogonView message handlers

BOOL CLS_LogonView::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STATIC_IP,IDS_LOGON_IP);
	SetDlgItemTextEx(IDC_STATIC_PROXY,IDS_LOGON_PROXY);
	SetDlgItemTextEx(IDC_STATIC_ID,IDS_LOGON_ID);
	SetDlgItemTextEx(IDC_STATIC_PORT,IDS_LOGON_PORT);
	SetDlgItemTextEx(IDC_STATIC_USERNAME,IDS_LOGON_USERNAME);
	SetDlgItemTextEx(IDC_STATIC_PASSWORD,IDS_LOGON_PASSWORD);
	SetDlgItemTextEx(IDC_BTN_OK,IDS_OK);

	SetDlgItemText(IDC_EDIT_IP,m_tDevice.cIP);
	SetDlgItemText(IDC_EDIT_PROXY,m_tDevice.cProxy);
	SetDlgItemText(IDC_EDIT_ID,m_tDevice.cID);
	SetDlgItemInt(IDC_EDIT_PORT,m_tDevice.iPort);
	SetDlgItemText(IDC_EDIT_USERNAME,m_tDevice.cUserName);
	SetDlgItemText(IDC_EDIT_PASSWORD,m_tDevice.cPassword);

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

	if (0 == m_iMode)
	{
		SetWindowTextEx(IDS_LOGON_ADD_DEVICE);
	}
	else
	{
		SetWindowTextEx(IDS_LOGON_LOGON_DEVICE);
//  		GetDlgItem(IDC_EDIT_IP)->EnableWindow(FALSE);
//  		GetDlgItem(IDC_EDIT_PROXY)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE);
	}

	return TRUE;  
}

void CLS_LogonView::OnDestroy()
{
	CDialog::OnDestroy();

}

void CLS_LogonView::OnBnClickedBtnLogon()
{
	GetDlgItemText(IDC_EDIT_IP,m_tDevice.cIP,sizeof(m_tDevice.cIP));
	GetDlgItemText(IDC_EDIT_PROXY,m_tDevice.cProxy,sizeof(m_tDevice.cProxy));
	GetDlgItemText(IDC_EDIT_ID,m_tDevice.cID,sizeof(m_tDevice.cID));
	m_tDevice.iPort = GetDlgItemInt(IDC_EDIT_PORT);
	GetDlgItemText(IDC_EDIT_USERNAME,m_tDevice.cUserName,sizeof(m_tDevice.cUserName));
	GetDlgItemText(IDC_EDIT_PASSWORD,m_tDevice.cPassword,sizeof(m_tDevice.cPassword));
	if(strlen(m_tDevice.cIP) <= 0 && strlen(m_tDevice.cID) <= 0)
	{
		AddLog(LOG_TYPE_MSG,"","ip and id is empty");
		return;
	}
	if(strlen(m_tDevice.cIP) > 0 && 1 != IsValidIP(m_tDevice.cIP))
	{
		AddLog(LOG_TYPE_MSG,"","invalid ip(%s)",m_tDevice.cIP);
		return;
	}
	if(strlen(m_tDevice.cProxy) > 0 && 1 != IsValidIP(m_tDevice.cProxy))
	{
		AddLog(LOG_TYPE_MSG,"","invalid proxy(%s)",m_tDevice.cProxy);
		return;
	}
	if(strlen(m_tDevice.cUserName) <= 0)
	{
		AddLog(LOG_TYPE_MSG,"","user name is empty");
		return;
	}
	OnOK();
}

LRESULT CLS_LogonView::OnGetDefID( WPARAM _wParam,LPARAM _lParam )
{
	return (DC_HASDEFID << 16 | IDC_BTN_OK);
}