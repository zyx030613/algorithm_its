

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_GoodsLose.h"

#define POINT_SUM				4
#define CHILD_AREA_SUM			3
#define MAIN_AREA				0
#define CHILD_AREA_1			1
#define CHILD_AREA_2			2
#define CHILD_AREA_3			3
#define MIN_TIME_FROM			0
#define MIN_TIME_TO				30
#define MIN_SIZE_FROM			0
#define MIN_SIZE_TO				100
#define MAX_SIZE_FROM			100
#define MAX_SIZE_TO				40000

// CLS_VCAEVENT_GoodsLose ¶Ô»°¿ò

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_GoodsLose, CDialog)

CLS_VCAEVENT_GoodsLose::CLS_VCAEVENT_GoodsLose(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_GoodsLose::IDD, pParent)
{

}

CLS_VCAEVENT_GoodsLose::~CLS_VCAEVENT_GoodsLose()
{
}

void CLS_VCAEVENT_GoodsLose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_GOODS_EVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CHK_GOODS_SHOW_ALARM_RULE, m_chkAlarmRule);
	DDX_Control(pDX, IDC_CHK_GOODS_SHOW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CHK_GOODS_SHOW_TARGET_BOX, m_chkTargetBox);
	DDX_Control(pDX, IDC_EDT_GOODS_MIN_TIME, m_edtMinTime);
	DDX_Control(pDX, IDC_EDT_GOODS_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_GOODS_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_CBO_GOODS_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_GOODS_UNALARM_COLOR, m_cboUnalarmColor);
	DDX_Control(pDX, IDC_CBO_GOODS_CHILDAREA_NUM, m_cboChildareaNum);
	DDX_Control(pDX, IDC_EDT_GOODS_MAIN_AREA, m_edtMainArea);
	DDX_Control(pDX, IDC_EDT_GOODS_CHILDAREA_1, m_edtChildArea1);
	DDX_Control(pDX, IDC_EDT_GOODS_CHILDAREA_2, m_edtChildArea2);
	DDX_Control(pDX, IDC_EDT_GOODS_CHILDAREA_3, m_edtChildArea3);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_GoodsLose, CDialog)
	ON_BN_CLICKED(IDC_BTN_GOODS_SET, &CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsSet)
	ON_EN_CHANGE(IDC_EDT_GOODS_MIN_TIME, &CLS_VCAEVENT_GoodsLose::OnEnChangeEdtGoodsMinTime)
	ON_EN_CHANGE(IDC_EDT_GOODS_MIN_SIZE, &CLS_VCAEVENT_GoodsLose::OnEnChangeEdtGoodsMinSize)
	ON_EN_CHANGE(IDC_EDT_GOODS_MAX_SIZE, &CLS_VCAEVENT_GoodsLose::OnEnChangeEdtGoodsMaxSize)
	ON_BN_CLICKED(IDC_BTN_GOODS_MAIN_AREA, &CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsMainArea)
	ON_BN_CLICKED(IDC_BTN_GOODS_CHILDAREA_1, &CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsChildarea1)
	ON_BN_CLICKED(IDC_BTN_GOODS_CHILDAREA_2, &CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsChildarea2)
	ON_BN_CLICKED(IDC_BTN_GOODS_CHILDAREA_3, &CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsChildarea3)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_CBO_GOODS_CHILDAREA_NUM, &CLS_VCAEVENT_GoodsLose::OnCbnSelchangeCboGoodsChildareaNum)
END_MESSAGE_MAP()

BOOL CLS_VCAEVENT_GoodsLose::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_GoodsLose::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_GoodsLose::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_GoodsLose::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_GOODS_EVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_GOODS_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_GOODS_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_GOODS_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_GOODS_MIN_TIME, IDS_VCA_MINTIME_SECONDS);
	SetDlgItemTextEx(IDC_STC_GOODS_MIN_SIZE, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STC_GOODS_MAX_SIZE, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STC_GOODS_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_GOODS_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_GOODS_CHILDAREA_NUM, IDS_VCAEVENT_CHILDAREA_NUM);
	SetDlgItemTextEx(IDC_STC_GOODS_MAIN_AREA, IDS_VCA_ABMAINREGION);
	SetDlgItemTextEx(IDC_STC_GOODS_CHILDAREA_1, IDS_VCA_ABSUBREGION1);
	SetDlgItemTextEx(IDC_STC_GOODS_CHILDAREA_2, IDS_VCA_ABSUBREGION2);
	SetDlgItemTextEx(IDC_STC_GOODS_CHILDAREA_3, IDS_VCA_ABSUBREGION3);
	SetDlgItemTextEx(IDC_BTN_GOODS_MAIN_AREA, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_GOODS_CHILDAREA_1, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_GOODS_CHILDAREA_2, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_GOODS_CHILDAREA_3, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_GOODS_SET, IDS_SET);

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
	m_cboChildareaNum.ResetContent();
	for (int i=0; i<sizeof(cstNum)/sizeof(CString); i++)
	{
		m_cboChildareaNum.InsertString(i, cstNum[i]);
	}
	m_cboChildareaNum.SetCurSel(0);

	m_edtMinTime.SetLimitText(2);
	SetDlgItemInt(IDC_EDT_GOODS_MIN_TIME, 5);
	m_edtMinSize.SetLimitText(3);
	SetDlgItemInt(IDC_EDT_GOODS_MIN_SIZE, 10);
	m_edtMaxSize.SetLimitText(5);
	SetDlgItemInt(IDC_EDT_GOODS_MAX_SIZE, 10000);
}

