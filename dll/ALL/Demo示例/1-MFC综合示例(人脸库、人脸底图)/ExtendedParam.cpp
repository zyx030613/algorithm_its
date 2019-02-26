// ExtendedParam.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ExtendedParam.h"


// CLS_ExtendedParam 对话框

IMPLEMENT_DYNAMIC(CLS_ExtendedParam, CDialog)

CLS_ExtendedParam::CLS_ExtendedParam(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ExtendedParam::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ExtendedParam::~CLS_ExtendedParam()
{
}

void CLS_ExtendedParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GP_BASIC_PARAM, m_gpBasicParam);
	DDX_Control(pDX, IDC_STC_NIGHT_BIT_VALUE, m_stcNightBitValue);
	DDX_Control(pDX, IDC_EDT_NIGHT_BIT_VALUE, m_edtNightBitValue);
	DDX_Control(pDX, IDC_BTN_SET_BASIC_PARAM, m_btnNightBitValue);
	DDX_Control(pDX, IDC_GP_FILL_LIGHT_CONTROL, m_gpFillLightControl);
	DDX_Control(pDX, IDC_STC_DAY_THRESHOLD_VALUE, m_stcDayThresholdValue);
	DDX_Control(pDX, IDC_STC_NIGHT_THRESHOLD_VALUE, m_stcNightThresholdValue);
	DDX_Control(pDX, IDC_EDT_DAY_THRESHOLD_VALUE, m_edtDayThresholdValue);
	DDX_Control(pDX, IDC_EDT_NIGHT_THRESHOLD_VALUE, m_edtNightThresholdValue);
	DDX_Control(pDX, IDC_BTN_SET_FILL_LIGHT_CONTROL, m_btnSetFillLightControl);
	DDX_Control(pDX, IDC_GP_TRAFFIC_DAY_NIGHT_TIME, m_gpTrafficDayNIghtTime);
	DDX_Control(pDX, IDC_STC_DAY_TIME, m_stcDayTime);
	DDX_Control(pDX, IDC_STC_NIGHT_TIME, m_stcNightTime);
	DDX_Control(pDX, IDC_EDT_DAY_TIME_HOUR, m_edtDayTimeHour);
	DDX_Control(pDX, IDC_EDT_DAY_TIME_MINUTE, m_edtDayTimeMinute);
	DDX_Control(pDX, IDC_EDT_NIGHT_TIME_HOUR, m_edtNightTimeHour);
	DDX_Control(pDX, IDC_EDT_NIGHT_TIME_MINUTE, m_edtNightTimeMiunte);
	DDX_Control(pDX, IDC_BTN_SET_TRAFFIC_DAY_NIGHT_TIME, m_btnTrafficDayNightTime);
}


BEGIN_MESSAGE_MAP(CLS_ExtendedParam, CDialog)
	ON_BN_CLICKED(IDC_BTN_SET_TRAFFIC_DAY_NIGHT_TIME, &CLS_ExtendedParam::OnBnClickedBtnSetTrafficDayNightTime)
	ON_BN_CLICKED(IDC_BTN_SET_FILL_LIGHT_CONTROL, &CLS_ExtendedParam::OnBnClickedBtnSetFillLightControl)
	ON_BN_CLICKED(IDC_BTN_SET_BASIC_PARAM, &CLS_ExtendedParam::OnBnClickedBtnSetBasicParam)
END_MESSAGE_MAP()


// CLS_ExtendedParam 消息处理程序


BOOL CLS_ExtendedParam::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_ExtendedParam::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannel = _iChannelNo;
	if(m_iChannel < 0) 
	{
		m_iChannel = 0;
	}
	UI_UpdateDialog();
}

