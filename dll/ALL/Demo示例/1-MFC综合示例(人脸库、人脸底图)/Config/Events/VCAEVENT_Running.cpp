// VCAEVENT_Running.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Running.h"

#define LEN_2					2
#define LEN_3					3
#define POINT_SUM				4
#define DEFAULT_ZORO			0
#define DEFAULT_RANGE			100
#define DEFAULT_MIN_SIZE		5
#define DEFAULT_MAX_SIZE		30
// CLS_VCAEVENT_Running 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Running, CDialog)

CLS_VCAEVENT_Running::CLS_VCAEVENT_Running(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Running::IDD, pParent)
{

}

CLS_VCAEVENT_Running::~CLS_VCAEVENT_Running()
{
}

void CLS_VCAEVENT_Running::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_RUN_ENVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CHK_RUN_SHOW_ALARM_RULE, m_chkAlarmRule);
	DDX_Control(pDX, IDC_CHK_RUN_SHOW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CHK_RUN_SHOW_TARGET_BOX, m_chkTargetBox);
	DDX_Control(pDX, IDC_EDT_RUN_MAX_DISTANCE, m_edtMaxDistance);
	DDX_Control(pDX, IDC_EDT_RUN_MIN_DISTANCE, m_edtMinDistance);
	DDX_Control(pDX, IDC_EDT_RUN_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_RUN_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_EDT_RUN_AREA, m_edtAreaDraw);
	DDX_Control(pDX, IDC_CBO_RUN_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_RUN_UNALARM_COLOR, m_cboUnalarmColor);
	DDX_Control(pDX, IDC_CBO_RUN_TARGET_TYPE, m_cboRunTargetType);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Running, CDialog)
	ON_BN_CLICKED(IDC_BTN_RUN_SET, &CLS_VCAEVENT_Running::OnBnClickedBtnRunSet)
	ON_BN_CLICKED(IDC_BTN_RUN_DRAW, &CLS_VCAEVENT_Running::OnBnClickedBtnRunDraw)
	ON_EN_CHANGE(IDC_EDT_RUN_MAX_DISTANCE, &CLS_VCAEVENT_Running::OnEnChangeEdtRunMaxDistance)
	ON_EN_CHANGE(IDC_EDT_RUN_MIN_DISTANCE, &CLS_VCAEVENT_Running::OnEnChangeEdtRunMinDistance)
	ON_EN_CHANGE(IDC_EDT_RUN_MIN_SIZE, &CLS_VCAEVENT_Running::OnEnChangeEdtRunMinSize)
	ON_EN_CHANGE(IDC_EDT_RUN_MAX_SIZE, &CLS_VCAEVENT_Running::OnEnChangeEdtRunMaxSize)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_VCAEVENT_Running 消息处理程序

BOOL CLS_VCAEVENT_Running::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here

	m_edtMaxDistance.SetLimitText(LEN_3);
	SetDlgItemInt(IDC_EDT_RUN_MAX_DISTANCE, DEFAULT_ZORO);
	m_edtMinDistance.SetLimitText(LEN_3);
	SetDlgItemInt(IDC_EDT_RUN_MIN_DISTANCE, DEFAULT_ZORO);
	m_edtMinSize.SetLimitText(LEN_2);
	SetDlgItemInt(IDC_EDT_RUN_MIN_SIZE, DEFAULT_MIN_SIZE);
	m_edtMaxSize.SetLimitText(LEN_3);
	SetDlgItemInt(IDC_EDT_RUN_MAX_SIZE, DEFAULT_MAX_SIZE);

	UpdateUIText();
	UpdatePageUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_Running::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		UpdateUIText();
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_Running::OnLanguageChanged()
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_Running::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_RUN_ENVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_RUN_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_RUN_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_RUN_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_RUN_MAX_DISTANCE, IDS_VCAEVENT_RUN_MAX_DIST);
	SetDlgItemTextEx(IDC_STC_RUN_MIN_DISTANCE, IDS_VCAEVENT_RUN_MIN_DIST);
	SetDlgItemTextEx(IDC_STC_RUN_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_RUN_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_RUN_MIN_SIZE, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STC_RUN_MAX_SIZE, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STC_RUN_AREA, IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_BTN_RUN_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_RUN_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STC_RUN_TARGET_TYPE, IDS_VCA_TARGET_TYPE);
	
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
	
	m_cboRunTargetType.ResetContent();
	m_cboRunTargetType.SetItemData(m_cboRunTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_NONE)), 0);
	m_cboRunTargetType.SetItemData(m_cboRunTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_PEOPLE)), 1);
	m_cboRunTargetType.SetItemData(m_cboRunTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_CAR)), 2);
	m_cboRunTargetType.SetItemData(m_cboRunTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_BOTH)), 3);
	m_cboRunTargetType.SetCurSel(0);
	m_cboAlarmColor.SetCurSel(0);
	m_cboUnalarmColor.SetCurSel(0);
}

void CLS_VCAEVENT_Running::CleanText()
{
	m_edtAreaDraw.Clear();
	m_edtMaxDistance.Clear();
	m_edtMaxSize.Clear();
	m_edtMinDistance.Clear();
	m_edtMinSize.Clear();
}

