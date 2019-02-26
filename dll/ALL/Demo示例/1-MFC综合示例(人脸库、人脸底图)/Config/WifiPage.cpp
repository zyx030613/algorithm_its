// WifiPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "WifiPage.h"


// CWifiPage dialog

IMPLEMENT_DYNAMIC(CWifiPage, CDialog)

CWifiPage::CWifiPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CWifiPage::IDD, pParent)
{
	m_iWifiWorkMode = -1;
}

CWifiPage::~CWifiPage()
{
}

void CWifiPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WIFICARD, m_cboWifiCard);
	DDX_Control(pDX, IDC_COMBO_WIFISTATE, m_cboWifiState);
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_cboWifiWorkMode);
	DDX_Control(pDX, IDC_COMBO_ENCRYPTION, m_cboEncryption);
	DDX_Control(pDX, IDC_COMBO_KEYTYPE, m_cboKeyType);
	DDX_Control(pDX, IDC_COMBO_KEYNUM, m_cboKeyNum);
	DDX_Control(pDX, IDC_COMBO_PWDTYPE, m_cboPwdType);
	DDX_Control(pDX, IDC_LIST_WIFILIST, m_lstWifiList);
	DDX_Control(pDX, IDC_CHECK_DHCP, m_chkDhcp);
	DDX_Control(pDX, IDC_CHECK_APDHCP, m_chkApDhcp);
}


BEGIN_MESSAGE_MAP(CWifiPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CWifiPage::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_SETWIFI, &CWifiPage::OnBnClickedButtonSetwifi)
	ON_BN_CLICKED(IDC_BUTTON_WIFIMODE, &CWifiPage::OnBnClickedButtonWifimode)
	ON_BN_CLICKED(IDC_BUTTON_SETAPDHCP, &CWifiPage::OnBnClickedButtonSetapdhcp)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CWifiPage::OnHdnItemdblclickListWifilist)
	ON_BN_CLICKED(IDC_CHECK_DHCP, &CWifiPage::OnBnClickedCheckDhcp)
	ON_BN_CLICKED(IDC_CHECK_APDHCP, &CWifiPage::OnBnClickedCheckApdhcp)
END_MESSAGE_MAP()


// CWifiPage message handlers
void CWifiPage::UI_UpdateWifiCard(int _iCurSel)
{
	_iCurSel = (-1 == _iCurSel)?0:_iCurSel;
    m_cboWifiCard.ResetContent();
	m_cboWifiCard.AddString(GetTextEx(IDS_CONFIG_WIFI_NO));
	m_cboWifiCard.AddString(GetTextEx(IDS_CONFIG_WIFI_YES));
	m_cboWifiCard.SetCurSel(_iCurSel);
}

void CWifiPage::UI_UpdateState(int _iCurSel)
{
	_iCurSel = (-1 == _iCurSel)?0:_iCurSel;
	m_cboWifiState.ResetContent();
	m_cboWifiState.AddString(GetTextEx(IDS_CONFIG_WIFI_OFFLINE));
	m_cboWifiState.AddString(GetTextEx(IDS_CONFIG_WIFI_ONLINE));
	m_cboWifiState.SetCurSel(_iCurSel);
}

void CWifiPage::UI_UpdateWorkMode()
{
	m_cboWifiWorkMode.ResetContent();
	m_cboWifiWorkMode.AddString(GetTextEx(IDS_CONFIG_WIFI_OFFLINE));
	m_cboWifiWorkMode.AddString(GetTextEx(IDS_CONFIG_WIFT_WIFIMODE_STA));
	m_cboWifiWorkMode.AddString(GetTextEx(IDS_CONFIG_WIFT_WIFIMODE_AP));

	int iWifiWorkMode = -1;
	if(0 == NetClient_GetLanParam(m_iLogonID,LAN_CMD_GET_WIFIWORKMODE,&iWifiWorkMode))
	{
		m_cboWifiWorkMode.SetCurSel(iWifiWorkMode);
		m_iWifiWorkMode = iWifiWorkMode;
	}
	else
	{
		m_cboWifiWorkMode.SetCurSel(0);
	}
}

void CWifiPage::UI_UpdateEncryption(int _iCurSel)
{
	_iCurSel = (-1 == _iCurSel)?0:_iCurSel;
	m_cboEncryption.ResetContent();
	m_cboEncryption.AddString("none");
	m_cboEncryption.AddString("WEP");
	m_cboEncryption.AddString("WPA-PSK");
	m_cboEncryption.AddString("WPA2-PSK");
	m_cboEncryption.SetCurSel(_iCurSel);
}

