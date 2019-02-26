// LANIPV4Page.cpp : implementation file
//

#include "stdafx.h"
#include "LANIPV4Page.h"

// CLS_LANIPV4Page dialog

IMPLEMENT_DYNAMIC(CLS_LANIPV4Page, CDialog)

CLS_LANIPV4Page::CLS_LANIPV4Page(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_LANIPV4Page::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_LANIPV4Page::~CLS_LANIPV4Page()
{
}

void CLS_LANIPV4Page::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IPV4_LANNO, m_cboLanNo);
	DDX_Control(pDX, IDC_EDIT_IPV4_LANTYPE, m_edtLanType);
	DDX_Control(pDX, IDC_EDIT_IPV4_IP, m_edtIP);
	DDX_Control(pDX, IDC_EDIT_IPV4_MASK, m_edtMask);
	DDX_Control(pDX, IDC_EDIT_IPV4_GATEWAY, m_edtGateway);
	DDX_Control(pDX, IDC_EDIT_IPV4_DNS, m_edtDNS);
	DDX_Control(pDX, IDC_EDIT_IPV4_BACKDNS, m_edtBackDNS);
	DDX_Control(pDX, IDC_EDIT_RESERVED, m_edtReserved);
	DDX_Control(pDX, IDC_BUTTON_IPV4, m_btnIPV4);
}


BEGIN_MESSAGE_MAP(CLS_LANIPV4Page, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_IPV4, &CLS_LANIPV4Page::OnBnClickedButtonIpv4)
	ON_CBN_SELCHANGE(IDC_COMBO_IPV4_LANNO, &CLS_LANIPV4Page::OnCbnSelchangeComboIpv4Lanno)
	ON_BN_CLICKED(IDC_CHECK_IPV4_DHCP, &CLS_LANIPV4Page::OnBnClickedCheckDhcp)
END_MESSAGE_MAP()


// CLS_LANIPV4Page message handlers

BOOL CLS_LANIPV4Page::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtLanType.EnableWindow(FALSE);
	m_edtIP.SetLimitText(LENGTH_IPV4);
	m_edtMask.SetLimitText(LENGTH_IPV4);
	m_edtGateway.SetLimitText(LENGTH_IPV4);
	m_edtDNS.SetLimitText(LENGTH_IPV4);
	m_edtBackDNS.SetLimitText(LENGTH_IPV4);
	m_edtReserved.SetLimitText(64);
	m_edtReserved.EnableWindow(FALSE);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_LANIPV4Page::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateLanNum();
	UI_UpdateIPV4();
	UI_UpdateDHCP();
}

void CLS_LANIPV4Page::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_LANIPV4Page::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_IPV4_LANNO,IDS_CONFIG_LAN_LANNO);
	SetDlgItemTextEx(IDC_STATIC_IPV4_LANTYPE,IDS_CONFIG_LAN_LANTYPE);
	SetDlgItemTextEx(IDC_STATIC_IPV4_IP,IDS_CONFIG_LAN_IP);
	SetDlgItemTextEx(IDC_STATIC_IPV4_MASK,IDS_CONFIG_LAN_MASK);
	SetDlgItemTextEx(IDC_STATIC_IPV4_GATEWAY,IDS_CONFIG_LAN_GATEWAY);
	SetDlgItemTextEx(IDC_STATIC_IPV4_DNS,IDS_CONFIG_LAN_DNS);
	SetDlgItemTextEx(IDC_STATIC_IPV4_BACKDNS,IDS_CONFIG_LAN_BACKDNS);
	SetDlgItemTextEx(IDC_STATIC_RESERVED,IDS_CONFIG_LAN_RESERVED);
	SetDlgItemTextEx(IDC_BUTTON_IPV4,IDS_SET);
}

BOOL CLS_LANIPV4Page::UI_UpdateLanNum()
{
	if (m_iLogonID < 0)
		return FALSE;

	m_cboLanNo.ResetContent();
	int iLanNum = 0;
	int iRet = NetClient_GetLanParam(m_iLogonID, LAN_CMD_GET_LANNUM, &iLanNum);
	if (0 == iRet)
	{
		CString strLanNo;
		for (int i=0; i<iLanNum; i++)
		{
			strLanNo.Format("Lan%d",i+1);
			m_cboLanNo.AddString(strLanNo);
		}
		m_cboLanNo.SetCurSel(0);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetLanParam(IPV4 %d,%d)",m_iLogonID,iLanNum);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanParam(IPV4 %d,%d)",m_iLogonID,iLanNum);
	}
	return TRUE;
}

