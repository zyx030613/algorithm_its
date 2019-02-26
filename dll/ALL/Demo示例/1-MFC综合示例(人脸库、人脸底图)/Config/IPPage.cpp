// Config\IPPage.cpp : implementation file
//

#include "stdafx.h"
#include "IPPage.h"


// CLS_IPPage dialog

IMPLEMENT_DYNAMIC(CLS_IPPage, CDialog)

CLS_IPPage::CLS_IPPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_IPPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_IPPage::~CLS_IPPage()
{
}

void CLS_IPPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_PROPERTY_DHCP, m_chkDhcp);
	DDX_Control(pDX, IDC_CHECK_PROPERTY_DHCP, m_chkDhcp);
	DDX_Control(pDX, IDC_EDIT_PROPERTY_IP, m_edtPtopertyIP);
	DDX_Control(pDX, IDC_EDIT_PROPERTY_SUBMASK, m_edtPropertyMask);
	DDX_Control(pDX, IDC_EDIT_PROPERTY_GATEWAY, m_edtPropertyGateway);
	DDX_Control(pDX, IDC_EDIT_PROPERTY_DNS, m_edtPropertyDNS);
	DDX_Control(pDX, IDC_EDIT_PROPERTY_BACKDNS, m_edtPropertyBackDNS);
	DDX_Control(pDX, IDC_EDIT_PROPERTY_GATEWAY, m_edtPropertyGateway);
	DDX_Control(pDX, IDC_CHECK_PROPERTY_UPNP, m_chkUpnp);
	DDX_Control(pDX, IDC_EDIT_FILTER_IP, m_edtFilterIP);
	DDX_Control(pDX, IDC_EDIT_FILTER_MASK, m_edtFilterMask);
	DDX_Control(pDX, IDC_EDIT_REGISTER_ID, m_edtRegID);
	DDX_Control(pDX, IDC_EDIT_REGISTER_PASSWORD, m_edtRegPassword);
	DDX_Control(pDX, IDC_EDIT_REGISTER_NVSNAME, m_edtRegNvsname);
	DDX_Control(pDX, IDC_EDIT_REGIP1, m_edtRegCenterIP1);
	DDX_Control(pDX, IDC_EDIT_REGIP2, m_edtRegCenterIP2);
	DDX_Control(pDX, IDC_EDIT_REGPORT1, m_edtRegPort1);
	DDX_Control(pDX, IDC_EDIT_REGPORT2, m_edtRegPort2);
	DDX_Control(pDX, IDC_EDIT_PPPOE_ACCOUNT, m_edtPppoeAccount);
	DDX_Control(pDX, IDC_EDIT_PPPOE_PASSWORD, m_edtPppoePassword);
	DDX_Control(pDX, IDC_CHECK_USINGPPPOE, m_chkUsingPppoe);
	DDX_Control(pDX, IDC_EDIT_WEBPORT, m_edtWebport);
	DDX_Control(pDX, IDC_EDIT_PROCXYIP, m_edtProcxyIP);
	DDX_Control(pDX, IDC_EDIT_PROCXYPORT, m_edtProcxyPort);
	DDX_Control(pDX, IDC_EDIT_PROCXYSTRING, m_edtProcxyString);
	DDX_Control(pDX, IDC_CHECK_SNMP, m_chkSNMP);
}


