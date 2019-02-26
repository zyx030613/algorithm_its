#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Hover.h"

#define POINT_SUM					4		
#define MIN_TIME_RANGE_FROM			5000
#define MIN_TIME_RANGE_TO			600000
#define MIN_TIME_DEFAULT			10000
#define	SENSITI_RANGE_FROM			0
#define SENSITI_RANGE_TO			100
#define	AREA_RANGE_FROM				0
#define AREA_RANGE_TO				100
#define AREA_DEFAULT				5
#define	HOVER_DIST_RANGE_FROM		0
#define HOVER_DIST_RANGE_TO			100

#define DEFAULT_ZERO				0
#define LEN_6						6

// CLS_VCAEVENT_Hover ¶Ô»°¿ò

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Hover, CDialog)

CLS_VCAEVENT_Hover::CLS_VCAEVENT_Hover(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Hover::IDD, pParent)
{

}

CLS_VCAEVENT_Hover::~CLS_VCAEVENT_Hover()
{
}

void CLS_VCAEVENT_Hover::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_HOVER_EVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CHK_HOVER_SHOW_ALARM_RULE, m_chkAlarmRule);
	DDX_Control(pDX, IDC_CHK_HOVER_SHOW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CHK_HOVER_SHOW_TARGET_BOX, m_chkTargetBox);
	DDX_Control(pDX, IDC_EDT_HOVER_HOVER_MIN_TIME, m_edtHoverMinTime);
	DDX_Control(pDX, IDC_EDT_HOVER_SENSITIVITY, m_edtSensitivity);
	DDX_Control(pDX, IDC_EDT_HOVER_MIN_DIST, m_edtHoverMinDist);
	DDX_Control(pDX, IDC_CBO_HOVER_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_HOVER_UNALARM_COLOR, m_cboUnalarmColor);
	DDX_Control(pDX, IDC_EDT_HOVER_RECTANGLE_AREA, m_edtRectArea);
	DDX_Control(pDX, IDC_EDT_HOVER_AREA, m_edtPointArea);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Hover, CDialog)
	ON_EN_CHANGE(IDC_EDT_HOVER_HOVER_MIN_TIME, &CLS_VCAEVENT_Hover::OnEnChangeEdtHoverHoverMinTime)
	ON_BN_CLICKED(IDC_BTN_HOVER_SET, &CLS_VCAEVENT_Hover::OnBnClickedBtnHoverSet)
	ON_BN_CLICKED(IDC_BTN_HOVER_DRAW, &CLS_VCAEVENT_Hover::OnBnClickedBtnHoverDraw)
	ON_EN_CHANGE(IDC_EDT_HOVER_SENSITIVITY, &CLS_VCAEVENT_Hover::OnEnChangeEdtHoverSensitivity)
	ON_EN_CHANGE(IDC_EDT_HOVER_MIN_DIST, &CLS_VCAEVENT_Hover::OnEnChangeEdtHoverMinDist)
	ON_EN_CHANGE(IDC_EDT_HOVER_RECTANGLE_AREA, &CLS_VCAEVENT_Hover::OnEnChangeEdtHoverRectangleArea)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_VCAEVENT_Hover::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_Hover::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_Hover::OnLanguageChanged()
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_Hover::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_HOVER_EVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_HOVER_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_HOVER_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_HOVER_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_HOVER_HOVER_MIN_TIME, IDS_VCAEVENT_HOVER_MIN_TIME);
	SetDlgItemTextEx(IDC_STC_HOVER_SENSITIVITY, IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_HOVER_MIN_DIST, IDS_VCAEVENT_HOVER_MIN_DIST);
	SetDlgItemTextEx(IDC_STC_HOVER_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_HOVER_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_HOVER_AREA, IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_BTN_HOVER_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_HOVER_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STC_HOVER_RECTANGLE_AREA, IDS_VCAEVENT_OUTER_RECTANGLE_AREA);

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

	m_edtHoverMinTime.SetLimitText(LEN_6);
	SetDlgItemInt(IDC_EDT_HOVER_HOVER_MIN_TIME, MIN_TIME_DEFAULT);
	SetDlgItemInt(IDC_EDT_HOVER_SENSITIVITY, DEFAULT_ZERO);
	SetDlgItemInt(IDC_EDT_HOVER_MIN_DIST, DEFAULT_ZERO);
	SetDlgItemInt(IDC_EDT_HOVER_RECTANGLE_AREA, AREA_DEFAULT);
}

void CLS_VCAEVENT_Hover::CleanText()
{
	m_edtPointArea.Clear();
}

