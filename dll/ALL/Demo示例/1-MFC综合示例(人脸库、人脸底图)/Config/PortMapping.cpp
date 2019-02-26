#include "stdafx.h"
#include "NetClientDemo.h"
#include "PortMapping.h"

// CLS_LinkHttp dialog

IMPLEMENT_DYNAMIC(CLS_PortMapping, CDialog)

CLS_PortMapping::CLS_PortMapping(CWnd* pParent /*=NULL*/)
: CLS_BasePage(CLS_PortMapping::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_PortMapping::~CLS_PortMapping()
{
	
}

void CLS_PortMapping::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LAN_PORT_PORTTYPE, m_cboPortType);
	DDX_Control(pDX, IDC_CHK_LAN_PORT_ENABLE, m_chkLanPortEnalbe);
	DDX_Control(pDX, IDC_BTN_LAN_PORT_SET, m_btnLanPortSet);
	DDX_Control(pDX, IDC_EDT_LAN_PORT_PORTMAPPING, m_edtLanMapPort);
}

BEGIN_MESSAGE_MAP(CLS_PortMapping, CDialog)
	ON_BN_CLICKED(IDC_BTN_LAN_PORT_SET, &CLS_PortMapping::OnBnClickedBtnLanPortSet)
	ON_CBN_SELCHANGE(IDC_COMBO_LAN_PORT_PORTTYPE, &CLS_PortMapping::OnCbnSelchangeComboLanPortPorttype)
END_MESSAGE_MAP()

BOOL CLS_PortMapping::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialogText();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_PortMapping::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_GBO_LAN_PORT_PORTMAPPING,IDS_CONFIG_LAN_PORT_CBOPORTMAPPING);
	SetDlgItemTextEx(IDC_CHK_LAN_PORT_ENABLE,IDS_CONFIG_LAN_PORT_CHKENABLE);
	SetDlgItemTextEx(IDC_STC_LAN_PORT_PORTMAPPING,IDS_CONFIG_LAN_PORT_STCPORTMAPPING);
	SetDlgItemTextEx(IDC_STC_LAN_PORT_PORTTYPE,IDS_CONFIG_LAN_PORT_STCPORTTYPE);
	SetDlgItemTextEx(IDC_BTN_LAN_PORT_SET,IDS_CONFIG_LAN_PORT_BTNSET);
	SetDlgItemTextEx(IDC_STC_LAN_PORT_SRC_PORT, IDS_CONFIG_LAN_SRC_PORT);

	InsertString(m_cboPortType,0,IDS_CONFIG_LAN_PORT_PORTTYPEH);
	InsertString(m_cboPortType,1,IDS_CONFIG_LAN_PORT_PORTTYPEDATA);
	InsertString(m_cboPortType,2,IDS_CONFIG_LAN_PORT_PORTTYPEUDP);
	m_cboPortType.SetCurSel(0);
}

void CLS_PortMapping::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialogText();
	UI_UpdatePortMapInfo();
}

void CLS_PortMapping::OnBnClickedBtnLanPortSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_PortMapping::OnBnClickedBtnLanPortSet]Invalid logon id(%d)", m_iLogonID);
		return;
	}
	
	RouteNat tRouteNatInfo = {0};
	GetInfoByDialog(&tRouteNatInfo);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_ROUTE_NAT, m_iChannelNo, &tRouteNatInfo, sizeof(RouteNat));
	if (RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_PortMapping::OnBnClickedBtnLanPortSet][NET_CLIENT_ROUTE_NAT] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[CLS_PortMapping::OnBnClickedBtnLanPortSet][NET_CLIENT_ROUTE_NAT] set success!");
	}
}

void CLS_PortMapping::GetInfoByDialog(RouteNat *_pRouteNatInfo)
{
	if(NULL == _pRouteNatInfo)
	{	
		return;
	}

	int iMapPort = GetDlgItemInt(IDC_EDT_LAN_PORT_PORTMAPPING);
	int iEnable = m_chkLanPortEnalbe.GetCheck();
	int iIndex = m_cboPortType.GetCurSel();

	_pRouteNatInfo->iSize = sizeof(RouteNat);
	_pRouteNatInfo->iProxyPort = iMapPort;
	_pRouteNatInfo->iEnable = iEnable;
	_pRouteNatInfo->iPortType = iIndex + 1; //端口类型从1开始，将索引值加1
	_pRouteNatInfo->iIpcSrcPort = GetDlgItemInt(IDC_EDT_LAN_PORT_SRC_PORT);
}

void CLS_PortMapping::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
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
	
	UI_UpdatePortMapInfo();
}

void CLS_PortMapping::UI_UpdatePortMapInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_PortMapping::UI_UpdatePortMapInfo] Invalid logon id(%d)", m_iLogonID);
		return;
	}
	
	RouteNat tRouteNatParam = {0};
	tRouteNatParam.iSize = sizeof(RouteNat);
	tRouteNatParam.iPortType = m_cboPortType.GetCurSel() + 1;
	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ROUTE_NAT, m_iChannelNo, &tRouteNatParam, sizeof(RouteNat), &iReturnByte);
	if (RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_PortMapping::UI_UpdatePortMapInfo][NET_CLIENT_ROUTE_NAT] Set fail,error = %d", GetLastError());
	}
	else
	{
		m_chkLanPortEnalbe.SetCheck(tRouteNatParam.iEnable);
		SetDlgItemInt(IDC_EDT_LAN_PORT_PORTMAPPING, tRouteNatParam.iProxyPort);
		SetDlgItemInt(IDC_EDT_LAN_PORT_SRC_PORT, tRouteNatParam.iIpcSrcPort);
		AddLog(LOG_TYPE_SUCC, "", "[CLS_PortMapping::UI_UpdatePortMapInfo][NET_CLIENT_ROUTE_NAT] set success!");
	}
}

void CLS_PortMapping::OnCbnSelchangeComboLanPortPorttype()
{
	UI_UpdatePortMapInfo();
}
