// VCAEVENT_WaterLevelDetection.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_WaterLevelDetection.h"


// CLS_VCAEVENT_WaterLevelDetection dialog

const int CONST_iPointValue = 55555;

const int CONST_iMinIntervel = 1;
const int CONST_iMaxIntervel = 1440;

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_WaterLevelDetection, CDialog)

CLS_VCAEVENT_WaterLevelDetection::CLS_VCAEVENT_WaterLevelDetection(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_WaterLevelDetection::IDD, pParent)
{
	memset(&m_tGetWld, 0, sizeof(m_tGetWld));
	m_iReferCount = 0;
	m_vecPresetScene.clear();
}

CLS_VCAEVENT_WaterLevelDetection::~CLS_VCAEVENT_WaterLevelDetection()
{
}

void CLS_VCAEVENT_WaterLevelDetection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_WLD_RULE_DISPLAY, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHK_WLD_DISPLAY_STATE, m_chkDisplayAlarmCount);
	DDX_Control(pDX, IDC_CBO_WLD_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_WLD_AREA_COLOR, m_cboAreaColor);
	DDX_Control(pDX, IDC_COMBO_WLD_GaugeType, m_cboGaugeType);
	DDX_Control(pDX, IDC_COMBO_WLD_PRESET_NO, m_cboPresetNo);
	DDX_Control(pDX, IDC_EDT_WLD_SnapIntervel, m_edtSnapIntervel);
	DDX_Control(pDX, IDC_EDT_WLD_BaseValue, m_edtBaseValue);
	DDX_Control(pDX, IDC_EDT_WLD_CurPresetID, m_edtCurPresetID);
	DDX_Control(pDX, IDC_EDIT_WLD_PRESETRANGE_BEGIN, m_edtPresetValueLow);
	DDX_Control(pDX, IDC_EDIT_WLD_PRESETRANGE_END, m_edtPresetValueHigh);
	DDX_Control(pDX, IDC_EDT_WLD_GaugeRect, m_edtGaugeRect);
	DDX_Control(pDX, IDC_EDT_WLD_AssistRect, m_edtAssistRect);
	DDX_Control(pDX, IDC_EDT_WLD_GaugeLine, m_edtGaugeLine);
	DDX_Control(pDX, IDC_EDT_WLD_ReferPoint, m_edtReferPoints);
	DDX_Control(pDX, IDC_EDIT_VCA_WLD_POINT_VALUE, m_edtReferPointValue);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_WaterLevelDetection, CDialog)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_WLD_PRESET_NO, &CLS_VCAEVENT_WaterLevelDetection::OnCbnSelchangeComboWldPresetNo)
	ON_BN_CLICKED(IDC_BTN_WLD_GaugeRect, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawGaugeRect)
	ON_BN_CLICKED(IDC_BTN_WLD_AssistRect, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawAssistRect)
	ON_BN_CLICKED(IDC_BTN_WLD_GaugeLine, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawGaugeLine)
	ON_BN_CLICKED(IDC_BTN_WLD_ReferPoint, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawReferPoints)
	ON_BN_CLICKED(IDC_BUTTON_WLD_ADD_PRESET_SCENE, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldAddPresetScene)
	ON_BN_CLICKED(IDC_BUTTON_WLD_DELETE_PRESET_SCENE, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldDeletePresetScene)
	ON_BN_CLICKED(IDC_BUTTON_WLD_SET, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldSet)
	ON_BN_CLICKED(IDC_BUTTON_WLD_CLEAR_PRESET_SCENE, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldClearPresetScene)
	ON_BN_CLICKED(IDC_BUTTON_VCA_WLD_SHOW_REGION, &CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonVcaWldShowRegion)
END_MESSAGE_MAP()


// CLS_VCAEVENT_WaterLevelDetection message handlers

BOOL CLS_VCAEVENT_WaterLevelDetection::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtSnapIntervel.SetLimitText(LEN_16);
	m_edtBaseValue.SetLimitText(LEN_16);
	m_edtCurPresetID.SetLimitText(LEN_16);
	m_edtPresetValueLow.SetLimitText(LEN_16);
	m_edtPresetValueHigh.SetLimitText(LEN_16);
	m_edtGaugeRect.SetLimitText(LEN_256);
	m_edtAssistRect.SetLimitText(LEN_256);
	m_edtGaugeLine.SetLimitText(LEN_256);
	m_edtReferPoints.SetLimitText(LEN_256);
	m_edtReferPointValue.SetLimitText(LEN_16);
	UI_UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_WaterLevelDetection::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		UI_UpdateSdkParam();
	}
}

