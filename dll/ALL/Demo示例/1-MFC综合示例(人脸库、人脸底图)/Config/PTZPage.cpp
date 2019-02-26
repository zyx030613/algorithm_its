// Config\PTZPage.cpp : implementation file
//

#include "stdafx.h"
#include "PTZPage.h"


// CLS_PTZPage dialog

IMPLEMENT_DYNAMIC(CLS_PTZPage, CDialog)

CLS_PTZPage::CLS_PTZPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_PTZPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_PTZPage::~CLS_PTZPage()
{
}

void CLS_PTZPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_NAME, m_cboProtocolName);
	DDX_Control(pDX, IDC_COMBO_COM_NO, m_cboComNo);
	DDX_Control(pDX, IDC_SPIN_ADDRESS, m_spinAddress);
	DDX_Control(pDX, IDC_COMBO_CHN_BAUD_RATE, m_cboBaudRate);
	DDX_Control(pDX, IDC_COMBO_CHN_PARITY_BIT, m_cboParityBit);
	DDX_Control(pDX, IDC_COMBO_CHN_DATA_BIT, m_cboDataBit);
	DDX_Control(pDX, IDC_COMBO_CHN_STOP_BIT, m_cboStopBit);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_EDIT_PRESETINDEX, m_edtPresetIndex);
	DDX_Control(pDX, IDC_EDIT_IDLETIME, m_edtIdleTime);
	DDX_Control(pDX, IDC_BUTTON_AUTOBACK, m_btnAutoBack);
	DDX_Control(pDX, IDC_SPIN_PRESETINDEX, m_spinPreset);
	DDX_Control(pDX, IDC_SPIN_IDLETIME, m_spinIdleTime);
}


BEGIN_MESSAGE_MAP(CLS_PTZPage,CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_TYPE, &CLS_PTZPage::OnBnClickedButtonDeviceType)
	ON_BN_CLICKED(IDC_BUTTON_CHN_PTZ_FORMAT, &CLS_PTZPage::OnBnClickedButtonPtzFormat)
	ON_BN_CLICKED(IDC_BUTTON_AUTOBACK, &CLS_PTZPage::OnBnClickedButtonAutoback)
	ON_BN_CLICKED(IDC_CHECK_CHNPTZ, &CLS_PTZPage::OnBnClickedChnptzEnable)
END_MESSAGE_MAP()


// CLS_PTZPage message handlers

BOOL CLS_PTZPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	m_cboBaudRate.AddString(_T("50"));
	m_cboBaudRate.AddString(_T("75"));
	m_cboBaudRate.AddString(_T("110"));
	m_cboBaudRate.AddString(_T("150"));
	m_cboBaudRate.AddString(_T("300"));
	m_cboBaudRate.AddString(_T("600"));
	m_cboBaudRate.AddString(_T("1200"));
	m_cboBaudRate.AddString(_T("2400"));
	m_cboBaudRate.AddString(_T("4800"));
	m_cboBaudRate.AddString(_T("9600"));
	m_cboBaudRate.AddString(_T("19200"));
	m_cboBaudRate.AddString(_T("38400"));
	m_cboBaudRate.AddString(_T("57600"));
	m_cboBaudRate.AddString(_T("76800"));
	m_cboBaudRate.AddString(_T("115200"));
	m_cboBaudRate.SetCurSel(9);

	m_cboParityBit.SetItemData(0,'n');
	m_cboParityBit.SetItemData(1,'o');
	m_cboParityBit.SetItemData(2,'e');
	m_cboParityBit.SetCurSel(0);

	m_cboDataBit.ResetContent();
	for (int i = 4; i < 9; ++i)
	{
		m_cboDataBit.AddString(IntToString(i));
	}
	m_cboDataBit.SetCurSel(4);

	m_cboStopBit.AddString(IntToString(1));
	m_cboStopBit.AddString(IntToString(2));
	m_cboStopBit.SetCurSel(0);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ADDRESS);
	pEdit->SetLimitText(3);
	m_spinAddress.SetRange(0,256);
	m_spinAddress.SetBuddy(pEdit);
	
	m_edtPresetIndex.SetLimitText(3);
	m_spinPreset.SetRange(1,256);
	m_spinPreset.SetBuddy(&m_edtPresetIndex);

	m_edtIdleTime.SetLimitText(5);
	m_spinIdleTime.SetRange32(10,65535);
	m_spinIdleTime.SetBuddy(&m_edtIdleTime);
	
	return TRUE;  
}

