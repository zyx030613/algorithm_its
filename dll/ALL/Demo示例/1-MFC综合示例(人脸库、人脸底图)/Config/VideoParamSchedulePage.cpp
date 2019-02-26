// Config\VdieoParamSchedulePage.cpp : implementation file
//

#include "stdafx.h"
#include "VideoParamSchedulePage.h"


// CLS_VdieoParamSchedulePage dialog

IMPLEMENT_DYNAMIC(CLS_VideoParamSchedulePage, CDialog)

CLS_VideoParamSchedulePage::CLS_VideoParamSchedulePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VideoParamSchedulePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	memset(&m_tSchedule,0,sizeof(m_tSchedule));
}

CLS_VideoParamSchedulePage::~CLS_VideoParamSchedulePage()
{

}

void CLS_VideoParamSchedulePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE, m_cboSchedule);
	DDX_Control(pDX, IDC_COMBO_COLOR_TO_BLACK, m_cboColorToGray);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_tmStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOP, m_tmStop);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_sldBrightness);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_sldContrast);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_sldSaturation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_sldHue);
}


BEGIN_MESSAGE_MAP(CLS_VideoParamSchedulePage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_SCHEDULE, &CLS_VideoParamSchedulePage::OnBnClickedButtonSchedule)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE, &CLS_VideoParamSchedulePage::OnCbnSelchangeComboSchedule)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BRIGHTNESS, &CLS_VideoParamSchedulePage::OnNMCustomdrawSliderBrightness)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CONTRAST, &CLS_VideoParamSchedulePage::OnNMCustomdrawSliderContrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SATURATION, &CLS_VideoParamSchedulePage::OnNMCustomdrawSliderSaturation)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_HUE, &CLS_VideoParamSchedulePage::OnNMCustomdrawSliderHue)
	ON_BN_CLICKED(IDC_BUTTON_SCHEDULE_SAVE, &CLS_VideoParamSchedulePage::OnBnClickedButtonScheduleSave)
END_MESSAGE_MAP()


// CLS_VdieoParamSchedulePage message handlers

BOOL CLS_VideoParamSchedulePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_tmStart.SetFormat(_T("HH:mm"));
	m_tmStop.SetFormat(_T("HH:mm"));

	m_sldBrightness.SetRange(0,255);
	m_sldHue.SetRange(0,255);
	m_sldContrast.SetRange(0,255);
	m_sldSaturation.SetRange(0,255);

	UI_UpdateDialog();

	CString strSchedule;
	for (int i = 1; i <= MAX_TIMESEGMENT; ++i)
	{
		strSchedule.Format(_T("%d"),i);
		m_cboSchedule.AddString(strSchedule);
	}
	m_cboSchedule.SetCurSel(0);

	m_cboColorToGray.SetCurSel(0);

	UI_UpdateSchedule();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VideoParamSchedulePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

	UpdateSchedule();

	UI_UpdateSchedule();
}

void CLS_VideoParamSchedulePage::OnLanguageChanged( int /*_iLanguage*/ )
{
	UI_UpdateDialog();
}

void CLS_VideoParamSchedulePage::OnCbnSelchangeComboSchedule()
{
	UI_UpdateSchedule();
}

void CLS_VideoParamSchedulePage::OnBnClickedButtonSchedule()
{
	if(FALSE == SaveSchedule())
	{
		return;
	}

	STR_VideoParam *pSchedule[MAX_TIMESEGMENT] = {&m_tSchedule[0],&m_tSchedule[1],&m_tSchedule[2],&m_tSchedule[3]};
	int iRet = NetClient_SetVideoparaSchedule(m_iLogonID,m_iChannelNo,pSchedule);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoparaSchedule(%d,%d,%#x)"
			,m_iLogonID,m_iChannelNo,pSchedule);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoparaSchedule(%d,%d,%#x)"
			,m_iLogonID,m_iChannelNo,pSchedule);
	}
}

void CLS_VideoParamSchedulePage::UI_UpdateDialog()
{
	InsertString(m_cboColorToGray,0,IDS_CFG_VIDEO_PARAM_SCHEDULE_DISABLE);	
	InsertString(m_cboColorToGray,1,IDS_CFG_VIDEO_PARAM_SCHEDULE_GRAY);
	InsertString(m_cboColorToGray,2,IDS_CFG_VIDEO_PARAM_SCHEDULE_COLOR);

	SetDlgItemTextEx(IDC_STATIC_SCHEDULE,IDS_CFG_VIDEO_PARAM_SCHEDULE_TEMPLET);
	SetDlgItemTextEx(IDC_STATIC_COLOR_TO_GRAY,IDS_CFG_VIDEO_PARAM_SCHEDULE_COLOR_TO_GRAY);
	SetDlgItemTextEx(IDC_STATIC_TIME_SPAN,IDS_CFG_VIDEO_PARAM_SCHEDULE_TIME_SPAN);
	SetDlgItemTextEx(IDC_STATIC_BRIGHTNESS,IDS_PREVIEW_BRIGHTNESS);
	SetDlgItemTextEx(IDC_STATIC_CONTRAST,IDS_PREVIEW_CONTRAST);
	SetDlgItemTextEx(IDC_STATIC_SATURATION,IDS_PREVIEW_SATURATION);
	SetDlgItemTextEx(IDC_STATIC_HUE,IDS_PREVIEW_HUE);
	SetDlgItemTextEx(IDC_BUTTON_SCHEDULE_SAVE,IDS_LOG_SAVE);
	SetDlgItemTextEx(IDC_BUTTON_SCHEDULE,IDS_SET);
}

