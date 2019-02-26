// HDSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "HDSchedule.h"


// CLS_HDSchedule dialog

IMPLEMENT_DYNAMIC(CLS_HDSchedule, CDialog)

CLS_HDSchedule::CLS_HDSchedule(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_HDSchedule::IDD, pParent)
{

}

CLS_HDSchedule::~CLS_HDSchedule()
{
}

void CLS_HDSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME1_START, m_timeSchedStart[0]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME2_START, m_timeSchedStart[1]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME3_START, m_timeSchedStart[2]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME4_START, m_timeSchedStart[3]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME5_START, m_timeSchedStart[4]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME6_START, m_timeSchedStart[5]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME7_START, m_timeSchedStart[6]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME8_START, m_timeSchedStart[7]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME1_STOP, m_timeSchedStop[0]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME2_STOP, m_timeSchedStop[1]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME3_STOP, m_timeSchedStop[2]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME4_STOP, m_timeSchedStop[3]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME5_STOP, m_timeSchedStop[4]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME6_STOP, m_timeSchedStop[5]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME7_STOP, m_timeSchedStop[6]);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCHEDTIME8_STOP, m_timeSchedStop[7]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE1, m_cboSchedule[0]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE2, m_cboSchedule[1]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE3, m_cboSchedule[2]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE4, m_cboSchedule[3]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE5, m_cboSchedule[4]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE6, m_cboSchedule[5]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE7, m_cboSchedule[6]);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE8, m_cboSchedule[7]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE1, m_chkSchedule[0]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE2, m_chkSchedule[1]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE3, m_chkSchedule[2]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE4, m_chkSchedule[3]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE5, m_chkSchedule[4]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE6, m_chkSchedule[5]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE7, m_chkSchedule[6]);
	DDX_Control(pDX, IDC_CHECK_SCHEDULE8, m_chkSchedule[7]);
}


BEGIN_MESSAGE_MAP(CLS_HDSchedule, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SCHEDULE_SET, &CLS_HDSchedule::OnBnClickedButtonScheduleSet)
	ON_CONTROL_RANGE(CBN_SELCHANGE,IDC_COMBO_SCHEDULE1,IDC_COMBO_SCHEDULE8,&CLS_HDSchedule::OnCbnSelchangeComboSchedule)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHECK_SCHEDULE1,IDC_CHECK_SCHEDULE8,&CLS_HDSchedule::OnBnClickedChkSchedule)
END_MESSAGE_MAP()


// CLS_HDSchedule message handlers

BOOL CLS_HDSchedule::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here

	CTime timeNow = CTime::GetCurrentTime();
	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),0, 0, 0);
	for(int i = 0;i < MAX_ITS_TIMERANGE;++i)
	{
		m_timeSchedStart[i].SetFormat(_T("HH:mm"));
		m_timeSchedStop[i].SetFormat(_T("HH:mm"));
		m_timeSchedStart[i].SetTime(&timeNow);
		m_timeSchedStop[i].SetTime(&timeNow);
	}

	((CButton*)GetDlgItem(IDC_RADIO_TEMPLATE_CHANGE_TYPE_IIME))->SetCheck(BST_CHECKED);
	UI_UpdateDialogText();
	return TRUE;  
}

void CLS_HDSchedule::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO =  _iStreamNo;
	}
	UI_UpdateDialogText();
	UpdateHDSchedulePara();
}

void CLS_HDSchedule::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
	UpdateHDSchedulePara();
}

