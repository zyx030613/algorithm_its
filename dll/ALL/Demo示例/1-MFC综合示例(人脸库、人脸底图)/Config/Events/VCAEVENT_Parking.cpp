// LS_VCAEVENT_Parking.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Parking.h"

#define	LEN_2						2
#define	LEN_3						3
#define LEN_5						5
#define POINT_SUM					4		//所画区域点的个数
#define MIN_TIME_FROM				0		//触发停车报警的持续时间（秒）,最小值	
#define MIN_TIME_TO					30		//触发停车报警的持续时间（秒）,最大值
#define MIN_TIME_DEFAULT			5		//触发停车报警的持续时间（秒），默认值
#define MIN_SIZE_FROM				0		//最小尺寸，最小值
#define MIN_SIZE_TO					100		//最小尺寸，最大值
#define MIN_SIZE_DEFAULT			5		//最小尺寸，默认值
#define MAX_SIZE_FROM				0		//最大尺寸，最小值
#define MAX_SIZE_TO					100		//最大尺寸，最大值
#define MAX_SIZE_DEFAULT			30		//最大尺寸，默认值
#define SPEED_THRESHOLD_FROM		0		//最大尺寸，最小值
#define SPEED_THRESHOLD_TO			100		//最大尺寸，最大值
#define SPEED_THRESHOLD_DEFAULT		30		//最大尺寸，默认值
// CLS_VCAEVENT_Parking 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Parking, CDialog)

CLS_VCAEVENT_Parking::CLS_VCAEVENT_Parking(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Parking::IDD, pParent)
{

}

CLS_VCAEVENT_Parking::~CLS_VCAEVENT_Parking()
{
}

void CLS_VCAEVENT_Parking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_PARK_EVENT_VALID, m_chkEventValid);
	DDX_Control(pDX, IDC_CHK_PARK_SHOW_ALARM_RULE, m_chkAlarmRule);
	DDX_Control(pDX, IDC_CHK_PARK_SHOW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CHK_PARK_SHOW_TARGET_BOX, m_chkTargetBox);
	DDX_Control(pDX, IDC_EDT_PARK_ALARM_TIME, m_edtAlarmTime);
	DDX_Control(pDX, IDC_EDT_PARK_SPEED_SHREHOLD, m_edtSpeedShrehold);
	DDX_Control(pDX, IDC_CBO_PARK_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_PARK_UNALARM_COLOR, m_cboUnalarmColor);
	DDX_Control(pDX, IDC_EDT_PARK_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_PARK_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_EDT_PARK_AREA, m_edtPointArea);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Parking, CDialog)
	ON_BN_CLICKED(IDC_BTN_PARK_SET, &CLS_VCAEVENT_Parking::OnBnClickedBtnParkSet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_PARK_DRAW, &CLS_VCAEVENT_Parking::OnBnClickedBtnParkDraw)
	ON_EN_CHANGE(IDC_EDT_PARK_ALARM_TIME, &CLS_VCAEVENT_Parking::OnEnChangeEdtParkAlarmTime)
	ON_EN_CHANGE(IDC_EDT_PARK_MIN_SIZE, &CLS_VCAEVENT_Parking::OnEnChangeEdtParkMinSize)
	ON_EN_CHANGE(IDC_EDT_PARK_MAX_SIZE, &CLS_VCAEVENT_Parking::OnEnChangeEdtParkMaxSize)
	ON_EN_CHANGE(IDC_EDT_PARK_SPEED_SHREHOLD, &CLS_VCAEVENT_Parking::OnEnChangeEdtParkSpeedShrehold)
END_MESSAGE_MAP()


// CLS_VCAEVENT_Parking 消息处理程序

void CLS_VCAEVENT_Parking::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}

	// TODO: 在此处添加消息处理程序代码
}