BEGIN_MESSAGE_MAP(CLS_IPPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTY_CHANGEIP, &CLS_IPPage::OnBnClickedButtonPropertyChangeip)
	ON_BN_CLICKED(IDC_CHECK_PROPERTY_DHCP, &CLS_IPPage::OnBnClickedCheckPropertyDhcp)
	ON_BN_CLICKED(IDC_CHECK_PROPERTY_UPNP, &CLS_IPPage::OnBnClickedCheckPropertyUpnp)
	ON_BN_CLICKED(IDC_BUTTON_FILTER_SET, &CLS_IPPage::OnBnClickedButtonFilterSet)
	ON_BN_CLICKED(IDC_BUTTON_REG_SET, &CLS_IPPage::OnBnClickedButtonRegSet)
	ON_BN_CLICKED(IDC_CHECK_USINGPPPOE, &CLS_IPPage::OnBnClickedCheckUsingpppoe)
	ON_BN_CLICKED(IDC_BUTTON_PPPOESET, &CLS_IPPage::OnBnClickedButtonPppoeset)
	ON_BN_CLICKED(IDC_BUTTON_WEBPORT, &CLS_IPPage::OnBnClickedButtonWebport)
	ON_BN_CLICKED(IDC_BUTTON_PROCXYSEND, &CLS_IPPage::OnBnClickedButtonProcxysend)
	ON_BN_CLICKED(IDC_CHECK_SNMP, &CLS_IPPage::OnBnClickedCheckSnmp)
END_MESSAGE_MAP()


// CLS_IPPage message handlers

BOOL CLS_IPPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtPtopertyIP.SetLimitText(15);
	m_edtPropertyMask.SetLimitText(15);
	m_edtPropertyGateway.SetLimitText(15);
	m_edtPropertyDNS.SetLimitText(15);
	m_edtPropertyBackDNS.SetLimitText(15);
	m_edtFilterIP.SetLimitText(15);
	m_edtFilterMask.SetLimitText(15);
	m_edtPppoeAccount.SetLimitText(63);
	m_edtPppoePassword.SetLimitText(63);

	m_edtRegID.SetLimitText(15);
	m_edtRegPassword.SetLimitText(15);
	m_edtRegNvsname.SetLimitText(31);
	m_edtRegCenterIP1.SetLimitText(31);
	m_edtRegCenterIP2.SetLimitText(31);
	m_edtRegPort1.SetLimitText(5);
	m_edtRegPort2.SetLimitText(5);
	m_edtWebport.SetLimitText(5);
	m_edtProcxyIP.SetLimitText(15);
	m_edtProcxyPort.SetLimitText(5);
	m_edtProcxyString.SetLimitText(1023);
	SetDlgItemInt(IDC_EDIT_PROCXYPORT,3001);
	UI_UpdateDialog();
	return TRUE;
}

void CLS_IPPage::OnChannelChanged(int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	GetPropertyEditInfo();
	GetUpnpInfo();
	GetDhcpInfo();
	GetFilterInfo();
	GetRegInfo();
	GetPppoeInfo();
	GetPortInfo();
	GetSnmpInfo();
}

