// AlarmPage.cpp : implementation file
//

#include "stdafx.h"
#include "AlarmPage.h"


// CLS_AlarmPage dialog

IMPLEMENT_DYNAMIC(CLS_AlarmPage, CDialog)

CLS_AlarmPage::CLS_AlarmPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AlarmPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_AlarmPage::~CLS_AlarmPage()
{
}

void CLS_AlarmPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ALARMSERVERIP, m_edtAlarmServerIp);
	DDX_Control(pDX, IDC_EDIT_ALARMSERVERPORT, m_edtAlarmServerPort);
	DDX_Control(pDX, IDC_BUTTON_ALARMSERVER, m_btnAlarmServerIp);
	DDX_Control(pDX, IDC_EDIT_COMSERVERIP, m_edtComServerIp);
	DDX_Control(pDX, IDC_EDIT_COMSERVERPORT, m_edtComServerPort);
	DDX_Control(pDX, IDC_BUTTON_COMSERVER, m_btnComServer);
	DDX_Control(pDX, IDC_SLIDER_MOTIONDETECTTHRESHOLD, m_sldMotionDetectThreshold);
	DDX_Control(pDX, IDC_BUTTON_MOTIONDETECTTHRESHOLD, m_btnMotionDetectThreshold);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_stxtProgress);
	DDX_Control(pDX, IDC_EDIT_CPU, m_edtCpu);
	DDX_Control(pDX, IDC_EDIT_MEM, m_edtMem);
	DDX_Control(pDX, IDC_BUTTON_THRESHOLD, m_btnThreshold);
	DDX_Control(pDX, IDC_SLIDER_AUDIOLOSESENSITIVITY, m_sldAudioLoseSensitivity);
	DDX_Control(pDX, IDC_CBO_LINK_TYPE, m_cboAlarmLinkType);
}


BEGIN_MESSAGE_MAP(CLS_AlarmPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_ALARMSERVER, &CLS_AlarmPage::OnBnClickedButtonAlarmserver)
	ON_BN_CLICKED(IDC_BUTTON_COMSERVER, &CLS_AlarmPage::OnBnClickedButtonComserver)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MOTIONDETECTTHRESHOLD, &CLS_AlarmPage::OnNMCustomdrawSliderMotiondetectthreshold)
	ON_BN_CLICKED(IDC_BUTTON_MOTIONDETECTTHRESHOLD, &CLS_AlarmPage::OnBnClickedButtonMotiondetectthreshold)
	ON_BN_CLICKED(IDC_BUTTON_THRESHOLD, &CLS_AlarmPage::OnBnClickedButtonThreshold)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOLOSESENSITIVITY, &CLS_AlarmPage::OnBnClickedButtonAudiolosesensitivity)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_AUDIOLOSESENSITIVITY, &CLS_AlarmPage::OnNMCustomdrawSliderAudiolosesensitivity)
	ON_BN_CLICKED(IDC_BTN_PRECEDE_DELAY_SNAP_SET, &CLS_AlarmPage::OnBnClickedBtnPrecedeDelaySnapSet)
	ON_BN_CLICKED(IDC_BTN_ALARM_LINK_INTERVAL_SET, &CLS_AlarmPage::OnBnClickedBtnAlarmLinkIntervalSet)
END_MESSAGE_MAP()


// CLS_AlarmPage message handlers
BOOL CLS_AlarmPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_sldMotionDetectThreshold.SetRange(0, 255, TRUE);
	m_sldMotionDetectThreshold.SetPos(0);
	m_sldMotionDetectThreshold.SetTicFreq(5);

	m_sldAudioLoseSensitivity.SetRange(0, 100, TRUE);
	m_sldAudioLoseSensitivity.SetPos(0);
	m_sldAudioLoseSensitivity.SetTicFreq(5);
	
	UI_UpdateDialog();

	return TRUE;
}

void CLS_AlarmPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

	UI_UpdateServer();
	UI_UpdateThreshold();
	UI_UpdateAlarmTrigger();
	UI_UpdatePrecedeDelaySnap();
	UI_UpdateAlarmLinkInterval();
}