BOOL CLS_VCAEVENT_Parking::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_VCAEVENT_Parking::OnLanguageChanged()
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_Parking::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_PARK_EVENT_VALID, IDS_VCAEVENT_EVENT_VALID);
	SetDlgItemTextEx(IDC_CHK_PARK_SHOW_ALARM_RULE, IDS_VCAEVENT_SHOW_ALARM_RULE);
	SetDlgItemTextEx(IDC_CHK_PARK_SHOW_ALARM_STAT, IDS_VCAEVENT_SHOW_ALARM_STATISTICS);
	SetDlgItemTextEx(IDC_CHK_PARK_SHOW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);
	SetDlgItemTextEx(IDC_STC_PARK_ALARM_TIME, IDS_VCAEVENT_TRIGGER_ALARM_SUSTAIN);
	SetDlgItemTextEx(IDC_STC_PARK_SPEED_SHREHOLD, IDS_VCAEVENT_SPEED_SHREHOLD);
	SetDlgItemTextEx(IDC_STC_PARK_MIN_SIZE, IDS_VCA_ABMINSIZE);
	SetDlgItemTextEx(IDC_STC_PARK_MAX_SIZE, IDS_VCA_ABMAXSIZE);
	SetDlgItemTextEx(IDC_STC_PARK_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_PARK_SPEED_SHREHOLD, IDC_STC_PARK_SPEED_SHREHOLD);
	SetDlgItemTextEx(IDC_STC_PARK_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_PARK_AREA, IDS_VCA_ABMAINREGION);
	SetDlgItemTextEx(IDC_BTN_PARK_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_PARK_SET, IDS_SET);

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

	m_edtAlarmTime.SetLimitText(LEN_2);
	SetDlgItemInt(IDC_EDT_PARK_ALARM_TIME, MIN_TIME_DEFAULT);

	m_edtSpeedShrehold.SetLimitText(LEN_5);
	m_edtMinSize.SetLimitText(LEN_2);
	SetDlgItemInt(IDC_EDT_PARK_MIN_SIZE, MIN_SIZE_DEFAULT);
	m_edtMaxSize.SetLimitText(LEN_3);
	SetDlgItemInt(IDC_EDT_PARK_MAX_SIZE, MAX_SIZE_DEFAULT);
}

void CLS_VCAEVENT_Parking::CleanText()
{
	m_edtPointArea.Clear();
}

void CLS_VCAEVENT_Parking::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Parking::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCAParking vp = {0};

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_PARKING, m_iChannelNO, &vp, sizeof(VCAParking));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Parking::NetClient_VCAGetConfig[VCA_CMD_PARKING] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkEventValid.SetCheck(vp.stRule.iValid);
		m_chkAlarmRule.SetCheck(vp.stDisplayParam.iDisplayRule);
		m_chkAlarmStat.SetCheck(vp.stDisplayParam.iDisplayStat);
		m_chkTargetBox.SetCheck(vp.iDisplayTarget);

		m_cboAlarmColor.SetCurSel(vp.stDisplayParam.iAlarmColor);
		m_cboUnalarmColor.SetCurSel(vp.stDisplayParam.iColor);

		SetDlgItemInt(IDC_EDT_PARK_ALARM_TIME, vp.iMinTime);

		CString cstrVelocity;
		cstrVelocity.Format("%.1f", vp.fThVelocity/10.0);
		SetDlgItemText(IDC_EDT_PARK_SPEED_SHREHOLD, cstrVelocity);	

		SetDlgItemInt(IDC_EDT_PARK_MIN_SIZE, vp.iMiniSize);
		SetDlgItemInt(IDC_EDT_PARK_MAX_SIZE, vp.iMaxSize);

		int iPointNum = vp.stRegion.iPointNum;
		CString cstPointBuf = "";
		for (int i=0; i<iPointNum; i++)
		{
			cstPointBuf.AppendFormat("(%d,%d)", vp.stRegion.stPoints[i].iX, vp.stRegion.stPoints[i].iY);
		}
		m_edtPointArea.SetWindowText(cstPointBuf);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Parking::NetClient_VCAGetConfig[VCA_CMD_PARKING] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_Parking::OnBnClickedBtnParkSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Parking::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	if(GetDlgItemInt(IDC_EDT_PARK_MIN_SIZE) >= GetDlgItemInt(IDC_EDT_PARK_MAX_SIZE))
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Parking::MAX_SIZE Value Must Greater Than MIN_SIZE Value (%d,%d)", m_iLogonID,m_iChannelNO);
	}

	VCAParking vp = {0};

	CString cstrVelocity = "";
	GetDlgItemText(IDC_EDT_PARK_SPEED_SHREHOLD, cstrVelocity);
	float fVelocity;
	fVelocity = (float)atof(cstrVelocity);
	vp.fThVelocity = (int)(fVelocity * 10);

	vp.iDisplayTarget = m_chkTargetBox.GetCheck();
	vp.iMaxSize = GetDlgItemInt(IDC_EDT_PARK_MAX_SIZE);
	vp.iMiniSize = GetDlgItemInt(IDC_EDT_PARK_MIN_SIZE);
	vp.iMinTime = GetDlgItemInt(IDC_EDT_PARK_ALARM_TIME);

	vp.stDisplayParam.iDisplayRule = m_chkAlarmRule.GetCheck();
	vp.stDisplayParam.iDisplayStat = m_chkAlarmStat.GetCheck();
	vp.stDisplayParam.iAlarmColor = m_cboAlarmColor.GetCurSel();
	vp.stDisplayParam.iColor = m_cboUnalarmColor.GetCurSel();

	vp.stRule.iRuleID = m_iRuleID;
	vp.stRule.iSceneID = m_iSceneID;