void CLS_PTZPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	
	UI_UpdateWindow();
}

void CLS_PTZPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_PTZPage::UI_UpdateDialog()
{
	InsertString(m_cboParityBit,0,IDS_CFG_COM_PARITY_NONE);
	InsertString(m_cboParityBit,1,IDS_CFG_COM_PARITY_ODD);
	InsertString(m_cboParityBit,2,IDS_CFG_COM_PARITY_EVEN);

	SetDlgItemTextEx(IDC_STATIC_PROTOCOL_NAME,IDS_CFG_PTZ_PROTOCOL_NAME);
	SetDlgItemTextEx(IDC_STATIC_COM_NO,IDS_CFG_PTZ_COM_NO);
	SetDlgItemTextEx(IDC_STATIC_ADDRESS,IDS_CFG_PTZ_ADDRESS);
	SetDlgItemTextEx(IDC_BUTTON_DEVICE_TYPE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CHN_BAUD_RATE,IDS_CFG_COM_BAUD_RATE);
	SetDlgItemTextEx(IDC_STATIC_CHN_PARITY_BIT,IDS_CFG_COM_PARITY_BIT);
	SetDlgItemTextEx(IDC_STATIC_CHN_DATA_BIT,IDS_CFG_COM_DATA_BIT);
	SetDlgItemTextEx(IDC_STATIC_CHN_STOP_BIT,IDS_CFG_COM_STOP_BIT);
	SetDlgItemTextEx(IDC_BUTTON_CHN_PTZ_FORMAT,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_AUTOBACK,IDS_CONFIG_PTZ_AUTOBACK);
	SetDlgItemTextEx(IDC_CHECK_ENABLE,IDS_CONFIG_ECOP_RECOPARAM_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_PRESETINDEX,IDS_CONFIG_PTZ_PRESETINDEX);
	SetDlgItemTextEx(IDC_STATIC_IDLETIME,IDS_CONFIG_PTZ_IDLETIME);
	SetDlgItemTextEx(IDC_BUTTON_AUTOBACK,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DEVICETYPE,IDS_CONFIG_PTZ_DEVICETYPE);
	SetDlgItemTextEx(IDC_STATIC_PTZ_FORMAT,IDS_CONFIG_PTZ_FORMAT);
	SetDlgItemTextEx(IDC_CHECK_CHNPTZ,IDS_CONFIG_ECOP_RECOPARAM_ENABLE);

}

