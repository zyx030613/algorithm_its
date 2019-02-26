// VCAAlarmSchedulePage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAAlarmSchedulePage.h"


// CLS_VCAAlarmSchedulePage dialog

#define VCA_MAX_RULE_NUM_NEW			10			//增加音视频检测后，规则ID共10个

IMPLEMENT_DYNAMIC(CLS_VCAAlarmSchedulePage, CDialog)
static vca_TVCAParam g_VcaParam = {0};
extern int g_iEventIDS[VCA_EVENT_MAX];
static int g_iEnableIDS[] = {IDS_CONFIG_VCA_DISABLE, IDS_CONFIG_VCA_ENABLE};
static int g_iWeek[] = {IDS_CONFIG_SUNDAY, IDS_CONFIG_MONDAY, IDS_CONFIG_TUESDAY, IDS_CONFIG_WEDNESDAY, IDS_CONFIG_THURSDAY, IDS_CONFIG_FRIDAY ,IDS_CONFIG_SATURDAY};

CLS_VCAAlarmSchedulePage::CLS_VCAAlarmSchedulePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VCAAlarmSchedulePage::IDD, pParent)
{
	memset(m_chkEnbale, 0 , sizeof(m_chkEnbale));
	m_iLogonID = -1;
	m_iChannelNo = -1;

}

CLS_VCAAlarmSchedulePage::~CLS_VCAAlarmSchedulePage()
{
}

void CLS_VCAAlarmSchedulePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ALARM_SCHEDULE_RULE, m_cboRuleID);
	DDX_Control(pDX, IDC_COMBO_ALARM_SCHEDULE_EVENT, m_cboEvent);
	DDX_Control(pDX, IDC_COMBO_ALARM_SCHEDULE_ENABLE, m_cboEnbale);
	DDX_Control(pDX, IDC_COMBO_ALARM_SCHEDULE_WEEK, m_cboWeek);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME1, m_dtBeginTime[0]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME2, m_dtBeginTime[1]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME3, m_dtBeginTime[2]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME4, m_dtBeginTime[3]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME1, m_dtEndTime[0]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME2, m_dtEndTime[1]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME3, m_dtEndTime[2]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME4, m_dtEndTime[3]);
	DDX_Check(pDX, IDC_CHECK_TIME1, m_chkEnbale[0]);
	DDX_Check(pDX, IDC_CHECK_TIME2, m_chkEnbale[1]);
	DDX_Check(pDX, IDC_CHECK_TIME3, m_chkEnbale[2]);
	DDX_Check(pDX, IDC_CHECK_TIME4, m_chkEnbale[3]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE_SCENE, m_CboSceneId);
}


BEGIN_MESSAGE_MAP(CLS_VCAAlarmSchedulePage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_SCHEDULE_SET, &CLS_VCAAlarmSchedulePage::OnBnClickedButtonAlarmScheduleSet)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_SCHEDULE_RULE, &CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboAlarmScheduleRule)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_SCHEDULE_ALLDAY, &CLS_VCAAlarmSchedulePage::OnBnClickedButtonAlarmScheduleAllday)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_SCHEDULE_WEEK, &CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboAlarmScheduleWeek)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_SCHEDULE_ENABLE, &CLS_VCAAlarmSchedulePage::OnBnClickedButtonAlarmScheduleEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE_SCENE, &CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboScheduleScene)
	ON_CBN_SELCHANGE(IDC_COMBO_SDDEVICENO, &CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboSddeviceno)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_SCHEDULE_ENABLE, &CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboAlarmScheduleEnable)
END_MESSAGE_MAP()


// CLS_VCAAlarmSchedulePage message handlers

void CLS_VCAAlarmSchedulePage::OnBnClickedButtonAlarmScheduleSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	int iWeek = m_cboWeek.GetCurSel();
	SetAlarmSchedule(iWeek);
}

