
#include "stdafx.h"
#include "NetClientDemo.h"
#include "PowerEnvParamPage.h"
#include "DhDebugKGL.h"
#include "DhDebugMNL.h"
#include "DhDebugWSD.h"
#include "NetClientTypes.h"
// CLS_PowerEnvParamPage 对话框

enum n_ListAlarmData{
	n_ListAlarmData_No,
	n_ListAlarmData_Name,
	n_ListAlarmData_AlarmState,
	n_ListAlarmData_ScheduleState,
	n_ListAlarmData_LiveData,
	n_ListAlarmData_Time,
	n_ListAlarmData_Operation
};


enum n_AlarmState{
	n_AlarmState_Normal,
	n_AlarmState_Alarming
};

enum n_AlarmType{
	BIT_HEAT_HI_ALARM = 1 << 0,//温度上限报警
	BIT_HEAT_HI_DEALARM = 1 << 1,//温度上限消警
	BIT_HEAT_LO_ALARM = 1 <<2,//温度下限报警
	BIT_HEAT_LO_DEALARM=1 << 3,//温度下限消警
	BIT_HUM_HI_ALARM = 1 <<4,//湿度上限报警
	BIT_HUM_HI_DEALARM = 1 <<5,//湿度上限消警
	BIT_HUM_LO_ALARM = 1 << 6,//湿度下限报警
	BIT_HUM_LO_DEALARM = 1 << 7,//湿度下限消警
	BIT_OFFLINE_ALARM = 1 << 31//设备掉线报警
};

enum n_ComType{
	n_TemperatureHumidity
};

IMPLEMENT_DYNAMIC(CLS_PowerEnvParamPage, CDialog)

CLS_PowerEnvParamPage::CLS_PowerEnvParamPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_PowerEnvParamPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_PowerEnvParamPage::~CLS_PowerEnvParamPage()
{
}

void CLS_PowerEnvParamPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_DH, m_lstctrlSchedule);
	DDX_Control(pDX, IDC_LST_SWITCH, m_lstctrlKey);
	DDX_Control(pDX, IDC_CHK_DH_SELALL, m_chkAllSchedule);
	DDX_Control(pDX, IDC_CHK_SWITCH_SELALL, m_chkAllKey);
}


BEGIN_MESSAGE_MAP(CLS_PowerEnvParamPage, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LST_DH, &CLS_PowerEnvParamPage::OnNMClickLstDh)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CLS_PowerEnvParamPage::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CLS_PowerEnvParamPage::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_MANUAL_BF, &CLS_PowerEnvParamPage::OnBnClickedBtnManualBf)
	ON_BN_CLICKED(IDC_BTN_MANUAL_SF, &CLS_PowerEnvParamPage::OnBnClickedBtnManualSf)
	ON_BN_CLICKED(IDC_BTN_MANUAL_RECOVER, &CLS_PowerEnvParamPage::OnBnClickedBtnManualRecover)
	ON_BN_CLICKED(IDC_CHK_DH_SELALL, &CLS_PowerEnvParamPage::OnBnClickedChkDhSelall)
	ON_BN_CLICKED(IDC_CHK_SWITCH_SELALL, &CLS_PowerEnvParamPage::OnBnClickedChkSwitchSelall)
END_MESSAGE_MAP()


// CLS_PowerEnvParamPage 消息处理程序

