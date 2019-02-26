// Config\SipPage.cpp : implementation file
//

#include "stdafx.h"
#include "SipPage.h"


// CLS_SipPage dialog

IMPLEMENT_DYNAMIC(CLS_SipPage, CDialog)

CLS_SipPage::CLS_SipPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_SipPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_SipPage::~CLS_SipPage()
{
}

void CLS_SipPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_SIP_LEVEL1, m_edtSipLevel1);
	DDX_Control(pDX, IDC_EDIT_SIP_PTZTIME, m_edtSipPtztime);
	DDX_Control(pDX, IDC_EDIT_SIP_LEVEL2, m_edtSipLevel2);
	DDX_Control(pDX, IDC_EDIT_SIP_CHANNELID1, m_edtSipChannelID1);
	DDX_Control(pDX, IDC_EDIT_SIP_CHANNELID2, m_edtSipChannelID2);
	DDX_Control(pDX, IDC_COMBO_ALARM, m_cboAlarmNo);
}


BEGIN_MESSAGE_MAP(CLS_SipPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SIP_VIDEOCHANNELSET, &CLS_SipPage::OnBnClickedButtonSipVideochannelset)
	ON_BN_CLICKED(IDC_BUTTON_SIP_ALARMCHANNELSET, &CLS_SipPage::OnBnClickedButtonSipAlarmchannelset)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM, &CLS_SipPage::OnCbnSelchangeComboAlarm)
	ON_BN_CLICKED(IDC_BTN_TEST, &CLS_SipPage::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CLS_SipPage message handlers
BOOL CLS_SipPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtSipChannelID1.SetLimitText(32);
	m_edtSipChannelID2.SetLimitText(32);
	m_edtSipLevel1.SetLimitText(10);
	m_edtSipLevel2.SetLimitText(10);
	m_edtSipPtztime.SetLimitText(10);
    UI_UpdateDialog();
	return TRUE;
}

void CLS_SipPage::OnChannelChanged(int _iLogonID, int _iChannelNo, int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon ID(%d)", m_iLogonID);
		return;
	}
	if (_iChannelNo < 0)
	{
		m_iChannelNum = 0;
	}
	else
	{
		m_iChannelNum = _iChannelNo;
	}
	int iAlarmChannelNo = 0,iAlarmOutPortNum = 0;
	int iRet = NetClient_GetAlarmPortNum(m_iLogonID, &iAlarmChannelNo, &iAlarmOutPortNum);
	m_cboAlarmNo.ResetContent();
	for (int i = 0; i < iAlarmChannelNo; i++)
	{
		CString szChannel;
		szChannel.Format("%d", i);
		m_cboAlarmNo.AddString(szChannel);
	}
	m_cboAlarmNo.SetCurSel(0);
	GetChannelSipInfo();
}

void CLS_SipPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}
void CLS_SipPage::OnBnClickedButtonSipVideochannelset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon ID(%d)", m_iLogonID);
		return;
	}

	CString strChannelID;
	m_edtSipChannelID1.GetWindowText(strChannelID);
	TSipVideoChannel svc = {0};
	svc.iChannelNo = m_iChannelNum;
	strcpy_s(svc.cChannelID, sizeof(svc.cChannelID), strChannelID);
	svc.iLevel = GetDlgItemInt(IDC_EDIT_SIP_LEVEL1);
	svc.iPtzTime = GetDlgItemInt(IDC_EDIT_SIP_PTZTIME);

	int iRet =  NetClient_SetChannelSipConfig(m_iLogonID, m_iChannelNum, SIP_CMD_SET_VIDEOCHANNEL, &svc, sizeof(svc));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
}

void CLS_SipPage::OnBnClickedButtonSipAlarmchannelset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon ID(%d)", m_iLogonID);
		return;
	}

	CString strChannelID;
	m_edtSipChannelID2.GetWindowText(strChannelID);
	TSipAlarmChannel sac = {0};
	sac.iChannelNo = m_cboAlarmNo.GetCurSel();
	strcpy_s(sac.cChannelID, sizeof(sac.cChannelID), strChannelID);
	sac.iLevel = GetDlgItemInt(IDC_EDIT_SIP_LEVEL2);

	int iRet = NetClient_SetChannelSipConfig(m_iLogonID, sac.iChannelNo, SIP_CMD_SET_ALARMCHANNEL, &sac, sizeof(sac));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
}