void CLS_AlarmPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_AlarmPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ALARMSERVERIP,IDS_CONFIG_ALARM_ALARMSERVERIP);
	SetDlgItemTextEx(IDC_BUTTON_ALARMSERVER,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_COMSERVERIP,IDS_CONFIG_ALARM_COMSERVERIP);
	SetDlgItemTextEx(IDC_BUTTON_COMSERVER,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_MOTIONDETECTTHRESHOLD,IDS_CONFIG_ALARM_MOTIONDETECTTHRESHOLD);
	SetDlgItemTextEx(IDC_BUTTON_MOTIONDETECTTHRESHOLD,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_THRESHOLD,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CPUMEM,IDS_CONFIG_ALARM_CPUMEM);
	SetDlgItemTextEx(IDC_STATIC_ALARMTRIGGERPARAM,IDS_CONFIG_ALARM_TRIGGERPARAM);
	SetDlgItemTextEx(IDC_STATIC_AUDIOLOSESENSITIVITY,IDS_CONFIG_ALARM_AUDIOLOSESENSITIVITY);
	SetDlgItemTextEx(IDC_BUTTON_AUDIOLOSESENSITIVITY,IDS_SET);
	SetDlgItemTextEx(IDC_GPO_PRECEDE_DELAY_SNAP,IDS_PRECEDE_DELAY_SNAP);
	SetDlgItemTextEx(IDC_STC_PRECEDE_NUM,IDS_PRECEDE_PIC_NUM);
	SetDlgItemTextEx(IDC_STC_DELAY_NUM,IDS_DELAY_PIC_NUM);
	SetDlgItemTextEx(IDC_BTN_PRECEDE_DELAY_SNAP_SET,IDS_SET);
	SetDlgItemTextEx(IDC_GPO_ALARM_LINK_INTERVAL,IDS_ALARM_LINK_INTERVAL);
	SetDlgItemTextEx(IDC_STC_LINK_TYPE,IDS_ALARM_LINK_INTERVAL_LINK_TYPE);
	SetDlgItemTextEx(IDC_STC_INTERVAL_TIME,IDS_ALARM_INTERVAL_TIME);
	SetDlgItemTextEx(IDC_BTN_ALARM_LINK_INTERVAL_SET,IDS_SET);

	int iTempSel = m_cboAlarmLinkType.GetCurSel();
	iTempSel = iTempSel >= 0 ? iTempSel : 0;
	m_cboAlarmLinkType.ResetContent();
	m_cboAlarmLinkType.SetItemData(m_cboAlarmLinkType.AddString(GetTextEx(IDS_CONFIG_DNVR_LINKSNAP)), 1);
	m_cboAlarmLinkType.SetItemData(m_cboAlarmLinkType.AddString(GetTextEx(IDS_CFG_3G_DVR_FILTER_ALL)), ALARM_LINK_INTERVAL_ALL_TYPE);
	if (m_cboAlarmLinkType.GetCount() > iTempSel)
	{
		m_cboAlarmLinkType.SetCurSel(iTempSel);
	}
	else
	{
		m_cboAlarmLinkType.SetCurSel(0);
	}
	
}

BOOL CLS_AlarmPage::UI_UpdateServer()
{
	if (m_iLogonID < 0)
		return FALSE;

	char cAlarmServerIP[32] = {0};
	int iServerPort;
	int iRet = NetClient_GetAlarmServer(m_iLogonID,cAlarmServerIP,&iServerPort);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetAlarmServer (%d,%s,%d)",m_iLogonID,cAlarmServerIP,iServerPort);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmServer (%d,%s,%d)",m_iLogonID,cAlarmServerIP,iServerPort);
	}
	SetDlgItemText(IDC_EDIT_ALARMSERVERIP, cAlarmServerIP);
	SetDlgItemInt(IDC_EDIT_ALARMSERVERPORT, iServerPort);

	char cComServerIP[32] = {0};
	int iComServerPort;
	iRet = NetClient_GetComServer(m_iLogonID,cComServerIP,&iComServerPort);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetComServer (%d,%s,%d)",m_iLogonID,cComServerIP,iComServerPort);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetComServer (%d,%s,%d)",m_iLogonID,cComServerIP,iComServerPort);
	}
	SetDlgItemText(IDC_EDIT_COMSERVERIP, cComServerIP);
	SetDlgItemInt(IDC_EDIT_COMSERVERPORT, iComServerPort);
	return TRUE;
}

