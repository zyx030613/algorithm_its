
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_AudioDiagnose.h"

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_AudioDiagnose, CDialog)

CLS_VCAEVENT_AudioDiagnose::CLS_VCAEVENT_AudioDiagnose(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_AudioDiagnose::IDD, pParent)
{

}

CLS_VCAEVENT_AudioDiagnose::~CLS_VCAEVENT_AudioDiagnose()
{
}

void CLS_VCAEVENT_AudioDiagnose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_AUDIO_UNALARM_COLOR, m_cboUnAlarmColor);
	DDX_Control(pDX, IDC_CBO_AUDIO_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_CBO_VAC_TYPE, m_cboEnableType);
	DDX_Control(pDX, IDC_CBO_LEVEL, m_cboLevel);
	DDX_Control(pDX, IDC_CHK_AUDIO_RULE_DISPLAY, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE, m_chkEnableType);
	for (int i=0; i<VCA_AUDIO_MAX; i++)
	{
		DDX_Control(pDX, IDC_CHK_TYPE1+i, m_chkType[i]);
	}
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_AudioDiagnose, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_VCA_AUDIO_SET, &CLS_VCAEVENT_AudioDiagnose::OnBnClickedBtnVcaAudioSet)
	ON_BN_CLICKED(IDC_CHK_VCA_TYPE, &CLS_VCAEVENT_AudioDiagnose::OnBnClickedChkVcaType)
END_MESSAGE_MAP()


// CLS_VCAEVENT_AudioDiagnose 消息处理程序

BOOL CLS_VCAEVENT_AudioDiagnose::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	UpdateUIText();

	return TRUE;
}

void CLS_VCAEVENT_AudioDiagnose::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_AudioDiagnose::UpdateUIText()
{
	SetDlgItemTextEx(IDC_STC_AUDIO_UNALARM_COLOR, IDS_VCA_NOALARM_COLOR);
	SetDlgItemTextEx(IDC_STC_AUDIO_ALARM_COLOR, IDS_VCA_ALARM_COLOR);
	SetDlgItemTextEx(IDC_CHK_AUDIO_RULE_DISPLAY, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHK_AUDIO_DIAPALYSTATE, IDS_VCA_DISPLAY_ALARMSTATUS);

	SetDlgItemTextEx(IDC_CHK_VCA_TYPE, IDS_VCA_AUDIO_TYPE);
	SetDlgItemTextEx(IDC_STC_LEVEL, IDS_VCA_LEVEL);
	SetDlgItemTextEx(IDC_BTN_VCA_AUDIO_SET, IDS_VCA_LINK_SET);

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), 
		GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_BLUE), 
		GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), 
		GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboUnAlarmColor.ResetContent();
	m_cboAlarmColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboUnAlarmColor.InsertString(i, strColor[i]);
		m_cboAlarmColor.InsertString(i, strColor[i]);
	}

	const CString strType[] = {GetTextEx(IDS_VCA_AUDIO_DROP), GetTextEx(IDS_VCA_AUDIO_UNUSUAL), 
		GetTextEx(IDS_VCA_NOISE_RESTRAIN), GetTextEx(IDS_VCA_ECHO_RESTRAIN), 
		GetTextEx(IDS_VCA_AUDIO_SIGNAL_UNUSUAL)};
	for (int i=0; i<sizeof(strType)/sizeof(CString); i++)
	{
		m_chkType[i].SetWindowText(strType[i]);
	}
	
	m_cboEnableType.ResetContent();
	for (int i=0; i<sizeof(strType)/sizeof(CString); i++)
	{
		m_cboEnableType.InsertString(i,strType[i]);
	}

	m_cboLevel.ResetContent();
	CString cstr;
	for (int i=0; i<sizeof(strType)/sizeof(CString); i++)
	{
		cstr.Format("%d",i+1);
		m_cboLevel.InsertString(i,cstr);
	}
}

void CLS_VCAEVENT_AudioDiagnose::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_AudioDiagnose::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable )
		return;

	VCA_TRuleParam_AudioDiagnose st = {0};
	st.iSize = sizeof(st);
	st.iChannelNo = m_iChannelNO;
	st.iRuleID = m_iRuleID;
	st.iSceneId = m_iSceneID;
	int iCmd = VCA_CMD_AUDIODIAGNOSE;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet >= 0)
	{
		m_chkDisplayRule.SetCheck(st.iDisplayStat);
		m_chkEnableType.SetCheck(st.iEnable);
		m_cboLevel.SetCurSel(st.iLevel-1);
		for (int i=0; i<VCA_AUDIO_MAX; i++)
		{
			m_chkType[i].SetCheck(!((st.iType & i)==0));
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}
}

void CLS_VCAEVENT_AudioDiagnose::OnBnClickedBtnVcaAudioSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable )
		return;

	VCA_TRuleParam_AudioDiagnose st = {0};
	st.iSize = sizeof(st);
	st.iChannelNo = m_iChannelNO;
	st.iRuleID = m_iRuleID;
	st.iSceneId = m_iSceneID;
	st.iDisplayStat = m_chkDisplayRule.GetCheck()?1:0;
	st.iEnable = m_chkEnableType.GetCheck()?1:0;
	st.iType = m_cboEnableType.GetCurSel();
	st.iType = m_chkType[0].GetCheck() | (m_chkType[1].GetCheck() << 1) | 
		(m_chkType[2].GetCheck()<<2) | (m_chkType[3].GetCheck()<<3) |
		(m_chkType[4].GetCheck()<<4);
	st.iLevel = m_cboLevel.GetCurSel()+1;
	int iCmd = VCA_CMD_AUDIODIAGNOSE;
	iRet = NetClient_VCASetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet >= 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCASetConfig(%d,%d,%d)error = %d",m_iLogonID, iCmd,m_iChannelNO);
	}
}

void CLS_VCAEVENT_AudioDiagnose::OnBnClickedChkVcaType()
{
	for (int i=0; i<VCA_AUDIO_MAX; i++)
	{
		m_chkType[i].EnableWindow(m_chkEnableType.GetCheck());
	}
}