void CLS_PTZPage::UI_UpdateWindow()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iProductType = 0;
	int iRet = NetClient_GetProductType(m_iLogonID, &iProductType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);

		iProductType &= 0xFFFF;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);
	}
	
	int iComPortCounts = 0;
	int iComPortStatus = 0;
	iRet = NetClient_GetComPortCounts(m_iLogonID, &iComPortCounts, &iComPortStatus);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetComPortCounts(%d,%d,%d)"
			,m_iLogonID, iComPortCounts, iComPortStatus);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetComPortCounts(%d,%d,%d)"
			,m_iLogonID, iComPortCounts, iComPortStatus);

		if (IsDVR(iProductType))
		{
			iComPortCounts = 4;
		}
		else
		{
			iComPortCounts = 2;
		}
	}

	int iComIndex = 0;
	CString strCom;
	m_cboComNo.ResetContent();

	if (0 == iComPortCounts)
	{
		iComIndex = m_cboComNo.AddString(_T("Com1"));
		m_cboComNo.SetItemData(iComIndex, 1);
		iComIndex = m_cboComNo.AddString(_T("Com2"));
		m_cboComNo.SetItemData(iComIndex, 2);
	}

	for (int i = 0; i < iComPortCounts; ++i)
	{
		if (0 == (iComPortStatus & (1<<i)))
		{
			continue;
		}

		strCom.Format(_T("COM%d"),i+1);
		iComIndex = m_cboComNo.AddString(strCom);
		m_cboComNo.SetItemData(iComIndex,i+1);
	}

	//获取协议列表
	st_NVSProtocol protocol = {0};
	m_cboProtocolName.ResetContent();
	iRet = NetClient_GetProtocolList(m_iLogonID,&protocol);
	if(0 == iRet && protocol.iCount > 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetProtocolList(%d,%d)"
			,m_iLogonID,protocol.iCount);

		//int iProtocolIndex = -1;
		for (int i = 0; i < protocol.iCount; i++)
		{
// 			iProtocolIndex = m_cboProtocolName.FindStringExact(-1,protocol.cProtocol[i]);
// 			if (iProtocolIndex < 0)
			{
				m_cboProtocolName.AddString(protocol.cProtocol[i]);
			}
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetProtocolList(%d,%#x)"
			,m_iLogonID,&protocol);

		m_cboProtocolName.AddString(_T("PTZ_PELCO_D"));
		m_cboProtocolName.AddString(_T("PTZ_PELCO_P"));
		m_cboProtocolName.AddString(_T("PTZ_TC615_P"));
		m_cboProtocolName.AddString(_T("DOME_PELCO_D"));
		m_cboProtocolName.AddString(_T("DOME_PELCO_P"));
		m_cboProtocolName.AddString(_T("DOME_PLUS"));
	}

	int iComPort = 0;
	int iDevAddress = 0;
	int iChannelNo = 0;
	char cDeviceType[64]= {0};
	if (IsDVR(iProductType)||iProductType==0x64)
	{
		iChannelNo = m_iChannelNo;
	}
	iRet = NetClient_GetDeviceType(m_iLogonID,iChannelNo,&iComPort,&iDevAddress,cDeviceType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,iComPort,iDevAddress,cDeviceType);

		if (0 == iComPort)
		{
			m_cboComNo.SetCurSel(0);
		}
		else
		{
			CString strComPort;
			strComPort.Format(_T("COM%d"), iComPort);
			m_cboComNo.SelectString(-1, strComPort);
		}
		m_cboProtocolName.SelectString(-1, cDeviceType);
		SetDlgItemInt(IDC_EDIT_ADDRESS,iDevAddress);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,iComPort,iDevAddress,cDeviceType);

		SetDlgItemText(IDC_EDIT_ADDRESS,_T(""));
		SetDlgItemText(IDC_EDIT_COM_FORMAT,_T(""));
	}

	char cComFormat[64] = {0};
	iRet = NetClient_GetCHNPTZFormat(m_iLogonID,m_iChannelNo,cComFormat);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCHNPTZFormat(%d,%d,%s)"
			,m_iLogonID,m_iChannelNo,cComFormat);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCHNPTZFormat(%d,%d,%s)"
			,m_iLogonID,m_iChannelNo,cComFormat);
	}

	if (strlen(cComFormat) <= 1)
	{
		CheckDlgButton(IDC_CHECK_CHNPTZ,FALSE);
	}
	else
	{
		int iBaudRate = 0;
		char cParityBit = 0;
		int iDataBit = 0;
		int iStopBit = 0;
		sscanf_s(cComFormat,"%d,%c,%d,%d",&iBaudRate,&cParityBit,sizeof(char),&iDataBit,&iStopBit);

		//m_cboBaudRate.SelectString(-1,IntToString(iBaudRate));
		SetDlgItemInt(IDC_COMBO_CHN_BAUD_RATE,iBaudRate);

		for (int i = 0; i < m_cboParityBit.GetCount(); ++i)
		{
			if(cParityBit == m_cboParityBit.GetItemData(i))
			{
				m_cboParityBit.SetCurSel(i);
				break;
			}
		}

		m_cboDataBit.SelectString(-1,IntToString(iDataBit));
		m_cboStopBit.SelectString(-1,IntToString(iStopBit));
		CheckDlgButton(IDC_CHECK_CHNPTZ,TRUE);
	}
	OnBnClickedChnptzEnable();
	
	int ipresetindex = 0;
	int iIdletime = 0;
	int iPTZEnable = 0;
	iRet = NetClient_GetPTZAutoBack(m_iLogonID,m_iChannelNo,&iPTZEnable,&ipresetindex,&iIdletime);
	if (0 == iRet)
	{
		m_chkEnable.SetCheck((iPTZEnable == 1)?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_PRESETINDEX, ipresetindex);
		SetDlgItemInt(IDC_EDIT_IDLETIME, iIdletime);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetPTZAutoBack(%d,%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,iPTZEnable,ipresetindex,ipresetindex);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetPTZAutoBack(%d,%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,iPTZEnable,ipresetindex,ipresetindex);
	}
}

