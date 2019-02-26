// VCAEVENT_Running.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_WindowDetevtion.h"

#define LEN_2								2
#define LEN_3								3
#define DEFAULT_LIMIT_LEN_5					5
#define POINT_SUM							4
#define DEFAULT_ZORO						0
#define DEFAULT_RANGE						100
#define DEFAULT_MIN_SIZE					5
#define DEFAULT_MAX_SIZE					30
#define DEFAULT_MAX_SENSIBILITY				80
#define MAX_ALARM_COLOR_TYPE				10
// CLS_VCAEVENT_WindowDetection 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_WindowDetection, CDialog)

CLS_VCAEVENT_WindowDetection::CLS_VCAEVENT_WindowDetection(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_WindowDetection::IDD, pParent)
{
	m_cstrArrayColor.RemoveAll();
	memset(&m_tWinPosInfo, 0, sizeof(m_tWinPosInfo));
	m_pDlgDrawVideoView = NULL;
}

CLS_VCAEVENT_WindowDetection::~CLS_VCAEVENT_WindowDetection()
{
	if (m_pDlgDrawVideoView)
	{
		if (IsWindow(m_pDlgDrawVideoView->GetSafeHwnd()))
		{
			m_pDlgDrawVideoView->DestroyWindow();
		}

		delete m_pDlgDrawVideoView;
		m_pDlgDrawVideoView = NULL;
	}
}

void CLS_VCAEVENT_WindowDetection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GBO_WINDOW_DETECTION_AREA_COLOR, m_cboAreaColor);
	DDX_Control(pDX, IDC_GBO_WINDOW_DETECTION_ALARM_AREA_COLOR, m_cboAlarmAreaColor);
	DDX_Control(pDX, IDC_EDT_WINDOW_DETECTION_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_WINDOW_DETECTION_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_GBO_WINDOW_DETECTION_TARGET_TYPE, m_cboTargetType);
	DDX_Control(pDX, IDC_CHK_WINDOW_DETECTION_SHOW_ALARM_RULE, m_chkShowAlarmRule);
	DDX_Control(pDX, IDC_CHK_WINDOW_DETECTION_SHOW_ALARM_STAT, m_chkShowAlarmStat);
	DDX_Control(pDX, IDC_CHK_WINDOW_DETECTION_SHOW_TARGET_BOX, m_chkShowTargetArea);
	DDX_Control(pDX, IDC_CHK_WINDOW_DETECTION_CHK_VALID, m_chkCheckValid);
}							


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_WindowDetection, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_WINDOW_DETECTION_SET, &CLS_VCAEVENT_WindowDetection::OnBnClickedBtnProtectSet)
	ON_EN_CHANGE(IDC_EDT_WINDOW_DETECTION_MIN_SIZE, &CLS_VCAEVENT_WindowDetection::OnEnChangeEdtProtectMinSize)
	ON_EN_CHANGE(IDC_EDT_WINDOW_DETECTION_MAX_SIZE, &CLS_VCAEVENT_WindowDetection::OnEnChangeEdtProtectMaxSize)
	ON_EN_CHANGE(IDC_EDT_WINDOW_DETECTION_SENSIBILITY, &CLS_VCAEVENT_WindowDetection::OnEnChangeEdtWindowDetectionSensibility)
	ON_BN_CLICKED(IDC_BTN_WINDOW_DETECTION_DRAW, &CLS_VCAEVENT_WindowDetection::OnBnClickedBtnWindowDetectionDraw)
END_MESSAGE_MAP()


BOOL CLS_VCAEVENT_WindowDetection::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	m_edtMaxSize.SetLimitText(LEN_3);
	SetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MIN_SIZE, DEFAULT_MAX_SIZE);
	m_edtMinSize.SetLimitText(LEN_2);
	SetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MAX_SIZE, DEFAULT_MIN_SIZE);

	m_chkCheckValid.SetCheck(BST_UNCHECKED);
	m_chkShowAlarmRule.SetCheck(BST_UNCHECKED);
	m_chkShowAlarmStat.SetCheck(BST_UNCHECKED);
	m_chkShowTargetArea.SetCheck(BST_UNCHECKED);

	UI_UpdateDialogText();
	UI_UpdateParam();

	return TRUE; 
}

void CLS_VCAEVENT_WindowDetection::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UI_UpdateDialogText();
		UI_UpdateParam();
	}
}

