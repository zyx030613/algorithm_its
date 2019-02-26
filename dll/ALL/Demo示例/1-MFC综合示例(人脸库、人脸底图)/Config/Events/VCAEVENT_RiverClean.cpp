
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_RiverClean.h"

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_RiverClean, CDialog)

CLS_VCAEVENT_RiverClean::CLS_VCAEVENT_RiverClean(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_RiverClean::IDD, pParent)
{
	
}

CLS_VCAEVENT_RiverClean::~CLS_VCAEVENT_RiverClean()
{
}

void CLS_VCAEVENT_RiverClean::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_RIVER_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_RIVER_AREA_COLOR, m_cboAreaColor);
	DDX_Control(pDX, IDC_CBO_RIVER_RECOGNIZE_MODE, m_cboRecgMode);
	DDX_Control(pDX, IDC_CHK_RIVER_RULE_DISPLAY, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHK_RIVER_DISPLAY_STATE, m_chkDisplayAlarmNum);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_RiverClean, CDialog)
	ON_BN_CLICKED(IDC_BTN_RIVER_SET, &CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverSet)
	ON_BN_CLICKED(IDC_BTN_RIVER_POINTS_DRAW, &CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverPointsDraw)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_CBO_RIVER_ALARM_COLOR, &CLS_VCAEVENT_RiverClean::OnCbnSelchangeCboRiverAlarmColor)
	ON_BN_CLICKED(IDC_BTN_RIVER_STOP, &CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverStop)
	ON_BN_CLICKED(IDC_BTN_RIVER_START, &CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverStart)
	ON_CBN_SELCHANGE(IDC_CBO_RIVER_RECOGNIZE_MODE, &CLS_VCAEVENT_RiverClean::OnCbnSelchangeCboRiverRecognizeMode)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CLS_VCAEVENT_RiverClean::OnBnClickedButtonReset)
END_MESSAGE_MAP()


BOOL CLS_VCAEVENT_RiverClean::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	UI_UpdateDialog();

	return TRUE;
}

void CLS_VCAEVENT_RiverClean::OnLanguageChanged()
{
	UI_UpdateDialog();
}

void CLS_VCAEVENT_RiverClean::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UI_UpdatePage();
	}
}

void CLS_VCAEVENT_RiverClean::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_RIVER_AREA_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_RIVER_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_CHK_RIVER_RULE_DISPLAY, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHK_RIVER_DISPLAY_STATE, IDS_VCA_DISPLAY_ALARMSTATUS);

	SetDlgItemTextEx(IDC_STC_RIVER_RECOGNIZE_MODE, IDS_VCA_RIVER_RECOGNIZE_MODE);
	SetDlgItemTextEx(IDC_STC_RIVER_MINSIZE, IDS_VCA_MINSIZE);
	SetDlgItemTextEx(IDC_STC_RIVER_MINSIZE_Range, IDS_VCA_MINSIZE_RANGE);
	SetDlgItemTextEx(IDC_STC_RIVER_MAXSIZE, IDS_VCA_MAXSIZE);
	SetDlgItemTextEx(IDC_STC_RIVER_MAXSIZE_RANGE, IDS_VCA_MAXSIZE_RANGE);
	SetDlgItemTextEx(IDC_STC_RIVER_PERCENTAGE, IDS_VCA_RIVER_PERCENTAGE);
	SetDlgItemTextEx(IDC_STC_RIVER_PERCENTAGE_RANGE, IDS_VCA_MINSIZE_RANGE);
	SetDlgItemTextEx(IDC_STC_RIVER_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_BUTTON_RESET, IDC_BUTTON_DREDGE_AUTO);
	SetDlgItemTextEx(IDC_STC_RIVER_SENSITIVITY, IDS_VCA_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_RIVER_SENSITIVITY_RANGE,IDS_STC_FIGHT_SENSITIVITY );
	SetDlgItemTextEx(IDC_STC_RIVER_POINTS, IDS_VCA_POINTS);

	SetDlgItemTextEx(IDC_BTN_RIVER_POINTS_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_RIVER_SET, IDS_SET);
	
	SetDlgItemTextEx(IDC_BTN_RIVER_STOP, IDS_STOP);
	SetDlgItemTextEx(IDC_BTN_RIVER_START, IDS_START);

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

	CString strMode[] = {GetTextEx(IDS_VCA_RIVER_RECGMODE_FLOAD), GetTextEx(IDS_VCA_RIVER_RECGMODE_ACCUMULATION), 
		GetTextEx(IDS_VCA_RIVER_RECGMODE_BLOCK)};

	m_cboRecgMode.ResetContent();
	for (int i=0; i<sizeof(strMode)/sizeof(CString); i++)
	{
		m_cboRecgMode.InsertString(i, strMode[i]);
	}
}