void CWifiPage::UI_UpdateKeyType(int _iCurSel)
{
	_iCurSel = (-1 == _iCurSel)?0:_iCurSel;
	m_cboKeyType.ResetContent();
	m_cboKeyType.AddString("ascii");
	m_cboKeyType.AddString("hex");
	m_cboKeyType.SetCurSel(_iCurSel);
}

void CWifiPage::UI_UpdatePwdType(int _iCurSel)
{
	_iCurSel = (-1 == _iCurSel)?0:_iCurSel;
	m_cboPwdType.ResetContent();
	m_cboPwdType.AddString("disable");
	m_cboPwdType.AddString("64bit");
	m_cboPwdType.AddString("128bit");
	m_cboPwdType.SetCurSel(_iCurSel);
}

void CWifiPage::UI_UpdateKeyNum(int _iCurSel)
{
	_iCurSel = (-1 == _iCurSel)?0:_iCurSel;
	m_cboKeyNum.ResetContent();
	m_cboKeyNum.AddString("1 -- TKIP");
	m_cboKeyNum.AddString("2 -- AES");
	m_cboKeyNum.AddString("3");
	m_cboKeyNum.AddString("4");
	m_cboKeyNum.SetCurSel(_iCurSel);
}

void CWifiPage::UI_UpdateWifiList()
{
	m_lstWifiList.DeleteAllItems();
	int nColumnCount = m_lstWifiList.GetHeaderCtrl()->GetItemCount();
	for (int i=0; i < nColumnCount; i++)
	{
		m_lstWifiList.DeleteColumn(0);
	}

	m_lstWifiList.SetExtendedStyle(m_lstWifiList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	int iColumnIndex = 0;
	m_lstWifiList.InsertColumn( iColumnIndex++, GetTextEx(IDS_CONFIG_WIFI_ESSIDLIST), LVCFMT_LEFT, 150 );
	m_lstWifiList.InsertColumn( iColumnIndex++, GetTextEx(IDS_CONFIG_WIFI_ENCRYPTIONLIST), LVCFMT_LEFT, 90 );
}

void CWifiPage::UI_UpdateSurface()
{
	UI_UpdateWifiList();
	SetDlgItemTextEx(IDC_STATIC_WIFIINFO, IDS_CONFIG_WIFI_INFO);
	SetDlgItemTextEx(IDC_BUTTON_SEARCH, IDS_CONFIG_WIFI_SEARCH);
	SetDlgItemTextEx(IDC_STATIC_WIFICARD, IDS_CONFIG_WIFI_WIFICARD);
	SetDlgItemTextEx(IDC_STATIC_STATE, IDS_CONFIG_WIFI_STATE);
	SetDlgItemTextEx(IDC_STATIC_WORKMODE, IDS_CONFIG_WIFI_WORKMODE);
	SetDlgItemTextEx(IDC_BUTTON_WIFIMODE, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_RANGE, IDS_CONFIG_WIFI_DHCPRANGE);
	SetDlgItemTextEx(IDC_STATIC_TO, IDS_CONFIG_WIFI_TO);
	SetDlgItemTextEx(IDC_STATIC_RENTTIME, IDS_CONFIG_WIFI_RENTTIME);
	SetDlgItemTextEx(IDC_STATIC_TIME, IDS_CONFIG_WIFI_MINUTE);
	SetDlgItemTextEx(IDC_BUTTON_SETAPDHCP, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_IP,IDS_CONFIG_IP);
	SetDlgItemTextEx(IDC_STATIC_GATEWAY,IDS_CONFIG_LAN_GATEWAY);
	SetDlgItemTextEx(IDC_STATIC_MASK, IDS_CONFIG_LAN_MASK);
	SetDlgItemTextEx(IDC_STATIC_DNS, IDS_CONFIG_WIFI_DNS);
	SetDlgItemTextEx(IDC_STATIC_ESSID, IDS_CONFIG_WIFI_ESSID);
	SetDlgItemTextEx(IDC_STATIC_ENCRYPTION, IDS_CONFIG_WIFI_ENCRYPTION);
	SetDlgItemTextEx(IDC_STATIC_PASSWORD, IDS_CONFIG_WIFI_PASSWORD);
	SetDlgItemTextEx(IDC_STATIC_KEYTYPE, IDS_CONFIG_WIFI_KEYTYPE);
	SetDlgItemTextEx(IDC_STATIC_KEYNUM, IDS_CONFIG_WIFI_KEYNUM);
	SetDlgItemTextEx(IDC_STATIC_PWDTYPE, IDS_CONFIG_WIFI_PWDTYPE);
	SetDlgItemTextEx(IDC_BUTTON_SETWIFI, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_HINT, IDS_CONFIG_WIFI_REMARK1);

	SetDlgItemTextEx(IDC_CHECK_DHCP, IDS_CONFIG_WIFI_DHCP);
	SetDlgItemTextEx(IDC_CHECK_APDHCP, IDS_CONFIG_WIFI_APDHCP);
	
	UI_UpdateWifiCard(m_cboWifiCard.GetCurSel());
	UI_UpdateState(m_cboWifiState.GetCurSel());
	UI_UpdateWorkMode();
	UI_UpdateEncryption(m_cboEncryption.GetCurSel());
	UpdateDeviceInfo();
}

void CWifiPage::UpdateDeviceInfo()
{
	NVS_WIFI_PARAM wifiPara = {0};

	int iWifiWorkMode = -1;
	int iCmd = LAN_CMD_GET_WIFIPARA;
	WIFIPARAM_DHCP dhcp = {0};
	dhcp.iSize = sizeof(WIFIPARAM_DHCP);
	if(0 == NetClient_GetLanParam(m_iLogonID,LAN_CMD_GET_WIFIWORKMODE,&iWifiWorkMode))
	{
		iCmd = (iWifiWorkMode == 2)?LAN_CMD_GET_WIFIAPPARA:LAN_CMD_GET_WIFIPARA;
		if (iWifiWorkMode == 2)
		{
			dhcp.iWifiDHCPMode = 1;
			if(0 == NetClient_GetLanParam(m_iLogonID,LAN_CMD_GET_WIFIDHCPMODE,&dhcp))
			{
				m_chkApDhcp.SetCheck(dhcp.iEnable);
			}
			m_chkDhcp.SetCheck(BST_UNCHECKED);
		}
		else if (iWifiWorkMode == 1)
		{
			dhcp.iWifiDHCPMode = 0;
			if(0 == NetClient_GetLanParam(m_iLogonID,LAN_CMD_GET_WIFIDHCPMODE,&dhcp))
			{
				m_chkDhcp.SetCheck(dhcp.iEnable);
			}
			m_chkApDhcp.SetCheck(BST_UNCHECKED);
		}
		else
		{
			m_chkApDhcp.SetCheck(BST_UNCHECKED);
			m_chkDhcp.SetCheck(BST_UNCHECKED);
		}
	}
	if(0 == NetClient_GetLanParam(m_iLogonID, iCmd, &wifiPara))
	{
		SetDlgItemText(IDC_EDIT_IP, wifiPara.cWifiSvrIP);
		SetDlgItemText(IDC_EDIT_MASK, wifiPara.cWifiMask);
        SetDlgItemText(IDC_EDIT_GATEWAY, wifiPara.cWifiGateway);
		SetDlgItemText(IDC_EDIT_DNS, wifiPara.cWifiDNS);
           
		SetDlgItemText(IDC_EDIT_ESSID, wifiPara.cESSID);
		SetDlgItemText(IDC_EDIT_PASSWORD, wifiPara.cWifiPassword); 
        m_cboKeyType.SelectString(-1, wifiPara.cWifiKeyType);
        m_cboEncryption.SelectString(-1, wifiPara.cEncryption);
        m_cboKeyNum.SelectString(-1, wifiPara.cWifiKeyNum);
		m_cboWifiCard.SetCurSel(wifiPara.iHaveCard);
        m_cboWifiState.SetCurSel(wifiPara.iCardOnline);

		//密码长度
		if (strcmp(wifiPara.cWifiKeyType, "hex") == 0 && strlen(wifiPara.cWifiPassword) == 10)
		{
			m_cboPwdType.SetCurSel(1);
		}
		else if(strcmp(wifiPara.cWifiKeyType, "hex") == 0 && strlen(wifiPara.cWifiPassword) == 26)
		{
			m_cboPwdType.SetCurSel(2);
		}
		else if(strcmp(wifiPara.cWifiKeyType, "ascii") == 0 && strlen(wifiPara.cWifiPassword) == 5)
		{
			m_cboPwdType.SetCurSel(1);
		}
		else if(strcmp(wifiPara.cWifiKeyType, "ascii") == 0 && strlen(wifiPara.cWifiPassword) == 13)
		{
			m_cboPwdType.SetCurSel(2);
		}
		else
		{
			m_cboPwdType.SetCurSel(0);
		}
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetLanParam(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetLanParam(%d)", m_iLogonID);
	}
}

BOOL CWifiPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateEncryption(0);
	UI_UpdateKeyType(0);
	UI_UpdatePwdType(0);
	UI_UpdateKeyNum(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWifiPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	UI_UpdateSurface();
	UI_UpdateWifiDhcp();
}

void CWifiPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateSurface();
}

void CWifiPage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser  )
{

}

