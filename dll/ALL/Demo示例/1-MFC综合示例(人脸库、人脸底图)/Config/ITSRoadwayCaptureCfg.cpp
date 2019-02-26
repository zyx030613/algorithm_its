#include "stdafx.h"
#include "NetClientDemo.h"
#include "ITSRoadwayCaptureCfg.h"

#define MIN_ILLEAGLTYPE_CONTROL_ID		IDC_CHK_ILLEGAL_TYPE0
#define MAX_ILLEAGLTYPE_CONTROL_ID		IDC_CHK_ILLEGAL_TYPE20
#define LINK_CAP_TYPE_TIME				0
#define LINK_CAP_TYPE_CAR_TYPE			1
#define BIT_TIME_STARTHOUR				24
#define VALUE_TIME_STARTHOUR			0xff000000
#define BIT_TIME_STARTMIN				16
#define VALUE_TIME_STARTMIN				0x00ff0000
#define BIT_TIME_ENDHOUR				8
#define VALUE_TIME_ENDHOUR				0x0000ff00
#define VALUE_TIME_ENDMIN				0x000000ff
#define VALUE_TIME_TRUE					0xFF

IMPLEMENT_DYNAMIC(CLS_DLG_ITSRoadwayCaptureCfg, CDialog)

CLS_DLG_ITSRoadwayCaptureCfg::CLS_DLG_ITSRoadwayCaptureCfg(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DLG_ITSRoadwayCaptureCfg::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_DLG_ITSRoadwayCaptureCfg::~CLS_DLG_ITSRoadwayCaptureCfg()
{
}

void CLS_DLG_ITSRoadwayCaptureCfg::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	for (int i = 0; i < MAX_ILLEGAL_TYPE; ++i)
	{
		DDX_Control(pDX, (MIN_ILLEAGLTYPE_CONTROL_ID + i), m_chkIllegalType[i]);
	}
	DDX_Control(pDX, IDC_CBO_ROADWANY_ID, m_cboRoadwayId);
	DDX_Control(pDX, IDC_CBO_SCENE_ID, m_cboSceneId);
	DDX_Control(pDX, IDC_CBO_LINK_CAP_TYPE, m_cboLinkCapType);
	DDX_Control(pDX, IDC_CBO_TIMERANGE_INDEX, m_cboTimeRangeIndex);
	DDX_Control(pDX, IDC_CBO_CAR_TYPE, m_cboCarType);
	DDX_Control(pDX, IDC_TIME_START_TIME, m_timeStartTime);
	DDX_Control(pDX, IDC_TIME_END_TIME, m_timeEndTime);
}


BEGIN_MESSAGE_MAP(CLS_DLG_ITSRoadwayCaptureCfg, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_CBO_LINK_CAP_TYPE, &CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboLinkCapType)
	ON_CBN_SELCHANGE(IDC_CBO_ROADWANY_ID, &CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboRoadwanyId)
	ON_CBN_SELCHANGE(IDC_CBO_SCENE_ID, &CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboSceneId)
	ON_CBN_SELCHANGE(IDC_CBO_TIMERANGE_INDEX, &CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboTimerangeIndex)
	ON_CBN_SELCHANGE(IDC_CBO_CAR_TYPE, &CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboCarType)
	ON_BN_CLICKED(IDC_BTN_LANE_CAPTURE_SET, &CLS_DLG_ITSRoadwayCaptureCfg::OnBnClickedBtnLaneCaptureSet)
END_MESSAGE_MAP()

BOOL CLS_DLG_ITSRoadwayCaptureCfg::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	
	MoveWidgetCorrect();
	
	UI_UpdateDialog();
	return TRUE; 
}

void CLS_DLG_ITSRoadwayCaptureCfg::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannel = (_iChannelNo < 0) ? 0 : _iChannelNo;
	UI_UpdateParam();
}