BOOL CLS_VCAAlarmSchedulePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	for (int i = 0; i < VCA_MAX_RULE_NUM_NEW; i++)
	{
		CString szRuleID;
		szRuleID.Format("%d", i + 1);
		m_cboRuleID.AddString(szRuleID);
	}
	for(int j = 1; j <= MAX_SCENE_NUM; j++)
	{
		CString szSceneID;
		szSceneID.Format("%d", j);
		m_CboSceneId.AddString(szSceneID);
	}
	m_CboSceneId.SetCurSel(0);
	m_cboRuleID.SetCurSel(0);
	UI_Clear();
	UI_UpdateText();
	SYSTEMTIME tSysTime;
	GetLocalTime(&tSysTime);
	m_cboWeek.SetCurSel(tSysTime.wDayOfWeek);
	UI_UpdateAlarmEnable();
	UI_UpdateAlarmSchedule();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboAlarmScheduleRule()
{
	// TODO: Add your control notification handler code here
	if(m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	m_cboEvent.SetCurSel(-1);
	UI_UpdateAlarmEnable();
	UI_UpdateAlarmSchedule();
}

void CLS_VCAAlarmSchedulePage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateText();	
}

void CLS_VCAAlarmSchedulePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iChannelNo = _iChannelNo;
	m_iLogonID = _iLogonID;
	if (m_iChannelNo < 0 || m_iLogonID < 0)
	{
		return;
	}
	m_cboEvent.SetCurSel(-1);
	UI_UpdateAlarmEnable();
	UI_UpdateAlarmSchedule();
}

void CLS_VCAAlarmSchedulePage::UI_UpdateAlarmSchedule()
{
	UI_Clear();
	//时间表
	int iWeekDay = m_cboWeek.GetCurSel();
	TAlarmScheduleParam alarmParam = {0};
	alarmParam.iBuffSize = sizeof(TAlarmScheduleParam);
	alarmParam.iSceneID = m_CboSceneId.GetCurSel();
	alarmParam.iWeekday = iWeekDay;
	alarmParam.iParam1 = m_cboRuleID.GetCurSel();
	alarmParam.iParam2 = m_cboEvent.GetCurSel();
	if(m_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	int iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_GET_ALARMSCHEDULE, &alarmParam);
	if (iRet >= 0)
	{
		NVS_SCHEDTIME *pTS = NULL;
		CTime timeNow = CTime::GetCurrentTime();
		CTime timeSchStart, timeSchStop;
		for (int i=0; i<MAX_TIMESEGMENT; i++)
		{
			pTS = &alarmParam.timeSeg[iWeekDay][i];
			VERIFY(pTS);

			if (pTS->iStartHour >= 0 && pTS->iStartHour < MAX_HOUR 
				&& pTS->iStartMin >= 0 && pTS->iStartMin < MAX_MINUTE)
			{
				timeSchStart = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), pTS->iStartHour, pTS->iStartMin, 0);
			} 
			else
			{
				timeSchStart = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 0, 0, 0);
			}
			if (pTS->iStopHour >= 0 && pTS->iStopHour < MAX_HOUR 
				&& pTS->iStopMin >= 0 && pTS->iStopMin < MAX_MINUTE)
			{
				timeSchStop = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), pTS->iStopHour, pTS->iStopMin, 0);
			} 
			else
			{
				timeSchStop = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 0, 0, 0);
			}
			m_dtBeginTime[i].SetTime(&timeSchStart);
			m_dtEndTime[i].SetTime(&timeSchStop);
			m_chkEnbale[i] = (BOOL)pTS->iRecordMode;
		}
	}
	else
	{
		m_cboEvent.SetCurSel(0);
		CTime timeNow = CTime::GetCurrentTime();
		CTime timeSchStart, timeSchStop;
		for (int i=0; i<MAX_TIMESEGMENT; i++)
		{
			timeSchStart = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),0, 0, 0);
			timeSchStop = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),0, 0, 0);
			m_dtBeginTime[i].SetTime(&timeSchStart);
			m_dtEndTime[i].SetTime(&timeSchStop);
			m_chkEnbale[i] = FALSE;
		}
	}
	UpdateData(FALSE);
}