void CLS_HDSchedule::UI_UpdateDialogText()
{
	for(int i = 0;i < MAX_ITS_TIMERANGE;++i)
	{
		int iTempIndex = m_cboSchedule[i].GetCurSel();
		iTempIndex = iTempIndex < 0 ? 0 : iTempIndex;
		InsertString(m_cboSchedule[i], 0, IDS_HD_MODE_OUTDOOR);
		InsertString(m_cboSchedule[i], 1, IDS_HD_MODE_INDOOR);
		InsertString(m_cboSchedule[i], 2, IDS_HD_MODE_MOTION);
		InsertString(m_cboSchedule[i], 3, IDS_HD_MODE_WDR);
		InsertString(m_cboSchedule[i], 4, IDS_HD_MODE_DARK);
		InsertString(m_cboSchedule[i], 5, IDS_HD_MODE_BRIGHT);
		InsertString(m_cboSchedule[i], 6, IDS_HD_MODE_COLORFUL);
		InsertString(m_cboSchedule[i], 7, IDS_HD_MODE_CUSTOMIZED);
		InsertString(m_cboSchedule[i], 8, IDS_HD_MODE_TEMP);
		m_cboSchedule[i].SetItemData(8, TEMP_TEMPLATE_INDEX);
		if (iTempIndex < m_cboSchedule[i].GetCount())
		{
			m_cboSchedule[i].SetCurSel(iTempIndex);
		}
		else
		{
			m_cboSchedule[i].SetCurSel(0);
		}
	}

	for (int iId = IDC_CBO_TEMPLATE_DAY; iId <= IDC_CBO_TEMPLATE_NIGHT; iId++)
	{
		CComboBox* pComboBox = ((CComboBox*)GetDlgItem(iId));
		int iTempIndex = pComboBox->GetCurSel();
		iTempIndex = iTempIndex < 0 ? 0 : iTempIndex;
		pComboBox->ResetContent();
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_OUTDOOR)), 0);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_INDOOR)), 1);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_MOTION)), 2);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_WDR)), 3);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_DARK)), 4);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_BRIGHT)), 5);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_COLORFUL)), 6);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_CUSTOMIZED)), 7);
		pComboBox->SetItemData(pComboBox->AddString(GetTextEx(IDS_HD_MODE_TEMP)), TEMP_TEMPLATE_INDEX);
		if (iTempIndex < pComboBox->GetCount())
		{
			pComboBox->SetCurSel(iTempIndex);
		}
		else
		{
			pComboBox->SetCurSel(0);
		}
	}

	SetDlgItemTextEx(IDC_BUTTON_SCHEDULE_SET, IDS_ITS_SET_DENOISE);

	SetDlgItemTextEx(IDC_STC_TEMPLATE_CHANGE_TYPE, IDS_TEMPLATE_MAP_CHANGE_TYPE);
	SetDlgItemTextEx(IDC_RADIO_TEMPLATE_CHANGE_TYPE_IIME, IDS_CONFIG_ITS_TIMERANGE_RANGE);
	SetDlgItemTextEx(IDC_RADIO_TEMPLATE_CHANGE_TYPE_DAY_NIGHT, IDS_STATIC_DAYNIGHT);
	SetDlgItemTextEx(IDC_STC_TEMPLATE_DAY, IDS_ADV_CHANNEL_DAYTIME);
	SetDlgItemTextEx(IDC_STC_TEMPLATE_NIGHT, IDS_ADV_CHANNEL_NIGHT);
}

