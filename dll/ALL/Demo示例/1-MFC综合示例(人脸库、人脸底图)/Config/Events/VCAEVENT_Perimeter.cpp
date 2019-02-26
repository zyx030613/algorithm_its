// VCAEVENT_Perimeter.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Perimeter.h"


// CLS_VCAEVENT_Perimeter dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Perimeter, CDialog)

CLS_VCAEVENT_Perimeter::CLS_VCAEVENT_Perimeter(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Perimeter::IDD, pParent)
{

}

CLS_VCAEVENT_Perimeter::~CLS_VCAEVENT_Perimeter()
{
}

void CLS_VCAEVENT_Perimeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DisplayRule, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHECK_DisplayState, m_chkDisplayState);
	DDX_Control(pDX, IDC_COMBO_TargetCheck, m_cboTargetCheck);
	DDX_Control(pDX, IDC_EDIT_MinDis, m_edtMinDis);
	DDX_Control(pDX, IDC_EDIT_MinTime, m_edtMinTime);
	DDX_Control(pDX, IDC_COMBO_Color, m_cboColor);
	DDX_Control(pDX, IDC_COMBO_AlarmColor, m_cboAlarmColor);
	DDX_Control(pDX, IDC_EDIT_Dir, m_edtDirection);
	DDX_Control(pDX, IDC_COMBO_Indentify, m_cboIndentify);
	DDX_Control(pDX, IDC_EDIT_PointNum, m_edtPointNum);
	DDX_Control(pDX, IDC_EDIT_Points, m_edtPoints);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Perimeter, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_Draw, &CLS_VCAEVENT_Perimeter::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_PerimeterSet, &CLS_VCAEVENT_Perimeter::OnBnClickedButtonPerimeterset)
	ON_BN_CLICKED(IDC_BUTTON_PerimeterStop, &CLS_VCAEVENT_Perimeter::OnBnClickedButtonPerimeterstop)
	ON_BN_CLICKED(IDC_BUTTON_PerimeterStart, &CLS_VCAEVENT_Perimeter::OnBnClickedButtonPerimeterstart)
END_MESSAGE_MAP()


// CLS_VCAEVENT_Perimeter message handlers

void CLS_VCAEVENT_Perimeter::UpdatePageUI()
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

	vp->chnParam[m_iChannelNO].iRuleID = m_iRuleID;
	int iCmd = -1;

	// 	iCmd = VCA_CMD_GET_RULE_COMMON;
	// 	iRet = TDVCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	// 	if (iRet >= 0)
	// 	{
	// 		m_chkValid.SetCheck(vp->chnParam[m_iChannelNO].rule[iRuleID].iValid);
	// 	}

	vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID = VCA_EVENT_PERIMETER;

	iCmd = VCA_CMD_GET_RULE2_PERIMETER;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if (vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_PERIMETER)
		{
			return;
		}
		const vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[m_iRuleID];
		const vca_TPerimeter& pm = vp->chnParam[m_iChannelNO].rule[m_iRuleID].events.perimeter;
		if (!tr.iValid || !pm.iValid)
			return;

		m_chkDisplayRule.SetCheck(tr.stDisplayParam.iDisplayRule);
		m_chkDisplayState.SetCheck(tr.stDisplayParam.iDisplayStat);

		m_cboTargetCheck.SetCurSel(pm.iTargetTypeCheck);
		//m_iMinDistance = tw.iMinDistance;
		SetDlgItemInt(IDC_EDIT_MinDis, pm.iMinDistance);
		SetDlgItemInt(IDC_EDIT_MinTime, pm.iMinTime);
		m_cboAlarmColor.SetCurSel(tr.stDisplayParam.iAlarmColor-1);
		m_cboColor.SetCurSel(tr.stDisplayParam.iColor-1);
		SetDlgItemInt(IDC_EDIT_Dir, pm.iDirection);

		//m_chkDirEnable.SetCheck(pm.iType);
		m_cboIndentify.SetCurSel(pm.iMode);
		SetDlgItemInt(IDC_EDIT_PointNum, pm.stRegion.iPointNum);
		CString szPointBuf;
		for (int i = 0; i < pm.stRegion.iPointNum; i ++ )
		{
			szPointBuf.AppendFormat("(%d,%d)", pm.stRegion.stPoints[i].iX, pm.stRegion.stPoints[i].iY);
		}
		m_edtPoints.SetWindowText(szPointBuf);

	}
	else
	{
		// TODO...
	}
}

BOOL CLS_VCAEVENT_Perimeter::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateUIText();
	m_cboAlarmColor.SetCurSel(0);
	m_cboColor.SetCurSel(0);
	m_cboTargetCheck.SetCurSel(0);
	m_cboIndentify.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_Perimeter::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_Perimeter::OnBnClickedButtonDraw()
{
	// TODO: Add your control notification handler code here
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
		//m_pDlgVideoView->Create(IDD_DLG_VIDEOVIEW_DRAWLINES, this);
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
		return;
	}
	/*******************/

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtPoints.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_PointNum, iPointNum);
		SetDlgItemInt(IDC_EDIT_Dir, iDirection);
	}
	else
	{

	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}