BOOL CLS_PowerEnvParamPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_CHK_DH_SELALL, IDS_CONFIG_LINK_SELECT_ALL);
	SetDlgItemTextEx(IDC_BTN_MANUAL_BF, IDS_CONFIG_DH_MANUAL_BF);
	SetDlgItemTextEx(IDC_BTN_MANUAL_SF, IDS_CONFIG_DH_MANUAL_SF);
	SetDlgItemTextEx(IDC_BTN_MANUAL_RECOVER, IDS_CONFIG_DH_MANUAL_RECOVER);
	SetDlgItemTextEx(IDC_STC_SWITCH, IDS_CONFIG_DH_SWITCH);
	SetDlgItemTextEx(IDC_CHK_SWITCH_SELALL, IDS_CONFIG_LINK_SELECT_ALL);
	SetDlgItemTextEx(IDC_BTN_OPEN, IDS_CONFIG_OPEN);
	SetDlgItemTextEx(IDC_BTN_CLOSE, IDS_CONFIG_CLOSE);

	int iColumn = 0;
	DWORD dwStyle = m_lstctrlSchedule.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT| LVS_EX_CHECKBOXES;  
	m_lstctrlSchedule.SetExtendedStyle(dwStyle);
	InsertColumn(m_lstctrlSchedule, iColumn++, GetTextEx(IDS_CONFIG_LINK_ACTION_NUM), LVCFMT_LEFT, 100);
	InsertColumn(m_lstctrlSchedule, iColumn++, GetTextEx(IDS_CONFIG_LINK_ACTION_NAME), LVCFMT_LEFT, 100);
	InsertColumn(m_lstctrlSchedule, iColumn++, GetTextEx(IDS_POWER_ENV_ALARM_STATE), LVCFMT_LEFT, 100);
	InsertColumn(m_lstctrlSchedule, iColumn++, GetTextEx(IDS_POWER_ENV_SCHEDULE_STATE), LVCFMT_LEFT, 100);
	InsertColumn(m_lstctrlSchedule, iColumn++, GetTextEx(IDS_POWER_ENV_DATA), LVCFMT_LEFT, 100);
	InsertColumn(m_lstctrlSchedule, iColumn++, GetTextEx(IDS_CONFIG_OPETATE), LVCFMT_LEFT, 50);

	iColumn = 0;
	dwStyle = m_lstctrlKey.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT| LVS_EX_CHECKBOXES;  
	m_lstctrlKey.SetExtendedStyle(dwStyle);
	InsertColumn(m_lstctrlKey, iColumn++, GetTextEx(IDS_CONFIG_LINK_DEV_NUM), LVCFMT_LEFT, 200);
	InsertColumn(m_lstctrlKey, iColumn++, GetTextEx(IDS_CONFIG_DH_STATUS), LVCFMT_LEFT, 200);
	
	return TRUE; 
}

void CLS_PowerEnvParamPage::OnLanguageChanged(int _iLanguage)
{
	OnInitDialog();
	UpdateDialog();
}

void CLS_PowerEnvParamPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_chkAllSchedule.SetCheck(FALSE);
	m_chkAllKey.SetCheck(FALSE);
	UpdateDialog();
}

BOOL CLS_PowerEnvParamPage::UpdateDialog()
{
	int iAlarmInPortNum = 0;
	int iAlarmOutPortNum = 0;
	int iRet = -1;
	iRet =  NetClient_GetAlarmPortNum(m_iLogonID, &iAlarmInPortNum, &iAlarmOutPortNum);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_PowerEnvParamPage::UpdateDialog] NetClient_GetAlarmPortNum(%d,,) failed! Error(0x%08x)"
			,m_iLogonID);
		m_lstctrlKey.DeleteAllItems();
		return FALSE;
	}

	UpdateInportInfo(iAlarmInPortNum);

	UpdateOutportInfo(iAlarmOutPortNum);

	return TRUE;
}

BOOL CLS_PowerEnvParamPage::UpdateInportInfo(int _iInportNum)
{
	AlarmInConfig tConfig;
	for (int i = 0; i < _iInportNum; ++i)
	{
		tConfig.iSize = sizeof(tConfig);
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,i,-1,CMD_ALARM_IN_CONFIG,&tConfig);
		if(0 != iRet)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_PowerEnvParamPage::UpdateInportInfo] NetClient_GetAlarmConfig(%d,%d,,CMD_ALARM_IN_CONFIG) failed! Error(0x%08x)"
				,m_iLogonID,i,GetLastError());

			continue;
		}

		//使能
		int iEnable = -1;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, i, -1, CMD_DH_DEVICE_ENABLE, &iEnable);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "OperateInfo-TDGetAlarmConfig(Get EnableInfo error. iEnable %d)",iEnable);
		}

		int iIndex = FindScheduleItem(i);
		if (iEnable)
		{
			if (iIndex < 0)
			{
				CString strChannelNo;
				strChannelNo.Format(_T("%d"), i+1);
				iIndex = m_lstctrlSchedule.InsertItem(m_lstctrlSchedule.GetItemCount(),strChannelNo);
				m_lstctrlSchedule.SetItemText(iIndex,5, GetText(IDS_DEBUG));
			}

			m_lstctrlSchedule.SetItemText(iIndex,1,tConfig.cName);


			UpdateAlarmStateItem(iIndex,-1,ALARM_NORMAL,n_AlarmState_Normal);

			//UpdateLiveDataInfo(iIndex,iInterfaceType,pcInfo,sizeof(_pData->cInfo));


			int iEnable = 0;
			int iRet = NetClient_GetAlarmConfig(m_iLogonID,i,-1,CMD_ALARM_IN_SCHEDULE_ENABLE,&iEnable);
			if(0 == iRet)
			{
				UpdateScheduleStateItem(i,1,iEnable);			
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","[CLS_PowerEnvParamPage::UpdateInportInfo] NetClient_GetAlarmConfig(%d,%d,,CMD_ALARM_IN_SCHEDULE_ENABLE) failed! Error(0x%08x)"
					,m_iLogonID,i,GetLastError());
			}
		}
		else
		{
			if (iIndex >= 0)
			{
				m_lstctrlSchedule.DeleteItem(iIndex);
			}
		}	
	}

	return TRUE;
}

