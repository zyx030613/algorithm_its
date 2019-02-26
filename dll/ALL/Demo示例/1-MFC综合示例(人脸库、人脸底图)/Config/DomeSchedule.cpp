// DomeSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeSchedule.h"

static int g_iWeek[] = {IDS_CONFIG_SUNDAY, IDS_CONFIG_MONDAY, IDS_CONFIG_TUESDAY
		, IDS_CONFIG_WEDNESDAY, IDS_CONFIG_THURSDAY, IDS_CONFIG_FRIDAY ,IDS_CONFIG_SATURDAY};
static int g_iEditID[] = {IDC_EDIT_SegVALUE1, IDC_EDIT_SegVALUE2, IDC_EDIT_SegVALUE3
		, IDC_EDIT_SegVALUE4, IDC_EDIT_SegVALUE5, IDC_EDIT_SegVALUE6, IDC_EDIT_SegVALUE7
		, IDC_EDIT_SegVALUE8};

// CLS_DomeSchedule dialog

IMPLEMENT_DYNAMIC(CLS_DomeSchedule, CDialog)

CLS_DomeSchedule::CLS_DomeSchedule(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeSchedule::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNO = 0;
}

CLS_DomeSchedule::~CLS_DomeSchedule()
{
}

void CLS_DomeSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WEEK, m_cboWeek);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME1, m_dtBeginTime[0]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME2, m_dtBeginTime[1]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME3, m_dtBeginTime[2]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME4, m_dtBeginTime[3]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME5, m_dtBeginTime[4]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME6, m_dtBeginTime[5]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME7, m_dtBeginTime[6]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME8, m_dtBeginTime[7]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME1, m_dtEndTime[0]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME2, m_dtEndTime[1]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME3, m_dtEndTime[2]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME4, m_dtEndTime[3]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME5, m_dtEndTime[4]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME6, m_dtEndTime[5]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME7, m_dtEndTime[6]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDTIME8, m_dtEndTime[7]);
	DDX_Control(pDX, IDC_CHECK_TIME1, m_chkEnbale[0]);
	DDX_Control(pDX, IDC_CHECK_TIME2, m_chkEnbale[1]);
	DDX_Control(pDX, IDC_CHECK_TIME3, m_chkEnbale[2]);
	DDX_Control(pDX, IDC_CHECK_TIME4, m_chkEnbale[3]);
	DDX_Control(pDX, IDC_CHECK_TIME5, m_chkEnbale[4]);
	DDX_Control(pDX, IDC_CHECK_TIME6, m_chkEnbale[5]);
	DDX_Control(pDX, IDC_CHECK_TIME7, m_chkEnbale[6]);
	DDX_Control(pDX, IDC_CHECK_TIME8, m_chkEnbale[7]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE1, m_cboSegType[0]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE2, m_cboSegType[1]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE3, m_cboSegType[2]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE4, m_cboSegType[3]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE5, m_cboSegType[4]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE6, m_cboSegType[5]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE7, m_cboSegType[6]);
	DDX_Control(pDX, IDC_COMBO_SegTYPE8, m_cboSegType[7]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE1, m_edtSegValue[0]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE2, m_edtSegValue[1]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE3, m_edtSegValue[2]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE4, m_edtSegValue[3]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE5, m_edtSegValue[4]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE6, m_edtSegValue[5]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE7, m_edtSegValue[6]);
	DDX_Control(pDX, IDC_EDIT_SegVALUE8, m_edtSegValue[7]);
}


BEGIN_MESSAGE_MAP(CLS_DomeSchedule, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DOME_SCHEDULE_SET, &CLS_DomeSchedule::OnBnClickedButtonDomeScheduleSet)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEK, &CLS_DomeSchedule::OnCbnSelchangeComboWeek)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_DomeSchedule message handlers

BOOL CLS_DomeSchedule::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialog();
	UI_Clear();
	CTime timeNow = CTime::GetCurrentTime();
	int iDayOfWeek = timeNow.GetDayOfWeek()-1;
	m_cboWeek.SetCurSel(iDayOfWeek);
	for (int i = 0; i < MAX_SCHEDULE; i++)
	{
		m_cboSegType[i].SetCurSel(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeSchedule::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo =  _iChannelNo;
	}

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO = _iStreamNo;
	}
}

