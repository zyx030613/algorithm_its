// LS_VCAEVENT_VIDEODETECT.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_VideoDetect.h"


// CLS_VCAEVENT_VideoDetect dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_VideoDetect, CDialog)

CLS_VCAEVENT_VideoDetect::CLS_VCAEVENT_VideoDetect(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_VideoDetect::IDD, pParent)
{

}

CLS_VCAEVENT_VideoDetect::~CLS_VCAEVENT_VideoDetect()
{
}

void CLS_VCAEVENT_VideoDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DisplayState, m_chkDisplayState);
	DDX_Control(pDX, IDC_EDIT_CheckTime, m_edtCheckTime);
	DDX_Control(pDX, IDC_CHECK_Noise, m_chkNoise);
	DDX_Control(pDX, IDC_CHECK_Clarity, m_chkClarity);
	DDX_Control(pDX, IDC_CHECK_Bright, m_chkBright);
	DDX_Control(pDX, IDC_CHECK_Color, m_chkColor);
	DDX_Control(pDX, IDC_CHECK_Freeze, m_chkFreeze);
	DDX_Control(pDX, IDC_CHECK_Nosignal, m_chkNosignal);
	DDX_Control(pDX, IDC_CHECK_Change, m_chkChange);
	DDX_Control(pDX, IDC_CHECK_Interface, m_chkInterfere);
	DDX_Control(pDX, IDC_CHECK_PTZ_LostCtrl, m_chkPTZ_Lost);
	DDX_Control(pDX, IDC_EDIT_VideoDetect_Enable, m_edtEnable);
	DDX_Control(pDX, IDC_EDIT_VideoDetect_level, m_edtLevel);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_VideoDetect, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_VideoDetectSet, &CLS_VCAEVENT_VideoDetect::OnBnClickedButtonVideodetectset)
	ON_BN_CLICKED(IDC_BUTTON_VideoDetectStop, &CLS_VCAEVENT_VideoDetect::OnBnClickedButtonVideodetectstop)
	ON_BN_CLICKED(IDC_BUTTON_VideoDetectStart, &CLS_VCAEVENT_VideoDetect::OnBnClickedButtonVideodetectstart)
END_MESSAGE_MAP()


// CLS_VCAEVENT_VideoDetect message handlers

BOOL CLS_VCAEVENT_VideoDetect::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_VideoDetect::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	CleanText();
	UpdatePageUI();
}

