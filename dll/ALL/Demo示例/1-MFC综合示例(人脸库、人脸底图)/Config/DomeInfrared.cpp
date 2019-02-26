// E:\SDK4.0\NVSSDK_V4.0\branches\M7.6\Demo\NetClientDemo\Config\CooperDome.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeInfrared.h"

#define CONTROL_MODE_TIME_OPEN	2  
#define ZOOM_MATCH_CLOSE		0
#define ZOOM_MATCH_OPEN			1

// CLSCooperDome dialog

IMPLEMENT_DYNAMIC(CLS_DomeInfrared, CDialog)

CLS_DomeInfrared::CLS_DomeInfrared(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeInfrared::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_DomeInfrared::~CLS_DomeInfrared()
{
}

void CLS_DomeInfrared::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CFG_DOME_PTZ_TYPE, m_cboDomePTZType);
	DDX_Control(pDX, IDC_COMBO_DOME_PTZ_WAITACT, m_cboWaitAct);
	DDX_Control(pDX, IDC_COMBO_DOME_PTZ_AUTOMATIC, m_cboAutiomatic);
	DDX_Control(pDX, IDC_CHECK_CFG_DOME_PTZ_ENABLE, m_chkDomePTZEnable);
	DDX_Control(pDX, IDC_CHECK_DOME_PTZ_MANUAL, m_chkManualOperation);
	DDX_Control(pDX, IDC_CHECK_DOME_PTZ_AUTOMATIC, m_chkAutomatic);
	DDX_Control(pDX, IDC_EDIT_DOME_PTZ_WAITACT, m_edtWaitAct);
	DDX_Control(pDX, IDC_COMBO_SPEED_LEVEL, m_cboSpeedLevel);
	DDX_Control(pDX, IDC_EDIT_DOME_PTZ_MANUAL, m_edtManualOperation);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_SENSITIVE_THRESHOLD, m_cboSensitiveThreshold);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_DELAY_TIME, m_cboDelayTime);
	DDX_Control(pDX, IDC_STC_CFG_COOPER_DOME_DELAY_TIME, m_stcDelayTime);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_CONTROL_MODE, m_cboControlMode);
	DDX_Control(pDX, IDC_BTN_CFG_COOPER_SET_CONTROL_TIME, m_btnSetControlTime);
	DDX_Control(pDX, IDC_DTP_CFG_COOPER_DOME_START_TIME, m_dtpStartTime);
	DDX_Control(pDX, IDC_DTP_CFG_COOPER_DOME_END_TIME, m_dtpEndTime);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_ZOOM_MATHC, m_cboZoomMatch);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT, m_cboInstantLight);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT, m_cboShortLight);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT2, m_cboInstantLight2);
	DDX_Control(pDX, IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT2, m_cboShortLight2);
}


BEGIN_MESSAGE_MAP(CLS_DomeInfrared, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_CFG_DOME_PTZ_TYPE, &CLS_DomeInfrared::OnCbnSelchangeComboCfgDomePtzType)
	ON_BN_CLICKED(IDC_BUTTON_DOME_PTZ_SET, &CLS_DomeInfrared::OnBnClickedButtonDomePtzSet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK_DOME_PTZ_MANUAL, &CLS_DomeInfrared::OnBnClickedCheckDomePtzManual)
	ON_BN_CLICKED(IDC_CHECK_DOME_PTZ_AUTOMATIC, &CLS_DomeInfrared::OnBnClickedCheckDomePtzAutomatic)
	ON_CBN_SELCHANGE(IDC_CBO_CFG_COOPER_DOME_SENSITIVE_THRESHOLD, &CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeSensitiveThreshold)
	ON_CBN_SELCHANGE(IDC_CBO_CFG_COOPER_DOME_DELAY_TIME, &CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeDelayTime)
	ON_BN_CLICKED(IDC_BTN_CFG_COOPER_SET_CONTROL_TIME, &CLS_DomeInfrared::OnBnClickedBtnCfgCooperSetControlTime)
	ON_BN_CLICKED(IDC_BTN_CFG_COOPER_SET_ZOOM_MATCH, &CLS_DomeInfrared::OnBnClickedBtnCfgCooperSetZoomMatch)
	ON_CBN_SELCHANGE(IDC_CBO_CFG_COOPER_DOME_CONTROL_MODE, &CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeControlMode)
	ON_CBN_SELCHANGE(IDC_CBO_CFG_COOPER_DOME_ZOOM_MATHC, &CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeZoomMathc)