void CLS_IPPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}
void CLS_IPPage::OnBnClickedButtonPropertyChangeip()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	CString strIP;
	m_edtPtopertyIP.GetWindowText(strIP);
	CString strGateWay;
	m_edtPropertyGateway.GetWindowText(strGateWay);
	if (BST_CHECKED == m_chkDhcp.GetCheck())
	{
		strIP = "0.0.0.0";
		strGateWay = "0.0.0.0";
	}
	else
	{
		if (IsValidIP(strIP) != 1 || IsValidIP(strGateWay) != 1)
		{
			AddLog(LOG_TYPE_MSG, "", "Change IP,IP or GateWay is invalid");
			return;
		}
	}
	CString strMask;
	m_edtPropertyMask.GetWindowText(strMask);
	CString strDNS;
	m_edtPropertyDNS.GetWindowText(strDNS);
	CString strBackDNS;
	m_edtPropertyBackDNS.GetWindowText(strBackDNS);
	if ((IsValidIP(strMask)==3) && IsValidIP(strDNS))
	{
		int iRet = NetClient_SetDHCPParam(m_iLogonID, m_chkDhcp.GetCheck());
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC, "%s", "NetClient_SetDHCPParam(%d,%d)", strIP, m_iLogonID,m_chkDhcp.GetCheck());
			int iTmp = NetClient_ChangeSvrIPEx(m_iLogonID, 
												(LPSTR)(LPCTSTR)strIP,
												(LPSTR)(LPCTSTR)strMask, 
												(LPSTR)(LPCTSTR)strGateWay,
												(LPSTR)(LPCTSTR)strDNS, 
												(LPSTR)(LPCTSTR)strBackDNS);

			if (0 == iTmp)
			{
				AddLog(LOG_TYPE_SUCC, "", "Change Server IP Success! LogonID(%d),Error(0x%08x)\n", m_iLogonID, ::GetLastError());
			}
			else
			{
				AddLog(LOG_TYPE_FAIL, "", "Change Server IP Failed! LogonID(%d),Error(0x%08x)\n", m_iLogonID, ::GetLastError());
			}
			
			int iCurTypeModel;
			NetClient_GetProductType(m_iLogonID, &iCurTypeModel);
			iCurTypeModel = iCurTypeModel & 0xFFFF;
			if (IsDVR(iCurTypeModel))
			{
				int iReboot = NetClient_Reboot(m_iLogonID);
				if (iReboot < 0)
				{
					AddLog(LOG_TYPE_FAIL, "", "[ChangeSvrIP] Reboot Failed,IP(%s),LogonID(%d), Error(0x%08x)", strIP, m_iLogonID, ::GetLastError());
				}
				else
				{
					AddLog(LOG_TYPE_SUCC, "", "[ChangeSvrIP] Reboot SUCCESS,IP(%s),LogonID(%d)", strIP, m_iLogonID);
				}
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "Set DHCP Param Failed! LogonID(%d),Error(0x%08x)\n", m_iLogonID, ::GetLastError());
		}
	}
	else
	{
		AddLog(LOG_TYPE_MSG, "", "Change IP, Mask or DNS is invalid");
	}
}

void CLS_IPPage::OnBnClickedCheckPropertyDhcp()
{
	int iCheckResult = m_chkDhcp.GetCheck();
	if (BST_CHECKED == iCheckResult)
	{
		m_edtPtopertyIP.EnableWindow(false);
		m_edtPropertyMask.EnableWindow(false);
		m_edtPropertyGateway.EnableWindow(false);
		m_edtPropertyDNS.EnableWindow(false);
		m_edtPropertyBackDNS.EnableWindow(false);
	}
	else if (BST_UNCHECKED == iCheckResult)
	{
		m_edtPtopertyIP.EnableWindow(true);
		m_edtPropertyMask.EnableWindow(true);
		m_edtPropertyGateway.EnableWindow(true);
		m_edtPropertyBackDNS.EnableWindow(true);
		m_edtPropertyDNS.EnableWindow(true);
	}
}

void CLS_IPPage::OnBnClickedCheckPropertyUpnp()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iEnable;
	if (BST_CHECKED == m_chkUpnp.GetCheck())
	{
		iEnable = 1;
	}
	else if (BST_UNCHECKED == m_chkUpnp.GetCheck())
	{
		iEnable = 0;
	}
	int iRet = NetClient_SetUPNPEnable(m_iLogonID, iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetUPNPEnable(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetUPNPEnable(%d)", m_iLogonID);
	}
}


void CLS_IPPage::GetPropertyEditInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	char cMac[18] = {0};
	char cMask[16] = {0};
	char cGateway[16] = {0};
	char cDNS[16] = {0};
	char cBackDNS[16]={0};
	PDEVICE_INFO pDev = FindDevice(m_iLogonID);
	if (NULL == pDev)
	{
		return;
	}
	if(NetClient_GetIpPropertyEx(m_iLogonID, cMac, cMask, cGateway, cDNS, cBackDNS) == 0) //显示登录的nvs ip
	{
		m_edtPtopertyIP.SetWindowText(pDev->cIP);
		m_edtPropertyMask.SetWindowText(cMask);
		m_edtPropertyGateway.SetWindowText(cGateway);
		m_edtPropertyDNS.SetWindowText(cDNS);
		m_edtPropertyBackDNS.SetWindowText(cBackDNS);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetIpPropertyEx(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetIpPropertyEx(%d)", m_iLogonID);	
	}
}

