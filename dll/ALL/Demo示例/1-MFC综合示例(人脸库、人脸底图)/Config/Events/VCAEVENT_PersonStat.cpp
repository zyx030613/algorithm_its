// VCAEVENT_PersonStat.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_PersonStat.h"

#define POINT_NUM_MIN			2			//点数最小值
#define POINT_NUM_MAX			15			//点数最大值
#define LEN_1					1
#define LEN_2					2
#define LEN_3					3
#define MIN_SIZE_FROM			0
#define MIN_SIZE_TO				100
#define MAX_SIZE_FROM			0
#define	MAX_SIZE_TO				100


// CLS_VCAEVENT_PersonStat 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_PersonStat, CDialog)

CLS_VCAEVENT_PersonStat::CLS_VCAEVENT_PersonStat(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_PersonStat::IDD, pParent)
{

}

CLS_VCAEVENT_PersonStat::~CLS_VCAEVENT_PersonStat()
{
}

void CLS_VCAEVENT_PersonStat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_PER_STAT_EVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CHK_PER_STAT_SHOW_ALARM_RULE, m_chkAlarmRule);
	DDX_Control(pDX, IDC_CHK_PER_STAT_SHOW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CHK_PER_STAT_SHOW_TARGET_BOX, m_chkTargetBox);
	DDX_Control(pDX, IDC_CBO_PER_STAT_DETECT_STYLE, m_cboDetectStyle);
	DDX_Control(pDX, IDC_CBO_PER_STAT_DETECT_MODE, m_cboDetectMode);
	DDX_Control(pDX, IDC_CBO_PER_STAT_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_PER_STAT_UNALARM_COLOR, m_cboUnalarmColor);
	DDX_Control(pDX, IDC_CBO_PER_STAT_POINT_NUM_IN_POLYGON, m_cboPolygonPointNum);
	DDX_Control(pDX, IDC_EDT_PER_STAT_POLYGON_AREA, m_edtPolygonArea);
	DDX_Control(pDX, IDC_EDT_PER_STAT_LINE_AREA, m_edtLineArea);
	DDX_Control(pDX, IDC_EDT_PER_STAT_SENSITIVITY, m_edtSensitivity);
	DDX_Control(pDX, IDC_EDT_PER_STAT_AIM_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_PER_STAT_AIM_MAX_SIZE, m_edtMaxSize);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_PersonStat, CDialog)
	ON_BN_CLICKED(IDC_BTN_PER_STAT_SET, &CLS_VCAEVENT_PersonStat::OnBnClickedBtnPerStatSet)
	ON_BN_CLICKED(IDC_STC_PER_BTN_POLYGON_AREA_DRAW, &CLS_VCAEVENT_PersonStat::OnBnClickedStcPerBtnPolygonAreaDraw)
	ON_BN_CLICKED(IDC_BTN_PER_STAT_LINE_AREA_DRAW, &CLS_VCAEVENT_PersonStat::OnBnClickedBtnPerStatLineAreaDraw)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_EDT_PER_STAT_SENSITIVITY, &CLS_VCAEVENT_PersonStat::OnEnChangeEdtPerStatSensitivity)
	ON_EN_CHANGE(IDC_EDT_PER_STAT_AIM_MIN_SIZE, &CLS_VCAEVENT_PersonStat::OnEnChangeEdtPerStatAimMinSize)
	ON_EN_CHANGE(IDC_EDT_PER_STAT_AIM_MAX_SIZE, &CLS_VCAEVENT_PersonStat::OnEnChangeEdtPerStatAimMaxSize)
	ON_CBN_SELCHANGE(IDC_CBO_PER_STAT_DETECT_STYLE, &CLS_VCAEVENT_PersonStat::OnCbnSelchangeCboPerStatDetectStyle)
END_MESSAGE_MAP()


// CLS_VCAEVENT_PersonStat 消息处理程序



void CLS_VCAEVENT_PersonStat::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if(bShow)
	{
		UpdatePageUI();
	}
}

