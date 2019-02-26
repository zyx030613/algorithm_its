// VCAEVENT_OnDutyDetect.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_OnDutyDetect.h"

#define DEFAULT_ZERO		0
#define LEN_1				1
#define LEN_2				2
#define LEN_3				3
#define LEN_4				4
#define MAIN_AREA_1			1
#define MAIN_AREA_2			2
#define MAIN_AREA_3			3
#define MAIN_AREA_4			4
#define POINT_SUM			4
#define POINT_SUM_TO_SEND	2
#define AREA_SUM			4
#define MIN_SIZE_FROM		0
#define MIN_SIZE_TO			100
#define MAX_SIZE_FROM		0
#define	MAX_SIZE_TO			100
#define SENS_FROM			0
#define SENS_TO				5


// CLS_VCAEVENT_OnDutyDetect 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_OnDutyDetect, CDialog)

CLS_VCAEVENT_OnDutyDetect::CLS_VCAEVENT_OnDutyDetect(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_OnDutyDetect::IDD, pParent)
{

}

CLS_VCAEVENT_OnDutyDetect::~CLS_VCAEVENT_OnDutyDetect()
{
}

void CLS_VCAEVENT_OnDutyDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_ONDUTY_EVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CHK_ONDUTY_ALARM_RULES, m_chkAlarmRule);
	DDX_Control(pDX, IDC_CHK_ONDUTY_ALARM_STATISTICS, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CHK_TARGET_BOX, m_chkTargetBox);
	DDX_Control(pDX, IDC_CBO_ONDUTY_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_ONDUTY_UNALARM_COLOR, m_cboUnalarmColor);
	DDX_Control(pDX, IDC_EDT_ONDUTY_MAIN_AREA_1, m_edtMainArea1);
	DDX_Control(pDX, IDC_EDT_ONDUTY_MAIN_AREA_2, m_edtMainArea2);
	DDX_Control(pDX, IDC_EDT_ONDUTY_MAIN_AREA_3, m_edtMainArea3);
	DDX_Control(pDX, IDC_EDT_ONDUTY_MAIN_AREA_4, m_edtMainArea4);
	DDX_Control(pDX, IDC_EDT_ONDUTY_LEAVE_ALARM_TIME, m_edtLeaveAlarmTime);
	DDX_Control(pDX, IDC_EDT_ONDUTY_RETURN_ALARM_TIME, m_edtReturnUnalarmTime);
	DDX_Control(pDX, IDC_EDT_ONDUTY_AREA_NUM, m_edtAreaNum);
	DDX_Control(pDX, IDC_EDT_ONDUTY_SENSITIVITY, m_edtSensitivity);
	DDX_Control(pDX, IDC_EDT_ONDUTY_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_EDT_ONDUTY_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_ONDUTY_NUM, m_edtOndutyNum);
	DDX_Control(pDX, IDC_SPIN_ONDUTY_LEAVE_ALARM_TIME, m_spinLeaveAlarmTime);
	DDX_Control(pDX, IDC_SPIN_ONDUTY_RETURN_ALARM_TIME, m_spinReturnUnalarmTime);
	DDX_Control(pDX, IDC_SPIN_ONDUTY_AREA_NUM, m_spinAreaNum);
}

BEGIN_MESSAGE_MAP(CLS_VCAEVENT_OnDutyDetect, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_ONDUTY_SET, &CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutySet)
	ON_BN_CLICKED(IDC_BTN_ONDUTY_DRAW_AREA_1, &CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea1)
	ON_BN_CLICKED(IDC_BTN_ONDUTY_DRAW_AREA_2, &CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea2)
	ON_BN_CLICKED(IDC_BTN_ONDUTY_DRAW_AREA_3, &CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea3)
	ON_BN_CLICKED(IDC_BTN_ONDUTY_DRAW_AREA_4, &CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea4)
	ON_EN_CHANGE(IDC_EDT_ONDUTY_NUM, &CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyNum)
	ON_EN_CHANGE(IDC_EDT_ONDUTY_MIN_SIZE, &CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyMinSize)
	ON_EN_CHANGE(IDC_EDT_ONDUTY_MAX_SIZE, &CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyMaxSize)
	ON_EN_CHANGE(IDC_EDT_ONDUTY_AREA_NUM, &CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyAreaNum)
	ON_EN_CHANGE(IDC_EDT_ONDUTY_SENSITIVITY, &CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutySensitivity)
