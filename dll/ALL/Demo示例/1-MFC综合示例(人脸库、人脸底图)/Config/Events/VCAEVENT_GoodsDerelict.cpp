// VCAEVENT_GoodsDerelict.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_GoodsDerelict.h"

#define POINT_SUM					4			//点的个数
#define CHILD_AREA_SUM				3			//子区域个数
#define MAIN_AREA					0			//主区域编号
#define CHILD_AREA_1				1			//子区域1编号
#define CHILD_AREA_2				2			//子区域2编号
#define CHILD_AREA_3				3			//子区域3编号

#define MIN_TIME_DEFAULT			5000		//最短时间默认值
#define MIN_SIZE_DEFAULT			10			//最小像素尺寸默认值
#define MAX_SIZE_DEFAULT			10000		//最大像素尺寸默认值

// CLS_VCAEVENT_GoodsDerelict 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_GoodsDerelict, CDialog)

CLS_VCAEVENT_GoodsDerelict::CLS_VCAEVENT_GoodsDerelict(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_GoodsDerelict::IDD, pParent)
{

}

CLS_VCAEVENT_GoodsDerelict::~CLS_VCAEVENT_GoodsDerelict()
{
}

void CLS_VCAEVENT_GoodsDerelict::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_DERELICT_EVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CHK_DERELICT_SHOW_ALARM_RULE, m_chkAlarmRule);
	DDX_Control(pDX, IDC_CHK_DERELICT_SHOW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CHK_DERELICT_SHOW_TARGET_BOX, m_chkTargetBox);
	DDX_Control(pDX, IDC_EDT_DERELICT_MIN_TIME, m_edtMinTime);
	DDX_Control(pDX, IDC_EDT_DERELICT_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_DERELICT_MAX_SIZE, m_chkMaxSize);
	DDX_Control(pDX, IDC_CBO_DERELICT_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_DERELICT_UNALARM_COLOR, m_cboUnalarmColor);
	DDX_Control(pDX, IDC_CBO_DERELICT_CHILDAREA_NUM, m_cboChildAreaNum);
	DDX_Control(pDX, IDC_EDT_DERELICT_MAIN_AREA, m_edtMainArea);
	DDX_Control(pDX, IDC_EDT_DERELICT_CHILDAREA_1, m_edtChildArea1);
	DDX_Control(pDX, IDC_EDT_DERELICT_CHILDAREA_2, m_edtChildArea2);
	DDX_Control(pDX, IDC_EDT_DERELICT_CHILDAREA_3, m_edtChildArea3);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_GoodsDerelict, CDialog)
	ON_BN_CLICKED(IDC_BTN_DERELICT_SET, &CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictSet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_DERELICT_MAIN_AREA, &CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictMainArea)
	ON_BN_CLICKED(IDC_BTN_DERELICT_CHILDAREA_1, &CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictChildarea1)
	ON_BN_CLICKED(IDC_BTN_DERELICT_CHILDAREA_2, &CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictChildarea2)
	ON_BN_CLICKED(IDC_BTN_DERELICT_CHILDAREA_3, &CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictChildarea3)
END_MESSAGE_MAP()

BOOL CLS_VCAEVENT_GoodsDerelict::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	UpdateUIText();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_VCAEVENT_GoodsDerelict::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		OnInitDialog();
	}
}

void CLS_VCAEVENT_GoodsDerelict::OnLanguageChanged()
{
	UpdateUIText();
	OnInitDialog();
}

