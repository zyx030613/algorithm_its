// VCAEVENT_OSC.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Abandum.h"


// CLS_VCAEVENT_OSC dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Abandum, CDialog)

CLS_VCAEVENT_Abandum::CLS_VCAEVENT_Abandum(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Abandum::IDD, pParent)
{

}

CLS_VCAEVENT_Abandum::~CLS_VCAEVENT_Abandum()
{
}

void CLS_VCAEVENT_Abandum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DisplayRule, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHECK_DisplayState, m_chkDisplayState);
	DDX_Control(pDX, IDC_EDIT_MinSize, m_edtMinSize);
	DDX_Control(pDX, IDC_EDIT_MaxSize, m_edtMaxSize);
	DDX_Control(pDX, IDC_EDIT_MinTime, m_edtMinTime);
	DDX_Control(pDX, IDC_COMBO_Color, m_cboColor);
	DDX_Control(pDX, IDC_COMBO_AlarmColor, m_cboAlarmColor);
	DDX_Control(pDX, IDC_EDIT_MainRegoin, m_edtMainRegion);
	DDX_Control(pDX, IDC_EDIT_SubRegoin1, m_edtSubRegion1);
	DDX_Control(pDX, IDC_EDIT_SubRegoin2, m_edtSubRegoin2);
	DDX_Control(pDX, IDC_EDIT_SubRegoin3, m_edtSubRegion3);
	DDX_Control(pDX, IDC_CHECK_ABValid, m_chkValid);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Abandum, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Draw, &CLS_VCAEVENT_Abandum::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_AbandumSet, &CLS_VCAEVENT_Abandum::OnBnClickedButtonAbandumset)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_ABANDUM_STOP, &CLS_VCAEVENT_Abandum::OnBnClickedButtonAbandumStop)
	ON_BN_CLICKED(IDC_BUTTON_ABANDUM_START, &CLS_VCAEVENT_Abandum::OnBnClickedButtonAbandumStart)
END_MESSAGE_MAP()

// CLS_VCAEVENT_OSC message handlers

BOOL CLS_VCAEVENT_Abandum::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateUIText();
	m_cboAlarmColor.SetCurSel(0);
	m_cboColor.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_Abandum::OnBnClickedButtonDraw()
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
	m_pDlgVideoView->SetDrawType(DrawType_abandum);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	char cPointBuf1[MAX_POINTBUF_LEN] = {0};
	char cPointBuf2[MAX_POINTBUF_LEN] = {0};
	char cPointBuf3[MAX_POINTBUF_LEN] = {0};
	char* cSubRegion[MAX_AB_SUBREGOIN_NUM] = {cPointBuf1, cPointBuf2, cPointBuf3};
	//char cSubRegion[MAX_POINTBUF_LEN][MAX_AB_SUBREGOIN_NUM] = {{0}};

	int iSetRet = m_pDlgVideoView->SetAbandumRegionParam(cPointBuf, cSubRegion);
	if (-1 == iSetRet)
	{
		return;
	}
	/*******************/

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		SetDlgItemText(IDC_EDIT_MainRegoin, cPointBuf);
		SetDlgItemText(IDC_EDIT_SubRegoin1, cPointBuf1);
		SetDlgItemText(IDC_EDIT_SubRegoin2, cPointBuf2);
		SetDlgItemText(IDC_EDIT_SubRegoin3, cPointBuf3);
	}
	else
	{

	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Abandum::OnBnClickedButtonAbandumset()
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
	//判断规则是否使能
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_RULE_COMMON, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[iRuleID];

	//if(tr.iValid != 1)
	//	return;
	memset(vp, 0, sizeof(vca_TVCAParam));
	vp->chnParam[m_iChannelNO].iRuleID = iRuleID;

	vca_tOSC & tOSC = vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stOSC;
	//    pm->iValid = chkVCAFaceInvalid->Checked;
	tr.stDisplayParam.iDisplayStat = m_chkDisplayState.GetCheck();
	tr.stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	tOSC.iColor = m_cboColor.GetCurSel()+1;
	tOSC.iAlarmColor = m_cboAlarmColor.GetCurSel()+1;

	int iMinSize = GetDlgItemInt(IDC_EDIT_MinSize);
	int iMaxSize = GetDlgItemInt(IDC_EDIT_MaxSize);
	int iMinTime = GetDlgItemInt(IDC_EDIT_MinTime);

	tOSC.iMinTime = iMinTime;
	tOSC.iMinSize = iMinSize;
	tOSC.iMaxSize = iMaxSize;

	CString strMainRegion;
	CString strSubRegion1;
	CString strSubRegion2;
	CString strSubRegion3;
	GetDlgItemText(IDC_EDIT_MainRegoin, strMainRegion);
	GetDlgItemText(IDC_EDIT_SubRegoin1, strSubRegion1);
	GetDlgItemText(IDC_EDIT_SubRegoin2, strSubRegion2);
	GetDlgItemText(IDC_EDIT_SubRegoin3, strSubRegion3);
	GetPolyFromString(strMainRegion, 0, tOSC.stMainRegion);
	GetPolyFromString(strSubRegion1, 0, tOSC.stSubRegion[0]);
	GetPolyFromString(strSubRegion2, 0, tOSC.stSubRegion[1]);
	GetPolyFromString(strSubRegion3, 0, tOSC.stSubRegion[2]);
	for(int i = 0; i < 3; i++)
	{
		if(tOSC.stSubRegion[i].iPointNum)
		{
			tOSC.iSunRegionCount++;
		}
	}
	
	iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE8_ABANDUM, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
	}
	else
	{
		//重启智能库
		RestartVCALib(m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_Abandum::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable)
		return;

	int iRuleID = m_iRuleID;
	int iCmd = VCA_CMD_GET_RULE8_ABANDUM;
	vp->chnParam[m_iChannelNO].iRuleID = m_iRuleID;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if( vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_ABANDUM)
		{
			return;
		}
		const vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[iRuleID];
		const vca_tOSC & tOSC = vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stOSC;

		m_chkDisplayState.SetCheck(tr.stDisplayParam.iDisplayStat);
		m_chkDisplayRule.SetCheck(tr.stDisplayParam.iDisplayRule);	
		m_chkValid.SetCheck(tr.iValid);

	
		m_cboAlarmColor.SetCurSel(tOSC.iAlarmColor-1);
		m_cboColor.SetCurSel(tOSC.iColor-1);

		SetDlgItemInt(IDC_EDIT_MinSize, tOSC.iMinSize);
		SetDlgItemInt(IDC_EDIT_MaxSize, tOSC.iMaxSize);
		SetDlgItemInt(IDC_EDIT_MinTime, tOSC.iMinTime);
		CString astr;
		for(int i =0 ; i < tOSC.stMainRegion.iPointNum; i++)
		{
			CString astrtemp;
			astrtemp.Format("(%d,%d)", tOSC.stMainRegion.stPoints[i].iX, tOSC.stMainRegion.stPoints[i].iY);
			astr += astrtemp;
		}
		SetDlgItemText(IDC_EDIT_MainRegoin, astr);

		for(int i = 0; i < tOSC.iSunRegionCount; i++)
		{
			CString astr;
			for(int j =0 ; j < tOSC.stSubRegion[i].iPointNum; j++)
			{
				CString astrtemp;
				astrtemp.Format("(%d,%d)", tOSC.stSubRegion[i].stPoints[j].iX, tOSC.stSubRegion[i].stPoints[j].iY);
				astr += astrtemp;
			}

			if(i == 0)
				SetDlgItemText(IDC_EDIT_SubRegoin1, astr);
			else if(i == 1)
				SetDlgItemText(IDC_EDIT_SubRegoin2, astr);
			else if(i == 2)
				SetDlgItemText(IDC_EDIT_SubRegoin3, astr);
		}
	}
	else
	{
		//chkOSCDisPlay->Checked = 0;
		//cbbVCAOSCColor->ItemIndex = -1;
		//cbbVCAOSCAlarmColor->ItemIndex =-1;
		//chkVCAOSCDisplayRule->Checked = 0;
		//chkType->Checked = 0;
		//edtMinTime->Text = 0;
		//edtMinSize->Text = 0;
		//edtMaxSize->Text = 0;
		//edtMainRegion->Text = "";
		//edtSubRegion1->Text = "";
		//edtSubRegion2->Text = "";
		//edtSubRegion3->Text = "";
		//VCATrace(iCmd, iRet);
	}
}