void CLS_PTZPage::OnBnClickedButtonDeviceType()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iDevAddress = GetDlgItemInt(IDC_EDIT_ADDRESS);
	if (iDevAddress > 256 || iDevAddress < 0)
	{
		AddLog(LOG_TYPE_MSG,"","please select a correct address(%d)",iDevAddress);
		return;
	}

	int iComIndex = m_cboComNo.GetCurSel();
	if (iComIndex < 0)
	{
		AddLog(LOG_TYPE_MSG,"","please select a correct com num");
		return;
	}

	char cDeviceType[64]= {0}; 
	m_cboProtocolName.GetWindowText(cDeviceType,sizeof(cDeviceType));
	if (strlen(cDeviceType) <= 0)
	{
		AddLog(LOG_TYPE_MSG,"","please select a correct protocol name");
		return;
	}

	int iProductType = 0;
	int iRet = NetClient_GetProductType(m_iLogonID, &iProductType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);

		iProductType &= 0xFFFF;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);
	}
	
	int iChannelNo = 0;
	if(IsDVR(iProductType)||iProductType==0x64||iProductType==0x66||iProductType==0x62)
	{
		iChannelNo = m_iChannelNo;
	}

	DWORD_PTR iComNo = m_cboComNo.GetItemData(iComIndex);
	iRet = NetClient_SetDeviceType(m_iLogonID, iChannelNo, iComNo,iDevAddress,cDeviceType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,iComNo,iDevAddress,cDeviceType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,iComNo,iDevAddress,cDeviceType);
	}
}

void CLS_PTZPage::OnBnClickedButtonPtzFormat()
{
	char cComFormat[64] = {0};
	if(IsDlgButtonChecked(IDC_CHECK_CHNPTZ))
	{
		int iBaudRate = GetDlgItemInt(IDC_COMBO_CHN_BAUD_RATE);
		char cParityBit = (char)m_cboParityBit.GetItemData(m_cboParityBit.GetCurSel());
		int iDataBit = GetDlgItemInt(IDC_COMBO_CHN_DATA_BIT);
		int iStopBit = GetDlgItemInt(IDC_COMBO_CHN_STOP_BIT);
		sprintf_s(cComFormat,"%d,%c,%d,%d",iBaudRate,cParityBit,iDataBit,iStopBit);
	}
	else
	{
		sprintf_s(cComFormat,"0");
	}

	int iRet = NetClient_SetCHNPTZFormat(m_iLogonID,m_iChannelNo,cComFormat);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCHNPTZFormat(%d,%d,%s)"
			,m_iLogonID,m_iChannelNo,cComFormat);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCHNPTZFormat(%d,%d,%s)"
			,m_iLogonID,m_iChannelNo,cComFormat);
	}
}

void CLS_PTZPage::OnBnClickedButtonAutoback()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int ipresetindex = GetDlgItemInt(IDC_EDIT_PRESETINDEX);
	if (ipresetindex < 1 || ipresetindex > 256)
	{
		AddLog(LOG_TYPE_MSG,"","please input a valid preset(%d),between 1 and 256",ipresetindex);
		return;
	}

	int iIdletime = GetDlgItemInt(IDC_EDIT_IDLETIME);
	if (iIdletime < 10 || ipresetindex > 65535)
	{
		AddLog(LOG_TYPE_MSG,"","please input a valid idle time(%d),between 10 and 65535",ipresetindex);
		return;
	}

	int iEnable = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	int iRet = NetClient_SetPTZAutoBack(m_iLogonID,m_iChannelNo,iEnable,ipresetindex,iIdletime);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetPTZAutoBack(%d,%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,iEnable,ipresetindex,iIdletime);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetPTZAutoBack(%d,%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,iEnable,ipresetindex,iIdletime);
	}
}

void CLS_PTZPage::OnBnClickedChnptzEnable()
{
	BOOL bEnable = IsDlgButtonChecked(IDC_CHECK_CHNPTZ);
	m_cboDataBit.EnableWindow(bEnable);
	m_cboParityBit.EnableWindow(bEnable);
	m_cboStopBit.EnableWindow(bEnable);
	m_cboBaudRate.EnableWindow(bEnable);
}
