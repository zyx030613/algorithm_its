// Config\HolidayPlanPage.cpp : implementation file
//author zhy zhy 2013.04.11

#include "stdafx.h"
#include "Config\HolidayPlanPage.h"


// CLS_HolidayPlanPage dialog

IMPLEMENT_DYNAMIC(CLS_HolidayPlanPage, CDialog)

CLS_HolidayPlanPage::CLS_HolidayPlanPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_HolidayPlanPage::IDD, pParent)
{
	m_iLogonID = -1;

}

CLS_HolidayPlanPage::~CLS_HolidayPlanPage()
{
}

void CLS_HolidayPlanPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PLAN_ID, m_cboPlanID);
	DDX_Control(pDX, IDC_COMBO_MODE, m_cboMode);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_TIME, m_timeStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_TIME, m_timeEnd);
	DDX_Control(pDX, IDC_COMBO_START_MONTH, m_cboStartMonth);
	DDX_Control(pDX, IDC_COMBO_START_WEEK, m_cboStartWeek);
	DDX_Control(pDX, IDC_COMBO_START_DAY_OF_WEEK, m_cboStartDayOfWeek);
	DDX_Control(pDX, IDC_COMBO_END_MONTH, m_cboEndMonth);
	DDX_Control(pDX, IDC_COMBO_END_WEEK, m_cboEndWeek);
	DDX_Control(pDX, IDC_COMBO_END_DAY_OF_WEEK, m_cboEndDayOfWeek);
}


BEGIN_MESSAGE_MAP(CLS_HolidayPlanPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_PLAN_ID, &CLS_HolidayPlanPage::OnCbnSelchangeComboPlanId)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, &CLS_HolidayPlanPage::OnCbnSelchangeComboMode)
	ON_BN_CLICKED(IDC_BUTTON_HOLIDAY_PLAN_SCHEDULE, &CLS_HolidayPlanPage::OnBnClickedButtonHolidayPlanSchedule)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_START_TIME, &CLS_HolidayPlanPage::OnDtnDatetimechangeDatetimepickerStartTime)
END_MESSAGE_MAP()

// CLS_HolidayPlanPage message handlers
BOOL CLS_HolidayPlanPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	((CEdit*)GetDlgItem(IDC_EDIT_PLAN_NAME))->SetLimitText(32);
	CString strPlanID;
	for (int i = 0; i < MAX_HOLIDAY_PLAN_SCHEDULE;++i)
	{
		strPlanID.Format(_T("%d"),i+1);
		m_cboPlanID.AddString(strPlanID);
	}
	m_cboPlanID.SetCurSel(0);

	RECT rcShow = {0};
	RECT rcStartTime = {0};
	RECT rcEndTime = {0};
	int iOffset = 0;
	SYSTEMTIME tTime = {0};

	m_cboStartMonth.GetWindowRect(&rcShow);
	m_timeStart.GetWindowRect(&rcStartTime);
	iOffset = rcShow.top - rcStartTime.top;
	ScreenToClient(&rcStartTime);
	OffsetRect(&rcStartTime,0,iOffset);
	m_timeStart.MoveWindow(&rcStartTime);
	m_timeEnd.GetWindowRect(&rcEndTime);
	ScreenToClient(&rcEndTime);
	OffsetRect(&rcEndTime,0,iOffset);
	m_timeEnd.MoveWindow(&rcEndTime);

	UI_UpdateDialog();
	return TRUE;
}

void CLS_HolidayPlanPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	UI_UpdateSchedule();	
}