void CLS_IPPage::GetUpnpInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iUpnpState;
	int iRet1 = NetClient_GetUPNPEnable(m_iLogonID, &iUpnpState);
	if (0 == iRet1)
	{
		int iCheck;
		if (0 == iUpnpState)
		{
			iCheck = BST_UNCHECKED;
		}
		else if (1 == iUpnpState)
		{
			iCheck = BST_CHECKED;
		}
		m_chkUpnp.SetCheck(iCheck);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetUPNPEnable(%d)", m_iLogonID);
	}
	else if(iRet1 < 0)
	{
		AddLog(LOG_TYPE_FAIL, "","NetClient_GetUPNPEnable(%d)", m_iLogonID);
	}
}
void CLS_IPPage::GetDhcpInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iDhcpState;
	int iRet2 = NetClient_GetDHCPParam(m_iLogonID, &iDhcpState);
	if (0 == iRet2)
	{
		int iCheck;
		if (0 == iDhcpState)
		{
			m_edtPtopertyIP.EnableWindow(true);
			m_edtPropertyMask.EnableWindow(true);
			m_edtPropertyGateway.EnableWindow(true);
			m_edtPropertyDNS.EnableWindow(true);
			m_edtPropertyBackDNS.EnableWindow(true);
			iCheck = BST_UNCHECKED;
		}
		else if (1 == iDhcpState)
		{
			m_edtPtopertyIP.EnableWindow(false);
			m_edtPropertyMask.EnableWindow(false);
			m_edtPropertyGateway.EnableWindow(false);
			m_edtPropertyDNS.EnableWindow(false);
			m_edtPropertyBackDNS.EnableWindow(false);
			iCheck = BST_CHECKED;
		}
		m_chkDhcp.SetCheck(iCheck);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDHCPParam(%d)", m_iLogonID);
	}
	else if (iRet2 < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDHCPParam(%d)", m_iLogonID);
	}
}

void CLS_IPPage::OnBnClickedButtonFilterSet()
{
	if (IDOK == MessageBox("请使用Ip扩展页面的ip过滤功能", "提示", MB_OK))
	{
		return;
	}
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	CString strIP;
	m_edtFilterIP.GetWindowText(strIP);
	CString strMask;
	m_edtFilterMask.GetWindowText(strMask);
	if (IsValidIP(strIP) != 1 || IsValidIP(strMask) != 3)
	{
		MessageBox("Change IP,IP or Mask is invalid", "", MB_OK|MB_TOPMOST);
		return;
	}
	int iRet = NetClient_SetIpFilter(m_iLogonID, (LPSTR)(LPCTSTR)strIP, (LPSTR)(LPCTSTR)strMask);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetIpFilter(%d)", m_iLogonID);
	}
	else 
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetIpFilter(%d)", m_iLogonID);
	}
}

void CLS_IPPage::GetFilterInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	char cFilterIP[16], cFilterMask[16];
	int iRet = NetClient_GetIpFilter(m_iLogonID, cFilterIP, cFilterMask);
	if (0 == iRet)
	{
		m_edtFilterIP.SetWindowText(cFilterIP);
		m_edtFilterMask.SetWindowText(cFilterMask);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetIpFilter(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetIpFilter(%d)", m_iLogonID);
	}
}

