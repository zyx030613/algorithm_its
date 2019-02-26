// VCAEVENT_LeaveDetect.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_LeaveDetect.h"


// CLS_VCAEVENT_LeaveDetect dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_LeaveDetect, CDialog)

CLS_VCAEVENT_LeaveDetect::CLS_VCAEVENT_LeaveDetect(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_LeaveDetect::IDD, pParent)
{

}

CLS_VCAEVENT_LeaveDetect::~CLS_VCAEVENT_LeaveDetect()
{
}

void CLS_VCAEVENT_LeaveDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_EVENT_LEAVEDETECT_RULE_DISPLAY, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHECK_EVENT_LEAVEDETECT_DIAPALYSTATE, m_chkDiaplayState);
	DDX_Control(pDX, IDC_EDIT_LEAVEDETECT_AREA_NUM, m_edtAreaNum);
	DDX_Control(pDX, IDC_EDIT_AREA1_POINT_NUM, m_edtArea1PointNum);
	DDX_Control(pDX, IDC_EDIT_AREA1_POINTS, m_edtArea1Points);
	DDX_Control(pDX, IDC_EDIT_AREA2_POINTNUM, m_edtArea2PointNum);
	DDX_Control(pDX, IDC_EDIT_AREA2_POINTS, m_edtArea2Points);
	DDX_Control(pDX, IDC_EDIT_AREA3_POINTNUM, m_edtArea3PointNum);
	DDX_Control(pDX, IDC_EDIT_AREA3_POINTS, m_edtArea3Points);
	DDX_Control(pDX, IDC_EDIT_AREA4_POINTNUM, m_edtArea4PointNum);
	DDX_Control(pDX, IDC_EDIT_AREA4_POINTS, m_edtArea4Points);
	DDX_Control(pDX, IDC_EDIT_LeaveAlarmTime, m_edtLeaveAlarmTime);
	DDX_Control(pDX, IDC_EDIT_RuturnClearAlarmTime, m_edtRuturnClearAlarmTime);
	DDX_Control(pDX, IDC_COMBO_LEAVEDETECT, m_cboAreaColor);
	DDX_Control(pDX, IDC_COMBO_LEAVEDETECT_ALARMCOLOR, m_cboAlarmAreaColor);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_LeaveDetect, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_AREA1_DRAW, &CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea1Draw)
	ON_BN_CLICKED(IDC_BUTTON_AREA2_DRAW, &CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea2Draw)
	ON_BN_CLICKED(IDC_BUTTON_AREA3_DRAW, &CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea3Draw)
	ON_BN_CLICKED(IDC_BUTTON_AREA4_DRAW, &CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea4Draw)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEDETECT_SET, &CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonLeavedetectSet)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEDETECT_STOP, &CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonLeavedetectStop)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEDETECT_START, &CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonLeavedetectStart)
END_MESSAGE_MAP()


// CLS_VCAEVENT_LeaveDetect message handlers