void CLS_VCAEVENT_WindowDetection::OnMainNotify( int _iLogonID,int _wParam, void* _lParam, void*_iUserData )
{
	if (m_pDlgDrawVideoView)
	{
		m_pDlgDrawVideoView->OnMainNotify(_iLogonID, _wParam, _lParam, _iUserData);
	}
}

void CLS_VCAEVENT_WindowDetection::OnLanguageChanged()
{
	UI_UpdateDialogText();
	UI_UpdateParam();
}

void CLS_VCAEVENT_WindowDetection::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_CHK_WINDOW_DETECTION_CHK_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_WINDOW_DETECTION_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_WINDOW_DETECTION_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_WINDOW_DETECTION_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_WINDOW_DETECTION_ALARM_AREA_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_WINDOW_DETECTION_AREA_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_WINDOW_DETECTION_MIN_SIZE, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STC_WINDOW_DETECTION_MAX_SIZE, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STC_WINDOW_DETECTION_AREA, IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_BTN_WINDOW_DETECTION_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_WINDOW_DETECTION_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STC_WINDOW_DETECTION_TARGET_TYPE, IDS_VCA_TARGET_TYPE);
	SetDlgItemTextEx(IDC_STC_WINDOW_DETECTION_SENSIBILITY, IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);

	m_cstrArrayColor.RemoveAll();
	m_cstrArrayColor.SetSize(MAX_ALARM_COLOR_TYPE);
	m_cstrArrayColor.InsertAt(1, GetTextEx(IDS_VCA_COL_RED));
	m_cstrArrayColor.InsertAt(2, GetTextEx(IDS_VCA_COL_GREEN));
	m_cstrArrayColor.InsertAt(3, GetTextEx(IDS_VCA_COL_YELLOW));
	m_cstrArrayColor.InsertAt(4, GetTextEx(IDS_VCA_COL_BLUE));
	m_cstrArrayColor.InsertAt(5, GetTextEx(IDS_VCA_COL_MAGENTA));
	m_cstrArrayColor.InsertAt(6, GetTextEx(IDS_VCA_COL_CYAN));
	m_cstrArrayColor.InsertAt(7, GetTextEx(IDS_VCA_COL_BLACK));
	m_cstrArrayColor.InsertAt(8, GetTextEx(IDS_VCA_COL_WHITE));
	m_cstrArrayColor.FreeExtra();

	//颜色
	m_cboAreaColor.ResetContent();
	m_cboAlarmAreaColor.ResetContent();
	for (int i = 0; i < m_cstrArrayColor.GetCount(); i++)
	{
		if (!((m_cstrArrayColor.GetAt(i)).IsEmpty()))
		{
			m_cboAreaColor.SetItemData(m_cboAreaColor.AddString(m_cstrArrayColor.GetAt(i)), i);
			m_cboAlarmAreaColor.SetItemData(m_cboAlarmAreaColor.AddString(m_cstrArrayColor.GetAt(i)), i);
		}
	}

	m_cboAreaColor.SetCurSel(0);
	m_cboAlarmAreaColor.SetCurSel(0);

	//区分目标类型
	m_cboTargetType.ResetContent();
	m_cboTargetType.SetItemData(m_cboTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_NONE)), 0);
	m_cboTargetType.SetItemData(m_cboTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_PEOPLE)), 1);
	m_cboTargetType.SetItemData(m_cboTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_CAR)), 2);
	m_cboTargetType.SetItemData(m_cboTargetType.AddString(GetTextEx(IDS_VCA_TARCHK_BOTH)), 3);
	m_cboTargetType.SetCurSel(0);
}