void CLS_LANIPV4Page::OnBnClickedButtonIpv4()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	LANPARAM_DHCP lDHCP = {sizeof(LANPARAM_DHCP)};
	lDHCP.iLanNo = m_cboLanNo.GetCurSel();
	lDHCP.iEnable = IsDlgButtonChecked(IDC_CHECK_IPV4_DHCP);	
	
	LANPARAM_IPV4 lIPV4 = {0};
	lIPV4.iSize = sizeof(LANPARAM_IPV4);
	lIPV4.iLanNo = lDHCP.iLanNo;
	lIPV4.iLanType = GetDlgItemInt(IDC_EDIT_IPV4_LANTYPE);
	GetDlgItemText(IDC_EDIT_IPV4_DNS, lIPV4.cDNS, LENGTH_IPV4);
	GetDlgItemText(IDC_EDIT_IPV4_BACKDNS, lIPV4.cBackDNS, LENGTH_IPV4);
	GetDlgItemText(IDC_EDIT_RESERVED, lIPV4.cReserved, sizeof(lIPV4.cReserved));
	if (lDHCP.iEnable)
	{
		strcpy_s(lIPV4.cIP,sizeof(lIPV4.cIP),"0.0.0.0");
		strcpy_s(lIPV4.cMask,sizeof(lIPV4.cMask),"255.255.255.0");
		strcpy_s(lIPV4.cGateway,sizeof(lIPV4.cGateway),"0.0.0.0");
	}
	else
	{
		GetDlgItemText(IDC_EDIT_IPV4_IP, lIPV4.cIP, LENGTH_IPV4);
		GetDlgItemText(IDC_EDIT_IPV4_MASK, lIPV4.cMask, LENGTH_IPV4);
		GetDlgItemText(IDC_EDIT_IPV4_GATEWAY, lIPV4.cGateway, LENGTH_IPV4);

		if (IsValidIP(lIPV4.cIP) != 1)
		{
			AddLog(LOG_TYPE_MSG, "", "Change IP is invalid");
			return;
		}
		if (IsValidIP(lIPV4.cMask) != 3)
		{
			AddLog(LOG_TYPE_MSG, "", "Change Mask is invalid");
			return;
		}
		if (IsValidIP(lIPV4.cGateway) != 1)
		{
			AddLog(LOG_TYPE_MSG, "", "Change Gateway is invalid");
			return;
		}
		if (IsValidIP(lIPV4.cDNS) == 0)
		{
			AddLog(LOG_TYPE_MSG, "", "Change DNS is invalid");
			return;
		}
		if (IsValidIP(lIPV4.cBackDNS) == 0)
		{
			AddLog(LOG_TYPE_MSG, "", "Change BackDNS is invalid");
			return;
		}
	}

	int iRet = NetClient_SetLanParam(m_iLogonID,LAN_CMD_SET_DHCP,&lDHCP);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetLanParam(DHCP %d)",m_iLogonID);
		iRet = NetClient_SetLanParam(m_iLogonID, LAN_CMD_SET_IPV4, &lIPV4);
		if (0 == iRet)
		{			
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetLanParam(IPV4 %d)",m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetLanParam(IPV4 %d)",m_iLogonID);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetLanParam(DHCP %d)",m_iLogonID);
		return;
	}

	iRet = MessageBox(GetTextEx(IDS_CONFIG_LAN_MESSAGETEXT), GetTextEx(IDS_CONFIG_PROMPT),MB_OKCANCEL);
	if (IDOK == iRet)
	{
		iRet = NetClient_Reboot(m_iLogonID);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_Reboot(%d)",m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_Reboot(%d)",m_iLogonID);
		}
	}
}

BOOL CLS_LANIPV4Page::UI_UpdateIPV4()
{
	if (m_iLogonID < 0)
		return FALSE;

	LANPARAM_IPV4 lIPV4 = {0};
	lIPV4.iSize = sizeof(LANPARAM_IPV4);
	lIPV4.iLanNo = m_cboLanNo.GetCurSel();
	int iRet = NetClient_GetLanParam(m_iLogonID, LAN_CMD_GET_IPV4, &lIPV4);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_IPV4_LANTYPE,lIPV4.iLanType);
		SetDlgItemText(IDC_EDIT_IPV4_IP,lIPV4.cIP);
		SetDlgItemText(IDC_EDIT_IPV4_MASK,lIPV4.cMask);
		SetDlgItemText(IDC_EDIT_IPV4_GATEWAY,lIPV4.cGateway);
		SetDlgItemText(IDC_EDIT_IPV4_DNS,lIPV4.cDNS);
		SetDlgItemText(IDC_EDIT_IPV4_BACKDNS,lIPV4.cBackDNS);
		SetDlgItemText(IDC_EDIT_RESERVED,lIPV4.cReserved);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetLanParam(IPV4 %d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanParam(IPV4 %d)",m_iLogonID);
	}
	return TRUE;
}

void CLS_LANIPV4Page::OnCbnSelchangeComboIpv4Lanno()
{
	UI_UpdateIPV4();
	UI_UpdateDHCP();
}

BOOL CLS_LANIPV4Page::UI_UpdateDHCP()
{
	if (m_iLogonID < 0)
		return FALSE;

	LANPARAM_DHCP lDHCP = {0};
	lDHCP.iSize = sizeof(LANPARAM_DHCP);
	lDHCP.iLanNo = m_cboLanNo.GetCurSel();
	int iRet = NetClient_GetLanParam(m_iLogonID,LAN_CMD_GET_DHCP,&lDHCP);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetLanParam(DHCP %d,%d)",m_iLogonID,lDHCP.iLanNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanParam(DHCP %d,%d)",m_iLogonID,lDHCP.iLanNo);
	}
	CheckDlgButton(IDC_CHECK_IPV4_DHCP,lDHCP.iEnable);
	DHCPEnable(lDHCP.iEnable);
	return TRUE;
}

void CLS_LANIPV4Page::DHCPEnable(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_IPV4_IP)->EnableWindow(!bEnable);
	GetDlgItem(IDC_EDIT_IPV4_MASK)->EnableWindow(!bEnable);
	GetDlgItem(IDC_EDIT_IPV4_GATEWAY)->EnableWindow(!bEnable);
	GetDlgItem(IDC_EDIT_IPV4_DNS)->EnableWindow(!bEnable);
	GetDlgItem(IDC_EDIT_IPV4_BACKDNS)->EnableWindow(!bEnable);
}

void CLS_LANIPV4Page::OnBnClickedCheckDhcp()
{
	DHCPEnable(IsDlgButtonChecked(IDC_CHECK_IPV4_DHCP));
}