BOOL CLS_VCAEVENT_LeaveDetect::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtLeaveAlarmTime.SetLimitText(16);
	m_edtRuturnClearAlarmTime.SetLimitText(16);
	m_edtAreaNum.SetLimitText(16);
	m_edtArea1PointNum.SetLimitText(16);
	m_edtArea1Points.SetLimitText(128);
	m_edtArea2PointNum.SetLimitText(16);
	m_edtArea2Points.SetLimitText(128);
	m_edtArea3PointNum.SetLimitText(16);
	m_edtArea3Points.SetLimitText(128);
	m_edtArea4PointNum.SetLimitText(16);
	m_edtArea4Points.SetLimitText(128);
	SetDlgItemInt(IDC_EDIT_LEAVEDETECT_AREA_NUM, 1);
	SetDlgItemInt(IDC_EDIT_LeaveAlarmTime, 120);
	SetDlgItemInt(IDC_EDIT_RuturnClearAlarmTime, 15);
	m_cboAlarmAreaColor.SetCurSel(0);
	m_cboAreaColor.SetCurSel(0);

	GetDlgItem(IDC_EDIT_LEAVEDETECT_AREA_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_Area2_Point_Num)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_AREA2_POINTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AREA2_POINTNUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AREA2_POINTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_AREA3_POINTNUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_AREA3_POINTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AREA3_POINTNUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AREA3_POINTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_AREA4_POINTNUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_AREA4_POINTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AREA4_POINTNUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AREA4_POINTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AREA2_DRAW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AREA3_DRAW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AREA4_DRAW)->EnableWindow(FALSE);

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_LeaveDetect::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_LeaveDetect::OnLanguageChanged()
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_LeaveDetect::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_EVENT_LEAVEDETECT_RULE_DISPLAY, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHECK_EVENT_LEAVEDETECT_DIAPALYSTATE, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STATI_EVENT_LEAVEDETECT_REGINNUM, IDS_VCA_EVENT_LEAVEDETECT_AREANUM);
	SetDlgItemTextEx(IDC_STATIC_AREA1_POINT_NUM, IDS_VCA_EVENT_LEAVEDETECT_AREA1_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_AREA1_POINTS, IDS_VCA_EVENT_LEAVEDETECT_AREA_POINTS);
	SetDlgItemTextEx(IDC_STATIC_Area2_Point_Num, IDS_VCA_EVENT_LEAVEDETECT_AREA2_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_AREA2_POINTS, IDS_VCA_EVENT_LEAVEDETECT_AREA_POINTS);
	SetDlgItemTextEx(IDC_STATIC_AREA3_POINTNUM, IDS_VCA_EVENT_LEAVEDETECT_AREA3_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_AREA3_POINTS, IDS_VCA_EVENT_LEAVEDETECT_AREA_POINTS);
	SetDlgItemTextEx(IDC_STATIC_AREA4_POINTNUM, IDS_VCA_EVENT_LEAVEDETECT_AREA4_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_AREA4_POINTS, IDS_VCA_EVENT_LEAVEDETECT_AREA_POINTS);
	SetDlgItemTextEx(IDC_BUTTON_AREA1_DRAW, IDS_VCA_EVENT_LEAVEDETECT_POINTS_DRAW);
	SetDlgItemTextEx(IDC_BUTTON_AREA2_DRAW, IDS_VCA_EVENT_LEAVEDETECT_POINTS_DRAW);
	SetDlgItemTextEx(IDC_BUTTON_AREA3_DRAW, IDS_VCA_EVENT_LEAVEDETECT_POINTS_DRAW);
	SetDlgItemTextEx(IDC_BUTTON_AREA4_DRAW, IDS_VCA_EVENT_LEAVEDETECT_POINTS_DRAW);
	SetDlgItemTextEx(IDC_BUTTON_LEAVEDETECT_SET, IDS_VCA_EVENT_LEAVEDETECT_SET);
	SetDlgItemTextEx(IDC_STATIC_LeaveAlarmTime, IDS_VCA_EVENT_LEAVEDETECT_LEAVEALARMTIME);
	SetDlgItemTextEx(IDC_STATIC_RuturnClearAlarmTime, IDS_VCA_EVENT_LEAVEDETECT_RETURNCLEARTIME);
	SetDlgItemTextEx(IDC_STATIC_LEAVE_TIME, IDS_VCA_EVENT_LEAVEDETECT_LEAVE_TIME);
	SetDlgItemTextEx(IDC_STATIC_RETURN_TIME, IDS_VCA_EVENT_LEAVEDETECT_RETURN_TIME);
	SetDlgItemTextEx(IDC_STATIC_LEAVEDETECT_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_ALARM_COLOR, IDS_VCA_ALARM_COLOR);


	SetDlgItemTextEx(IDC_BUTTON_LEAVEDETECT_STOP, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_LEAVEDETECT_START, IDS_START);
	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), 
								GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_BLUE), 
								GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), 
								GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmAreaColor.ResetContent();
	m_cboAreaColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAlarmAreaColor.InsertString(i, strColor[i]);
		m_cboAreaColor.InsertString(i, strColor[i]);
	}
}

