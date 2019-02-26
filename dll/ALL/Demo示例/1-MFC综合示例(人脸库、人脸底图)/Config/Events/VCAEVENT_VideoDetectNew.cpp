// VCAEVENT_VideoDetectNew.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_VideoDetectNew.h"

#define ALOG_TYPE_SUM			9			//算法类型总数
#define DEFAULT_ZORO			0			//默认值 0
#define SENSITIVITY_MIN			0			//灵敏度最小值
#define SENSITIVITY_MAX			5			//灵敏度最大值
#define TIME_MIN				0			//检测时间最小值
#define	TIME_MAX				5			//检测时间最大值
#define VIDEO_DIAGNOSE_RULEID	8			//视频诊断ruleid用8

// CLS_VCAEVENT_VideoDetectNew 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_VideoDetectNew, CDialog)

CLS_VCAEVENT_VideoDetectNew::CLS_VCAEVENT_VideoDetectNew(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_VideoDetectNew::IDD, pParent)
{

}

CLS_VCAEVENT_VideoDetectNew::~CLS_VCAEVENT_VideoDetectNew()
{
}

void CLS_VCAEVENT_VideoDetectNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_VIDEO_NEW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CBO_VIDEO_NEW_ALGO_TYPE, m_cboAlgoType);
	DDX_Control(pDX, IDC_CHK_VIDEO_NEW_ALGO_TYPE, m_chkUse);
	DDX_Control(pDX, IDC_SLD_SENSITIVITY, m_sldSensitivity);
	DDX_Control(pDX, IDC_SLD_VIDEO_NEW_DETECT_TIME, m_sldDetectTime);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_VideoDetectNew, CDialog)
	ON_BN_CLICKED(IDC_BTN_VIDEO_NEW_SET, &CLS_VCAEVENT_VideoDetectNew::OnBnClickedBtnVideoNewSet)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_SENSITIVITY, &CLS_VCAEVENT_VideoDetectNew::OnNMCustomdrawSldSensitivity)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_VIDEO_NEW_DETECT_TIME, &CLS_VCAEVENT_VideoDetectNew::OnNMCustomdrawSldVideoNewDetectTime)
	ON_CBN_SELCHANGE(IDC_CBO_VIDEO_NEW_ALGO_TYPE, &CLS_VCAEVENT_VideoDetectNew::OnCbnSelchangeCboVideoNewAlgoType)
END_MESSAGE_MAP()


// CLS_VCAEVENT_VideoDetectNew 消息处理程序

void CLS_VCAEVENT_VideoDetectNew::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		UpdatePageUI();
	}
}

BOOL CLS_VCAEVENT_VideoDetectNew::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_VCAEVENT_VideoDetectNew::OnLanguageChanged()
{	
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_VideoDetectNew::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_VIDEO_NEW_ALARM_STAT, IDS_VCA_SHOW_ALARM_STATISTIC);
	SetDlgItemTextEx(IDC_STC_VIDEO_NEW_ALGO_TYPE, IDS_VCA_AUDIO_TYPE);
	SetDlgItemTextEx(IDC_CHK_VIDEO_NEW_ALGO_TYPE, IDS_CONFIG_VIDEOPARAM_ENABLE);
	SetDlgItemTextEx(IDC_STC_VIDEO_NEW_SENSITIVITY, IDS_VCA_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_VIDEO_NEW_DETECT_TIME, IDS_VCA_VD_CHECKTIME);
	SetDlgItemTextEx(IDC_BTN_VIDEO_NEW_SET, IDS_SET);

	m_cboAlgoType.ResetContent();
	const CString cstType[] = {GetTextEx(IDS_VCAEVENT_NOISE_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_DEFINITION_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_BRIGHT_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_COLOR_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_SCREEN_FREEZE_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_SIGNAL_LOSE_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_SCENE_CHANGE_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_MAN_MADE_INTER_DIAGNOSE),
		GetTextEx(IDS_VCAEVENT_PTZ_LOSE_CONTROL_DIAGNOSE)};
	for(int i=0; i<sizeof(cstType)/sizeof(CString); i++)
	{
		m_cboAlgoType.InsertString(i, cstType[i]);
	}
	m_cboAlgoType.SetCurSel(0);


	m_sldDetectTime.SetRange(TIME_MIN, TIME_MAX);
	m_sldSensitivity.SetPos(DEFAULT_ZORO);
	SetDlgItemInt(IDC_STC_VIDEO_NEW_SENSITIVITY_NUM,DEFAULT_ZORO);

	m_sldSensitivity.SetRange(SENSITIVITY_MIN, SENSITIVITY_MAX);
	m_sldDetectTime.SetPos(DEFAULT_ZORO);
	SetDlgItemInt(IDC_STC_VIDEO_NEW_DETECT_TIME_NUM, DEFAULT_ZORO);
}