BOOL CLS_PowerEnvParamPage::UpdateOutportInfo(int _iOutportNum)
{
	m_lstctrlKey.DeleteAllItems();

	CString strState;	
	for (int i = 0; i < _iOutportNum; ++i)
	{
		int iState = 0;
		int iRet = NetClient_GetOutportState(m_iLogonID,i,&iState);
		if (0 != iRet)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_PowerEnvParamPage::UpdateOutportInfo] NetClient_GetOutportEnable(%d,%d) failed! Error(0x%08x)"
				,m_iLogonID,i,GetLastError());
			continue;
		}
		strState.Format(_T("%d"), i+1);
		m_lstctrlKey.InsertItem(i, strState);


		UpdateOutportItem(i,iState);
	}

	return TRUE;
}

BOOL CLS_PowerEnvParamPage::UpdateScheduleStateItem(int _iOutportNo,int _iType,int _iState)
{
	int iIndex = FindScheduleItem(_iOutportNo);
	if (iIndex < 0)
	{
		return FALSE;
	}

	CString cstrState;

	switch(_iType)
	{
	case 1:
		{
			cstrState.Append(GetText(IDS_MANUAL));
		}
		break;
	case 2:
		{
			cstrState.Append(GetText(IDS_ALARM_SCHEDULE_AUTO));
		}
		break;
	default:
		return FALSE;
	}

	if (1 == _iState)
	{
		cstrState.AppendFormat(_T("%s"),GetText(IDS_ALARM_SCHEDULE_STATUS_ENABLE));
	}
	else
	{
		cstrState.AppendFormat(_T("%s"),GetText(IDS_ALARM_SCHEDULE_STATUS_DISABLE));
	}

// 	if (1 == _iState)
// 	{
// 		cstrState = GetTextEx(IDS_ALARM_SCHEDULE_STATUS_ENABLE);
// 	}
// 	else
// 	{
// 		cstrState = GetTextEx(IDS_ALARM_SCHEDULE_STATUS_DISABLE);
// 	}
	m_lstctrlSchedule.SetItemText(iIndex,3,cstrState);

	return TRUE;
}

int CLS_PowerEnvParamPage::FindScheduleItem( int _iOutportNo )
{
	int iIndex = -1;
	for (int i = 0; i < m_lstctrlSchedule.GetItemCount(); ++i)
	{
		char cChannelNo[16] = {0};
		int iChannelNo = -1;
		m_lstctrlSchedule.GetItemText(i,0,cChannelNo,sizeof(cChannelNo));
		iChannelNo = atoi(cChannelNo) - 1;
		if (iChannelNo == _iOutportNo)
		{
			iIndex = i;
			break;
		}
	}
	return iIndex;
}

BOOL CLS_PowerEnvParamPage::UpdateOutportItem(int _iIndex,int _iState)
{
	CString cstrState;
	if (1 == _iState)
	{
		cstrState = GetTextEx(IDS_OUTPORT_STATE_ON);
	}
	else
	{
		cstrState = GetTextEx(IDS_OUTPORT_STATE_OFF);
	}
	m_lstctrlKey.SetItemText(_iIndex,1,cstrState);

	return TRUE;
}

