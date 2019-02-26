// AdvChannelParamPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "AdvChannelParamPage.h"

#define BRIGHT_VALUE		0
#define	LEN_3				3
#define DAY_LIGNT_MAX		255
#define NIGHT_LIGHT_MAX		255
#define DELAY_MAX			120
// CLS_AdvChannelParamPage dialog

IMPLEMENT_DYNAMIC(CLS_AdvChannelParamPage, CDialog)

CLS_AdvChannelParamPage::CLS_AdvChannelParamPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AdvChannelParamPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_AdvChannelParamPage::~CLS_AdvChannelParamPage()
{
}

void CLS_AdvChannelParamPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_PRERECORD_ENABLE, m_ComboBoxPreRecord);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_COLOR_TO_GRAY, m_ComboBoxColorToGray);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_TYPE, m_ComboBoxChannelType);
	DDX_Control(pDX, IDC_COMBO4, m_ComboBoxChannelNo);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_TYPE_NO, m_ComboBoxTypeNo);
	DDX_Control(pDX, IDC_EDIT_BRIGHTVALUE, m_edtBrightValue);
	DDX_Control(pDX, IDC_DTP_GRAY2COLOR_TIME, m_dtpGray2ColorTime);
	DDX_Control(pDX, IDC_DTP_COLOR2GRAY_TIME, m_dtpColor2GrayTime);
	DDX_Control(pDX, IDC_EDIT_CHANNEL_DAYRANGE, m_edtDayLight);
	DDX_Control(pDX, IDC_EDIT_CHANNEL_NIGHTRANGE, m_edtNightLight);
	DDX_Control(pDX, IDC_EDIT_COLORDELAY, m_edtColor2GrayDelay);
	DDX_Control(pDX, IDC_EDIT_GRAYDELAY, m_edtGray2ColorDelay);
}


BEGIN_MESSAGE_MAP(CLS_AdvChannelParamPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_PRERECORD_ENABLE, &CLS_AdvChannelParamPage::OnBnClickedButtonChannelPrerecordEnable)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_COLOR, &CLS_AdvChannelParamPage::OnBnClickedButtonChannelColor)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_PWM, &CLS_AdvChannelParamPage::OnBnClickedButtonChannelPwm)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_CUSTOM, &CLS_AdvChannelParamPage::OnBnClickedButtonChannelCustom)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_CUSTOM_RECORD_TYPE, &CLS_AdvChannelParamPage::OnBnClickedButtonChannelCustomRecordType)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_TYPE, &CLS_AdvChannelParamPage::OnCbnSelchangeComboChannelType)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CLS_AdvChannelParamPage::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_TYPE_NO, &CLS_AdvChannelParamPage::OnCbnSelchangeComboChannelTypeNo)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_COLOR_TO_GRAY, &CLS_AdvChannelParamPage::OnCbnSelchangeComboChannelColorToGray)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_CHANNEL_DAYRANGE, &CLS_AdvChannelParamPage::OnEnChangeEditChannelDayrange)
	ON_EN_CHANGE(IDC_EDIT_CHANNEL_NIGHTRANGE, &CLS_AdvChannelParamPage::OnEnChangeEditChannelNightrange)
	ON_EN_CHANGE(IDC_EDIT_COLORDELAY, &CLS_AdvChannelParamPage::OnEnChangeEditColordelay)
	ON_EN_CHANGE(IDC_EDIT_GRAYDELAY, &CLS_AdvChannelParamPage::OnEnChangeEditGraydelay)
END_MESSAGE_MAP()


// CLS_AdvChannelParamPage message handlers

BOOL CLS_AdvChannelParamPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_dtpColor2GrayTime.SetFormat(_T("HH:mm"));
	m_dtpGray2ColorTime.SetFormat(_T("HH:mm"));
	CTime timeNow = CTime::GetCurrentTime();
	m_dtpColor2GrayTime.SetTime(&timeNow);
	m_dtpGray2ColorTime.SetTime(&timeNow);

	m_edtDayLight.SetLimitText(LEN_3);
	m_edtNightLight.SetLimitText(LEN_3);
	m_edtGray2ColorDelay.SetLimitText(LEN_3);
	m_edtColor2GrayDelay.SetLimitText(LEN_3);

	UI_UpdateComBoxLaguage();
	UI_UpdateText();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLS_AdvChannelParamPage::DestroyWindow()
{
	return CLS_BasePage::DestroyWindow();
}