END_MESSAGE_MAP()


// CLSCooperDome message handlers

BOOL CLS_DomeInfrared::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtWaitAct.SetLimitText(16);
	m_edtManualOperation.SetLimitText(16);

	GetDlgItem(IDC_STATIC_DOME_PTZ_VLEVEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_DOME_PTZ_INFRARED_MODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SPEED_LEVEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATI_WAIT_ACT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MANUAL_OPERATION)->EnableWindow(FALSE);

	UI_UpdateText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeInfrared::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	UI_CleanText();
	if (bShow)
	{
		UI_UpdateInfo();
	}
}

void CLS_DomeInfrared::OnChannelChanged(int _iLogonID, int _iChannelNo, int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}

	UI_UpdateInfo();
}

void CLS_DomeInfrared::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateText();
	UI_UpdateInfo();
}

void CLS_DomeInfrared::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_CHECK_CFG_DOME_PTZ_ENABLE, IDS_DOME_PTZ_ENABLE);
	SetDlgItemTextEx(IDC_CHECK_DOME_PTZ_MANUAL, IDS_DOME_PTZ_MODE_TYPE);
	SetDlgItemTextEx(IDC_CHECK_DOME_PTZ_AUTOMATIC, IDS_DOME_PTZ_MODE_Automatic);
	SetDlgItemTextEx(IDC_STATIC_DOME_PTZ_VLEVEL, IDS_DOME_PTZ_SPEEDLEVEL);
	SetDlgItemTextEx(IDC_STATIC_DOME_PTZ_WAITACT, IDS_DOME_PTZ_WAIT_ACT);
	SetDlgItemTextEx(IDC_STATIC_DOME_PTZ_INFRARED_MODE, IDS_DOME_PTZ_INFRARED_MODE);
	SetDlgItemTextEx(IDC_STATI_WAIT_ACT, IDS_DOME_PTZ_WAIT_SECOND);
	SetDlgItemTextEx(IDC_STATIC_MANUAL_OPERATION, IDS_DOME_PTZ_ACT_RANGE);
	SetDlgItemTextEx(IDC_BUTTON_DOME_PTZ_SET, IDS_VCA_EVENT_LEAVEDETECT_SET);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_SENSITIVE_SHRESHOLD, IDS_DOME_SENSITIVE_SHRESHOLD);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_DELAY_TIME, IDS_DOME_DELAY_TIME);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_CONTROL_MODE, IDS_CONTROL_MODE);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_START_TIME, IDS_PLAYBACK_DOWNLOAD_BEGINTIME);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_END_TIME, IDS_CONFIG_HOLIDAY_END_TIME);
	SetDlgItemTextEx(IDC_BTN_CFG_COOPER_SET_CONTROL_TIME, IDS_SET);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_ZOOM_MATCH, IDS_ZOOM_MATCH);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_DISTANT_LIGHT, IDS_DOME_DISTANT_LIGHT);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_SHORT_LIGHT, IDS_DOME_SHORT_LIGHT);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_DISTANT_LIGHT2, IDS_DOME_DISTANT_LIGHT2);
	SetDlgItemTextEx(IDC_STC_CFG_COOPER_DOME_SHORT_LIGHT2, IDS_DOME_SHORT_LIGHT2);
	SetDlgItemTextEx(IDC_BTN_CFG_COOPER_SET_ZOOM_MATCH, IDS_SET);
	
	const CString strDomePtzType[] = {GetTextEx(IDS_DOME_PTZ_PRESET_FREEZE_UP)
									, GetTextEx(IDS_DOME_PTZ_AUTO_FLIP)
									, GetTextEx(IDS_DOME_PTZ_PRESET_SPEED_LEVE)
									, GetTextEx(IDS_DOME_PTZ_MANUL_SEPPD_LEVEL)
									, GetTextEx(IDS_DOME_PTZ_WAIT_ACT)
									, GetTextEx(IDS_DOME_PTZ_INFRARED_MODE)};
	m_cboDomePTZType.ResetContent();
	for (int i=0; i<sizeof(strDomePtzType)/sizeof(CString); i++)
	{
		m_cboDomePTZType.InsertString(i, strDomePtzType[i]);
	}

	const CString strSpeedLevel[] = {GetTextEx(IDS_DOME_PTZ_SPEED_LEVEL)
									, GetTextEx(IDS_DOME_PTZ_SPEED_MIDDLE)
									, GetTextEx(IDS_DOME_PTZ_SPEED_HIGH)};
	m_cboSpeedLevel.ResetContent();
	for (int i=0; i<sizeof(strSpeedLevel)/sizeof(CString); i++)
	{
		m_cboSpeedLevel.InsertString(i, strSpeedLevel[i]);
	}

	const CString strWaitAct[] = {GetTextEx(IDS_DOME_PTZ_ACT_RESET)
									, GetTextEx(IDS_DOME_PTZ_ACT_SWEEP)
									, GetTextEx(IDS_DOME_PTZ_ACT_CRUISE)
	                                , GetTextEx(IDS_DOME_PTZ_ACT_PATTERN)};
	m_cboWaitAct.ResetContent();
	for (int i=0; i<sizeof(strWaitAct)/sizeof(CString); i++)
	{
		m_cboWaitAct.InsertString(i, strWaitAct[i]);
	}

	const CString strInfraRedMode[] = {GetTextEx(IDS_DOME_PTZ_ACT_LOWEST)
									, GetTextEx(IDS_DOME_PTZ_ACT_LOWER)
									, GetTextEx(IDS_DOME_PTZ_ACT_HIGHER)
									, GetTextEx(IDS_DOME_PTZ_ACT_NORMAL)
									, GetTextEx(IDS_DOME_PTZ_ACT_HIGHEST)};
	m_cboAutiomatic.ResetContent();
	for (int i=0; i<sizeof(strInfraRedMode)/sizeof(CString); i++)
	{
		m_cboAutiomatic.InsertString(i, strInfraRedMode[i]);
	}

	//感光阈值
	const CString strDomeSensitiveShreshold[] = {GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_HIGH_LOW)
		, GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_LOW)
		, GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_STANDARD)
		, GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_MIDDLE)
		, GetTextEx(IDS_DOME_SENSITIVE_SHRESHOLD_HIGH)};
	m_cboSensitiveThreshold.ResetContent();
	for (int i=0; i<sizeof(strDomeSensitiveShreshold)/sizeof(CString); i++)
	{
		m_cboSensitiveThreshold.InsertString(i, strDomeSensitiveShreshold[i]);
	}
	m_cboSensitiveThreshold.SetCurSel(0);

	//延时时间
	const CString strDomeDelayTime[] = {GetTextEx(IDS_DOME_DELAY_TIME_LOW)
		, GetTextEx(IDS_DOME_DELAY_TIME_MIDDLE)
		, GetTextEx(IDS_DOME_DELAY_TIME_HIGH)};
	m_cboDelayTime.ResetContent();
	for (int i=0; i<sizeof(strDomeDelayTime)/sizeof(CString); i++)
	{
		m_cboDelayTime.InsertString(i, strDomeDelayTime[i]);
	}
	m_cboDelayTime.SetCurSel(0);

	//控制方式
	const CString strDomeControlMode[] = {GetTextEx(IDS_DOME_AUTO)
		, GetTextEx(IDS_DOME_CAMERA_FOLLOW)
		, GetTextEx(IDS_DOME_TIME_OPENING)
		, GetTextEx(IDS_DOME_MANUAL_OPEN)
		, GetTextEx(IDS_DOME_MANUAL_CLOSE)};
	m_cboControlMode.ResetContent();
	for (int i=0; i<sizeof(strDomeControlMode)/sizeof(CString); i++)
	{
		m_cboControlMode.InsertString(i, strDomeControlMode[i]);
	}
	m_cboControlMode.SetCurSel(0);
	OnCbnSelchangeCboCfgCooperDomeControlMode();
	
	//变倍匹配
	const CString strDomeZoomMatch[] = {GetTextEx(IDS_CONFIG_CLOSE)
	, GetTextEx(IDS_CFG_CRUISE_START)};
	m_cboZoomMatch.ResetContent();
	for (int i=0; i<sizeof(strDomeZoomMatch)/sizeof(CString); i++)
	{
		m_cboZoomMatch.InsertString(i, strDomeZoomMatch[i]);
	}
	m_cboZoomMatch.SetCurSel(0);

	//远灯1
	const CString strDomeDistantLight[] = {"0","1","2","3","4","5","6","7","8","9","10"};
	m_cboInstantLight.ResetContent();
	for (int i=0; i<sizeof(strDomeDistantLight)/sizeof(CString); i++)
	{
		m_cboInstantLight.InsertString(i, strDomeDistantLight[i]);
	}
	m_cboInstantLight.SetCurSel(0);

	//近灯1
	const CString strDomeShortLight[] = {"0","1","2","3","4","5","6","7","8","9","10"};
	m_cboShortLight.ResetContent();
	for (int i=0; i<sizeof(strDomeShortLight)/sizeof(CString); i++)
	{
		m_cboShortLight.InsertString(i, strDomeShortLight[i]);
	}
	m_cboShortLight.SetCurSel(0);

	//远灯2
	const CString strDomeDistantLight2[] = {"0","1","2","3","4","5","6","7","8","9","10"};
	m_cboInstantLight2.ResetContent();
	for (int i=0; i<sizeof(strDomeDistantLight2)/sizeof(CString); i++)
	{
		m_cboInstantLight2.InsertString(i, strDomeDistantLight2[i]);
	}
	m_cboInstantLight2.SetCurSel(0);

	//近灯2
	const CString strDomeShortLight2[] = {"0","1","2","3","4","5","6","7","8","9","10"};
	m_cboShortLight2.ResetContent();
	for (int i=0; i<sizeof(strDomeShortLight2)/sizeof(CString); i++)
	{
		m_cboShortLight2.InsertString(i, strDomeShortLight2[i]);
	}
	m_cboShortLight2.SetCurSel(0);

}