void CLS_VCAEVENT_WaterLevelDetection::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_WLD_AREA_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_WLD_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_CHK_WLD_RULE_DISPLAY, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHK_WLD_DISPLAY_STATE, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_BUTTON_WLD_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_WLD_GaugeRect, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_WLD_AssistRect, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_WLD_GaugeLine, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_WLD_ReferPoint, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_STC_WLD_INTERVAL, IDS_CFG_VCA_WLD_INTERVAL);
	SetDlgItemTextEx(IDC_STC_WLD_SnapIntervel, IDS_VCA_WLD_INTERVAL);
	SetDlgItemTextEx(IDC_STC_WLD_BaseValue, IDS_VCA_WLD_BWL);
	SetDlgItemTextEx(IDC_STC_WLD_CurPresetID, IDS_VCA_WLD_CUR_PRESET);
	SetDlgItemTextEx(IDC_STATIC_WLD_GaugeType, IDS_VCA_WLD_GAUGE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_WLD_PRESET_SCENE_INFO, IDS_VCA_WLD_PRESET_SCENE);
	SetDlgItemTextEx(IDC_STATIC_WLD_PRESET_NO, IDS_VCA_WLD_PRESET_NUMBER);
	SetDlgItemTextEx(IDC_STATIC_WLD_PRESETRANGE, IDS_VCA_WLD_PRESET_RANGE);
	SetDlgItemTextEx(IDC_STC_WLD_GaugeRect, IDS_VCA_WLD_GAUGE_AREA);
	SetDlgItemTextEx(IDC_STC_WLD_AssistRect, IDS__VCA_WLD_AID_AREA);
	SetDlgItemTextEx(IDC_STC_WLD_GaugeLine, IDS_VCA_WLD_REFER_LINE);
	SetDlgItemTextEx(IDC_STC_WLD_ReferPoint, IDS_VCA_WLD_REFER_POINT);
	SetDlgItemTextEx(IDC_BUTTON_WLD_ADD_PRESET_SCENE, IDS_VCA_WLD_ADD);
	SetDlgItemTextEx(IDC_BUTTON_WLD_DELETE_PRESET_SCENE, IDS_VCA_WLD_DELETE_PRESET_SCENE);
	SetDlgItemTextEx(IDC_BUTTON_WLD_CLEAR_PRESET_SCENE, IDS_VCA_WLD_CLEAR_PRESET_SCENE);
	SetDlgItemTextEx(IDC_STC_WLD_BaseValueEx, IDS_VCA_WLD_MM);
	SetDlgItemTextEx(IDC_STATIC_WLD_PRESETRANGE2, IDS_VCA_WLD_MM);
	SetDlgItemTextEx(IDC_STC_WLD_CURPRESETID1, IDS_VCA_WLD_RANGE);
	SetDlgItemTextEx(IDC_BUTTON_VCA_WLD_SHOW_REGION, IDS_VCA_WLD_SHOW_REGION);

	SetDlgItemInt(IDC_EDIT_VCA_WLD_POINT_VALUE, CONST_iPointValue);

	CString cstrColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), 
		GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_BLUE), 
		GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), 
		GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboAreaColor.ResetContent();
	for (int i = 0; i < sizeof(cstrColor)/sizeof(CString); i++)
	{
		m_cboAreaColor.InsertString(i, cstrColor[i]);
		m_cboAlarmColor.InsertString(i, cstrColor[i]);
	}
	m_cboAreaColor.SetCurSel(0);
	m_cboAlarmColor.SetCurSel(0);

	CString cstrGaugeType[] = {GetTextEx(IDS_ITS_RETAIN), GetTextEx(IDS_VCA_WLD_WIDE_RULERR)
		, GetTextEx(IDS_VCA_WLD_NARROW_RULE), GetTextEx(IDS_VCA_SPECILA_WATER_RULER)};
	m_cboGaugeType.ResetContent();
	for (int i = 0 ; i < sizeof(cstrGaugeType)/sizeof(CString); i++)
	{
		m_cboGaugeType.InsertString(i, cstrGaugeType[i]);
	}
	m_cboGaugeType.SetCurSel(3);

	CString cstrPresetNo;
	m_cboPresetNo.ResetContent();
	for (int i = 0; i < MAX_PRESET_NUM_EX; ++i)
	{
		cstrPresetNo.Format("%d", i + 1);
		m_cboPresetNo.InsertString(i, cstrPresetNo);
	}
	m_cboPresetNo.SetCurSel(0);
}