void CLS_VCAEVENT_RiverClean::UI_UpdatePage()
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

	VCARiverClean st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;
	int iCmd = VCA_CMD_RIVERCLEAN;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet == 0)
	{
		m_chkDisplayRule.SetCheck(st.stDisplayParam.iDisplayRule);
		m_chkDisplayAlarmNum.SetCheck(st.stDisplayParam.iDisplayStat);
		m_cboAreaColor.SetCurSel(st.stDisplayParam.iColor - 1);
		m_cboAlarmColor.SetCurSel(st.stDisplayParam.iAlarmColor - 1);

		m_cboRecgMode.SetCurSel(st.iType);
		SetDlgItemInt(IDC_EDT_RIVER_MINSIZE,st.iMinSize);
		SetDlgItemInt(IDC_EDT_RIVER_MAXSIZE,st.iMaxSize);
		SetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE,st.iPercentage);
		SetDlgItemInt(IDC_EDT_RIVER_SENSITIVITY,st.iSensitivity);
		SetDlgItemInt(IDC_EDT_RIVER_POINTNUM,st.stPoints.iPointNum);
		int _iPointNum = st.stPoints.iPointNum;
		CString strPointArray;
		CString strPoint[VCA_MAX_POLYGON_POINT_NUMEX];
		for(int i = 0; i != _iPointNum; i++)
		{
			strPoint[i].Format("(%d,%d)", st.stPoints.stPoints[i].iX, st.stPoints.stPoints[i].iY);
			strPointArray += strPoint[i];
		}
		SetDlgItemText(IDC_EDT_RIVER_POINTS,strPointArray);
	}
	else
	{
		AutoShowParam();
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}
}


void CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}
	CheckValueLimits();

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable )
		return;

	VCARiverClean st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;
	st.stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	st.stDisplayParam.iDisplayStat = m_chkDisplayAlarmNum.GetCheck();
	st.stDisplayParam.iColor = m_cboAreaColor.GetCurSel() + 1;
	st.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel() + 1;
	st.iMinSize = GetDlgItemInt(IDC_EDT_RIVER_MINSIZE);
	st.iMaxSize = GetDlgItemInt(IDC_EDT_RIVER_MAXSIZE);
	st.iPercentage = GetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE);
	st.iSensitivity = GetDlgItemInt(IDC_EDT_RIVER_SENSITIVITY);
	st.stPoints.iPointNum = GetDlgItemInt(IDC_EDT_RIVER_POINTNUM);
	st.iType = m_cboRecgMode.GetCurSel();

	CString strPointStr;
	vca_TPolygon stRegion = {0};
	GetDlgItemText(IDC_EDT_RIVER_POINTS, strPointStr);
	GetPolyFromString(strPointStr, st.stPoints.iPointNum, stRegion);
	memcpy(&st.stPoints, &stRegion, sizeof(stRegion));

	int iCmd = VCA_CMD_RIVERCLEAN;
	iRet = NetClient_VCASetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet >= 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}

	//恢复智能分析
	int iState = 1;
	NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iState, sizeof(int));
}

void CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverPointsDraw()
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
		return;
	}

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		GetDlgItem(IDC_EDT_RIVER_POINTS)->SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDT_RIVER_POINTNUM, iPointNum);
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_RiverClean::OnCbnSelchangeCboRiverAlarmColor()
{
	// TODO: Add your control notification handler code here
}

void CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverStop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_RiverClean::OnBnClickedBtnRiverStart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_RiverClean::OnCbnSelchangeCboRiverRecognizeMode()
{
	// TODO: Add your control notification handler code here
}

void CLS_VCAEVENT_RiverClean::AutoShowParam()
{
	//提示默认值
	SetDlgItemInt(IDC_EDT_RIVER_MINSIZE, 10);
	SetDlgItemInt(IDC_EDT_RIVER_MAXSIZE, 30);
	SetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE, 10);
	SetDlgItemInt(IDC_EDT_RIVER_SENSITIVITY, 2);
}

void CLS_VCAEVENT_RiverClean::CheckValueLimits()
{
	int iValue;
	iValue = GetDlgItemInt(IDC_EDT_RIVER_MINSIZE);
	if(iValue < 8)
	{
		SetDlgItemInt(IDC_EDT_RIVER_MINSIZE, 8);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_RIVER_MINSIZE, 100);
	}

	iValue = GetDlgItemInt(IDC_EDT_RIVER_MAXSIZE);
	if(iValue < 8)
	{
		SetDlgItemInt(IDC_EDT_RIVER_MAXSIZE, 8);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_RIVER_MAXSIZE, 100);
	}

	iValue = GetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE);
	if(iValue < 8)
	{
		SetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE, 8);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE, 100);
	}

	iValue = GetDlgItemInt(IDC_EDT_RIVER_SENSITIVITY);
	if(iValue < 0)
	{
		SetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE, 0);
	}
	if(iValue > 5)
	{
		SetDlgItemInt(IDC_EDT_RIVER_PERCENTAGE, 5);
	}
}

void CLS_VCAEVENT_RiverClean::OnBnClickedButtonReset()
{
	AutoShowParam();
}
