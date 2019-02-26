// VCAEVENT_TripwireEx.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_TripwireEx.h"


// VCAEVENT_TripwireEx dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_TripwireEx, CDialog)

CLS_VCAEVENT_TripwireEx::CLS_VCAEVENT_TripwireEx(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_TripwireEx::IDD, pParent)
{

}

CLS_VCAEVENT_TripwireEx::~CLS_VCAEVENT_TripwireEx()
{
}

void CLS_VCAEVENT_TripwireEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TWEX_TARGETTYPE, m_cbo_twex_TargetType);
	DDX_Control(pDX, IDC_COMBO_TWEX_ALARM_COLOR, m_cbo_twex_AlarmColor);
	DDX_Control(pDX, IDC_COMBO_TWEX_COLOR, m_cbo_twex_Color);
	DDX_Control(pDX, IDC_CHECK_TWEX_DISPLAY_RULE, m_chk_twex_DisplayRule);
	DDX_Control(pDX, IDC_CHECK_TWEX_DISPLAY_STAT, m_chk_twex_DisplayState);
	DDX_Control(pDX, IDC_CHECK_TWEX_TW_TYPE, m_chk_twex_TripWireType);
	DDX_Control(pDX, IDC_EDIT_TWEX_MINISIZE, m_edt_twex_MiniSize);
	DDX_Control(pDX, IDC_EDIT_TWEX_MAXSIZE, m_edt_twex_MaxSize);
	DDX_Control(pDX, IDC_EDIT_TWEX_DIRECTION, m_edt_twex_Direction);
	DDX_Control(pDX, IDC_EDIT_TWEX_POINT_NUM, m_edt_twex_PointNum);
	DDX_Control(pDX, IDC_EDIT_TWEX_POINTS, m_edt_twex_Points);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_TripwireEx, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TWEX_Set, &CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexSet)
	ON_BN_CLICKED(IDC_BUTTON_TWEX_Draw, &CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexDraw)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_TWEX_Stop, &CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexStop)
	ON_BN_CLICKED(IDC_BUTTON_TWEX_Start, &CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexStart)
END_MESSAGE_MAP()


// VCAEVENT_TripwireEx message handlers

void CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexDraw()
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
	m_pDlgVideoView->SetDrawType(DrawType_Flux);
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
		m_edt_twex_Points.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_TWEX_POINT_NUM, iPointNum);
	}
	else
	{
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	int iRuleID = m_iRuleID;
	VCA_TRuleParam_Tripwire vp = {0};
	//memset(vp, 0, sizeof(VCA_TRuleParam_Tripwire));
	
	vp.stRule.iRuleID = iRuleID;
	vp.stRule.iSceneID = m_iSceneID;
	vca_TVCAParam *temp_vp = m_pVcaParam;
	memset(temp_vp, 0, sizeof(vca_TVCAParam));

	temp_vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, temp_vp, sizeof(vca_TVCAParam));
	if (0 == temp_vp->chnParam[temp_vp->iChannelID].iEnable )
		return;
	int iCmd = VCA_CMD_TRIPWIRE_EX;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, temp_vp, sizeof(vca_TVCAParam));
	
	vp.stRule.iValid = temp_vp->chnParam[m_iChannelNO].rule[m_iRuleID].iValid;
	vp.iBufSize = sizeof(VCA_TRuleParam_Tripwire);
	vp.iMinSize = GetDlgItemInt(IDC_EDIT_TWEX_MINISIZE);
	vp.iMaxSize = GetDlgItemInt(IDC_EDIT_TWEX_MAXSIZE);
	vp.stDisplayParam.iColor = m_cbo_twex_Color.GetCurSel() + 1;
	vp.stDisplayParam.iAlarmColor = m_cbo_twex_AlarmColor.GetCurSel() + 1;
	vp.iTargetTypeCheck = m_cbo_twex_TargetType.GetCurSel() + 1;
	vp.stDisplayParam.iDisplayRule = m_chk_twex_DisplayRule.GetCheck();
	vp.stDisplayParam.iDisplayStat = m_chk_twex_DisplayState.GetCheck();
	vp.iTripwireType = m_chk_twex_TripWireType.GetCheck();
	vp.iTripwireDirection = GetDlgItemInt(IDC_EDIT_TWEX_DIRECTION);
	vp.stRegion1.iPointNum = GetDlgItemInt(IDC_EDIT_TWEX_POINT_NUM);

	CString strPointStr;
	GetDlgItemText(IDC_EDIT_TWEX_POINT_NUM, strPointStr);
	vca_TPolygon t_vp = {0};
	GetPolyFromString(strPointStr, vp.stRegion1.iPointNum, t_vp);
	memcpy(&vp.stRegion1, &t_vp, sizeof(vca_TPolygon));
	
	iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_TRIPWIRE_EX, m_iChannelNO, &vp, sizeof(VCA_TRuleParam_Tripwire));
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

BOOL CLS_VCAEVENT_TripwireEx::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();
	UpdateUIText();
	m_cbo_twex_Color.SetCurSel(0);
	m_cbo_twex_AlarmColor.SetCurSel(0);
	m_cbo_twex_TargetType.SetCurSel(0);
	m_edt_twex_MiniSize.SetWindowText("0");
	m_edt_twex_MaxSize.SetWindowText("0");
	m_edt_twex_Direction.SetWindowText("0");
	return TRUE;
}