void CLS_VCAAlarmSchedulePage::UI_UpdateAlarmEnable()
{

	if(m_iChannelNo < 0 || m_iChannelNo >= MAX_CHANNEL_NUM)
	{
		m_iChannelNo = 0;
	}

	int iSceneID = m_CboSceneId.GetCurSel();
	int iRuleID = m_cboRuleID.GetCurSel();
	VCARuleParam  tParam = {0};
	tParam.stRule.iRuleID = iRuleID;
	tParam.stRule.iSceneID = iSceneID;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_RULE_PARAM, m_iChannelNo, &tParam, sizeof(VCARuleParam));
	if (iRet < 0 || !tParam.stRule.iValid)
	{
		m_cboEvent.SetCurSel(0);
		return;
	}
	int iEventID = tParam.iEventID;
	m_cboEvent.SetCurSel(iEventID);

	TAlarmScheEnableParam st = {0};
	st.iSceneID = iSceneID;
	st.iEnable = 0;
	st.iBuffSize = sizeof(TAlarmScheEnableParam);
	st.pvReserved = NULL;
	st.iParam1 = iRuleID;
	st.iParam2 = iEventID;
	iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo,ALARM_TYPE_VCA, CMD_GET_ALARMSCH_ENABLE, &st);
	if(iRet < 0)
	{
		m_cboEnbale.SetCurSel(0);
	}
	else
	{
		m_cboEnbale.SetCurSel(st.iEnable);
	}
}

void CLS_VCAAlarmSchedulePage::SetAlarmSchedule( int iWeek )
{
	UpdateData(TRUE);
	int iRuleID = m_cboRuleID.GetCurSel();
	int iEventID = m_cboEvent.GetCurSel();
	int iSceneID = m_CboSceneId.GetCurSel();
	int iWeekDay = iWeek;
	NVS_SCHEDTIME schedtime[MAX_TIMESEGMENT];
	vca_TVCAParam * vp = &g_VcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->chnParam[m_iChannelNo].iRuleID = iRuleID;
	vca_TAlarmSchedule * pAS = NULL;
	pAS = &vp->chnParam[m_iChannelNo].rule[iRuleID].alarmSchedule;
	pAS->iWeekday = iWeekDay;
	CTime BeginTime;
	CTime EndTime;

	for (int i=0; i<MAX_TIMESEGMENT; i++)
	{
		m_dtBeginTime[i].GetTime(BeginTime);
		m_dtEndTime[i].GetTime(EndTime);
	
		schedtime[i].iRecordMode = m_chkEnbale[i];		
		schedtime[i].iStartHour = BeginTime.GetHour();
		schedtime[i].iStartMin = BeginTime.GetMinute();
		schedtime[i].iStopHour = EndTime.GetHour();
		schedtime[i].iStopMin = EndTime.GetMinute();
	}

	TAlarmScheduleParam alarmParam = {0};
	alarmParam.iBuffSize = sizeof(alarmParam);
	alarmParam.iWeekday = iWeekDay;
	alarmParam.iSceneID = iSceneID;
	alarmParam.iParam1 = iRuleID;
	alarmParam.iParam2 = iEventID;
	for(int i=0; i< MAX_TIMESEGMENT; i++)
	{
		alarmParam.timeSeg[iWeekDay][i] = schedtime[i];
	}
	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_SET_ALARMSCHEDULE,  &alarmParam);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetAlarmConfig(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetAlarmConfig(%d)", m_iLogonID);
	}
}
void CLS_VCAAlarmSchedulePage::OnBnClickedButtonAlarmScheduleAllday()
{
	// TODO: Add your control notification handler code here
	if (m_iChannelNo < 0 || m_iLogonID < 0)
	{
		return;
	}
	for (int i = 0; i < 7; i++)
	{
		SetAlarmSchedule(i);
	}
}

void CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboAlarmScheduleWeek()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return ;
	}
	UI_UpdateAlarmSchedule();
}

