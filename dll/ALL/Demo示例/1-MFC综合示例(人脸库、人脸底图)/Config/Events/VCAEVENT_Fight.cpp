// VCAEVENT_Fight.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Fight.h"


// CLS_VCAEVENT_Fight dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Fight, CDialog)

CLS_VCAEVENT_Fight::CLS_VCAEVENT_Fight(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Fight::IDD, pParent)
{

}

CLS_VCAEVENT_Fight::~CLS_VCAEVENT_Fight()
{
}

void CLS_VCAEVENT_Fight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_FIGHT_RULE_DISPLAY, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHK_FIGHT_DISPLAY_STATE, m_chkDisplayAlarmNum);
	DDX_Control(pDX, IDC_CBO_FIGHT_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_FIGHT_AREA_COLOR, m_cboAreaColor);
	DDX_Control(pDX, IDC_EDT_FIGHT_SENSITIVITY, m_edtSensitivity);
	DDX_Control(pDX, IDC_EDT_FIGHT_ALARMTIME, m_edtAlarmTime);
	DDX_Control(pDX, IDC_EDT_FIGHT_POINTNUM, m_edtPointsNum);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Fight, CDialog)
	ON_BN_CLICKED(IDC_BTN_FIGHT_POINTS_DRAW, &CLS_VCAEVENT_Fight::OnBnClickedBtnFightPointsDraw)
	ON_BN_CLICKED(IDC_BTN_FIGHT_SET, &CLS_VCAEVENT_Fight::OnBnClickedBtnFightSet)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_VCAEVENT_Fight message handlers

BOOL CLS_VCAEVENT_Fight::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialogText();
	UI_UpdateFightArithmetic();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_Fight::OnLanguageChanged()
{
	UI_UpdateDialogText();
	UI_UpdateFightArithmetic();
}

void CLS_VCAEVENT_Fight::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STC_FIGHT_AREA_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_FIGHT_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_CHK_FIGHT_RULE_DISPLAY, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHK_FIGHT_DISPLAY_STATE, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STC_FIGHT_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STC_FIGHT_POINTS, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_STC_FIGHT_ALARMTIME, IDS_VCA_ALARMTIME);
	SetDlgItemTextEx(IDC_STC_FIGHT_SENSITIVITY, IDS_VCA_SENSITIVITY);
	SetDlgItemTextEx(IDC_BTN_FIGHT_POINTS_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_FIGHT_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_FIGHT_SENSITIVITY, IDS_STC_FIGHT_SENSITIVITY);

	CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), 
		GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_BLUE), 
		GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), 
		GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboAreaColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAreaColor.InsertString(i, strColor[i]);
		m_cboAlarmColor.InsertString(i, strColor[i]);
	}
}

void CLS_VCAEVENT_Fight::UI_UpdateFightArithmetic()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable )
		return;

	FightArithmetic st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;
	int iCmd = VCA_CMD_FIGHT;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet == 0)
	{
		m_chkDisplayRule.SetCheck(st.stDisplayParam.iDisplayRule);
		m_chkDisplayAlarmNum.SetCheck(st.stDisplayParam.iDisplayStat);
		m_cboAreaColor.SetCurSel(st.stDisplayParam.iColor - 1);
		m_cboAlarmColor.SetCurSel(st.stDisplayParam.iAlarmColor - 1);
		SetDlgItemInt(IDC_EDT_FIGHT_SENSITIVITY,st.iSensitivity);
		SetDlgItemInt(IDC_EDT_FIGHT_ALARMTIME,st.iAlarmTime);
		SetDlgItemInt(IDC_EDT_FIGHT_POINTNUM,st.stPoints.iPointNum);
		int _iPointNum = st.stPoints.iPointNum;
		CString strPointArray;
		CString strPoint[VCA_MAX_POLYGON_POINT_NUMEX];
		for(int i = 0; i != _iPointNum; i++)
		{
			strPoint[i].Format("(%d,%d)", st.stPoints.stPoints[i].iX, st.stPoints.stPoints[i].iY);
			strPointArray += strPoint[i];
		}
		SetDlgItemText(IDC_EDT_FIGHT_POINTS,strPointArray);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_VCAGetConfig(%d,%d,%d)",m_iLogonID, iCmd,m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}
}

void CLS_VCAEVENT_Fight::OnBnClickedBtnFightPointsDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
	}

	/*以下代码为了能从draw对话框中取出相应参数*/
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
		return;
	}

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		GetDlgItem(IDC_EDT_FIGHT_POINTS)->SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDT_FIGHT_POINTNUM, iPointNum);
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Fight::OnBnClickedBtnFightSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable )
		return;

	FightArithmetic st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;
	st.stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	st.stDisplayParam.iDisplayStat = m_chkDisplayAlarmNum.GetCheck();
	st.stDisplayParam.iColor = m_cboAreaColor.GetCurSel() + 1;
	st.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel() + 1;
	st.iSensitivity = GetDlgItemInt(IDC_EDT_FIGHT_SENSITIVITY);
	st.iAlarmTime = GetDlgItemInt(IDC_EDT_FIGHT_ALARMTIME);
	st.stPoints.iPointNum = GetDlgItemInt(IDC_EDT_FIGHT_POINTNUM);

	CString strPointStr;
	vca_TPolygon stRegion = {0};
	GetDlgItemText(IDC_EDT_FIGHT_POINTS, strPointStr);
	GetPolyFromString(strPointStr, st.stPoints.iPointNum, stRegion);
	memcpy(&st.stPoints, &stRegion, sizeof(stRegion));
	int iCmd = VCA_CMD_FIGHT;
	iRet = NetClient_VCASetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet >= 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_VCASetConfig(%d,%d,%d)",m_iLogonID, iCmd,m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Fight::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	UI_UpdateDialogText();
	UI_UpdateFightArithmetic();
}