void CLS_VCAEVENT_WindowDetection::UI_UpdateParam()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage LogId(%d)", m_iLogonID);
		return;
	}

	if (m_iChannelNO < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage ChannelNo(%d)", m_iChannelNO);
		return;
	}

	VCAWindowDetection tVCAWindowInfo = {0};
	tVCAWindowInfo.iBufSize = sizeof(VCAWindowDetection);
	tVCAWindowInfo.tRule.iRuleID = m_iRuleID;
	tVCAWindowInfo.tRule.iSceneID = m_iSceneID;

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_WINDOW_DETECTION, m_iChannelNO, &tVCAWindowInfo, sizeof(tVCAWindowInfo));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Protect::NetClient_VCAGetConfig[VCA_CMD_WINDOW_DETECTION] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkCheckValid.SetCheck(tVCAWindowInfo.tRule.iValid);
		m_chkShowAlarmRule.SetCheck(tVCAWindowInfo.tDisplayParam.iDisplayRule);
		m_chkShowAlarmStat.SetCheck(tVCAWindowInfo.tDisplayParam.iDisplayStat);
		m_chkShowTargetArea.SetCheck(tVCAWindowInfo.iDisplayTarget);

		m_cboAlarmAreaColor.SetCurSel(GetCboSel(&m_cboAlarmAreaColor, tVCAWindowInfo.tDisplayParam.iAlarmColor));
		m_cboAreaColor.SetCurSel(GetCboSel(&m_cboAreaColor,  tVCAWindowInfo.tDisplayParam.iColor));
		m_cboTargetType.SetCurSel(GetCboSel(&m_cboTargetType, tVCAWindowInfo.iTargetTypeCheck));

		SetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MIN_SIZE, tVCAWindowInfo.iMiniSize);
		SetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MAX_SIZE, tVCAWindowInfo.iMaxSize);


		int iPolygonNum = tVCAWindowInfo.iDoubleCircleNum;
		if (iPolygonNum > MAX_WINDOW_DOUBLE_CIRCLE_NUM)
		{
			AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_WindowDetection::NetClient_VCAGetConfig[VCA_CMD_WINDOW_DETECTION] (%d, %d)", m_iLogonID, m_iChannelNO);
		}

		m_tWinPosInfo.iDoubleCircleNum = iPolygonNum;
		memcpy(m_tWinPosInfo.tWindowDetectionPos, tVCAWindowInfo.tWindowDetectionPos, min(sizeof(m_tWinPosInfo.tWindowDetectionPos), sizeof(tVCAWindowInfo.tWindowDetectionPos)));
		UI_ShowPolygonInEdit(&m_tWinPosInfo);
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_WindowDetection::NetClient_VCAGetConfig[VCA_CMD_WINDOW_DETECTION] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_WindowDetection::OnBnClickedBtnProtectSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage LogId(%d)", m_iLogonID);
		return;
	}

	if (m_iChannelNO < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage ChannelNo(%d)", m_iChannelNO);
		return;
	}

	VCAWindowDetection tVCAWinInfo = {0};
	tVCAWinInfo.iBufSize = sizeof(VCAWindowDetection);
	tVCAWinInfo.tRule.iRuleID = m_iRuleID;
	tVCAWinInfo.tRule.iSceneID = m_iSceneID;

	tVCAWinInfo.tRule.iValid = m_chkCheckValid.GetCheck();
	tVCAWinInfo.tDisplayParam.iDisplayRule = m_chkShowAlarmRule.GetCheck();
	tVCAWinInfo.tDisplayParam.iDisplayStat = m_chkShowAlarmStat.GetCheck();
	tVCAWinInfo.iDisplayTarget = m_chkShowTargetArea.GetCheck();

	tVCAWinInfo.tDisplayParam.iAlarmColor = (int)m_cboAlarmAreaColor.GetItemData(m_cboAlarmAreaColor.GetCurSel());
	tVCAWinInfo.tDisplayParam.iColor = (int)m_cboAlarmAreaColor.GetItemData(m_cboAlarmAreaColor.GetCurSel());
	tVCAWinInfo.tDisplayParam.iAlarmColor = (int)m_cboAreaColor.GetItemData(m_cboAreaColor.GetCurSel());
	tVCAWinInfo.iTargetTypeCheck = (int)m_cboTargetType.GetItemData(m_cboTargetType.GetCurSel());


	tVCAWinInfo.iMiniSize = GetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MIN_SIZE);
	tVCAWinInfo.iMaxSize = GetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MAX_SIZE);
	tVCAWinInfo.iSensitivity = GetDlgItemInt(IDC_EDT_WINDOW_DETECTION_SENSIBILITY);

	//TODO 从划线界面将划线信息复制到成员变量里面
	tVCAWinInfo.iDoubleCircleNum = m_tWinPosInfo.iDoubleCircleNum;
	memcpy(tVCAWinInfo.tWindowDetectionPos, m_tWinPosInfo.tWindowDetectionPos, min(sizeof(m_tWinPosInfo.tWindowDetectionPos), sizeof(tVCAWinInfo.tWindowDetectionPos)));

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_WINDOW_DETECTION, m_iChannelNO, &tVCAWinInfo, sizeof(VCAWindowDetection));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_WindowDetection::NetClient_VCASetConfig[VCA_CMD_WINDOW_DETECTION] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_WindowDetection::NetClient_VCASetConfig[VCA_CMD_WINDOW_DETECTION] (%d, %d)", m_iLogonID, m_iChannelNO);
	}	
}