void CLS_HDSchedule::UpdateHDSchedulePara()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iRet = -1;
	//更新选择框和时间段
	ITS_TTimeRange stTimeRange = {0};
	for (int i = 0;i < MAX_ITS_TIMERANGE;++i)
	{	
		CTime timeNow = CTime::GetCurrentTime();
		timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),0, 0, 0);
		m_timeSchedStart[i].SetTime(&timeNow);
		m_timeSchedStop[i].SetTime(&timeNow);
		iRet = NetClient_GetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, i, &stTimeRange, sizeof(ITS_TTimeRange));
		if(iRet >= 0)
		{
			int iBegainHour = 0,iBegainMin = 0,iEndHour = 0,iEndMin = 0;	
			iBegainHour = ((stTimeRange.iTimeRange >> 24) & 0xFF);
			iBegainMin = ((stTimeRange.iTimeRange >> 16) & 0xFF);
			iEndHour = ((stTimeRange.iTimeRange >> 8) & 0xFF);
			iEndMin = (stTimeRange.iTimeRange & 0xFF);

			if (stTimeRange.iEnable == 1)
			{
				timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iBegainHour, iBegainMin, 0);
				m_timeSchedStart[i].SetTime(&timeNow);
				timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iEndHour, iEndMin, 0);
				m_timeSchedStop[i].SetTime(&timeNow);
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRangeEnable(m_iLogonID %d)", m_iLogonID);
		}
		m_chkSchedule[i].SetCheck(stTimeRange.iEnable);
	}

	//更新模板
	for (int i=0;i < MAX_ITS_TIMERANGE;++i)
	{
		m_cboSchedule[i].ResetContent();
	}
	((CComboBox*)GetDlgItem(IDC_CBO_TEMPLATE_DAY))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_CBO_TEMPLATE_NIGHT))->ResetContent();
	for(int i = 0;i < MAX_ITS_TEMPLATE;++i)
	{
		char szTemplateName[LEN_64] = {0};
		iRet = NetClient_GetHDTemplateName(m_iLogonID, i, szTemplateName);
		if(iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTemplateName(m_iLogonID %d)", m_iLogonID);
		}
		CString strTemplateName = GetHDTemplateName(szTemplateName);
		
		for (int j=0;j < MAX_ITS_TIMERANGE;++j)
		{
			m_cboSchedule[j].AddString(strTemplateName);
		}

		for (int iId = IDC_CBO_TEMPLATE_DAY; iId <= IDC_CBO_TEMPLATE_NIGHT; iId++)
		{
			CComboBox* pComboBox = (CComboBox*)GetDlgItem(iId);
			pComboBox->AddString(strTemplateName);
		}
	}

	ITS_TOTAL_TTemplateMap stTemplateMap = {0};
	iRet = NetClient_GetHDTemplateMap(m_iLogonID, m_iChannelNo, &stTemplateMap, sizeof(ITS_TOTAL_TTemplateMap));
	if(iRet >= 0)
	{
		for (int i = 0;i < MAX_ITS_TIMERANGE;++i)
		{
			m_cboSchedule[i].SetCurSel(stTemplateMap.templatemap[i].iTemplateID);
		}
		((CComboBox*)GetDlgItem(IDC_CBO_TEMPLATE_DAY))->SetCurSel(stTemplateMap.iDayTemplateID);
		((CComboBox*)GetDlgItem(IDC_CBO_TEMPLATE_NIGHT))->SetCurSel(stTemplateMap.iNightTemplateID);
		
		BOOL blChangeTypeTime = (0 == stTemplateMap.iHDTemplateType) ? TRUE : FALSE;
		((CButton*)GetDlgItem(IDC_RADIO_TEMPLATE_CHANGE_TYPE_IIME))->SetCheck(blChangeTypeTime);
		((CButton*)GetDlgItem(IDC_RADIO_TEMPLATE_CHANGE_TYPE_DAY_NIGHT))->SetCheck(!blChangeTypeTime);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTemplateMap(m_iLogonID %d)", m_iLogonID);
	}
}