void CLS_VCAEVENT_TripwireEx::UpdatePageUI()
{
	if (m_iLogonID ==-1 || m_iChannelNO == -1)
	{
		return;
	}
	vca_TVCAParam *temp_vp = m_pVcaParam;
	memset(temp_vp, 0, sizeof(vca_TVCAParam));

	temp_vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, temp_vp, sizeof(vca_TVCAParam));
	if (0 == temp_vp->chnParam[temp_vp->iChannelID].iEnable )
		return;
	VCA_TRuleParam_Tripwire vp = {0};
	//memset(vp, 0, sizeof(VCA_TRuleParam_Tripwire));

	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_TRIPWIRE_EX, m_iChannelNO, &vp, sizeof(VCA_TRuleParam_Tripwire));
	if (iRet >= 0)
	{
		if ( vp.iBufSize <= 0)
		{
			return;
		}
		

		m_chk_twex_DisplayRule.SetCheck(vp.stDisplayParam.iDisplayRule);
		m_chk_twex_DisplayState.SetCheck(vp.stDisplayParam.iDisplayStat);

		m_chk_twex_TripWireType.SetCheck(vp.iTripwireDirection);
		m_cbo_twex_TargetType.SetCurSel(vp.iTargetTypeCheck-1);
		m_cbo_twex_AlarmColor.SetCurSel(vp.stDisplayParam.iAlarmColor-1);
		m_cbo_twex_Color.SetCurSel(vp.stDisplayParam.iColor-1);

		SetDlgItemInt(IDC_EDIT_TWEX_MINISIZE, vp.iMinSize);
		SetDlgItemInt(IDC_EDIT_TWEX_MAXSIZE, vp.iMaxSize);
		SetDlgItemInt(IDC_EDIT_TWEX_DIRECTION, vp.iTripwireDirection);
		SetDlgItemInt(IDC_EDIT_TWEX_POINT_NUM, vp.stRegion1.iPointNum);
		
		CString szPointBuf;
		for (int i = 0; i < vp.stRegion1.iPointNum; i++)
		{
			CString tmpStr;
			tmpStr.Format("(%d,%d)", vp.stRegion1.stPoints[i].iX, vp.stRegion1.stPoints[i].iY);
			szPointBuf += tmpStr;
		}
		m_edt_twex_Points.SetWindowText(szPointBuf);
	}
	else
	{
		// TODO
	}

}

void CLS_VCAEVENT_TripwireEx::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	//CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_TripwireEx::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_TWEX_DISPLAY_RULE, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHECK_TWEX_DISPLAY_STAT, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_CHECK_TWEX_TW_TYPE, IDS_VCA_DOUBLE_DIR);
	SetDlgItemTextEx(IDC_BUTTON_TWEX_Draw, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BUTTON_TWEX_Set, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_TWEX_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_TWEX_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STATIC_TWEX_TARGETTYPE, IDS_VCA_TARGET_CHECK);
	SetDlgItemTextEx(IDC_STATIC_TWEX_MINISIZE, IDS_VCA_ADV_MINSIZE);
	SetDlgItemTextEx(IDC_STATIC_TWEX_MAXSIZE, IDS_VCA_ADV_MAXSIZE);
	SetDlgItemTextEx(IDC_STATIC_TWEX_POINT_NUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_TWEX_POINTS, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_STATIC_TWEX_DIRECTION, IDS_VCA_DIRECTION);
	
	SetDlgItemTextEx(IDC_BUTTON_TWEX_Stop, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_TWEX_Start, IDS_START);
	
	m_cbo_twex_TargetType.ResetContent();
	const CString strTarCheck[] = {GetTextEx(IDS_VCA_TARCHK_NONE), GetTextEx(IDS_VCA_TARCHK_PEOPLE), GetTextEx(IDS_VCA_TARCHK_CAR), GetTextEx(IDS_VCA_TARCHK_BOTH)};
	for (int i=0; i<sizeof(strTarCheck)/sizeof(CString); i++)
	{
		m_cbo_twex_TargetType.InsertString(i, strTarCheck[i]);
	}

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), GetTextEx(IDS_VCA_COL_YELLOW), 
		GetTextEx(IDS_VCA_COL_BLUE), GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cbo_twex_AlarmColor.ResetContent();
	m_cbo_twex_Color.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cbo_twex_AlarmColor.InsertString(i, strColor[i]);
		m_cbo_twex_Color.InsertString(i, strColor[i]);
	}
}

void CLS_VCAEVENT_TripwireEx::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_TripwireEx::CleanText()
{
	m_chk_twex_DisplayRule.SetCheck(0);
	m_chk_twex_DisplayState.SetCheck(0);
	m_chk_twex_TripWireType.SetCheck(0);
	m_edt_twex_Direction.Clear();
	m_edt_twex_MaxSize.Clear();
	m_edt_twex_MiniSize.Clear();
	m_edt_twex_PointNum.Clear();
	m_edt_twex_Points.Clear();
	m_cbo_twex_Color.SetCurSel(-1);
	m_cbo_twex_AlarmColor.SetCurSel(-1);
	m_cbo_twex_TargetType.SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_TWEX_DIRECTION, "");
	SetDlgItemText(IDC_EDIT_TWEX_MAXSIZE, "");
	SetDlgItemText(IDC_EDIT_TWEX_MINISIZE, "");
	SetDlgItemText(IDC_EDIT_TWEX_POINT_NUM, "");
	SetDlgItemText(IDC_EDIT_TWEX_POINTS, "");
}

void CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexStop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_TripwireEx::OnBnClickedButtonTwexStart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