void CLS_VideoParamSchedulePage::UI_UpdateSchedule()
{
	int iIndex = m_cboSchedule.GetCurSel();
	if (iIndex < 0)
	{
		return;
	}

	SYSTEMTIME tTime = {0};
	GetSystemTime(&tTime);
	tTime.wHour = m_tSchedule[iIndex].strctTempletTime.iStartHour;
	tTime.wMinute = m_tSchedule[iIndex].strctTempletTime.iStartMin;
	m_tmStart.SetTime(&tTime);
	tTime.wHour = m_tSchedule[iIndex].strctTempletTime.iStopHour;
	tTime.wMinute = m_tSchedule[iIndex].strctTempletTime.iStopMin;
	m_tmStop.SetTime(&tTime);
	m_cboColorToGray.SetCurSel(m_tSchedule[iIndex].strctTempletTime.iRecordMode);
	m_sldBrightness.SetPos(m_tSchedule[iIndex].m_u16Brightness);
	m_sldHue.SetPos(m_tSchedule[iIndex].m_u16Hue);
	m_sldContrast.SetPos(m_tSchedule[iIndex].m_u16Contrast);
	m_sldSaturation.SetPos(m_tSchedule[iIndex].m_u16Saturation);
}

void CLS_VideoParamSchedulePage::OnNMCustomdrawSliderBrightness(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	SetDlgItemInt(IDC_STATIC_BRIGHTNESS_VALUE,m_sldBrightness.GetPos());

	*pResult = 0;
}

void CLS_VideoParamSchedulePage::OnNMCustomdrawSliderContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	SetDlgItemInt(IDC_STATIC_CONTRAST_VALUE,m_sldContrast.GetPos());

	*pResult = 0;
}

void CLS_VideoParamSchedulePage::OnNMCustomdrawSliderSaturation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	SetDlgItemInt(IDC_STATIC_SATURATION_VALUE,m_sldSaturation.GetPos());

	*pResult = 0;
}

void CLS_VideoParamSchedulePage::OnNMCustomdrawSliderHue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	SetDlgItemInt(IDC_STATIC_HUE_VALUE,m_sldHue.GetPos());

	*pResult = 0;
}

void CLS_VideoParamSchedulePage::UpdateSchedule()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	memset(&m_tSchedule,0,sizeof(m_tSchedule));    
	STR_VideoParam* pSchedule[] = {&m_tSchedule[0],&m_tSchedule[1],&m_tSchedule[2],&m_tSchedule[3]};
	int iRet =  NetClient_GetVideoparaSchedule(m_iLogonID, m_iChannelNo, pSchedule);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoparaSchedule(%d,%d,%#x)"
			,m_iLogonID,m_iChannelNo,pSchedule);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoparaSchedule(%d,%d,%#x)"
			,m_iLogonID,m_iChannelNo,pSchedule);
	}
}

BOOL CLS_VideoParamSchedulePage::SaveSchedule()
{
	int iIndex = m_cboSchedule.GetCurSel();
	if (iIndex < 0)
	{
		AddLog(LOG_TYPE_MSG,"","please select a valid schedule(%d)",iIndex);
		return FALSE;
	}

	CTime ctmStart = 0;
	CTime ctmStop = 0;
	m_tmStart.GetTime(ctmStart);
	m_tmStop.GetTime(ctmStop);
	int iStart = ctmStart.GetHour()*60+ctmStart.GetMinute();
	int iStop = ctmStop.GetHour()*60+ctmStop.GetMinute();
	
	if ((iStart+iStop) > 0 && iStart >= iStop)
	{
		AddLog(LOG_TYPE_MSG,"","please select a valid time range");
		return FALSE;
	}

	int iStarti = 0;
	int iStopi = 0;
	for (int i = 0; i < MAX_TIMESEGMENT; ++i)
	{
		NVS_SCHEDTIME& tSchedTime = m_tSchedule[i].strctTempletTime;
		iStarti = tSchedTime.iStartHour*60+tSchedTime.iStartMin;
		iStopi = tSchedTime.iStopHour*60+tSchedTime.iStopMin;
		if (iIndex == i || 0 ==(iStarti+iStopi) || 0 == (iStart+iStop))
		{
			continue;
		}

		if (iStarti >= iStopi
			|| iStart >= iStarti && iStart < iStopi 
			|| iStop > iStarti && iStop <= iStopi)
		{
			AddLog(LOG_TYPE_MSG,"","collide with time range(%2d:%2d - %2d:%2d)"
				,tSchedTime.iStartHour,tSchedTime.iStartMin,tSchedTime.iStopHour,tSchedTime.iStopMin);
			return FALSE;
		}
	}

	m_tSchedule[iIndex].strctTempletTime.iStartHour = ctmStart.GetHour();
	m_tSchedule[iIndex].strctTempletTime.iStartMin = ctmStart.GetMinute();
	m_tSchedule[iIndex].strctTempletTime.iStopHour = ctmStop.GetHour();
	m_tSchedule[iIndex].strctTempletTime.iStopMin = ctmStop.GetMinute();
	m_tSchedule[iIndex].strctTempletTime.iRecordMode = m_cboColorToGray.GetCurSel();
	m_tSchedule[iIndex].m_u16Brightness = m_sldBrightness.GetPos();
	m_tSchedule[iIndex].m_u16Hue = m_sldHue.GetPos();
	m_tSchedule[iIndex].m_u16Contrast = m_sldContrast.GetPos();
	m_tSchedule[iIndex].m_u16Saturation = m_sldSaturation.GetPos();
	AddLog(LOG_TYPE_MSG,"","save schedule(%d) finished",iIndex);

	return TRUE;
}

void CLS_VideoParamSchedulePage::OnBnClickedButtonScheduleSave()
{
	SaveSchedule();
}