void CLS_VCAEVENT_GoodsDerelict::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_DERELICT_EVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_DERELICT_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_DERELICT_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_DERELICT_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_DERELICT_MIN_TIME, IDS_VCA_MINTIME);
	SetDlgItemTextEx(IDC_STC_DERELICT_MIN_SIZE, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STC_DERELICT_MAX_SIZE, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STC_DERELICT_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_DERELICT_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_DERELICT_CHILDAREA_NUM, IDS_VCAEVENT_CHILDAREA_NUM);
	SetDlgItemTextEx(IDC_STC_DERELICT_MAIN_AREA, IDS_VCA_ABMAINREGION);
	SetDlgItemTextEx(IDC_STC_DERELICT_CHILDAREA_1, IDS_VCA_ABSUBREGION1);
	SetDlgItemTextEx(IDC_STC_DERELICT_CHILDAREA_2, IDS_VCA_ABSUBREGION2);
	SetDlgItemTextEx(IDC_STC_DERELICT_CHILDAREA_3, IDS_VCA_ABSUBREGION3);
	SetDlgItemTextEx(IDC_BTN_DERELICT_MAIN_AREA, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_DERELICT_CHILDAREA_1, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_DERELICT_CHILDAREA_2, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_DERELICT_CHILDAREA_3, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_DERELICT_SET, IDS_SET);

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), 
		GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_BLUE), 
		GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), 
		GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboUnalarmColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAlarmColor.InsertString(i, strColor[i]);
		m_cboUnalarmColor.InsertString(i, strColor[i]);
	}
	m_cboAlarmColor.SetCurSel(0);
	m_cboUnalarmColor.SetCurSel(0);

	const CString cstNum[] = {"1","2","3"};
	m_cboChildAreaNum.ResetContent();
	for (int i=0; i<sizeof(cstNum)/sizeof(CString); i++)
	{
		m_cboChildAreaNum.InsertString(i, cstNum[i]);
	}
	m_cboChildAreaNum.SetCurSel(0);

	SetDlgItemInt(IDC_EDT_DERELICT_MIN_TIME, MIN_TIME_DEFAULT);
	SetDlgItemInt(IDC_EDT_DERELICT_MIN_SIZE, MIN_SIZE_DEFAULT);
	SetDlgItemInt(IDC_EDT_DERELICT_MAX_SIZE, MAX_SIZE_DEFAULT);
}

void CLS_VCAEVENT_GoodsDerelict::CleanText()
{
	m_edtMainArea.Clear();
	m_edtChildArea1.Clear();
	m_edtChildArea2.Clear();
	m_edtChildArea3.Clear();
}

void CLS_VCAEVENT_GoodsDerelict::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_GoodsDerelict::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCADerelict vd = {0};

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_DERELICT, m_iChannelNO, &vd, sizeof(VCALeaveDetect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_GoodsDerelict::NetClient_VCAGetConfig[VCA_CMD_DERELICT] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkEventValid.SetCheck(vd.stRule.iValid);
		SetDlgItemInt(IDC_EDT_GOODS_MIN_TIME, vd.iMinTime);
		SetDlgItemInt(IDC_EDT_GOODS_MIN_SIZE, vd.iMinSize);
		SetDlgItemInt(IDC_EDT_GOODS_MAX_SIZE, vd.iMaxSize);

		m_cboChildAreaNum.SetCurSel(vd.iSunRegionNum - 1);
		m_chkAlarmRule.SetCheck(vd.stDisplayParam.iDisplayRule);
		m_chkAlarmStat.SetCheck(vd.stDisplayParam.iDisplayStat);
		m_cboAlarmColor.SetCurSel(vd.stDisplayParam.iAlarmColor);
		m_cboUnalarmColor.SetCurSel(vd.stDisplayParam.iColor);
		m_chkTargetBox.SetCheck(vd.iDisplayTarget);

		CString cstPointBufMain = "";
		for (int i=0; i<vd.stMainRegion.iPointNum; i++)
		{
			cstPointBufMain.AppendFormat("(%d,%d)", vd.stMainRegion.stPoints[i].iX, vd.stMainRegion.stPoints[i].iY);
		}
		m_edtMainArea.SetWindowText(cstPointBufMain);

		CString cstPointBuf[CHILD_AREA_SUM];
		for(int i=0; i<CHILD_AREA_SUM; i++)
		{
			for(int j=0; j<vd.stSubRegion[i].iPointNum; j++)
			{
				cstPointBuf[i].AppendFormat("(%d,%d)", vd.stSubRegion[i].stPoints[j].iX, vd.stSubRegion[i].stPoints[j].iY);
			}
		}
		m_edtChildArea1.SetWindowText(cstPointBuf[0]);
		m_edtChildArea2.SetWindowText(cstPointBuf[1]);
		m_edtChildArea3.SetWindowText(cstPointBuf[2]);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_GoodsLose::NetClient_VCAGetConfig[VCA_CMD_STOLEN] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}
