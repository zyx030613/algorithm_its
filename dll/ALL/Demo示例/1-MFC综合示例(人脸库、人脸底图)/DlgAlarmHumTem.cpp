
#include "stdafx.h"
#include "NetClientDemo.h"
#include "DlgAlarmHumTem.h"

#define MAX_INPUT_HUM_DATA_LEN		4
#define MAX_INPUT_TEM_DATA_LEN		5

#define TO_REAL(x)			(((x) - 1000.0)/10.0) 
#define TO_PROTOCOLS(x)		((x)*10 + 1000)

CString DoubleToString(double _dbPara)
{
	CString cstrString;
	cstrString.Format("%.1f", _dbPara);
	return cstrString;
}

double StringToDouble(CString _cstrPara)
{
	double dbTemp = atof(_cstrPara.GetBuffer());
	_cstrPara.ReleaseBuffer();
	return dbTemp;
}

IMPLEMENT_DYNAMIC(CLS_DlgAlarmHumTem, CDialog)

CLS_DlgAlarmHumTem::CLS_DlgAlarmHumTem(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgAlarmHumTem::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgAlarmHumTem::~CLS_DlgAlarmHumTem()
{
}

void CLS_DlgAlarmHumTem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


}


BEGIN_MESSAGE_MAP(CLS_DlgAlarmHumTem, CLS_BasePage)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_HUM_TEM_THRESHOLD_SET, &CLS_DlgAlarmHumTem::OnBnClickedBtnHumTemThresholdSet)
END_MESSAGE_MAP()

BOOL CLS_DlgAlarmHumTem::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	((CEdit*)GetDlgItem(IDC_EDT_HUM_LOW))->SetLimitText(MAX_INPUT_HUM_DATA_LEN);
	((CEdit*)GetDlgItem(IDC_EDT_HUM_UP))->SetLimitText(MAX_INPUT_HUM_DATA_LEN);
	((CEdit*)GetDlgItem(IDC_EDT_TEM_LOW))->SetLimitText(MAX_INPUT_TEM_DATA_LEN);
	((CEdit*)GetDlgItem(IDC_EDT_TEM_UP))->SetLimitText(MAX_INPUT_TEM_DATA_LEN);

	return TRUE;
}

void CLS_DlgAlarmHumTem::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		UI_UpdateHumTemThreshold();
	}
}

void CLS_DlgAlarmHumTem::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (0 > _iChannelNo) ? 0 : _iChannelNo;
	m_iStreamNo = (0 > _iStreamNo) ? 0 : _iStreamNo;

	UI_UpdateHumTemThreshold();
}

void CLS_DlgAlarmHumTem::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DlgAlarmHumTem::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	if (_iLogonID != m_iLogonID)
	{
		return;
	}

	switch (_iParaType)
	{
	case PARA_ALARMTRIGGER_TEMPERATURE:
		UI_UpdateTemThreshold();
		break;
	case PARA_ALARMTRIGGER_HUMIDITY:
		UI_UpdateHumThreshold();
		break;
	default:
		break;
	}
}

void CLS_DlgAlarmHumTem::InitDialogItemText()
{
	SetDlgItemText(IDC_GPO_HUM_TEM_THRESHOLD, GetTextEx(IDS_HUM_TEM_THRESHOLD));
	SetDlgItemText(IDC_STC_TEM_THRESHOLD, GetTextEx(IDS_TEM_THRESHOLD));
	SetDlgItemText(IDC_STC_TEM_UP, GetTextEx(IDS_TEMP_UP) + _T("(℃)"));
	SetDlgItemText(IDC_STC_TEM_LOW, GetTextEx(IDS_TEM_LOW) + _T("(℃)"));
	SetDlgItemText(IDC_STC_HUM_THRESHOLD, GetTextEx(IDS_HUM_THRESHOLD));
	SetDlgItemText(IDC_STC_HUM_UP, GetTextEx(IDS_HUM_UP));
	SetDlgItemText(IDC_STC_HUM_LOW, GetTextEx(IDS_HUM_LOW));
	SetDlgItemText(IDC_BTN_HUM_TEM_THRESHOLD_SET, GetTextEx(IDS_SET));
}