void CLS_DomeInfrared::UI_CleanText()
{
	m_cboDomePTZType.SetCurSel(0);
	m_cboWaitAct.SetCurSel(0);
	m_cboAutiomatic.SetCurSel(0);
	m_cboSpeedLevel.SetCurSel(0);
	m_chkDomePTZEnable.SetCheck(0);
	m_chkManualOperation.SetCheck(0);
	m_chkAutomatic.SetCheck(0);
	m_edtWaitAct.Clear();
	SetDlgItemText(IDC_EDIT_DOME_PTZ_WAITACT, "");
	m_edtManualOperation.Clear();
	SetDlgItemText(IDC_EDIT_DOME_PTZ_MANUAL, "");
}

void CLS_DomeInfrared::OnCbnSelchangeComboCfgDomePtzType()
{
	// TODO: Add your control notification handler code here
	int iDomePtzType = m_cboDomePTZType.GetCurSel();
	if ((PRESET_FREEZE_UP_SEL == iDomePtzType) || (AUTO_FLIP_SEL == iDomePtzType))
	{
		GetDlgItem(IDC_STATIC_DOME_PTZ_VLEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DOME_PTZ_INFRARED_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SPEED_LEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATI_WAIT_ACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MANUAL_OPERATION)->EnableWindow(FALSE);
	}
	else if ((PRESET_SPEED_LEVE_SEL == iDomePtzType) || (MANUL_SEPPD_LEVEL_SEL == iDomePtzType))
	{
		GetDlgItem(IDC_STATIC_DOME_PTZ_VLEVEL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SPEED_LEVEL)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DOME_PTZ_INFRARED_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATI_WAIT_ACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MANUAL_OPERATION)->EnableWindow(FALSE);
	}
	else if (WAIT_ACT_SEL == iDomePtzType)
	{
		GetDlgItem(IDC_STATIC_DOME_PTZ_WAITACT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_WAITACT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_WAITACT)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATI_WAIT_ACT)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DOME_PTZ_VLEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DOME_PTZ_INFRARED_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SPEED_LEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MANUAL_OPERATION)->EnableWindow(FALSE);
	}
	else if (INFRARED_MODE_SEL == iDomePtzType)
	{
		GetDlgItem(IDC_STATIC_DOME_PTZ_INFRARED_MODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_MANUAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_MANUAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DOME_PTZ_AUTOMATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_AUTOMATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_MANUAL_OPERATION)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DOME_PTZ_VLEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_WAITACT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SPEED_LEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATI_WAIT_ACT)->EnableWindow(FALSE);	
	}
	else
	{
		//TODO:......
	}
	UI_UpdateInfo();
}