void CLS_VCAEVENT_LeaveDetect::CleanText()
{
	m_chkDisplayRule.SetCheck(0);
	m_chkDiaplayState.SetCheck(0);
	m_edtLeaveAlarmTime.Clear();
	m_edtRuturnClearAlarmTime.Clear();
	m_edtAreaNum.Clear();
	m_edtArea1PointNum.Clear();
	m_edtArea1Points.Clear();
	m_edtArea2PointNum.Clear();
	m_edtArea2Points.Clear();
	m_edtArea3PointNum.Clear();
	m_edtArea3Points.Clear();
	m_edtArea4PointNum.Clear();
	m_edtArea4Points.Clear();
	SetDlgItemText(IDC_EDIT_AREA1_POINT_NUM, "");
	SetDlgItemText(IDC_EDIT_AREA1_POINTS, "");
	SetDlgItemText(IDC_EDIT_AREA2_POINTNUM, "");
	SetDlgItemText(IDC_EDIT_AREA2_POINTS, "");
	SetDlgItemText(IDC_EDIT_AREA3_POINTNUM, "");
	SetDlgItemText(IDC_EDIT_AREA3_POINTS, "");
	SetDlgItemText(IDC_EDIT_AREA4_POINTNUM, "");
	SetDlgItemText(IDC_EDIT_AREA4_POINTS, "");
	SetDlgItemInt(IDC_EDIT_LEAVEDETECT_AREA_NUM, 1);
	SetDlgItemText(IDC_EDIT_LeaveAlarmTime, "");
	SetDlgItemText(IDC_EDIT_RuturnClearAlarmTime, "");
	m_cboAreaColor.SetCurSel(-1);
	m_cboAlarmAreaColor.SetCurSel(-1);
}

void CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea1Draw()
{
	// TODO: Add your control notification handler code here
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
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		return;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtArea1Points.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_AREA1_POINT_NUM, iPointNum);
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea2Draw()
{
	// TODO: Add your control notification handler code here
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
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		return;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtArea2Points.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_AREA2_POINTNUM, iPointNum);
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea3Draw()
{
	// TODO: Add your control notification handler code here
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
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		return;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtArea3Points.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_AREA3_POINTNUM, iPointNum);
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonArea4Draw()
{
	// TODO: Add your control notification handler code here
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
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		return;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtArea4Points.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_AREA4_POINTNUM, iPointNum);
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonLeavedetectSet()
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
	pRP->iEventID = VCA_EVENT_LEAVE_DETECT;
	vca_tLeaveDetect *tLeaveDetect = &(vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stLeaveDetect);
	pRP->stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	pRP->stDisplayParam.iDisplayStat = m_chkDiaplayState.GetCheck();
	pRP->stDisplayParam.iColor = m_cboAreaColor.GetCurSel()+1;
	pRP->stDisplayParam.iAlarmColor = m_cboAlarmAreaColor.GetCurSel()+1;

	int iLeaveAlarmTime = GetDlgItemInt(IDC_EDIT_LeaveAlarmTime);
	tLeaveDetect->iLeaveAlarmTime = iLeaveAlarmTime;
	int iRuturnClearAlarmTime = GetDlgItemInt(IDC_EDIT_RuturnClearAlarmTime);
	tLeaveDetect->iRuturnClearAlarmTime = iRuturnClearAlarmTime;
	int iAreaNum = GetDlgItemInt(IDC_EDIT_LEAVEDETECT_AREA_NUM);
	tLeaveDetect->iAreaNum = iAreaNum;

	int iArea1PointNum  = GetDlgItemInt(IDC_EDIT_AREA1_POINT_NUM);
	CString strArea1PointStr;
	GetDlgItemText(IDC_EDIT_AREA1_POINTS, strArea1PointStr);
	GetPolyFromString(strArea1PointStr, iArea1PointNum, tLeaveDetect->stRegion[0]);

	int iArea2PointNum  = GetDlgItemInt(IDC_EDIT_AREA2_POINTNUM);
	CString strArea2PointStr;
	GetDlgItemText(IDC_EDIT_AREA2_POINTS, strArea2PointStr);
	GetPolyFromString(strArea2PointStr, iArea2PointNum, tLeaveDetect->stRegion[1]);

	int iArea3PointNum  = GetDlgItemInt(IDC_EDIT_AREA3_POINTNUM);
	CString strArea3PointStr;
	GetDlgItemText(IDC_EDIT_AREA3_POINTS, strArea3PointStr);
	GetPolyFromString(strArea3PointStr, iArea3PointNum, tLeaveDetect->stRegion[2]);

	int iArea4PointNum  = GetDlgItemInt(IDC_EDIT_AREA4_POINTNUM);
	CString strArea4PointStr;
	GetDlgItemText(IDC_EDIT_AREA4_POINTS, strArea4PointStr);
	GetPolyFromString(strArea4PointStr, iArea4PointNum, tLeaveDetect->stRegion[3]);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE14_LEAVE_DETECT, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CVCAEventPage::OnBnClickedButtonLeavedetectSet]TDVCASetConfig leave detect Set error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[CVCAEventPage::OnBnClickedButtonLeavedetectSet]TDVCASetConfig leave detect set success!");
		RestartVCALib(m_iLogonID, m_iChannelNO);//重启智能库
	}
}