END_MESSAGE_MAP()


// CLS_VCAEVENT_OnDutyDetect 消息处理程序

BOOL CLS_VCAEVENT_OnDutyDetect::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_spinLeaveAlarmTime.SetRange(0, 9999);                 
	m_spinLeaveAlarmTime.SetBuddy(this->GetDlgItem(IDC_EDT_ONDUTY_LEAVE_ALARM_TIME)); 
	m_edtLeaveAlarmTime.SetWindowText("120");
	m_spinReturnUnalarmTime.SetRange(0, 9999);
	m_spinReturnUnalarmTime.SetBuddy(this->GetDlgItem(IDC_EDT_ONDUTY_RETURN_ALARM_TIME));
	m_edtReturnUnalarmTime.SetWindowText("15");
	m_spinAreaNum.SetRange(1,4);
	m_spinAreaNum.SetBuddy(this->GetDlgItem(IDC_EDT_ONDUTY_AREA_NUM));
	m_edtAreaNum.SetWindowText("1");

	m_edtOndutyNum.SetLimitText(LEN_1);
	m_edtMaxSize.SetLimitText(LEN_3);
	m_edtMinSize.SetLimitText(LEN_2);
	m_edtSensitivity.SetLimitText(LEN_1);
	m_edtMainArea1.SetLimitText(LEN_128);
	m_edtMainArea2.SetLimitText(LEN_128);
	m_edtMainArea3.SetLimitText(LEN_128);
	m_edtMainArea4.SetLimitText(LEN_128);
	m_edtLeaveAlarmTime.SetLimitText(LEN_4);
	m_edtReturnUnalarmTime.SetLimitText(LEN_4);

	m_cboAlarmColor.SetCurSel(0);
	m_cboUnalarmColor.SetCurSel(0);

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_OnDutyDetect::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_OnDutyDetect::OnLanguageChanged()
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_OnDutyDetect::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_ONDUTY_EVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_ONDUTY_ALARM_RULES, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_ONDUTY_ALARM_STATISTICS, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_ONDUTY_NUM, IDS_VCAEVENT_ONDUTY_NUM);
	SetDlgItemTextEx(IDC_STC_ONDUTY_LEAVE_ALARM_TIME, IDS_VCA_EVENT_LEAVEDETECT_LEAVEALARMTIME);
	SetDlgItemTextEx(IDC_STC_ONDUTY_RETURN_ALARM_TIME, IDS_VCAEVENT_ONDUTY_RETURN_UNALARM_TIME);
	SetDlgItemTextEx(IDC_STC_ONDUTY_MAX_SIZE, IDS_VCA_MAXSIZE);
	SetDlgItemTextEx(IDC_STC_ONDUTY_MIN_SIZE, IDS_VCA_MINSIZE);
	SetDlgItemTextEx(IDC_STC_ONDUTY_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_ONDUTY_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_ONDUTY_SENSITIVITY, IDS_VCA_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_ONDUTY_AREA_NUM, IDS_ITS_AREA_SUM);
	SetDlgItemTextEx(IDC_STC_ONDUTY_MAIN_AREA_1, IDS_VCAEVENT_ONDUTY_MAIN_AREA_1);
	SetDlgItemTextEx(IDC_STC_ONDUTY_MAIN_AREA_2, IDS_VCAEVENT_ONDUTY_MAIN_AREA_2);
	SetDlgItemTextEx(IDC_STC_ONDUTY_MAIN_AREA_3, IDS_VCAEVENT_ONDUTY_MAIN_AREA_3);
	SetDlgItemTextEx(IDC_STC_ONDUTY_MAIN_AREA_4, IDS_VCAEVENT_ONDUTY_MAIN_AREA_4);
	SetDlgItemTextEx(IDC_BTN_ONDUTY_DRAW_AREA_1, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_ONDUTY_DRAW_AREA_2, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_ONDUTY_DRAW_AREA_3, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_ONDUTY_DRAW_AREA_4, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_ONDUTY_SET, IDS_SET);

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
}

