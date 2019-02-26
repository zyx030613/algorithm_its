// VCAEVENT_Tripwire.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Tripwire.h"

// CLS_VCAEVENT_Tripwire dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Tripwire, CDialog)

CLS_VCAEVENT_Tripwire::CLS_VCAEVENT_Tripwire(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Tripwire::IDD, pParent)
{
	
}

CLS_VCAEVENT_Tripwire::~CLS_VCAEVENT_Tripwire()
{
}

void CLS_VCAEVENT_Tripwire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DisplayRule, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHECK_DisplayState, m_chkDisplayState);
	DDX_Control(pDX, IDC_CHECK_DoubleDir, m_chkDoubleDir);
	DDX_Control(pDX, IDC_EDIT_MinDis, m_edtMinDis);
	DDX_Control(pDX, IDC_EDIT_MinTime, m_edtMinTime);
	DDX_Control(pDX, IDC_COMBO_Color, m_cboColor);
	DDX_Control(pDX, IDC_COMBO_AlarmColor, m_cboAlarmColor);
	DDX_Control(pDX, IDC_EDIT_Dir, m_edtDirection);
	DDX_Control(pDX, IDC_EDIT_Points, m_edtPoints);
	DDX_Control(pDX, IDC_EDIT_PointNum, m_edtPointNum);
	DDX_Control(pDX, IDC_COMBO_TargetCheck_tw, m_cboTargetCheck);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Tripwire, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Draw, &CLS_VCAEVENT_Tripwire::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_TripSet, &CLS_VCAEVENT_Tripwire::OnBnClickedButtonTripset)
//	ON_WM_SHOWWINDOW()
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_BUTTON_TripStop, &CLS_VCAEVENT_Tripwire::OnBnClickedButtonTripstop)
ON_BN_CLICKED(IDC_BUTTON_TripStart, &CLS_VCAEVENT_Tripwire::OnBnClickedButtonTripstart)
END_MESSAGE_MAP()


// CLS_VCAEVENT_Tripwire message handlers

void CLS_VCAEVENT_Tripwire::OnBnClickedButtonDraw()
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
	m_pDlgVideoView->SetDrawType(DrawType_tripwire);
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

// void CLS_VCAEVENT_Tripwire::OnMainNotify( int _iLogonID,int _wParam, int _lParam,int _iUserData )
// {
// // 	if (m_pDlgVideoView->IsWindowVisible())
// // 	{
// // 		m_pDlgVideoView->OnMainNotify(_iLogonID, _wParam, _lParam, _iUserData);
// // 	}
// }
// 
// void CLS_VCAEVENT_Tripwire::Init( int _iLogonID,int _iChannelNo,int _iStreamNo )
// {
// 	
// }

void CLS_VCAEVENT_Tripwire::OnBnClickedButtonTripset()
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
	pRP->iEventID = VCA_EVENT_TRIPWIRE;
	vca_TTripwire *pTm = &(vp->chnParam[m_iChannelNO].rule[iRuleID].events.tripwire);
	//pTm->iValid = m_chkValid.GetCheck();
	pRP->stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	pRP->stDisplayParam.iDisplayStat = m_chkDisplayState.GetCheck();
	pRP->stDisplayParam.iColor = m_cboColor.GetCurSel()+1;
	pRP->stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel()+1;

	pTm->iType = m_chkDoubleDir.GetCheck();
	pTm->iTargetTypeCheck = m_cboTargetCheck.GetCurSel();
	pTm->iMinDistance = GetDlgItemInt(IDC_EDIT_MinDis);
	pTm->iMinTime = GetDlgItemInt(IDC_EDIT_MinTime);;
	pTm->iDirection = GetDlgItemInt(IDC_EDIT_Dir);

	int iPointNum = GetDlgItemInt(IDC_EDIT_PointNum);
	CString strPointStr;
	GetDlgItemText(IDC_EDIT_Points, strPointStr);
	GetLineFromString(strPointStr, pTm->stLine);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE0_TRIPWIRE, m_iChannelNO, vp, sizeof(vca_TVCAParam));
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

//void CLS_VCAEVENT_Tripwire::OnShowWindow(BOOL bShow, UINT nStatus)
//{
//	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);
//
//	// TODO: Add your message handler code here
//}

BOOL CLS_VCAEVENT_Tripwire::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateUIText();
	m_cboTargetCheck.SetCurSel(0);
	m_cboAlarmColor.SetCurSel(0);
	m_cboColor.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_Tripwire::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		return;
	}

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

	vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID = VCA_EVENT_TRIPWIRE;

	iCmd = VCA_CMD_GET_RULE0_TRIPWIRE;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if ( vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_TRIPWIRE)
		{
			return;
		}
		const vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[m_iRuleID];
		const vca_TTripwire& tw = vp->chnParam[m_iChannelNO].rule[m_iRuleID].events.tripwire;
		if (!tr.iValid || !tw.iValid)
			return;

		m_chkDisplayRule.SetCheck(tr.stDisplayParam.iDisplayRule);
		m_chkDisplayState.SetCheck(tr.stDisplayParam.iDisplayStat);

		m_chkDoubleDir.SetCheck(tw.iType);
		m_cboTargetCheck.SetCurSel(tw.iTargetTypeCheck);
		//m_iMinDistance = tw.iMinDistance;
		SetDlgItemInt(IDC_EDIT_MinDis, tw.iMinDistance);
		SetDlgItemInt(IDC_EDIT_MinTime, tw.iMinTime);
		m_cboAlarmColor.SetCurSel(tr.stDisplayParam.iAlarmColor-1);
		m_cboColor.SetCurSel(tr.stDisplayParam.iColor-1);
		SetDlgItemInt(IDC_EDIT_Dir, tw.iDirection);
		CString szPointBuf;
		szPointBuf.Format("(%d,%d)(%d,%d)", tw.stLine.stStart.iX, tw.stLine.stStart.iY, tw.stLine.stEnd.iX, tw.stLine.stEnd.iY);
		m_edtPoints.SetWindowText(szPointBuf);
	}
	else
	{
		// TODO
	}

