#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_IllegalPark.h"

#define LEN_2			2
#define POINT_RANGE		15		//点数范围


// CLS_VCAEVENT_IllegalPark 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_IllegalPark, CDialog)

CLS_VCAEVENT_IllegalPark::CLS_VCAEVENT_IllegalPark(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_IllegalPark::IDD, pParent)
{

}

CLS_VCAEVENT_IllegalPark::~CLS_VCAEVENT_IllegalPark()
{
}

void CLS_VCAEVENT_IllegalPark::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_ILLPARK_USE, m_chkUse);
	DDX_Control(pDX, IDC_CHK_ILLPARK_EVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CBO_ILLPARK_PRESET, m_cboPreset);
	DDX_Control(pDX, IDC_CBO_ILLPARK_AREA_NUM, m_cboAreaNum);
	DDX_Control(pDX, IDC_EDT_ILLPARK_AREA_NAME, m_edtAreaName);
	DDX_Control(pDX, IDC_EDT_ILLPARK_NOPARK_TIME, m_edtNoparkTime);
	DDX_Control(pDX, IDC_CBO_ILLPARK_SENSITIVITY, m_cboSensitivity);
	DDX_Control(pDX, IDC_EDT_ILLPARK_PARK_JUDGE_TIME, m_edtParkJudgeTime);
	DDX_Control(pDX, IDC_EDT_ILLPARK_POINTS, m_edtPoints);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME1_START, m_dtpTimeStart[0]);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME1_END, m_dtpTimeEnd[0]);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME2_START, m_dtpTimeStart[1]);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME2_END, m_dtpTimeEnd[1]);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME3_START, m_dtpTimeStart[2]);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME3_END, m_dtpTimeEnd[2]);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME4_START, m_dtpTimeStart[3]);
	DDX_Control(pDX, IDC_DTP_ILLPARK_TIME4_END, m_dtpTimeEnd[3]);
	DDX_Control(pDX, IDC_CHK_ILLPARK_PARK_CAPTURE, m_chkParkCapture);
	DDX_Control(pDX, IDC_EDT_ILLPARK_POINT_NUM, m_edtPointNum);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_IllegalPark, CDialog)
	ON_BN_CLICKED(IDC_BTN_ILLPARK_SET, &CLS_VCAEVENT_IllegalPark::OnBnClickedBtnIllparkSet)
	ON_BN_CLICKED(IDC_BTN_ILLPARK_DRAW, &CLS_VCAEVENT_IllegalPark::OnBnClickedBtnIllparkDraw)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_CBO_ILLPARK_PRESET, &CLS_VCAEVENT_IllegalPark::OnCbnSelchangeCboIllparkPreset)
	ON_CBN_SELCHANGE(IDC_CBO_ILLPARK_AREA_NUM, &CLS_VCAEVENT_IllegalPark::OnCbnSelchangeCboIllparkAreaNum)
	ON_EN_CHANGE(IDC_EDT_ILLPARK_POINT_NUM, &CLS_VCAEVENT_IllegalPark::OnEnChangeEdtIllparkPointNum)
END_MESSAGE_MAP()