void CLS_DomeInfrared::OnBnClickedButtonDomePtzSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNo);
		return;
	}

	DOMEPTZ DomePtz = {0};
	DomePtz.iSize = sizeof(DOMEPTZ);
	DomePtz.iType = m_cboDomePTZType.GetCurSel() + 1;
	DomePtz.iAutoEnable = m_chkDomePTZEnable.GetCheck();

	int iRet = -1;
	if ((DOME_PTZ_TYPE_PRESET_FREEZE_UP == DomePtz.iType) || (DOME_PTZ_TYPE_AUTO_FLIP == DomePtz.iType))
	{
		iRet = NetClient_SetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	}
	else if ((DOME_PTZ_TYPE_PRESET_SPEED_LEVE == DomePtz.iType) || (DOME_PTZ_TYPE_MANUL_SEPPD_LEVEL == DomePtz.iType))
	{
		DomePtz.iParam1 = m_cboSpeedLevel.GetCurSel();
		iRet = NetClient_SetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	}
	else if (DOME_PTZ_TYPE_WAIT_ACT == DomePtz.iType)
	{
		DomePtz.iParam1 = GetDlgItemInt(IDC_EDIT_DOME_PTZ_WAITACT);
		DomePtz.iParam2 = m_cboWaitAct.GetCurSel();
		iRet = NetClient_SetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	}
	else if (DOME_PTZ_TYPE_INFRARED_MODE == DomePtz.iType)
	{
		DomePtz.iParam1 = m_chkAutomatic.GetCheck();
		if (BST_CHECKED == m_chkAutomatic.GetCheck())
		{
			DomePtz.iParam2 = m_cboAutiomatic.GetCurSel();
		} 
		else
		{
			DomePtz.iParam2 = GetDlgItemInt(IDC_EDIT_DOME_PTZ_MANUAL);
		}

		iRet = NetClient_SetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	}
	else
	{
		//TODO:......
	}

	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetDomePTZ(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetDomePTZ(%d)", m_iLogonID);
	}
}