void CLS_VCAEVENT_Perimeter::OnBnClickedButtonPerimeterset()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	int iRuleID = m_iRuleID;
	vca_TVCAParam *vp = m_pVcaParam;
	if (NULL == vp)
	{
		AddLog(LOG_TYPE_FAIL, "Error!!", "VCA param is NULL.");
		return;
	}
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->chnParam[m_iChannelNO].iRuleID = iRuleID;
	vca_TRuleParam* pRP = &vp->chnParam[m_iChannelNO].rule[iRuleID];
	pRP->iEventID = VCA_EVENT_PERIMETER;
	vca_TPerimeter *pPm = &(vp->chnParam[m_iChannelNO].rule[iRuleID].events.perimeter);
	//pTm->iValid = m_chkValid.GetCheck();
	pRP->stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	pRP->stDisplayParam.iDisplayStat = m_chkDisplayState.GetCheck();
	pRP->stDisplayParam.iColor = m_cboColor.GetCurSel()+1;
	pRP->stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel()+1;

	//pPm->iType = m_chkDoubleDir.GetCheck();
	pPm->iTargetTypeCheck = m_cboTargetCheck.GetCurSel();
	pPm->iMinDistance = GetDlgItemInt(IDC_EDIT_MinDis);
	pPm->iMinTime = GetDlgItemInt(IDC_EDIT_MinTime);
	pPm->iDirection = GetDlgItemInt(IDC_EDIT_Dir);
	pPm->iMode = m_cboIndentify.GetCurSel();

	int iPointNum = GetDlgItemInt(IDC_EDIT_PointNum);
	pPm->stRegion.iPointNum = iPointNum;
	CString strPointStr;
	GetDlgItemText(IDC_EDIT_Points, strPointStr);
	vca_TLine stLineTmp = {0};
	GetPolyFromString(strPointStr, iPointNum, pPm->stRegion);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE2_PERIMETER, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		//log(1, "[CVCAEventPage::OnBnClickedButtonEventset]TDVCASetConfig tripwire error = %d", GetLastError());
	}
	else
	{
		//重启智能库
		RestartVCALib(m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_Perimeter::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_DisplayRule, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHECK_DisplayState, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STATIC_TargetCheck, IDS_VCA_TARGET_CHECK);
	SetDlgItemTextEx(IDC_STATIC_MinDis, IDS_VCA_MINDISTANCE);
	SetDlgItemTextEx(IDC_STATIC_MinTime, IDS_VCA_MINTIME);
	SetDlgItemTextEx(IDC_STATIC_Color, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_AlarmColor, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_Dir, IDS_VCA_DIRECTION);
	SetDlgItemTextEx(IDC_STATIC_VCA_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_Points, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_BUTTON_Draw, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_STATIC_Indentify, IDS_VCA_CHECK_MODE);	//检测模式
	SetDlgItemTextEx(IDC_BUTTON_PerimeterSet, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_PerimeterStop, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_PerimeterStart, IDS_START);
	m_cboTargetCheck.ResetContent();
	const CString strTarCheck[] = {GetTextEx(IDS_VCA_TARCHK_NONE), GetTextEx(IDS_VCA_TARCHK_PEOPLE), GetTextEx(IDS_VCA_TARCHK_CAR), GetTextEx(IDS_VCA_TARCHK_BOTH)};
	for (int i=0; i<sizeof(strTarCheck)/sizeof(CString); i++)
	{
		m_cboTargetCheck.InsertString(i, strTarCheck[i]);
	}

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), GetTextEx(IDS_VCA_COL_YELLOW), 
		GetTextEx(IDS_VCA_COL_BLUE), GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAlarmColor.InsertString(i, strColor[i]);
		m_cboColor.InsertString(i, strColor[i]);
	}

	const CString strIndentify[] = {GetTextEx(IDS_VCA_INTRUSION), GetTextEx(IDS_VCA_ENTER), GetTextEx(IDS_VCA_LEAVE)};
	m_cboIndentify.ResetContent();
	for (int i=0; i<sizeof(strIndentify)/sizeof(CString); i++)
	{
		m_cboIndentify.InsertString(i, strIndentify[i]);
	}
}

void CLS_VCAEVENT_Perimeter::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_Perimeter::CleanText()
{
	m_chkDisplayRule.SetCheck(0);
	m_chkDisplayState.SetCheck(0);
	m_cboTargetCheck.SetCurSel(-1);
	m_edtMinDis.Clear();
	m_edtMinTime.Clear();
	m_cboColor.SetCurSel(-1);
	m_cboAlarmColor.SetCurSel(-1);
	m_edtDirection.Clear();
	m_cboIndentify.SetCurSel(-1);
	m_edtPointNum.Clear();
	m_edtPoints.Clear();
	SetDlgItemText(IDC_EDIT_MinDis, "");
	SetDlgItemText(IDC_EDIT_MinTime, "");
	SetDlgItemText(IDC_EDIT_PointNum, "");
	SetDlgItemText(IDC_EDIT_Points, "");
	SetDlgItemText(IDC_EDIT_Dir, "");
}
void CLS_VCAEVENT_Perimeter::OnBnClickedButtonPerimeterstop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_Perimeter::OnBnClickedButtonPerimeterstart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