void CLS_HolidayPlanPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_HolidayPlanPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_PLAN_ID, IDS_CONFIG_HOLIDAY_TEMPLATE_NO);
	SetDlgItemTextEx(IDC_CHECK_PLAN_ENABLE, IDS_CONFIG_COMS_Flip1);
	SetDlgItemTextEx(IDC_STATIC_PLAN_NAME, IDS_CONFIG_HOLIDAY_TEMPLATE_NAME);
	SetDlgItemTextEx(IDC_STATIC_Mode, IDS_CONFIG_HOLIDAY_TIME_FORMATE);
	SetDlgItemTextEx(IDC_STATIC_START_TIME, IDS_CONFIG_HOLIDAY_START_TIME);
	SetDlgItemTextEx(IDC_STATIC_END_TIME, IDS_CONFIG_HOLIDAY_END_TIME);
	SetDlgItemTextEx(IDC_BUTTON_HOLIDAY_PLAN_SCHEDULE, IDS_SET);

	InsertString(m_cboMode,0,IDS_HOLIDAY_PLAN_MODE_DATE);
	InsertString(m_cboMode,1,IDS_HOLIDAY_PLAN_MODE_WEEK);
	InsertString(m_cboMode,2,IDS_HOLIDAY_PLAN_MODE_MONTH);
	m_cboMode.SetCurSel(0);

	InsertString(m_cboStartMonth,0,IDS_MONTH1);
	InsertString(m_cboStartMonth,1,IDS_MONTH2);
	InsertString(m_cboStartMonth,2,IDS_MONTH3);
	InsertString(m_cboStartMonth,3,IDS_MONTH4);
	InsertString(m_cboStartMonth,4,IDS_MONTH5);
	InsertString(m_cboStartMonth,5,IDS_MONTH6);
	InsertString(m_cboStartMonth,6,IDS_MONTH7);
	InsertString(m_cboStartMonth,7,IDS_MONTH8);
	InsertString(m_cboStartMonth,8,IDS_MONTH9);
	InsertString(m_cboStartMonth,9,IDS_MONTH10);
	InsertString(m_cboStartMonth,10,IDS_MONTH11);
	InsertString(m_cboStartMonth,11,IDS_MONTH12);
	m_cboStartMonth.SetCurSel(0);

	InsertString(m_cboEndMonth,0,IDS_MONTH1);
	InsertString(m_cboEndMonth,1,IDS_MONTH2);
	InsertString(m_cboEndMonth,2,IDS_MONTH3);
	InsertString(m_cboEndMonth,3,IDS_MONTH4);
	InsertString(m_cboEndMonth,4,IDS_MONTH5);
	InsertString(m_cboEndMonth,5,IDS_MONTH6);
	InsertString(m_cboEndMonth,6,IDS_MONTH7);
	InsertString(m_cboEndMonth,7,IDS_MONTH8);
	InsertString(m_cboEndMonth,8,IDS_MONTH9);
	InsertString(m_cboEndMonth,9,IDS_MONTH10);
	InsertString(m_cboEndMonth,10,IDS_MONTH11);
	InsertString(m_cboEndMonth,11,IDS_MONTH12);
	m_cboEndMonth.SetCurSel(0);

	InsertString(m_cboStartWeek,0,IDS_WEEK1);
	InsertString(m_cboStartWeek,1,IDS_WEEK2);
	InsertString(m_cboStartWeek,2,IDS_WEEK3);
	InsertString(m_cboStartWeek,3,IDS_WEEK4);
	InsertString(m_cboStartWeek,4,IDS_WEEK5);
	//InsertString(m_cboStartWeek,5,IDS_WEEK6);
	m_cboStartWeek.SetCurSel(0);

	InsertString(m_cboEndWeek,0,IDS_WEEK1);
	InsertString(m_cboEndWeek,1,IDS_WEEK2);
	InsertString(m_cboEndWeek,2,IDS_WEEK3);
	InsertString(m_cboEndWeek,3,IDS_WEEK4);
	InsertString(m_cboEndWeek,4,IDS_WEEK5);
	//InsertString(m_cboEndWeek,5,IDS_WEEK6);
	m_cboEndWeek.SetCurSel(0);

	InsertString(m_cboStartDayOfWeek,0,IDS_SUNDAY);
	InsertString(m_cboStartDayOfWeek,1,IDS_MONDAY);
	InsertString(m_cboStartDayOfWeek,2,IDS_TUESDAY);
	InsertString(m_cboStartDayOfWeek,3,IDS_WEDNESDAY);
	InsertString(m_cboStartDayOfWeek,4,IDS_THURSDAY);
	InsertString(m_cboStartDayOfWeek,5,IDS_FRIDAY);
	InsertString(m_cboStartDayOfWeek,6,IDS_SATURDAY);	
	m_cboStartDayOfWeek.SetCurSel(0);

	InsertString(m_cboEndDayOfWeek,0,IDS_SUNDAY);
	InsertString(m_cboEndDayOfWeek,1,IDS_MONDAY);
	InsertString(m_cboEndDayOfWeek,2,IDS_TUESDAY);
	InsertString(m_cboEndDayOfWeek,3,IDS_WEDNESDAY);
	InsertString(m_cboEndDayOfWeek,4,IDS_THURSDAY);
	InsertString(m_cboEndDayOfWeek,5,IDS_FRIDAY);
	InsertString(m_cboEndDayOfWeek,6,IDS_SATURDAY);	
	m_cboEndDayOfWeek.SetCurSel(0);
}