void CLS_IPPage::OnBnClickedButtonRegSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	CString strRegID, strRegPassWord, strRegHost, strRegDNS1, strRegDNS2, strRegPort1, strRegPort2;
	unsigned short ustRegPort1, ustRegPort2;

	m_edtRegID.GetWindowText(strRegID);
	m_edtRegPassword.GetWindowText(strRegPassWord);
	m_edtRegNvsname.GetWindowText(strRegHost);
	m_edtRegCenterIP1.GetWindowText(strRegDNS1);
	m_edtRegCenterIP2.GetWindowText(strRegDNS2);
	m_edtRegPort1.GetWindowText(strRegPort1);
	m_edtRegPort2.GetWindowText(strRegPort2);
	ustRegPort1 = atoi(strRegPort1);
	ustRegPort2 = atoi(strRegPort2);
	if (IsValidIP(strRegDNS1) != 1 || IsValidIP(strRegDNS2) != 1)
	{
		MessageBox("DNS is invalid", "", MB_OK|MB_TOPMOST);
		return;
	}

	if(strRegID == "" || strRegPassWord == "" || strRegHost == "" || (strRegDNS1 == "" && strRegDNS2 == ""))
	{
		return;
	}
	int iRet = 	NetClient_SetDomainParsePara(m_iLogonID, 60, 
											(LPSTR)(LPCTSTR)strRegID, 
											(LPSTR)(LPCTSTR)strRegPassWord, 
											(LPSTR)(LPCTSTR)strRegHost, 
											(LPSTR)(LPCTSTR)strRegDNS1, 
											(LPSTR)(LPCTSTR)strRegDNS2, ustRegPort1, ustRegPort2);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDomainParsePara(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDomainParsePara(%d)", m_iLogonID);
	}
}

void CLS_IPPage::GetRegInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	char cUserID[16]={0}, cPassword[16]={0}, cHost[32]={0}, cDomain1[32]={0}, cDomain2[32]={0};
	int iInterval;
	unsigned short ustPort1, ustPort2;
	int iRet = NetClient_GetDomainParsePara(m_iLogonID, &iInterval, cUserID, cPassword, cHost, cDomain1, cDomain2, &ustPort1, &ustPort2);
	if (0 == iRet)
	{
		m_edtRegID.SetWindowText((LPCTSTR)cUserID);
		m_edtRegPassword.SetWindowText((LPCTSTR)cPassword);
		m_edtRegNvsname.SetWindowText((LPCTSTR)cHost);
		m_edtRegCenterIP1.SetWindowText((LPCTSTR)cDomain1);
		m_edtRegCenterIP2.SetWindowText((LPCTSTR)cDomain2);
		SetDlgItemInt(IDC_EDIT_REGPORT1, (int)ustPort1);
		SetDlgItemInt(IDC_EDIT_REGPORT2, (int)ustPort2);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDomainParsePara(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDomainParsePara(%d)", m_iLogonID);
	}
}

void CLS_IPPage::OnBnClickedCheckUsingpppoe()
{
	int iCheckRst = m_chkUsingPppoe.GetCheck();
	if (BST_CHECKED == iCheckRst)
	{
		m_edtPppoeAccount.EnableWindow(true);
		m_edtPppoePassword.EnableWindow(true);
	}
	else if (BST_UNCHECKED == iCheckRst)
	{
		m_edtPppoeAccount.EnableWindow(false);
		m_edtPppoePassword.EnableWindow(false);
	}
}

void CLS_IPPage::OnBnClickedButtonPppoeset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	CString strAccount, strPassword;
	int iEnable = m_chkUsingPppoe.GetCheck();
	if (BST_CHECKED == iEnable)
	{
		m_edtPppoeAccount.GetWindowText(strAccount);
		m_edtPppoePassword.GetWindowText(strPassword);
	}
	int iRet = NetClient_SetPPPoEInfo(m_iLogonID, (LPSTR)(LPCTSTR)strAccount, (LPSTR)(LPCTSTR)strPassword, iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetPPPoEInfo(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetPPPoEInfo(%d)", m_iLogonID);
	}
}	