void CLS_PowerEnvParamPage::OnAlarmNotify(int _iLogonID, int _iChannelNo, int _iAlarmState,int _iAlarmType,int _iUserData)
{
	/*
	switch (_iAlarmType)
	{
	case ALARM_ANALOG_UPPER_LIMIT:
		{
			UpdateAlarmStateItem(_iChannelNo,IDS_ALARM_ANALOG_UPPER_LIMIT,_iAlarmState);
		}
		break;
	case ALARM_ANALOG_LOWER_LIMIT:
		{
			UpdateAlarmStateItem(_iChannelNo,IDS_ALARM_ANALOG_LOWER_LIMIT,_iAlarmState);
		}
		break;
	case ALARM_TEMPERATURE_UPPER_LIMIT:
		{
			UpdateAlarmStateItem(_iChannelNo,IDS_ALARM_TEMPERATURE_UPPER_LIMIT,_iAlarmState);
		}
		break;
	case ALARM_TEMPERATURE_LOWER_LIMIT:
		{
			UpdateAlarmStateItem(_iChannelNo,IDS_ALARM_TEMPERATURE_LOWER_LIMIT,_iAlarmState);
		}
		break;
	case ALARM_HUMIDITY_UPPER_LIMIT:
		{
			UpdateAlarmStateItem(_iChannelNo,IDS_ALARM_HUMIDITY_UPPER_LIMIT,_iAlarmState);
		}
		break;
	case ALARM_HUMIDITY_LOWER_LIMIT:
		{
			UpdateAlarmStateItem(_iChannelNo,IDS_ALARM_HUMIDITY_LOWER_LIMIT,_iAlarmState);
		}
		break;
	default:
		break;
	}
	*/
}

BOOL CLS_PowerEnvParamPage::UpdateAlarmStateItem( int _iOutportNo,int _iInterfaceType,int _iAlarmType, int _iState)
{
	int iIndex = FindScheduleItem(_iOutportNo);
	if (iIndex < 0)
	{
		return FALSE;
	}

		CString strAlarm;
		if (n_AlarmState_Alarming == _iState)
		{
			if (_iInterfaceType == ALARM_INTERFACE_TYPE_COM)
			{
				int iIDSAlarm = IDS_NORMAL;
				if (_iAlarmType & BIT_HEAT_HI_ALARM)
				{
					iIDSAlarm = GetAlarmStateID(ALARM_TEMPERATURE_UPPER_LIMIT_ON);
					strAlarm.AppendFormat(_T("%s "),GetText(iIDSAlarm));
				}
				if (_iAlarmType & BIT_HEAT_LO_ALARM)
				{
					iIDSAlarm = GetAlarmStateID(ALARM_TEMPERATURE_LOWER_LIMIT_ON);
					strAlarm.AppendFormat(_T("%s "),GetText(iIDSAlarm));
				}
				if (_iAlarmType & BIT_HUM_HI_ALARM)
				{
					iIDSAlarm = GetAlarmStateID(ALARM_HUMIDITY_UPPER_LIMIT_ON);
					strAlarm.AppendFormat(_T("%s "),GetText(iIDSAlarm));
				}
				if (_iAlarmType & BIT_HUM_LO_ALARM)
				{
					iIDSAlarm = GetAlarmStateID(ALARM_HUMIDITY_LOWER_LIMIT_ON);
					strAlarm.AppendFormat(_T("%s "),GetText(iIDSAlarm));
				}
				if (_iAlarmType & BIT_OFFLINE_ALARM)
				{
					strAlarm.AppendFormat(_T("%s "),GetText(IDS_ALARM_OFFLINE));
				}
				if (strAlarm.GetLength() <= 0)
				{
					strAlarm.AppendFormat(_T("%s "),GetText(IDS_NORMAL));
				}
			}
			else
			{
				int iIDSAlarm = GetAlarmStateID(_iAlarmType);
				strAlarm.Format(_T("%s"),GetText(iIDSAlarm));
			}
		}
		else
		{
			strAlarm.Format(_T("%s"),GetText(IDS_NORMAL));
		}

		m_lstctrlSchedule.SetItemText(iIndex,n_ListAlarmData_AlarmState,strAlarm);


	return TRUE;
}