BOOL CLS_VCAEVENT_IllegalPark::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here

	m_edtAreaName.SetLimitText(LEN_32 - 1);
	m_edtNoparkTime.SetLimitText(LEN_32 - 1);
	m_edtParkJudgeTime.SetLimitText(LEN_32 - 1);
	m_edtPointNum.SetLimitText(LEN_8);
	m_edtPointNum.SetLimitText(LEN_2);

	CTime timeNow = CTime::GetCurrentTime();
	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(),0, 0, 0);

	for (int i=0; i<TIME_SUM; i++)
	{
		m_dtpTimeStart[i].SetFormat(_T("HH:mm"));
		m_dtpTimeEnd[i].SetFormat(_T("HH:mm"));
		m_dtpTimeStart[i].SetTime(&timeNow);
		m_dtpTimeEnd[i].SetTime(&timeNow);
	}

	UpdateUIText();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_IllegalPark::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_IllegalPark::OnLanguageChanged()
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_IllegalPark::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_ILLPARK_USE, IDS_START);
	SetDlgItemTextEx(IDC_CHK_ILLPARK_EVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_STC_ILLPARK_PRESET, IDS_CONFIG_8D1_PRESET);
	SetDlgItemTextEx(IDC_STC_ILLPARK_AREA_NUM, IDS_VCAEVENT_AREA_NUM);
	SetDlgItemTextEx(IDC_STC_ILLPARK_AREA_NAME, IDS_ITS_REGION_NAME);
	SetDlgItemTextEx(IDC_STC_ILLPARK_NOPARK_TIME, IDS_VCAEVENT_NOPARK_TIME);
	SetDlgItemTextEx(IDC_STC_ILLPARK_SENSITIVITY, IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_ILLPARK_PARK_JUDGE_TIME, IDS_VCAEVENT_PARK_JUDGE_TIME);
	SetDlgItemTextEx(IDC_STC_ILLPARK_TIME_1, IDS_CONFIG_DNVR_ALMSCH_TIME1);
	SetDlgItemTextEx(IDC_STC_ILLPARK_TIME_2, IDS_CONFIG_DNVR_ALMSCH_TIME2);
	SetDlgItemTextEx(IDC_STC_ILLPARK_TIME_3, IDS_CONFIG_DNVR_ALMSCH_TIME3);
	SetDlgItemTextEx(IDC_STC_ILLPARK_TIME_4, IDS_CONFIG_DNVR_ALMSCH_TIME4);
	SetDlgItemTextEx(IDC_STC_ILLPARK_POINTS, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_BTN_ILLPARK_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_ILLPARK_SET, IDS_SET);
	SetDlgItemTextEx(IDC_CHK_ILLPARK_PARK_CAPTURE, IDS_VCAEVENT_PARK_CAPTURE);
	SetDlgItemTextEx(IDC_STC_ILLPARK_POINT_NUM, IDS_VCAEVENT_POINT_NUM);

	m_cboPreset.ResetContent();
	const CString cstPreset[] = {"1","2","3","4","5","6","7","8"};
	for (int i = 0; i < sizeof(cstPreset)/sizeof(CString); i ++)
	{
		m_cboPreset.InsertString(i, cstPreset[i]);
	}
	m_cboPreset.SetCurSel(0);

	m_cboAreaNum.ResetContent();
	const CString cstAreaNum[] = {"1","2","3","4"};
	for (int i = 0; i < sizeof(cstAreaNum)/sizeof(CString); i ++)
	{
		m_cboAreaNum.InsertString(i, cstAreaNum[i]);
	}
	m_cboAreaNum.SetCurSel(0);

	m_cboSensitivity.ResetContent();
	const CString cstSensitivity[] = {GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_LOW),
									GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_MIDDLE),
									GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_HIGH)};
	for (int i = 0; i < sizeof(cstSensitivity)/sizeof(CString); i ++)
	{
		m_cboSensitivity.InsertString(i, cstSensitivity[i]);
	}
	m_cboSensitivity.SetCurSel(0);

}

void CLS_VCAEVENT_IllegalPark::CleanText()
{
	m_edtPoints.Clear();
}

