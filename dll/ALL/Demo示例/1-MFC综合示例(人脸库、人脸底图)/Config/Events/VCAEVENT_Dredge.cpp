
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Dredge.h"


#define MAX_ZOOM_SIZE		20
#define MIN_ZOOM_SIZE		1
#define MIN_MIN_SIZE		0		//最小尺寸最小值

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Dredge, CDialog)

CLS_VCAEVENT_Dredge::CLS_VCAEVENT_Dredge(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Dredge::IDD, pParent)
{

}

CLS_VCAEVENT_Dredge::~CLS_VCAEVENT_Dredge()
{
}

void CLS_VCAEVENT_Dredge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_DREDGE_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_DREDGE_AREA_COLOR, m_cboAreaColor);
	DDX_Control(pDX, IDC_CBO_DREDGE_RECOGNIZE_MODE, m_cboRecgMode);
	DDX_Control(pDX, IDC_CHK_DREDGE_RULE_DISPLAY, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHK_DREDGE_DISPLAY_STATE, m_chkDisplayAlarmNum);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Dredge, CDialog)
	ON_BN_CLICKED(IDC_BTN_DREDGE_SET, &CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgeSet)
	ON_BN_CLICKED(IDC_BTN_DREDGE_POINTS_DRAW, &CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgePointsDraw)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_DREDGE_STOP, &CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgeStop)
	ON_BN_CLICKED(IDC_BTN_DREDGE_START, &CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgeStart)
	ON_BN_CLICKED(IDC_BUTTON_DREDGE_AUTO, &CLS_VCAEVENT_Dredge::OnBnClickedButtonDredgeAuto)
	ON_EN_CHANGE(IDC_EDT_ZOOM_CONTROL, &CLS_VCAEVENT_Dredge::OnEnChangeEdtZoomControl)
END_MESSAGE_MAP()


BOOL CLS_VCAEVENT_Dredge::OnInitDialog()
{
	CDialog::OnInitDialog();

	UI_UpdateDialog();

	return TRUE;
}

void CLS_VCAEVENT_Dredge::OnLanguageChanged()
{
	UI_UpdateDialog();
}

void CLS_VCAEVENT_Dredge::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		UI_UpdatePage();
	}
}

void CLS_VCAEVENT_Dredge::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_DREDGE_AREA_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_DREDGE_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_CHK_DREDGE_RULE_DISPLAY, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHK_DREDGE_DISPLAY_STATE, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STC_DREDGE_RECOGNIZE_MODE, IDS_VCA_RIVER_RECOGNIZE_MODE);
	SetDlgItemTextEx(IDC_STC_DREDGE_MINSIZE, IDS_VCA_MINSIZE);
	SetDlgItemTextEx(IDC_STC_DREDGE_MAXSIZE, IDS_VCA_MAXSIZE);
	SetDlgItemTextEx(IDC_STC_DREDGE_PERCENTAGE, IDS_VCA_RIVER_PERCENTAGE);
	SetDlgItemTextEx(IDC_STC_DREDGE_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STC_DREDGE_POINTS, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_STC_DREDGE_ALARMTIME, IDS_VCA_ALARMTIME);
	SetDlgItemTextEx(IDC_STC_DREDGE_SENSITIVITY, IDS_VCA_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_DREDGE_SENSITIVITY_RANGE, IDS_STC_FIGHT_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_DREDGE_MINSIZE_RANGE,IDC_STC_DREDGE_MINSIZE_RANGE);
	SetDlgItemTextEx(IDC_STC_DREDGE_MAXSIZE_RANGE,IDS_VCA_MAXSIZE_RANGE);
	SetDlgItemTextEx(IDC_BUTTON_DREDGE_AUTO, IDC_BUTTON_DREDGE_AUTO);
	SetDlgItemTextEx(IDC_BTN_DREDGE_POINTS_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_DREDGE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_DREDGE_STOP, IDS_STOP);
	SetDlgItemTextEx(IDC_BTN_DREDGE_START, IDS_START);
	SetDlgItemTextEx(IDC_STC_ZOOM_CONTROL, IDS_ZOOM_CONTROL_SIZE);
	SetDlgItemTextEx(IDC_STC_DREDGE_ALARM_TIME, IDS_DOME_PTZ_WAIT_SECOND);

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


void CLS_VCAEVENT_Dredge::UI_UpdatePage()
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

	VCADredge st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;
	int iCmd = VCA_CMD_DREDGE;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet == 0)
	{
		m_chkDisplayRule.SetCheck(st.stDisplayParam.iDisplayRule);
		m_chkDisplayAlarmNum.SetCheck(st.stDisplayParam.iDisplayStat);
		m_cboAreaColor.SetCurSel(st.stDisplayParam.iColor - 1);
		m_cboAlarmColor.SetCurSel(st.stDisplayParam.iAlarmColor - 1);

		SetDlgItemInt(IDC_EDT_DREDGE_MINSIZE,st.iMinSize);
		SetDlgItemInt(IDC_EDT_DREDGE_MAXSIZE,st.iMaxSize);
		SetDlgItemInt(IDC_EDT_DREDGE_SENSITIVITY,st.iSensitivity);
		SetDlgItemInt(IDC_EDT_DREDGE_ALARMTIME,st.iTimeMin);
		SetDlgItemInt(IDC_EDT_DREDGE_POINTNUM,st.stPoints.iPointNum);
		int _iPointNum = st.stPoints.iPointNum;
		CString strPointArray;
		CString strPoint[VCA_MAX_POLYGON_POINT_NUMEX];
		for(int i = 0; i != _iPointNum; i++)
		{
			strPoint[i].Format("(%d,%d)", st.stPoints.stPoints[i].iX, st.stPoints.stPoints[i].iY);
			strPointArray += strPoint[i];
		}
		SetDlgItemText(IDC_EDT_DREDGE_POINTS,strPointArray);
	}
	else
	{
		AutoShowParam();
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}

	UI_UpdateZoomControl();
}


void CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgeSet()
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

	VCADredge st = {0};
	st.iBufSize = sizeof(st);
	st.stRule.iRuleID = m_iRuleID;
	st.stRule.iSceneID = m_iSceneID;

	st.stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	st.stDisplayParam.iDisplayStat = m_chkDisplayAlarmNum.GetCheck();
	st.stDisplayParam.iColor = m_cboAreaColor.GetCurSel() + 1;
	st.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel() + 1;
	st.iMinSize = GetDlgItemInt(IDC_EDT_DREDGE_MINSIZE);
	st.iMaxSize = GetDlgItemInt(IDC_EDT_DREDGE_MAXSIZE);
	st.iSensitivity = GetDlgItemInt(IDC_EDT_DREDGE_SENSITIVITY);
	st.iTimeMin = GetDlgItemInt(IDC_EDT_DREDGE_ALARMTIME);
	st.stPoints.iPointNum = GetDlgItemInt(IDC_EDT_DREDGE_POINTNUM);

	CString strPointStr;
	vca_TPolygon stRegion = {0};
	GetDlgItemText(IDC_EDT_DREDGE_POINTS, strPointStr);
	GetPolyFromString(strPointStr, st.stPoints.iPointNum, stRegion);
	memcpy(&st.stPoints, &stRegion, sizeof(stRegion));

	int iCmd = VCA_CMD_DREDGE;
	iRet = NetClient_VCASetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet >= 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}

	SetZoomControl();

	//恢复智能分析
	int iState = 1;
	NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iState, sizeof(int));
}

void CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgePointsDraw()
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
		GetDlgItem(IDC_EDT_DREDGE_POINTS)->SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDT_DREDGE_POINTNUM, iPointNum);
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgeStop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_Dredge::OnBnClickedBtnDredgeStart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_Dredge::AutoShowParam()
{
	SetDlgItemInt(IDC_EDT_DREDGE_MINSIZE, 10);
	SetDlgItemInt(IDC_EDT_DREDGE_MAXSIZE, 30);
	SetDlgItemInt(IDC_EDT_DREDGE_SENSITIVITY, 2);
}

void CLS_VCAEVENT_Dredge::CheckValueLimits()
{
	int iValue;
	iValue = GetDlgItemInt(IDC_EDT_DREDGE_MINSIZE);
	if(iValue < MIN_MIN_SIZE)
	{
		SetDlgItemInt(IDC_EDT_DREDGE_MINSIZE, MIN_MIN_SIZE);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_DREDGE_MINSIZE, 100);
	}

	iValue = GetDlgItemInt(IDC_EDT_DREDGE_MAXSIZE);
	if(iValue < 8)
	{
		SetDlgItemInt(IDC_EDT_DREDGE_MAXSIZE, 8);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_DREDGE_MAXSIZE, 100);
	}
	iValue = GetDlgItemInt(IDC_EDT_DREDGE_SENSITIVITY);
	if(iValue < 0)
	{
		SetDlgItemInt(IDC_EDT_DREDGE_SENSITIVITY, 0);
	}
	if(iValue > 5)
	{
		SetDlgItemInt(IDC_EDT_DREDGE_SENSITIVITY, 5);
	}
}

void CLS_VCAEVENT_Dredge::OnBnClickedButtonDredgeAuto()
{
	AutoShowParam();
}

void CLS_VCAEVENT_Dredge::SetZoomControl()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illegal LogonId(%d)!", m_iLogonID);
		return;
	}
	int iRet = RET_FAILED;
	ZoomControl tZoomControl = {0};
	tZoomControl.iSize = sizeof(ZoomControl);
	tZoomControl.iZoomSize = GetDlgItemInt(IDC_EDT_ZOOM_CONTROL);

	iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_ZOOM_CONTROL, m_iChannelNO, &tZoomControl, sizeof(ZoomControl));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig  ZOOM_CONTROL failed ! logonID(%d)", m_iLogonID);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig  ZOOM_CONTROL Success ! logonID(%d)", m_iLogonID);
	goto EXIT_FUNC;

EXIT_FUNC:
	return;
}

void CLS_VCAEVENT_Dredge::UI_UpdateZoomControl()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illegal LogonId(%d)!", m_iLogonID);
		return;
	}

	int iRet = RET_FAILED;
	ZoomControl tZoomControl = {0};
	tZoomControl.iSize = sizeof(ZoomControl);
	int iReturnSize = 0;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ZOOM_CONTROL, m_iChannelNO, &tZoomControl, sizeof(ZoomControl), &iReturnSize);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig  ZOOM_CONTROL failed ! logonID(%d)", m_iLogonID);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig  ZOOM_CONTROL Success ! logonID(%d)", m_iLogonID);
	SetDlgItemInt(IDC_EDT_ZOOM_CONTROL, tZoomControl.iZoomSize);

EXIT_FUNC:
	return;
}

void CLS_VCAEVENT_Dredge::OnEnChangeEdtZoomControl()
{
	int iZoomSize = GetDlgItemInt(IDC_EDT_ZOOM_CONTROL);
	if (iZoomSize > MAX_ZOOM_SIZE)
	{
		SetDlgItemInt(IDC_EDT_ZOOM_CONTROL, MAX_ZOOM_SIZE);
		goto EXIT_FUNC;
	}

	if (iZoomSize < MIN_ZOOM_SIZE)
	{
		SetDlgItemInt(IDC_EDT_ZOOM_CONTROL, MIN_ZOOM_SIZE);
		goto EXIT_FUNC;	
	}

EXIT_FUNC:
	return;
}
