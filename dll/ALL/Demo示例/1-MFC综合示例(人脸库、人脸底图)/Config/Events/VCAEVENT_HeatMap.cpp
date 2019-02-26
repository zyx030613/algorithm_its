// VCAEVENT_Running.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_HeatMap.h"

#define LEN_2					2
#define LEN_3					3
#define LEN_10					10
#define DEFAULT_LIMIT_LEN_5		5
#define DEFAULT_ZORO			0
#define DEFAULT_RANGE			100
#define DEFAULT_MIN_SIZE		5
#define DEFAULT_MAX_SIZE		30
#define MAX_HEATMAP_SIZE		100
// CLS_VCAEVENT_HeatMap 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_HeatMap, CDialog)

CLS_VCAEVENT_HeatMap::CLS_VCAEVENT_HeatMap(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_HeatMap::IDD, pParent)
{
	m_iAreaPointNum = 0;
}

CLS_VCAEVENT_HeatMap::~CLS_VCAEVENT_HeatMap()
{
}

void CLS_VCAEVENT_HeatMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_HEATMAP_MIN_DISTANCE, m_edtMinDistance);
	DDX_Control(pDX, IDC_EDT_HEATMAP_MIN_TIME, m_edtMinTime);
	DDX_Control(pDX, IDC_EDT_HEATMAP_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_HEATMAP_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_CHK_HEATMAP_CHK_VALID, m_chkCheckValid);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_HeatMap, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_HEATMAP_SET, &CLS_VCAEVENT_HeatMap::OnBnClickedBtnHeatMapSet)
	ON_BN_CLICKED(IDC_BTN_HEATMAP_DRAW, &CLS_VCAEVENT_HeatMap::OnBnClickedBtnHeatMapDraw)
	ON_EN_CHANGE(IDC_EDT_HEATMAP_MIN_SIZE, &CLS_VCAEVENT_HeatMap::OnEnChangeEdtHeatMapMinSize)
	ON_EN_CHANGE(IDC_EDT_HEATMAP_MAX_SIZE, &CLS_VCAEVENT_HeatMap::OnEnChangeEdtHeatMapMaxSize)
END_MESSAGE_MAP()


BOOL CLS_VCAEVENT_HeatMap::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	m_edtMaxSize.SetLimitText(LEN_3);
	SetDlgItemInt(IDC_EDT_HEATMAP_MIN_SIZE, DEFAULT_MAX_SIZE);
	m_edtMinSize.SetLimitText(LEN_2);
	SetDlgItemInt(IDC_EDT_HEATMAP_MAX_SIZE, DEFAULT_MIN_SIZE);

	m_edtMinDistance.SetLimitText(DEFAULT_LIMIT_LEN_5);
	m_edtMinTime.SetLimitText(DEFAULT_LIMIT_LEN_5);

	m_chkCheckValid.SetCheck(BST_UNCHECKED);

	UI_UpdateDialogText();
	UI_UpdateParam();

	return TRUE; 
}

void CLS_VCAEVENT_HeatMap::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UI_UpdateDialogText();
		UI_UpdateParam();
	}
}

void CLS_VCAEVENT_HeatMap::OnLanguageChanged()
{
	UI_UpdateDialogText();
	UI_UpdateParam();
}

void CLS_VCAEVENT_HeatMap::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_CHK_HEATMAP_CHK_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_STC_HEATMAP_MIN_SIZE, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STC_HEATMAP_MAX_SIZE, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STC_HEATMAP_AREA, IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_BTN_HEATMAP_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_STC_HEATMAP_MIN_DISTANCE, IDS_VCA_MINDISTANCE);
	SetDlgItemTextEx(IDC_STC_HEATMAP_MIN_TIME, IDS_VCA_MINTIME);
	SetDlgItemTextEx(IDC_BTN_HEATMAP_SET, IDS_SET);
}

