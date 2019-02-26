// PUPage.cpp : implementation file
//

#include "stdafx.h"
#include "PUPage.h"
#include "../Common/md5.h"


// CLS_PUPage dialog

IMPLEMENT_DYNAMIC(CLS_PUPage, CDialog)

CLS_PUPage::CLS_PUPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_PUPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_PUPage::~CLS_PUPage()
{
}

void CLS_PUPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_REGISTERSVR, m_edtRegisterSvr);
	DDX_Control(pDX, IDC_EDIT_REGISTERSVR_PORT, m_edtRegisterSvrPort);
	DDX_Control(pDX, IDC_EDIT_HEARTBEATSVR, m_edtHeartbeatSvr);
	DDX_Control(pDX, IDC_EDIT_HEARTBEATSVR_PORT, m_edtHeartbeatSvrPort);
	DDX_Control(pDX, IDC_EDIT_ALARMSVR, m_edtAlarmSvr);
	DDX_Control(pDX, IDC_EDIT_ALARMSVR_PORT, m_edtAlarmSvrPort);
	DDX_Control(pDX, IDC_BUTTON_MANAGEINFO, m_btnManageInfo);
	DDX_Control(pDX, IDC_EDIT_DEVICEID, m_edtDeviceID);
	DDX_Control(pDX, IDC_EDIT_DEVICENAME, m_edtDeviceName);
	DDX_Control(pDX, IDC_EDIT_VSPPORT, m_edtVSPPort);
	DDX_Control(pDX, IDC_EDIT_VAPPORT, m_edtVAPPort);
	DDX_Control(pDX, IDC_EDIT_ACCESSPASS, m_edtAccessPass);
	DDX_Control(pDX, IDC_EDIT_MD5, m_edtMD5);
	DDX_Control(pDX, IDC_BUTTON_DEVICEID, m_btnDeviceID);
}


BEGIN_MESSAGE_MAP(CLS_PUPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_MANAGEINFO, &CLS_PUPage::OnBnClickedButtonManageinfo)
	ON_BN_CLICKED(IDC_BUTTON_DEVICEID, &CLS_PUPage::OnBnClickedButtonDeviceid)
	ON_EN_CHANGE(IDC_EDIT_ACCESSPASS, &CLS_PUPage::OnEnChangeEditAccesspass)
	ON_BN_CLICKED(IDC_BTN_IDENTI_CODE, &CLS_PUPage::OnBnClickedBtnIdentiCode)
	ON_BN_CLICKED(IDC_BTN_BARCODE_SET, &CLS_PUPage::OnBnClickedBtnBarcodeSet)
END_MESSAGE_MAP()


// CLS_PUPage message handlers

BOOL CLS_PUPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	
	m_edtRegisterSvr.SetLimitText(16);
	m_edtRegisterSvrPort.SetLimitText(5);
	m_edtHeartbeatSvr.SetLimitText(16);
	m_edtHeartbeatSvrPort.SetLimitText(5);
	m_edtAlarmSvr.SetLimitText(16);
	m_edtAlarmSvrPort.SetLimitText(5);

	m_edtDeviceID.SetLimitText(32);
	m_edtDeviceName.SetLimitText(32);
	m_edtVSPPort.SetLimitText(5);
	m_edtVAPPort.SetLimitText(5);
	m_edtAccessPass.SetLimitText(32);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_PUPage::OnChannelChanged(int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;

	UI_UpdateManagerInfo();
	UI_UpdateDeviceID();
	UI_UpdateIdentiCode();
	UI_UpdateBarCode();
}

void CLS_PUPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_PUPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_MANAGERINFO, IDS_CONFIG_OPTION_PU_MANAGERINFO);
	SetDlgItemTextEx(IDC_STATIC_REGISTERSVR, IDS_CONFIG_OPTION_PU_REGISTERSVR);
	SetDlgItemTextEx(IDC_STATIC_HEARTBEATSVR, IDS_CONFIG_OPTION_PU_HEARTBEATSVR);
	SetDlgItemTextEx(IDC_STATIC_ALARMSVR, IDS_CONFIG_OPTION_PU_ALARMSVR);
	SetDlgItemTextEx(IDC_BUTTON_MANAGEINFO, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DEVICE, IDS_CONFIG_OPTION_PU_DEVICEID);
	SetDlgItemTextEx(IDC_STATIC_DEVICEID, IDS_CONFIG_OPTION_PU_DEVICEID);
	SetDlgItemTextEx(IDC_STATIC_DEVICENAME, IDS_CONFIG_OPTION_PU_DEVICENAME);
	SetDlgItemTextEx(IDC_STATIC_VSPPORT, IDS_CONFIG_OPTION_PU_VSPPORT);
	SetDlgItemTextEx(IDC_STATIC_VAPPORT, IDS_CONFIG_OPTION_PU_VAPPORT);
	SetDlgItemTextEx(IDC_STATIC_ACCESSPASS, IDS_CONFIG_OPTION_PU_ACCESSPASS);
	SetDlgItemTextEx(IDC_BUTTON_DEVICEID, IDS_SET);
	SetDlgItemTextEx(IDC_STC_IDENTI_CODE, IDS_IDENTIFICATION_CODE);
	SetDlgItemTextEx(IDC_BTN_IDENTI_CODE, IDS_SET);
	SetDlgItemTextEx(IDC_STC_BARCODE, IDS_BAR_CODE);
	SetDlgItemTextEx(IDC_BTN_BARCODE_SET, IDS_SET);
	
}