void CLS_VCAEVENT_GoodsLose::CleanText()
{
	m_edtMainArea.Clear();
	m_edtChildArea1.Clear();
	m_edtChildArea2.Clear();
	m_edtChildArea3.Clear();
}

void CLS_VCAEVENT_GoodsLose::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCADerelict vd = {0};

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_STOLEN, m_iChannelNO, &vd, sizeof(VCALeaveDetect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_GoodsLose::NetClient_VCAGetConfig[VCA_CMD_STOLEN] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkEventValid.SetCheck(vd.stRule.iValid);
		SetDlgItemInt(IDC_EDT_GOODS_MIN_TIME, vd.iMinTime/1000);
		SetDlgItemInt(IDC_EDT_GOODS_MIN_SIZE, vd.iMinSize);
		SetDlgItemInt(IDC_EDT_GOODS_MAX_SIZE, vd.iMaxSize);

		m_cboChildareaNum.SetCurSel(vd.iSunRegionNum-1);
		OnCbnSelchangeCboGoodsChildareaNum();
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
//ÉèÖÃ
void CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCADerelict vd = {0};

	vd.iBufSize = sizeof(vd);
	vd.iMinTime = GetDlgItemInt(IDC_EDT_GOODS_MIN_TIME) * 1000;
	vd.iMinSize = GetDlgItemInt(IDC_EDT_GOODS_MIN_SIZE);
	vd.iMaxSize = GetDlgItemInt(IDC_EDT_GOODS_MAX_SIZE);
	if (vd.iMaxSize < MAX_SIZE_FROM)
	{
		vd.iMaxSize = MAX_SIZE_FROM;
		AddLog(LOG_TYPE_MSG, "", "Invalid Max Size Value£¡(%d,%d)", m_iLogonID,m_iChannelNO);
	}
	vd.iDisplayTarget = m_chkTargetBox.GetCheck();
	vd.iSunRegionNum = m_cboChildareaNum.GetCurSel()+1;

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
	GetPolyFromString(strPointChildArea1, POINT_SUM, vd.stSubRegion[0]);
	GetDlgItemText(IDC_EDT_GOODS_CHILDAREA_2, strPointChildArea2);	
	GetPolyFromString(strPointChildArea2, POINT_SUM, vd.stSubRegion[1]);
	GetDlgItemText(IDC_EDT_GOODS_CHILDAREA_3, strPointChildArea3);
	GetPolyFromString(strPointChildArea3, POINT_SUM, vd.stSubRegion[2]);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_STOLEN, m_iChannelNO, &vd, sizeof(VCALeaveDetect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_GoodsLose::NetClient_VCASetConfig[VCA_CMD_STOLEN] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_GoodsLose::NetClient_VCASetConfig[VCA_CMD_STOLEN] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_GoodsLose::OnEnChangeEdtGoodsMinTime()
{
	int iTemp = GetDlgItemInt(IDC_EDT_GOODS_MIN_TIME);
	if (iTemp < MIN_TIME_FROM || iTemp > MIN_TIME_TO)
	{
		SetDlgItemInt(IDC_EDT_GOODS_MIN_TIME, MIN_TIME_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_GoodsLose::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}	
}

void CLS_VCAEVENT_GoodsLose::OnEnChangeEdtGoodsMinSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_GOODS_MIN_SIZE);
	if (iTemp < MIN_SIZE_FROM || iTemp > MIN_SIZE_TO)
	{
		SetDlgItemInt(IDC_EDT_GOODS_MIN_SIZE, MIN_SIZE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_GoodsLose::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_GoodsLose::OnEnChangeEdtGoodsMaxSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_GOODS_MAX_SIZE);
	if (iTemp > MAX_SIZE_TO)
	{
		SetDlgItemInt(IDC_EDT_GOODS_MAX_SIZE, MAX_SIZE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_GoodsLose::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

int CLS_VCAEVENT_GoodsLose::DrawArea(int _iAreaNum)
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

void CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsMainArea()
{
	DrawArea(0);
}

void CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsChildarea1()
{
	DrawArea(1);
}

void CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsChildarea2()
{
	DrawArea(2);
}

void CLS_VCAEVENT_GoodsLose::OnBnClickedBtnGoodsChildarea3()
{
	DrawArea(3);
}

void CLS_VCAEVENT_GoodsLose::OnCbnSelchangeCboGoodsChildareaNum()
{
	int iChoose = m_cboChildareaNum.GetCurSel();
	if (0 == iChoose)
	{
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_2)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDT_GOODS_CHILDAREA_2, _T(""));
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_3)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDT_GOODS_CHILDAREA_3, _T(""));
	}
	else if (1 == iChoose)
	{
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_3)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDT_GOODS_CHILDAREA_3, _T(""));
	}
	else if (2 == iChoose)
	{
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_3)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_1)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDT_GOODS_CHILDAREA_1, _T(""));
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_2)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDT_GOODS_CHILDAREA_2, _T(""));
		GetDlgItem(IDC_BTN_GOODS_CHILDAREA_3)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDT_GOODS_CHILDAREA_3, _T(""));
	}
}