void CLS_VCAEVENT_WindowDetection::OnEnChangeEdtProtectMinSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MIN_SIZE);
	if (iTemp < DEFAULT_ZORO || iTemp > DEFAULT_RANGE)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_WindowDetection::Put Invalid Value(%d)", iTemp);
		SetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MIN_SIZE, iTemp / 10);
	}
	return;
}

void CLS_VCAEVENT_WindowDetection::OnEnChangeEdtProtectMaxSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MAX_SIZE);
	if (iTemp < DEFAULT_ZORO || iTemp > DEFAULT_RANGE)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_WindowDetection::Put Invalid Value(%d)", iTemp);
		SetDlgItemInt(IDC_EDT_WINDOW_DETECTION_MAX_SIZE, iTemp / 10);
	}
	return;
}

void CLS_VCAEVENT_WindowDetection::OnEnChangeEdtWindowDetectionSensibility()
{
	int iTemp = GetDlgItemInt(IDC_EDT_WINDOW_DETECTION_SENSIBILITY);
	if (iTemp < DEFAULT_ZORO || iTemp > DEFAULT_RANGE)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_WindowDetection::Put Invalid Value(%d)", iTemp);
		SetDlgItemInt(IDC_EDT_WINDOW_DETECTION_SENSIBILITY, iTemp / 10);
	}
	return;
}

void CLS_VCAEVENT_WindowDetection::OnBnClickedBtnWindowDetectionDraw()
{
	if (NULL == m_pDlgDrawVideoView)
	{
		m_pDlgDrawVideoView = new CLS_VideoViewForDrawWindowDetection();
		if (NULL == m_pDlgDrawVideoView)
		{
			return;
		}
	}

	m_pDlgDrawVideoView->InitVideoParam(m_iLogonID, m_iChannelNO, m_iStreamNO);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	m_pDlgDrawVideoView->SetDrawPolygonInfo(&m_tWinPosInfo, sizeof(m_tWinPosInfo));
	if (IDOK == m_pDlgDrawVideoView->DoModal())
	{
		m_pDlgDrawVideoView->GetDrawPolygonInfo(&m_tWinPosInfo, sizeof(m_tWinPosInfo));
		UI_ShowPolygonInEdit(&m_tWinPosInfo);
	}

	m_pDlgDrawVideoView->DestroyWindow();
	delete m_pDlgDrawVideoView;
	m_pDlgDrawVideoView = NULL;
}

void CLS_VCAEVENT_WindowDetection::UI_ShowPolygonInEdit(VCAWindowDetectionPosInfo* _ptPolygonInfo)
{
	if (NULL == _ptPolygonInfo)
	{
		return;
	}

	int iPolygonNum = _ptPolygonInfo->iDoubleCircleNum;
	if (iPolygonNum > MAX_WINDOW_DOUBLE_CIRCLE_NUM)
	{
		return;
	}

	CString cstPoint;
	for(int i = 0; i < iPolygonNum; i++)
	{
		WindowDetectionPos& tWinPolygonInfo = _ptPolygonInfo->tWindowDetectionPos[i];

		cstPoint += _T("{");
		cstPoint += _T("[");
		//外框坐标
		int iOutPolygonPointsNum = tWinPolygonInfo.iOutPolygonPointNum;
		for (int iTempOutPos = 0; iTempOutPos < iOutPolygonPointsNum && iOutPolygonPointsNum < VCA_MAX_POLYGON_POINT_NUM; ++iTempOutPos)
		{
			cstPoint.AppendFormat("(%d,%d)", tWinPolygonInfo.stOutPolygonPoints[iTempOutPos].iX, tWinPolygonInfo.stOutPolygonPoints[iTempOutPos].iY);
		}
		cstPoint += _T("],");
		cstPoint += _T("[");
		//内框坐标
		int iInnerPointNum = tWinPolygonInfo.iInnerPolygonPointNum;
		for (int iTempInnerPos = 0; iTempInnerPos < iInnerPointNum && iInnerPointNum < VCA_MAX_POLYGON_POINT_NUM; ++iTempInnerPos)
		{
			cstPoint.AppendFormat("(%d,%d)", tWinPolygonInfo.stInnerPolygonPoints[iTempInnerPos].iX, tWinPolygonInfo.stInnerPolygonPoints[iTempInnerPos].iY);
		}
		cstPoint += _T("]");
		cstPoint += _T("}; \r\n");
	}
	SetDlgItemText(IDC_EDT_WINDOW_DETECTION_AREA, cstPoint);
}