void CLS_IPPage::GetPppoeInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	char cAccount[64]={0},cPassword[64]={0};
	int iEnabled;
	int iRet =  NetClient_GetPPPoEInfo(m_iLogonID, cAccount, cPassword, &iEnabled);
	if (0 == iRet)
	{
		int iCheck;
		if (0 == iEnabled)
		{
			iCheck = BST_UNCHECKED;
			m_edtPppoeAccount.EnableWindow(false);
			m_edtPppoePassword.EnableWindow(false);
		}
		else if (1 == iEnabled)
		{
			iCheck = BST_CHECKED;
			m_edtPppoeAccount.EnableWindow(true);
			m_edtPppoePassword.EnableWindow(true);
		}
		m_chkUsingPppoe.SetCheck(iCheck);
		m_edtPppoeAccount.SetWindowText(cAccount);
		m_edtPppoePassword.SetWindowText(cPassword);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetPPPoEInfo(%d)", m_iLogonID);
	}
	else if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "","NetClient_GetPPPoEInfo(%d)", m_iLogonID);
	}
}
void CLS_IPPage::OnBnClickedButtonWebport()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iPort;
	iPort = GetDlgItemInt(IDC_EDIT_WEBPORT);
	if(iPort < 80 || iPort > 65535)
	{
		return;
	}
    int iRet = NetClient_SetHTTPPort(m_iLogonID, iPort);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetHTTPPort(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetHTTPPort(%d)", m_iLogonID);
	}
}

void CLS_IPPage::GetPortInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	WORD wdPort;
	int iRet = NetClient_GetHTTPPort(m_iLogonID, &wdPort);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_WEBPORT, (int)wdPort);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetHTTPPort(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetHTTPPort(%d)", m_iLogonID);
	}
}

void CLS_IPPage::OnBnClickedButtonProcxysend()
{
	CString strProcxyIP, strPorcxyPort, strPRocxyString;
	m_edtProcxyIP.GetWindowText(strProcxyIP);
	m_edtProcxyPort.GetWindowText(strPorcxyPort);
	m_edtProcxyString.GetWindowText(strPRocxyString);
	if (IsValidIP(strProcxyIP) != 1)
	{
		MessageBox("ProcxyIP is invalid", "", MB_OK|MB_TOPMOST);
		return;
	}
	int iRet = NetClient_SendStringToCenter((LPSTR)(LPCTSTR)strProcxyIP, atoi(strPorcxyPort),
											(LPSTR)(LPCTSTR)strPRocxyString, (int)strlen(strPRocxyString));
	
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SendStringToCenter(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SendStringToCenter(%d)", m_iLogonID);
	}
}

