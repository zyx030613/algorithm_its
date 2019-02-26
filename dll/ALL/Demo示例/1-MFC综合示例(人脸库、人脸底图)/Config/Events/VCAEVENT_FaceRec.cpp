
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_FaceRec.h"


// CLS_VCAEVENT_FaceRec dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_FaceRec, CDialog)

CLS_VCAEVENT_FaceRec::CLS_VCAEVENT_FaceRec(CWnd* pParent /*=NULL*/)
: CLS_VCAEventBasePage(CLS_VCAEVENT_FaceRec::IDD, pParent)
{

}

CLS_VCAEVENT_FaceRec::~CLS_VCAEVENT_FaceRec()
{
}

void CLS_VCAEVENT_FaceRec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_Valid, m_chkFaceRecValid);
	DDX_Control(pDX, IDC_COMBO_Color, m_cboColor);
	DDX_Control(pDX, IDC_COMBO_AlarmColor, m_cboAlarmColor);
	DDX_Control(pDX, IDC_EDIT_PointNum, m_edtPointNum);
	DDX_Control(pDX, IDC_EDIT_Points, m_edtPoints);
	DDX_Control(pDX, IDC_CHECK_DisplayRule, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHECK_DisplayState, m_chkDisplayState);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_FaceRec, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Draw, &CLS_VCAEVENT_FaceRec::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_FaceRecSet, &CLS_VCAEVENT_FaceRec::OnBnClickedButtonFaceRecset)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_FaceRecStop, &CLS_VCAEVENT_FaceRec::OnBnClickedButtonFacerecstop)
	ON_BN_CLICKED(IDC_BUTTON_FaceRecStart, &CLS_VCAEVENT_FaceRec::OnBnClickedButtonFacerecstart)
END_MESSAGE_MAP()


// CLS_VCAEVENT_FaceRec message handlers
BOOL CLS_VCAEVENT_FaceRec::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateUIText();
	m_cboAlarmColor.SetCurSel(0);
	m_cboColor.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_FaceRec::OnBnClickedButtonDraw()
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
	m_pDlgVideoView->SetDrawType(DrawType_facerec);
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

void CLS_VCAEVENT_FaceRec::OnBnClickedButtonFaceRecset()
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
	pRP->iEventID = VCA_EVENT_FACEREC;
	vca_TFaceRec* pFR = &(vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stFaceRec);

	pRP->stDisplayParam.iDisplayRule = m_chkFaceRecValid.GetCheck();
	//pRP->stDisplayParam.iDisplayStat = m_chkDisplayAlarmCount.GetCheck();
	pRP->stDisplayParam.iColor = 0;						//人脸的非报警颜色暂时只有0
	pRP->stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel();		

	//pRP->iValid = m_chkValid.GetCheck();
	//人脸的点暂时不用
	pFR->stRegion.iPointNum = 0;
	pFR->stRegion.stPoints[0].iX = 0;
	pFR->stRegion.stPoints[0].iY = 0;

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE9_FACEREC, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CVCAEventPage::OnBnClickedButtonEventset]TDVCASetConfig face rec error = %d", GetLastError());
	}
	else
	{
		//重启智能库
		RestartVCALib(m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_FaceRec::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);
	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}

	// TODO: Add your message handler code here
}

void CLS_VCAEVENT_FaceRec::UpdatePageUI()
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
	iCmd = VCA_CMD_GET_RULE9_FACEREC;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if (vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_FACEREC)
		{
			return;
		}
		const vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[m_iRuleID];
		const vca_TFaceRec& fr = vp->chnParam[m_iChannelNO].rule[m_iRuleID].events.m_stFaceRec;
		if (!tr.iValid || !fr.iValid)
			return;

		m_chkFaceRecValid.SetCheck(tr.iValid);
		m_chkDisplayRule.SetCheck(tr.stDisplayParam.iDisplayRule);
		m_chkDisplayState.SetCheck(tr.stDisplayParam.iDisplayStat);

		m_cboAlarmColor.SetCurSel(tr.stDisplayParam.iAlarmColor-1);
		m_cboColor.SetCurSel(tr.stDisplayParam.iColor-1);
		SetDlgItemInt(IDC_EDIT_PointNum, fr.stRegion.iPointNum);

	}
	else
	{
		// TODO...
	}
}

void CLS_VCAEVENT_FaceRec::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_FaceRec::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_DisplayRule, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHECK_DisplayState, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_CHECK_Valid, IDS_VCA_VALID);
	SetDlgItemTextEx(IDC_STATIC_Color, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_AlarmColor, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_VCA_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_Points, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_BUTTON_Draw, IDS_VCA_DRAWWING);

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), GetTextEx(IDS_VCA_COL_YELLOW), 
		GetTextEx(IDS_VCA_COL_BLUE), GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAlarmColor.InsertString(i, strColor[i]);
		m_cboColor.InsertString(i, strColor[i]);
	}

	SetDlgItemTextEx(IDC_BUTTON_FaceRecSet, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_FaceRecStop, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_FaceRecStart, IDS_START);
}

void CLS_VCAEVENT_FaceRec::CleanText()
{
	m_chkFaceRecValid.SetCheck(0);
	m_cboColor.SetCurSel(-1);
	m_cboAlarmColor.SetCurSel(-1);
	m_edtPointNum.Clear();
	m_edtPoints.Clear();
	m_chkDisplayRule.SetCheck(0);
	m_chkDisplayState.SetCheck(0);
	SetDlgItemText(IDC_EDIT_PointNum, "");
	SetDlgItemText(IDC_EDIT_Points, "");	
}

void CLS_VCAEVENT_FaceRec::OnBnClickedButtonFacerecstop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_FaceRec::OnBnClickedButtonFacerecstart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
