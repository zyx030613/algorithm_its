// ECOPOtherPage.cpp : implementation file
//

#include "stdafx.h"
#include "ItsSystemParam1.h"


// CLS_ECOPOtherPage dialog

IMPLEMENT_DYNAMIC(CLS_ItsSystemParam1, CDialog)

CLS_ItsSystemParam1::CLS_ItsSystemParam1(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsSystemParam1::IDD, pParent)
{
	m_iLogonID = -1;

}

CLS_ItsSystemParam1::~CLS_ItsSystemParam1()
{
}

void CLS_ItsSystemParam1::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_CHECK_WATERMARK_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_COMBO_SN_TYPE, m_cboSnType);
	DDX_Control(pDX, IDC_EDIT_SN_SN, m_edtSn);
	DDX_Control(pDX, IDC_EDIT_LOCKRET, m_edtLocalRet);
	DDX_Control(pDX, IDC_BUTTON_SN, m_btnSn);
	DDX_Control(pDX, IDC_EDIT_SYSTEM_TYPE, m_edtSystemType);
	DDX_Control(pDX, IDC_BUTTON_SYSTEM, m_btnSystem);
	DDX_Control(pDX, IDC_COMBO_DETECTMODE, m_cboDetectMode);
	DDX_Control(pDX, IDC_BUTTON_DETECTMODE, m_btnDetectMode);
	DDX_Control(pDX, IDC_EDIT_SWITCHTIME, m_edtSwitchTime);
	DDX_Control(pDX, IDC_EDIT_DELAYTIME, m_edtDelayTime);
	DDX_Control(pDX, IDC_BUTTON_SWITCH_DELAY, m_btnSwitchDelay);
	DDX_Control(pDX, IDC_GP_TEST_MODE, m_gpTestMode);
	DDX_Control(pDX, IDC_GP_TIME_SET, m_gpTimeSet);
	DDX_Control(pDX, IDC_GP_DAYNIGHT, m_gpDayNight);
	DDX_Control(pDX, IDC_STC_TIMESEGMENT, m_stcTimeSegment);
	DDX_Control(pDX, IDC_EDT_TIMESEGMENT, m_edtTimeSegment);
	DDX_Control(pDX, IDC_BTN_DAYNIGHT, m_btnSetDayNight);
	DDX_Control(pDX, IDC_STC_DAY_START_TIME, m_stcDayStart);
	DDX_Control(pDX, IDC_EDT_DAY_START, m_edtDayStart);
	DDX_Control(pDX, IDC_STC_NIGHT_START_TIME, m_stcNightStart);
	DDX_Control(pDX, IDC_EDT_NIGHT_START, m_edtNightStart);
	DDX_Control(pDX, IDC_EDT_DAY_START_MIN, m_edtDayStartMin);
	DDX_Control(pDX, IDC_EDT_NIGHT_START_MIN, m_edtNightStartMin);
	DDX_Control(pDX, IDC_STC_DAY_POINT, m_stcDayPoint);
	DDX_Control(pDX, IDC_STC_NIGHT_POINT, m_stcNightPoint);
}


BEGIN_MESSAGE_MAP(CLS_ItsSystemParam1, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ItsSystemParam1::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_CHECK_WATERMARK_ENABLE, &CLS_ItsSystemParam1::OnBnClickedCheckWatermarkEnable)
	ON_BN_CLICKED(IDC_BUTTON_SN, &CLS_ItsSystemParam1::OnBnClickedButtonSn)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM, &CLS_ItsSystemParam1::OnBnClickedButtonSystem)
	ON_BN_CLICKED(IDC_BUTTON_DETECTMODE, &CLS_ItsSystemParam1::OnBnClickedButtonDetectmode)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH_DELAY, &CLS_ItsSystemParam1::OnBnClickedButtonSwitchDelay)
	ON_BN_CLICKED(IDC_BTN_SET_SWITCH_INTERVAL, &CLS_ItsSystemParam1::OnBnClickedBtnSetSwitchInterval)
	ON_BN_CLICKED(IDC_BTN_SET_DAY_AND_NIGHT, &CLS_ItsSystemParam1::OnBnClickedBtnSetDayAndNight)
	ON_CBN_SELCHANGE(IDC_COMBO_SN_TYPE, &CLS_ItsSystemParam1::OnCbnSelchangeComboSnType)
END_MESSAGE_MAP()


