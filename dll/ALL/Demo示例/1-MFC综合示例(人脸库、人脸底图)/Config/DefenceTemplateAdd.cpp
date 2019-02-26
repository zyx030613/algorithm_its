
#include "stdafx.h"
#include "NetClientDemo.h"
#include "DefenceTemplateAdd.h"
#include "../Common/CommonFun.h"

// CLS_DefenceTemplateAdd 对话框

IMPLEMENT_DYNAMIC(CLS_DefenceTemplateAdd, CDialog)

CLS_DefenceTemplateAdd::CLS_DefenceTemplateAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_DefenceTemplateAdd::IDD, pParent)
{	
}

CLS_DefenceTemplateAdd::~CLS_DefenceTemplateAdd()
{
}

void CLS_DefenceTemplateAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	for (int i=0;i<MAX_DAYS;i++)
	{		
		DDX_Control(pDX, IDC_CHK_SUNDAY+i, m_chkWeek[i]);
	}
	for (int i=0; i<MAX_DH_TIMESEGMENT;i++)
	{
		DDX_Control(pDX, IDC_CHK_TIME1+i, m_chkTime[i]);
		DDX_Control(pDX, IDC_DATETIMEPICKER_TIME_START1+i, m_dtStart[i]);
		DDX_Control(pDX, IDC_DATETIMEPICKER_TIME_END1+i, m_dtStop[i]);
	}
	DDX_Control(pDX, IDC_CBO_WEEK_SELECT, m_cboWeekSelect);	
	DDX_Control(pDX, IDC_CHK_WEEK_ALL, m_chkWeekSelAll);
	DDX_Text(pDX,IDC_EDT_TEMPLATE_NAME, m_cstrTmpName);
}


BEGIN_MESSAGE_MAP(CLS_DefenceTemplateAdd, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD_TEMPLATE_OK, &CLS_DefenceTemplateAdd::OnBnClickedBtnAddTemplateOk)
	ON_CBN_SELCHANGE(IDC_CBO_WEEK_SELECT, &CLS_DefenceTemplateAdd::OnCbnSelchangeCboWeekSelect)
	ON_BN_CLICKED(IDC_CHK_WEEK_ALL, &CLS_DefenceTemplateAdd::OnBnClickedChkWeekAll)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_TIME1, IDC_CHK_TIME8, OnBnClickedChkTime) 
END_MESSAGE_MAP()


// CLS_DefenceTemplateAdd 消息处理程序

BOOL CLS_DefenceTemplateAdd::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->SetWindowText(GetTextEx(IDS_CONFIG_TIME_TEMPLATE));
	SetDlgItemTextEx(IDC_STC_TEMPLATE_NAME, IDS_CONFIG_HD_TEMPLATENAME);
	SetDlgItemTextEx(IDC_STC_DEFENCE_SET, IDS_VCA_ALARM_SCHEDULE);
	SetDlgItemTextEx(IDC_STC_COPY_TO_WEEK, IDS_CONFIG_COPYTOWEEK);
	SetDlgItemTextEx(IDC_CHK_WEEK_ALL, IDS_CONFIG_LINK_SELECT_ALL);
	SetDlgItemTextEx(IDC_CHK_SUNDAY, IDS_CONFIG_SUNDAY);
	SetDlgItemTextEx(IDC_CHK_MONDAY, IDS_CONFIG_MONDAY);
	SetDlgItemTextEx(IDC_CHK_TUESDAY, IDS_CONFIG_TUESDAY);
	SetDlgItemTextEx(IDC_CHK_WEDNESDAY, IDS_CONFIG_WEDNESDAY);
	SetDlgItemTextEx(IDC_CHK_THURSDAY, IDS_CONFIG_THURSDAY);
	SetDlgItemTextEx(IDC_CHK_FRIDAY, IDS_CONFIG_FRIDAY);
	SetDlgItemTextEx(IDC_CHK_SATURDAY, IDS_CONFIG_SATURDAY);
	SetDlgItemTextEx(IDC_BTN_ADD_TEMPLATE_OK, IDS_CONFIG_LINK_SURE);

	memset(&m_tAlmInTmp,0,sizeof(AlarmInSchedule));
	m_tAlmInTmp.iSize = sizeof(AlarmInSchedule);

	memset(&m_tAlmInTmpSet,0,sizeof(AlarmInSchedule));
	m_tAlmInTmpSet.iSize = sizeof(AlarmInSchedule);

	m_cstrTmpName = "";

	InitDlgCtrl();

	return TRUE;
}