BOOL CLS_VCAEVENT_PersonStat::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	m_edtSensitivity.SetLimitText(LEN_1);
	m_edtMaxSize.SetLimitText(LEN_3);
	m_edtMinSize.SetLimitText(LEN_2);

	m_iLineAreaPointNum = 0;
	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLS_VCAEVENT_PersonStat::OnLanguageChanged()
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_PersonStat::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_PER_STAT_EVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_PER_STAT_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_PER_STAT_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_PER_STAT_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_PER_STAT_DETECT_STYLE, IDS_VCAEVENT_DETECT_STYLE);
	SetDlgItemTextEx(IDC_STC_PER_STAT_DETECT_MODE, IDS_CONFIG_ITS_TIMERANGE_DETECTMODE);
	SetDlgItemTextEx(IDC_STC_PER_STAT_SENSITIVITY, IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_PER_STAT_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_PER_STAT_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_PER_STAT_AIM_MIN_SIZE, IDS_VCA_ADV_MINSIZE);
	SetDlgItemTextEx(IDC_STC_PER_STAT_AIM_MAX_SIZE, IDS_VCA_ADV_MAXSIZE);
	SetDlgItemTextEx(IDC_STC_PER_STAT_POINT_NUM_IN_POLYGON, IDS_VCAEVENT_POLYGON_POINT_NUM);
	SetDlgItemTextEx(IDC_STC_PER_STAT_POLYGON_AREA, IDS_VCAEVENT_POLYGON);
	SetDlgItemTextEx(IDC_STC_PER_STAT_LINE_AREA, IDS_VCAEVENT_TRIP_LINE_AREA);
	SetDlgItemTextEx(IDC_STC_PER_BTN_POLYGON_AREA_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_PER_STAT_LINE_AREA_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_PER_STAT_SET, IDS_SET);

	m_cboDetectStyle.ResetContent();
	const CString cstDetectStyle[] = {GetTextEx(IDS_VCAEVENT_DETECT_AREA),
		GetTextEx(IDS_VCAEVENT_DETECT_LINE)};
	for (int i = 0; i < sizeof(cstDetectStyle)/sizeof(CString); i++)
	{
		m_cboDetectStyle.InsertString(i, cstDetectStyle[i]);
	}
	m_cboDetectStyle.SetCurSel(0);

	m_cboDetectMode.ResetContent();
	const CString cstDetectMode[] = {GetTextEx(IDS_VCAEVENT_VERTICAL_PERSON_STAT),
		GetTextEx(IDS_VCAEVENT_LEVEL_PERSON_STAT)};
	for (int i = 0; i < sizeof(cstDetectMode)/sizeof(CString); i++)
	{
		m_cboDetectMode.InsertString(i, cstDetectMode[i]);
	}
	m_cboDetectMode.SetCurSel(0);

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), 
		GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_BLUE), 
		GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), 
		GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboUnalarmColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAlarmColor.InsertString(i, strColor[i]);
		m_cboUnalarmColor.InsertString(i, strColor[i]);
	}
	m_cboAlarmColor.SetCurSel(0);
	m_cboUnalarmColor.SetCurSel(0);

	CString cstTemp = "";
	m_cboPolygonPointNum.ResetContent();
	for (int i=(POINT_NUM_MIN - 2); i <= (POINT_NUM_MAX - 2); i++)
	{	
		cstTemp.Format("%d",i + 2);
		m_cboPolygonPointNum.InsertString(i, cstTemp);
	}
	m_cboPolygonPointNum.SetCurSel(0);
}

void CLS_VCAEVENT_PersonStat::CleanText()
{
	m_edtPolygonArea.Clear();
	m_edtLineArea.Clear();
}

