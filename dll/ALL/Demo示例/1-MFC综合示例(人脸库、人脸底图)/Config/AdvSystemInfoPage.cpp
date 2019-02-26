// AdvSystemInfoPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "AdvSystemInfoPage.h"

#define TELNET_ENABLE	1
#define TELNET_DISABLE	0
#define SYSTEM_MODE24   0
#define SYSTEM_MODE12   1

// CLS_AdvSystemInfoPage dialog

IMPLEMENT_DYNAMIC(CLS_AdvSystemInfoPage, CDialog)

CLS_AdvSystemInfoPage::CLS_AdvSystemInfoPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AdvSystemInfoPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_blTelnetClose = TRUE;
	m_iChannelNo = -1;
}

CLS_AdvSystemInfoPage::~CLS_AdvSystemInfoPage()
{
}

void CLS_AdvSystemInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBoxTimeFormat);
	DDX_Control(pDX, IDC_COMBO_CONNECT_INFO, m_ComboBoxConnInfo);
	DDX_Control(pDX, IDC_LIST1, m_lstCtConnectInfo);
	DDX_Control(pDX, IDC_COMBO3, m_ComboBoxSeparate);
	DDX_Control(pDX, IDC_COMBO_TIMEMODE, m_cboTimeMode);
	DDX_Control(pDX, IDC_CHECK_WEEKDIS, m_chkWeekDis);
	DDX_Radio(pDX, IDC_RADIO_ADV_SYS_TELNET_OPEN, m_blTelnetClose);
	DDX_Control(pDX, IDC_CBO_ALGORITHM_TYPE, m_cboAlgorithmType);
}


BEGIN_MESSAGE_MAP(CLS_AdvSystemInfoPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADV_SYS_SET_TIME, &CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysSetTime)
	ON_BN_CLICKED(IDC_BUTTON_ADV_SYS_DEFAULT, &CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysDefault)
	ON_BN_CLICKED(IDC_BUTTON_ADV_SYS_REBOOT, &CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysReboot)
	ON_BN_CLICKED(IDC_BUTTON_ADV_SYS_SHUTDOWN, &CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysShutdown)
	ON_BN_CLICKED(IDC_BUTTON_TIME_FORMAT_SET, &CLS_AdvSystemInfoPage::OnBnClickedButtonTimeFormatSet)
	ON_CBN_SELCHANGE(IDC_COMBO_CONNECT_INFO, &CLS_AdvSystemInfoPage::OnCbnSelchangeComboConnectInfo)
	ON_BN_CLICKED(IDC_BUTTON_ADV_SYS_REFRESH, &CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysRefresh)
	ON_BN_CLICKED(IDC_RADIO_ADV_SYS_TELNET_OPEN, &CLS_AdvSystemInfoPage::OnBnClickedRadioAdvSysTelnetSet)
	ON_BN_CLICKED(IDC_RADIO_ADV_SYS_TELNET_CLOSE, &CLS_AdvSystemInfoPage::OnBnClickedRadioAdvSysTelnetSet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SET_ALG_TYPE, &CLS_AdvSystemInfoPage::OnBnClickedSetAlgType)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATE, &CLS_AdvSystemInfoPage::OnBnClickedButtonCalibrate)
END_MESSAGE_MAP()


// CLS_AdvSystemInfoPage message handlers



void CLS_AdvSystemInfoPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? 0 : _iChannelNo;
	UI_UpdateText();
	UI_UpdateTimeFormat();
	UI_UpdateAlgType();
}