void CLS_PUPage::OnBnClickedButtonManageinfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	char cRegSvrIP[33] = {0};
	unsigned short usRegPort;
	char cHeartSvrIP[33] = {0};
	unsigned short usHeartPort;
	char cAlarmSvrIP[33] = {0};
	unsigned short usAlarmPort;

	GetDlgItemText(IDC_EDIT_REGISTERSVR, cRegSvrIP, 16);
	usRegPort = GetDlgItemInt(IDC_EDIT_REGISTERSVR_PORT);
	GetDlgItemText(IDC_EDIT_HEARTBEATSVR, cHeartSvrIP, 16);
	usHeartPort = GetDlgItemInt(IDC_EDIT_HEARTBEATSVR_PORT);
	GetDlgItemText(IDC_EDIT_ALARMSVR, cAlarmSvrIP, 16);
	usAlarmPort = GetDlgItemInt(IDC_EDIT_ALARMSVR_PORT);

	if (IsValidIP(cRegSvrIP) != 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Change Register Server IP is invalid");
		return;
	}
	if (IsValidIP(cHeartSvrIP) != 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Change Heartbeat Server IP is invalid");
		return;
	}
	if (IsValidIP(cAlarmSvrIP) != 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Change Alarm Server IP is invalid");
		return;
	}
	
	int iRet = NetClient_SetManagerServersInfo(m_iLogonID, cRegSvrIP, usRegPort, cHeartSvrIP, usHeartPort, cAlarmSvrIP, usAlarmPort);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetManagerServersInfo(%d,%s,%d,%s,%d,%s,%d)",m_iLogonID,cRegSvrIP,usRegPort,cHeartSvrIP,usHeartPort,cAlarmSvrIP,usAlarmPort);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetManagerServersInfo(%d,%s,%d,%s,%d,%s,%d)",m_iLogonID,cRegSvrIP,usRegPort,cHeartSvrIP,usHeartPort,cAlarmSvrIP,usAlarmPort);
	}
}

BOOL CLS_PUPage::UI_UpdateManagerInfo()
{
	if (m_iLogonID < 0)
		return FALSE;

	char cRegSvrIP[33] = {0};
	unsigned short usRegPort;
	char cHeartSvrIP[33] = {0};
	unsigned short usHeartPort;
	char cAlarmSvrIP[33] = {0};
	unsigned short usAlarmPort;

	int iRet = NetClient_GetManagerServersInfo(m_iLogonID, cRegSvrIP, &usRegPort, cHeartSvrIP, &usHeartPort, cAlarmSvrIP, &usAlarmPort);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_REGISTERSVR, cRegSvrIP);
		SetDlgItemInt(IDC_EDIT_REGISTERSVR_PORT, usRegPort);
		SetDlgItemText(IDC_EDIT_HEARTBEATSVR, cHeartSvrIP);
		SetDlgItemInt(IDC_EDIT_HEARTBEATSVR_PORT, usHeartPort);
		SetDlgItemText(IDC_EDIT_ALARMSVR, cAlarmSvrIP);
		SetDlgItemInt(IDC_EDIT_ALARMSVR_PORT, usAlarmPort);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetManagerServersInfo(%d,%s,%d,%s,%d,%s,%d)",m_iLogonID,cRegSvrIP,usRegPort,cHeartSvrIP,usHeartPort,cAlarmSvrIP,usAlarmPort);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetManagerServersInfo(%d,%s,%d,%s,%d,%s,%d)",m_iLogonID,cRegSvrIP,usRegPort,cHeartSvrIP,usHeartPort,cAlarmSvrIP,usAlarmPort);
	}
	return TRUE;
}

void CLS_PUPage::OnBnClickedButtonDeviceid()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	char cDeviceID[33] = {0};
	char cDeviceName[33] = {0};
	unsigned short usVSPPort;
	unsigned short usVAPPort;
	char cMD5Password[36] = {0};
	GetDlgItemText(IDC_EDIT_DEVICEID, cDeviceID, 32);
	GetDlgItemText(IDC_EDIT_DEVICENAME, cDeviceName, 32);
	usVSPPort = GetDlgItemInt(IDC_EDIT_VSPPORT);
	usVAPPort = GetDlgItemInt(IDC_EDIT_VAPPORT);
	GetDlgItemText(IDC_EDIT_MD5, cMD5Password, 35);
	int iRet = NetClient_SetDeviceID(m_iLogonID, cDeviceID, cDeviceName, usVSPPort, cMD5Password, usVAPPort);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDeviceID(%d,%s,%s,%d,%s,%d)",m_iLogonID,cDeviceID,cDeviceName,usVSPPort,cMD5Password,usVAPPort);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDeviceID(%d,%s,%s,%d,%s,%d)",m_iLogonID,cDeviceID,cDeviceName,usVSPPort,cMD5Password,usVAPPort);
	}
}