// CLS_ECOPOtherPage message handlers
BOOL CLS_ItsSystemParam1::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	m_cboSnType.AddString("0--RECOGNIZE_ARITHMETIC");
	m_cboSnType.AddString("1--PROGRAM");

	m_edtSn.SetLimitText(63);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ItsSystemParam1::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannel = (_iChannelNo < 0) ? 0 : _iChannelNo;

	UI_UpdateOther();
	UI_UpdateDetectmode();
	UI_UpdateSwitchDelay();
	UI_UpdateDayAndNight();
	//UI_UpdateSn();
}

void CLS_ItsSystemParam1::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
	
}

void CLS_ItsSystemParam1::UI_UpdateDialog()
{
	InsertString(m_cboDetectMode,0,IDS_CONFIG_ITS_DETECTMODE0);
	InsertString(m_cboDetectMode,1,IDS_CONFIG_ITS_DETECTMODE1);
	InsertString(m_cboDetectMode,2,IDS_CONFIG_ITS_DETECTMODE2);
	InsertString(m_cboDetectMode,3,IDS_CONFIG_ITS_DETECTMODE3);
	InsertString(m_cboDetectMode,4,IDS_CONFIG_ITS_DETECTMODE4);
	InsertString(m_cboDetectMode,5,IDS_CONFIG_ITS_DETECTMODE5);
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_WATERMARK,IDS_CONFIG_ECOP_WATERMARK);
	SetDlgItemTextEx(IDC_CHECK_WATERMARK_ENABLE,IDS_CONFIG_ECOP_WATERMARK_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_SN,IDS_CONFIG_ECOP_SN);
	SetDlgItemTextEx(IDC_STATIC_SN_TYPE,IDS_CONFIG_ECOP_SN_TYPE);
	SetDlgItemTextEx(IDC_STATIC_SN_SN,IDS_CONFIG_ECOP_SN);
	SetDlgItemTextEx(IDC_STATIC_LOCKRET,IDS_CONFIG_ECOP_LOCALRET);
	SetDlgItemTextEx(IDC_BUTTON_SN,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_SYSTEM,IDS_CONFIG_ECOP_SYSTEM);
	SetDlgItemTextEx(IDC_STATIC_SYSTEM_TYPE,IDS_CONFIG_ECOP_SYSTEM_TYPE);
	SetDlgItemTextEx(IDC_BUTTON_SYSTEM,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DETECTMODE,IDS_CONFIG_ITS_TIMERANGE_DETECTMODE);
	SetDlgItemTextEx(IDC_BUTTON_DETECTMODE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DELAYTIME,IDS_CONFIG_ITS_TIMERANGE_DELAYTIME);
	SetDlgItemTextEx(IDC_STATIC_SWITCHTIME,IDS_CONFIG_ITS_TIMERANGE_SWITCHTIME);
	SetDlgItemTextEx(IDC_BUTTON_SWITCH_DELAY,IDS_SET);
	SetDlgItemTextEx(IDC_GP_TEST_MODE, IDS_ITS_TEST_MODE);
	SetDlgItemTextEx(IDC_GP_TIME_SET, IDS_ITS_TIME_SET);
	SetDlgItemTextEx(IDC_GP_DAYNIGHT,IDS_CONFIG_ITS_DAYNIGHT);
	SetDlgItemTextEx(IDC_STC_TIMESEGMENT,IDS_CONFIG_ITS_TIMESEGMENT);
	SetDlgItemTextEx(IDC_BTN_DAYNIGHT,IDS_SET);
	SetDlgItemTextEx(IDC_GP_DAYNIGHT, IDS_ITS_DAY_NIGHT);
	SetDlgItemTextEx(IDC_STC_DAY_START_TIME, IDS_ITS_DAY_START_TIME);
	SetDlgItemTextEx(IDC_STC_NIGHT_START_TIME, IDS_ITS_NIGHT_START_TIME);
	SetDlgItemTextEx(IDC_STC_SWITCH_INTERVERAL, IDS_ITS_MIX_HAPPEN);
	SetDlgItemTextEx(IDC_BTN_SET_DAY_AND_NIGHT, IDS_SET);
	SetDlgItemTextEx(IDC_STC_DETECTMODE_INTERVAL_TIME, IDS_CONFIG_ECOP_INTERVAL);

	UI_UpdateOther();
	UI_UpdateDetectmode();
	UI_UpdateSwitchDelay();
	UI_UpdateDayAndNight();
	//UI_UpdateSn();
}