//设置
void CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_GoodsDerelict::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCADerelict vd = {0};

	vd.iBufSize = sizeof(vd);
	vd.iMinTime = GetDlgItemInt(IDC_EDT_GOODS_MIN_TIME);
	vd.iMinSize = GetDlgItemInt(IDC_EDT_GOODS_MIN_SIZE);
	vd.iMaxSize = GetDlgItemInt(IDC_EDT_GOODS_MAX_SIZE);
	vd.iDisplayTarget = m_chkTargetBox.GetCheck();
	vd.iSunRegionNum = m_cboChildAreaNum.GetCurSel() + 1;

	vd.stRule.iRuleID = m_iRuleID;
	vd.stRule.iSceneID = m_iSceneID;
	vd.stRule.iValid = m_chkEventValid.GetCheck();

	vd.stDisplayParam.iDisplayRule = m_chkAlarmRule.GetCheck();
	vd.stDisplayParam.iDisplayStat = m_chkAlarmStat.GetCheck();
	vd.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel();
	vd.stDisplayParam.iColor = m_cboUnalarmColor.GetCurSel();

	CString strPointMain;
	CString strPointChildArea1;
	CString strPointChildArea2;
	CString strPointChildArea3;
	GetDlgItemText(IDC_EDT_GOODS_MAIN_AREA, strPointMain);
	GetPolyFromString(strPointMain, POINT_SUM, vd.stMainRegion);
	GetDlgItemText(IDC_EDT_GOODS_CHILDAREA_1, strPointChildArea1);
	GetPolyFromString(strPointChildArea1, POINT_SUM, vd.stSubRegion[1]);
	GetDlgItemText(IDC_EDT_GOODS_CHILDAREA_2, strPointChildArea2);	
	GetPolyFromString(strPointChildArea2, POINT_SUM, vd.stSubRegion[2]);
	GetDlgItemText(IDC_EDT_GOODS_CHILDAREA_3, strPointChildArea3);
	GetPolyFromString(strPointChildArea3, POINT_SUM, vd.stSubRegion[3]);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_DERELICT, m_iChannelNO, &vd, sizeof(VCALeaveDetect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_GoodsDerelict::NetClient_VCASetConfig[VCA_CMD_DERELICT] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_GoodsDerelict::NetClient_VCASetConfig[VCA_CMD_DERELICT] (%d, %d)", m_iLogonID, m_iChannelNO);
	}

}

int CLS_VCAEVENT_GoodsDerelict::ToDrawArea(int _iAreaNum)
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return -1;
		}
	}

	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		delete m_pDlgVideoView;
		m_pDlgVideoView = NULL;
		return -1;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		switch (_iAreaNum)
		{
		case MAIN_AREA:
			m_edtMainArea.SetWindowText(cPointBuf);
			break;
		case CHILD_AREA_1:
			m_edtChildArea1.SetWindowText(cPointBuf);
			break;
		case CHILD_AREA_2:
			m_edtChildArea2.SetWindowText(cPointBuf);
			break;
		case CHILD_AREA_3:
			m_edtChildArea3.SetWindowText(cPointBuf);
			break;
		default:
			break;
		}
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;

	return 0;
}

void CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictMainArea()
{
	ToDrawArea(MAIN_AREA);
}

void CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictChildarea1()
{
	ToDrawArea(CHILD_AREA_1);
}

void CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictChildarea2()
{
	ToDrawArea(CHILD_AREA_2);
}

void CLS_VCAEVENT_GoodsDerelict::OnBnClickedBtnDerelictChildarea3()
{
	ToDrawArea(CHILD_AREA_3);
}