void CLS_VCAEVENT_VideoDetect::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	VCA_TRuleParam_VideoDiagnose vcap = {0};
	//memset(vcap, 0, sizeof(VCA_TRuleParam_VideoDiagnose));
	vcap.iChannelNo = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_VIDEODIAGNOSE, m_iChannelNO, &vcap, sizeof(VCA_TRuleParam_VideoDiagnose));
	
	if (iRet >= 0)
	{
		if (vcap.iSize <= 0)
		{
			return;
		}
		
		int iEventType = vcap.iType;

		//chkVDDisplayStat->Checked = (tr.stDisplayParam.iDisplayStat != 0);
		//edtVCAVDCheckTime->Text = vd.m_iCheckTime;
		m_chkNoise.SetCheck(!((iEventType & VCA_AVD_NOISE)==0));
		m_chkClarity.SetCheck(!((iEventType & VCA_AVD_CLARITY)==0));
		m_chkBright.SetCheck(!((iEventType & VCA_AVD_BRIGHT_ABMNL)==0))  ;
		m_chkColor.SetCheck(!((iEventType & VCA_ADV_COLOR)==0));
		m_chkFreeze.SetCheck( !((iEventType & VCA_ADV_FREEZE)==0));
		m_chkNosignal.SetCheck(!((iEventType & VCA_ADV_NOSIGNAL)==0));
		m_chkChange.SetCheck(!((iEventType & VCA_ADV_CHANGE)==0));
		m_chkInterfere.SetCheck(!((iEventType & VCA_ADV_INTERFERE)==0));
		m_chkPTZ_Lost.SetCheck(!((iEventType & VCA_ADV_PTZ_LOST_CTL)==0));

		m_chkDisplayState.SetCheck(vcap.iDisplayStat);
		SetDlgItemInt(IDC_EDIT_CheckTime, vcap.iTime);
		SetDlgItemInt(IDC_EDIT_VideoDetect_level, vcap.iLevel);
		SetDlgItemInt(IDC_EDIT_VideoDetect_Enable, vcap.iEnable);
		SetSceneID(vcap.iSceneId);
		SetRuleID(vcap.iRuleID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "[CVCAEventPage::UpdateUI_Event]TDVCAGetConfig error = 0x%p\n", GetLastError());
	}

	/*vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable )
		return;

	vp->chnParam[m_iChannelNO].iRuleID = m_iRuleID;
	int iRuleID = m_iRuleID;

	vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID = VCA_EVENT_VIDEODETECT;
	int iCmd = VCA_CMD_GET_RULE10_VIDEODETECT;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if (vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_VIDEODETECT)
		{
			return;
		}
		const vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[iRuleID];
		const vca_TVideoDetection& vd = vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stVideoDetection;

		if (!tr.iValid || !vd.iValid)
			return;
		int iEventType = vd.iValid;

		//chkVDDisplayStat->Checked = (tr.stDisplayParam.iDisplayStat != 0);
		//edtVCAVDCheckTime->Text = vd.m_iCheckTime;
		m_chkNoise.SetCheck(!((iEventType & VCA_AVD_NOISE)==0));
		m_chkClarity.SetCheck(!((iEventType & VCA_AVD_CLARITY)==0));
		m_chkBright.SetCheck(!((iEventType & VCA_AVD_BRIGHT_ABMNL)==0))  ;
		m_chkColor.SetCheck(!((iEventType & VCA_ADV_COLOR)==0));
		m_chkFreeze.SetCheck( !((iEventType & VCA_ADV_FREEZE)==0));
		m_chkNosignal.SetCheck(!((iEventType & VCA_ADV_NOSIGNAL)==0));
		m_chkChange.SetCheck(!((iEventType & VCA_ADV_CHANGE)==0));
		m_chkInterfere.SetCheck(!((iEventType & VCA_ADV_INTERFERE)==0));
		m_chkPTZ_Lost.SetCheck(!((iEventType & VCA_ADV_PTZ_LOST_CTL)==0));

		m_chkDisplayState.SetCheck(tr.stDisplayParam.iDisplayStat);
		SetDlgItemInt(IDC_EDIT_CheckTime, vd.m_iCheckTime);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "[CVCAEventPage::UpdateUI_Event]TDVCAGetConfig error = 0x%p\n", GetLastError());
	}*/
}