void CLS_PowerEnvParamPage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	switch(_wParam)
	{
	case WCM_ALARM_INFORMATION:
		{
			AlarmInfoData* pData = (AlarmInfoData*)_iLParam;
			if (pData)
			{
				UpdateAlarmInfo(pData);			
			}
		}
		break;
	case WCM_ALARM_OUT_STATUS:
		{
			if (m_iLogonID == _iLogonID)
			{
				int iOutportNo = (int)_iLParam;
				int iState = (int)_iUser;
				UpdateOutportItem(iOutportNo,iState);
			}
		}
	case WCM_ALARM_SCHEDULE_STATUS:
		{

			if (m_iLogonID == _iLogonID)
			{

				int iLogonID = HIWORD(_wParam);
				if (m_iLogonID == iLogonID)
				{
					int iInportNo = HIWORD((unsigned short)_iLParam);
					int iIndex = FindInportItem(iInportNo);
					if (iIndex >= 0)
					{
						int iType = LOWORD((unsigned short)_iLParam) >> 8;
						int iState = LOWORD((unsigned short)_iLParam) & 0xFF;
						UpdateScheduleStateItem(iIndex,iType,iState);
					}				
				}			
			}
		}
		break;
	}
}

void CLS_PowerEnvParamPage::OnMainNotify( WPARAM _wParam, LPARAM lParam )
{
	switch(_wParam)
	{
	case WCM_ALARM_INFORMATION:
		{
			AlarmInfoData* pData = (AlarmInfoData*)lParam;
			if (pData)
			{
				UpdateAlarmInfo(pData);			
			}
		}
		break;
	case WCM_ALARM_OUT_STATUS:
		{
 		}
	case WCM_ALARM_SCHEDULE_STATUS:
		{
		}
		break;
	}
}

BOOL CLS_PowerEnvParamPage::UpdateLiveDataItem( int _iOutportNo, char* _pcData)
{
	AlarmInConfig tConfig = {0};
	tConfig.iSize = sizeof(AlarmInConfig);
	tConfig.iInterfaceNo = _iOutportNo;
	int iRet = NetClient_GetAlarmConfig(m_iLogonID,-1,-1,CMD_ALARM_IN_CONFIG,&tConfig);
	if(0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_PowerEnvParamPage::UpdateAlarmInfo] GetAlarmConfig(%d,%d,,CMD_ALARM_IN_CONFIG) failed! Error(0x%08x)"
			,m_iLogonID,_iOutportNo,GetLastError());
		return FALSE;
	}

	//使能
	int iEnable = -1;
	iRet = NetClient_GetAlarmConfig(m_iLogonID, _iOutportNo, -1, CMD_DH_DEVICE_ENABLE, &iEnable);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "OperateInfo-TDGetAlarmConfig(Get EnableInfo error. iEnable %d)",iEnable);
	}

	int iIndex = FindScheduleItem(_iOutportNo);
	if (iEnable)
	{
		if (iIndex < 0)
		{
			CString strChannelNo;
			strChannelNo.Format(_T("%d"), _iOutportNo+1);
			iIndex = m_lstctrlSchedule.InsertItem(m_lstctrlSchedule.GetItemCount(),strChannelNo);
			m_lstctrlSchedule.SetItemText(iIndex,5, GetTextEx(IDS_DEBUG));
		}
		m_lstctrlSchedule.SetItemText(iIndex,1,tConfig.cName);
		m_lstctrlSchedule.SetItemText(iIndex,4,_pcData);		
	}
	else
	{
		if (iIndex >= 0)
		{
			m_lstctrlSchedule.DeleteItem(iIndex);
		}
	}	

	return TRUE;
}

void CLS_PowerEnvParamPage::OnNMClickLstDh(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int nItem = pNMListView->iItem;		//行号
	int nSub = 	pNMListView->iSubItem;	//列号
	int iCount = m_lstctrlSchedule.GetItemCount();
	if(nItem > iCount)	//该行没数据则返回
	{
		return;
	}
	if (nSub == 5)
	{
		CString strInportNo = m_lstctrlSchedule.GetItemText(nItem,n_ListAlarmData_No);
		int iInportNo = atoi((LPSTR)(LPCTSTR)strInportNo) - 1;

		AlarmInConfig tParam = {sizeof(tParam)};
		tParam.iInterfaceNo = iInportNo;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,iInportNo,-1,CMD_ALARM_IN_CONFIG,&tParam);
		if (0 != iRet)
		{
			return;
		}	
		switch (tParam.iInterfaceType)
		{
		case 1:	//开关量
			{
				CLS_DhDebugKGL dlgDebug;
				dlgDebug.Init(m_iLogonID,iInportNo);
				dlgDebug.DoModal();
			}
			break;
		case 2:	//模拟量
			{
				CLS_DhDebugMNL dlgDebug;
				dlgDebug.Init(m_iLogonID,iInportNo);
				dlgDebug.DoModal();
			}
			break;
		case 3:	//温湿度
			{
				CLS_DhDebugWSD dlgDebug;
				dlgDebug.Init(m_iLogonID,iInportNo);
				dlgDebug.DoModal();
			}
			break;
		}
	}
	*pResult = 0;
}