void CLS_DLG_ITSRoadwayCaptureCfg::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DLG_ITSRoadwayCaptureCfg::UI_UpdateDialog()
{
	m_timeStartTime.SetFormat(_T("HH:mm"));
	m_timeEndTime.SetFormat(_T("HH:mm"));

	SetDlgItemTextEx(IDC_STC_ROADWANY_ID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_BTN_LANE_CAPTURE_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STC_SCENE_ID,IDS_CONFIG_COMS_SCENE);
	SetDlgItemTextEx(IDC_STC_LINK_CAP_TYPE,IDS_CAP_LINK_TYPE);
	SetDlgItemTextEx(IDC_STC_TIMERANGE_INDEX,IDS_CONFIG_ITS_TIMERANGE_INDEX);
	SetDlgItemTextEx(IDC_STC_TIME_RANGE,IDS_CONFIG_ITS_TIMERANGE_RANGE);
	SetDlgItemTextEx(IDC_STC_CAR_TYPE,IDS_ITS_CAR_TYPE);
	SetDlgItemTextEx(IDC_GPO_LANE_CAPTURE_SET,IDS_ROADWAY_CAP_CFG);

	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE0,IDS_ITS_BAYONET);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE1,IDS_ITS_REDLIGHT);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE2,IDS_ITS_RETROGRADE);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE3,IDS_ITS_SPEED);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE4,IDS_ITS_FORBID_LEFT);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE5,IDS_ITS_FORBID_RIGHT);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE6,IDS_ITS_PRESS_YELLOW);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE7,IDS_ITS_NON_MOTOR);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE8,IDS_ITS_NOT_GUIDE_DRIVE);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE9,IDS_ITS_FORBID_STRAIGHT);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE10,IDS_ITS_BUS_WAY);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE11,IDS_ITS_PRESS_LINE);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE12,IDS_ITS_WAIT_RED_LIGHT);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE13,IDS_ITS_ILLEGAL_PARK);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE14,IDS_ITS_MIX_CAP_SPEED);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE15, IDS_ITS_BACK);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE16, IDS_ITS_TURN2);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE17,IDS_ITS_RIDE_CAPTURE);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE18,IDS_ITS_MIXED_ENABLE);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE19,IDS_ITS_FASTENSB);
	SetDlgItemTextEx(IDC_CHK_ILLEGAL_TYPE20,IDS_ITS_CALLING);

	int iTempSel = 0;

	iTempSel = m_cboRoadwayId.GetCurSel();
	m_cboRoadwayId.ResetContent();
	for (int i = 0; i <  MAX_ROADWAY_COUNT; ++i)
	{
		m_cboRoadwayId.SetItemData(m_cboRoadwayId.AddString(IntToCString(i)), i);
	}
	iTempSel = (iTempSel < 0 || iTempSel >= m_cboRoadwayId.GetCount()) ? 0 : iTempSel;
	m_cboRoadwayId.SetCurSel(iTempSel);

	iTempSel = m_cboSceneId.GetCurSel();
	m_cboSceneId.ResetContent();
	for (int i = 0; i <  MAX_SCENE_NUM; ++i)
	{
		m_cboSceneId.SetItemData(m_cboSceneId.AddString(IntToCString(i + 1)), i);
	}
	iTempSel = (iTempSel < 0 || iTempSel >= m_cboSceneId.GetCount()) ? 0 : iTempSel;
	m_cboSceneId.SetCurSel(iTempSel);
	
	iTempSel = m_cboTimeRangeIndex.GetCurSel();
	m_cboTimeRangeIndex.ResetContent();
	for (int i = 0; i <  MAX_ITS_TIMERANGE; ++i)
	{
		m_cboTimeRangeIndex.SetItemData(m_cboTimeRangeIndex.AddString(IntToCString(i + 1)), i);
	}
	iTempSel = (iTempSel < 0 || iTempSel >= m_cboTimeRangeIndex.GetCount()) ? 0 : iTempSel;
	m_cboTimeRangeIndex.SetCurSel(iTempSel);

	iTempSel = m_cboLinkCapType.GetCurSel();
	m_cboLinkCapType.ResetContent();
	m_cboLinkCapType.SetItemData(m_cboLinkCapType.AddString(GetTextEx(IDS_CONFIG_ITS_TIMERANGE_RANGE)), LINK_CAP_TYPE_TIME);
	m_cboLinkCapType.SetItemData(m_cboLinkCapType.AddString(GetTextEx(IDS_ITS_CAR_TYPE)), LINK_CAP_TYPE_CAR_TYPE);
	iTempSel = (iTempSel < 0 || iTempSel >= m_cboLinkCapType.GetCount()) ? 0 : iTempSel;
	m_cboLinkCapType.SetCurSel(iTempSel);

	int iData = 0;
	iTempSel = m_cboCarType.GetCurSel();
	m_cboCarType.ResetContent();
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_UNKNOW_CAR_TYPE)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_MUNI_COACH)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_SAMLL_CAR)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_TRUCK)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_MICROBUS)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_BIG_TRUCK)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_SMALL_TRUCK)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_NON_MOTOR_VEHICLE)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_PEDESTRIAN)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_SUV)), iData++);
	m_cboCarType.SetItemData(m_cboCarType.AddString(GetTextEx(IDS_MEDIUM_BUS)), iData++);
	iTempSel = (iTempSel < 0 || iTempSel >= m_cboCarType.GetCount()) ? 0 : iTempSel;
	m_cboCarType.SetCurSel(iTempSel);

	OnCbnSelchangeCboLinkCapType();
}