void CWifiPage::OnBnClickedButtonSearch()
{
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	m_lstWifiList.DeleteAllItems();
	if(0 == NetClient_WifiSearch(m_iLogonID))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_WifiSearch(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_WifiSearch(%d)", m_iLogonID);
	}
}

void CWifiPage::OnBnClickedButtonSetwifi()
{
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	NVS_WIFI_PARAM wifiParam = {0};
	GetDlgItemText(IDC_EDIT_IP, wifiParam.cWifiSvrIP, sizeof(wifiParam.cWifiSvrIP));
	GetDlgItemText(IDC_EDIT_MASK, wifiParam.cWifiMask, sizeof(wifiParam.cWifiMask));
	GetDlgItemText(IDC_EDIT_GATEWAY, wifiParam.cWifiGateway, sizeof(wifiParam.cWifiGateway));
	GetDlgItemText(IDC_EDIT_DNS, wifiParam.cWifiDNS, sizeof(wifiParam.cWifiDNS));
	GetDlgItemText(IDC_EDIT_ESSID, wifiParam.cESSID, sizeof(wifiParam.cESSID));
	GetDlgItemText(IDC_COMBO_KEYTYPE, wifiParam.cWifiKeyType, sizeof(wifiParam.cWifiKeyType));
	GetDlgItemText(IDC_EDIT_PASSWORD, wifiParam.cWifiPassword, sizeof(wifiParam.cWifiPassword));
	GetDlgItemText(IDC_COMBO_ENCRYPTION, wifiParam.cEncryption, sizeof(wifiParam.cEncryption));
	GetDlgItemText(IDC_COMBO_KEYNUM, wifiParam.cWifiKeyNum, sizeof(wifiParam.cWifiKeyNum));

	//限制密码长度
	if (strcmp(wifiParam.cWifiKeyType, "hex") == 0)
	{
		if (m_cboPwdType.GetCurSel() == 1)
		{
			if (strlen(wifiParam.cWifiPassword) != 10)
			{
				MessageBox(GetTextEx(IDS_CONFIG_WIFI_PWD_NOT_LEAGL));;
				return;
			}
		}
		else if (m_cboPwdType.GetCurSel() == 2)
		{
			if (strlen(wifiParam.cWifiPassword) != 26)
			{
				MessageBox(GetTextEx(IDS_CONFIG_WIFI_PWD_NOT_LEAGL));;
				return;
			}
		}
		
	}
	else if(strcmp(wifiParam.cWifiKeyType, "ascii") == 0)
	{
		if (m_cboPwdType.GetCurSel() == 1)
		{
			if (strlen(wifiParam.cWifiPassword) != 5)
			{
				MessageBox(GetTextEx(IDS_CONFIG_WIFI_PWD_NOT_LEAGL));;
				return;
			}
		}
		else if (m_cboPwdType.GetCurSel() == 2)
		{
			if (strlen(wifiParam.cWifiPassword) != 13)
			{
				MessageBox(GetTextEx(IDS_CONFIG_WIFI_PWD_NOT_LEAGL));;
				return;
			}
		}
	}

	int iWifiWorkMode = -1;
	int iCmd = LAN_CMD_SET_WIFIPARA;
	if(0 == NetClient_GetLanParam(m_iLogonID,LAN_CMD_GET_WIFIWORKMODE,&iWifiWorkMode))
	{
		iCmd = (iWifiWorkMode == 2)?LAN_CMD_SET_WIFIAPPARA:LAN_CMD_SET_WIFIPARA;
	}
 
	if(0 == NetClient_SetLanParam(m_iLogonID, iCmd, &wifiParam))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
}