void CLS_AlarmPage::OnBnClickedButtonAlarmserver()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	char cAlarmServerIP[32] = {0};
	int iServerPort;
	GetDlgItemText(IDC_EDIT_ALARMSERVERIP, cAlarmServerIP, 16);
	iServerPort = GetDlgItemInt(IDC_EDIT_ALARMSERVERPORT);
	if (iServerPort == -1)
	{
		MessageBox(GetTextEx(IDS_CONFIG_ALARM_MESSAGE),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
		return;
	}
	int iRet = NetClient_SetAlarmServer(m_iLogonID, cAlarmServerIP, iServerPort);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmServer (%d,%s,%d)",m_iLogonID,cAlarmServerIP,iServerPort);
	} 
	else
	{
		MessageBox(GetTextEx(IDS_CONFIG_ALARM_MESSAGE1),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmServer (%d,%s,%d)",m_iLogonID,cAlarmServerIP,iServerPort);
	}
}

void CLS_AlarmPage::OnBnClickedButtonComserver()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	char cComServerIP[32] = {0};
	int iComServerPort;
	GetDlgItemText(IDC_EDIT_COMSERVERIP, cComServerIP, 16);
	iComServerPort = GetDlgItemInt(IDC_EDIT_COMSERVERPORT);
	if (iComServerPort == -1)
	{
		MessageBox(GetTextEx(IDS_CONFIG_ALARM_MESSAGE),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
		return;
	}
	int iRet = NetClient_SetComServer(m_iLogonID, cComServerIP, iComServerPort);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetComServer (%d,%s,%d)",m_iLogonID,cComServerIP,iComServerPort);
	} 
	else
	{
		MessageBox(GetTextEx(IDS_CONFIG_ALARM_MESSAGE1),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetComServer (%d,%s,%d)",m_iLogonID,cComServerIP,iComServerPort);
	}
}

void CLS_AlarmPage::OnNMCustomdrawSliderMotiondetectthreshold(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iThreshold = m_sldMotionDetectThreshold.GetPos();
	SetDlgItemInt(IDC_STATIC_PROGRESS, iThreshold);

	*pResult = 0;
}

void CLS_AlarmPage::OnBnClickedButtonMotiondetectthreshold()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iThreshold = m_sldMotionDetectThreshold.GetPos();
	int iRet = NetClient_SetThreshold(m_iLogonID, m_iChannelNo, iThreshold);
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetThreshold(%d,%d,%d)", m_iLogonID,m_iChannelNo,iThreshold);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetThreshold(%d,%d,%d)", m_iLogonID,m_iChannelNo,iThreshold);
	}
}

BOOL CLS_AlarmPage::UI_UpdateThreshold()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iMotionDetectThreshold;
	int iRet = 	NetClient_GetThreshold(m_iLogonID,m_iChannelNo,&iMotionDetectThreshold);
	if (0 == iRet)
	{
		m_sldMotionDetectThreshold.SetPos(iMotionDetectThreshold);
		SetDlgItemInt(IDC_STATIC_PROGRESS, iMotionDetectThreshold);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetThreshold (%d,%d,%d)",m_iLogonID,m_iChannelNo,iMotionDetectThreshold);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetThreshold (%d,%d,%d)",m_iLogonID,m_iChannelNo,iMotionDetectThreshold);
	}
	int iCPUThreshold = 0;
	int iMEMThreshold = 0;
	iRet = NetClient_GetCPUMEMAlarmThreshold(m_iLogonID, &iCPUThreshold, &iMEMThreshold);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_CPU, iCPUThreshold);
		SetDlgItemInt(IDC_EDIT_MEM, iMEMThreshold);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCPUMEMAlarmThreshold (%d,%d,%d)",m_iLogonID,iCPUThreshold,iMEMThreshold);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCPUMEMAlarmThreshold (%d,%d,%d)",m_iLogonID,iCPUThreshold,iMEMThreshold);
	}
	return TRUE;
}