void CLS_VCAEVENT_OnDutyDetect::CleanText()
{
	m_edtMainArea1.Clear();
	m_edtMainArea2.Clear();
	m_edtMainArea3.Clear();
	m_edtMainArea4.Clear();

	m_cboAlarmColor.SetCurSel(-1);
	m_cboUnalarmColor.SetCurSel(-1);
}

void CLS_VCAEVENT_OnDutyDetect::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCALeaveDetect vld = {0};

	vld.stRule.iRuleID = m_iRuleID;
	vld.stRule.iSceneID = m_iSceneID;

 	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_RULE14_LEAVE_DETECT, m_iChannelNO, &vld, sizeof(VCALeaveDetect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_VCAGetConfig[VCA_CMD_RULE14_LEAVE_DETECT] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		// TODO: Nothing
		VCARule vRule = vld.stRule;
		int iEventValid = vRule.iValid;
		if (1 == iEventValid)//事件有效
		{
			m_chkEventValid.SetCheck(1);
		}
		else
		{
			m_chkEventValid.SetCheck(0);
		}

		vca_TDisplayParam vDisplayPara = vld.stDisplayParam;
		int iAlarmRule = vDisplayPara.iDisplayRule;
		if (1 == iAlarmRule)//报警规则有效
		{
			m_chkAlarmRule.SetCheck(1);
		}
		else
		{
			m_chkEventValid.SetCheck(0);
		}
		int iAlarmStat = vDisplayPara.iDisplayStat;
		if (1 == iAlarmStat)//报警统计有效
		{
			m_chkAlarmStat.SetCheck(1);
		}
		else
		{
			m_chkAlarmStat.SetCheck(0);
		}

		int iTarget = vld.iDisplayTarget;
		if (1 == iTarget)//目标框有效
		{
			m_chkTargetBox.SetCheck(1);
		}
		else
		{
			m_chkTargetBox.SetCheck(0);
		}

		SetDlgItemInt(IDC_EDT_ONDUTY_NUM, vld.iDutyNum);
		SetDlgItemInt(IDC_EDT_ONDUTY_LEAVE_ALARM_TIME, vld.iLeaveAlarmTime);
		SetDlgItemInt(IDC_EDT_ONDUTY_RETURN_ALARM_TIME, vld.iRuturnClearAlarmTime);
		SetDlgItemInt(IDC_EDT_ONDUTY_MIN_SIZE, vld.iMinSize);
		SetDlgItemInt(IDC_EDT_ONDUTY_MAX_SIZE, vld.iMaxSize);

		m_cboAlarmColor.SetCurSel(vDisplayPara.iAlarmColor - 1);
		m_cboUnalarmColor.SetCurSel(vDisplayPara.iColor - 1);

		SetDlgItemInt(IDC_EDT_ONDUTY_SENSITIVITY, vld.iSensitivity);
		SetDlgItemInt(IDC_EDT_ONDUTY_AREA_NUM, vld.iAreaNum);
		OnEnChangeEdtOndutyAreaNum();

		CString szPointBuf[MAX_RULE_REGION_NUM];
		for (int i = 0; i < vld.iAreaNum; i++)
		{
			for (int j = 0; j < vld.stRegion1[i].iPointNum; j ++ )
			{
				szPointBuf[i].AppendFormat("(%d,%d)", vld.stRegion1[i].stPoints[j].iX, vld.stRegion1[i].stPoints[j].iY);
			}
		}
		m_edtMainArea1.SetWindowText(szPointBuf[0]);
		m_edtMainArea2.SetWindowText(szPointBuf[1]);
		m_edtMainArea3.SetWindowText(szPointBuf[2]);
		m_edtMainArea4.SetWindowText(szPointBuf[3]);
	}
}