void CLS_VCAEVENT_WaterLevelDetection::UI_UpdateSdkParam()
{
	if (!CheckPublicPara())
	{
		return;
	}

	vca_TVCAParam* ptVcaPara = m_pVcaParam;
	memset(ptVcaPara, 0, sizeof(vca_TVCAParam));
	ptVcaPara->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, ptVcaPara, sizeof(vca_TVCAParam));
	if (0 == ptVcaPara->chnParam[ptVcaPara->iChannelID].iEnable)
	{
		AddLog(LOG_TYPE_MSG, "", "VcaParam: iChannelNO(%d), iEnable(%d)", m_iChannelNO, ptVcaPara->chnParam[ptVcaPara->iChannelID].iEnable);
	}

	memset(&m_tGetWld, 0, sizeof(m_tGetWld));
	m_tGetWld.iSize = sizeof(WaterSamplePoint);
	m_tGetWld.stRule.iRuleID = m_iRuleID;
	m_tGetWld.stRule.iSceneID = m_iSceneID;
	int iCmd = VCA_CMD_GET_RULE15_WATER_LEVEL;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, &m_tGetWld, sizeof(WaterSamplePoint));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_VCAGetConfig]VCA_CMD_SET_RULE15_WATER_LEVEL fail!");
		return;
	}

	m_chkDisplayRule.SetCheck(m_tGetWld.stDisplayParam.iDisplayRule);
	m_chkDisplayAlarmCount.SetCheck(m_tGetWld.stDisplayParam.iDisplayStat);
	m_cboAreaColor.SetCurSel(m_tGetWld.stDisplayParam.iColor - 1);
	m_cboAlarmColor.SetCurSel(m_tGetWld.stDisplayParam.iAlarmColor - 1);
	m_cboGaugeType.SetCurSel(m_tGetWld.iGaugeType);

	SetDlgItemInt(IDC_EDT_WLD_SnapIntervel, m_tGetWld.iSnapInterval);
	SetDlgItemInt(IDC_EDT_WLD_BaseValue, m_tGetWld.iBaseValue);
	SetDlgItemInt(IDC_EDT_WLD_CurPresetID, m_tGetWld.iCurrentPresetId);

	m_vecPresetScene.clear();
	for (int i = 0; i < m_tGetWld.iPresetCount; ++i)
	{
		m_vecPresetScene.push_back(m_tGetWld.stPresetInfo[i]);
	}
	UI_UpdatePresetSceneText();

	UI_UpdatePresetScene();
}

void CLS_VCAEVENT_WaterLevelDetection::UI_UpdatePresetScene()
{
	int iPresetIndex = m_cboPresetNo.GetCurSel();
	SetDlgItemInt(IDC_EDIT_WLD_PRESETRANGE_BEGIN, m_tGetWld.stPresetInfo[iPresetIndex].stGaugeRange.iStart);
	SetDlgItemInt(IDC_EDIT_WLD_PRESETRANGE_END, m_tGetWld.stPresetInfo[iPresetIndex].stGaugeRange.iEnd);

	CString cstrGaugeRect;
	cstrGaugeRect.Format("(%d,%d,%d,%d)"
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeRect.left
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeRect.top
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeRect.right
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeRect.bottom);
	SetDlgItemText(IDC_EDT_WLD_GaugeRect, cstrGaugeRect);

	CString cstrAssistRect;
	cstrAssistRect.Format("(%d,%d,%d,%d)"
		, m_tGetWld.stPresetInfo[iPresetIndex].rcAssistRect.left
		, m_tGetWld.stPresetInfo[iPresetIndex].rcAssistRect.top
		, m_tGetWld.stPresetInfo[iPresetIndex].rcAssistRect.right
		, m_tGetWld.stPresetInfo[iPresetIndex].rcAssistRect.bottom);
	SetDlgItemText(IDC_EDT_WLD_AssistRect, cstrAssistRect);

	CString cstrGaugeLine;
	cstrGaugeLine.Format("(%d,%d,%d,%d)"
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeLine.left
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeLine.top
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeLine.right
		, m_tGetWld.stPresetInfo[iPresetIndex].rcGaugeLine.bottom);
	SetDlgItemText(IDC_EDT_WLD_GaugeLine, cstrGaugeLine);

	int iReferNum = m_tGetWld.stPresetInfo[iPresetIndex].iReferNum;
	CString strPointArray;
	CString strPoint[MAX_REFERPOINT_NUM];
	for(int i = 0; i < iReferNum && i < MAX_REFERPOINT_NUM; ++i)
	{
		strPoint[i].Format("(%d,%d,%d)"
			, m_tGetWld.stPresetInfo[iPresetIndex].stReferPoint[i].iPointX
			, m_tGetWld.stPresetInfo[iPresetIndex].stReferPoint[i].iPointY
			, m_tGetWld.stPresetInfo[iPresetIndex].stReferPoint[i].iValue);
		strPointArray += strPoint[i];
	}
	SetDlgItemText(IDC_EDT_WLD_ReferPoint,strPointArray);
}