void CLS_VCAEVENT_PersonStat::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_PersonStat::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	PersonStatisticArithmetic psa = {0};
	int iBytesReturn = 0;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_PERSON_STATISTIC_ARITHMETIC, m_iChannelNO, &psa, sizeof(PersonStatisticArithmetic), &iBytesReturn);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_PersonStat::NetClient_GetDevConfig[NET_CLIENT_PERSON_STATISTIC_ARITHMETIC] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkTargetBox.SetCheck(psa.iDisplayTarget);
		m_cboDetectStyle.SetCurSel(psa.iDetectType - 1);
		m_cboDetectMode.SetCurSel(psa.iMode - 1);
		
		SetDlgItemInt(IDC_EDT_PER_STAT_SENSITIVITY, psa.iSensitiv);
		SetDlgItemInt(IDC_EDT_PER_STAT_AIM_MIN_SIZE, psa.iTargetMinSize);
		SetDlgItemInt(IDC_EDT_PER_STAT_AIM_MAX_SIZE, psa.iTargetMaxSize);

		m_cboPolygonPointNum.SetCurSel(psa.iPointNum - 2);

		CString cstPolygonBuf = "";
		for(int i=0; i<psa.iPointNum; i++)
		{
			cstPolygonBuf.AppendFormat("(%d, %d)", psa.ptArea[i].x, psa.ptArea[i].y);
		}
		SetDlgItemText(IDC_EDT_PER_STAT_POLYGON_AREA, cstPolygonBuf);

		CString cstLineAreaBuf = "";
		for (int i=0; i<psa.stRegion.iPointNum; i++)
		{
			cstLineAreaBuf.AppendFormat("(%d, %d)", psa.stRegion.stPoints[i].iX, psa.stRegion.stPoints[i].iY);
		}
		SetDlgItemText(IDC_EDT_PER_STAT_LINE_AREA, cstLineAreaBuf);

		if (0 == m_cboDetectStyle.GetCurSel())
		{
			GetDlgItem(IDC_EDT_PER_STAT_POLYGON_AREA)->EnableWindow(TRUE);
			GetDlgItem(IDC_STC_PER_BTN_POLYGON_AREA_DRAW)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDT_PER_STAT_LINE_AREA)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PER_STAT_LINE_AREA_DRAW)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_EDT_PER_STAT_POLYGON_AREA)->EnableWindow(FALSE);
			GetDlgItem(IDC_STC_PER_BTN_POLYGON_AREA_DRAW)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDT_PER_STAT_LINE_AREA)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_PER_STAT_LINE_AREA_DRAW)->EnableWindow(TRUE);
		}
	      
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_PersonStat::NetClient_GetDevConfig[NET_CLIENT_PERSON_STATISTIC_ARITHMETIC] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_PersonStat::OnBnClickedBtnPerStatSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_PersonStat::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}
	if (GetDlgItemInt(IDC_EDT_PER_STAT_AIM_MIN_SIZE) >= GetDlgItemInt(IDC_EDT_PER_STAT_AIM_MAX_SIZE))
	{
			AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_PersonStat::MAX_SIZE Value Must Greater Than MIN_SIZE Value (%d,%d)", m_iLogonID,m_iChannelNO);
	}

	PersonStatisticArithmetic psa = {0};

	psa.iDetectType = m_cboDetectStyle.GetCurSel() + 1;
	psa.iDisplayTarget = m_chkTargetBox.GetCheck();
	psa.iMode = m_cboDetectMode.GetCurSel() + 1;
	psa.iPointNum = m_cboPolygonPointNum.GetCurSel() + 2;
	psa.iSceneID = m_iSceneID;
	psa.iSensitiv = GetDlgItemInt(IDC_EDT_PER_STAT_SENSITIVITY);
	psa.iTargetMaxSize = GetDlgItemInt(IDC_EDT_PER_STAT_AIM_MAX_SIZE);
	psa.iTargetMinSize = GetDlgItemInt(IDC_EDT_PER_STAT_AIM_MIN_SIZE);

	POINT ptPolygon[MAX_FACE_DETECT_AREA_COUNT] = {0} ;
	CString cstPolygon = "";
	GetDlgItemText(IDC_EDT_PER_STAT_POLYGON_AREA, cstPolygon);
	GetPointsFromString(cstPolygon, psa.iPointNum, ptPolygon);
	for (int i=0; i<psa.iPointNum; i++)
	{
		psa.ptArea[i] = ptPolygon[i];
	}

	CString cstLineArea = "";
	GetDlgItemText(IDC_EDT_PER_STAT_LINE_AREA, cstLineArea);
	GetPolyFromStringEx(cstLineArea, m_iLineAreaPointNum, psa.stRegion);

	psa.iBufSize = sizeof(psa);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_PERSON_STATISTIC_ARITHMETIC, m_iChannelNO, &psa, sizeof(PersonStatisticArithmetic));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_PersonStat::NetClient_SetDevConfig[NET_CLIENT_PERSON_STATISTIC_ARITHMETIC] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_PersonStat::NetClient_SetDevConfig[NET_CLIENT_PERSON_STATISTIC_ARITHMETIC] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_PersonStat::OnBnClickedStcPerBtnPolygonAreaDraw()
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
		if (iPointNum > 1)
		{
			m_edtPolygonArea.SetWindowText(cPointBuf);
			m_cboPolygonPointNum.SetCurSel(iPointNum - 2);
		}
		else
		{
			m_edtPolygonArea.SetWindowText("");
			m_cboPolygonPointNum.SetCurSel(-1);
		}
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_PersonStat::OnBnClickedBtnPerStatLineAreaDraw()
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
	m_pDlgVideoView->SetDrawType(DrawType_tripwire);
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
		m_edtLineArea.SetWindowText(cPointBuf);
		m_iLineAreaPointNum = iPointNum;
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}
void CLS_VCAEVENT_PersonStat::OnEnChangeEdtPerStatSensitivity()
{
	int iTemp = GetDlgItemInt(IDC_EDT_PER_STAT_SENSITIVITY);
	if (iTemp < 0 || iTemp > 5)
	{
		SetDlgItemInt(IDC_EDT_PER_STAT_SENSITIVITY, 5);
	}
}

