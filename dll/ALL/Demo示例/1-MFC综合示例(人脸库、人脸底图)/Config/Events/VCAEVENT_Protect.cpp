// VCAEVENT_Running.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Protect.h"

#define LEN_2					2
#define LEN_3					3
#define DEFAULT_LIMIT_LEN_5		5
#define POINT_SUM				4
#define DEFAULT_ZORO			0
#define DEFAULT_RANGE			100
#define DEFAULT_MIN_SIZE		5
#define DEFAULT_MAX_SIZE		30
// CLS_VCAEVENT_Protect 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Protect, CDialog)

CLS_VCAEVENT_Protect::CLS_VCAEVENT_Protect(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Protect::IDD, pParent)
{
	m_iAreaPointNum = 0;
}

CLS_VCAEVENT_Protect::~CLS_VCAEVENT_Protect()
{
}

void CLS_VCAEVENT_Protect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_PROTECT_MIN_DISTANCE, m_edtMinDistance);
	DDX_Control(pDX, IDC_EDT_PROTECT_MIN_TIME, m_edtMinTime);
	DDX_Control(pDX, IDC_EDT_PROTECT_RESORT_TIME, m_edtResortTime);
	DDX_Control(pDX, IDC_GBO_PROTECT_AREA_COLOR, m_cboAreaColor);
	DDX_Control(pDX, IDC_GBO_PROTECT_ALARM_AREA_COLOR, m_cboAlarmAreaColor);
	DDX_Control(pDX, IDC_EDT_PROTECT_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_PROTECT_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_GBO_PROTECT_TARGET_TYPE, m_cboTargetType);
	DDX_Control(pDX, IDC_GBO_PROTECT_CHECK_MODE, m_cboCheckType);
	DDX_Control(pDX, IDC_CHK_PROTECT_SHOW_ALARM_RULE, m_chkShowAlarmRule);
	DDX_Control(pDX, IDC_CHK_PROTECT_SHOW_ALARM_STAT, m_chkShowAlarmStat);
	DDX_Control(pDX, IDC_CHK_PROTECT_SHOW_TARGET_BOX, m_chkShowTargetArea);
	DDX_Control(pDX, IDC_CHK_PROTECT_CHK_VALID, m_chkCheckValid);
	DDX_Control(pDX, IDC_GBO_PROTECT_DIRECTION_LIMIT, m_cboLimitDirection);
	DDX_Control(pDX, IDC_EDT_PROTECT_LIMIT_ANGLE, m_edtLimitAngle);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Protect, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_PROTECT_SET, &CLS_VCAEVENT_Protect::OnBnClickedBtnProtectSet)
	ON_BN_CLICKED(IDC_BTN_PROTECT_DRAW, &CLS_VCAEVENT_Protect::OnBnClickedBtnProtectDraw)
	ON_EN_CHANGE(IDC_EDT_PROTECT_MIN_SIZE, &CLS_VCAEVENT_Protect::OnEnChangeEdtProtectMinSize)
	ON_EN_CHANGE(IDC_EDT_PROTECT_MAX_SIZE, &CLS_VCAEVENT_Protect::OnEnChangeEdtProtectMaxSize)
END_MESSAGE_MAP()