void CLS_VCAEVENT_WaterLevelDetection::OnLanguageChanged()
{
	UI_UpdateDialog();
}

void CLS_VCAEVENT_WaterLevelDetection::OnCbnSelchangeComboWldPresetNo()
{
	UI_UpdatePresetScene();
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawGaugeRect()
{
	int iPointCount = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	RECT tRect = {0};
	GetInfoOnDrawVideo(&iPointCount, cPointBuf, &tRect, DrawType_Crowd);
	CString cstrGaugeRect;
	cstrGaugeRect.Format("(%d,%d,%d,%d)", tRect.left, tRect.top, tRect.right, tRect.bottom);
	m_edtGaugeRect.SetWindowText(cstrGaugeRect);
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawAssistRect()
{
	int iPointCount = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	RECT tRect = {0};
	GetInfoOnDrawVideo(&iPointCount, cPointBuf, &tRect, DrawType_Crowd);
	CString cstrAssistRect;
	cstrAssistRect.Format("(%d,%d,%d,%d)", tRect.left, tRect.top, tRect.right, tRect.bottom);
	m_edtAssistRect.SetWindowText(cstrAssistRect);
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawGaugeLine()
{
	int iPointCount = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	GetInfoOnDrawVideo(&iPointCount, cPointBuf, NULL, DrawType_tripwire);
	POINT tPoints[2] = {0} ;
	GetPointsFromString(cPointBuf, 2, tPoints);
	CString cstrGaugeLine;
	cstrGaugeLine.Format("(%d,%d,%d,%d)", tPoints[0].x, tPoints[0].y, tPoints[1].x, tPoints[1].y);
	m_edtGaugeLine.SetWindowText(cstrGaugeLine);
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedBtnWldDrawReferPoints()
{
	int iPointCount = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	GetInfoOnDrawVideo(&iPointCount, cPointBuf, NULL, DrawType_perimeter);
	m_iReferCount = iPointCount;
	POINT tPoints[VCA_MAX_POLYGON_POINT_NUM] = {0}; 
	GetPointsFromString(cPointBuf, m_iReferCount, tPoints);
	CString cstrMsg;
	CString cstrTmp;
	for (int i = 0; i < m_iReferCount && i < MAX_REFERPOINT_NUM; ++i)
	{
		cstrTmp.Format("(%d,%d,0)", tPoints[i].x, tPoints[i].y);
		cstrMsg += cstrTmp;
	}
	m_edtReferPoints.SetWindowText(cstrMsg);
}

void CLS_VCAEVENT_WaterLevelDetection::GetInfoOnDrawVideo(int* _piPointCount, char* _pcPointsBuf, RECT* _ptRect, int _iDrawType)
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
	m_pDlgVideoView->SetDrawType(_iDrawType);
	int iDirection = 0;
	if (NULL != _piPointCount && NULL != _pcPointsBuf)
	{
		m_pDlgVideoView->SetPointRegionParam(_pcPointsBuf, _piPointCount, &iDirection);
	}

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		if (NULL != _ptRect)
		{
			m_pDlgVideoView->GetPointCoordirate((int*)&_ptRect->left, (int*)&_ptRect->top, (int*)&_ptRect->right, (int*)&_ptRect->bottom);
		}
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldAddPresetScene()
{
	bool blFind = false;
	int iIndex = -1;
	int iPresetId = m_cboPresetNo.GetCurSel() + 1;
	for (size_t i = 0; i < m_vecPresetScene.size(); ++i)
	{
		if (iPresetId == m_vecPresetScene[i].iPresetId)
		{
			blFind = true;
			iIndex = i;
			break;
		}
	}

	WaterPresetInfo tPresetScene = {0};
	tPresetScene.iSize = sizeof(WaterPresetInfo);
	tPresetScene.iPresetId = m_cboPresetNo.GetCurSel() + 1;
	tPresetScene.stGaugeRange.iStart = GetDlgItemInt(IDC_EDIT_WLD_PRESETRANGE_BEGIN);
	tPresetScene.stGaugeRange.iEnd = GetDlgItemInt(IDC_EDIT_WLD_PRESETRANGE_END);

	CString cstrGaugeRect;
	m_edtGaugeRect.GetWindowText(cstrGaugeRect);
	sscanf_s((LPSTR)(LPCTSTR)cstrGaugeRect, "(%d,%d,%d,%d)"
		, &tPresetScene.rcGaugeRect.left, &tPresetScene.rcGaugeRect.top
		, &tPresetScene.rcGaugeRect.right, &tPresetScene.rcGaugeRect.bottom);

	CString cstrAssistRect;
	m_edtAssistRect.GetWindowText(cstrAssistRect);
	sscanf_s((LPSTR)(LPCTSTR)cstrAssistRect, "(%d,%d,%d,%d)"
		, &tPresetScene.rcAssistRect.left, &tPresetScene.rcAssistRect.top
		, &tPresetScene.rcAssistRect.right, &tPresetScene.rcAssistRect.bottom);

	CString cstrGaugeLine;
	m_edtGaugeLine.GetWindowText(cstrGaugeLine);
	sscanf_s((LPSTR)(LPCTSTR)cstrGaugeLine, "(%d,%d,%d,%d)"
		, &tPresetScene.rcGaugeLine.left, &tPresetScene.rcGaugeLine.top
		, &tPresetScene.rcGaugeLine.right, &tPresetScene.rcGaugeLine.bottom);

	if(blFind)
	{
		tPresetScene.iReferNum = 0 == m_iReferCount ? m_vecPresetScene[iIndex].iReferNum : m_iReferCount;
	}
	else
	{
		tPresetScene.iReferNum = m_iReferCount;
	}
	
	WldPoint tWldPoints[VCA_MAX_POLYGON_POINT_NUM] = {0} ;
	CString cstrPointBuf;
	m_edtReferPoints.GetWindowText(cstrPointBuf);
	GetWldPointsFromString(cstrPointBuf.GetBuffer(), tPresetScene.iReferNum , tWldPoints);
	for (int i = 0; i < tPresetScene.iReferNum  && i < MAX_REFERPOINT_NUM; ++i)
	{
		tPresetScene.stReferPoint[i].iPointX = tWldPoints[i].iX;
		tPresetScene.stReferPoint[i].iPointY = tWldPoints[i].iY;
		tPresetScene.stReferPoint[i].iValue = tWldPoints[i].iValue;
	}

	if (blFind)
	{
		//更新参数
		memcpy(&m_vecPresetScene[iIndex], &tPresetScene, sizeof(WaterPresetInfo));
	}
	else
	{	//新加
		m_vecPresetScene.push_back(tPresetScene);
	}
	
	UI_UpdatePresetSceneText();
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldDeletePresetScene()
{
	int iPresetId = m_cboPresetNo.GetCurSel() + 1;
	for (size_t i = 0; i < m_vecPresetScene.size(); ++i)
	{
		if (iPresetId == m_vecPresetScene[i].iPresetId)
		{
			m_vecPresetScene.erase(m_vecPresetScene.begin() + i);
			break;
		}
	}
	UI_UpdatePresetSceneText();
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldClearPresetScene()
{
	m_vecPresetScene.clear();
	UI_UpdatePresetSceneText();
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonWldSet()
{
	if (!CheckPublicPara())
	{
		return;
	}

	int iSnapInterval = GetDlgItemInt(IDC_EDT_WLD_SnapIntervel);
	if (iSnapInterval < CONST_iMinIntervel || iSnapInterval > CONST_iMaxIntervel)
	{
		MessageBox(GetTextEx(IDS_VCAEVENT_WLD_USR_MSG), GetTextEx(IDS_CONFIG_PROMPT), MB_OK|MB_TOPMOST);
		return;
	}

	WaterSamplePoint tWaterSample = {0};
	tWaterSample.iSize = sizeof(WaterSamplePoint);
	tWaterSample.stRule.iRuleID = m_iRuleID;
	tWaterSample.stRule.iSceneID = m_iSceneID;
	tWaterSample.stRule.iValid = 1;
	tWaterSample.stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	tWaterSample.stDisplayParam.iDisplayStat = m_chkDisplayAlarmCount.GetCheck();
	tWaterSample.stDisplayParam.iColor = m_cboAreaColor.GetCurSel() + 1;
	tWaterSample.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel() + 1;
	tWaterSample.iSamplePointId = m_iSceneID;
	tWaterSample.iSnapInterval = iSnapInterval;
	tWaterSample.iBaseValue = GetDlgItemInt(IDC_EDT_WLD_BaseValue);
	tWaterSample.iCurrentPresetId = GetDlgItemInt(IDC_EDT_WLD_CurPresetID);
	tWaterSample.iGaugeType = m_cboGaugeType.GetCurSel();
	tWaterSample.iPresetCount = m_vecPresetScene.size();
	for (int i = 0; i < tWaterSample.iPresetCount && i < MAX_PRESET_NUM_EX; ++i)
	{
		memcpy(&tWaterSample.stPresetInfo[i], &m_vecPresetScene[i], sizeof(WaterPresetInfo));
	}
	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE15_WATER_LEVEL, m_iChannelNO, &tWaterSample, sizeof(WaterSamplePoint));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_VCASetConfig]VCA_CMD_SET_RULE15_WATER_LEVEL water detect Set error = %d", GetLastError());
		return;
	}

	AddLog(LOG_TYPE_SUCC, "", "[NetClient_VCASetConfig]VCA_CMD_SET_RULE15_WATER_LEVEL water detect set success!");

	//恢复智能分析
	int iState = 1;
	NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iState, sizeof(int));
}

void CLS_VCAEVENT_WaterLevelDetection::UI_UpdatePresetSceneText()
{
	int iPsCount = (int)m_vecPresetScene.size();
	if (iPsCount <= 0)
	{
		SetDlgItemText(IDC_STATIC_WLD_PRESET_SCENE_TOTAL_COUNT, "");
		return;
	}

	CString cstrTmp;
	CString cstrArr;
	CString cstrMsg;
	for (int i = 0; i < iPsCount - 1; ++i)
	{
		cstrTmp.Format("%d, ", m_vecPresetScene[i].iPresetId);
		cstrArr += cstrTmp;
	}
	cstrTmp.Format("%d", m_vecPresetScene[iPsCount - 1].iPresetId);
	cstrArr += cstrTmp;

	cstrTmp.Format("%d", iPsCount);
	cstrMsg = GetTextEx(IDS_CFG_VCA_WLD_ADDED) + cstrTmp + GetTextEx(IDS_CFG_VCA_WLD_PRESET_SCENE) + GetTextEx(IDS_CFG_VCA_WLD_ID_IS) + cstrArr;
	SetDlgItemText(IDC_STATIC_WLD_PRESET_SCENE_TOTAL_COUNT, cstrMsg);
}

void CLS_VCAEVENT_WaterLevelDetection::OnBnClickedButtonVcaWldShowRegion()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
	}

	int iPresetIndex = m_cboPresetNo.GetCurSel();
	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetVcaWldRegion(&m_tGetWld.stPresetInfo[iPresetIndex]);
	m_pDlgVideoView->DoModal();
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_WaterLevelDetection::OnMainNotify(int _ulLogonID, int _iWparam, void* _pvLParam, void* _pvUser)
{
	if (NULL != m_pDlgVideoView)
	{
		m_pDlgVideoView->OnMainNotify(_ulLogonID, _iWparam, _pvLParam, _pvUser);
	}
}