void CLS_AdvSystemInfoPage::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_BUTTON_ADV_SYS_SET_TIME, IDS_ADV_SYSTEM__TIME_SET);
	SetDlgItemTextEx(IDC_BUTTON_ADV_SYS_DEFAULT, IDS_ADV_SYSTEM_DEFAULT);
	SetDlgItemTextEx(IDC_BUTTON_ADV_SYS_REBOOT, IDS_ADV_SYSTEM_REBOOT);
	SetDlgItemTextEx(IDC_BUTTON_ADV_SYS_SHUTDOWN, IDS_ADV_SYSTEM_SHUTDOWN);
	SetDlgItemTextEx(IDC_BUTTON_CALIBRATE, IDS_CAMRA_CALIBRATE);	

	m_ComboBoxConnInfo.ResetContent();
	m_ComboBoxConnInfo.AddString(GetTextEx(IDS_ADV_SYSTEM_LOGON_INFO));
	m_ComboBoxConnInfo.AddString(GetTextEx(IDS_ADV_SYSTEM_CONNECT_INFO));
	m_ComboBoxConnInfo.SetCurSel(0);

	m_cboTimeMode.ResetContent();
	m_cboTimeMode.SetItemData(m_cboTimeMode.AddString(GetTextEx(IDS_ADV_SYSTEM_24MODE)), SYSTEM_MODE24);
	m_cboTimeMode.SetItemData(m_cboTimeMode.AddString(GetTextEx(IDS_ADV_SYSTEM_12MODE)), SYSTEM_MODE12);

	UI_UpdateTimeFormat();
	UI_UpdateConnInfoList();
	SetDlgItemTextEx(IDC_BUTTON_ADV_SYS_REFRESH, IDS_ADV_CONNECT_INFO_REFRESH);
	SetDlgItemTextEx(IDC_STATIC_ADV_CONNECT_INFO, IDS_ADV_CONNECT_INFO);
	SetDlgItemTextEx(IDC_BUTTON_TIME_FORMAT_SET, IDS_ADV_SYSTEM_TIME_FORMAT_SET);

	SetDlgItemTextEx(IDC_STATIC_TIMEMODE, IDS_ADV_SYSTEM_TIMEMODE);
 	SetDlgItemTextEx(IDC_STC_ADV_SYS_TELNET_SET, IDS_ADVANCE_SYSTEM_INFO_TELNET);
 	SetDlgItemTextEx(IDC_STATIC, IDS_HOLIDAY_PLAN_MODE);
	SetDlgItemTextEx(IDC_CHECK_WEEKDIS, IDS_ADV_SYSTEM_WEEKDIS);

	SetDlgItemTextEx(IDC_RADIO_ADV_SYS_TELNET_OPEN, IDS_CONFIG_OPEN);
	SetDlgItemTextEx(IDC_RADIO_ADV_SYS_TELNET_CLOSE, IDS_CONFIG_CLOSE);

	int iTempSel = m_cboAlgorithmType.GetCurSel();
	m_cboAlgorithmType.ResetContent();
	m_cboAlgorithmType.SetItemData(m_cboAlgorithmType.AddString(GetTextEx(IDS_MONITO)), ALGORITHM_TYPE_MONITOR);
	m_cboAlgorithmType.SetItemData(m_cboAlgorithmType.AddString(GetTextEx(IDS_TRAFFIC_ALG)), ALGORITHM_TYPE_TRAFFIC);
	iTempSel = (m_cboAlgorithmType.GetCount() > iTempSel) ? iTempSel : 0;
	m_cboAlgorithmType.SetCurSel(iTempSel);
	SetDlgItemTextEx(IDC_STC_ALGORITHM_TYPE, IDS_ITS_ALGTYPE_TYPE);
	SetDlgItemTextEx(IDC_SET_ALG_TYPE, IDS_SET);
}

void CLS_AdvSystemInfoPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateText();
}

void CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysSetTime()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return;
	}
	SYSTEMTIME tCurrent;
 	GetLocalTime(&tCurrent);
	int iRet = NetClient_SetTime(m_iLogonID, tCurrent.wYear, tCurrent.wMonth, tCurrent.wDay,
		tCurrent.wHour, tCurrent.wMinute, tCurrent.wSecond);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);	
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "","NetClient_SetTime(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
}

void CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysDefault()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return;
	}
	int iRet = NetClient_DefaultPara(m_iLogonID);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "","NetClient_DefaultPara(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
}

void CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysReboot()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return;
	}
	int iRet = NetClient_Reboot(m_iLogonID);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "","NetClient_DefaultPara(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
}

void CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysShutdown()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return;
	}
	int iRet = NetClient_ShutDownDev(m_iLogonID, 0);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "","NetClient_DefaultPara(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
}