void CLS_VCAEVENT_Hover::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Hover::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCALinger vl = {0};

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_LINGER, m_iChannelNO, &vl, sizeof(VCALinger));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Hover::NetClient_VCAGetConfig[VCA_CMD_LINGER] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkEventValid.SetCheck(vl.stRule.iValid);
		m_chkAlarmRule.SetCheck(vl.stDisplayParam.iDisplayRule);
		m_chkAlarmStat.SetCheck(vl.stDisplayParam.iDisplayStat);
		m_chkTargetBox.SetCheck(vl.iDisplayTarget);

		SetDlgItemInt(IDC_EDT_HOVER_HOVER_MIN_TIME, vl.iMinTime);
		SetDlgItemInt(IDC_EDT_HOVER_SENSITIVITY, vl.iSensitivity);
		SetDlgItemInt(IDC_EDT_HOVER_MIN_DIST, vl.iMinRange);
		SetDlgItemInt(IDC_EDT_HOVER_AREA, vl.iMinBoundy);

		m_cboAlarmColor.SetCurSel(vl.stDisplayParam.iAlarmColor);
		m_cboUnalarmColor.SetCurSel(vl.stDisplayParam.iColor);

		int iPointNum = vl.stRegion.iPointNum;
		CString cstPointBuf = "";
		for (int i=0; i<iPointNum; i++)
		{
			cstPointBuf.AppendFormat("(%d,%d)", vl.stRegion.stPoints[i].iX, vl.stRegion.stPoints[i].iY);
		}
		m_edtPointArea.SetWindowText(cstPointBuf);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Hover::NetClient_VCAGetConfig[VCA_CMD_LINGER] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_Hover::OnBnClickedBtnHoverSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Hover::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCALinger vl = {0};

	vl.iDisplayTarget = m_chkTargetBox.GetCheck();
	vl.iMinBoundy = GetDlgItemInt(IDC_EDT_HOVER_AREA);
	vl.iMinRange = GetDlgItemInt(IDC_EDT_HOVER_MIN_DIST);
	vl.iMinTime = GetDlgItemInt(IDC_EDT_HOVER_HOVER_MIN_TIME);
	vl.iSensitivity = GetDlgItemInt(IDC_EDT_HOVER_SENSITIVITY);
	vl.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel();
	vl.stDisplayParam.iColor = m_cboUnalarmColor.GetCurSel();
	vl.stDisplayParam.iDisplayRule = m_chkAlarmRule.GetCheck();
	vl.stDisplayParam.iDisplayStat = m_chkAlarmStat.GetCheck();
	vl.stRule.iRuleID = m_iRuleID;
	vl.stRule.iSceneID = m_iSceneID;
	vl.stRule.iValid = m_chkEventValid.GetCheck();

	vl.stRegion.iPointNum = POINT_SUM;
	CString strPoint;
	GetDlgItemText(IDC_EDT_HOVER_AREA, strPoint);
	GetPolyFromString(strPoint, POINT_SUM, vl.stRegion);

	vl.iBufSize = sizeof(vl);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_LINGER, m_iChannelNO, &vl, sizeof(VCALinger));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Hover::NetClient_VCASetConfig[VCA_CMD_LINGER] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Hover::NetClient_VCASetConfig[VCA_CMD_LINGER] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_Hover::OnBnClickedBtnHoverDraw()
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
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
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
		m_edtPointArea.SetWindowText(cPointBuf);
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;

}

void CLS_VCAEVENT_Hover::OnEnChangeEdtHoverHoverMinTime()
{
	int iTemp = GetDlgItemInt(IDC_EDT_HOVER_HOVER_MIN_TIME);
	if (iTemp < MIN_TIME_RANGE_FROM)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Hover::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
	if (iTemp > MIN_TIME_RANGE_TO)
	{
		SetDlgItemInt(IDC_EDT_HOVER_HOVER_MIN_TIME, MIN_TIME_RANGE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Hover::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Hover::OnEnChangeEdtHoverSensitivity()
{
	int iTemp = GetDlgItemInt(IDC_EDT_HOVER_SENSITIVITY);
	if (iTemp < SENSITI_RANGE_FROM || iTemp > SENSITI_RANGE_TO)
	{
		SetDlgItemInt(IDC_EDT_HOVER_SENSITIVITY, SENSITI_RANGE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Hover::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Hover::OnEnChangeEdtHoverMinDist()
{
	int iTemp = GetDlgItemInt(IDC_EDT_HOVER_MIN_DIST);
	if (iTemp < HOVER_DIST_RANGE_FROM || iTemp > HOVER_DIST_RANGE_TO)
	{
		SetDlgItemInt(IDC_EDT_HOVER_MIN_DIST, HOVER_DIST_RANGE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Hover::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Hover::OnEnChangeEdtHoverRectangleArea()
{
	int iTemp = GetDlgItemInt(IDC_EDT_HOVER_RECTANGLE_AREA);
	if (iTemp < AREA_RANGE_FROM || iTemp > AREA_RANGE_TO)
	{
		SetDlgItemInt(IDC_EDT_HOVER_RECTANGLE_AREA, AREA_RANGE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Hover::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}