void CLS_DLG_ITSRoadwayCaptureCfg::ShowLinkTimeRange(BOOL _blShow)
{
	GetDlgItem(IDC_CBO_TIMERANGE_INDEX)->ShowWindow(_blShow);
	GetDlgItem(IDC_STC_TIMERANGE_INDEX)->ShowWindow(_blShow);
	GetDlgItem(IDC_STC_TIME_RANGE)->ShowWindow(_blShow);
	GetDlgItem(IDC_TIME_START_TIME)->ShowWindow(_blShow);
	GetDlgItem(IDC_TIME_END_TIME)->ShowWindow(_blShow);
	GetDlgItem(IDC_STC_UNUSEED)->ShowWindow(_blShow);
}

void CLS_DLG_ITSRoadwayCaptureCfg::ShowLinkCarType(BOOL _blShow)
{
	GetDlgItem(IDC_STC_CAR_TYPE)->ShowWindow(_blShow);
	GetDlgItem(IDC_CBO_CAR_TYPE)->ShowWindow(_blShow);
}

void CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboLinkCapType()
{
	int iSel = (int)m_cboLinkCapType.GetItemData(m_cboLinkCapType.GetCurSel());
	BOOL blShowLink = (LINK_CAP_TYPE_TIME == iSel) ? TRUE : FALSE;
	ShowLinkTimeRange(blShowLink);
	ShowLinkCarType(!blShowLink);
	UI_UpdateParam();
}

void CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboRoadwanyId()
{
	UI_UpdateParam();
}

void CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboSceneId()
{
	UI_UpdateParam();
}

void CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboTimerangeIndex()
{
	UI_UpdateRelateTimeRangePara();
}

void CLS_DLG_ITSRoadwayCaptureCfg::OnCbnSelchangeCboCarType()
{
	UI_UpdateRelateCarTypePara();
}

void CLS_DLG_ITSRoadwayCaptureCfg::MoveWidgetCorrect()
{
	RECT rcTempRect = {0};
	m_cboTimeRangeIndex.GetWindowRect(&rcTempRect);
	ScreenToClient(&rcTempRect);
	m_cboCarType.MoveWindow(&rcTempRect);

	GetDlgItem(IDC_STC_TIMERANGE_INDEX)->GetWindowRect(&rcTempRect);
	ScreenToClient(&rcTempRect);
	GetDlgItem(IDC_STC_CAR_TYPE)->MoveWindow(&rcTempRect);
}