void CLS_VCAEVENT_IllegalPark::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_IllegalPark::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	ITS_IllegalPark iip = {0};

	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARK_CMD_SET, m_iChannelNO, &iip, sizeof(ITS_IllegalPark));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_IllegalPark::NetClient_GetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkUse.SetCheck(iip.iEnable);
		m_chkEventValid.SetCheck(iip.iValid);
		m_cboPreset.SetCurSel(iip.iPresetNo);
		m_cboAreaNum.SetCurSel(iip.iAreaNo);
		SetDlgItemText(IDC_EDT_ILLPARK_AREA_NAME, iip.cAreaName);
		SetDlgItemInt(IDC_EDT_ILLPARK_NOPARK_TIME, iip.iIllegalParkTime);
		m_cboSensitivity.SetCurSel(iip.iSensitivity);
		SetDlgItemInt(IDC_EDT_ILLPARK_PARK_JUDGE_TIME, iip.iCheckParkTime);
		SetDlgItemInt(IDC_EDT_ILLPARK_POINT_NUM, iip.iPointCounts);

		int iCapture = iip.iCapEnable & 0x0001;
		m_chkParkCapture.SetCheck(iCapture);

		CString szPointBuf;
		for (int i =0; i < iip.iPointCounts; i++)
		{
			szPointBuf.AppendFormat("(%d,%d)", iip.arrPTArea[i].x, iip.arrPTArea[i].y);	
		}
		m_edtPoints.SetWindowText(szPointBuf);

		int iTime = 0;
		int iStratHour = 0;
		int iStratMinute = 0; 
		int iEndHour = 0;
		int iEndMinute = 0;

		for (int i = 0; i < TIME_SUM; i ++)
		{
			CTime timeNow = CTime::GetCurrentTime();
			timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 0, 0, 0);

			iTime = iip.iTimeRange[i];
			iStratHour = ((iTime>>24) & 0xFF);
			iStratMinute = ((iTime>>16) & 0xFF);
			iEndHour = ((iTime>>8) & 0xFF);
			iEndMinute = ((iTime) & 0xFF);

			timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iStratHour, iStratMinute, 0);
			m_dtpTimeStart[i].SetTime(&timeNow);
			timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iEndHour, iEndMinute, 0);
			m_dtpTimeEnd[i].SetTime(&timeNow);	
		}	      
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_IllegalPark::NetClient_GetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

//设置
void CLS_VCAEVENT_IllegalPark::OnBnClickedBtnIllparkSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_IllegalPark::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	ITS_IllegalPark iip = {0};

	iip.iPresetNo = m_cboPreset.GetCurSel();
	iip.iAreaNo = m_cboAreaNum.GetCurSel();
	iip.iIllegalParkTime = GetDlgItemInt(IDC_EDT_ILLPARK_NOPARK_TIME);

	for (int i=0; i<MAX_TIMESEGMENT; i++)
	{
		iip.iTimeRange[i] = 0;
	}

	CTime timeNow = CTime::GetCurrentTime();
	for(int i = 0; i < TIME_SUM; i ++)
	{
		m_dtpTimeStart[i].GetTime(timeNow);
		iip.iTimeRange[i] |= (timeNow.GetHour()<<24);
		iip.iTimeRange[i] |= (timeNow.GetMinute()<<16);
		m_dtpTimeEnd[i].GetTime(timeNow);
		iip.iTimeRange[i] |= (timeNow.GetHour()<<8);
		iip.iTimeRange[i] |= (timeNow.GetMinute());
	}

	int iPointNum = GetDlgItemInt(IDC_EDT_ILLPARK_POINT_NUM);
	iip.iPointCounts = iPointNum;

	POINT poPoint[MAX_AREA_COUNT] = {0} ;
	CString cstPoints = "";
	GetDlgItemText(IDC_EDT_ILLPARK_POINTS, cstPoints);
	GetPointsFromString(cstPoints, iPointNum, poPoint);

	for (int i=0; i<iPointNum; i++)
	{
		iip.arrPTArea[i] = poPoint[i];
	}

	iip.iCheckParkTime = GetDlgItemInt(IDC_EDT_ILLPARK_PARK_JUDGE_TIME);
	iip.iSensitivity = m_cboSensitivity.GetCurSel();

	char cTmpAreaName[LEN_32] = {0};
	GetDlgItemText(IDC_EDT_ILLPARK_AREA_NAME, cTmpAreaName, LEN_32);
	memcpy(iip.cAreaName, cTmpAreaName, LEN_32);

	iip.iEnable = m_chkUse.GetCheck();
	iip.iValid = m_chkEventValid.GetCheck();
	iip.iRuleID = m_iRuleID;
	iip.iCapEnable = m_chkParkCapture.GetCheck();

	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARK_CMD_SET, m_iChannelNO, &iip, sizeof(iip));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_IllegalPark::NetClient_SetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_IllegalPark::NetClient_SetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}