void CLS_DefenceTemplateAdd::InitDlgCtrl()
{
	for (int i = 0; i < MAX_DAYS; i++)
	{
		m_cboWeekSelect.InsertString(i,GetTextEx(IDS_CONFIG_SUNDAY+i));
	}
	for (int i = 0; i < MAX_DH_TIMESEGMENT; i++)
	{
		m_dtStart[i].SetFormat(_T("HH:mm"));
		m_dtStop[i].SetFormat(_T("HH:mm"));
		m_dtStart[i].SetTime(&GetTimeHHmm(0, 0));
		m_dtStop[i].SetTime(&GetTimeHHmm(0, 0));
		SetTimeCheck(0, i);
	}
	SYSTEMTIME st;
	GetLocalTime(&st);
	m_cboWeekSelect.SetCurSel(st.wDayOfWeek);
	m_iWeekNum = st.wDayOfWeek;
	m_chkWeek[st.wDayOfWeek].SetCheck(BST_CHECKED);
	
	m_tAlmInTmp.iScheduleNo = m_iTempNo;
	if (n_Dlg_Edit == m_iDlgType)
	{
		UpdateUI();			
	} 
}

void CLS_DefenceTemplateAdd::UpdateUI()
{
	UpdateData(TRUE);
	
	m_cstrTmpName = "";

	int iRet = NetClient_GetAlarmConfig(m_iLogonID,-1 ,-1, CMD_ALARM_IN_SCHEDULE, &m_tAlmInTmp);
	m_tAlmInTmpSet = m_tAlmInTmp;
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DefenceTemplatePage::UpdateSchedule] NetClient_GetAlarmConfig failed! logonID(%d),error(%d)"
			,m_iLogonID,GetLastError());
		return;
	}
	m_cstrTmpName = (CString)m_tAlmInTmp.cName;
	if (-1 == m_tAlmInTmp.iWeekday)//整周设置
	{
		m_chkWeekSelAll.SetCheck(TRUE);
		OnBnClickedChkWeekAll();		
	}

	for (int i = 0; i < MAX_DH_TIMESEGMENT; i++)
	{
		SetTimeSegInfo(m_iWeekNum, i);
	}

	UpdateData(FALSE);
}

void CLS_DefenceTemplateAdd::OnCbnSelchangeCboWeekSelect()
{	
	int iSel = m_cboWeekSelect.GetCurSel();
	if (m_iWeekNum == iSel)
	{
		return;
	}
	
	for (int i = 0; i < MAX_DH_TIMESEGMENT; i++)
	{
		if(!GetTimeSegInfo(m_iWeekNum, i))
		{
			m_cboWeekSelect.SetCurSel(m_iWeekNum);
			return;
		}
	}
	m_iWeekNum = iSel;
	for (int i = 0; i < MAX_DH_TIMESEGMENT; i++)
	{
		SetTimeSegInfo(m_iWeekNum, i);
	}
}