void CLS_VCAEVENT_PersonStat::OnEnChangeEdtPerStatAimMinSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_PER_STAT_AIM_MIN_SIZE);
	if (iTemp < MIN_SIZE_FROM || iTemp > MIN_SIZE_TO - 1)
	{
		SetDlgItemInt(IDC_EDT_PER_STAT_AIM_MIN_SIZE, MIN_SIZE_TO - 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_PersonStat::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_PersonStat::OnEnChangeEdtPerStatAimMaxSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_PER_STAT_AIM_MAX_SIZE);
	if (iTemp < MAX_SIZE_FROM + 1)
	{
		SetDlgItemInt(IDC_EDT_PER_STAT_AIM_MAX_SIZE, MAX_SIZE_FROM + 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_PersonStat::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
	if (iTemp > MAX_SIZE_TO)
	{
		SetDlgItemInt(IDC_EDT_PER_STAT_AIM_MAX_SIZE, MAX_SIZE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_PersonStat::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_PersonStat::OnCbnSelchangeCboPerStatDetectStyle()
{
	 if (0 == m_cboDetectStyle.GetCurSel())
	 {
		 GetDlgItem(IDC_EDT_PER_STAT_POLYGON_AREA)->EnableWindow(TRUE);
		 GetDlgItem(IDC_STC_PER_BTN_POLYGON_AREA_DRAW)->EnableWindow(TRUE);
		 GetDlgItem(IDC_EDT_PER_STAT_LINE_AREA)->EnableWindow(FALSE);
		 GetDlgItem(IDC_BTN_PER_STAT_LINE_AREA_DRAW)->EnableWindow(FALSE);
	 }
	 else
	 {
		 GetDlgItem(IDC_EDT_PER_STAT_POLYGON_AREA)->EnableWindow(FALSE);
		 GetDlgItem(IDC_STC_PER_BTN_POLYGON_AREA_DRAW)->EnableWindow(FALSE);
		 GetDlgItem(IDC_EDT_PER_STAT_LINE_AREA)->EnableWindow(TRUE);
		 GetDlgItem(IDC_BTN_PER_STAT_LINE_AREA_DRAW)->EnableWindow(TRUE);
	 }
}