//设置
void CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutySet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCALeaveDetect vld = {0};

	for (int i = 0; i <AREA_SUM; i ++)
	{
		vld.stRegion1[i].iPointNum = POINT_SUM_TO_SEND;
	}
	CString strPointStrArea1;
	CString strPointStrArea2;
	CString strPointStrArea3;
	CString strPointStrArea4;
	GetDlgItemText(IDC_EDT_ONDUTY_MAIN_AREA_1, strPointStrArea1);
	GetPolyFromString(strPointStrArea1, POINT_SUM_TO_SEND, vld.stRegion1[0]);
	GetDlgItemText(IDC_EDT_ONDUTY_MAIN_AREA_2, strPointStrArea2);
	GetPolyFromString(strPointStrArea2, POINT_SUM_TO_SEND, vld.stRegion1[1]);
	GetDlgItemText(IDC_EDT_ONDUTY_MAIN_AREA_3, strPointStrArea3);
	GetPolyFromString(strPointStrArea3, POINT_SUM_TO_SEND, vld.stRegion1[2]);
	GetDlgItemText(IDC_EDT_ONDUTY_MAIN_AREA_4, strPointStrArea4);
	GetPolyFromString(strPointStrArea4, POINT_SUM_TO_SEND, vld.stRegion1[3]);

	vld.stRule.iRuleID = m_iRuleID;
	vld.stRule.iSceneID = m_iSceneID;

	vld.stDisplayParam.iDisplayRule = m_chkAlarmRule.GetCheck();
	vld.stDisplayParam.iDisplayStat = m_chkAlarmStat.GetCheck();
	vld.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel() + 1;
	vld.stDisplayParam.iColor = m_cboUnalarmColor.GetCurSel() + 1;

	vld.iLeaveAlarmTime = GetDlgItemInt(IDC_EDT_ONDUTY_LEAVE_ALARM_TIME);
	vld.iRuturnClearAlarmTime = GetDlgItemInt(IDC_EDT_ONDUTY_RETURN_ALARM_TIME);
	vld.iAreaNum = GetDlgItemInt(IDC_EDT_ONDUTY_AREA_NUM);
	vld.iDutyNum = GetDlgItemInt(IDC_EDT_ONDUTY_NUM);
	vld.iMinSize = GetDlgItemInt(IDC_EDT_ONDUTY_MIN_SIZE);
	vld.iMaxSize = GetDlgItemInt(IDC_EDT_ONDUTY_MAX_SIZE);
	vld.iSensitivity = GetDlgItemInt(IDC_EDT_ONDUTY_SENSITIVITY);
	vld.iDisplayTarget = m_chkTargetBox.GetCheck();
	vld.iBufSize = sizeof(vld);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_RULE14_LEAVE_DETECT, m_iChannelNO, &vld, sizeof(VCALeaveDetect));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_VCASetConfig[VCA_CMD_RULE14_LEAVE_DETECT] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_VCASetConfig[VCA_CMD_RULE14_LEAVE_DETECT] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}