void CLS_DomeInfrared::UI_UpdateInfo()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNo);
		return;
	}

	int iRet = -1;
	DOMEPTZ DomePtz = {0};
	DomePtz.iSize = sizeof(DOMEPTZ);

	DomePtz.iType = DOME_PTZ_TYPE_PRESET_FREEZE_UP;
	iRet = NetClient_GetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		m_chkDomePTZEnable.SetCheck(DomePtz.iAutoEnable);
		iRet = -1;
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetDomePTZ(%d)", m_iLogonID);
	}

	DomePtz.iType = DOME_PTZ_TYPE_AUTO_FLIP;
	iRet = NetClient_GetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		m_chkDomePTZEnable.SetCheck(DomePtz.iAutoEnable);
		iRet = -1;
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetDomePTZ(%d)", m_iLogonID);
	}

	DomePtz.iType = DOME_PTZ_TYPE_PRESET_SPEED_LEVE;
	iRet = NetClient_GetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		m_chkDomePTZEnable.SetCheck(DomePtz.iAutoEnable);
		m_cboSpeedLevel.SetCurSel(DomePtz.iParam1);
		iRet = -1;
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetDomePTZ(%d)", m_iLogonID);
	}

	DomePtz.iType = DOME_PTZ_TYPE_MANUL_SEPPD_LEVEL;
	iRet = NetClient_GetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		m_chkDomePTZEnable.SetCheck(DomePtz.iAutoEnable);
		m_cboSpeedLevel.SetCurSel(DomePtz.iParam1);
		iRet = -1;
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetDomePTZ(%d)", m_iLogonID);
	}

	DomePtz.iType = DOME_PTZ_TYPE_WAIT_ACT;
	iRet = NetClient_GetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		m_chkDomePTZEnable.SetCheck(DomePtz.iAutoEnable);
		SetDlgItemInt(IDC_EDIT_DOME_PTZ_WAITACT, DomePtz.iParam1);
		m_cboWaitAct.SetCurSel(DomePtz.iParam2);
		iRet = -1;
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetDomePTZ(%d)", m_iLogonID);
	}

	DomePtz.iType = DOME_PTZ_TYPE_INFRARED_MODE;
	iRet = NetClient_GetDomePTZ(m_iLogonID, m_iChannelNo, &DomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		m_chkDomePTZEnable.SetCheck(DomePtz.iAutoEnable);
		if (1 == DomePtz.iParam1)
		{
			m_chkManualOperation.SetCheck(BST_CHECKED);
			SetDlgItemInt(IDC_EDIT_DOME_PTZ_MANUAL, DomePtz.iParam2);
		} 
		else
		{
			m_chkAutomatic.SetCheck(BST_CHECKED);
			m_cboAutiomatic.SetCurSel(DomePtz.iParam2);
		}
		iRet = -1;
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetDomePTZ(%d)", m_iLogonID);
	}

	//获取感光阈值当前参数
	int iBytesReturned = 0;
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SENSITIVE_THRESHOLD;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam, sizeof(TDomeParam), &iBytesReturned);
	if (0 == iRet)
	{
		int iIndex = tParam.iParam1;
		m_cboSensitiveThreshold.SetCurSel(iIndex);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_SENSITIVE_THRESHOLD] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_SENSITIVE_THRESHOLD] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}

	//获取延时时间当前参数
	int iBytesReturnedDelayTime = 0;
	TDomeParam tParamDelayTime = {0};
	tParamDelayTime.iType = DOME_PARA_DELAY_TIME;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParamDelayTime, sizeof(TDomeParam), &iBytesReturnedDelayTime);
	if (0 == iRet)
	{
		int iIndex = tParamDelayTime.iParam1;
		m_cboDelayTime.SetCurSel(iIndex);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_DELAY_TIME] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_DELAY_TIME] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}

	//获取当前控制方式
	iBytesReturned = 0;
	memset(&tParam, 0, sizeof(tParam));
	tParam.iType = DOME_PARA_CONTROL_MODE;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam, sizeof(TDomeParam), &iBytesReturned);
	if (0 == iRet)
	{
		int iIndex = tParam.iParam1;
		m_cboControlMode.SetCurSel(iIndex);
		if (CONTROL_MODE_TIME_OPEN == iIndex)
		{
			int iTime = tParam.iParam2;

			int iStartHour = iTime>>24 & 0xFF;
			int iStartMinute = iTime>>16 & 0xFF;
			int iEndHour = iTime>>8 & 0xFF;
			int iEndMinute = iTime & 0xFF;

			SYSTEMTIME stStartTime;        //定义一个系统时间类型的变量
			stStartTime.wHour = iStartHour;
			stStartTime.wMinute = iStartMinute;
			CTime ctStartTime(stStartTime);        //定义CTime对象并赋值给它
		
			SYSTEMTIME stEndTime;
			stEndTime.wHour = iEndHour;
			stEndTime.wMinute = iEndMinute;
			CTime ctEndTime(stEndTime); 

			m_dtpStartTime.SetTime(&ctStartTime);
			UpdateData(FALSE);
			m_dtpEndTime.SetTime(&ctEndTime);
			UpdateData(FALSE);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_CONTROL_MODE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_CONTROL_MODE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}

	//获取当前变倍匹配
	iBytesReturned = 0;
	memset(&tParam, 0, sizeof(tParam));
	tParam.iType = DOME_PARA_ZOOM_MATCH;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam, sizeof(TDomeParam), &iBytesReturned);
	if (0 == iRet)
	{
		int iIndex = tParam.iParam1;
		m_cboZoomMatch.SetCurSel(iIndex);
		if (ZOOM_MATCH_CLOSE == iIndex)
		{
			int iPara = tParam.iParam2;

			int iInstantLight = iPara>>24 & 0xFF;
			int iInstantLight2 = iPara>>16 & 0xFF;
			int iShortLight = iPara>>8 & 0xFF;
			int iShortLight2 = iPara & 0xFF;

			m_cboInstantLight.SetCurSel(iInstantLight);
			m_cboInstantLight2.SetCurSel(iInstantLight2);
			m_cboShortLight.SetCurSel(iShortLight);
			m_cboShortLight2.SetCurSel(iShortLight2);

			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT)->EnableWindow(TRUE);
			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT2)->EnableWindow(TRUE);
			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT)->EnableWindow(TRUE);
			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT2)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT)->EnableWindow(FALSE);
			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT2)->EnableWindow(FALSE);
			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT)->EnableWindow(FALSE);
			GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT2)->EnableWindow(FALSE);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_ZOOM_MATCH] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_ZOOM_MATCH] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}

