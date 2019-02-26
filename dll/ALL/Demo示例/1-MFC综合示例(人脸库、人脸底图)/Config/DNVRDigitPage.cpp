// DNVRDigitPage.cpp : implementation file
//

#include "stdafx.h"
#include "DNVRDigitPage.h"


// CLS_DNVRDigitPage dialog

IMPLEMENT_DYNAMIC(CLS_DNVRDigitPage, CDialog)

CLS_DNVRDigitPage::CLS_DNVRDigitPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DNVRDigitPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_DNVRDigitPage::~CLS_DNVRDigitPage()
{
}

void CLS_DNVRDigitPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DIGIT_ENABLE, m_chkDigitEnable);
	DDX_Control(pDX, IDC_COMBO_CONNECTMODE, m_cboConnectMode);
	DDX_Control(pDX, IDC_EDIT_IPIDDDNS, m_edtIPIDDDNS);
	DDX_Control(pDX, IDC_EDIT_PROXYIP, m_edtProxyIP);
	DDX_Control(pDX, IDC_COMBO_DEVICECHAN, m_cboDeviceChan);
	DDX_Control(pDX, IDC_EDIT_DEVICEPORT, m_edtDevicePort);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_cboStreamType);
	DDX_Control(pDX, IDC_COMBO_NETMODE, m_cboNetMode);
	DDX_Control(pDX, IDC_COMBO_PTZPROTOCOL, m_cboPTZProtocol);
	DDX_Control(pDX, IDC_EDIT_PTZADDR, m_edtPTZAddr);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_edtUserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edtPassword);
	DDX_Control(pDX, IDC_EDIT_ENCRYPTKEY, m_edtEncryptKey);
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE, m_cboServerType);
	DDX_Control(pDX, IDC_COMBO_IPCPNP, m_cboIPCPnP);
	DDX_Control(pDX, IDC_BUTTON_DIGIT, m_btnDigit);
	DDX_Control(pDX, IDC_EDIT_COMSEND, m_edtComSend);
	DDX_Control(pDX, IDC_BUTTON_COMSEND, m_btnComSend);
}


BEGIN_MESSAGE_MAP(CLS_DNVRDigitPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_IPCPNP, &CLS_DNVRDigitPage::OnCbnSelchangeComboIpcpnp)
	ON_BN_CLICKED(IDC_BUTTON_DIGIT, &CLS_DNVRDigitPage::OnBnClickedButtonDigit)
	ON_BN_CLICKED(IDC_BUTTON_COMSEND, &CLS_DNVRDigitPage::OnBnClickedButtonComsend)
END_MESSAGE_MAP()


// CLS_DNVRDigitPage message handlers
BOOL CLS_DNVRDigitPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_cboConnectMode.AddString("IP");
	m_cboConnectMode.AddString("DDNS");
	m_cboConnectMode.AddString("DSM");

	m_cboStreamType.AddString("Main");
	m_cboStreamType.AddString("Sub");

	m_cboNetMode.AddString("TCP");
	m_cboNetMode.AddString("UDP");
	m_cboNetMode.AddString("MUC");

	m_edtIPIDDDNS.LimitText(32);
	m_edtProxyIP.LimitText(32);
	m_edtDevicePort.LimitText(5);
	m_cboStreamType.SetCurSel(0);
	m_cboNetMode.SetCurSel(0);
	m_edtPTZAddr.LimitText(5);
	m_edtUserName.LimitText(16);
	m_edtPassword.LimitText(16);
	m_edtEncryptKey.LimitText(16);

	SetDlgItemText(IDC_EDIT_COMSEND, "00,01,02,03,04,05,06,07");
	UI_UpdateDialog();

	return TRUE;
}

void CLS_DNVRDigitPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

	UI_UpdateDigit();
	UI_UpdateIPCPnp();
}