BOOL CLS_AdvChannelParamPage::CheckChannel()
{
	if (m_iLogonID < 0|| m_iChannelNo < 0)
	{
		return FALSE;
	}
	int iChannelNum = 0;
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);

	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetChannelNum(%s, %d)", Device->cIP, m_iLogonID);
		}
		return FALSE;
	}
	if (m_iChannelNo >= iChannelNum)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "Channel No too large(%s, %d, %d)", Device->cIP, m_iChannelNo, iChannelNum);
		}
		return FALSE;
	}

	return TRUE;
}

void CLS_AdvChannelParamPage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser )
{

}

void CLS_AdvChannelParamPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = 	_iChannelNo;
	}
	m_iLogonID = _iLogonID;
	UI_UpdateParam();

	int iStatus = -1;
	int iRetBytes = -1;
	NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_CHN_CONNECT_STATE, m_iChannelNo, (void*)&iStatus, sizeof(iStatus), &iRetBytes);
}


void CLS_AdvChannelParamPage::OnBnClickedButtonChannelPrerecordEnable()
{
	if (!CheckChannel())
	{
		return;
	}
	int iEnable = m_ComboBoxPreRecord.GetCurSel();
	int iRet = NetClient_SetPreRecEnable(m_iLogonID, m_iChannelNo, iEnable);
	if (iRet < 0)
	{                                                                             
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetPreRecEnable(%s, %d)", Device->cIP, m_iLogonID);
		}
		return;
	}
}


void CLS_AdvChannelParamPage::OnBnClickedButtonChannelColor()
{
	if (!CheckChannel())
	{
		return;
	}

	TColor2GrayParam tColor2GrayParam = {0};
	tColor2GrayParam.m_isize = sizeof(TColor2GrayParam);
	tColor2GrayParam.m_iDayRange = GetDlgItemInt(IDC_EDIT_CHANNEL_DAYRANGE);
	tColor2GrayParam.m_iNightRange = GetDlgItemInt(IDC_EDIT_CHANNEL_NIGHTRANGE);
	if (tColor2GrayParam.m_iDayRange <= tColor2GrayParam.m_iNightRange)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_AdvChannelParamPage::DayRange Must Greater Than NightRange!(%d,%d)", m_iLogonID, m_iChannelNo);
		return;
	}

	tColor2GrayParam.m_iColor2Gray = m_ComboBoxColorToGray.GetCurSel();
	tColor2GrayParam.m_iColorDelay = GetDlgItemInt(IDC_EDIT_COLORDELAY);
	tColor2GrayParam.m_iGrayDelay = GetDlgItemInt(IDC_EDIT_GRAYDELAY);

	CTime ctimeGray2Color;
	m_dtpGray2ColorTime.GetTime(ctimeGray2Color);
	int iGray2Color_hour = ctimeGray2Color.GetHour();
	int iGray2Color_minute = ctimeGray2Color.GetMinute();
	CTime ctimeColor2Gray;
	m_dtpColor2GrayTime.GetTime(ctimeColor2Gray);
	int iColor2Gray_hour = ctimeColor2Gray.GetHour();
	int iColor2Gray_minute = ctimeColor2Gray.GetMinute();

	tColor2GrayParam.m_iTimeRange |= (iGray2Color_hour << 24);//天亮小时
	tColor2GrayParam.m_iTimeRange |= (iGray2Color_minute << 16);//天亮分钟
	tColor2GrayParam.m_iTimeRange |= (iColor2Gray_hour << 8);//天黑小时
	tColor2GrayParam.m_iTimeRange |= iColor2Gray_minute;//天黑分钟

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLINET_COLOR2GRAY, m_iChannelNo, &tColor2GrayParam, sizeof(tColor2GrayParam));
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice((m_iLogonID));
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
}

void CLS_AdvChannelParamPage::OnBnClickedButtonChannelPwm()
{
	if (!CheckChannel())
	{
		return;
	}
	int iPWMValue = GetDlgItemInt(IDC_EDIT_CHANNEL_COLOR_PWM);
	int iRet = NetClient_SetPWMValue(m_iLogonID,m_iChannelNo,iPWMValue );
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetPWMValue(%s, %d)", Device->cIP, m_iLogonID);
		}
		return;
	}
}

