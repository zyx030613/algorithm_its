// Config\ATMPage.cpp : implementation file
//

#include "stdafx.h"
#include "ATMPage.h"


// CLS_ATMPage dialog

IMPLEMENT_DYNAMIC(CLS_ATMPage, CDialog)

CLS_ATMPage::CLS_ATMPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ATMPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_ATMPage::~CLS_ATMPage()
{
}

void CLS_ATMPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ATM_OSDENABLE, m_edtOsdEnable);
	DDX_Control(pDX, IDC_EDIT_ATM_X, m_edtOsdX);
	DDX_Control(pDX, IDC_EDIT_ATM_Y, m_edtOsdY);
	DDX_Control(pDX, IDC_COMBO_ATM_INFORMWAY, m_cmbInformWay);
	DDX_Control(pDX, IDC_COMBO_PROTOCOLNAME, m_cmbProtocolName);
	DDX_Control(pDX, IDC_EDIT_ATM_STRIP, m_edtSrcIP);
	DDX_Control(pDX, IDC_EDIT_ATM_STRPORT, m_edtSrcPort);
	DDX_Control(pDX, IDC_EDIT_ATM_DESTIP, m_edtDestIP);
	DDX_Control(pDX, IDC_EDIT_ATM_DESTPORT, m_edtDestPort);
	DDX_Control(pDX, IDC_COMBO_ATM_COM, m_cmbComNo);
	DDX_Control(pDX, IDC_COMBO_ATM_WORKMODE, m_cmbWorkMode);
	DDX_Control(pDX, IDC_EDIT_ATM_COMFORMAT, m_edtComFormat);
}


BEGIN_MESSAGE_MAP(CLS_ATMPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ATMINFO_SET, &CLS_ATMPage::OnBnClickedButtonAtminfoSet)
	ON_CBN_SELCHANGE(IDC_COMBO_ATM_INFORMWAY, &CLS_ATMPage::OnCbnSelchangeComboAtmInformway)
END_MESSAGE_MAP()


// CLS_ATMPage message handlers
BOOL CLS_ATMPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_edtOsdEnable.SetLimitText(2);
	m_edtOsdX.SetLimitText(5);
	m_edtOsdY.SetLimitText(5);
	m_edtSrcIP.SetLimitText(16);
	m_edtDestIP.SetLimitText(16);
	m_edtSrcPort.SetLimitText(5);
	m_edtDestPort.SetLimitText(5);
	m_cmbInformWay.SetCurSel(0);
	m_edtSrcIP.ShowWindow(false);
	GetDlgItem(IDC_STATIC_ATM_SRCIP)->ShowWindow(false);
	m_edtSrcPort.ShowWindow(false);
	GetDlgItem(IDC_STATIC_ATM_SRCPORT)->ShowWindow(false);
	m_edtDestIP.ShowWindow(false);
	GetDlgItem(IDC_STATIC_ATM_DESTIP)->ShowWindow(false);
	m_edtDestPort.ShowWindow(false);
	GetDlgItem(IDC_STATIC_ATM_DESTPORT)->ShowWindow(false);
	UI_UpdateDialog();
	return TRUE;
}

void CLS_ATMPage::OnChannelChanged(int _iLogonID, int /*_iChannelNo*/, int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	UI_UpdateATMInfo(-1);
}