void CLS_DNVRDigitPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DNVRDigitPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_CHECK_DIGIT_ENABLE,IDS_CONFIG_FTP_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_CONNECTMODE,IDS_CONFIG_DNVR_DIGIT_CONNECTMODE);
	SetDlgItemTextEx(IDC_STATIC_IPIDDDNS,IDS_CONFIG_DNVR_DIGIT_IPIDDDNS);
	SetDlgItemTextEx(IDC_STATIC_PROXYIP,IDS_CONFIG_DNVR_DIGIT_PROXYIP);
	SetDlgItemTextEx(IDC_STATIC_DEVICECHAN,IDS_CONFIG_DNVR_DIGIT_DEVICECHAN);
	SetDlgItemTextEx(IDC_STATIC_DEVICEPORT,IDS_CONFIG_DNVR_DIGIT_DEVICEPORT);
	SetDlgItemTextEx(IDC_STATIC_STREAMTYPE,IDS_CONFIG_DNVR_DIGIT_STREAMTYPE);
	SetDlgItemTextEx(IDC_STATIC_NETMODE,IDS_CONFIG_DNVR_DIGIT_NETMODE);
	SetDlgItemTextEx(IDC_STATIC_PTZPROTOCOL,IDS_CONFIG_DNVR_DIGIT_PTZPROTOCOL);
	SetDlgItemTextEx(IDC_STATIC_PTZADDR,IDS_CONFIG_DNVR_DIGIT_PTZADDR);
	SetDlgItemTextEx(IDC_STATIC_USERNAME,IDS_CONFIG_DNVR_DIGIT_USERNAME);
	SetDlgItemTextEx(IDC_STATIC_PASSWORD,IDS_CONFIG_DNVR_DIGIT_PASSWORD);
	SetDlgItemTextEx(IDC_STATIC_ENCRYPTKEY,IDS_CONFIG_DNVR_DIGIT_ENCRYPTKEY);
	SetDlgItemTextEx(IDC_STATIC_SERVERTYPE,IDS_CONFIG_DNVR_DIGIT_SERVERTYPE);
	SetDlgItemTextEx(IDC_STATIC_IPCPNP,IDS_CONFIG_DNVR_DIGIT_IPCPNP);
	SetDlgItemTextEx(IDC_BUTTON_DIGIT,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_COMSEND,IDS_CONFIG_DNVR_DIGIT_COMSEND);
	SetDlgItemTextEx(IDC_BUTTON_COMSEND,IDS_CONFIG_DNVR_DIGIT_SEND);

	InsertString(m_cboServerType,0,IDS_CONFIG_DNVR_PRIVATE);
	InsertString(m_cboServerType,1,IDS_CONFIG_DNVR_ONVIF);
	InsertString(m_cboServerType,2,IDS_CONFIG_DNVR_PUSHSTREAM);
	InsertString(m_cboServerType,3,"RTSP");

	InsertString(m_cboIPCPnP,0,IDS_CONFIG_DNVR_DISABLE);
	InsertString(m_cboIPCPnP,1,IDS_CONFIG_DNVR_AUTO);
	InsertString(m_cboIPCPnP,2,IDS_CONFIG_DNVR_NOTICE);
}