void CLS_AdvChannelParamPage::OnBnClickedButtonChannelCustom()
{
	if (!CheckChannel())
	{
		return;
	}
	int iChannelType = m_ComboBoxChannelType.GetCurSel();
	int iChannelNo = m_ComboBoxChannelNo.GetCurSel();
	CString szName ;
	GetDlgItemText(IDC_EDIT_CHANNEL_NAME, szName);
	int iRet = NetClient_SetCustomChannelName(m_iLogonID, iChannelNo,iChannelType, szName.GetBuffer() );
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetCustomChannelName(%s, %d)", Device->cIP, m_iLogonID);
		}
		return;
	}
}

void CLS_AdvChannelParamPage::OnBnClickedButtonChannelCustomRecordType()
{
	if (!CheckChannel())
	{
		return;
	}
	int iTypeNo = m_ComboBoxTypeNo.GetCurSel();
	CString szName;
	GetDlgItemText(IDC_EDIT_CHANNEL_RECORD_TYPE_NAME, szName);
	int iRet = NetClient_SetCustomRecType(m_iLogonID, iTypeNo, szName.GetBuffer() );
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetCustomRecType(%s, %d)", Device->cIP, m_iLogonID);
		}
		return;
	}
}	

void CLS_AdvChannelParamPage::UI_UpdateParam()
{
	if (!CheckChannel())
	{
		return;
	}
	int iPreRecEnable = 0;
	int iRet = NetClient_GetPreRecEnable(m_iLogonID, m_iChannelNo, &iPreRecEnable);
	if (iPreRecEnable < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetPreRecEnable(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
	else
	{
		m_ComboBoxPreRecord.SetCurSel(iPreRecEnable);
	}

	int iReturnedValue = 0;
	TColor2GrayParam tTempColor2GrayParam = {0};
	tTempColor2GrayParam.m_isize = sizeof(TColor2GrayParam);
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLINET_COLOR2GRAY, m_iChannelNo, &tTempColor2GrayParam, sizeof(tTempColor2GrayParam), &iReturnedValue);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig(%s, %d)", Device->cIP, m_iLogonID);
		}
	} 
	else
	{
		CString cstrDayRange;
		CString cstrNightRange;
		cstrDayRange.Format("%d", tTempColor2GrayParam.m_iDayRange);
		cstrNightRange.Format("%d", tTempColor2GrayParam.m_iNightRange);
		SetDlgItemText(IDC_EDIT_CHANNEL_DAYRANGE, cstrDayRange);
		SetDlgItemText(IDC_EDIT_CHANNEL_NIGHTRANGE, cstrNightRange);

		m_ComboBoxColorToGray.SetCurSel(tTempColor2GrayParam.m_iColor2Gray);
		OnCbnSelchangeComboChannelColorToGray();

		SetDlgItemInt(IDC_EDIT_COLORDELAY, tTempColor2GrayParam.m_iColorDelay);
		SetDlgItemInt(IDC_EDIT_GRAYDELAY, tTempColor2GrayParam.m_iGrayDelay);

		int iGray2Color_hour = (tTempColor2GrayParam.m_iTimeRange >> 24) & 0x00000FF;//天亮小时
		int iGray2Color_minute = (tTempColor2GrayParam.m_iTimeRange >> 16) & 0x00000FF;//天亮分钟
		int iColor2Gray_hour = (tTempColor2GrayParam.m_iTimeRange >> 8) & 0x00000FF;//天黑小时
		int iColor2Gray_minute = tTempColor2GrayParam.m_iTimeRange & 0x00000FF;//天黑分钟

		CTime timeNow = CTime::GetCurrentTime();
		CTime timetemp1(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iColor2Gray_hour, iColor2Gray_minute, 0);
		m_dtpColor2GrayTime.SetTime(&timetemp1);
		CTime timetemp2(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iGray2Color_hour, iGray2Color_minute, 0);
		m_dtpGray2ColorTime.SetTime(&timetemp2);
	}

	int iPWMValue = 0;
	iRet = NetClient_GetPWMValue(m_iLogonID, m_iChannelNo, &iPWMValue);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetColorParam(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
	else
	{	
		CString szPWM;
		szPWM.Format("%d", iPWMValue);
		SetDlgItemText(IDC_EDIT_CHANNEL_COLOR_PWM, szPWM);
	}
	
	m_ComboBoxChannelType.SetCurSel(0);
	UI_UpdateCustomChannel();
	UI_UpateCustomRecName();

	NetClient_CheckDeviceState(m_iLogonID,m_iChannelNo,0);

	SetTimer(BRIGHT_VALUE, 1000, NULL);
}

