// Config/VehiclePage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VehiclePage.h"


// CLS_VehiclePage dialog

IMPLEMENT_DYNAMIC(CLS_VehiclePage, CDialog)

CLS_VehiclePage::CLS_VehiclePage(CWnd* pParent /*=NULL*/)
: CLS_BasePage(CLS_VehiclePage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_VehiclePage::~CLS_VehiclePage()
{
}

void CLS_VehiclePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GPS_TYPE, m_cboGpsType);
	DDX_Control(pDX, IDC_PROGRESS_GPS_SIGNAL, m_progressGpsSignal);
	DDX_Control(pDX, IDC_SPIN_ALARM_VOLTAGE_THRESHOLD, m_spinAlarmValue);
	DDX_Control(pDX, IDC_SPIN_SHUTDOWN_VOLTAGE_THRESHOLD, m_spinShutdownValue);
}


BEGIN_MESSAGE_MAP(CLS_VehiclePage, CDialog)
	ON_BN_CLICKED(IDC_CHECK_GPS_CALIBRATION, &CLS_VehiclePage::OnBnClickedCheckGpsCalibration)
	ON_BN_CLICKED(IDC_BUTTON_VOLTAGE_THRESHOLD, &CLS_VehiclePage::OnBnClickedButtonVoltageThreshold)
END_MESSAGE_MAP()


// CLS_VehiclePage message handlers

BOOL CLS_VehiclePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	m_cboGpsType.SetCurSel(0);
	m_progressGpsSignal.SetRange(0,100);

	m_tipCtrl.Create(this,TTF_ALWAYSTIP);
	m_tipCtrl.AddTool(&m_progressGpsSignal,_T("0%"));
	m_tipCtrl.SetDelayTime(150);

	return TRUE; 
}

void CLS_VehiclePage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_GPS_TYPE,IDS_VEHICLE_GPS_MODULE_TYPE);
	SetDlgItemTextEx(IDC_CHECK_GPS_CALIBRATION,IDS_VEHICLE_GPS_CALIBRATION);
	SetDlgItemTextEx(IDC_STATIC_VOLTAGE_THRESHOLD,IDS_VEHICLE_VOLTAGE_THRESHOLD);
	SetDlgItemTextEx(IDC_STATIC_SATELLITE_NUM,IDS_VEHICLE_SATELLITE_NUM);
	SetDlgItemTextEx(IDC_STATIC_GPS_SIGNAL,IDS_VEHICLE_GPS_SIGNAL);
	SetDlgItemTextEx(IDC_STATIC_TEMPERATURE,IDS_VEHICLE_TEMPERATURE);
	SetDlgItemTextEx(IDC_STATIC_SUPPLY_VOLTAGE,IDS_VEHICLE_SUPPLY_VOLTAGE);
	SetDlgItemTextEx(IDC_STATIC_ALARM_VOLTAGE_THRESHOLD,IDS_VEHICLE_ALARM_VOLTAGE_THRESHOLD);
	SetDlgItemTextEx(IDC_STATIC_SHUTDOWN_VOLTAGE_THRESHOLD,IDS_VEHICLE_SHUTDOWN_VOLTAGE_THRESHOLD);
	SetDlgItemTextEx(IDC_BUTTON_VOLTAGE_THRESHOLD,IDS_SET);

	InsertString(m_cboGpsType,0,IDS_VEHICLE_MODULE_TYPE_NONE);
	InsertString(m_cboGpsType,1,IDS_VEHICLE_MODULE_TYPE_GPS);
	InsertString(m_cboGpsType,2,IDS_VEHICLE_MODULE_TYPE_COMPASS);
	
}

void CLS_VehiclePage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	UI_UpdateVehicle();
}