void CLS_PowerEnvParamPage::OnBnClickedChkDhSelall()
{
	for (int i=0; i<m_lstctrlSchedule.GetItemCount(); i++)
	{
		m_lstctrlSchedule.SetCheck(i,m_chkAllSchedule.GetCheck());
	}
}

void CLS_PowerEnvParamPage::OnBnClickedChkSwitchSelall()
{
	for (int i=0; i<m_lstctrlKey.GetItemCount(); i++)
	{
		m_lstctrlKey.SetCheck(i,m_chkAllKey.GetCheck());
	}
}

void CLS_PowerEnvParamPage::OnBnClickedBtnManualBf()
{
	ScheduleEnable(1);
}

void CLS_PowerEnvParamPage::OnBnClickedBtnManualSf()
{
	ScheduleEnable(0);
}

void CLS_PowerEnvParamPage::OnBnClickedBtnManualRecover()
{
	ScheduleEnable(2);
}

BOOL CLS_PowerEnvParamPage::ScheduleEnable(int _iValue )
{
	for (int i = 0; i < m_lstctrlSchedule.GetItemCount(); ++i)
	{
		if (m_lstctrlSchedule.GetCheck(i))
		{
			CString strInportNo = m_lstctrlSchedule.GetItemText(i,0);
			int iInportNo = atoi((LPSTR)(LPCTSTR)strInportNo) - 1;
			int iRet = NetClient_SetAlarmConfig(m_iLogonID,iInportNo,-1,CMD_ALARM_IN_SCHEDULE_ENABLE,&_iValue);
			if(0 != iRet)
			{
				AddLog(LOG_TYPE_FAIL,"","[CLS_PowerEnvParamPage::ScheduleEnable] SetAlarmConfig(%d,%d,,CMD_ALARM_IN_SCHEDULE_ENABLE,%d) failed! Error(0x%08x)"
					,m_iLogonID,iInportNo,_iValue);
			}
		}
	}
	return TRUE;
}

void CLS_PowerEnvParamPage::OnBnClickedBtnOpen()
{
	OutportEnable(1);
}

void CLS_PowerEnvParamPage::OnBnClickedBtnClose()
{
	OutportEnable(0);
}

BOOL CLS_PowerEnvParamPage::OutportEnable(int _iValue )
{
	for (int i = 0; i < m_lstctrlKey.GetItemCount(); ++i)
	{
		if (m_lstctrlKey.GetCheck(i))
		{
			CString strOutportNo = m_lstctrlKey.GetItemText(i,0);
			int iOutportNo = atoi((LPSTR)(LPCTSTR)strOutportNo) - 1;
			int iRet = NetClient_SetOutPortState(m_iLogonID,iOutportNo,_iValue);
			if(0 != iRet)
			{
				AddLog(LOG_TYPE_FAIL,"","[CLS_PowerEnvParamPage::OutportEnable] NetClient_SetOutportEnable(%d,%d,%d) failed! Error(0x%08x)"
					,m_iLogonID,iOutportNo,_iValue,GetLastError());
			}
		}
	}
	return TRUE;
}

