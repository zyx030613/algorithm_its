// VCAEVENT_AudioDiagnoseNew.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_AudioDiagnoseNew.h"

#define DEFAULT_ZORO			0			//默认值 0
#define SENSITIVITY_MIN			0			//灵敏度最小值
#define SENSITIVITY_MAX			5			//灵敏度最大值
#define AUDIO_DIAGNOSE_RULEID	9			//音频诊断ruleid用9

// CLS_VCAEVENT_AudioDiagnoseNew 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_AudioDiagnoseNew, CDialog)

CLS_VCAEVENT_AudioDiagnoseNew::CLS_VCAEVENT_AudioDiagnoseNew(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_AudioDiagnoseNew::IDD, pParent)
{

}

CLS_VCAEVENT_AudioDiagnoseNew::~CLS_VCAEVENT_AudioDiagnoseNew()
{
}

void CLS_VCAEVENT_AudioDiagnoseNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_AUDIO_NEW_ALARM_STAT, m_chkAlarmStat);
	DDX_Control(pDX, IDC_CBO_AUDIO_NEW_ALGO_TYPE, m_cboAlgoType);
	DDX_Control(pDX, IDC_CHK_AUDIO_NEW_ALGO_TYPE, m_chkUse);
	DDX_Control(pDX, IDC_SLD_AUDIO_NEW_SENSITIVITY, m_sldSensitivity);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_AudioDiagnoseNew, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_AUDIO_NEW_SET, &CLS_VCAEVENT_AudioDiagnoseNew::OnBnClickedBtnAudioNewSet)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_AUDIO_NEW_SENSITIVITY, &CLS_VCAEVENT_AudioDiagnoseNew::OnNMCustomdrawSldAudioNewSensitivity)
	ON_CBN_SELCHANGE(IDC_CBO_AUDIO_NEW_ALGO_TYPE, &CLS_VCAEVENT_AudioDiagnoseNew::OnCbnSelchangeCboAudioNewAlgoType)
END_MESSAGE_MAP()


// CLS_VCAEVENT_AudioDiagnoseNew 消息处理程序


BOOL CLS_VCAEVENT_AudioDiagnoseNew::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLS_VCAEVENT_AudioDiagnoseNew::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UpdatePageUI();
	}
}


void CLS_VCAEVENT_AudioDiagnoseNew::OnLanguageChanged()
{	
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_AudioDiagnoseNew::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_AUDIO_NEW_ALARM_STAT, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STC_AUDIO_NEW_ALGO_TYPE, IDS_VCA_AUDIO_TYPE);
	SetDlgItemTextEx(IDC_CHK_AUDIO_NEW_ALGO_TYPE, IDS_CONFIG_VIDEOPARAM_ENABLE);
	SetDlgItemTextEx(IDC_STC_AUDIO_NEW_SENSITIVITY, IDS_VCA_SENSITIVITY);
	SetDlgItemTextEx(IDC_BTN_AUDIO_NEW_SET, IDS_SET);

	m_cboAlgoType.ResetContent();
	const CString cstType[] = {GetTextEx(IDS_VCA_AUDIO_DROP),
		GetTextEx(IDS_VCA_AUDIO_UNUSUAL),
		GetTextEx(IDS_VCA_NOISE_RESTRAIN),
		GetTextEx(IDS_VCA_ECHO_RESTRAIN),
		GetTextEx(IDS_VCA_AUDIO_SIGNAL_UNUSUAL)};
	for(int i = 0; i < sizeof(cstType)/sizeof(CString); i++)
	{
		m_cboAlgoType.InsertString(i, cstType[i]);
	}
	m_cboAlgoType.SetCurSel(0);

	m_sldSensitivity.SetRange(SENSITIVITY_MIN, SENSITIVITY_MAX);
	m_sldSensitivity.SetPos(DEFAULT_ZORO);
	SetDlgItemInt(IDC_STC_VIDEO_NEW_SENSITIVITY_NUM,DEFAULT_ZORO);
}

void CLS_VCAEVENT_AudioDiagnoseNew::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_AudioDiagnoseNew::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCA_TRuleParam_AudioDiagnose vtad = {0};

	vtad.iChannelNo = m_iChannelNO;
	vtad.iSceneId = m_iSceneID;
	vtad.iRuleID = AUDIO_DIAGNOSE_RULEID;
	vtad.iType = m_cboAlgoType.GetCurSel();

	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_AUDIODIAGNOSE, m_iChannelNO, &vtad, sizeof(VCA_TRuleParam_AudioDiagnose));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_AudioDiagnoseNew::NetClient_VCAGetConfig[VCA_CMD_AUDIODIAGNOSE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkUse.SetCheck(vtad.iEnable);
		m_chkAlarmStat.SetCheck(vtad.iDisplayStat);

		m_sldSensitivity.SetPos(vtad.iLevel);
		SetDlgItemInt(IDC_STC_AUDIO_NEW_SENSITIVITY_NUM, vtad.iLevel);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_AudioDiagnoseNew::NetClient_VCAGetConfig[VCA_CMD_AUDIODIAGNOSE] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
} 

void CLS_VCAEVENT_AudioDiagnoseNew::OnBnClickedBtnAudioNewSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_AudioDiagnoseNew::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	VCA_TRuleParam_AudioDiagnose vtad = {0};

	vtad.iChannelNo = m_iChannelNO;
	vtad.iRuleID = AUDIO_DIAGNOSE_RULEID;
	vtad.iSceneId = m_iSceneID;
	vtad.iDisplayStat = m_chkAlarmStat.GetCheck();
	vtad.iEnable = m_chkUse.GetCheck();
	vtad.iLevel = m_sldSensitivity.GetPos();
	vtad.iType = m_cboAlgoType.GetCurSel();
	vtad.iSize = sizeof(vtad);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_AUDIODIAGNOSE, m_iChannelNO, &vtad, sizeof(VCA_TRuleParam_AudioDiagnose));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_AudioDiagnoseNew::NetClient_VCASetConfig[VCA_CMD_AUDIODIAGNOSE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_AudioDiagnoseNew::NetClient_VCASetConfig[VCA_CMD_AUDIODIAGNOSE] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_AudioDiagnoseNew::OnNMCustomdrawSldAudioNewSensitivity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int iPos = m_sldSensitivity.GetPos();
	SetDlgItemInt(IDC_STC_AUDIO_NEW_SENSITIVITY_NUM, iPos);
	*pResult = 0;
}

void CLS_VCAEVENT_AudioDiagnoseNew::OnCbnSelchangeCboAudioNewAlgoType()
{
	UpdatePageUI();
}