void CLS_VCAEVENT_VideoDetect::OnBnClickedButtonVideodetectset()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	VCA_TRuleParam_VideoDiagnose vcap = {0};
	//memset(vcap, 0, sizeof(VCA_TRuleParam_VideoDiagnose));
	vcap.iRuleID = m_iRuleID;
	vcap.iSceneId = m_iSceneID;
	vcap.iChannelNo = m_iChannelNO;
	vcap.iDisplayStat = m_chkDisplayState.GetCheck();
	vcap.iType = m_chkNoise.GetCheck() | (m_chkClarity.GetCheck() << 1) | 
		(m_chkBright.GetCheck()<<2) | (m_chkColor.GetCheck()<<3) |
		(m_chkFreeze.GetCheck()<<4) | (m_chkNosignal.GetCheck()<<5) |
		(m_chkChange.GetCheck()<<6) | (m_chkInterfere.GetCheck()<<7) | 
		(m_chkPTZ_Lost.GetCheck()<<8);
	vcap.iTime = GetDlgItemInt(IDC_EDIT_CheckTime);
	vcap.iLevel = GetDlgItemInt(IDC_EDIT_VideoDetect_level);
	vcap.iEnable = GetDlgItemInt(IDC_EDIT_VideoDetect_Enable);


	/*vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->chnParam[m_iChannelNO].iRuleID = m_iRuleID;
	int iRuleID = m_iRuleID;

	//视频诊断只支持规则0
	vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[iRuleID];
	tr.iValid=m_chkNoise.GetCheck() | (m_chkClarity.GetCheck() << 1) | 
		(m_chkBright.GetCheck()<<2) | (m_chkColor.GetCheck()<<3) |
		(m_chkFreeze.GetCheck()<<4) | (m_chkNosignal.GetCheck()<<5) |
		(m_chkChange.GetCheck()<<6) | (m_chkInterfere.GetCheck()<<7) | 
		(m_chkPTZ_Lost.GetCheck()<<8);
	vp->chnParam[m_iChannelNO].rule[iRuleID].iEventID = VCA_EVENT_VIDEODETECT;
	vca_TVideoDetection& vd = vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stVideoDetection;
	//    pm->iValid = chkVCAFaceInvalid->Checked;
	tr.stDisplayParam.iDisplayStat = m_chkDisplayState.GetCheck();
	vd.m_iCheckTime = GetDlgItemInt(IDC_EDIT_CheckTime );*/

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_VIDEODIAGNOSE, m_iChannelNO, &vcap, sizeof(VCA_TRuleParam_VideoDiagnose));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CVCAEventPage::OnBnClickedButtonEventset]TDVCASetConfig video detect error = %d", GetLastError());
	}
	else
	{
		//重启智能库
		RestartVCALib(m_iLogonID, m_iChannelNO);
	}

}

void CLS_VCAEVENT_VideoDetect::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_VideoDetect::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_DisplayState, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STATIC_CheckTime, IDS_VCA_VD_CHECKTIME);

	SetDlgItemTextEx(IDC_CHECK_Noise, IDS_VCA_VD_NOISE);
	SetDlgItemTextEx(IDC_CHECK_Clarity, IDS_VCA_VD_CLARITY);
	SetDlgItemTextEx(IDC_CHECK_Bright, IDS_VCA_VD_BRIGHT);
	SetDlgItemTextEx(IDC_CHECK_Color, IDS_VCA_VD_COLOR);
	SetDlgItemTextEx(IDC_CHECK_Freeze, IDS_VCA_VD_FREEZE);
	SetDlgItemTextEx(IDC_CHECK_Nosignal, IDS_VCA_VD_NOSIGNAL);
	SetDlgItemTextEx(IDC_CHECK_Change, IDS_VCA_VD_CHANGE);
	SetDlgItemTextEx(IDC_CHECK_Interface, IDS_VCA_VD_INTERFACE);
	SetDlgItemTextEx(IDC_CHECK_PTZ_LostCtrl, IDS_VCA_VD_PTZ_LOSTCTRL);
	SetDlgItemTextEx(IDC_STATIC_VideoDetect_Enable, IDS_VCA_VIDEODETECT_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_VideoDetect_Level, IDS_VCA_VIDEODETECT_LEVEL);

	SetDlgItemTextEx(IDC_BUTTON_VideoDetectSet, IDS_SET);

	SetDlgItemTextEx(IDC_BUTTON_VideoDetectStop, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_VideoDetectStart, IDS_START);
}

void CLS_VCAEVENT_VideoDetect::CleanText()
{
	m_chkDisplayState.SetCheck(0);
	m_edtCheckTime.Clear();
	m_chkNoise.SetCheck(0);
	m_chkClarity.SetCheck(0);
	m_chkBright.SetCheck(0);
	m_chkColor.SetCheck(0);
	m_chkFreeze.SetCheck(0);
	m_chkNosignal.SetCheck(0);
	m_chkChange.SetCheck(0);
	m_chkInterfere.SetCheck(0);
	m_chkPTZ_Lost.SetCheck(0);
	SetDlgItemText(IDC_EDIT_CheckTime, "");
	m_edtLevel.Clear();
	m_edtEnable.Clear();
}
void CLS_VCAEVENT_VideoDetect::OnBnClickedButtonVideodetectstop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_VideoDetect::OnBnClickedButtonVideodetectstart()
{
	int iStatus =1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