void CLS_VCAAlarmSchedulePage::OnBnClickedButtonAlarmScheduleEnable()
{
	// TODO: Add your control notification handler code here
	
}

void CLS_VCAAlarmSchedulePage::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_STATIC_RULE_ID, IDS_VCA_RULE_ID);
	SetDlgItemTextEx(IDC_STATIC_EVENT_ID, IDS_VCA_EVENT_ID);
	SetDlgItemTextEx(IDC_STATIC_ALARM_SCHEDULE_ENABLE, IDS_VCA_SCHEDULE_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_ENABLE, IDS_VCA_ALARM_ENABLE);
	SetDlgItemTextEx(IDC_BUTTON_ALARM_SCHEDULE_ENABLE, IDS_VCA_LINK_SET);
	SetDlgItemTextEx(IDC_STATIC_SCHEDULE, IDS_VCA_SCHEDULE_SET);
	SetDlgItemTextEx(IDC_STATIC_OUT_WEEKDAY, IDS_VCA_WEEK);
	SetDlgItemTextEx(IDC_BUTTON_ALARM_SCHEDULE_SET, IDS_VCA_LINK_SET);
	SetDlgItemTextEx(IDC_BUTTON_ALARM_SCHEDULE_ALLDAY, IDS_VCA_ALL_WEEK_COPY);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME1,IDS_CONFIG_DNVR_ALMSCH_TIME1);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME2,IDS_CONFIG_DNVR_ALMSCH_TIME2);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME3,IDS_CONFIG_DNVR_ALMSCH_TIME3);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME4,IDS_CONFIG_DNVR_ALMSCH_TIME4);
	SetDlgItemTextEx(IDC_STATIC_SCHEDULE_SCENE,IDS_VCA_SCENE_ID);
	for (int i = 0; i < 7; i++)
	{
		InsertString(m_cboWeek, i, g_iWeek[i]);
	}
	for (int i = 0; i < VCA_EVENT_MAX; i++)
	{
		InsertString(m_cboEvent, i, g_iEventIDS[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		InsertString(m_cboEnbale, i, g_iEnableIDS[i]);
	}
}

void CLS_VCAAlarmSchedulePage::UI_Clear()
{
	CTime BeginTime(1971, 1, 1, 0, 0, 0);
	CTime EndTime(1971, 1, 1, 23, 59, 59);
	for (int i = 0; i < 4; i++)
	{
		m_dtBeginTime[i].SetFormat("HH:mm");
		m_dtBeginTime[i].SetTime(&BeginTime);
		m_dtEndTime[i].SetFormat("HH:mm");
		m_dtEndTime[i].SetTime(&EndTime);
		m_chkEnbale[i] = FALSE;
	}
	UpdateData(FALSE);
}
void CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboScheduleScene()
{
	UI_UpdateAlarmEnable();
	UI_UpdateAlarmSchedule();
}

void CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboSddeviceno()
{
	// TODO: Add your control notification handler code here
}



void CLS_VCAAlarmSchedulePage::OnCbnSelchangeComboAlarmScheduleEnable()
{
	if (m_iChannelNo < 0 || m_iLogonID < 0)
	{
		return;
	}
	int iRuleID = m_cboRuleID.GetCurSel(); 
	int iEventID = m_cboEvent.GetCurSel();
	if(iEventID < 0)
	{
		iEventID = 0;
		m_cboEvent.SetCurSel(0);
	}
	TAlarmScheEnableParam ScheEnableParam = {0};
	ScheEnableParam.iBuffSize = sizeof(TAlarmScheEnableParam);
	ScheEnableParam.iParam1 = iRuleID;
	ScheEnableParam.iParam2 = iEventID;
	ScheEnableParam.iSceneID = m_CboSceneId.GetCurSel();

	ScheEnableParam.iEnable = m_cboEnbale.GetCurSel();
	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_SET_ALARMSCH_ENABLE, &ScheEnableParam);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "[frmVCAAlarmPage::OnSetScheEnable]TDSetAlarmConfig error = 0x%p", GetLastError());
	}
}