void CLS_AdvSystemInfoPage::UI_UpdateTimeFormat()
{
	if (m_iLogonID < 0)
	{
		return;
	}
	int iBytesReturned = 0;
	TDateFormat tDateFormat = {0};
	tDateFormat.iSize = sizeof(TDateFormat);
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DATE_FORMATE, 0x7FFFFFFF, &tDateFormat, sizeof(tDateFormat), &iBytesReturned);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig faied! Logon id(%d)", m_iLogonID);
	}
	else
	{	
		m_ComboBoxTimeFormat.SetCurSel(tDateFormat.iFormatType);
		m_ComboBoxSeparate.SelectString(-1, &tDateFormat.cSeparate);
		m_cboTimeMode.SetCurSel((int)m_cboTimeMode.GetItemData(tDateFormat.iTimeMode));
		
		m_chkWeekDis.SetCheck(tDateFormat.iFlagWeek);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig success! Logon id(%d)", m_iLogonID);
	}
}
BOOL CLS_AdvSystemInfoPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ComboBoxTimeFormat.AddString("yyyy/mm/dd");
	m_ComboBoxTimeFormat.AddString("mm/dd/yyyy");
	m_ComboBoxTimeFormat.AddString("dd/mm/yyyy");
	m_ComboBoxTimeFormat.AddString("M. day yyyy");
	m_ComboBoxTimeFormat.AddString("day M. yyyy");
	m_ComboBoxTimeFormat.SetCurSel(0);

	m_ComboBoxSeparate.AddString("/");
	m_ComboBoxSeparate.AddString("-");
	m_ComboBoxSeparate.AddString(".");
	m_ComboBoxSeparate.SetCurSel(0);

	m_cboTimeMode.ResetContent();
	m_cboTimeMode.SetItemData(m_cboTimeMode.AddString(GetTextEx(IDS_ADV_SYSTEM_24MODE)), SYSTEM_MODE24);
	m_cboTimeMode.SetItemData(m_cboTimeMode.AddString(GetTextEx(IDS_ADV_SYSTEM_12MODE)), SYSTEM_MODE12);


	m_chkWeekDis.SetCheck(FALSE);

	m_lstCtConnectInfo.SetExtendedStyle(m_lstCtConnectInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	UI_UpdateTimeFormat();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_AdvSystemInfoPage::OnBnClickedButtonTimeFormatSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return;
	}
	CString szSeparate;
	m_ComboBoxSeparate.GetLBText(m_ComboBoxSeparate.GetCurSel(), szSeparate);
	TDateFormat tDateFormat = {0};
	tDateFormat.iSize = sizeof(TDateFormat);
	tDateFormat.iFormatType = m_ComboBoxTimeFormat.GetCurSel();
	memcpy(&tDateFormat.cSeparate, szSeparate.GetBuffer(), 1);
	tDateFormat.iTimeMode =  (int)m_cboTimeMode.GetItemData(m_cboTimeMode.GetCurSel());
	tDateFormat.iFlagWeek = m_chkWeekDis.GetCheck();

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DATE_FORMATE, 0x7FFFFFFF, &tDateFormat, sizeof(tDateFormat));
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice((m_iLogonID));
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig(%s, %d)", Device->cIP, m_iLogonID);
		}
	}

}

BOOL CLS_AdvSystemInfoPage::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CLS_BasePage::DestroyWindow();
}

void CLS_AdvSystemInfoPage::UI_UpdateConnInfoList()
{
	m_lstCtConnectInfo.DeleteAllItems();
	m_lstCtConnectInfo.DeleteColumn(2);
	m_lstCtConnectInfo.DeleteColumn(2);
	if (m_ComboBoxConnInfo.GetCurSel())
	{
		int iColumnIndex = 0;
		InsertColumn( m_lstCtConnectInfo, iColumnIndex++, IDS_ADV_CONNECT_INFO_CLIENT_IP, LVCFMT_LEFT, 80 );//插入列
		InsertColumn( m_lstCtConnectInfo, iColumnIndex++, IDS_ADV_CONNECT_INFO_USERNAME, LVCFMT_LEFT, 80 );
		InsertColumn( m_lstCtConnectInfo, iColumnIndex++, IDS_ADV_CONNECT_INFO_CHANNEL, LVCFMT_LEFT, 200 );
		InsertColumn( m_lstCtConnectInfo, iColumnIndex++, IDS_ADV_CONNECT_INFO_NETMODE, LVCFMT_LEFT, 70 );
		InsertColumn( m_lstCtConnectInfo, iColumnIndex++, IDS_LOG_STATUS, LVCFMT_LEFT, 70 );
	}
	else
	{
		int iColumnIndex = 0;
		InsertColumn( m_lstCtConnectInfo, iColumnIndex++, IDS_ADV_CONNECT_INFO_CLIENT_IP, IDS_ADV_CONNECT_INFO_CLIENT_IP, 80 );//插入列
		InsertColumn( m_lstCtConnectInfo, iColumnIndex++, IDS_ADV_CONNECT_INFO_USERNAME, LVCFMT_LEFT, 80 );
	}
	UpdateConnInfoList();
}