int CLS_DLG_ITSRoadwayCaptureCfg::UI_UpdateRelateTimeRangePara()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return RET_FAILED;
	}

	int iRet = RET_FAILED;

	ITSChnlCapSet tITSChnlCapSet = {0};
	tITSChnlCapSet.iSize = sizeof(ITSChnlCapSet);
	tITSChnlCapSet.iRoadwayID = (int)m_cboRoadwayId.GetItemData(m_cboRoadwayId.GetCurSel());
	tITSChnlCapSet.iSceneID = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());
	tITSChnlCapSet.iIndex = (int)m_cboTimeRangeIndex.GetItemData(m_cboTimeRangeIndex.GetCurSel());

	iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CHNLCAPSET, m_iChannel, &tITSChnlCapSet, sizeof(ITSChnlCapSet));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[CHNLCAPSET](%d, %d)", m_iLogonID, m_iChannel);
		iRet = RET_FAILED;
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[CHNLCAPSET](%d, %d)", m_iLogonID, m_iChannel);
	UI_UpdateTimeWidget(tITSChnlCapSet.iTimeRange);
	UI_UpdateCapTypeWidget(tITSChnlCapSet.iCapType);
	iRet = RET_SUCCESS;
	
EXIT_FUNC:
	return iRet;
}

int CLS_DLG_ITSRoadwayCaptureCfg::SetCapRelateTimeRange()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return RET_FAILED;
	}

	int iRet = RET_FAILED;

	ITSChnlCapSet tITSChnlCapSet = {0};
	tITSChnlCapSet.iSize = sizeof(ITSChnlCapSet);
	tITSChnlCapSet.iRoadwayID = (int)m_cboRoadwayId.GetItemData(m_cboRoadwayId.GetCurSel());
	tITSChnlCapSet.iSceneID = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());
	tITSChnlCapSet.iIndex = (int)m_cboTimeRangeIndex.GetItemData(m_cboTimeRangeIndex.GetCurSel());
	tITSChnlCapSet.iTimeRange = GetTimeWidgetValue();
	tITSChnlCapSet.iCapType = GetCapTypeWidgetValue();

	iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CHNLCAPSET, m_iChannel, &tITSChnlCapSet, sizeof(ITSChnlCapSet));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[CHNLCAPSET](%d, %d)", m_iLogonID, m_iChannel);
		iRet = RET_FAILED;
		goto EXIT_FUNC;
	}
	AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[CHNLCAPSET](%d, %d)", m_iLogonID, m_iChannel);
	iRet = RET_SUCCESS;

EXIT_FUNC:
	return iRet;
}

int CLS_DLG_ITSRoadwayCaptureCfg::UI_UpdateRelateCarTypePara()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return RET_FAILED;
	}

	int iRet = RET_FAILED;

	ITSChnlCarCapType tITSChnlCarCapType = {0};
	tITSChnlCarCapType.iSize = sizeof(ITSChnlCapSet);
	tITSChnlCarCapType.iRoadwayID = (int)m_cboRoadwayId.GetItemData(m_cboRoadwayId.GetCurSel());
	tITSChnlCarCapType.iSceneID = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());
	tITSChnlCarCapType.iCarType = (int)m_cboCarType.GetItemData(m_cboCarType.GetCurSel());

	iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CHNLCARCAPTPYE, m_iChannel, &tITSChnlCarCapType, sizeof(ITSChnlCapSet));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[CHNLCARCAPTPY](%d, %d)", m_iLogonID, m_iChannel);
		iRet = RET_FAILED;
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[CHNLCARCAPTPY](%d, %d)", m_iLogonID, m_iChannel);
	UI_UpdateCapTypeWidget(tITSChnlCarCapType.iCapType);
	iRet = RET_SUCCESS;

EXIT_FUNC:
	return iRet;
}


int CLS_DLG_ITSRoadwayCaptureCfg::SetCapRelateCarType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return RET_FAILED;
	}

	int iRet = RET_FAILED;

	ITSChnlCarCapType tITSChnlCarCapType = {0};
	tITSChnlCarCapType.iSize = sizeof(ITSChnlCapSet);
	tITSChnlCarCapType.iRoadwayID = (int)m_cboRoadwayId.GetItemData(m_cboRoadwayId.GetCurSel());
	tITSChnlCarCapType.iSceneID = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());
	tITSChnlCarCapType.iCarType = (int)m_cboCarType.GetItemData(m_cboCarType.GetCurSel());
	tITSChnlCarCapType.iCapType = GetCapTypeWidgetValue();

	iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CHNLCARCAPTPYE, m_iChannel, &tITSChnlCarCapType, sizeof(ITSChnlCapSet));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[CHNLCARCAPTPY](%d, %d)", m_iLogonID, m_iChannel);
		iRet = RET_FAILED;
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[CHNLCARCAPTPY](%d, %d)", m_iLogonID, m_iChannel);
	iRet = RET_SUCCESS;