void CLS_ExtendedParam::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ExtendedParam::UI_UpdateBasicParamData()
{
	int iDayRange = 0;
	int iNightRange = 0;
	int iColorGrayChange = 0;
	int iRet = NetClient_GetColorParam(m_iLogonID, m_iChannel, &iColorGrayChange,  &iDayRange, &iNightRange);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetColorParam (%d,%d)",m_iLogonID,m_iChannel);
		SetDlgItemInt(IDC_EDT_DAY_THRESHOLD_VALUE, iDayRange);
		SetDlgItemInt(IDC_EDT_NIGHT_THRESHOLD_VALUE, iNightRange);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetColorParam (%d,%d)",m_iLogonID,m_iChannel);
	}
}
void CLS_ExtendedParam::UI_UpdateFillLightControlData()
{
	int iDayRange = 0;
	int iNightRange = 0;
	int iColorGrayChange = 0;
	int iTemp = 0;
	int iRet1 = NetClient_GetColorParam(m_iLogonID, m_iChannel, &iColorGrayChange,  &iDayRange, &iNightRange);
	if(iRet1 == 0)
	{
		SetDlgItemInt(IDC_EDT_DAY_THRESHOLD_VALUE, iDayRange);
		SetDlgItemInt(IDC_EDT_NIGHT_THRESHOLD_VALUE, iNightRange);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetColorParam(%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetColorParam(%d,%d),error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}


	DZ_INFO_PARAM tInputGetValue = {0};
	int iRet = NetClient_GetDZInfo(m_iLogonID, &tInputGetValue);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDZInfo (%d)",m_iLogonID);
		SetDlgItemText(IDC_EDT_NIGHT_BIT_VALUE, (LPSTR)tInputGetValue.m_cParam11);
		//GetDlgItem(IDC_EDT_NIGHT_BIT_VALUE)->SetWindowText((LPSTR)tInputGetValue.m_cParam11);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDZInfo (%d)",m_iLogonID);
	}
}
//刷新交通白天夜晚时间段
void CLS_ExtendedParam::UI_UpdateTrafficDayNightTimeData()
{
	int iGet = 0;
	int iRet = NetClient_GetITSDayNight(m_iLogonID, &iGet);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDayNight (%d)",m_iLogonID);
		SetDlgItemInt(IDC_EDT_NIGHT_TIME_MINUTE, iGet & 0x00000FF);
		SetDlgItemInt(IDC_EDT_NIGHT_TIME_HOUR, (iGet>>8) & 0x00000FF);
		SetDlgItemInt(IDC_EDT_DAY_TIME_MINUTE, (iGet>>16) & 0x00000FF);
		SetDlgItemInt(IDC_EDT_DAY_TIME_HOUR, (iGet>>24) & 0x00000FF);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDayNight (%d)",m_iLogonID);
	}

}

void CLS_ExtendedParam::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_GP_BASIC_PARAM, IDS_ITS_ARITHMETIC_BASIC_NUMBER);
	SetDlgItemTextEx(IDC_STC_NIGHT_BIT_VALUE, IDS_ITS_NIGHTTHRESHOLD);
	SetDlgItemTextEx(IDC_GP_FILL_LIGHT_CONTROL, IDS_ITS_FILL_LIGHT_CONTROL);
	SetDlgItemTextEx(IDC_STC_DAY_THRESHOLD_VALUE, IDS_ITS_DAY_THRESHOLD_VALUE);
	SetDlgItemTextEx(IDC_STC_NIGHT_THRESHOLD_VALUE, IDS_ITS_NIGHT_THRESHOLD_VALUE);
	SetDlgItemTextEx(IDC_GP_TRAFFIC_DAY_NIGHT_TIME, IDS_ITS_TRAFFIC_DAY_NIGHT_TIME);
	SetDlgItemTextEx(IDC_STC_DAY_TIME, IDS_ITS_DAY);
	SetDlgItemTextEx(IDC_STC_NIGHT_TIME, IDS_ITS_NIGHT);
	SetDlgItemTextEx(IDC_BTN_SET_BASIC_PARAM, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_SET_FILL_LIGHT_CONTROL, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_SET_TRAFFIC_DAY_NIGHT_TIME, IDS_SET);
	UI_UpdateBasicParamData();
	UI_UpdateFillLightControlData();
	UI_UpdateTrafficDayNightTimeData();
}