void CLS_AdvChannelParamPage::UI_UpdateCustomChannel()
{
	int iVideoChannelNum = 0, iAlarmInPortNum = 0, iAlarmOutPortNum = 0, iChannelNum = 0;
	NetClient_GetAlarmPortNum(m_iLogonID,&iAlarmInPortNum,&iAlarmOutPortNum);
	NetClient_GetChannelNum(m_iLogonID, &iVideoChannelNum);
	m_ComboBoxChannelNo.ResetContent();
	int iChannelType = m_ComboBoxChannelType.GetCurSel();
	if (VIDEO_CHANNEL == iChannelType)
	{
		iChannelNum = iVideoChannelNum;
	}
	else if (ALARM_INPUT_CHANNEL == iChannelType)
	{
		iChannelNum = iAlarmInPortNum;
	}
	else
	{
		iChannelNum = iAlarmOutPortNum;
	}

	if (iChannelNum <= 0)
	{
		m_ComboBoxChannelNo.AddString("0");
	}
	else
	{
		for (int i = 0; i < iChannelNum; i++)
		{
			CString szChannelNo;
			szChannelNo.Format("%d", i);
			m_ComboBoxChannelNo.AddString(szChannelNo);
		}
	}
	m_ComboBoxChannelNo.SetCurSel(0);
	UI_UpdateChannelName();
}
void CLS_AdvChannelParamPage::OnCbnSelchangeComboChannelType()
{
	if (!CheckChannel())
	{
		return;
	}
	UI_UpdateCustomChannel();
}

void CLS_AdvChannelParamPage::OnCbnSelchangeCombo4()
{
	if (!CheckChannel())
	{
		return;
	}
	UI_UpdateChannelName();
}

void CLS_AdvChannelParamPage::OnCbnSelchangeComboChannelTypeNo()
{
	if (!CheckChannel())
	{
		return;
	}
	UI_UpateCustomRecName();
}

void CLS_AdvChannelParamPage::UI_UpateCustomRecName()
{
	int iTypeNo = m_ComboBoxTypeNo.GetCurSel();
	char cCustomRecType[32]={0};
	int iRet = NetClient_GetCustomRecType(m_iLogonID, iTypeNo,cCustomRecType);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetCustomRecType(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
	else
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_RECORD_TYPE_NAME, cCustomRecType);
	}
}

void CLS_AdvChannelParamPage::UI_UpdateChannelName()
{
	char cChannelTypeName[64]={0};  
	int iChannelNo = m_ComboBoxChannelNo.GetCurSel();
	int iChannelType = m_ComboBoxChannelType.GetCurSel();
	int iRet = NetClient_GetCustomChannelName(m_iLogonID,iChannelNo,iChannelType,cChannelTypeName);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetCustomChannelName(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
	else
	{
		SetDlgItemText(IDC_EDIT_CHANNEL_NAME, cChannelTypeName);
	}
}

void CLS_AdvChannelParamPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateComBoxLaguage();
	UI_UpdateText();
	UI_UpdateParam();
}