BOOL CLS_ItsSystemParam1::UI_UpdateOther()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iChannelID = m_cboRoadwayID.GetCurSel();
	int iWaterMarkEnable = 0;
	int iRet = NetClient_GetWaterMarkEnable(m_iLogonID,iChannelID,&iWaterMarkEnable);
	if (0 == iRet)
	{
		m_chkEnable.SetCheck(iWaterMarkEnable?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetWaterMarkEnable (%d,%d)",m_iLogonID,iWaterMarkEnable);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetWaterMarkEnable (%d,%d)",m_iLogonID,iWaterMarkEnable);
	}
	int iLockRet = 0;
	iRet = NetClient_GetSNReg(m_iLogonID,&iLockRet);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_LOCKRET, iLockRet);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetSNReg (%d,%d)",m_iLogonID,iLockRet);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetSNReg (%d,%d)",m_iLogonID,iLockRet);
	}
	int iSystemType = 0;
	iRet = NetClient_GetSystemType(m_iLogonID,&iSystemType);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_SYSTEM_TYPE, iSystemType);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetSystemType (%d,%d)",m_iLogonID,iSystemType);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetSystemType (%d,%d)",m_iLogonID,iSystemType);
	}

	if (m_iLogonID < 0)
		return FALSE;

	int iTimeSegment = -1;
	iRet = NetClient_GetITSDayNight(m_iLogonID, &iTimeSegment);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_TIMESEGMENT, iTimeSegment);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSDayNight (%d,%d)",m_iLogonID,iTimeSegment);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSDayNight (%d,%d)",m_iLogonID,iTimeSegment);
	}
	return TRUE;
}

void CLS_ItsSystemParam1::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateOther();
	UI_UpdateDetectmode();
	UI_UpdateSwitchDelay();

}

void CLS_ItsSystemParam1::UI_UpdateDetectmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid logon id(%d)", m_iLogonID);
		return;
	}

	if (m_iChannel < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid channel num(%d)", m_iChannel);
		return;
	}

	ItsDetectMode tItsDetectMode = {0};
	tItsDetectMode.iSize = sizeof(ItsDetectMode);
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_DETECTMODE, m_iChannel, &tItsDetectMode, sizeof(ItsDetectMode));
	if (0 == iRet)
	{
		m_cboDetectMode.SetCurSel(tItsDetectMode.iDetectMode);
		SetDlgItemInt(IDC_EDT_DETECTMODE_INTERVAL_TIME, tItsDetectMode.iIntervalTime);
		AddLog(LOG_TYPE_SUCC,"","GetITSDetectMode (%d,%d)", m_iLogonID, tItsDetectMode.iDetectMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","GetITSDetectMode (%d,%d), error(%d)", m_iLogonID, tItsDetectMode.iDetectMode, GetLastError());
	}	
}

void CLS_ItsSystemParam1::UI_UpdateSwitchDelay()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iSwitchTime = 0;
	int iDelayTime = 0;
	int iRet = NetClient_GetITSSwitchTime(m_iLogonID, &iSwitchTime, &iDelayTime);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_SWITCHTIME, iSwitchTime / 60);
		SetDlgItemInt(IDC_EDIT_DELAYTIME, iDelayTime);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSSwitchTime (%d,%d,%d), error(%d)",m_iLogonID,iSwitchTime,iDelayTime,GetLastError());
	}
}

void CLS_ItsSystemParam1::OnBnClickedCheckWatermarkEnable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iChannelID = m_cboRoadwayID.GetCurSel();
	int iEnable = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	int iRet = NetClient_SetWaterMarkEnable(m_iLogonID,iChannelID,iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetWaterMarkEnable (%d,%d)",m_iLogonID,iEnable);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetWaterMarkEnable (%d,%d)",m_iLogonID,iEnable);
	}
}

void CLS_ItsSystemParam1::OnBnClickedButtonSn()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iType = m_cboSnType.GetCurSel();
	char cSN[64] = {0};
	GetDlgItemText(IDC_EDIT_SN_SN, cSN, 63);
	int iRet = NetClient_SetEncryptSN(m_iLogonID,iType,cSN);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetEncryptSN (%d,%s)",m_iLogonID,cSN);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetEncryptSN (%d,%s)",m_iLogonID,cSN);
	}
}

// BOOL CLS_ItsSystemParam1::UI_UpdateSn()
// {
// 	if(m_iLogonID < 0)
// 		return FALSE;
// 
// 	int iType = m_cboSnType.GetCurSel();
// 	//char cSN[64] = {0};
// 	int iLockRct = 0;
// 	int iRet = NetClient_GetSNReg(m_iLogonID,&iLockRct);
// 	if(iRet == 0)
// 	{
// 		SetDlgItemInt(IDC_EDIT_LOCKRET, iLockRct);
// 		AddLog(LOG_TYPE_SUCC,"","NetClient_GetSNReg(%d)", m_iLogonID);
// 	}
// 	else
// 	{
// 		AddLog(LOG_TYPE_SUCC,"","NetClient_GetSNReg(%d),error(%d)", m_iLogonID, GetLastError());
// 		return FALSE;
// 	}
// 	return TRUE;
// }


