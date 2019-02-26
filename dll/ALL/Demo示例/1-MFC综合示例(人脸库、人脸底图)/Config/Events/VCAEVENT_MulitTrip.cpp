
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_MulitTrip.h"


// CLS_VCAEVENT_MulitTrip 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_MulitTrip, CDialog)

CLS_VCAEVENT_MulitTrip::CLS_VCAEVENT_MulitTrip(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_MulitTrip::IDD, pParent)
{

}

CLS_VCAEVENT_MulitTrip::~CLS_VCAEVENT_MulitTrip()
{
}

void CLS_VCAEVENT_MulitTrip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_MULITTRIP_UNALARM_COLOR, m_cboUnAlarmColor);
	DDX_Control(pDX, IDC_CBO_MULITTRIP_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_MULITTRIP_TARGET, m_cboTargetType);
	DDX_Control(pDX, IDC_CHK_MULITTRIP_RULE_DISPLAY, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHK_MULITTRIP_DIAPALYSTATE, m_chkDisplayAlarmNum);
	DDX_Control(pDX, IDC_CHK_MULITTRIP_TYPE, m_chkIsDoubleDir);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_MIN_DBTIME, m_edtMinDbTime);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_MAX_DBTIME, m_edtMaxDbType);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_POINTNUM_LINE1, m_edtTripwire1PointNum);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_POINTNUM_LINE2, m_edtTripwire2PointNum);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_POINTS_LINE1, m_edtTripwire1Points);
	DDX_Control(pDX, IDC_EDT_MULITTRIP_POINTS_LINE2, m_edtTripwire2Points);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_MulitTrip, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_MULITTRIP_SET, &CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripSet)
	ON_BN_CLICKED(IDC_BTN_MULITTRIP_DRAW1, &CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripDraw1)
	ON_BN_CLICKED(IDC_BTN_MULITTRIP_DRAW2, &CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripDraw2)
	ON_BN_CLICKED(IDC_BTN_MULITTRIP_Stop, &CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripStop)
	ON_BN_CLICKED(IDC_BTN_MULITTRIP_START, &CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripStart)
END_MESSAGE_MAP()

BOOL CLS_VCAEVENT_MulitTrip::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateUIText();

	return TRUE;
}

void CLS_VCAEVENT_MulitTrip::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_MulitTrip::UpdateUIText()
{
	SetDlgItemTextEx(IDC_STC_MULITTRIP_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_CHK_MULITTRIP_RULE_DISPLAY, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHK_MULITTRIP_DIAPALYSTATE, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_CHK_MULITTRIP_TYPE, IDS_VCA_DOUBLE_DIR);

	SetDlgItemTextEx(IDC_STC_MULITTRIP_TARGET, IDS_VCA_TARGET_CHECK);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_DIR, IDS_VCA_DIRECTION);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_MIN_SIZE, IDS_VCA_MINSIZE);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_MAX_SIZE, IDS_VCA_MAXSIZE);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_MIN_DBTIME, IDS_VCA_MINDBTIME);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_MAX_DBTIME, IDS_VCA_MAXDBTIME);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_POINTNUM_LINE1, IDS_VCA_LINE1_POINTNUM);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_POINTNUM_LINE2, IDS_VCA_LINE2_POINTNUM);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_POINTS_LINE1, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_STC_MULITTRIP_POINTS_LINE2, IDS_VCA_POINTS);

	SetDlgItemTextEx(IDC_BTN_MULITTRIP_DRAW1, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_MULITTRIP_DRAW2, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_MULITTRIP_SET, IDS_SET);

	SetDlgItemTextEx(IDC_BTN_MULITTRIP_Stop, IDS_STOP);
	SetDlgItemTextEx(IDC_BTN_MULITTRIP_START, IDS_START);

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), 
		GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_BLUE), 
		GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), 
		GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboUnAlarmColor.ResetContent();
	m_cboAlarmColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboUnAlarmColor.InsertString(i, strColor[i]);
		m_cboAlarmColor.InsertString(i, strColor[i]);
	}
		
	const CString strTarCheck[] = {GetTextEx(IDS_VCA_TARCHK_NONE), GetTextEx(IDS_VCA_TARCHK_PEOPLE), 
		GetTextEx(IDS_VCA_TARCHK_CAR), GetTextEx(IDS_VCA_TARCHK_BOTH)};
	m_cboTargetType.ResetContent();
	for (int i=0; i<sizeof(strTarCheck)/sizeof(CString); i++)
	{
		m_cboTargetType.InsertString(i, strTarCheck[i]);
	}
}