void CWifiPage::OnBnClickedButtonWifimode()
{
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	int  iWifiWorkMode = m_cboWifiWorkMode.GetCurSel();
	if(0 == NetClient_SetLanParam(m_iLogonID, LAN_CMD_SET_WIFIWORKMODE, &iWifiWorkMode))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
}

void CWifiPage::OnBnClickedButtonSetapdhcp()
{
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	WIFIAPDHCPPARA_DHCP  WifiApDHCPPara = {0};
	WifiApDHCPPara.iSize = sizeof(WIFIAPDHCPPARA_DHCP);

	
	WifiApDHCPPara.iDHCPStart = GetDlgItemInt(IDC_EDIT_IPSTART);
	WifiApDHCPPara.iDHCPEnd = GetDlgItemInt(IDC_EDIT_IPEND);
	WifiApDHCPPara.iDHCPLease = GetDlgItemInt(IDC_EDIT_RENTTIME);

	if (0 == NetClient_SetLanParam(m_iLogonID, LAN_CMD_SET_WIFIAPDHCPPARA, &WifiApDHCPPara))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
}

void CWifiPage::OnHdnItemdblclickListWifilist(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = -1;
	if (pNMItemActivate != NULL)
	{
		nItem = pNMItemActivate->iItem;
		if (-1 != nItem)
		{
			SetDlgItemText(IDC_EDIT_ESSID,m_lstWifiList.GetItemText(nItem,0));	
		}
	}
	*pResult = 0;
}