void CLS_AdvSystemInfoPage::OnCbnSelchangeComboConnectInfo()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return;
	}
	UI_UpdateConnInfoList();
}

void CLS_AdvSystemInfoPage::UpdateConnInfoList()
{
	TTotalConnectInfo svc = {0};
	int iChannelNum = 0;
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);	
		if(Device)
		{
			AddLog(LOG_TYPE_FAIL, "","NetClient_GetChannelNum(%s, %d)", Device->cIP, m_iLogonID);	
		}
		return;
	}

	iRet = NetClient_GetConnectInfo(m_iLogonID, &svc, sizeof(svc));
	if (iRet < 0)
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);	
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "","NetClient_GetConnectInfo(%s, %d)", Device->cIP, m_iLogonID);	
		}
	}
	else
	{
		if (m_ComboBoxConnInfo.GetCurSel())
		{
			int iRow = 0;
			for (int i = 0; i < MAX_CONNECT_COUNT; i++)
			{
				if (strcmp(svc.connInfo[i].cClientIP, "") == 0 || svc.connInfo[i].iChannelType == 0)
				{
					continue;
				}
				m_lstCtConnectInfo.InsertItem(iRow, "");
				int iColumn = 0;
				m_lstCtConnectInfo.SetItemText(iRow, iColumn++, svc.connInfo[i].cClientIP);
				m_lstCtConnectInfo.SetItemText(iRow, iColumn++, svc.connInfo[i].cUserName);
				CString szChannel;
				if (svc.connInfo[i].iChannelID/iChannelNum == 0)
				{
					szChannel.Format("MainStream Channel%d", svc.connInfo[i].iChannelID);
				}
				else if(svc.connInfo[i].iChannelID/iChannelNum == 1)
				{
					szChannel.Format("SubStream Channel%d", svc.connInfo[i].iChannelID%iChannelNum);
				}
				else if (svc.connInfo[i].iChannelID/iChannelNum == 2)
				{
					szChannel.Format("InterTalk Channel");
				}
				else if(svc.connInfo[i].iChannelID/iChannelNum == 4)
				{
					szChannel.Format("Picture Channel");
				}
				else
				{
					szChannel.Format("Download Channel");
				}

				m_lstCtConnectInfo.SetItemText(iRow, iColumn++, szChannel);
				if (svc.connInfo[i].iNetMode == 4)
				{
					m_lstCtConnectInfo.SetItemText(iRow, iColumn++, "Avtive");
				}
				else if (svc.connInfo[i].iNetMode == 3)
				{
					m_lstCtConnectInfo.SetItemText(iRow, iColumn++, "Multiple");
				}
				else if (svc.connInfo[i].iNetMode == 2)
				{
					m_lstCtConnectInfo.SetItemText(iRow, iColumn++, "UDP");
				}
				else
				{
					m_lstCtConnectInfo.SetItemText(iRow, iColumn++, "TCP");
				}

				CString cstrConnectStatus;
				cstrConnectStatus = (0 == svc.connInfo[i].iConnectState) ? GetTextEx(IDS_MENU_CONNECT) : GetTextEx(IDS_MENU_DISCONNECT);
				m_lstCtConnectInfo.SetItemText(iRow, iColumn++, cstrConnectStatus);

				iRow ++;
			}
		}
		else
		{
			int iRow = 0;
			for (int i = 0; i < MAX_CONNECT_COUNT; i++)
			{
				if (strcmp(svc.connInfo[i].cClientIP, "") == 0 || svc.connInfo[i].iChannelType == 1)
				{
					continue;
				}
				m_lstCtConnectInfo.InsertItem(iRow, "");
				int iColumn = 0;
				m_lstCtConnectInfo.SetItemText(iRow, iColumn++, svc.connInfo[i].cClientIP);
				m_lstCtConnectInfo.SetItemText(iRow, iColumn++, svc.connInfo[i].cUserName);
				iRow ++;
			}
		}
	}
}
void CLS_AdvSystemInfoPage::OnBnClickedButtonAdvSysRefresh()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return;
	}
	UI_UpdateConnInfoList();
}