void CLS_VCAEVENT_LeaveDetect::UpdatePageUI()
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

	vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID = VCA_EVENT_LEAVE_DETECT;

	iCmd = VCA_CMD_GET_RULE14_LEAVE_DETECT;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if (vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_LEAVE_DETECT)
		{
			return;
		}
		const vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[m_iRuleID];
		const vca_tLeaveDetect& tLD = vp->chnParam[m_iChannelNO].rule[m_iRuleID].events.m_stLeaveDetect;
		if (!tr.iValid || !tLD.iValid)
			return;

		m_cboAlarmAreaColor.SetCurSel(tr.stDisplayParam.iAlarmColor-1);
		m_cboAreaColor.SetCurSel(tr.stDisplayParam.iColor-1);
		m_chkDisplayRule.SetCheck(tr.stDisplayParam.iDisplayRule);
		m_chkDiaplayState.SetCheck(tr.stDisplayParam.iDisplayStat);

		SetDlgItemInt(IDC_EDIT_LeaveAlarmTime, tLD.iLeaveAlarmTime);
		SetDlgItemInt(IDC_EDIT_RuturnClearAlarmTime, tLD.iRuturnClearAlarmTime);
		SetDlgItemInt(IDC_EDIT_LEAVEDETECT_AREA_NUM, tLD.iAreaNum);

		CString szPointBuf[MAX_RULE_REGION_NUM];
		for (int i =0; i < MAX_RULE_REGION_NUM; i++)
		{
			for (int j = 0; j < tLD.stRegion[i].iPointNum; j ++ )
			{
				szPointBuf[i].AppendFormat("(%d,%d)", tLD.stRegion[i].stPoints[j].iX, tLD.stRegion[i].stPoints[j].iY);
			}
		}
		SetDlgItemInt(IDC_EDIT_AREA1_POINT_NUM, tLD.stRegion[0].iPointNum);
		SetDlgItemInt(IDC_EDIT_AREA2_POINTNUM, tLD.stRegion[1].iPointNum);
		SetDlgItemInt(IDC_EDIT_AREA3_POINTNUM, tLD.stRegion[2].iPointNum);
		SetDlgItemInt(IDC_EDIT_AREA4_POINTNUM, tLD.stRegion[3].iPointNum);
		m_edtArea1Points.SetWindowText(szPointBuf[0]);
		m_edtArea2Points.SetWindowText(szPointBuf[1]);
		m_edtArea3Points.SetWindowText(szPointBuf[2]);
		m_edtArea4Points.SetWindowText(szPointBuf[3]);
	}
	else
	{
		// TODO: Nothing
		AddLog(LOG_TYPE_FAIL, "", "[CLS_VCAEVENT_LeaveDetect::UpdatePageUI]NetClient_VCAGetConfig fail,Set error = %d", GetLastError());
	}
}

void CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonLeavedetectStop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_LeaveDetect::OnBnClickedButtonLeavedetectStart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