void CWifiPage::OnBnClickedCheckDhcp()
{
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	WIFIPARAM_DHCP WifiParam = {0};
	WifiParam.iSize = sizeof(WIFIPARAM_DHCP);
	WifiParam.iWifiDHCPMode = 0;
	WifiParam.iEnable = (BST_CHECKED == m_chkDhcp.GetCheck())?1:0;

	if (WifiParam.iEnable)
	{
		GetDlgItem(IDC_EDIT_IPSTART)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPEND)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RENTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SETAPDHCP)->EnableWindow(FALSE);
		m_chkApDhcp.SetCheck(BST_UNCHECKED);
	}

	if(0 == NetClient_SetLanParam(m_iLogonID,LAN_CMD_SET_WIFIDHCPMODE,&WifiParam))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
}

void CWifiPage::OnBnClickedCheckApdhcp()
{
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	WIFIPARAM_DHCP WifiParam = {0};
	WifiParam.iSize = sizeof(WIFIPARAM_DHCP);
	WifiParam.iWifiDHCPMode = 1;
	WifiParam.iEnable = (BST_CHECKED == m_chkApDhcp.GetCheck())?1:0;

	if (WifiParam.iEnable)
	{
		GetDlgItem(IDC_EDIT_IPSTART)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IPEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RENTTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SETAPDHCP)->EnableWindow(TRUE);
		m_chkDhcp.SetCheck(BST_UNCHECKED);
	}

	if(0 == NetClient_SetLanParam(m_iLogonID,LAN_CMD_SET_WIFIDHCPMODE,&WifiParam))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetLanParam(%d)", m_iLogonID);
	}
}

void CWifiPage::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser )
{
	int       iWifiCount = 0;
    switch(_iParaType)
	{
	case PARA_WIFI_SEARCH_RESULT:
		WIFI_INFO *pWifiInfo;
		
		NetClient_GetWifiSearchResult(m_iLogonID, &pWifiInfo, &iWifiCount);
		m_lstWifiList.DeleteAllItems();
		for (int i=0; i<iWifiCount; i++)
		{
			int iColumnIndex = 0;;
			m_lstWifiList.InsertItem(0, "");
			m_lstWifiList.SetItemText(0, iColumnIndex++, pWifiInfo[i].cESSID);
			m_lstWifiList.SetItemText(0, iColumnIndex++, pWifiInfo[i].cEncryption);
		}
		break;
	default:
		break;
	}
}

void CWifiPage::UI_UpdateWifiDhcp()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	if (m_chkApDhcp.GetCheck() == BST_CHECKED)
	{
		GetDlgItem(IDC_EDIT_IPSTART)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IPEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RENTTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SETAPDHCP)->EnableWindow(TRUE);

		WIFIAPDHCPPARA_DHCP  WifiApDHCPPara = {0};
		WifiApDHCPPara.iSize = sizeof(WIFIAPDHCPPARA_DHCP);
		if (0 == NetClient_GetLanParam(m_iLogonID, LAN_CMD_GET_WIFIAPDHCPPARA, &WifiApDHCPPara))
		{
			SetDlgItemInt(IDC_EDIT_IPSTART, WifiApDHCPPara.iDHCPStart);
			SetDlgItemInt(IDC_EDIT_IPEND, WifiApDHCPPara.iDHCPEnd);
			SetDlgItemInt(IDC_EDIT_RENTTIME, WifiApDHCPPara.iDHCPLease);
			AddLog(LOG_TYPE_SUCC, "", "NetClient_SetLanParam(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetLanParam(%d)", m_iLogonID);
		}
	}
	else
	{
		GetDlgItem(IDC_EDIT_IPSTART)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPEND)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RENTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SETAPDHCP)->EnableWindow(FALSE);

	}

}