BOOL CLS_DNVRDigitPage::UI_UpdateDigit()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iChannelProperty = -1;
	int iRet = NetClient_GetChannelProperty(m_iLogonID, m_iChannelNo, GENERAL_CMD_GET_CHANNEL_TYPE, &iChannelProperty, sizeof(iChannelProperty));
	if (iChannelProperty != 2)
	{
		m_chkDigitEnable.SetCheck(BST_UNCHECKED);
		m_chkDigitEnable.EnableWindow(FALSE);
		m_cboConnectMode.SetCurSel(0);
		SetDlgItemText(IDC_EDIT_IPIDDDNS, "");
		SetDlgItemText(IDC_EDIT_PROXYIP, "");
		SetDlgItemText(IDC_EDIT_DEVICEPORT, "");
		m_cboDeviceChan.ResetContent();
		m_cboStreamType.SetCurSel(0);
		m_cboNetMode.SetCurSel(0);
		SetDlgItemText(IDC_EDIT_PTZADDR, "");
		SetDlgItemText(IDC_EDIT_USERNAME, "");
		SetDlgItemText(IDC_EDIT_PASSWORD, "");
		SetDlgItemText(IDC_EDIT_ENCRYPTKEY, "");
		m_cboServerType.SetCurSel(0);
		for (int i=0; i<32; i++)
		{
			CString strDeviceChan;
			strDeviceChan.Format("%d",i);
			m_cboDeviceChan.AddString(strDeviceChan);
		}
		return FALSE;
	}
	m_cboDeviceChan.ResetContent();
	for (int i=0; i<32; i++)
	{
		CString strDeviceChan;
		strDeviceChan.Format("%d",i);
		m_cboDeviceChan.AddString(strDeviceChan);
	}
	TDigitalChannelParam dcp = {0};
	dcp.iChannel = m_iChannelNo;
	iRet = NetClient_GetDigitalChannelConfig(m_iLogonID, m_iChannelNo, DC_CMD_GET_ALL, &dcp, sizeof(dcp));
	if (0 == iRet)
	{
		m_chkDigitEnable.SetCheck(dcp.iEnable?BST_CHECKED:BST_UNCHECKED);
		m_chkDigitEnable.EnableWindow(TRUE);
		m_cboConnectMode.SetCurSel(dcp.iConnectMode);
		SetDlgItemText(IDC_EDIT_IPIDDDNS, dcp.cIP);
		SetDlgItemText(IDC_EDIT_PROXYIP, dcp.cProxyIP);
		CString strDeviceChannel;
		strDeviceChannel.Format("%d",dcp.iDevChannel);
		m_cboDeviceChan.SelectString(-1, strDeviceChannel);
		SetDlgItemInt(IDC_EDIT_DEVICEPORT, dcp.iDevPort);
		m_cboStreamType.SetCurSel(dcp.iStreamType);
		m_cboNetMode.SetCurSel(dcp.iNetMode-1);
		SetDlgItemInt(IDC_EDIT_PTZADDR, dcp.iPtzAddr);
		SetDlgItemText(IDC_EDIT_USERNAME, dcp.cUserName);
		SetDlgItemText(IDC_EDIT_PASSWORD, dcp.cPassword);
		SetDlgItemText(IDC_EDIT_ENCRYPTKEY, dcp.cEncryptKey);
		SetDlgItemText(IDC_EDIT_RTSP_URL, dcp.cRTSPUrlEx);

		m_cboServerType.SetCurSel(dcp.iServerType);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
	st_NVSProtocol protocol;
	m_cboPTZProtocol.ResetContent();
	m_cboPTZProtocol.AddString("PTZ_PELCO_D");
	m_cboPTZProtocol.AddString("PTZ_PELCO_P");
	m_cboPTZProtocol.AddString("PTZ_TC615_P");
	m_cboPTZProtocol.AddString("DOME_PELCO_D");
	m_cboPTZProtocol.AddString("DOME_PELCO_P");
	m_cboPTZProtocol.AddString("DOME_PLUS");
	memset(&protocol,0,sizeof(st_NVSProtocol));
	iRet = NetClient_GetProtocolList(m_iLogonID,&protocol);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetProtocolList(%d,%#x)",m_iLogonID,&protocol);
		int iProtocolIndex = -1;
		for (int i = 0; i < protocol.iCount; i++)
		{
			iProtocolIndex = m_cboPTZProtocol.FindStringExact(-1,protocol.cProtocol[i]);
			if (iProtocolIndex < 0)
			{
				m_cboPTZProtocol.AddString(protocol.cProtocol[i]);
			}
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetProtocolList(%d,%#x)",m_iLogonID,&protocol);
	}
	int iComPort = 0;
	int iDevAddress = 0;
	int iChannelNo = 0;
	char cDeviceType[64]= {0};
	iRet = NetClient_GetDeviceType(m_iLogonID,iChannelNo,&iComPort,&iDevAddress,cDeviceType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)",m_iLogonID,iChannelNo,iComPort,iDevAddress,cDeviceType);
		m_cboPTZProtocol.SelectString(-1,cDeviceType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)",m_iLogonID,iChannelNo,iComPort,iDevAddress,cDeviceType);
	}
	return TRUE;
}

void CLS_DNVRDigitPage::OnCbnSelchangeComboIpcpnp()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iIPCPnP = m_cboIPCPnP.GetCurSel();
	int iRet = NetClient_SetDigitalChannelConfig(m_iLogonID,m_iChannelNo,DC_CMD_SET_IPCPnP,&iIPCPnP,sizeof(int));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
}

