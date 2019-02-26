// DDNSPage.cpp : implementation file
//

#include "stdafx.h"
#include "DDNSPage.h"


// CLS_DDNSPage dialog

IMPLEMENT_DYNAMIC(CLS_DDNSPage, CDialog)

CLS_DDNSPage::CLS_DDNSPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DDNSPage::IDD, pParent)
{

}

CLS_DDNSPage::~CLS_DDNSPage()
{
}

void CLS_DDNSPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_edtUserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edtPassword);
	DDX_Control(pDX, IDC_EDIT_NVSNAME, m_edtNvsName);
	DDX_Control(pDX, IDC_COMBO_DDNSSERVER, m_cboDDNSServer);
	DDX_Control(pDX, IDC_EDIT_DDNSPORT, m_edtDDNSPort);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_BUTTON_DDNS, m_btnDDNS);
}


BEGIN_MESSAGE_MAP(CLS_DDNSPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_DDNS, &CLS_DDNSPage::OnBnClickedButtonDdns)
END_MESSAGE_MAP()


// CLS_DDNSPage message handlers
BOOL CLS_DDNSPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtUserName.SetLimitText(32);
	m_edtPassword.SetLimitText(32);
	m_edtNvsName.SetLimitText(32);
	m_cboDDNSServer.AddString("www.3322.org");
	m_cboDDNSServer.AddString("www.ChangeIP.org");
	m_cboDDNSServer.AddString("www.freeDns.org");
	m_cboDDNSServer.AddString("dynupdate.no-ip.com");
	m_cboDDNSServer.AddString("members.dyndns.org");
	m_cboDDNSServer.SetCurSel(0);
	m_edtDDNSPort.SetLimitText(5);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_DDNSPage::OnChannelChanged(int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	
	UI_UpdateDDNS();
}

void CLS_DDNSPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DDNSPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_USERNAME, IDS_CONFIG_FTP_USER);
	SetDlgItemTextEx(IDC_STATIC_PASSWORD, IDS_CONFIG_FTP_PASSWORD);
	SetDlgItemTextEx(IDC_STATIC_NVSNAME, IDS_CONFIG_DDNS_NVSNAME);
	SetDlgItemTextEx(IDC_STATIC_DDNSSERVER, IDS_CONFIG_DDNS_DDNSSERVER);
	SetDlgItemTextEx(IDC_STATIC_DDNSPORT, IDS_CONFIG_DDNS_DDNSPORT);
	SetDlgItemTextEx(IDC_CHECK_ENABLE, IDS_CONFIG_FTP_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_BUTTON_DDNS, IDS_SET);
}

BOOL CLS_DDNSPage::UI_UpdateDDNS()
{
	if (m_iLogonID < 0)
		return FALSE;

	//»ñµÃDDNS
	char cDUserName[32] = {0};
	char cDPassword[32] = {0};
	char cDNvsName[32] = {0};
	char cDomain[32] = {0};
	int iDPort = -1;
	int iDEnable = 0;
	int iRet = NetClient_GetDDNSPara(m_iLogonID,cDUserName,cDPassword,cDNvsName,cDomain,&iDPort,&iDEnable);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_USERNAME, cDUserName);
		SetDlgItemText(IDC_EDIT_PASSWORD, cDPassword);
		SetDlgItemText(IDC_EDIT_NVSNAME, cDNvsName);
		SetDlgItemInt(IDC_EDIT_DDNSPORT, iDPort);
		m_cboDDNSServer.SelectString(-1, cDomain);
		m_chkEnable.SetCheck((iDEnable == 1)?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDDNSPara(%d,%s,%s,%s,%s,%d,%d)",m_iLogonID,cDUserName,cDPassword,cDNvsName,cDomain,iDPort,iDEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDDNSPara(%d,%s,%s,%s,%s,%d,%d)",m_iLogonID,cDUserName,cDPassword,cDNvsName,cDomain,iDPort,iDEnable);
	}
	return TRUE;
}
void CLS_DDNSPage::OnBnClickedButtonDdns()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	char cDUserName[32] = {0};
	char cDPassword[32] = {0};
	char cDNvsName[32] = {0};
	char cDomain[32] = {0};
	int iDPort = -1;
	int iDEnable = 0;
	GetDlgItemText(IDC_EDIT_USERNAME, cDUserName, 32);
	GetDlgItemText(IDC_EDIT_PASSWORD, cDPassword, 32);
	GetDlgItemText(IDC_EDIT_NVSNAME, cDNvsName, 32);
	GetDlgItemText(IDC_COMBO_DDNSSERVER, cDomain, 32);
	iDPort = GetDlgItemInt(IDC_EDIT_DDNSPORT);
	iDEnable = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	int iRet = NetClient_SetDDNSPara(m_iLogonID,cDUserName,cDPassword,cDNvsName,cDomain,iDPort,iDEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDDNSPara(%d,%s,%s,%s,%s,%d,%d)",m_iLogonID,cDUserName,cDPassword,cDNvsName,cDomain,iDPort,iDEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDDNSPara(%d,%s,%s,%s,%s,%d,%d)",m_iLogonID,cDUserName,cDPassword,cDNvsName,cDomain,iDPort,iDEnable);
	}
}