void CLS_VCAEVENT_Abandum::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_Abandum::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_ABValid, IDS_VCA_VALID);
	SetDlgItemTextEx(IDC_CHECK_DisplayRule, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHECK_DisplayState, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STATIC_MinSize, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STATIC_MaxSize, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STATIC_MinTime, IDS_VCA_MINTIME);
	SetDlgItemTextEx(IDC_STATIC_Color, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_AlarmColor, IDS_VCA_ALARM_COLOR);

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), GetTextEx(IDS_VCA_COL_YELLOW), 
		GetTextEx(IDS_VCA_COL_BLUE), GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAlarmColor.InsertString(i, strColor[i]);
		m_cboColor.InsertString(i, strColor[i]);
	}

	SetDlgItemTextEx(IDC_STATIC_MainRegoin, IDS_VCA_ABMAINREGION);
	SetDlgItemTextEx(IDC_STATIC_SubRegoin1, IDS_VCA_ABSUBREGION1);
	SetDlgItemTextEx(IDC_STATIC_SubRegoin2, IDS_VCA_ABSUBREGION2);
	SetDlgItemTextEx(IDC_STATIC_SubRegoin3, IDS_VCA_ABSUBREGION3);
	SetDlgItemTextEx(IDC_BUTTON_Draw, IDS_VCA_DRAWWING);

	SetDlgItemTextEx(IDC_BUTTON_AbandumSet, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_ABANDUM_STOP, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_AbandumSet, IDS_START);
}

void CLS_VCAEVENT_Abandum::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_Abandum::CleanText()
{
	m_chkValid.SetCheck(0);
	m_edtMinSize.Cut();
	m_edtMaxSize.Clear();
	m_edtMinTime.Clear();
	m_cboColor.SetCurSel(-1);
	m_cboAlarmColor.SetCurSel(-1);
	m_edtMainRegion.Clear();
	m_edtSubRegion1.Clear();
	m_edtSubRegoin2.Clear();
	m_edtSubRegion3.Clear();
	m_chkDisplayRule.SetCheck(0);
	m_chkDisplayState.SetCheck(0);
	SetDlgItemText(IDC_EDIT_MinSize, "");
	SetDlgItemText(IDC_EDIT_MaxSize, "");
	SetDlgItemText(IDC_EDIT_MinTime, "");
	SetDlgItemText(IDC_EDIT_MainRegoin, "");
	SetDlgItemText(IDC_EDIT_SubRegoin1, "");
	SetDlgItemText(IDC_EDIT_SubRegoin2, "");
	SetDlgItemText(IDC_EDIT_SubRegoin3, "");
	UpdateData(TRUE);
}
void CLS_VCAEVENT_Abandum::OnBnClickedButtonAbandumStop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_Abandum::OnBnClickedButtonAbandumStart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