void CLS_VCAEVENT_HeatMap::UI_UpdateParam()
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

	VCAHeatMap tVCAHeatMap = {0};
	tVCAHeatMap.iSize = sizeof(VCAHeatMap);
	tVCAHeatMap.tRule.iRuleID = m_iRuleID;
	tVCAHeatMap.tRule.iSceneID = m_iSceneID;

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_HEATMAP, m_iChannelNO, &tVCAHeatMap, sizeof(tVCAHeatMap));
	if (iRet >= RET_SUCCESS)
	{
		m_chkCheckValid.SetCheck(tVCAHeatMap.tRule.iValid);
		SetDlgItemInt(IDC_EDT_HEATMAP_MIN_DISTANCE, tVCAHeatMap.iMinDistance);
		SetDlgItemInt(IDC_EDT_HEATMAP_MIN_TIME, tVCAHeatMap.iMinTime);
		SetDlgItemInt(IDC_EDT_HEATMAP_MIN_SIZE, tVCAHeatMap.iMiniSize);
		SetDlgItemInt(IDC_EDT_HEATMAP_MAX_SIZE, tVCAHeatMap.iMaxSize);

		int iPointNum = tVCAHeatMap.tPoints.iPointNum;
		CString cstPoint;
		for(int i = 0; i < iPointNum; i++)
		{
			cstPoint.AppendFormat("(%d,%d)", tVCAHeatMap.tPoints.stPoints[i].iX, tVCAHeatMap.tPoints.stPoints[i].iY);
		}
		SetDlgItemText(IDC_EDT_HEATMAP_AREA, cstPoint);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_HeatMap::NetClient_VCAGetConfig[VCA_CMD_HEATMAP] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_HeatMap::NetClient_VCAGetConfig[VCA_CMD_HEATMAP] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
}

void CLS_VCAEVENT_HeatMap::OnBnClickedBtnHeatMapSet()
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

	VCAHeatMap tVCAHeatMap = {0};
	tVCAHeatMap.iSize = sizeof(VCAHeatMap);
	tVCAHeatMap.tRule.iRuleID = m_iRuleID;
	tVCAHeatMap.tRule.iSceneID = m_iSceneID;
	tVCAHeatMap.tRule.iValid = m_chkCheckValid.GetCheck();
	tVCAHeatMap.iMinDistance = GetDlgItemInt(IDC_EDT_HEATMAP_MIN_DISTANCE);
	tVCAHeatMap.iMinTime = GetDlgItemInt(IDC_EDT_HEATMAP_MIN_TIME);
	tVCAHeatMap.iMiniSize = GetDlgItemInt(IDC_EDT_HEATMAP_MIN_SIZE);
	tVCAHeatMap.iMaxSize = GetDlgItemInt(IDC_EDT_HEATMAP_MAX_SIZE);

	tVCAHeatMap.tPoints.iPointNum = m_iAreaPointNum;

	CString cstPoint;
	vca_TPolygon stRegion = {0};

	if (0 >= m_iAreaPointNum)
	{
		AddLog(LOG_TYPE_FAIL,"","HeatMapSet Illeage Point Num(%d)", m_iAreaPointNum);
		goto EXIT_FUNC;
	}

	GetDlgItemText(IDC_EDT_HEATMAP_AREA, cstPoint);
	GetPolyFromString(cstPoint, tVCAHeatMap.tPoints.iPointNum, stRegion);
	memcpy(&tVCAHeatMap.tPoints, &stRegion, sizeof(stRegion));

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_HEATMAP, m_iChannelNO, &tVCAHeatMap, sizeof(VCAHeatMap));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_HeatMap::NetClient_VCASetConfig[VCA_CMD_HEATMAP] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_HeatMap::NetClient_VCASetConfig[VCA_CMD_HEATMAP] (%d, %d)", m_iLogonID, m_iChannelNO);
	}	

EXIT_FUNC:
	return;
}

void CLS_VCAEVENT_HeatMap::OnBnClickedBtnHeatMapDraw()
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
		SetDlgItemText(IDC_EDT_HEATMAP_AREA, cPointBuf);
		m_iAreaPointNum = iPointNum;
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_HeatMap::OnEnChangeEdtHeatMapMinSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MIN_SIZE);
	if (iTemp < DEFAULT_ZORO || iTemp > MAX_HEATMAP_SIZE)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_HeatMap::Put Invalid Value(%d)", iTemp);
		SetDlgItemInt(IDC_EDT_HEATMAP_MIN_SIZE, iTemp / LEN_10);
	}
	return;
}

void CLS_VCAEVENT_HeatMap::OnEnChangeEdtHeatMapMaxSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_RUN_MIN_SIZE);
	if (iTemp < DEFAULT_ZORO || iTemp > MAX_HEATMAP_SIZE)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_HeatMap::Put Invalid Value(%d)", iTemp);
		SetDlgItemInt(IDC_EDT_HEATMAP_MAX_SIZE, iTemp / LEN_10);
	}
	return;
}