BOOL CLS_VCAEVENT_Protect::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	m_edtMaxSize.SetLimitText(LEN_3);
	SetDlgItemInt(IDC_EDT_PROTECT_MIN_SIZE, DEFAULT_MAX_SIZE);
	m_edtMinSize.SetLimitText(LEN_2);
	SetDlgItemInt(IDC_EDT_PROTECT_MAX_SIZE, DEFAULT_MIN_SIZE);

	m_edtMinDistance.SetLimitText(DEFAULT_LIMIT_LEN_5);
	m_edtMinTime.SetLimitText(DEFAULT_LIMIT_LEN_5);
	m_edtResortTime.SetLimitText(DEFAULT_LIMIT_LEN_5);
	m_edtLimitAngle.SetLimitText(DEFAULT_LIMIT_LEN_5);

	m_chkCheckValid.SetCheck(BST_UNCHECKED);
	m_chkShowAlarmRule.SetCheck(BST_UNCHECKED);
	m_chkShowAlarmStat.SetCheck(BST_UNCHECKED);
	m_chkShowTargetArea.SetCheck(BST_UNCHECKED);

	//TODO 没有SetSize会使内存被频繁的的分配和拷贝，导致效率低下，和内存零碎
	cstrArrayColor.InsertAt(1, GetTextEx(IDS_VCA_COL_RED));
	cstrArrayColor.InsertAt(2, GetTextEx(IDS_VCA_COL_GREEN));
	cstrArrayColor.InsertAt(3, GetTextEx(IDS_VCA_COL_YELLOW));
	cstrArrayColor.InsertAt(4, GetTextEx(IDS_VCA_COL_BLUE));
	cstrArrayColor.InsertAt(5, GetTextEx(IDS_VCA_COL_MAGENTA));
	cstrArrayColor.InsertAt(6, GetTextEx(IDS_VCA_COL_CYAN));
	cstrArrayColor.InsertAt(7, GetTextEx(IDS_VCA_COL_BLACK));
	cstrArrayColor.InsertAt(8, GetTextEx(IDS_VCA_COL_WHITE));

	UI_UpdateDialogText();
	UI_UpdateParam();

	return TRUE; 
}

void CLS_VCAEVENT_Protect::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UI_UpdateDialogText();
		UI_UpdateParam();
	}
}

void CLS_VCAEVENT_Protect::OnLanguageChanged()
{
	UI_UpdateDialogText();
	UI_UpdateParam();
}