int CLS_PowerEnvParamPage::GetAlarmStateID( int _iAlarmType)
{
	int iIDSAlarm = IDS_NORMAL;
	switch (_iAlarmType)
	{
	case ALARM_VDO_INPORT:
		{
			iIDSAlarm = IDS_ALARM_SWITCH;
		}
		break;
	case ALARM_ANALOG_UPPER_LIMIT_ON:
		{
			iIDSAlarm = IDS_ALARM_ANALOG_UPPER_LIMIT;
		}
		break;
	case ALARM_ANALOG_LOWER_LIMIT_ON:
		{
			iIDSAlarm = IDS_ALARM_ANALOG_LOWER_LIMIT;
		}
		break;
	case ALARM_TEMPERATURE_UPPER_LIMIT_ON:
		{
			iIDSAlarm = IDS_ALARM_TEMPERATURE_UPPER_LIMIT;
		}
		break;
	case ALARM_TEMPERATURE_LOWER_LIMIT_ON:
		{
			iIDSAlarm = IDS_ALARM_TEMPERATURE_LOWER_LIMIT;
		}
		break;
	case ALARM_HUMIDITY_UPPER_LIMIT_ON:
		{
			iIDSAlarm = IDS_ALARM_HUMIDITY_UPPER_LIMIT;
		}
		break;
	case ALARM_HUMIDITY_LOWER_LIMIT_ON:
		{
			iIDSAlarm = IDS_ALARM_HUMIDITY_LOWER_LIMIT;
		}
		break;
	default:
		break;
	}
	return iIDSAlarm;
}

int CLS_PowerEnvParamPage::FindInportItem( int _iInportNo )
{
	CString strInportNo;
	strInportNo.Format(_T("%d"),_iInportNo+1);
	LVFINDINFO tInfo = {0};
	tInfo.flags = LVFI_STRING;
	tInfo.psz = strInportNo;

	return m_lstctrlSchedule.FindItem(&tInfo,-1);
}

BOOL CLS_PowerEnvParamPage::UpdateAlarmInfo( AlarmInfoData* _pData )
{
	if (NULL == _pData)
	{
		return FALSE;
	}

	__try
	{
		int iInportNo = _pData->iChannelNo;
		int iIndex = FindInportItem(iInportNo);
		if (iIndex < 0)
		{
			return FALSE;
		}

		int iAlarmType = _pData->iAlarmState;
		int iScheduleState = _pData->iStatus;
		char* pcInfo = _pData->cInfo;

		int iInterfaceType = _pData->iDhInterfaceType;
		UpdateAlarmStateItem(iIndex,iInterfaceType,iAlarmType,n_AlarmState_Alarming);		
		UpdateLiveDataInfo(iInportNo,iInterfaceType,pcInfo,sizeof(_pData->cInfo));
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}

	return TRUE;
}

BOOL CLS_PowerEnvParamPage::UpdateLiveDataInfo( int _iInportNo,int _iInterfaceType,char* _pcInfo,int _iLen )
{
	int iIndex = FindInportItem(_iInportNo);
	if (iIndex < 0)
	{
		return FALSE;
	}	

	UpdateLiveDataItem(iIndex,_iInterfaceType,_pcInfo,_iLen);

	return TRUE;
}

BOOL CLS_PowerEnvParamPage::UpdateLiveDataItem( int _iIndex,int _iType,char* _pcInfo,int _iLen )
{
	if (NULL == _pcInfo)
	{
		return FALSE;
	}

	CString strInfo;
	strInfo.Format(_T("%s"),_pcInfo);
	CString strField;
	CString strLiveData;
	switch (_iType)
	{
	case ALARM_INTERFACE_TYPE_SWITCH:
		{
			SwitchData tData = {0};
			StringToStruct(strInfo,&tData);
			if (0 == tData.iState)
			{
				strLiveData = GetText(IDS_OUTPORT_STATE_OFF);
			}
			else
			{
				strLiveData = GetText(IDS_OUTPORT_STATE_ON);
			}
		}
		break;
	case ALARM_INTERFACE_TYPE_ANALOG:
		{
			AnalogData tData = {0};
			StringToStruct(strInfo,&tData);
			strLiveData.Format(_T("%0.2f%s"),(tData.iData-10000)*1.0/100,tData.cUnit);
		}
		break;
	case ALARM_INTERFACE_TYPE_COM:
		{
			ComData tData = {0};
			StringToStruct(strInfo,&tData);
			switch (tData.iType)
			{
			case n_TemperatureHumidity:
				{
					strLiveData.Format(_T("%s:%0.2f%s %s:%0.2f%s"),GetText(IDS_POWER_ENV_DEBUG_TEMPERATURE),(tData.iTemperature-10000)*1.0/100,tData.cTemUnit
						,GetText(IDS_POWER_ENV_DEBUG_HUMIDITY),(tData.iHumidity-10000)*1.0/100,tData.cHumUnit);
				}
				break;
			default:
				break;
			}					
		}
		break;
	default:
		break;
	}
	m_lstctrlSchedule.SetItemText(_iIndex,n_ListAlarmData_LiveData,strLiveData);		

	return TRUE;
}