void CLS_ATMPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ATMPage::OnBnClickedButtonAtminfoSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	ATM_OSD_INFO tATMOSDInfo = {sizeof(ATM_OSD_INFO)};
	tATMOSDInfo.uEnable = GetDlgItemInt(IDC_EDIT_ATM_OSDENABLE,NULL,FALSE);
	tATMOSDInfo.iX = GetDlgItemInt(IDC_EDIT_ATM_X);
	tATMOSDInfo.iY = GetDlgItemInt(IDC_EDIT_ATM_Y);
	SetDlgItemInt(IDC_EDIT_ATM_Y,tATMOSDInfo.iY);
	if (tATMOSDInfo.iY < -1)
	{
		MessageBox("Please input a valid Y value", "Warn", MB_OK|MB_TOPMOST);
		return;
	}

	int iRet = NetClient_SetATMConfig(m_iLogonID, ATM_CONFIG_CMD_OSD_INFO, &tATMOSDInfo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetATMConfig(%d,OSD_INFO)", m_iLogonID);
	}
	else 
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetATMConfig(%d,OSD_INFO)", m_iLogonID);
	}

	ATM_INFO tATMInfo = {sizeof(ATM_INFO)};
	tATMInfo.iInformWay = m_cmbInformWay.GetCurSel();
	m_cmbProtocolName.GetWindowText(tATMInfo.cProtocolName,sizeof(tATMInfo.cProtocolName));
	m_edtSrcIP.GetWindowText(tATMInfo.cSrcIP,sizeof(tATMInfo.cSrcIP));
	tATMInfo.iSrcPort = GetDlgItemInt(IDC_EDIT_ATM_STRPORT);
	m_edtDestIP.GetWindowText(tATMInfo.cDestIP,sizeof(tATMInfo.cDestIP));
	tATMInfo.iDestPort = GetDlgItemInt(IDC_EDIT_ATM_DESTPORT);
	if (strlen(tATMInfo.cProtocolName) <= 0)
	{
		MessageBox("Please select a protocol name", "Warn", MB_OK|MB_TOPMOST);
		return;
	}
	
	if(1 == tATMInfo.iInformWay)
	{
		if(1 != IsValidIP(tATMInfo.cSrcIP))
		{
			MessageBox("Please input a valid src ip", "Warn", MB_OK|MB_TOPMOST);
			return;
		}
		if(tATMInfo.iSrcPort < 81 || tATMInfo.iSrcPort > 65535)
		{
			MessageBox("Please input a valid src port,between 81 and 65535", "Warn", MB_OK|MB_TOPMOST);
			return;
		}
		if(1 != IsValidIP(tATMInfo.cDestIP))
		{
			MessageBox("Please input a valid dest ip", "Warn", MB_OK|MB_TOPMOST);
			return;
		}
		if(tATMInfo.iDestPort < 81 || tATMInfo.iDestPort > 65535)
		{
			MessageBox("Please input a valid dest port,between 81 and 65535", "Warn", MB_OK |MB_TOPMOST);
			return;
		}
	}

	int iTmp = NetClient_SetATMConfig(m_iLogonID, ATM_CONFIG_CMD_ATM_INFO, &tATMInfo);
	if (0 == iTmp)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetATMConfig(%d,ATM_INFO)", m_iLogonID);
	}
	else 
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetATMConfig(%d,ATM_INFO)", m_iLogonID);
	}
}

void CLS_ATMPage::OnCbnSelchangeComboAtmInformway()
{
	int iInfowayIdex = m_cmbInformWay.GetCurSel();
	if (0 == iInfowayIdex)
	{
		m_edtSrcIP.ShowWindow(false);
		GetDlgItem(IDC_STATIC_ATM_SRCIP)->ShowWindow(false);
		m_edtSrcPort.ShowWindow(false);
		GetDlgItem(IDC_STATIC_ATM_SRCPORT)->ShowWindow(false);
		m_edtDestIP.ShowWindow(false);
		GetDlgItem(IDC_STATIC_ATM_DESTIP)->ShowWindow(false);
		m_edtDestPort.ShowWindow(false);
		GetDlgItem(IDC_STATIC_ATM_DESTPORT)->ShowWindow(false);
		m_cmbComNo.ShowWindow(true);
		GetDlgItem(IDC_STATIC_ATM_COM)->ShowWindow(true);
		m_cmbWorkMode.ShowWindow(true);
		GetDlgItem(IDC_STATIC_ATM_WORKMODE)->ShowWindow(true);
		m_edtComFormat.ShowWindow(true);
		GetDlgItem(IDC_STATIC_ATM_COMFORMAT)->ShowWindow(true);
	}
	else//UDP
	{
		m_edtSrcIP.ShowWindow(true);
		GetDlgItem(IDC_STATIC_ATM_SRCIP)->ShowWindow(true);
		m_edtSrcPort.ShowWindow(true);
		GetDlgItem(IDC_STATIC_ATM_SRCPORT)->ShowWindow(true);
		m_edtDestIP.ShowWindow(true);
		GetDlgItem(IDC_STATIC_ATM_DESTIP)->ShowWindow(true);
		m_edtDestPort.ShowWindow(true);
		GetDlgItem(IDC_STATIC_ATM_DESTPORT)->ShowWindow(true);
		m_cmbComNo.ShowWindow(false);
		GetDlgItem(IDC_STATIC_ATM_COM)->ShowWindow(false);
		m_cmbWorkMode.ShowWindow(false);
		GetDlgItem(IDC_STATIC_ATM_WORKMODE)->ShowWindow(false);
		m_edtComFormat.ShowWindow(false);
		GetDlgItem(IDC_STATIC_ATM_COMFORMAT)->ShowWindow(false);
	}
	UI_UpdateATMInfo(iInfowayIdex);
}