void CLS_IPPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_PROPERTY, IDS_CONFIG_IP_PROPERTY);
	SetDlgItemTextEx(IDC_STATIC_PROPERTY_IP, IDS_CONFIG_IP_PROPERTY_IP);
	SetDlgItemTextEx(IDC_STATIC_PROXY, IDS_CONFIG_IP_PROPERTY_SUBMASK);
	SetDlgItemTextEx(IDC_STATIC_PROPERTY_GATEWAY, IDS_CONFIG_IP_PROPERTY_GATEWAY);
	SetDlgItemTextEx(IDC_STATIC_PROPERTY_DNS, IDS_CONFIG_IP_PROPERTY_DNS);
	SetDlgItemTextEx(IDC_STATIC_PROPERTY_BACKDNS, IDS_CONFIG_IP_PROPERTY_BACKDNS);
	SetDlgItemTextEx(IDC_BUTTON_PROPERTY_CHANGEIP, IDS_CONFIG_IP_PROPERTY_CHANGEIP);
	SetDlgItemTextEx(IDC_STATIC_FILTER, IDS_CONFIG_IP_FILTER);
	SetDlgItemTextEx(IDC_STATIC_FILTER_IP, IDS_CONFIG_IP_FILTER_IP);
	SetDlgItemTextEx(IDC_STATIC_FILTER_MASK, IDS_CONFIG_IP_FILTER_MASK);
	SetDlgItemTextEx(IDC_BUTTON_FILTER_SET, IDS_CONFIG_IP_FILTER_SET);
	SetDlgItemTextEx(IDC_STATIC_REGISTER, IDS_CONFIG_IP_REGSTER);
	SetDlgItemTextEx(IDC_STATIC_REGISTER_ID, IDS_CONFIG_IP_REGSTER_ID);
	SetDlgItemTextEx(IDC_STATIC_REGISTER_PASSWORD, IDS_CONFIG_IP_REGISTER_PASSWORD);
	SetDlgItemTextEx(IDC_STATIC_REGISTER_NVSNAME, IDS_CONFIG_IP_REGISTER_NVSMAME);
	SetDlgItemTextEx(IDC_STATIC_REGIP1, IDS_CONFIG_IP_REGISTER_REGIP1);
	SetDlgItemTextEx(IDC_STATIC_REGPORT1, IDS_CONFIG_IP_REGISTER_REGPORT1);
	SetDlgItemTextEx(IDC_STATIC_REGIP2, IDS_CONFIG_IP_REGISTER_REGIP2);
	SetDlgItemTextEx(IDC_STATIC_REGPORT2, IDS_CONFIG_IP_REGISTER_REGPORT2);
	SetDlgItemTextEx(IDC_BUTTON_REG_SET, IDS_CONFIG_IP_REGISTER_SET);
	SetDlgItemTextEx(IDC_CHECK_USINGPPPOE, IDS_CONFIG_IP_PPPOE_USINGPPPOE);
	SetDlgItemTextEx(IDC_STATIC_PPPOE_ACCOUNT, IDS_CONFIG_IP_PPPOE_ACCOUNT);
	SetDlgItemTextEx(IDC_STATIC_PPPOE_PASSWORD, IDS_CONFIG_IP_PPPOE_PASSWORD);
	SetDlgItemTextEx(IDC_BUTTON_PPPOESET, IDS_CONFIG_IP_PPPOESET);
	SetDlgItemTextEx(IDC_STATIC_PORT, IDS_CONFIG_IP_PORT);
	SetDlgItemTextEx(IDC_STATIC_WEBPORT, IDS_CONFIG_IP_PORT_WEBPORT);
	SetDlgItemTextEx(IDC_BUTTON_WEBPORT, IDS_CONFIG_IP_PORT_SET);
	SetDlgItemTextEx(IDC_STATIC_PROCXY, IDS_CONFIG_IP_PROCXY);
	SetDlgItemTextEx(IDC_STATIC_PROXYIP, IDS_CONFIG_IP_PROCXYIP);
	SetDlgItemTextEx(IDC_STATIC_PROCXYPORT, IDS_CONFIG_IP_PROCXYPORT);
	SetDlgItemTextEx(IDC_STATIC_PROCXYSTRING, IDS_CONFIG_IP_PROCXYSTRING);
	SetDlgItemTextEx(IDC_BUTTON_PROCXYSEND, IDS_CONFIG_IP_PROCXYSEND);
}
void CLS_IPPage::OnBnClickedCheckSnmp()
{
	// TODO: Add your control notification handler code here
	int iEnableValue = (m_chkSNMP.GetCheck()==BST_CHECKED)?1:0;
	int iRet = NetClient_SetCommonEnable(m_iLogonID, CI_NET_SERVICE_SNMP, 0x7FFFFFFF, iEnableValue);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetCommonEnable(%d)", iEnableValue);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetCommonEnable(%d)", iEnableValue);
	}
}

void CLS_IPPage::GetSnmpInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iEnableSnmp = 0;
	int iRet = NetClient_GetCommonEnable(m_iLogonID, CI_NET_SERVICE_SNMP, 0x7FFFFFFF, &iEnableSnmp);
	if (0 == iRet)
	{
		m_chkSNMP.SetCheck(iEnableSnmp);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetCommonEnable(%d)", iEnableSnmp);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetCommonEnable(%d)", iEnableSnmp);
	}
}