void CLS_VCAEVENT_VideoDetectNew::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_VideoDetectNew::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCA_TRuleParam_VideoDiagnose vtvd = {0};
	vtvd.iChannelNo = m_iChannelNO;
	vtvd.iRuleID = VIDEO_DIAGNOSE_RULEID;//视频诊断固定用8
	vtvd.iSceneId = m_iSceneID;
	vtvd.iType = m_cboAlgoType.GetCurSel();

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_VIDEODIAGNOSE, m_iChannelNO, &vtvd, sizeof(VCA_TRuleParam_VideoDiagnose));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_VideoDetectNew::NetClient_VCAGetConfig[VCA_CMD_VIDEODIAGNOSE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkUse.SetCheck(vtvd.iEnable);
		m_chkAlarmStat.SetCheck(vtvd.iDisplayStat);

		m_sldSensitivity.SetPos(vtvd.iLevel);
		SetDlgItemInt(IDC_STC_VIDEO_NEW_SENSITIVITY_NUM, vtvd.iLevel);
		m_sldDetectTime.SetPos(vtvd.iTime);
		SetDlgItemInt(IDC_STC_VIDEO_NEW_DETECT_TIME_NUM, vtvd.iTime);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_VideoDetectNew::NetClient_VCAGetConfig[VCA_CMD_VIDEODIAGNOSE] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_VideoDetectNew::OnBnClickedBtnVideoNewSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_VideoDetectNew::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCA_TRuleParam_VideoDiagnose vtvd = {0};

	vtvd.iChannelNo = m_iChannelNO;
	vtvd.iRuleID = VIDEO_DIAGNOSE_RULEID;//视频诊断固定用8
	vtvd.iSceneId = m_iSceneID;
	vtvd.iDisplayStat = m_chkAlarmStat.GetCheck();
	vtvd.iEnable = m_chkUse.GetCheck();
	vtvd.iLevel = m_sldSensitivity.GetPos();
	vtvd.iTime = m_sldDetectTime.GetPos();
	vtvd.iType = m_cboAlgoType.GetCurSel();
	vtvd.iSize = sizeof(vtvd);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_VIDEODIAGNOSE, m_iChannelNO, &vtvd, sizeof(VCA_TRuleParam_VideoDiagnose));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_VideoDetectNew::NetClient_VCASetConfig[VCA_CMD_VIDEODIAGNOSE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_VideoDetectNew::NetClient_VCASetConfig[VCA_CMD_VIDEODIAGNOSE] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_VideoDetectNew::OnNMCustomdrawSldSensitivity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iPos = m_sldSensitivity.GetPos();
	SetDlgItemInt(IDC_STC_VIDEO_NEW_SENSITIVITY_NUM, iPos);
	*pResult = 0;
}

void CLS_VCAEVENT_VideoDetectNew::OnNMCustomdrawSldVideoNewDetectTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int iPos = m_sldDetectTime.GetPos();
	SetDlgItemInt(IDC_STC_VIDEO_NEW_DETECT_TIME_NUM, iPos);

	*pResult = 0;
}

void CLS_VCAEVENT_VideoDetectNew::OnCbnSelchangeCboVideoNewAlgoType()
{
	UpdatePageUI();
}