void CLS_AlarmPage::OnBnClickedButtonThreshold()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCPUThreshold = GetDlgItemInt(IDC_EDIT_CPU);
	int iMEMThreshold = GetDlgItemInt(IDC_EDIT_MEM);
	int iRet = NetClient_SetCPUMEMAlarmThreshold(m_iLogonID,iCPUThreshold,iMEMThreshold);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCPUMEMAlarmThreshold (%d,%d,%d)",m_iLogonID,iCPUThreshold,iMEMThreshold);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCPUMEMAlarmThreshold (%d,%d,%d)",m_iLogonID,iCPUThreshold,iMEMThreshold);
	}
}

void CLS_AlarmPage::OnBnClickedButtonAudiolosesensitivity()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TAlarmTriggerParam triParam = {0};
	triParam.iBuffSize = sizeof(triParam);
	triParam.iType = ALARM_TYPE_AUDIOLOST;
	triParam.iID = ATPI_AUDIO_LOST;
	triParam.iValue = m_sldAudioLoseSensitivity.GetPos();
	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_AUDIOLOST, CMD_SET_ALARMTRIGGER, &triParam);

	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig (%d,%d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig (%d,%d)",m_iLogonID,m_iChannelNo);
	}

}


void CLS_AlarmPage::OnNMCustomdrawSliderAudiolosesensitivity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	SetDlgItemInt(IDC_STATIC_AUDIOLOSESENSITIVITYNUM, m_sldAudioLoseSensitivity.GetPos());

	*pResult = 0;
}

BOOL CLS_AlarmPage::UI_UpdateAlarmTrigger()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iMotionDetectThreshold;
	int iRet = 	NetClient_GetThreshold(m_iLogonID,m_iChannelNo,&iMotionDetectThreshold);
	if (0 == iRet)
	{
		m_sldMotionDetectThreshold.SetPos(iMotionDetectThreshold);
		SetDlgItemInt(IDC_STATIC_PROGRESS, iMotionDetectThreshold);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetThreshold (%d,%d,%d)",m_iLogonID,m_iChannelNo,iMotionDetectThreshold);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetThreshold (%d,%d,%d)",m_iLogonID,m_iChannelNo,iMotionDetectThreshold);
	}
	int iCPUThreshold = 0;
	int iMEMThreshold = 0;
	iRet = NetClient_GetCPUMEMAlarmThreshold(m_iLogonID, &iCPUThreshold, &iMEMThreshold);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_CPU, iCPUThreshold);
		SetDlgItemInt(IDC_EDIT_MEM, iMEMThreshold);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCPUMEMAlarmThreshold (%d,%d,%d)",m_iLogonID,iCPUThreshold,iMEMThreshold);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCPUMEMAlarmThreshold (%d,%d,%d)",m_iLogonID,iCPUThreshold,iMEMThreshold);
	}
	
	
	TAlarmTriggerParam triParam = {0};
	triParam.iBuffSize = sizeof(triParam);
	triParam.iType = ALARM_TYPE_AUDIOLOST;
	triParam.iID = ATPI_AUDIO_LOST;
	iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_AUDIOLOST, CMD_GET_ALARMTRIGGER, &triParam);
	if(0 == iRet)
	{
		m_sldAudioLoseSensitivity.SetPos(triParam.iValue);
	}
	
	return TRUE;

}

//ÉèÖÃÔ¤ÀÀ×¥ÅÄºÍÑÓ³Ù×¥ÅÄ
void CLS_AlarmPage::OnBnClickedBtnPrecedeDelaySnapSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	if (m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid ChannelNo(%d)",m_iChannelNo);
		return;
	}

	int iPrecedePicNum = GetDlgItemInt(IDC_EDT_PRECEDE_NUM);
	if (iPrecedePicNum < 0 || iPrecedePicNum > 4)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage Precede Pic Num(%d)",iPrecedePicNum);
		return;
	}

	int iDelayPicNum = GetDlgItemInt(IDC_EDT_DELAY_NUM);
	if (iDelayPicNum < 0 || iDelayPicNum > 4)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage Delay Pic Num(%d)",iDelayPicNum);
		return;
	}

	PrecedeDelaySnap tPrecedeDelaySnap = {0};
	tPrecedeDelaySnap.iSize = sizeof(PrecedeDelaySnap);
	tPrecedeDelaySnap.iDelayNum = iDelayPicNum;
	tPrecedeDelaySnap.iPrecedeNum = iPrecedePicNum;

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_PRECEDE_DELAY_SNAP, m_iChannelNo, (void*)&tPrecedeDelaySnap, sizeof(PrecedeDelaySnap));
	
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig PrecedeDelaySnapSet(%d,%d)",m_iLogonID,m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig PrecedeDelaySnapSet(%d,%d)",m_iLogonID,m_iChannelNo);
	}

	return;
}