void CLS_VehiclePage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_VehiclePage::UI_UpdateGpsCalibration()
{
	if (NetClient_GetCommonEnable)
	{
		int iEnableValue = -1;
		int iRet = NetClient_GetCommonEnable(m_iLogonID, CI_VEHICLE_GPS_CALIBRATION, 0x7FFFFFFF, &iEnableValue);
		if (0 == iRet)
		{
			CheckDlgButton(IDC_CHECK_GPS_CALIBRATION,iEnableValue);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetCommonEnable(%d,CI_VEHICLE_GPS_CALIBRATION)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateGpsModuleType()
{
	if (NetClient_GetBroadcastMessage)
	{
		BROADCAST_MSG tMsg = {0};
		tMsg.iMsgID = MSG_VEHICLE_GPS_MODULE_TYPE;
		int iRet = NetClient_GetBroadcastMessage(m_iLogonID, &tMsg,sizeof(BROADCAST_MSG));
		if (0 == iRet)
		{
			m_cboGpsType.SetCurSel(tMsg.iMsgValue);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetBroadcastMessage(%d,MSG_VEHICLE_GPS_MODULE_TYPE)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateSatelliteNum()
{
	if (NetClient_GetBroadcastMessage)
	{
		BROADCAST_MSG tMsg = {0};
		tMsg.iMsgID = MSG_VEHICLE_SATELLITE_NUM;
		int iRet = NetClient_GetBroadcastMessage(m_iLogonID, &tMsg,sizeof(BROADCAST_MSG));
		if (0 == iRet)
		{
			int iSatelliteNum = tMsg.iMsgValue;
			SetDlgItemInt(IDC_COMBO_SATELLITE_NUM,iSatelliteNum);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetBroadcastMessage(%d,MSG_VEHICLE_SATELLITE_NUM)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateSignalIntensity()
{
	if (NetClient_GetBroadcastMessage)
	{
		BROADCAST_MSG tMsg = {0};
		tMsg.iMsgID = MSG_VEHICLE_SIGNAL_INTENSITY;
		int iRet = NetClient_GetBroadcastMessage(m_iLogonID, &tMsg,sizeof(BROADCAST_MSG));
		if (0 == iRet)
		{
			int iGpsSignal = tMsg.iMsgValue;
			m_progressGpsSignal.SetPos(iGpsSignal);
			CString strSignal;
			strSignal.Format(_T("%d%%"),iGpsSignal);
			m_tipCtrl.UpdateTipText(strSignal,&m_progressGpsSignal);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetBroadcastMessage(%d,MSG_VEHICLE_SIGNAL_INTENSITY)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateSupplyVoltage()
{
	if (NetClient_GetBroadcastMessage)
	{
		BROADCAST_MSG tMsg = {0};
		tMsg.iMsgID = MSG_VEHICLE_VOLTAGE;
		int iRet = NetClient_GetBroadcastMessage(m_iLogonID, &tMsg,sizeof(BROADCAST_MSG));
		if (0 == iRet)
		{
			int iVoltage = tMsg.iMsgValue;
			CString strVoltage;
			strVoltage.Format(_T("%d.%d V"),iVoltage/10,iVoltage%10);
			SetDlgItemText(IDC_EDIT_SUPPLY_VOLTAGE,strVoltage);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetBroadcastMessage(%d,MSG_VEHICLE_VOLTAGE)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateTemperature()
{
	if (NetClient_GetBroadcastMessage)
	{
		BROADCAST_MSG tMsg = {0};
		tMsg.iMsgID = MSG_VEHICLE_TEMPERATURE;
		int iRet = NetClient_GetBroadcastMessage(m_iLogonID, &tMsg,sizeof(BROADCAST_MSG));
		if (0 == iRet)
		{
			int iTemperature = tMsg.iMsgValue-1000;
			CString strTemperature;
			strTemperature.Format(_T("%d.%d ¡æ"),iTemperature/10,iTemperature%10);
			SetDlgItemText(IDC_EDIT_TEMPERATURE,strTemperature);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetBroadcastMessage(%d,MSG_VEHICLE_TEMPERATURE)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateAlarmThreshold()
{
	if (NetClient_GetCommonEnable)
	{
		int iThreshold = 0;
		int iRet = NetClient_GetCommonEnable(m_iLogonID, CI_VEHICLE_ALARM_THRESHOLD, 0x7FFFFFFF, &iThreshold);
		if (0 == iRet)
		{
			SetDlgItemInt(IDC_EDIT_ALARM_VOLTAGE_THRESHOLD,iThreshold/10);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetCommonEnable(%d,CI_VEHICLE_ALARM_THRESHOLD)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateShutdownThreshold()
{
	if (NetClient_GetCommonEnable)
	{
		int iThreshold = 0;
		int iRet = NetClient_GetCommonEnable(m_iLogonID, CI_VEHICLE_SHUTDOWN_THRESHOLD, 0x7FFFFFFF, &iThreshold);
		if (0 == iRet)
		{
			SetDlgItemInt(IDC_EDIT_SHUTDOWN_VOLTAGE_THRESHOLD,iThreshold/10);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetCommonEnable(%d,CI_VEHICLE_SHUTDOWN_THRESHOLD)",m_iLogonID);
		}
	}
}

void CLS_VehiclePage::UI_UpdateVehicle()
{
	UI_UpdateGpsCalibration();
	UI_UpdateGpsModuleType();
	UI_UpdateSatelliteNum();
	UI_UpdateSignalIntensity();
	UI_UpdateSupplyVoltage();
	UI_UpdateTemperature();
	UI_UpdateAlarmThreshold();
	UI_UpdateShutdownThreshold();
}

void CLS_VehiclePage::OnBnClickedCheckGpsCalibration()
{
	if (NetClient_SetCommonEnable)
	{
		int iEnableValue = IsDlgButtonChecked(IDC_CHECK_GPS_CALIBRATION);
		int iRet = NetClient_SetCommonEnable(m_iLogonID, CI_VEHICLE_GPS_CALIBRATION, 0x7FFFFFFF, iEnableValue);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","SetCommonEnable(%d,CI_VEHICLE_GPS_CALIBRATION,%d)",m_iLogonID,iEnableValue);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","SetCommonEnable(%d,CI_VEHICLE_GPS_CALIBRATION,%d)",m_iLogonID,iEnableValue);
		}
	}
}

void CLS_VehiclePage::OnBnClickedButtonVoltageThreshold()
{
	if (NetClient_SetCommonEnable)
	{
		int iLower = 0;
		int iUpper = 0;
		m_spinAlarmValue.GetRange(iLower,iUpper);
		int iAlarmThreshold = GetDlgItemInt(IDC_EDIT_ALARM_VOLTAGE_THRESHOLD);
		int iShutdownThreshold = GetDlgItemInt(IDC_EDIT_SHUTDOWN_VOLTAGE_THRESHOLD);
		if (iAlarmThreshold > iUpper)
		{
			iAlarmThreshold = iUpper;
			SetDlgItemInt(IDC_EDIT_ALARM_VOLTAGE_THRESHOLD,iAlarmThreshold);
		}
		if (iShutdownThreshold > iUpper)
		{
			iShutdownThreshold = iUpper;
			SetDlgItemInt(IDC_EDIT_SHUTDOWN_VOLTAGE_THRESHOLD,iShutdownThreshold);
		}
		iAlarmThreshold *= 10;
		iShutdownThreshold *= 10;

		int iThreshold = iAlarmThreshold;
		int iRet = NetClient_SetCommonEnable(m_iLogonID, CI_VEHICLE_ALARM_THRESHOLD, 0x7FFFFFFF, iThreshold);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","SetCommonEnable(%d,CI_VEHICLE_ALARM_THRESHOLD,%d)",m_iLogonID,iThreshold);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","SetCommonEnable(%d,CI_VEHICLE_ALARM_THRESHOLD,%d)",m_iLogonID,iThreshold);
		}

		iThreshold = iShutdownThreshold;
		iRet = NetClient_SetCommonEnable(m_iLogonID, CI_VEHICLE_SHUTDOWN_THRESHOLD, 0x7FFFFFFF, iThreshold);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","SetCommonEnable(%d,CI_VEHICLE_SHUTDOWN_THRESHOLD,%d)",m_iLogonID,iThreshold);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","SetCommonEnable(%d,CI_VEHICLE_SHUTDOWN_THRESHOLD,%d)",m_iLogonID,iThreshold);
		}
	}
}

void CLS_VehiclePage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	int iMsgType = LOWORD(_wParam);
	switch(iMsgType)
	{
	case WCM_BROADCAST_MSG:
		{
			int iLogonID = HIWORD(_wParam);
			PBROADCAST_MSG pMsg = (PBROADCAST_MSG)_iLParam;
			if (NULL == pMsg)
			{
				break;
			}
			switch(pMsg->iMsgID)
			{
			case MSG_VEHICLE_GPS_CALIBRATION:
				UI_UpdateGpsCalibration();
				break;
			case MSG_VEHICLE_VOLTAGE:
				UI_UpdateSupplyVoltage();
				break;
			case MSG_VEHICLE_TEMPERATURE:
				UI_UpdateTemperature();
				break;
			case MSG_VEHICLE_SATELLITE_NUM:
				UI_UpdateSatelliteNum();
				break;
			case MSG_VEHICLE_SIGNAL_INTENSITY:
				UI_UpdateSignalIntensity();
				break;
			case MSG_VEHICLE_GPS_MODULE_TYPE:
				UI_UpdateGpsModuleType();
				break;
			case MSG_VEHICLE_ALARM_THRESHOLD:
				UI_UpdateAlarmThreshold();
				break;
			case MSG_VEHICLE_SHUTDOWN_THRESHOLD:
				UI_UpdateShutdownThreshold();
				break;
			}
		}
		break;
	}
}

BOOL CLS_VehiclePage::PreTranslateMessage(MSG* pMsg)
{
	if(WM_MOUSEMOVE == pMsg->message)
	{
		m_tipCtrl.RelayEvent(pMsg);
	}

	return CLS_BasePage::PreTranslateMessage(pMsg);
}