BOOL CLS_DefenceTemplateAdd::GetTimeSegInfo(int _iWeek, int _iTimeSeg)
{
	CTime tStrat;
	CTime tStop;
	int iIsCheck = m_chkTime[_iTimeSeg].GetCheck()?1:0;
	m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iRecordMode = iIsCheck;
	if (iIsCheck)
	{
		m_dtStart[_iTimeSeg].GetTime(tStrat);
		m_dtStop[_iTimeSeg].GetTime(tStop);
		if (tStrat >= tStop)
		{
			MessageBox(GetTextEx(IDS_MSG_ALARM_TIME),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
			return FALSE;
		}

		for(int i=0; i<_iTimeSeg;i++)
		{
			if (!m_tAlmInTmp.timeSeg[_iWeek][i].iRecordMode)
			{
				continue;
			}
			CTime tEnd = GetTimeHHmm(m_tAlmInTmp.timeSeg[_iWeek][i].iStopHour, m_tAlmInTmp.timeSeg[_iWeek][i].iStopMin);
			if (tEnd >= tStrat)
			{
				MessageBox(GetTextEx(IDS_MSG_ALARM_TIMESPAN),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
				return FALSE;
			}
		}
		m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStartHour = tStrat.GetHour();
		m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStartMin = tStrat.GetMinute();
		
		m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStopHour = tStop.GetHour();
		m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStopMin = tStop.GetMinute();
	}
	SetTimeCheck(iIsCheck, _iTimeSeg);

	return TRUE;
}

void CLS_DefenceTemplateAdd::SetTimeSegInfo(int _iWeek, int _iTimeSeg)
{
	int iIsCheck = m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iRecordMode;
	m_chkTime[_iTimeSeg].SetCheck(iIsCheck);
	if (iIsCheck)
	{
		int iHour = m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStartHour;
		int iMin =m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStartMin;
		m_dtStart[_iTimeSeg].SetFormat(_T("HH:mm"));
		m_dtStart[_iTimeSeg].SetTime(&GetTimeHHmm(iHour, iMin));

		iHour = m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStopHour;
		iMin = m_tAlmInTmp.timeSeg[_iWeek][_iTimeSeg].iStopMin;
		m_dtStop[_iTimeSeg].SetFormat(_T("HH:mm"));
		m_dtStop[_iTimeSeg].SetTime(&GetTimeHHmm(iHour, iMin));
	}
	SetTimeCheck(iIsCheck, _iTimeSeg);
}

void CLS_DefenceTemplateAdd::SetTimeCheck(int _iIsChk, int _iNo)
{
	if (_iIsChk)
	{
		m_dtStart[_iNo].EnableWindow(TRUE);
		m_dtStop[_iNo].EnableWindow(TRUE);
	}
	else
	{
		m_dtStart[_iNo].EnableWindow(FALSE);
		m_dtStop[_iNo].EnableWindow(FALSE);

		m_dtStart[_iNo].SetTime(&GetTimeHHmm(0, 0));
		m_dtStop[_iNo].SetTime(&GetTimeHHmm(0, 0));
	}
}

void CLS_DefenceTemplateAdd::OnBnClickedChkTime(UINT uId)
{
	int iNo = uId - IDC_CHK_TIME1;
	int iIsSel = m_chkTime[iNo].GetCheck();
	SetTimeCheck(iIsSel, iNo);
}

CTime CLS_DefenceTemplateAdd::GetTimeHHmm(int _iHour, int _iMin)
{
	CTime tTime =  CTime::GetCurrentTime();
	tTime = CTime(tTime.GetYear(), tTime.GetMonth(), tTime.GetDay(),_iHour, _iMin, 0);
	return tTime;
}

void CLS_DefenceTemplateAdd::OnBnClickedChkWeekAll()
{
	if (m_chkWeekSelAll.GetCheck())
	{
		for (int i=0;i<MAX_DAYS;i++)
		{
			m_chkWeek[i].SetCheck(TRUE);
		}
	}
	else
	{
		for (int i=0;i<MAX_DAYS;i++)
		{
			m_chkWeek[i].SetCheck(FALSE);
		}
	}	
}

void CLS_DefenceTemplateAdd::OnBnClickedBtnAddTemplateOk()
{
	UpdateData(TRUE);

	int iRet = -1;
	strcpy_s(m_tAlmInTmpSet.cName, m_cstrTmpName);
	m_tAlmInTmpSet.iEnable = 1;
	m_tAlmInTmpSet.iScheduleNo = m_iTempNo;
	m_tAlmInTmpSet.iSize = sizeof(AlarmInSchedule);
	int iWeek = m_cboWeekSelect.GetCurSel();
	for (int i=0;i<MAX_DH_TIMESEGMENT;i++)
	{
		if(!GetTimeSegInfo(m_iWeekNum, i))
		{
			return;
		}
	}

	if (m_chkWeekSelAll.GetCheck())
	{	
		m_tAlmInTmpSet.iWeekday = -1;
				
		for (int i=0;i<MAX_DAYS;i++)
		{
			memcpy(&m_tAlmInTmpSet.timeSeg[i],m_tAlmInTmp.timeSeg[iWeek],MAX_DAYS*MAX_DH_TIMESEGMENT*sizeof(NVS_SCHEDTIME));
		}
		iRet = NetClient_SetAlarmConfig(m_iLogonID,-1 ,-1, CMD_ALARM_IN_SCHEDULE, &m_tAlmInTmpSet);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_DefenceTemplateAdd::OnBnClickedBtnAddTemplateOk] NetClient_SetAlarmConfig failed! logonID(%d),error(%d)"
				,m_iLogonID,GetLastError());
			return;
		}
	}
	else
	{
		for (int i=0;i<MAX_DAYS;i++)
		{
			if(m_chkWeek[i].GetCheck())
			{
				m_tAlmInTmpSet.iWeekday = i;
				//memcpy(&m_tAlmInTmpSet.timeSeg[i],m_tAlmInTmp.timeSeg[iWeek],sizeof(NVS_SCHEDTIME));
				memcpy(&m_tAlmInTmpSet.timeSeg[i],m_tAlmInTmp.timeSeg[iWeek],MAX_DAYS*MAX_DH_TIMESEGMENT*sizeof(NVS_SCHEDTIME));
				iRet = NetClient_SetAlarmConfig(m_iLogonID,-1 ,-1, CMD_ALARM_IN_SCHEDULE, &m_tAlmInTmpSet);
				if (iRet < 0)
				{
					AddLog(LOG_TYPE_FAIL,"","[CLS_DefenceTemplateAdd::OnBnClickedBtnAddTemplateOk] NetClient_SetAlarmConfig failed! logonID(%d),error(%d)"
						,m_iLogonID,GetLastError());
					return;
				}
			}
		}
	}
	
	UpdateData(FALSE);

	EndDialog(IDOK);
}