BOOL CLS_PowerEnvParamPage::StringToStruct( CString _cstrSrc,SwitchData* _strctDest )
{
	if (NULL == _strctDest)
	{
		return FALSE;
	}

	_cstrSrc.AppendChar(',');
	static int s_iParamNum = 0;
	while(1)
	{
		int iIndex = _cstrSrc.Find(',');

 		if (iIndex < 0)
 		{
			s_iParamNum = 0;
			break;
 		}

		s_iParamNum++;
		CString cstrParam = _cstrSrc.Left(iIndex);

		int iParamIndex = cstrParam.Find('=');
		if (iParamIndex < 0)
		{
			s_iParamNum = 0;
			break;
		}
		CString strKey = cstrParam.Left(iParamIndex);
		CString strValue = cstrParam.Right(cstrParam.GetLength()-iParamIndex-1);

		switch (s_iParamNum)
		{
		case 1:
			_strctDest->iTime = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 2:
			_strctDest->iState = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		default:
			break;
		}

		_cstrSrc = _cstrSrc.Right(_cstrSrc.GetLength()-iIndex-1);
	}

	return TRUE;
}

BOOL CLS_PowerEnvParamPage::StringToStruct( CString _cstrSrc,AnalogData* _strctDest )
{
	if (NULL == _strctDest)
	{
		return FALSE;
	}

	_cstrSrc.AppendChar(',');
	static int s_iParamNum = 0;
	while(1)
	{
		int iIndex = _cstrSrc.Find(',');
		if (iIndex < 0)
		{
			s_iParamNum = 0;
			break;
		}

		s_iParamNum++;
		CString cstrParam = _cstrSrc.Left(iIndex);

		int iParamIndex = cstrParam.Find('=');
		if (iParamIndex < 0)
		{
			return FALSE;
		}
		CString strKey = cstrParam.Left(iParamIndex);
		CString strValue = cstrParam.Right(cstrParam.GetLength()-iParamIndex-1);

		switch (s_iParamNum)
		{
		case 1:
			_strctDest->iTime = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 2:
			_strctDest->iDistanceUpperLimit = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 3:
			_strctDest->iDistanceLowerLimit = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 4:
			_strctDest->iData = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 5:
			strcpy_s(_strctDest->cUnit,(LPSTR)(LPCTSTR)strValue);
			break;
		default:
			break;
		}
		_cstrSrc = _cstrSrc.Right(_cstrSrc.GetLength()-iIndex-1);
	}
	return TRUE;
}

BOOL CLS_PowerEnvParamPage::StringToStruct( CString _cstrSrc,ComData* _strctDest )
{
	if (NULL == _strctDest)
	{
		return FALSE;
	}

	_cstrSrc.AppendChar(',');
	static int s_iParamNum = 0;
	while(1)
	{
		int iIndex = _cstrSrc.Find(',');
		if (iIndex < 0)
		{
			s_iParamNum = 0;
			break;
		}

		s_iParamNum++;
		CString cstrParam = _cstrSrc.Left(iIndex);

		int iParamIndex = cstrParam.Find('=');
		if (iParamIndex < 0)
		{
			return FALSE;
		}
		CString strKey = cstrParam.Left(iParamIndex);
		CString strValue = cstrParam.Right(cstrParam.GetLength()-iParamIndex-1);

		switch (s_iParamNum)
		{
		case 1:
			_strctDest->iTime = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 2:
			_strctDest->iType = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 3:
			_strctDest->iTemperature = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 4:
			_strctDest->iTemAlarmStatus = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 5:
			strcpy_s(_strctDest->cTemUnit,(LPSTR)(LPCTSTR)strValue);
			break;
		case 6:
			_strctDest->iHumidity = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 7:
			_strctDest->iHumAlarmStatus = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 8:
			strcpy_s(_strctDest->cHumUnit,(LPSTR)(LPCTSTR)strValue);
			break;
		default:
			break;
		}
		_cstrSrc = _cstrSrc.Right(_cstrSrc.GetLength()-iIndex-1);
	}
	return TRUE;
}