int CLS_VCAEVENT_OnDutyDetect::DrawArea(int _iAreaNum)
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
	CString cstrPointBufOut = "";
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		delete m_pDlgVideoView;
		m_pDlgVideoView = NULL;
		return -1;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		ChangeToTwoPoints(cPointBuf, cstrPointBufOut);
		switch (_iAreaNum)
		{
		case MAIN_AREA_1:
			m_edtMainArea1.SetWindowText(cstrPointBufOut);
			break;
		case MAIN_AREA_2:
			m_edtMainArea2.SetWindowText(cstrPointBufOut);
			break;
		case MAIN_AREA_3:
			m_edtMainArea3.SetWindowText(cstrPointBufOut);
			break;
		case MAIN_AREA_4:
			m_edtMainArea4.SetWindowText(cstrPointBufOut);
			break;
		default:
			m_edtMainArea1.SetWindowText(cstrPointBufOut);
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

//将区域的4个顶点取“左上”和“右下”两个顶点传给设备
int CLS_VCAEVENT_OnDutyDetect::ChangeToTwoPoints(char* _pcPointBufIn, CString& _cstrPointBufOut)
{
	int iLenIn = (int)strlen(_pcPointBufIn);
	int iLeftIndex[POINT_SUM] = {0};
	int iRightIndex[POINT_SUM] = {0};
	int iLeft = -1;
	int iRight = -1;
	for(int i = 0; i < iLenIn; i++)
	{
		if ('(' == _pcPointBufIn[i])
		{
			iLeft++;
			if (iLeft > 0 && iLeft < POINT_SUM)
			{
				iLeftIndex[iLeft] = i;
			}
		}
		if (')' == _pcPointBufIn[i])
		{
			iRight++;
			if (iRight > 0 && iRight < POINT_SUM)
			{
				iRightIndex[iRight] = i;
			}
		}
		if (2 == iLeft && 2 == iRight)
		{
			CString cstrTemp = _pcPointBufIn;
			cstrTemp = cstrTemp.Left(iRightIndex[iRight] + 1);
			cstrTemp = cstrTemp.Left(iLeftIndex[1]) + cstrTemp.Right(cstrTemp.GetLength() - iRightIndex[1] - 1);
			_cstrPointBufOut = cstrTemp;
 			return 0;
		}
	}
	return -1;
}

void CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea1()
{
	DrawArea(MAIN_AREA_1);
}

void CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea2()
{
	DrawArea(MAIN_AREA_2);
}

void CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea3()
{
	DrawArea(MAIN_AREA_3);
}

void CLS_VCAEVENT_OnDutyDetect::OnBnClickedBtnOndutyDrawArea4()
{
	DrawArea(MAIN_AREA_4);
}

void CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyNum()
{
	CString cstrNum = "";
	GetDlgItem(IDC_EDT_ONDUTY_NUM)->GetWindowText(cstrNum);
	if (!cstrNum.IsEmpty())
	{
		int iNum = GetDlgItemInt(IDC_EDT_ONDUTY_NUM);
		if ((2 < iNum) || (1 > iNum))
		{
			SetDlgItemInt(IDC_EDT_ONDUTY_NUM, 1);
		}
	}	
}

void CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyMinSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_ONDUTY_MIN_SIZE);
	if (iTemp < MIN_SIZE_FROM || iTemp > MIN_SIZE_TO - 1)
	{
		SetDlgItemInt(IDC_EDT_ONDUTY_MIN_SIZE, MIN_SIZE_TO - 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_OnDutyDetect::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyMaxSize()
{
	int iTemp = GetDlgItemInt(IDC_EDT_ONDUTY_MAX_SIZE);
	if (iTemp < MAX_SIZE_FROM + 1)
	{
		SetDlgItemInt(IDC_EDT_ONDUTY_MAX_SIZE, MAX_SIZE_FROM + 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_OnDutyDetect::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
	if (iTemp > MAX_SIZE_TO)
	{
		SetDlgItemInt(IDC_EDT_ONDUTY_MAX_SIZE, MAX_SIZE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_OnDutyDetect::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutyAreaNum()
{
	int iNum = GetDlgItemInt(IDC_EDT_ONDUTY_AREA_NUM);
	if (iNum < DEFAULT_ZERO || iNum > AREA_SUM)
	{
		SetDlgItemInt(IDC_EDT_ONDUTY_AREA_NUM, AREA_SUM);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_OnDutyDetect::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
	if (0 == iNum)
	{
		
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_1)->SetWindowText(_T(""));
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_2)->SetWindowText(_T(""));
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_3)->SetWindowText(_T(""));
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_4)->SetWindowText(_T(""));
	}
	else if (1 == iNum)
	{
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_2)->SetWindowText(_T(""));
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_3)->SetWindowText(_T(""));
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_4)->SetWindowText(_T(""));
	}
	else if (2 == iNum)
	{
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_3)->SetWindowText(_T(""));
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_4)->SetWindowText(_T(""));
	}
	else if (3 == iNum)
	{
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_ONDUTY_MAIN_AREA_4)->SetWindowText(_T(""));
	}
	else
	{
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ONDUTY_DRAW_AREA_4)->EnableWindow(TRUE);
	}
}

void CLS_VCAEVENT_OnDutyDetect::OnEnChangeEdtOndutySensitivity()
{
	int iSens = GetDlgItemInt(IDC_EDT_ONDUTY_SENSITIVITY);
	if (iSens < SENS_FROM || iSens > SENS_TO)
	{
		SetDlgItemInt(IDC_EDT_ONDUTY_SENSITIVITY, SENS_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_OnDutyDetect::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}