void CLS_AdvChannelParamPage::UI_UpdateComBoxLaguage()
{
	m_ComboBoxPreRecord.ResetContent();
	m_ComboBoxColorToGray.ResetContent();
	m_ComboBoxChannelType.ResetContent();
	m_ComboBoxPreRecord.AddString(GetTextEx(IDS_ADV_CHANNEL_DISABLE));
	m_ComboBoxPreRecord.AddString(GetTextEx(IDS_ADV_CHANNEL_ENABLE));
	m_ComboBoxPreRecord.SetCurSel(0);
	m_ComboBoxColorToGray.AddString(GetTextEx(IDS_CONFIG_INNER_SYN));
	m_ComboBoxColorToGray.AddString(GetTextEx(IDS_CONFIG_BLACK_WHITE));
	m_ComboBoxColorToGray.AddString(GetTextEx(IDS_CONFIG_COLOR));
	m_ComboBoxColorToGray.AddString(GetTextEx(IDS_CONFIG_OUT_SYN));
	m_ComboBoxColorToGray.AddString(GetTextEx(IDS_CONFIG_ALARM_SYN));
	m_ComboBoxColorToGray.AddString(GetTextEx(IDS_CONFIG_SETTIME));
	m_ComboBoxColorToGray.SetCurSel(0);
	m_ComboBoxChannelType.AddString(GetTextEx(IDS_ADV_CHANNEL_TYPE_VIDEO));
	m_ComboBoxChannelType.AddString(GetTextEx(IDS_ADV_CHANNEL_TYPE_ALARM_INPUT));
	m_ComboBoxChannelType.AddString(GetTextEx(IDS_ADV_CHANNEL_TYPE_ALARM_OUTPUT));
	m_ComboBoxChannelType.SetCurSel(0);
	for (int i = 0; i< 32; i++)
	{
		CString szTypeNo;
		szTypeNo.Format("%d", i+32);
		m_ComboBoxTypeNo.AddString(szTypeNo);
	}
	m_ComboBoxTypeNo.SetCurSel(0);		
}

void CLS_AdvChannelParamPage::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_STATIC1_CHANNEL_PRERECORD_ENABLE, IDS_ADV_CHANNEL_PRRECORD);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_PRERECORD_ENABLE, IDS_ADV_CHANNEL_PRERECORD_ENABLE);
	SetDlgItemTextEx(IDC_BUTTON_CHANNEL_PRERECORD_ENABLE, IDS_ADV_CHANNEL_SET);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_COLOR, IDS_ADV_CHANNEL_COLOR_PARAM);
	SetDlgItemTextEx(IDC_STATIC1_CHANNEL_PWM, IDS_ADV_PWM_SET);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_PWM, IDS_ADV_PWM_VALUE);
	SetDlgItemTextEx(IDC_STATICON_CHANNEL_CUSTOM, IDS_ADV_CUSTOM_CHANNEL_NAME);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_TYPE, IDS_ADV_CHANNEL_TYPE);
	SetDlgItemTextEx(IDC_STATIC_CHANNE_NO, IDS_ADV_CHANNELNO);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_NAME, IDS_ADV_CHANNEL_NAME);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_CUSTOM_RECORD_TYPE, IDS_ADV_CUSTOM_RECORD_NAME);
	SetDlgItemTextEx(IDC_STATICO_CHANNEL_TYPE_NO, IDS_ADV_TYPE_NO);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_RECORD_TYPE_NAME, IDS_ADV_TYPE_NAME);
	SetDlgItemTextEx(IDC_BUTTON_CHANNEL_COLOR, IDS_ADV_CHANNEL_SET);
	SetDlgItemTextEx(IDC_BUTTON_CHANNEL_PWM, IDS_ADV_CHANNEL_SET);
	SetDlgItemTextEx(IDC_BUTTON_CHANNEL_CUSTOM, IDS_ADV_CHANNEL_SET);
	SetDlgItemTextEx(IDC_BUTTON_CHANNEL_CUSTOM_RECORD_TYPE, IDS_ADV_CHANNEL_SET);
	SetDlgItemTextEx(IDC_STATIC_BRIGHT, IDS_ADV_CHANNEL_SET_BRIGHT);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGE, IDS_ADV_CHANNEL_SETTIMERANGE); 
	SetDlgItemTextEx(IDC_BUTTON_CHANNEL_COLOR, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_COLOR_TO_GRAY, IDS_DOME_COLOR2GRAY_TYPE);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_DAYTIME, IDS_DOME_DAY_LIGHT);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_NIGHT, IDS_DOME_NIGHT_LIGHT);
	SetDlgItemTextEx(IDC_STATIC_GRAYDELAY, IDS_DOME_GRAY2COLOR_DELAY);
	SetDlgItemTextEx(IDC_STATIC_COLORDELAY, IDS_DOME_COLOR2GRAY_DELAY);
	SetDlgItemTextEx(IDC_STC_GRAY2COLOR_TIME, IDS_DOME_GRAY2COLOR_TIME);
	SetDlgItemTextEx(IDC_STC_COLOR2GRAY_TIME, IDS_DOME_COLOR2GRAY_TIME);
}