void CLS_HDSchedule::OnBnClickedButtonScheduleSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	//判断是否选择了模板
	BOOL blSet = FALSE;
	for (int i = 0; i < MAX_ITS_TIMERANGE; i++)
	{
		if (m_chkSchedule[i].GetCheck())
		{
			blSet = TRUE;
		}
	}
	if (!blSet)
	{
		MessageBox("Please select at least one template!", "", MB_OK|MB_TOPMOST);
		return;
	}

	//判断时间是否有重合
	BOOL bValidTime = TRUE;
	int iTemp = -1;
	CTime ctOldEnd = GetCurrentTime();
	CTime ctNewStart = GetCurrentTime();
	CTime ctNewEnd = GetCurrentTime();
	for (int i = 0; i < MAX_ITS_TIMERANGE; i++)
	{	
		if (m_chkSchedule[i].GetCheck())
		{
			m_timeSchedStart[i].GetTime(ctNewStart);
			m_timeSchedStop[i].GetTime(ctNewEnd);
			if (-1 == iTemp)//第一次比较
			{
				CTimeSpan ctsNewEndToNewStart = ctNewEnd - ctNewStart;
				int iNewEndToNewStart = (int)ctsNewEndToNewStart.GetTotalSeconds();
				if (iNewEndToNewStart < 0)
				{
					bValidTime = FALSE;
					break;
				}
				iTemp = i;
				ctOldEnd = ctNewEnd;
			}
			else
			{
				CTimeSpan ctsNewStartToOldEnd = ctNewStart - ctOldEnd;
				CTimeSpan ctsNewEndToNewStart = ctNewEnd - ctNewStart;
				int iNewStartToOldEnd = (int)ctsNewStartToOldEnd.GetTotalSeconds();
				int iNewEndToNewStart = (int)ctsNewEndToNewStart.GetTotalSeconds();
				if ((iNewEndToNewStart < 0) || (iNewStartToOldEnd < 0))
				{
					bValidTime = FALSE;
					break;
				}
				ctOldEnd = ctNewEnd;
			}
		}
	}
	if (!bValidTime)
	{
		MessageBox("Please select valid time !", "", MB_OK|MB_TOPMOST);
		return;
	}

	ITS_TOTAL_TTemplateMap stTemplateMap = {0};
	for (int i = 0;i < MAX_ITS_TIMERANGE;++i)
	{
		stTemplateMap.templatemap[i].iTemplateID = m_cboSchedule[i].GetCurSel();
		CString strName;
		m_cboSchedule[i].GetWindowText(strName);
		memcpy_s(stTemplateMap.templatemap[i].cTemplateName,
			sizeof(stTemplateMap.templatemap[i].cTemplateName),
			(LPCSTR)(LPCTSTR)strName,strName.GetLength());
	}
	
	BOOL blChangeTypeDayNight = ((CButton*)GetDlgItem(IDC_RADIO_TEMPLATE_CHANGE_TYPE_DAY_NIGHT))->GetCheck();
	stTemplateMap.iHDTemplateType = (int)blChangeTypeDayNight;	
	stTemplateMap.iDayTemplateID = ((CComboBox*)GetDlgItem(IDC_CBO_TEMPLATE_DAY))->GetCurSel();
	stTemplateMap.iNightTemplateID = ((CComboBox*)GetDlgItem(IDC_CBO_TEMPLATE_NIGHT))->GetCurSel();

	int iRet = NetClient_SetHDTemplateMap(m_iLogonID, m_iChannelNo, &stTemplateMap, sizeof(ITS_TOTAL_TTemplateMap));
	if(iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTemplateMap(m_iLogonID %d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTemplateMap(m_iLogonID %d)", m_iLogonID);
	}

	CTime timeNow = CTime::GetCurrentTime();
	for (int i = 0;i < MAX_ITS_TIMERANGE;++i)
	{
		ITS_TTimeRange stTimeRange = {0};
		m_timeSchedStart[i].GetTime(timeNow);
		stTimeRange.iTimeRange |= (timeNow.GetHour() << 24);
		stTimeRange.iTimeRange |= (timeNow.GetMinute() << 16);
		m_timeSchedStop[i].GetTime(timeNow);
		stTimeRange.iTimeRange |= (timeNow.GetHour() << 8);
		stTimeRange.iTimeRange |= timeNow.GetMinute();

		stTimeRange.iEnable = m_chkSchedule[i].GetCheck();

		iRet = NetClient_SetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, i, &stTimeRange, sizeof(ITS_TTimeRange));
		if(iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRangeEnable(m_iLogonID %d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRangeEnable(m_iLogonID %d)", m_iLogonID);
		}
	}

	int  iTmp = 1; 
	NetClient_SendCommand(m_iLogonID,COMMAND_ID_SAVECFG, m_iChannelNo, &iTmp, 0);
}

void CLS_HDSchedule::OnCbnSelchangeComboSchedule( UINT _uiID )
{

}

void CLS_HDSchedule::OnBnClickedChkSchedule( UINT _uiID )
{
	int index = _uiID - IDC_CHECK_SCHEDULE1;
	CTime timeNow = CTime::GetCurrentTime();
	if (m_chkSchedule[index].GetCheck() == BST_UNCHECKED)
	{
		CTime timeNow = CTime::GetCurrentTime();
		timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),0, 0, 0);
		m_timeSchedStart[index].SetTime(&timeNow);
		m_timeSchedStop[index].SetTime(&timeNow);
	}
	else
	{
		m_chkSchedule[index].SetCheck(BST_CHECKED);
	}
}