void CLS_SipPage::GetChannelSipInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon ID(%d)", m_iLogonID);
		return;
	}

	TSipVideoChannel svc = {0};
	svc.iChannelNo = m_iChannelNum;
	int iCmd = SIP_CMD_GET_VIDEOCHANNEL;
	int iRet1 = NetClient_GetChannelSipConfig(m_iLogonID, m_iChannelNum, SIP_CMD_GET_VIDEOCHANNEL, &svc, sizeof(svc));
	if (iRet1 == 0)
	{
		m_edtSipChannelID1.SetWindowText(svc.cChannelID);
		SetDlgItemInt(IDC_EDIT_SIP_LEVEL1, svc.iLevel);
		SetDlgItemInt(IDC_EDIT_SIP_PTZTIME, svc.iPtzTime);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
	else if (iRet1 < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}

	TSipAlarmChannel sac = {0};
	sac.iChannelNo = m_cboAlarmNo.GetCurSel();
	iCmd = SIP_CMD_GET_ALARMCHANNEL;
	int iRet2 = NetClient_GetChannelSipConfig(m_iLogonID, sac.iChannelNo, SIP_CMD_GET_ALARMCHANNEL, &sac, sizeof(sac));
	if (iRet2 == 0)
	{
		m_edtSipChannelID2.SetWindowText(sac.cChannelID);
		SetDlgItemInt(IDC_EDIT_SIP_LEVEL2, sac.iLevel);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
	else if (iRet2 < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
}

void CLS_SipPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_SIP_VIDEOCHANNEL, IDS_CONFIG_SIP_VIDEOCHANNEL);
	SetDlgItemTextEx(IDC_STATIC_SIP_CHANNELID1, IDS_CONFIG_SIP_CHANNELID1);
	SetDlgItemTextEx(IDC_STATIC_SIP_LEVEL, IDS_CONFIG_SIP_LEVEL1);
	SetDlgItemTextEx(IDC_STATIC_SIP_PTZTIME, IDS_CONFIG_SIP_PTZTIME);
	SetDlgItemTextEx(IDC_BUTTON_SIP_VIDEOCHANNELSET, IDS_CONFIG_SIP_VIDEOSET);
	SetDlgItemTextEx(IDC_STATIC_SIP_ALARMCHANNEL, IDS_CONFIG_SIP_ALARMCHANNEL);
	SetDlgItemTextEx(IDC_STATIC_SIP_CHANNELID2, IDS_CONFIG_SIP_CHANNELID2);
	SetDlgItemTextEx(IDC_STATIC_SIP_LEVEL2, IDS_CONFIG_SIP_LEVEL2);
	SetDlgItemTextEx(IDC_BUTTON_SIP_ALARMCHANNELSET, IDS_CONFIG_SIP_ALARMSET);
	SetDlgItemTextEx(IDC_STATIC_ALARM, IDS_CONFIG_ALARM_NO);
	SetDlgItemTextEx(IDC_BTN_TEST, IDS_LOG_TEST);
}
void CLS_SipPage::OnCbnSelchangeComboAlarm()
{
	// TODO: Add your control notification handler code here
	TSipAlarmChannel sac = {0};
	sac.iChannelNo = m_cboAlarmNo.GetCurSel();
	int iCmd = SIP_CMD_GET_ALARMCHANNEL;
	int iRet2 = NetClient_GetChannelSipConfig(m_iLogonID, sac.iChannelNo, SIP_CMD_GET_ALARMCHANNEL, &sac, sizeof(sac));
	if (iRet2 == 0)
	{
		m_edtSipChannelID2.SetWindowText(sac.cChannelID);
		SetDlgItemInt(IDC_EDIT_SIP_LEVEL2, sac.iLevel);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
	else if (iRet2 < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetChannelSipConfig ID(%d)ChannelNum(%d)", m_iLogonID, m_iChannelNum);
	}
}

void CLS_SipPage::OnBnClickedBtnTest()
{
	// TODO: Add your control notification handler code here
	
	int iCommand = NET_CLIENT_BARCODE;
	int iChannelNum = 0;
	int iTmpBufSize = sizeof(char); 
	CString cTmpBarCode;

	GetDlgItemText(IDC_EDT_TEST, cTmpBarCode);

	int iRet = NetClient_SetDevConfig(m_iLogonID, iCommand, iChannelNum, (void*)(LPSTR)(LPCTSTR)cTmpBarCode, iTmpBufSize);
	if(0 != iRet)
	{
		return;
	}
}