BOOL CLS_DNVRDigitPage::UI_UpdateIPCPnp()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iIPCPnP = 0;
	if(0 == NetClient_GetDigitalChannelConfig(m_iLogonID,m_iChannelNo,DC_CMD_GET_IPCPnP,&iIPCPnP,sizeof(int)))
	{
		m_cboIPCPnP.SetCurSel(iIPCPnP);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
	return TRUE;
}

void CLS_DNVRDigitPage::OnBnClickedButtonDigit()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TDigitalChannelParam dcp = {0};
	dcp.iChannel = m_iChannelNo;
	dcp.iEnable = (m_chkDigitEnable.GetCheck() == BST_CHECKED)?1:0;
	dcp.iConnectMode = m_cboConnectMode.GetCurSel();
	GetDlgItemText(IDC_EDIT_IPIDDDNS, dcp.cIP, 32);
	GetDlgItemText(IDC_EDIT_PROXYIP, dcp.cProxyIP, 32);
	CString strDeviceChannel;
	GetDlgItemText(IDC_COMBO_DEVICECHAN, strDeviceChannel);
	dcp.iDevChannel = atoi(strDeviceChannel);
	dcp.iDevPort = GetDlgItemInt(IDC_EDIT_DEVICEPORT);
	dcp.iStreamType = m_cboStreamType.GetCurSel();
	dcp.iNetMode = m_cboNetMode.GetCurSel() + 1;
	GetDlgItemText(IDC_COMBO_PTZPROTOCOL, dcp.cPtzProtocolName, 32);
	dcp.iPtzAddr = GetDlgItemInt(IDC_EDIT_PTZADDR);
	GetDlgItemText(IDC_EDIT_USERNAME, dcp.cUserName, 16);
	GetDlgItemText(IDC_EDIT_PASSWORD, dcp.cPassword, 16);
	GetDlgItemText(IDC_EDIT_ENCRYPTKEY, dcp.cEncryptKey, 16);
	
	dcp.iServerType = m_cboServerType.GetCurSel();
	if (dcp.iServerType == SERVERTYPE_RTSP)
	{
		GetDlgItemText(IDC_EDIT_RTSP_URL, dcp.cRTSPUrlEx, 4*MAX_RTSPURL_LEN_EX);
	}
	else
	{
		GetDlgItemText(IDC_EDIT_RTSP_URL, dcp.cRTSPUrlEx, MAX_RTSPURL_LEN);
	}

	int iRet = NetClient_SetDigitalChannelConfig(m_iLogonID, m_iChannelNo, DC_CMD_SET_ALL, &dcp, sizeof(dcp));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDigitalChannelConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}
}

void CLS_DNVRDigitPage::OnBnClickedButtonComsend()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	CString strData;
	GetDlgItemText(IDC_EDIT_COMSEND,strData);
	strData.Replace(_T(","),_T(""));
	strData.Replace(_T(" "),_T(""));
	strData.Replace(_T("\r"),_T(""));
	strData.Replace(_T("\n"),_T(""));
	char* pucData = (LPSTR)(LPCTSTR)strData;
	char ucBuf[1024] = {0};
	int iLen = strData.GetLength()/2;
	if (iLen >= 1024)
	{
		iLen = 1023;
	}
	int i;
	for (i = 0; i < iLen; ++i)
	{
		sscanf_s(pucData+i*2,"%2x",ucBuf+i);
	}

	int iRet = NetClient_DigitalChannelSend(m_iLogonID, m_iChannelNo,(unsigned char *)ucBuf,i);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DigitalChannelSend(%d,%#x,%d)",m_iLogonID,ucBuf,i);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DigitalChannelSend(%d,%#x,%d)",m_iLogonID,ucBuf,i);
	}

}