BOOL CLS_AlarmPage::UI_UpdatePrecedeDelaySnap()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return FALSE;
	}

	PrecedeDelaySnap tPrecedeDelaySnap = {0};
	tPrecedeDelaySnap.iSize = sizeof(PrecedeDelaySnap);
	int iByteReturn = 0;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_PRECEDE_DELAY_SNAP, m_iChannelNo, (void*)&tPrecedeDelaySnap, sizeof(PrecedeDelaySnap), &iByteReturn);

	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig PrecedeDelaySnapGet(%d,%d)",m_iLogonID,m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig PrecedeDelaySnapGet(%d,%d)",m_iLogonID,m_iChannelNo);
		return FALSE;
	}

	SetDlgItemInt(IDC_EDT_PRECEDE_NUM, tPrecedeDelaySnap.iPrecedeNum);
	SetDlgItemInt(IDC_EDT_DELAY_NUM, tPrecedeDelaySnap.iDelayNum);

	return TRUE;
}

void CLS_AlarmPage::OnBnClickedBtnAlarmLinkIntervalSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	if (m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid ChannelNo(%d)",m_iChannelNo);
		return;
	}

	int iIntervalTime = GetDlgItemInt(IDC_EDT_INTERVAL_TIME);
	if (iIntervalTime < 0 || iIntervalTime > 300)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage Interval Time(%d)",iIntervalTime);
		return;
	}

	int iAlarmLinkType = (int)m_cboAlarmLinkType.GetItemData(m_cboAlarmLinkType.GetCurSel());

	AlarmLinkInterVal  tAlarmLinkInterval = {0};
	tAlarmLinkInterval.iSize = sizeof(AlarmLinkInterVal);
	tAlarmLinkInterval.iLinkType = iAlarmLinkType;
	tAlarmLinkInterval.iInterval = iIntervalTime;

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_ALARM_LINK_INTERVAL, m_iChannelNo, (void*)&tAlarmLinkInterval, sizeof(AlarmLinkInterVal));

	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig AlarmLinkIntervalSet(%d,%d)",m_iLogonID,m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig AlarmLinkIntervalSet(%d,%d)",m_iLogonID,m_iChannelNo);
	}

	return;
}

BOOL CLS_AlarmPage::UI_UpdateAlarmLinkInterval()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return FALSE;
	}

	int iAlarmLinkType = (int)m_cboAlarmLinkType.GetItemData(m_cboAlarmLinkType.GetCurSel());

	if (ALARM_LINK_INTERVAL_ALL_TYPE == iAlarmLinkType)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage Link Type Get Param(%d)",iAlarmLinkType);
		return FALSE;
	}

	AlarmLinkInterVal tAlarmLinkInterval = {0};
	tAlarmLinkInterval.iSize = sizeof(AlarmLinkInterVal);
	tAlarmLinkInterval.iLinkType = iAlarmLinkType;
	int iByteReturn = 0;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ALARM_LINK_INTERVAL, m_iChannelNo, (void*)&tAlarmLinkInterval, sizeof(AlarmLinkInterVal), &iByteReturn);

	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig AlarmLinkIntervalGet(%d,%d)",m_iLogonID,m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig AlarmLinkIntervalGet(%d,%d)",m_iLogonID,m_iChannelNo);
		return FALSE;
	}

	SetDlgItemInt(IDC_EDT_INTERVAL_TIME, tAlarmLinkInterval.iInterval);
	return TRUE;
}