BOOL CLS_PUPage::UI_UpdateDeviceID()
{
	if (m_iLogonID < 0)
		return FALSE;

	char cDeviceID[33] = {0};
	char cDeviceName[33] = {0};
	unsigned short usVSPPort;
	unsigned short usVAPPort;
	char cMD5Password[36] = {0};
	int iRet = NetClient_GetDeviceID(m_iLogonID, cDeviceID, cDeviceName, &usVSPPort, cMD5Password, &usVAPPort);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_DEVICEID, cDeviceID);
		SetDlgItemText(IDC_EDIT_DEVICENAME, cDeviceName);
		SetDlgItemInt(IDC_EDIT_VSPPORT, usVSPPort);
		SetDlgItemInt(IDC_EDIT_VAPPORT, usVAPPort);
		SetDlgItemText(IDC_EDIT_MD5, cMD5Password);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDeviceID(%d,%s,%s,%d,%s,%d)",m_iLogonID,cDeviceID,cDeviceName,usVSPPort,cMD5Password,usVAPPort);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceID(%d,%s,%s,%d,%s,%d)",m_iLogonID,cDeviceID,cDeviceName,usVSPPort,cMD5Password,usVAPPort);
	}
	return TRUE;
}

void CLS_PUPage::OnEnChangeEditAccesspass()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	m_edtMD5.Clear();
	unsigned char ucAccessPassword[33] = {0};
	unsigned int uiLen;
	unsigned char ucMD5Password[33] = {0};
	GetDlgItemText(IDC_EDIT_ACCESSPASS, (LPTSTR)ucAccessPassword, 32);
	uiLen = m_edtAccessPass.GetWindowTextLength();
	MD5(ucAccessPassword, uiLen, ucMD5Password);
	SetDlgItemText(IDC_EDIT_MD5,(LPTSTR)ucMD5Password);

}

BOOL CLS_PUPage::UI_UpdateIdentiCode()
{
	if (m_iLogonID < 0)
		return FALSE;

	IdentiCode stIdentiCode = {0};
	stIdentiCode.iBufSize = sizeof(IdentiCode);
	int iRetSize;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_IDENTI_CODE,0, &stIdentiCode, sizeof(IdentiCode), &iRetSize);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_DEVICEID, stIdentiCode.cParam);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(%d,%d,%s,%d,%d)",m_iLogonID,NET_CLIENT_IDENTI_CODE,stIdentiCode.cParam,sizeof(IdentiCode),iRetSize);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(%d,%d,%s,%d,%d)",m_iLogonID,NET_CLIENT_IDENTI_CODE,stIdentiCode.cParam,sizeof(IdentiCode),iRetSize);
	}
	return TRUE;
}


void CLS_PUPage::OnBnClickedBtnIdentiCode()
{
	if (m_iLogonID < 0)
		return ;

	IdentiCode stIdentiCode = {0};
	stIdentiCode.iBufSize = sizeof(IdentiCode);
	CString cstr = "";
	GetDlgItemText(IDC_EDT_IDENTI_CODE, cstr);
	memcpy(stIdentiCode.cParam, cstr, sizeof(stIdentiCode.cParam));
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_IDENTI_CODE,0, &stIdentiCode, sizeof(IdentiCode));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d,%s,%d)",m_iLogonID,NET_CLIENT_IDENTI_CODE,stIdentiCode.cParam,sizeof(IdentiCode));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d,%s,%d)",m_iLogonID,NET_CLIENT_IDENTI_CODE,stIdentiCode.cParam,sizeof(IdentiCode));
	}
}

BOOL CLS_PUPage::UI_UpdateBarCode()
{
	if (m_iLogonID < 0)
		return FALSE;

	char cBarCode[64];
	int iRetSize = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_BARCODE,0, &cBarCode, sizeof(char), &iRetSize);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDT_BARCODE, cBarCode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(%d,%d,%s,%d,%d)",m_iLogonID,NET_CLIENT_BARCODE,cBarCode,sizeof(char),iRetSize);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(%d,%d,%s,%d,%d)",m_iLogonID,NET_CLIENT_BARCODE,cBarCode,sizeof(char),iRetSize);
	}
	return TRUE;
}

void CLS_PUPage::OnBnClickedBtnBarcodeSet()
{
	if (m_iLogonID < 0)
		return ;

	char cBarCode[64];
	CString cstr = "";
	GetDlgItemText(IDC_EDT_BARCODE, cstr);
	strcpy(cBarCode, cstr);
	//cBarCode = cstr;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_BARCODE,0, &cBarCode, sizeof(char));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d,%s,%d)",m_iLogonID,NET_CLIENT_BARCODE,cstr,sizeof(char));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d,%s,%d)",m_iLogonID,NET_CLIENT_BARCODE,cstr,sizeof(char));
	}
}