void CLS_AdvSystemInfoPage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	int iMsgType = _wParam & 0xFFFF;
	switch(iMsgType)
	{
	case WCM_CONNECT_INFO:
		{
			NVS_IPAndID* pIPID = (NVS_IPAndID*)_iLParam;
			int iLogonID = *pIPID->m_piLogonID;
			if (m_iLogonID == iLogonID)
			{
				UI_UpdateConnInfoList();
			}
		}
		break;
	default:
		break;
	}
}

void CLS_AdvSystemInfoPage::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	if (PARA_DEV_TELNET == _iParaType)
	{
		BOOL blIsOpen = 0;
		NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_TELNET, 0x7FFFFFFF, &blIsOpen);
		m_blTelnetClose = !blIsOpen;
		UpdateData(FALSE);
	}	
}

void CLS_AdvSystemInfoPage::OnBnClickedRadioAdvSysTelnetSet()
{
	int iTelnetStatus = m_blTelnetClose;
	UpdateData();
	if (iTelnetStatus == m_blTelnetClose)
	{
		return;
	}

	NetClient_SetCommonEnable(m_iLogonID, CI_COMMON_ID_TELNET, 0x7FFFFFFF, !m_blTelnetClose);
}

void CLS_AdvSystemInfoPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		BOOL blIsOpen = 0;
		NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_TELNET, 0x7FFFFFFF, &blIsOpen);
		m_blTelnetClose = !blIsOpen;
		UpdateData(FALSE);
	}
}

void CLS_AdvSystemInfoPage::UI_UpdateAlgType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}
	AlgorithmType tAlgorithmType = {0};
	tAlgorithmType.iSize = sizeof(AlgorithmType);
	int iByteReturn = 0;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ALGORITHM_TYPE, m_iChannelNo, &tAlgorithmType, sizeof(AlgorithmType), &iByteReturn);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","GetDevConfig AlgorithmType(%d,%d)",m_iLogonID, m_iChannelNo);
		goto EXIT_FUNC;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","GetDevConfig AlgorithmType(%d,%d)",m_iLogonID, m_iChannelNo);
	} 

	m_cboAlgorithmType.SetCurSel(GetCboSel(&m_cboAlgorithmType, tAlgorithmType.iAlgorithmType));

EXIT_FUNC:
	return;
}

void CLS_AdvSystemInfoPage::OnBnClickedSetAlgType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}
	AlgorithmType tAlgorithmType = {0};
	tAlgorithmType.iSize = sizeof(AlgorithmType);
	tAlgorithmType.iAlgorithmType = (int)m_cboAlgorithmType.GetItemData(m_cboAlgorithmType.GetCurSel());

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_ALGORITHM_TYPE, m_iChannelNo, &tAlgorithmType, sizeof(AlgorithmType));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","SetDevConfig AlgorithmType(%d,%d)",m_iLogonID, m_iChannelNo);
		goto EXIT_FUNC;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","SetDevConfig AlgorithmType(%d,%d)",m_iLogonID, m_iChannelNo);
	} 

EXIT_FUNC:
	return;
}

void CLS_AdvSystemInfoPage::OnBnClickedButtonCalibrate()
{
	int iTestType = 1;
	int iTestEnable = 1;

	int iRet = NetClient_CheckCamera(m_iLogonID, m_iChannelNo, iTestType, iTestEnable);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_CheckCamera(%d,%d)",m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_CheckCamera(%d,%d)",m_iLogonID, m_iChannelNo);
	}

}