void CLS_ExtendedParam::OnBnClickedBtnSetTrafficDayNightTime()
{
	unsigned int InputTime = 0;
	unsigned int uiTemp = 0;
	unsigned int uiDayHour = GetDlgItemInt(IDC_EDT_DAY_TIME_HOUR);
	unsigned int uiDayMinute = GetDlgItemInt(IDC_EDT_DAY_TIME_MINUTE);
	unsigned int uiNightHour = GetDlgItemInt(IDC_EDT_NIGHT_TIME_HOUR);
	unsigned int uiNightMinute = GetDlgItemInt(IDC_EDT_NIGHT_TIME_MINUTE);
	if(uiDayHour > uiNightHour)
	{
		uiTemp = uiDayHour;
		uiDayHour = uiNightHour;
		uiNightHour = uiTemp;
		uiTemp = uiDayMinute;
		uiDayMinute = uiNightMinute;
		uiNightMinute = uiTemp;
	}
	else if((uiDayHour == uiNightHour)&&(uiDayMinute > uiNightMinute))
	{
		uiTemp = uiDayMinute;
		uiDayMinute = uiNightMinute;
		uiNightMinute = uiTemp;
	}
	InputTime = min(uiDayHour, HOUR_LIMIT);
	InputTime = (InputTime<<8)|min(uiDayMinute, MINUTE_LIMIT);
	InputTime = (InputTime<<8)|min(uiNightHour, HOUR_LIMIT);
	InputTime = (InputTime<<8)|min(uiNightMinute, MINUTE_LIMIT);
	int iRet = NetClient_SetITSDayNight(m_iLogonID, InputTime);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDayNight (%d,%d)",m_iLogonID,InputTime);
		SetDlgItemInt(IDC_EDT_DAY_TIME_HOUR, uiDayHour);
		SetDlgItemInt(IDC_EDT_DAY_TIME_MINUTE, uiDayMinute);
		SetDlgItemInt(IDC_EDT_NIGHT_TIME_HOUR, uiNightHour);
		SetDlgItemInt(IDC_EDT_NIGHT_TIME_MINUTE, uiNightMinute);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDayNight (%d,%d)",m_iLogonID,InputTime);
	}
}

void CLS_ExtendedParam::OnBnClickedBtnSetFillLightControl()
{
	int iDayRange = 0;
	int iNightRange = 0;
	int iColorGrayChange = 0;
	int iTemp = 0;
	int iRet1 = NetClient_GetColorParam(m_iLogonID, m_iChannel, &iColorGrayChange,  &iDayRange, &iNightRange);
	if (0 != iRet1)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetColorParam (%d,%d)",m_iLogonID, m_iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetColorParam (%d,%d)",m_iLogonID, m_iChannel);
		iDayRange = GetDlgItemInt(IDC_EDT_DAY_THRESHOLD_VALUE);
		if(iDayRange > 255)
		{
			iDayRange = 255;
		}
		else if(iDayRange < 0)
		{
			iDayRange = 0;
		}
		iNightRange = GetDlgItemInt(IDC_EDT_NIGHT_THRESHOLD_VALUE);
		if(iNightRange > 255)
		{
			iNightRange = 255;
		}
		else if(iNightRange < 0)
		{
			iNightRange = 0;
		}

		if(iDayRange < iNightRange)
		{
			iTemp = iDayRange;
			iDayRange = iNightRange;
			iNightRange = iTemp;
		}
		int iRet2 = NetClient_SetColorParam(m_iLogonID, m_iChannel, iColorGrayChange,  iDayRange, iNightRange);
		if (0 == iRet2)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetColorParam (%d,%d)",m_iLogonID, m_iChannel);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetColorParam (%d,%d)",m_iLogonID, m_iChannel);
		}
	}
}

void CLS_ExtendedParam::OnBnClickedBtnSetBasicParam()
{
	DZ_INFO_PARAM tInputSetValue = {0};
	int iRet1 = NetClient_GetDZInfo(m_iLogonID, &tInputSetValue);
	if (0 != iRet1)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDZInfo (%d)",m_iLogonID);
		
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDZInfo (%d)",m_iLogonID);
		memcpy(tInputSetValue.m_cParam1,"DETECTBASIC",sizeof("DETECTBASIC"));
		GetDlgItem(IDC_EDT_NIGHT_BIT_VALUE)->GetWindowText((LPSTR)(tInputSetValue.m_cParam11),LEN_64);
		int iRet2 = NetClient_SetDZInfo(m_iLogonID, &tInputSetValue);
		if (0 == iRet2)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDZInfo (%d)",m_iLogonID);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDZInfo (%d)",m_iLogonID);
		}
	}
	
}