void CLS_DomeInfrared::OnBnClickedCheckDomePtzManual()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chkManualOperation.GetCheck())
	{
		GetDlgItem(IDC_CHECK_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_AUTOMATIC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_DOME_PTZ_AUTOMATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DOME_PTZ_AUTOMATIC)->EnableWindow(TRUE);
	}
}

void CLS_DomeInfrared::OnBnClickedCheckDomePtzAutomatic()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chkAutomatic.GetCheck())
	{
		GetDlgItem(IDC_CHECK_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MANUAL_OPERATION)->EnableWindow(FALSE);
	} 
	else
	{
		GetDlgItem(IDC_CHECK_DOME_PTZ_MANUAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOME_PTZ_MANUAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_MANUAL_OPERATION)->EnableWindow(TRUE);
	}
}

//设置感光阈值
void CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeSensitiveThreshold()
{
	int iIndex = m_cboSensitiveThreshold.GetCurSel();
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SENSITIVE_THRESHOLD;
	tParam.iParam1 = iIndex;
	if (iIndex >= 0)
	{
		int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam, sizeof(TDomeParam));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_SENSITIVE_THRESHOLD] (%d, %d)", m_iLogonID, m_iChannelNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_SENSITIVE_THRESHOLD] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
		}
	}
}

//设置延时时间
void CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeDelayTime()
{
	int iIndex = m_cboDelayTime.GetCurSel();
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_DELAY_TIME;
	tParam.iParam1 = iIndex;
	if (iIndex >= 0)
	{
		int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam, sizeof(TDomeParam));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_DELAY_TIME] (%d, %d)", m_iLogonID, m_iChannelNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_DELAY_TIME] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
		}
	}
}