void CLS_ATMPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ATM_INFORMWAY, IDS_CONFIG_ATM_INRORMWAY);
	SetDlgItemTextEx(IDC_STATIC_ATM_PROTOCOLNAME, IDS_CONFIG_ATM_PROTOCOLNAME);
	SetDlgItemTextEx(IDC_STATIC_ATM_ENABLE, IDS_CONFIG_ATM_OSDENABLE);
	SetDlgItemTextEx(IDC_STATIC_ATM_X, IDS_CONFIG_ATM_OSDX);
	SetDlgItemTextEx(IDC_STATIC_ATM_Y, IDS_CONFIG_ATM_OSDY);
	SetDlgItemTextEx(IDC_STATIC_ATM_COM, IDS_CONFIG_ATM_COM);
	SetDlgItemTextEx(IDC_STATIC_ATM_WORKMODE, IDS_CONFIG_ATM_WORKMODE);
	SetDlgItemTextEx(IDC_STATIC_ATM_COMFORMAT, IDS_CONFIG_ATM_COMFORMAT);
	SetDlgItemTextEx(IDC_STATIC_ATM_SRCIP, IDS_CONFIG_ATM_SRCIP);
	SetDlgItemTextEx(IDC_STATIC_ATM_SRCPORT, IDS_CONFIG_ATM_SRCPORT);
	SetDlgItemTextEx(IDC_STATIC_ATM_DESTIP, IDS_CONFIG_ATM_DESTIP);
	SetDlgItemTextEx(IDC_STATIC_ATM_DESTPORT, IDS_CONFIG_ATM_DESTPORT);
	SetDlgItemTextEx(IDC_BUTTON_ATMINFO_SET, IDS_CFG_USER_SET);
}