void CLS_ItsSystemParam1::OnBnClickedButtonSystem()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iType = GetDlgItemInt(IDC_EDIT_SYSTEM_TYPE);
	if(iType == SYSTEM_TYPE_DEBUG || iType == SYSTEM_TYPE_GATE || iType == SYSTEM_TYPE_ECOP)
	{
		int iRet = NetClient_SetSystemType(m_iLogonID,iType);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetSystemType (%d,%d)",m_iLogonID,iType);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetSystemType (%d,%d)",m_iLogonID,iType);
		}
	}
}

void CLS_ItsSystemParam1::OnBnClickedButtonDetectmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid logon id(%d)", m_iLogonID);
		return;
	}

	ItsDetectMode tItsDetectMode = {0};
	tItsDetectMode.iSize = sizeof(ItsDetectMode);
	tItsDetectMode.iDetectMode = m_cboDetectMode.GetCurSel();
	tItsDetectMode.iIntervalTime = GetDlgItemInt(IDC_EDT_DETECTMODE_INTERVAL_TIME);

	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_DETECTMODE, m_iChannel, &tItsDetectMode, sizeof(ItsDetectMode));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","SetITSDetectMode (%d,%d)", m_iLogonID, tItsDetectMode.iDetectMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","SetITSDetectMode (%d,%d), error(%d)",m_iLogonID, tItsDetectMode.iDetectMode, GetLastError());
	}
}

void CLS_ItsSystemParam1::OnBnClickedButtonSwitchDelay()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iSwitchTime = GetDlgItemInt(IDC_EDIT_SWITCHTIME) * 60;
	int iDelayTime = GetDlgItemInt(IDC_EDIT_DELAYTIME);
	int iRet = NetClient_SetITSSwitchTime(m_iLogonID, iSwitchTime, iDelayTime);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSSwitchTime (%d,%d,%d), error(%d)",m_iLogonID,iSwitchTime,iDelayTime, GetLastError());
	}
}

void CLS_ItsSystemParam1::OnBnClickedBtnSetSwitchInterval()
{
	int iSwitchTime = 0;
	int iDelayTime = 0;
	if(m_iLogonID >= 0)
	{
		int iRet1 = NetClient_GetITSSwitchTime(m_iLogonID, &iSwitchTime, &iDelayTime);
		if (0 == iRet1)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
		}
		if(0 == iRet1)
		{
			iSwitchTime = GetDlgItemInt(IDC_EDT_SWITCH_INTERVAL);
			iSwitchTime = max(iSwitchTime, SWITCH_TIME_MIN);
			iSwitchTime = min(iSwitchTime, SWITCH_TIME_MAX);
			int iRet2 = NetClient_SetITSSwitchTime(m_iLogonID, iSwitchTime, iDelayTime);
			if (0 == iRet2)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
			} 
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
			}
		}
	}
}

void CLS_ItsSystemParam1::OnBnClickedBtnSetDayAndNight()
{
	unsigned int InputTime = 0;
	InputTime = min(GetDlgItemInt(IDC_EDT_DAY_START), HOUR_LIMIT);
	InputTime = (InputTime<<8)|min(GetDlgItemInt(IDC_EDT_DAY_START_MIN), MINUTE_LIMIT);
	InputTime = (InputTime<<8)|min(GetDlgItemInt(IDC_EDT_NIGHT_START), HOUR_LIMIT);
	InputTime = (InputTime<<8)|min(GetDlgItemInt(IDC_EDT_NIGHT_START_MIN), MINUTE_LIMIT);
	int iRet = NetClient_SetITSDayNight(m_iLogonID, InputTime);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDayNight (%d,%d)",m_iLogonID,InputTime);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDayNight (%d,%d)",m_iLogonID,InputTime);
	}
}
BOOL CLS_ItsSystemParam1::UI_UpdateDayAndNight()
{
	int uiInputTime = 0;
	int iRet = NetClient_GetITSDayNight(m_iLogonID, &uiInputTime);
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDT_NIGHT_START_MIN,(uiInputTime & 0x00FF));
		SetDlgItemInt(IDC_EDT_NIGHT_START, (uiInputTime >> 8) & 0x00FF);
		SetDlgItemInt(IDC_EDT_DAY_START_MIN, (uiInputTime >> 16) & 0x00FF);
		SetDlgItemInt(IDC_EDT_DAY_START, (uiInputTime >> 24) & 0x00FF);
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}
void CLS_ItsSystemParam1::OnCbnSelchangeComboSnType()
{
	UI_UpdateOther();
}