void CLS_VCAEVENT_Running::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCARunning tVcaRunning = {0};

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_RUNNING, m_iChannelNO, &tVcaRunning, sizeof(VCARunning));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Running::NetClient_VCAGetConfig[VCA_CMD_RUNNING] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkEventValid.SetCheck(tVcaRunning.stRule.iValid);
		m_chkAlarmRule.SetCheck(tVcaRunning.stDisplayParam.iDisplayRule);
		m_chkAlarmStat.SetCheck(tVcaRunning.stDisplayParam.iDisplayStat);
		m_chkTargetBox.SetCheck(tVcaRunning.iDisplayTarget);

		SetDlgItemInt(IDC_EDT_RUN_MAX_DISTANCE, tVcaRunning.iMaxDistance);
		SetDlgItemInt(IDC_EDT_RUN_MIN_DISTANCE, tVcaRunning.iMinDistancePerSec);
		SetDlgItemInt(IDC_EDT_RUN_MIN_SIZE, tVcaRunning.iMiniSize);
		SetDlgItemInt(IDC_EDT_RUN_MAX_SIZE, tVcaRunning.iMaxSize);

		m_cboAlarmColor.SetCurSel(tVcaRunning.stDisplayParam.iAlarmColor);
		m_cboUnalarmColor.SetCurSel(tVcaRunning.stDisplayParam.iColor);
		m_cboRunTargetType.SetCurSel(GetCboSel(&m_cboRunTargetType, tVcaRunning.iTargetTypeCheck));

		int iPointNum = tVcaRunning.stRegion.iPointNum;
		CString cstPoint;
		for(int i = 0; i < iPointNum; i++)
		{
			cstPoint.AppendFormat("(%d,%d)", tVcaRunning.stRegion.stPoints[i].iX, tVcaRunning.stRegion.stPoints[i].iY);
		}
		SetDlgItemText(IDC_EDT_RUN_AREA, cstPoint);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Running::NetClient_VCAGetConfig[VCA_CMD_RUNNING] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

//设置
void CLS_VCAEVENT_Running::OnBnClickedBtnRunSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	if(GetDlgItemInt(IDC_EDT_RUN_MIN_SIZE) >= GetDlgItemInt(IDC_EDT_RUN_MAX_SIZE))
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::MAX_SIZE Value Must Greater Than MIN_SIZE Value (%d,%d)", m_iLogonID,m_iChannelNO);
	}

	VCARunning tVcaRunning = {0};

	tVcaRunning.iDisplayTarget = m_chkTargetBox.GetCheck();
	tVcaRunning.iMaxDistance = GetDlgItemInt(IDC_EDT_RUN_MAX_DISTANCE);
	tVcaRunning.iMinDistancePerSec = GetDlgItemInt(IDC_EDT_RUN_MIN_DISTANCE);
	tVcaRunning.iMiniSize = GetDlgItemInt(IDC_EDT_RUN_MIN_SIZE);
	tVcaRunning.iMaxSize = GetDlgItemInt(IDC_EDT_RUN_MAX_SIZE);

	tVcaRunning.stRule.iRuleID = m_iRuleID;
	tVcaRunning.stRule.iSceneID = m_iSceneID;
	tVcaRunning.stRule.iValid = m_chkEventValid.GetCheck();

	tVcaRunning.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel();
	tVcaRunning.stDisplayParam.iColor = m_cboUnalarmColor.GetCurSel();
	tVcaRunning.stDisplayParam.iDisplayRule = m_chkAlarmRule.GetCheck();
	tVcaRunning.stDisplayParam.iDisplayStat = m_chkAlarmStat.GetCheck();
	tVcaRunning.iTargetTypeCheck = (int)m_cboRunTargetType.GetItemData(m_cboRunTargetType.GetCurSel());
	
	tVcaRunning.stRegion.iPointNum = POINT_SUM;
	CString cstPoint = "";
	vca_TPolygon stRegion = {0};
	GetDlgItemText(IDC_EDT_RUN_AREA, cstPoint);
	GetPolyFromString(cstPoint, tVcaRunning.stRegion.iPointNum, stRegion);
	memcpy(&tVcaRunning.stRegion, &stRegion, sizeof(stRegion));

	tVcaRunning.iBufSize = sizeof(VCARunning);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_RUNNING, m_iChannelNO, &tVcaRunning, sizeof(VCARunning));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Running::NetClient_VCASetConfig[VCA_CMD_RUNNING] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Running::NetClient_VCASetConfig[VCA_CMD_RUNNING] (%d, %d)", m_iLogonID, m_iChannelNO);
	}	
}

//绘制
void CLS_VCAEVENT_Running::OnBnClickedBtnRunDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
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
		return;
	}

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		GetDlgItem(IDC_EDT_RUN_AREA)->SetWindowText(cPointBuf);
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Running::OnEnChangeEdtRunMaxDistance()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MAX_DISTANCE);
	if (iTemp < DEFAULT_ZORO || iTemp > DEFAULT_RANGE)
	{
		SetDlgItemInt(IDC_EDT_RUN_MAX_DISTANCE, DEFAULT_RANGE);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Running::OnEnChangeEdtRunMinDistance()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MIN_DISTANCE);
	if (iTemp < DEFAULT_ZORO || iTemp > DEFAULT_RANGE)
	{
		SetDlgItemInt(IDC_EDT_RUN_MIN_DISTANCE, DEFAULT_RANGE);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Running::OnEnChangeEdtRunMinSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MIN_SIZE);
	if (iTemp < DEFAULT_ZORO || iTemp > DEFAULT_RANGE - 1)
	{
		SetDlgItemInt(IDC_EDT_RUN_MIN_SIZE, DEFAULT_RANGE - 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Running::OnEnChangeEdtRunMaxSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MAX_SIZE);
	if (iTemp < DEFAULT_ZORO + 1)
	{
		SetDlgItemInt(IDC_EDT_RUN_MAX_SIZE, DEFAULT_ZORO + 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
	if (iTemp > DEFAULT_RANGE)
	{
		SetDlgItemInt(IDC_EDT_RUN_MAX_SIZE, DEFAULT_RANGE);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Running::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}