void CLS_AdvChannelParamPage::OnCbnSelchangeComboChannelColorToGray()
{
	int iChoose = m_ComboBoxColorToGray.GetCurSel();
	if (COLOR_AUTO_IN == iChoose || COLOR2GRAY_OUT_SYN == iChoose)
	{
		GetDlgItem(IDC_EDIT_CHANNEL_DAYRANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CHANNEL_NIGHTRANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_COLORDELAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GRAYDELAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_DTP_GRAY2COLOR_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DTP_COLOR2GRAY_TIME)->EnableWindow(FALSE);
	}
	else if (COLOR2GRAY_SETTIME == iChoose)
	{
		GetDlgItem(IDC_EDIT_CHANNEL_DAYRANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CHANNEL_NIGHTRANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_COLORDELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GRAYDELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DTP_GRAY2COLOR_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_DTP_COLOR2GRAY_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CHANNEL_DAYRANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CHANNEL_NIGHTRANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_COLORDELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GRAYDELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DTP_GRAY2COLOR_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DTP_COLOR2GRAY_TIME)->EnableWindow(FALSE);
	}
}

void CLS_AdvChannelParamPage::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData )
{
	switch(_iParaType)
	{
	case PARA_DEVICE_STATE:
		{
			GetBrightValue();
		}
		break;
	default:
		break;
	}
}

void CLS_AdvChannelParamPage::GetBrightValue()
{
	int iBrightValue=0;
	int iRet = NetClient_GetDeviceState(m_iLogonID, m_iChannelNo, 0, &iBrightValue);
	{
		CString strValue;
		strValue.Format(_T("%02d"), iBrightValue);
		m_edtBrightValue.SetWindowText(strValue);
	}
}

void CLS_AdvChannelParamPage::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case BRIGHT_VALUE:
		{
			int iRet = NetClient_CheckDeviceState(m_iLogonID, m_iChannelNo, 0);
			if (iRet<0)
			{
				AddLog(LOG_TYPE_FAIL, "", "NetClient_CheckDeviceState(LogonID=%d,ChanNo=%d)", m_iLogonID, m_iChannelNo);
			}
		}
		break;
	}
	
	CLS_BasePage::OnTimer(nIDEvent);
}

void CLS_AdvChannelParamPage::OnEnChangeEditChannelDayrange()
{
	int iDay = GetDlgItemInt(IDC_EDIT_CHANNEL_DAYRANGE);
	if (iDay < 0 || iDay > DAY_LIGNT_MAX)
	{
		SetDlgItemInt(IDC_EDIT_CHANNEL_DAYRANGE, DAY_LIGNT_MAX);
		AddLog(LOG_TYPE_MSG, "", "CLS_AdvChannelParamPage::Put Invalid Value(%d,%d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_AdvChannelParamPage::OnEnChangeEditChannelNightrange()
{
	int iNight = GetDlgItemInt(IDC_EDIT_CHANNEL_NIGHTRANGE);
	if (iNight < 0 || iNight > NIGHT_LIGHT_MAX)
	{
		SetDlgItemInt(IDC_EDIT_CHANNEL_NIGHTRANGE, NIGHT_LIGHT_MAX);
		AddLog(LOG_TYPE_MSG, "", "CLS_AdvChannelParamPage::Put Invalid Value(%d,%d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_AdvChannelParamPage::OnEnChangeEditColordelay()
{
	int iDelay = GetDlgItemInt(IDC_EDIT_COLORDELAY);
	if (iDelay < 0 || iDelay > DELAY_MAX)
	{
		SetDlgItemInt(IDC_EDIT_COLORDELAY, DELAY_MAX);
		AddLog(LOG_TYPE_MSG, "", "CLS_AdvChannelParamPage::Put Invalid Value(%d,%d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_AdvChannelParamPage::OnEnChangeEditGraydelay()
{
	int iDelay = GetDlgItemInt(IDC_EDIT_GRAYDELAY);
	if (iDelay < 0 || iDelay > DELAY_MAX)
	{
		SetDlgItemInt(IDC_EDIT_GRAYDELAY, DELAY_MAX);
		AddLog(LOG_TYPE_MSG, "", "CLS_AdvChannelParamPage::Put Invalid Value(%d,%d)", m_iLogonID, m_iChannelNo);
	}
}