EXIT_FUNC:
	return iRet;
}

void CLS_DLG_ITSRoadwayCaptureCfg::UI_UpdateTimeWidget(int _iTime)
{
	int iStartHour = (_iTime >> BIT_TIME_STARTHOUR & VALUE_TIME_TRUE);
	int iStartMin = (_iTime >> BIT_TIME_STARTMIN & VALUE_TIME_TRUE);
	int iEndHour = (_iTime >> BIT_TIME_ENDHOUR & VALUE_TIME_TRUE);
	int iEndMin = (_iTime & VALUE_TIME_TRUE);

	CTime timeNow = CTime::GetCurrentTime();
	
	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),iStartHour, iStartMin, 0);
	m_timeStartTime.SetTime(&timeNow);

	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),iEndHour, iEndMin, 0);
	m_timeEndTime.SetTime(&timeNow);
}

int CLS_DLG_ITSRoadwayCaptureCfg::GetTimeWidgetValue()
{
	CTime timeTemp;
	m_timeStartTime.GetTime(timeTemp);
	int iStartHour = timeTemp.GetHour();
	int iStartMin = timeTemp.GetMinute();
	m_timeEndTime.GetTime(timeTemp);
	int iEndHour = timeTemp.GetHour();
	int iEndMin = timeTemp.GetMinute();
	int iTime = ((iStartHour << BIT_TIME_STARTHOUR) & VALUE_TIME_STARTHOUR) |   	//开始小时放在int类型24~31位
	((iStartMin << BIT_TIME_STARTMIN) & VALUE_TIME_STARTMIN) |    					//开始分钟放在int类型16~23位
	((iEndHour << BIT_TIME_ENDHOUR) & VALUE_TIME_ENDHOUR) |      					//结束小时放在int类型8~15位
	(iEndMin & VALUE_TIME_ENDMIN);   

	return iTime;
}

void CLS_DLG_ITSRoadwayCaptureCfg::UI_UpdateCapTypeWidget(int _iIllegalType)
{
	for (int i = 0; i < MAX_ILLEGAL_TYPE; ++i)
	{
		m_chkIllegalType[i].SetCheck(FALSE);
		BOOL blChk = _iIllegalType & (1 << i);
		m_chkIllegalType[i].SetCheck(blChk);
	}
}

int CLS_DLG_ITSRoadwayCaptureCfg::GetCapTypeWidgetValue()
{
	int iIllegalType = 0;

	for (int i = 0; i < MAX_ILLEGAL_TYPE; ++i)
	{
		iIllegalType += ((int)(m_chkIllegalType[i].GetCheck())) << i;
	}

	return iIllegalType;
}

void CLS_DLG_ITSRoadwayCaptureCfg::UI_UpdateParam()
{
	int iLinkType = (int)m_cboLinkCapType.GetItemData(m_cboLinkCapType.GetCurSel());
	if (LINK_CAP_TYPE_TIME == iLinkType)
	{
		UI_UpdateRelateTimeRangePara();
	}
	else if (LINK_CAP_TYPE_CAR_TYPE == iLinkType)
	{
		UI_UpdateRelateCarTypePara();
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_ITSRoadwayCaptureCfg::UI_UpdateParam] Unknown Link Type(%d)", iLinkType);
	}

}


void CLS_DLG_ITSRoadwayCaptureCfg::OnBnClickedBtnLaneCaptureSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iLinkType = (int)m_cboLinkCapType.GetItemData(m_cboLinkCapType.GetCurSel());
	if (LINK_CAP_TYPE_TIME == iLinkType)
	{
		SetCapRelateTimeRange();
	}
	else if (LINK_CAP_TYPE_CAR_TYPE == iLinkType)
	{
		SetCapRelateCarType();
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_ITSRoadwayCaptureCfg::OnBnClickedBtnLaneCaptureSet] Unknown Link Type(%d)", iLinkType);
	}
}