void CLS_DlgAlarmHumTem::OnBnClickedBtnHumTemThresholdSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","Set HumTemThreshold  LogonID < 0");
		return;
	}

	int iRet = RET_FAILED;


	CString cstrTemp;
	//湿度阈值
	TAlarmTriggerParam tHumThreshold = {0};
	tHumThreshold.iBuffSize = sizeof(TAlarmTriggerParam);
	tHumThreshold.iType = ALARM_TRIGGER_TYPE_HUMIDITY;
	GetDlgItemText(IDC_EDT_HUM_UP, cstrTemp);
	tHumThreshold.iValue = TO_PROTOCOLS(StringToDouble(cstrTemp));
	cstrTemp.Empty();
	GetDlgItemText(IDC_EDT_HUM_LOW, cstrTemp);
	tHumThreshold.iValueEx = TO_PROTOCOLS(StringToDouble(cstrTemp));
	iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_HUMIDITY, CMD_SET_ALARMTRIGGER, &tHumThreshold);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_HUMIDITY, CMD_SET_ALARMTRIGGER);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_HUMIDITY, CMD_SET_ALARMTRIGGER);
	}

	cstrTemp.Empty();

	//温度阈值
	TAlarmTriggerParam tTempThreshold = {0};
	tTempThreshold.iBuffSize = sizeof(TAlarmTriggerParam);
	tTempThreshold.iType = ALARM_TRIGGER_TYPE_TEMPERATURE;
	GetDlgItemText(IDC_EDT_TEM_UP, cstrTemp);
	tTempThreshold.iValue = TO_PROTOCOLS(StringToDouble(cstrTemp));
	cstrTemp.Empty();
	GetDlgItemText(IDC_EDT_TEM_LOW, cstrTemp);
	tTempThreshold.iValueEx = TO_PROTOCOLS(StringToDouble(cstrTemp));
	iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_TEMPERATURE, CMD_SET_ALARMTRIGGER, &tTempThreshold);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_TEMPERATURE, CMD_SET_ALARMTRIGGER);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_TEMPERATURE, CMD_SET_ALARMTRIGGER);
	}

	return;

}

void CLS_DlgAlarmHumTem::UI_UpdateHumTemThreshold()
{
	UI_UpdateHumThreshold();
	UI_UpdateTemThreshold();
}

void CLS_DlgAlarmHumTem::UI_UpdateHumThreshold()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","Update HumThreshold  LogonID < 0");
		return;
	}

	int iRet = RET_FAILED;

	//湿度阈值
	TAlarmTriggerParam tHumThreshold = {0};
	tHumThreshold.iBuffSize = sizeof(TAlarmTriggerParam);
	tHumThreshold.iType = ALARM_TRIGGER_TYPE_HUMIDITY;
	iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_HUMIDITY, CMD_GET_ALARMTRIGGER, &tHumThreshold);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmConfig(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_HUMIDITY, CMD_GET_ALARMTRIGGER);
	}
	else
	{
		SetDlgItemText(IDC_EDT_HUM_UP, DoubleToString(TO_REAL(tHumThreshold.iValue)));
		SetDlgItemText(IDC_EDT_HUM_LOW, DoubleToString(TO_REAL(tHumThreshold.iValueEx)));
	}

	return;
}

void CLS_DlgAlarmHumTem::UI_UpdateTemThreshold()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","Update TemThreshold  LogonID < 0");
		return;
	}

	int iRet = RET_FAILED;

	//温度阈值
	TAlarmTriggerParam tTempThreshold = {0};
	tTempThreshold.iBuffSize = sizeof(TAlarmTriggerParam);
	tTempThreshold.iType = ALARM_TRIGGER_TYPE_TEMPERATURE;
	iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_TEMPERATURE, CMD_GET_ALARMTRIGGER, &tTempThreshold);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmConfig(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, ALARM_TRIGGER_TYPE_TEMPERATURE, CMD_GET_ALARMTRIGGER);
	}
	else
	{
		SetDlgItemText(IDC_EDT_TEM_UP, DoubleToString(TO_REAL(tTempThreshold.iValue)));
		SetDlgItemText(IDC_EDT_TEM_LOW, DoubleToString(TO_REAL(tTempThreshold.iValueEx)));
	}

	return;
}