void CLS_VCAEVENT_Protect::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_CHK_PROTECT_CHK_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_PROTECT_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_PROTECT_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_PROTECT_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_PROTECT_ALARM_AREA_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_PROTECT_AREA_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_PROTECT_MIN_SIZE, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STC_PROTECT_MAX_SIZE, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STC_PROTECT_AREA, IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_BTN_PROTECT_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_PROTECT_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STC_PROTECT_TARGET_TYPE, IDS_VCA_TARGET_TYPE);
	SetDlgItemTextEx(IDC_STC_PROTECT_MIN_DISTANCE, IDS_VCA_MINDISTANCE);
	SetDlgItemTextEx(IDC_STC_PROTECT_MIN_TIME, IDS_VCA_MINTIME);
	SetDlgItemTextEx(IDC_STC_PROTECT_RESORT_TIME, IDS_RESORT_TIME);
	SetDlgItemTextEx(IDC_STC_PROTECT_DIRECTION_LIMIT, IDS_VCA_DIR_LIMIT);
	SetDlgItemTextEx(IDC_STC_PROTECT_LIMIT_ANGLE, IDS_LIMIT_ANGLE);
	SetDlgItemTextEx(IDC_STC_PROTECT_CHECK_MODE, IDS_CONFIG_ITS_TIMERANGE_DETECTMODE);

	//颜色
	m_cboAreaColor.ResetContent();
	m_cboAlarmAreaColor.ResetContent();
	for (int i = 0; i < cstrArrayColor.GetCount(); i++)
	{
		if (!((cstrArrayColor.GetAt(i)).IsEmpty()))
		{
			m_cboAreaColor.SetItemData(m_cboAreaColor.AddString(cstrArrayColor.GetAt(i)), i);
			m_cboAlarmAreaColor.SetItemData(m_cboAlarmAreaColor.AddString(cstrArrayColor.GetAt(i)), i);
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

	//检测模式
	m_cboCheckType.ResetContent();
	m_cboCheckType.SetItemData(m_cboCheckType.AddString(GetTextEx(IDS_VCA_INTRUSION)), 0);
	m_cboCheckType.SetItemData(m_cboCheckType.AddString(GetTextEx(IDS_VCA_ENTER)), 1);
	m_cboCheckType.SetItemData(m_cboCheckType.AddString(GetTextEx(IDS_VCA_LEAVE)), 2);
	m_cboCheckType.SetCurSel(0);

	//是否做方向限制
	m_cboLimitDirection.ResetContent();
	m_cboLimitDirection.SetItemData(m_cboLimitDirection.AddString(GetTextEx(IDS_ITS_NO)), 0);
	m_cboLimitDirection.SetItemData(m_cboLimitDirection.AddString(GetTextEx(IDS_ITS_YES)), 1);
	m_cboLimitDirection.SetCurSel(0);

}

void CLS_VCAEVENT_Protect::UI_UpdateParam()
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

	VCAProtect tVCAProtect = {0};
	tVCAProtect.iSize = sizeof(VCAProtect);
	tVCAProtect.stRule.iRuleID = m_iRuleID;
	tVCAProtect.stRule.iSceneID = m_iSceneID;

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_PROTECT, m_iChannelNO, &tVCAProtect, sizeof(tVCAProtect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Protect::NetClient_VCAGetConfig[VCA_CMD_PROTECT] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkCheckValid.SetCheck(tVCAProtect.stRule.iValid);
		m_chkShowAlarmRule.SetCheck(tVCAProtect.stDisplayParam.iDisplayRule);
		m_chkShowAlarmStat.SetCheck(tVCAProtect.stDisplayParam.iDisplayStat);
		m_chkShowTargetArea.SetCheck(tVCAProtect.iDisplayTarget);

		m_cboAlarmAreaColor.SetCurSel(GetCboSel(&m_cboAlarmAreaColor, tVCAProtect.stDisplayParam.iAlarmColor));
		m_cboAreaColor.SetCurSel(GetCboSel(&m_cboAreaColor,  tVCAProtect.stDisplayParam.iColor));
		m_cboCheckType.SetCurSel(GetCboSel(&m_cboCheckType, tVCAProtect.iMode));
		m_cboTargetType.SetCurSel(GetCboSel(&m_cboTargetType, tVCAProtect.iTargetTypeCheck));
		m_cboLimitDirection.SetCurSel(GetCboSel(&m_cboLimitDirection, tVCAProtect.iType));

		m_cboLimitDirection.
		SetDlgItemInt(IDC_EDT_PROTECT_MIN_DISTANCE, tVCAProtect.iMinDistance);
		SetDlgItemInt(IDC_EDT_PROTECT_MIN_TIME, tVCAProtect.iMinTime);
		SetDlgItemInt(IDC_EDT_PROTECT_RESORT_TIME, tVCAProtect.iResortTime);
		SetDlgItemInt(IDC_EDT_PROTECT_MIN_SIZE, tVCAProtect.iMiniSize);
		SetDlgItemInt(IDC_EDT_PROTECT_MAX_SIZE, tVCAProtect.iMaxSize);
		SetDlgItemInt(IDC_EDT_PROTECT_LIMIT_ANGLE, tVCAProtect.iDirection);



		int iPointNum = tVCAProtect.stPoints.iPointNum;
		CString cstPoint;
		for(int i = 0; i < iPointNum; i++)
		{
			cstPoint.AppendFormat("(%d,%d)", tVCAProtect.stPoints.stPoints[i].iX, tVCAProtect.stPoints.stPoints[i].iY);
		}
		SetDlgItemText(IDC_EDT_PROTECT_AREA, cstPoint);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Protect::NetClient_VCAGetConfig[VCA_CMD_PROTECT] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_Protect::OnBnClickedBtnProtectSet()
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

	VCAProtect tVCAProtect = {0};
	tVCAProtect.iSize = sizeof(VCAProtect);
	tVCAProtect.stRule.iRuleID = m_iRuleID;
	tVCAProtect.stRule.iSceneID = m_iSceneID;

	tVCAProtect.stRule.iValid = m_chkCheckValid.GetCheck();
	tVCAProtect.stDisplayParam.iDisplayRule = m_chkShowAlarmRule.GetCheck();
	tVCAProtect.stDisplayParam.iDisplayStat = m_chkShowAlarmStat.GetCheck();
	tVCAProtect.iDisplayTarget = m_chkShowTargetArea.GetCheck();

	tVCAProtect.stDisplayParam.iAlarmColor = (int)m_cboAlarmAreaColor.GetItemData(m_cboAlarmAreaColor.GetCurSel());
	tVCAProtect.stDisplayParam.iColor = (int)m_cboAlarmAreaColor.GetItemData(m_cboAlarmAreaColor.GetCurSel());
	tVCAProtect.stDisplayParam.iAlarmColor = (int)m_cboAreaColor.GetItemData(m_cboAreaColor.GetCurSel());
	tVCAProtect.iMode = (int)m_cboCheckType.GetItemData(m_cboCheckType.GetCurSel());
	tVCAProtect.iTargetTypeCheck = (int)m_cboTargetType.GetItemData(m_cboTargetType.GetCurSel());
	tVCAProtect.iType = (int)m_cboLimitDirection.GetItemData(m_cboLimitDirection.GetCurSel());


	tVCAProtect.iMinDistance = GetDlgItemInt(IDC_EDT_PROTECT_MIN_DISTANCE);
	tVCAProtect.iMinTime = GetDlgItemInt(IDC_EDT_PROTECT_MIN_TIME);
	tVCAProtect.iResortTime = GetDlgItemInt(IDC_EDT_PROTECT_RESORT_TIME);
	tVCAProtect.iMiniSize = GetDlgItemInt(IDC_EDT_PROTECT_MIN_SIZE);
	tVCAProtect.iMaxSize = GetDlgItemInt(IDC_EDT_PROTECT_MAX_SIZE);
	tVCAProtect.iDirection = GetDlgItemInt(IDC_EDT_PROTECT_LIMIT_ANGLE);

	tVCAProtect.stPoints.iPointNum = m_iAreaPointNum;

	if (0 >= m_iAreaPointNum)
	{
		AddLog(LOG_TYPE_FAIL,"","ProtectSet Illeage Point Num(%d)", m_iAreaPointNum);
		return;
	}

	CString cstPoint;
	vca_TPolygon stRegion = {0};
	GetDlgItemText(IDC_EDT_PROTECT_AREA, cstPoint);
	GetPolyFromString(cstPoint, tVCAProtect.stPoints.iPointNum, stRegion);
	memcpy(&tVCAProtect.stPoints, &stRegion, sizeof(stRegion));

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_PROTECT, m_iChannelNO, &tVCAProtect, sizeof(VCAProtect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Protect::NetClient_VCASetConfig[VCA_CMD_PROTECT] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Protect::NetClient_VCASetConfig[VCA_CMD_PROTECT] (%d, %d)", m_iLogonID, m_iChannelNO);
	}	
}

void CLS_VCAEVENT_Protect::OnBnClickedBtnProtectDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
	}

	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_perimeter);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		delete m_pDlgVideoView;
		m_pDlgVideoView = NULL;
		return;
	}

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		SetDlgItemText(IDC_EDT_PROTECT_AREA, cPointBuf);
		m_iAreaPointNum = iPointNum;
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Protect::OnEnChangeEdtProtectMinSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MIN_SIZE);
	if (iTemp < DEFAULT_ZORO || iTemp > 100)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Protect::Put Invalid Value(%d)", iTemp);
		SetDlgItemInt(IDC_EDT_PROTECT_MIN_SIZE, iTemp / 10);
	}
	return;
}

void CLS_VCAEVENT_Protect::OnEnChangeEdtProtectMaxSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MIN_SIZE);
	if (iTemp < DEFAULT_ZORO || iTemp > 100)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Protect::Put Invalid Value(%d)", iTemp);
		SetDlgItemInt(IDC_EDT_PROTECT_MAX_SIZE, iTemp / 10);
	}
	return;
}