//控制方式
void CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeControlMode()
{
	int iIndex = m_cboControlMode.GetCurSel();
	if (CONTROL_MODE_TIME_OPEN == iIndex)
	{
		GetDlgItem(IDC_STC_CFG_COOPER_DOME_START_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_DTP_CFG_COOPER_DOME_START_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STC_CFG_COOPER_DOME_END_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_DTP_CFG_COOPER_DOME_END_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_STC_CFG_COOPER_DOME_START_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DTP_CFG_COOPER_DOME_START_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_STC_CFG_COOPER_DOME_END_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DTP_CFG_COOPER_DOME_END_TIME)->EnableWindow(FALSE);
	}
}

//设置控制方式
void CLS_DomeInfrared::OnBnClickedBtnCfgCooperSetControlTime()
{
	int iRet = -1;
	int iIndex = m_cboControlMode.GetCurSel();
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_CONTROL_MODE;
	tParam.iParam1 = iIndex;
	if (CONTROL_MODE_TIME_OPEN == iIndex)
	{
		CTime ctStartTime = 0;
		CTime ctEndTime = 0;

		m_dtpStartTime.GetTime(ctStartTime);
		int iStartHour = ctStartTime.GetHour();
		int iStartMinute= ctStartTime.GetMinute();

		m_dtpEndTime.GetTime(ctEndTime);
		int iEndHour = ctEndTime.GetHour();
		int iEndMinute= ctEndTime.GetMinute();

		tParam.iParam2 = (iStartHour<<24)|(iStartMinute<<16)|(iEndHour<<8)|iEndMinute;
	}

	iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam, sizeof(TDomeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_CONTROL_MODE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_CONTROL_MODE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}		
}

//设置变倍匹配
void CLS_DomeInfrared::OnBnClickedBtnCfgCooperSetZoomMatch()
{
	int iRet = -1;
	int iIndex = m_cboZoomMatch.GetCurSel();
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_ZOOM_MATCH;
	tParam.iParam1 = iIndex;
	//if (ZOOM_MATCH_CLOSE == iIndex)
	{
		int iDistantLightDegree = m_cboInstantLight.GetCurSel();
		int iShortLightDegree = m_cboShortLight.GetCurSel();
		int iDistantLightDegree2 = m_cboInstantLight2.GetCurSel();
		int iShortLightDegree2 = m_cboShortLight2.GetCurSel();
		tParam.iParam2 = (iDistantLightDegree<<24)|(iDistantLightDegree2<<16)|(iShortLightDegree<<8)|iShortLightDegree2;
	}

	iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam, sizeof(TDomeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_ZOOM_MATCH] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_ZOOM_MATCH] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}

void CLS_DomeInfrared::OnCbnSelchangeCboCfgCooperDomeZoomMathc()
{
	int iIndex = m_cboZoomMatch.GetCurSel();
	if (ZOOM_MATCH_CLOSE == iIndex)
	{
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT2)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_SHORT_LIGHT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CBO_CFG_COOPER_DOME_INSTANT_LIGHT2)->EnableWindow(FALSE);
	}
}