void CLS_DomeSchedule::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_DomeSchedule::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}
	UI_Clear();

	int iWeekDay = m_cboWeek.GetCurSel();
	TDomeWorkSchedule DomeWorkSchedule = {0};
	int iBytesReturned = 0;
	DomeWorkSchedule.iWeekDay = iWeekDay;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_WORK_SCHEDULE, m_iChannelNo, &DomeWorkSchedule, sizeof(TDomeWorkSchedule), &iBytesReturned);
	if (iRet < 0 )
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_WORK_SCHEDULE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
		return;
	}
	
	for (int i = 0; i < MAX_SCHEDULE; i++)
	{
		CTime BeginTime(1971, 1, 1 , DomeWorkSchedule.tWork[i].iBeginHour, DomeWorkSchedule.tWork[i].iBeginMinute, 0);
		CTime EndTime(1971, 1, 1 , DomeWorkSchedule.tWork[i].iEndHour, DomeWorkSchedule.tWork[i].iEndMinute, 0);
		m_dtBeginTime[i].SetTime(&BeginTime);
		m_dtEndTime[i].SetTime(&EndTime);
		m_chkEnbale[i].SetCheck(DomeWorkSchedule.tWork[i].iEnable);
		m_cboSegType[i].SetCurSel(DomeWorkSchedule.tWork[i].iWorkType);
		SetDlgItemInt(g_iEditID[i], DomeWorkSchedule.tWork[i].iWorkValue);
	}
	AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_DOME_WORK_SCHEDULE] (%d, %d)", m_iLogonID, m_iChannelNo);
}

void CLS_DomeSchedule::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_DOME_WORK_SCHEDULE:
		UpdatePageUI();
		break;
	default:
		break;
	}
}

void CLS_DomeSchedule::UI_UpdateDialog()
{
	for (int i = 0; i < 7; i++)
	{
		InsertString(m_cboWeek, i, g_iWeek[i]);
	}

	for (int i = 0; i < MAX_SCHEDULE; i++)
	{
		InsertString(m_cboSegType[i], 0, IDS_WITHOUT_ACTION);
		InsertString(m_cboSegType[i], 1, IDS_CONFIG_8D1_PRESET);
		InsertString(m_cboSegType[i], 2, IDS_DOME_PTZ_ACT_SWEEP);
		InsertString(m_cboSegType[i], 3, IDS_DOME_PTZ_ACT_CRUISE);
		InsertString(m_cboSegType[i], 4, IDS_CONFIG_STORAGE_DISKMODE);
	}

	SetDlgItemTextEx(IDC_STATIC_WEEKDAY, IDS_VCA_WEEK);
	SetDlgItemTextEx(IDC_BUTTON_DOME_SCHEDULE_SET, IDS_VCA_LINK_SET);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME1,IDS_CONFIG_DNVR_ALMSCH_TIME1);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME2,IDS_CONFIG_DNVR_ALMSCH_TIME2);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME3,IDS_CONFIG_DNVR_ALMSCH_TIME3);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME4,IDS_CONFIG_DNVR_ALMSCH_TIME4);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME5, IDS_CONFIG_DNVR_ALMSCH_TIME5);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME6, IDS_CONFIG_DNVR_ALMSCH_TIME6);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME7, IDS_CONFIG_DNVR_ALMSCH_TIME7);
	SetDlgItemTextEx(IDC_STATIC_OUT_TIME8, IDS_CONFIG_DNVR_ALMSCH_TIME8);
}

void CLS_DomeSchedule::OnBnClickedButtonDomeScheduleSet()
{
	// TODO: Add your control notification handler code here
	int iWeekDay = m_cboWeek.GetCurSel();
	TDomeWorkSchedule DomeWorkSchedule = {0};
	DomeWorkSchedule.iWeekDay = iWeekDay;

	CTime BeginTime;
	CTime EndTime;
	for (int i= 0; i < MAX_SCHEDULE; i++)
	{
		m_dtBeginTime[i].GetTime(BeginTime);
		m_dtEndTime[i].GetTime(EndTime);
		DomeWorkSchedule.tWork[i].iBeginHour = BeginTime.GetHour();
		DomeWorkSchedule.tWork[i].iBeginMinute = BeginTime.GetMinute();
		DomeWorkSchedule.tWork[i].iEndHour = EndTime.GetHour();
		DomeWorkSchedule.tWork[i].iEndMinute = EndTime.GetMinute();
		DomeWorkSchedule.tWork[i].iEnable = m_chkEnbale[i].GetCheck();
		DomeWorkSchedule.tWork[i].iWorkType = m_cboSegType[i].GetCurSel();
		DomeWorkSchedule.tWork[i].iWorkValue = GetDlgItemInt(g_iEditID[i]); 
	}

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_WORK_SCHEDULE, m_iChannelNo, &DomeWorkSchedule, sizeof(TDomeWorkSchedule));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig[NET_CLIENT_DOME_WORK_SCHEDULE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig[NET_CLIENT_DOME_WORK_SCHEDULE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_DomeSchedule::UI_Clear()
{
	CTime BeginTime(1971, 1, 1, 0, 0, 0);
	CTime EndTime(1971, 1, 1, 23, 59, 59);
	for (int i = 0; i < MAX_SCHEDULE; i++)
	{
		m_dtBeginTime[i].SetFormat("HH:mm");
		m_dtBeginTime[i].SetTime(&BeginTime);
		m_dtEndTime[i].SetFormat("HH:mm");
		m_dtEndTime[i].SetTime(&EndTime);
	}
}

void CLS_DomeSchedule::OnCbnSelchangeComboWeek()
{
	// TODO: Add your control notification handler code here
	UpdatePageUI();
}

void CLS_DomeSchedule::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	UpdatePageUI();
}