void CLS_ATMPage::UI_UpdateATMInfo(int _iInformWay)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	ATM_INFO tATMInfo = {sizeof(ATM_INFO)};
	int iRet = NetClient_GetATMConfig(m_iLogonID, ATM_CONFIG_CMD_ATM_INFO, &tATMInfo);
	if(0 == iRet)
	{
		int iCount = 0;
		m_cmbProtocolName.ResetContent();
		if(_iInformWay < 0)
		{
			_iInformWay = tATMInfo.iInformWay;
			if (_iInformWay > 1)
			{
				_iInformWay = 1;
			}
		}

		iRet = NetClient_GetATMConfig(m_iLogonID, ATM_CONFIG_CMD_PROTOCOL_COUNT, &iCount);
		if(0 == iRet)
		{
			for(int i = 0; i < iCount; ++i)
			{
				ATM_PROTOCOL_NAME tProtocolName = {sizeof(ATM_PROTOCOL_NAME), i};
				if(0 == NetClient_GetATMConfig(m_iLogonID, ATM_CONFIG_CMD_PROTOCOL_NAME, &tProtocolName))
				{
					m_cmbProtocolName.AddString(tProtocolName.cName);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","GetATMConfig(%d,PROTOCOL_NAME,%d)", m_iLogonID,i);
				}
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","GetATMConfig(%d,PROTOCOL_COUNT,%d)", m_iLogonID,iCount);
		}
		m_cmbInformWay.SetCurSel(_iInformWay);
		m_cmbProtocolName.SelectString(-1,tATMInfo.cProtocolName);

		ATM_OSD_INFO tATMOSDInfo = {sizeof(ATM_OSD_INFO)};
		if(0 == NetClient_GetATMConfig(m_iLogonID, ATM_CONFIG_CMD_OSD_INFO, &tATMOSDInfo))
		{
			SetDlgItemInt(IDC_EDIT_ATM_OSDENABLE, tATMOSDInfo.uEnable,FALSE);
			SetDlgItemInt(IDC_EDIT_ATM_X, tATMOSDInfo.iX);
			SetDlgItemInt(IDC_EDIT_ATM_Y, tATMOSDInfo.iY);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "GetATMConfig(%d,OSD_INFO)", m_iLogonID);
		}

		if(0 == _iInformWay)   //COM
		{
			int iRet = -1;
			int iComPortCounts = 0;
			int	iComPortStatus = 0;
			iRet = NetClient_GetComPortCounts(m_iLogonID, &iComPortCounts, &iComPortStatus);
			if (0 != iRet)
			{
				int iCurTypeModel;
				NetClient_GetProductType(m_iLogonID, &iCurTypeModel);
				iCurTypeModel = iCurTypeModel & 0xFFFF;
				if (IsDVR(iCurTypeModel))
				{
					iComPortCounts = 4;
				}
				else
				{
					iComPortCounts = 2;
				}
			}

			char cComFormat[32] = {0};
			int iWorkMode = 0;
			CString strComPort;
			m_cmbComNo.ResetContent();
			m_edtComFormat.SetWindowText("");
			m_cmbWorkMode.SetCurSel(-1);
			for (int i = 0; i < iComPortCounts; ++i)
			{
				strComPort.Format(_T("COM%d"), i+1);
				m_cmbComNo.AddString(strComPort);
				if(0 == NetClient_GetComFormat(m_iLogonID, i+1, cComFormat, &iWorkMode) && 7 == iWorkMode)
				{
					m_cmbComNo.SetCurSel(i);
					m_edtComFormat.SetWindowText(cComFormat);
					m_cmbWorkMode.SetCurSel(iWorkMode-1);
				}
			}

			m_edtSrcIP.ShowWindow(false);
			GetDlgItem(IDC_STATIC_ATM_SRCIP)->ShowWindow(false);
			m_edtSrcPort.ShowWindow(false);
			GetDlgItem(IDC_STATIC_ATM_SRCPORT)->ShowWindow(false);
			m_edtDestIP.ShowWindow(false);
			GetDlgItem(IDC_STATIC_ATM_DESTIP)->ShowWindow(false);
			m_edtDestPort.ShowWindow(false);
			GetDlgItem(IDC_STATIC_ATM_DESTPORT)->ShowWindow(false);
			m_cmbComNo.ShowWindow(true);
			GetDlgItem(IDC_STATIC_ATM_COM)->ShowWindow(true);
			m_cmbWorkMode.ShowWindow(true);
			GetDlgItem(IDC_STATIC_ATM_WORKMODE)->ShowWindow(true);
			m_edtComFormat.ShowWindow(true);
			GetDlgItem(IDC_STATIC_ATM_COMFORMAT)->ShowWindow(true);
		}
		else     //UDP
		{
			m_edtSrcIP.SetWindowText(tATMInfo.cSrcIP);
			SetDlgItemInt(IDC_EDIT_ATM_STRPORT, tATMInfo.iSrcPort);
			m_edtDestIP.SetWindowText(tATMInfo.cDestIP);
			SetDlgItemInt(IDC_EDIT_ATM_DESTPORT, tATMInfo.iDestPort);

			m_edtSrcIP.ShowWindow(true);
			GetDlgItem(IDC_STATIC_ATM_SRCIP)->ShowWindow(true);
			m_edtSrcPort.ShowWindow(true);
			GetDlgItem(IDC_STATIC_ATM_SRCPORT)->ShowWindow(true);
			m_edtDestIP.ShowWindow(true);
			GetDlgItem(IDC_STATIC_ATM_DESTIP)->ShowWindow(true);
			m_edtDestPort.ShowWindow(true);
			GetDlgItem(IDC_STATIC_ATM_DESTPORT)->ShowWindow(true);
			m_cmbComNo.ShowWindow(false);
			GetDlgItem(IDC_STATIC_ATM_COM)->ShowWindow(false);
			m_cmbWorkMode.ShowWindow(false);
			GetDlgItem(IDC_STATIC_ATM_WORKMODE)->ShowWindow(false);
			m_edtComFormat.ShowWindow(false);
			GetDlgItem(IDC_STATIC_ATM_COMFORMAT)->ShowWindow(false);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "[ATM] GetATMConfig ATM_INFO Failed, error(0x%08x)\n", GetLastError());
	}

}
	