BOOL CLS_HolidayPlanPage::UI_UpdateSchedule()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return FALSE;
	}

	HOLIDAYPLAN_SCHEDULE tSchedule = {0};
	tSchedule.iPlanID = m_cboPlanID.GetCurSel();
	int iRet = NetClient_GetHolidayPlan(m_iLogonID,HOLIDAY_PLAN_CMD_SCHEDULE,&tSchedule,sizeof(HOLIDAYPLAN_SCHEDULE));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHolidayPlan(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHolidayPlan(%d)",m_iLogonID);
	}
	CheckDlgButton(IDC_CHECK_PLAN_ENABLE,tSchedule.iEnable);
	SetDlgItemText(IDC_EDIT_PLAN_NAME,tSchedule.cPlanName);
	m_cboMode.SetCurSel(tSchedule.iMode);
	UI_UpdateMode();

	if (0 == tSchedule.tStartTime.iYear)
	{
		tSchedule.tStartTime.iYear = 1970;
	}
	if (0 == tSchedule.tStartTime.iMonth)
	{
		tSchedule.tStartTime.iMonth = 1;
	}
	if (0 == tSchedule.tStartTime.iDay)
	{
		tSchedule.tStartTime.iDay = 1;
	}
	if (0 == tSchedule.tEndTime.iYear)
	{
		tSchedule.tEndTime.iYear = 1970;
	}
	if (0 == tSchedule.tEndTime.iMonth)
	{
		tSchedule.tEndTime.iMonth = 1;
	}
	if (0 == tSchedule.tEndTime.iDay)
	{
		tSchedule.tEndTime.iDay = 1;
	}

	switch(tSchedule.iMode)
	{
	case 0:
		{
			SYSTEMTIME tTime = {0};
			m_timeStart.GetTime(&tTime);
			tTime.wYear = tSchedule.tStartTime.iYear;
			tTime.wMonth = tSchedule.tStartTime.iMonth;
			tTime.wDay = tSchedule.tStartTime.iDay;
			m_timeStart.SetTime(&tTime);

			m_timeEnd.GetTime(&tTime);
			tTime.wYear = tSchedule.tEndTime.iYear;
			tTime.wMonth = tSchedule.tEndTime.iMonth;
			tTime.wDay = tSchedule.tEndTime.iDay;
			m_timeEnd.SetTime(&tTime);
		}
		break;
	case 1:
		{
			m_cboStartMonth.SetCurSel(tSchedule.tStartTime.iMonth-1);
			m_cboStartWeek.SetCurSel(tSchedule.tStartTime.iWeekOfMonth-1);
			m_cboStartDayOfWeek.SetCurSel(tSchedule.tStartTime.iDayOfWeek);

			m_cboEndMonth.SetCurSel(tSchedule.tEndTime.iMonth-1);
			m_cboEndWeek.SetCurSel(tSchedule.tEndTime.iWeekOfMonth-1);
			m_cboEndDayOfWeek.SetCurSel(tSchedule.tEndTime.iDayOfWeek);
		}
		break;
	case 2:
		{
			SYSTEMTIME tTime = {0};
			m_timeStart.GetTime(&tTime);
			tTime.wMonth = tSchedule.tStartTime.iMonth;
			tTime.wDay = tSchedule.tStartTime.iDay;
			m_timeStart.SetTime(&tTime);

			m_timeEnd.GetTime(&tTime);
			tTime.wMonth = tSchedule.tEndTime.iMonth;
			tTime.wDay = tSchedule.tEndTime.iDay;
			m_timeEnd.SetTime(&tTime);
		}
		break;
	}
	return TRUE;
}

BOOL CLS_HolidayPlanPage::UI_UpdateMode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return FALSE; 
	}

	int iMode = m_cboMode.GetCurSel();
	CString strFormat;
	switch(iMode)
	{
	case 0:
		strFormat.Format(_T("yyyy-MM-dd"));
		break;
	case 2:
		strFormat.Format(_T("MM-dd"));
		break;
	default:
		break;
	}

	if (strFormat.GetLength() > 0)
	{
		UI_UpdateWindowMode(FALSE);
		m_timeStart.SetFormat(strFormat);
		m_timeEnd.SetFormat(strFormat);
	}
	else
	{
		UI_UpdateWindowMode(TRUE);
	}
	return TRUE;
}

void CLS_HolidayPlanPage::OnCbnSelchangeComboPlanId()
{
	// TODO: Add your control notification handler code here
	UI_UpdateSchedule();
}

void CLS_HolidayPlanPage::OnCbnSelchangeComboMode()
{
	// TODO: Add your control notification handler code here
	UI_UpdateMode();
}

