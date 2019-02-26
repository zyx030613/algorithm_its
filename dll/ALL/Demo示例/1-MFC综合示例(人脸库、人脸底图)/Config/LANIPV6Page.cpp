// LANIPV6Page.cpp : implementation file
//

#include "stdafx.h"
#include "LANIPV6Page.h"


// CLS_LANIPV6Page dialog

IMPLEMENT_DYNAMIC(CLS_LANIPV6Page, CDialog)

CLS_LANIPV6Page::CLS_LANIPV6Page(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_LANIPV6Page::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_LANIPV6Page::~CLS_LANIPV6Page()
{
}

void CLS_LANIPV6Page::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IPV6_LANNO, m_cboLanNo);
	DDX_Control(pDX, IDC_EDIT_IPV6_IP, m_edtIP);
	DDX_Control(pDX, IDC_EDIT_IPV6_PREFIXLEN, m_edtPreFixLen);
	DDX_Control(pDX, IDC_EDIT_IPV6_GATEWAY, m_edtGateway);
	DDX_Control(pDX, IDC_EDIT_IPV6_DNS, m_edtDNS);
	DDX_Control(pDX, IDC_EDIT_IPV6_BACKDNS, m_edtBackDNS);
	DDX_Control(pDX, IDC_EDIT_RESERVED, m_edtReserved);
	DDX_Control(pDX, IDC_BUTTON_IPV6, m_btnIPV6);
}


BEGIN_MESSAGE_MAP(CLS_LANIPV6Page, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_IPV6, &CLS_LANIPV6Page::OnBnClickedButtonIpv6)
	ON_CBN_SELCHANGE(IDC_COMBO_IPV6_LANNO, &CLS_LANIPV6Page::OnCbnSelchangeComboIpv6Lanno)
END_MESSAGE_MAP()


// CLS_LANIPV6Page message handlers

BOOL CLS_LANIPV6Page::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtIP.SetLimitText(LENGTH_IPV6);
	m_edtGateway.SetLimitText(LENGTH_IPV6);
	m_edtDNS.SetLimitText(LENGTH_IPV6);
	m_edtBackDNS.SetLimitText(LENGTH_IPV6);
	m_edtReserved.SetLimitText(64);
	m_edtReserved.EnableWindow(FALSE);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_LANIPV6Page::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;

	UI_UpdateLanNum();
	UI_UpdateIPV6();

}

void CLS_LANIPV6Page::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_LANIPV6Page::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_IPV6_LANNO,IDS_CONFIG_LAN_LANNO);
	SetDlgItemTextEx(IDC_STATIC_IPV6_IP,IDS_CONFIG_LAN_IP);
	SetDlgItemTextEx(IDC_STATIC_IPV6_PREFIXLEN,IDS_CONFIG_LAN_PREFIXLEN);
	SetDlgItemTextEx(IDC_STATIC_IPV6_GATEWAY,IDS_CONFIG_LAN_GATEWAY);
	SetDlgItemTextEx(IDC_STATIC_IPV6_DNS,IDS_CONFIG_LAN_DNS);
	SetDlgItemTextEx(IDC_STATIC_IPV6_BACKDNS,IDS_CONFIG_LAN_BACKDNS);
	SetDlgItemTextEx(IDC_STATIC_RESERVED,IDS_CONFIG_LAN_RESERVED);
	SetDlgItemTextEx(IDC_BUTTON_IPV6,IDS_SET);
}

BOOL CLS_LANIPV6Page::UI_UpdateLanNum()
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
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetLanParam(IPV6 %d,%d)",m_iLogonID,iLanNum);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanParam(IPV6 %d,%d)",m_iLogonID,iLanNum);
	}
	return TRUE;
}

void CLS_LANIPV6Page::OnBnClickedButtonIpv6()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	LANPARAM_IPV6 lIPV6 = {0};
	lIPV6.iSize = sizeof(LANPARAM_IPV4);
	lIPV6.iLanNo = m_cboLanNo.GetCurSel();
	char cIP[LENGTH_IPV6] = {0};				
	char cGateway[LENGTH_IPV6] = {0}; 		
	char cDNS[LENGTH_IPV6] = {0};			
	char cBackDNS[LENGTH_IPV6] = {0};		
	char cReserved[LENGTH_IPV6] = {0};
	lIPV6.iPrefixLen = GetDlgItemInt(IDC_EDIT_IPV6_PREFIXLEN);
	GetDlgItemText(IDC_EDIT_IPV6_IP, cIP, LENGTH_IPV6);
	GetDlgItemText(IDC_EDIT_IPV6_GATEWAY, cGateway, LENGTH_IPV6);
	GetDlgItemText(IDC_EDIT_IPV6_DNS, cDNS, LENGTH_IPV6);
	GetDlgItemText(IDC_EDIT_IPV6_BACKDNS, cBackDNS, LENGTH_IPV6);
	if (IsValidIP(cIP) != 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Change IP is invalid");
		return;
	}
	if (IsValidIP(cGateway) != 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Change Gateway is invalid");
		return;
	}
	if (IsValidIP(cDNS) != 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Change DNS is invalid");
		return;
	}
	if (IsValidIP(cBackDNS) != 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Change BackDNS is invalid");
		return;
	}
	memcpy(lIPV6.cIP, cIP, sizeof(cIP));
	memcpy(lIPV6.cGateway, cGateway, sizeof(cGateway));
	memcpy(lIPV6.cDNS, cDNS, sizeof(cDNS));
	memcpy(lIPV6.cBackDNS, cBackDNS, sizeof(cBackDNS));
	int iRet = NetClient_SetLanParam(m_iLogonID, LAN_CMD_SET_IPV6, &lIPV6);
	if (0 == iRet)
	{
		iRet = MessageBox(GetTextEx(IDS_CONFIG_LAN_MESSAGETEXT), GetTextEx(IDS_CONFIG_PROMPT),MB_OKCANCEL);
		if (IDOK == iRet)
		{
			iRet = NetClient_Reboot(m_iLogonID);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetLanParam(IPV6 %d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetLanParam(IPV6 %d)",m_iLogonID);
	}
}

BOOL CLS_LANIPV6Page::UI_UpdateIPV6()
{
	if (m_iLogonID < 0)
		return FALSE;

	LANPARAM_IPV6 lIPV6 = {0};
	lIPV6.iSize = sizeof(LANPARAM_IPV6);
	lIPV6.iLanNo = m_cboLanNo.GetCurSel();
	int iRet = NetClient_GetLanParam(m_iLogonID, LAN_CMD_GET_IPV6, &lIPV6);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_IPV6_IP,lIPV6.cIP);
		SetDlgItemInt(IDC_EDIT_IPV6_PREFIXLEN,lIPV6.iPrefixLen);
		SetDlgItemText(IDC_EDIT_IPV6_GATEWAY,lIPV6.cGateway);
		SetDlgItemText(IDC_EDIT_IPV6_DNS,lIPV6.cDNS);
		SetDlgItemText(IDC_EDIT_IPV6_BACKDNS,lIPV6.cBackDNS);
		SetDlgItemText(IDC_EDIT_RESERVED,lIPV6.cReserved);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetLanParam(IPV6 %d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanParam(IPV6 %d)",m_iLogonID);
	}
	return TRUE;
}

void CLS_LANIPV6Page::OnCbnSelchangeComboIpv6Lanno()
{
	UI_UpdateIPV6();
}