// 			m_ptTripwire[0].x = tw.stLine.stStart.iX;
// 			m_ptTripwire[0].y = tw.stLine.stStart.iY;
// 			m_ptTripwire[1].x = tw.stLine.stEnd.iX;
// 			m_ptTripwire[1].y = tw.stLine.stEnd.iY;
// 
// 			/*if (m_bRuleEnable && m_chkValid.GetCheck() == 1 && m_chkShowRule.GetCheck() == 1)*/
// 			if (m_ptTripwire[0] == CPoint(0, 0) && m_ptTripwire[1] == CPoint(0, 0))
// 			{
// 				log(1, "[CVCAEventPage::UpdateUI_Event] No tripwire!\n");
// 				m_ptTripTemp[0] = CPoint(0, 0);
// 				m_ptTripTemp[1] = CPoint(0, 0);
// 
// 				ASSERT(TDDrawPolyOnLocalVideo);
// 				CPoint ptClear[2] = {CPoint(0, 0), CPoint(0, 0)};
// 				int iRet = TDDrawPolyOnLocalVideo(s_pLogonConnInfo->m_ulConnectID, ptClear, 2, 0);
// 				if (iRet < 0)
// 				{
// 					log(1, "[CVCAEventPage::DrawTripwire]TDDrawPolyOnLocalVideo error = 0x%p\n", GetLastError());
// 				}
// 			}
// 			else
// 			{
// 				m_ptTripTemp[0] = m_ptTripwire[0];
// 				m_ptTripTemp[1] = m_ptTripwire[1];
// 
// 				// 				if (m_chkDirEnable.GetCheck() == 0)
// 				// 				{
// 				// 					ShowTripwire(TRUE);		
// 				// 				}
// 				// 				else
// 				// 				{
// 				// 					ShowTripwire(FALSE);
// 				// 				}	
// 
// 				//清空缓存
// 				// 				m_ptTripTemp[0] = CPoint(0, 0);
// 				// 				m_ptTripTemp[1] = CPoint(0, 0);
// 			}
// 		}
// 		else
// 		{
// 			m_ptTripTemp[0] = CPoint(0, 0);
// 			m_ptTripTemp[1] = CPoint(0, 0);
// 			m_ptTripwire[0] = CPoint(0, 0);
// 			m_ptTripwire[1] = CPoint(0, 0);
// 			log(1, "[CVCAEventPage::UpdateUI_Event]TDVCAGetConfig error = 0x%p\n", GetLastError());
// 		}
}

void CLS_VCAEVENT_Tripwire::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_Tripwire::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_DisplayRule, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHECK_DisplayState, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_CHECK_DoubleDir, IDS_VCA_DOUBLE_DIR);
	SetDlgItemTextEx(IDC_STATIC_TargetCheck, IDS_VCA_TARGET_CHECK);
	SetDlgItemTextEx(IDC_STATIC_MinDis, IDS_VCA_MINDISTANCE);
	SetDlgItemTextEx(IDC_STATIC_MinTime, IDS_VCA_MINTIME);
	SetDlgItemTextEx(IDC_STATIC_VCA_Color, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_AlarmColor, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARMCOLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_Dir, IDS_VCA_DIRECTION);
	SetDlgItemTextEx(IDC_STATIC_VCA_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_Points, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_BUTTON_Draw, IDS_VCA_DRAWWING);

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

	SetDlgItemTextEx(IDC_BUTTON_TripSet, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_TripStop, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_TripStart, IDS_START);
}

void CLS_VCAEVENT_Tripwire::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_Tripwire::CleanText()
{
	m_chkDisplayRule.SetCheck(0);
	m_chkDisplayState.SetCheck(0);
	m_chkDoubleDir.SetCheck(0);
	m_edtMinDis.Clear();
	m_edtMinTime.Clear();
	m_cboColor.SetCurSel(-1);
	m_cboAlarmColor.Clear();
	m_edtDirection.Clear();
	m_edtPoints.Clear();
	m_edtPointNum.Clear();
	m_cboTargetCheck.SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_MinDis, "");
	SetDlgItemText(IDC_EDIT_MinTime, "");
	SetDlgItemText(IDC_EDIT_Dir, "");
	SetDlgItemText(IDC_EDIT_Points, "");
	SetDlgItemText(IDC_EDIT_PointNum, "");
}
void CLS_VCAEVENT_Tripwire::OnBnClickedButtonTripstop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_Tripwire::OnBnClickedButtonTripstart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