//绘制
void CLS_VCAEVENT_IllegalPark::OnBnClickedBtnIllparkDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return ;
		}
	}

	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_perimeter);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		delete m_pDlgVideoView;
		m_pDlgVideoView = NULL;
		return ;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtPoints.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDT_ILLPARK_POINT_NUM, iPointNum);
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_IllegalPark::OnCbnSelchangeCboIllparkPreset()
{
	UpdataChangePresetAreaNum();
}

void CLS_VCAEVENT_IllegalPark::OnCbnSelchangeCboIllparkAreaNum()
{
	UpdataChangePresetAreaNum();
}


void CLS_VCAEVENT_IllegalPark::UpdataChangePresetAreaNum()
{
	ITS_IllegalPark iip = {0};

	iip.iPresetNo = m_cboPreset.GetCurSel();
	iip.iAreaNo = m_cboAreaNum.GetCurSel();

	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARK_CMD_SET, m_iChannelNO, &iip, sizeof(ITS_IllegalPark));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_IllegalPark::NetClient_GetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkUse.SetCheck(iip.iEnable);
		m_chkEventValid.SetCheck(iip.iValid);

		SetDlgItemText(IDC_EDT_ILLPARK_AREA_NAME, iip.cAreaName);
		SetDlgItemInt(IDC_EDT_ILLPARK_NOPARK_TIME, iip.iIllegalParkTime);
		m_cboSensitivity.SetCurSel(iip.iSensitivity);
		SetDlgItemInt(IDC_EDT_ILLPARK_PARK_JUDGE_TIME, iip.iCheckParkTime);
		SetDlgItemInt(IDC_EDT_ILLPARK_POINT_NUM, iip.iPointCounts);

		int iCapture = iip.iCapEnable & 0x0001;
		m_chkParkCapture.SetCheck(iCapture);

		CString szPointBuf;
		for (int i =0; i < iip.iPointCounts; i++)
		{
			szPointBuf.AppendFormat("(%d,%d)", iip.arrPTArea[i].x, iip.arrPTArea[i].y);	
		}
		m_edtPoints.SetWindowText(szPointBuf);

		int iTime = 0;
		int iStratHour = 0;
		int iStratMinute = 0; 
		int iEndHour = 0;
		int iEndMinute = 0;

		for (int i = 0; i < TIME_SUM; i ++)
		{
			CTime timeNow = CTime::GetCurrentTime();
			timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 0, 0, 0);

			iTime = iip.iTimeRange[i];
			iStratHour = ((iTime>>24) & 0xFF);
			iStratMinute = ((iTime>>16) & 0xFF);
			iEndHour = ((iTime>>8) & 0xFF);
			iEndMinute = ((iTime) & 0xFF);

			timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iStratHour, iStratMinute, 0);
			m_dtpTimeStart[i].SetTime(&timeNow);
			timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iEndHour, iEndMinute, 0);
			m_dtpTimeEnd[i].SetTime(&timeNow);	
		}	      
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_IllegalPark::NetClient_GetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET] (%d, %d)", m_iLogonID, m_iChannelNO);
	}

}
void CLS_VCAEVENT_IllegalPark::OnEnChangeEdtIllparkPointNum()
{
	int iTemp = GetDlgItemInt(IDC_EDT_ILLPARK_POINT_NUM);
	if (iTemp > 15)
	{
		SetDlgItemInt(IDC_EDT_ILLPARK_POINT_NUM, POINT_RANGE);
	}
}