//	vp.stRule.iValid = m_chkEventValid.GetCheck();

	vp.stRegion.iPointNum = POINT_SUM;
	CString strPointArea = "";
	GetDlgItemText(IDC_EDT_PARK_AREA, strPointArea);
	GetPolyFromString(strPointArea, POINT_SUM, vp.stRegion);

	vp.iBufSize = sizeof(vp);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_PARKING, m_iChannelNO, &vp, sizeof(VCAParking));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_Parking::NetClient_VCASetConfig[VCA_CMD_PARKING] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_Parking::NetClient_VCASetConfig[VCA_CMD_PARKING] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}


void CLS_VCAEVENT_Parking::OnBnClickedBtnParkDraw()
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
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
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
		m_edtPointArea.SetWindowText(cPointBuf);
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Parking::OnEnChangeEdtParkAlarmTime()
{
	int iAlarmTime = GetDlgItemInt(IDC_EDT_PARK_ALARM_TIME);
	if (iAlarmTime < MIN_TIME_FROM || iAlarmTime > MIN_TIME_TO)
	{
		SetDlgItemInt(IDC_EDT_PARK_ALARM_TIME, MIN_TIME_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Parking::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Parking::OnEnChangeEdtParkMinSize()
{
	int iMinSize = GetDlgItemInt(IDC_EDT_PARK_MIN_SIZE);
	if (iMinSize < MIN_SIZE_FROM || iMinSize > MIN_SIZE_TO - 1)
	{
		SetDlgItemInt(IDC_EDT_PARK_MIN_SIZE, MIN_TIME_TO - 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Parking::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Parking::OnEnChangeEdtParkMaxSize()
{
	int iMaxSize = GetDlgItemInt(IDC_EDT_PARK_MAX_SIZE);
	if (iMaxSize < (MIN_SIZE_FROM + 1))
	{
		SetDlgItemInt(IDC_EDT_PARK_MAX_SIZE, MIN_SIZE_FROM + 1);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Parking::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
	if (iMaxSize > MIN_SIZE_TO)
	{
		SetDlgItemInt(IDC_EDT_PARK_MAX_SIZE, MIN_SIZE_TO);
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_Parking::Put Invalid Value(%d,%d)", m_iLogonID,m_iChannelNO);
	}
}

void CLS_VCAEVENT_Parking::OnEnChangeEdtParkSpeedShrehold()
{
	CString cstrSpeed;
	GetDlgItem(IDC_EDT_PARK_SPEED_SHREHOLD)->GetWindowText(cstrSpeed);
	// 只允许输数据
	int iStringLength = cstrSpeed.GetLength();
	int iDotCount = 0;
	// 点字符不能多于1个,小数点后只能有一位数字
	for (int iIndex = 0; iIndex < iStringLength; iIndex++)
	{
		if (cstrSpeed[iIndex] == '.' )
		{
			iDotCount++;
			if ((1 == iDotCount) && (iIndex < iStringLength - 1))
			{
				CString cstrTmp;
				cstrTmp = cstrSpeed.Left(iIndex + 2);
				GetDlgItem(IDC_EDT_PARK_SPEED_SHREHOLD)->SetWindowText(cstrTmp);
			}
			if (iDotCount > 1)
			{
				CString cstrTmp;
				cstrTmp = cstrSpeed.Left(iIndex);
				cstrTmp += cstrSpeed.Right(cstrSpeed.GetLength() - iIndex - 1);
				GetDlgItem(IDC_EDT_PARK_SPEED_SHREHOLD)->SetWindowText(cstrTmp);
			}
		}
	}

	// 不允许输入数字和点以外的字符
	for (int iIndex = 0; iIndex < iStringLength; iIndex++)
	{
		if (cstrSpeed[iIndex] != '.' && (cstrSpeed[iIndex] > '9' || cstrSpeed[iIndex] < '0'))
		{
			cstrSpeed = cstrSpeed.Left(iIndex) + cstrSpeed.Right(cstrSpeed.GetLength() - iIndex - 1);
			GetDlgItem(IDC_EDT_PARK_SPEED_SHREHOLD)->SetWindowText(cstrSpeed);
		}
	}

	CString cstrVelocity = "";
	GetDlgItemText(IDC_EDT_PARK_SPEED_SHREHOLD, cstrVelocity);
	float fVelocity = 0.0;
	fVelocity = (float)atof(cstrVelocity);
	if (fVelocity > SPEED_THRESHOLD_TO)
	{
		SetDlgItemInt(IDC_EDT_PARK_SPEED_SHREHOLD, SPEED_THRESHOLD_TO);
	}
}