void CLS_HolidayPlanPage::OnBnClickedButtonHolidayPlanSchedule()
{
	// TODO: Add your control notification handler code here
	HOLIDAYPLAN_SCHEDULE tSchedule = {0};
	tSchedule.iPlanID = m_cboPlanID.GetCurSel();
	tSchedule.iEnable = IsDlgButtonChecked(IDC_CHECK_PLAN_ENABLE);
	tSchedule.iMode = m_cboMode.GetCurSel();
	GetDlgItemText(IDC_EDIT_PLAN_NAME,tSchedule.cPlanName,sizeof(tSchedule.cPlanName)); 
	SYSTEMTIME tTime = {0};
	int iStartTime = 0;
	int iEndTime = 0;
	switch(tSchedule.iMode)
	{
	case 0:
		{
			m_timeStart.GetTime(&tTime);
			tSchedule.tStartTime.iYear =tTime.wYear;
			tSchedule.tStartTime.iMonth = tTime.wMonth;
			tSchedule.tStartTime.iDay = tTime.wDay;
			iStartTime = tTime.wYear*12*31+tTime.wMonth*31+tTime.wDay;
			m_timeEnd.GetTime(&tTime);
			tSchedule.tEndTime.iYear = tTime.wYear;
			tSchedule.tEndTime.iMonth = tTime.wMonth;
			tSchedule.tEndTime.iDay = tTime.wDay;
			iEndTime = tTime.wYear*12*31+tTime.wMonth*31+tTime.wDay;
			if (iStartTime > iEndTime)
			{
				MessageBox(GetTextEx(IDS_MSG_ALARM_TIME), _T(""));
				return;
			}
		}
		break;
	case 1:
		{
			tSchedule.tStartTime.iMonth = m_cboStartMonth.GetCurSel()+1;
			tSchedule.tStartTime.iWeekOfMonth = m_cboStartWeek.GetCurSel()+1;
			tSchedule.tStartTime.iDayOfWeek = m_cboStartDayOfWeek.GetCurSel();
			iStartTime = tSchedule.tStartTime.iMonth*31+tSchedule.tStartTime.iWeekOfMonth*7+tSchedule.tStartTime.iDayOfWeek;
			tSchedule.tEndTime.iMonth = m_cboEndMonth.GetCurSel()+1;
			tSchedule.tEndTime.iWeekOfMonth = m_cboEndWeek.GetCurSel()+1;
			tSchedule.tEndTime.iDayOfWeek = m_cboEndDayOfWeek.GetCurSel();
			iEndTime = tSchedule.tEndTime.iMonth*31+tSchedule.tEndTime.iWeekOfMonth*7+tSchedule.tEndTime.iDayOfWeek;
			if (iStartTime > iEndTime)
			{
				MessageBox(GetTextEx(IDS_MSG_ALARM_TIME), _T(""));
				return;
			}
		}
		break;
	case 2:
		{
			m_timeStart.GetTime(&tTime);
			tSchedule.tStartTime.iMonth = tTime.wMonth;
			tSchedule.tStartTime.iDay = tTime.wDay;
			iStartTime = tTime.wYear*12*31+tTime.wMonth*31+tTime.wDay;
			m_timeEnd.GetTime(&tTime);
			tSchedule.tEndTime.iMonth = tTime.wMonth;
			tSchedule.tEndTime.iDay = tTime.wDay;
			iEndTime = tTime.wYear*12*31+tTime.wMonth*31+tTime.wDay;
			if (iStartTime > iEndTime)
			{
				MessageBox(GetTextEx(IDS_MSG_ALARM_TIME), _T(""));
				return;
			}
		}
		break;
	default:
		return;
	}

	int iRet = NetClient_SetHolidayPlan(m_iLogonID,HOLIDAY_PLAN_CMD_SCHEDULE,&tSchedule,sizeof(HOLIDAYPLAN_SCHEDULE));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHolidayPlan(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHolidayPlan(%d)",m_iLogonID);
	}
}

void CLS_HolidayPlanPage::UI_UpdateWindowMode( BOOL _bShow)
{
	int iCmd = SW_HIDE;
	if (TRUE == _bShow)
	{
		iCmd = SW_NORMAL;
	}
	m_cboStartMonth.ShowWindow(iCmd);
	m_cboStartWeek.ShowWindow(iCmd);
	m_cboStartDayOfWeek.ShowWindow(iCmd);
	m_cboEndMonth.ShowWindow(iCmd);
	m_cboEndWeek.ShowWindow(iCmd);
	m_cboEndDayOfWeek.ShowWindow(iCmd);
	m_timeStart.ShowWindow(1-iCmd);
	m_timeEnd.ShowWindow(1-iCmd);
}
void CLS_HolidayPlanPage::OnDtnDatetimechangeDatetimepickerStartTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