void CLS_VCAEVENT_MulitTrip::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_MulitTrip::UpdatePageUI()
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

	VCADbTripwire st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;
	int iCmd = VCA_CMD_MULITTRIP;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet >= 0)
	{
		m_chkDisplayRule.SetCheck(st.stDisplayParam.iDisplayRule);
		m_chkDisplayAlarmNum.SetCheck(st.stDisplayParam.iDisplayStat);
		m_chkIsDoubleDir.SetCheck(st.iTripwireType);
		m_cboUnAlarmColor.SetCurSel(st.stDisplayParam.iColor);
		m_cboAlarmColor.SetCurSel(st.stDisplayParam.iAlarmColor);
		m_cboTargetType.SetCurSel(st.iTargetTypeCheck);

		SetDlgItemInt(IDC_EDT_MULITTRIP_DIR,st.iDirTripwire1);
		SetDlgItemInt(IDC_EDT_MULITTRIP_MIN_SIZE,st.iMinSize);
		SetDlgItemInt(IDC_EDT_MULITTRIP_MAX_SIZE,st.iMaxSize);
		SetDlgItemInt(IDC_EDT_MULITTRIP_MIN_DBTIME,st.iMinDBTime);
		SetDlgItemInt(IDC_EDT_MULITTRIP_MAX_DBTIME,st.iMaxDBTime);
		SetDlgItemInt(IDC_EDT_MULITTRIP_POINTNUM_LINE1,st.stRegion1.iPointNum);
		SetDlgItemInt(IDC_EDT_MULITTRIP_POINTNUM_LINE2,st.stRegion2.iPointNum);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}
}

void CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripSet()
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

	VCADbTripwire st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;

	st.stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	st.stDisplayParam.iDisplayStat = m_chkDisplayAlarmNum.GetCheck();
	st.iTripwireType = m_chkIsDoubleDir.GetCheck();
	st.stDisplayParam.iColor = m_cboUnAlarmColor.GetCurSel();
	st.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel();
	st.iTargetTypeCheck = m_cboTargetType.GetCurSel();
	st.iDirTripwire1 = GetDlgItemInt(IDC_EDT_MULITTRIP_DIR);
	st.iMinSize = GetDlgItemInt(IDC_EDT_MULITTRIP_MIN_SIZE);
	st.iMaxSize = GetDlgItemInt(IDC_EDT_MULITTRIP_MAX_SIZE);
	st.iMinDBTime = GetDlgItemInt(IDC_EDT_MULITTRIP_MIN_DBTIME);
	st.iMaxDBTime = GetDlgItemInt(IDC_EDT_MULITTRIP_MAX_DBTIME);
	st.stRegion1.iPointNum = GetDlgItemInt(IDC_EDT_MULITTRIP_POINTNUM_LINE1);
	st.stRegion2.iPointNum = GetDlgItemInt(IDC_EDT_MULITTRIP_POINTNUM_LINE2);

	CString strPointStr;
	vca_TPolygon stRegion = {0};
	GetDlgItemText(IDC_EDT_MULITTRIP_POINTS_LINE1, strPointStr);
	GetPolyFromString(strPointStr, st.stRegion1.iPointNum, stRegion);
	memcpy(st.stRegion1.stPoints, &stRegion, sizeof(stRegion));
	
	strPointStr = "" ;
	memset(&stRegion, 0, sizeof(stRegion));
	GetDlgItemText(IDC_EDT_MULITTRIP_POINTS_LINE2, strPointStr);
	GetPolyFromString(strPointStr, st.stRegion1.iPointNum, stRegion);
	memcpy(st.stRegion2.stPoints, &stRegion, sizeof(stRegion));

	int iCmd = VCA_CMD_MULITTRIP;
	iRet = NetClient_VCASetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet >= 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}
}

void CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripDraw1()
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
		m_edtTripwire1Points.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDT_MULITTRIP_POINTNUM_LINE1, iPointNum);
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripDraw2()
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
		m_edtTripwire2Points.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDT_MULITTRIP_POINTNUM_LINE2, iPointNum);
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripStop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_MulitTrip::OnBnClickedBtnMulittripStart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
