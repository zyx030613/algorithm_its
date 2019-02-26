 // Config\ComPage.cpp : implementation file
//

#include "stdafx.h"
#include "ComPage.h"


// CLS_ComPage dialog

IMPLEMENT_DYNAMIC(CLS_ComPage, CDialog)

CLS_ComPage::CLS_ComPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ComPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_ComPage::~CLS_ComPage()
{
}

void CLS_ComPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COM_NO, m_cboComNo);
	DDX_Control(pDX, IDC_COMBO_BAUD_RATE, m_cboBaudRate);
	DDX_Control(pDX, IDC_COMBO_PARITY_BIT, m_cboParityBit);
	DDX_Control(pDX, IDC_COMBO_DATA_BIT, m_cboDataBit);
	DDX_Control(pDX, IDC_COMBO_STOP_BIT, m_cboStopBit);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_cboWorkMode);
	DDX_Control(pDX, IDC_COMBO_COMTYPE, m_cboComType);
	DDX_Control(pDX, IDC_COMBO_DEVICE_NAME, m_cboDeviceName);
	DDX_Control(pDX, IDC_CMB_MEM, m_cboDlMem);
}


BEGIN_MESSAGE_MAP(CLS_ComPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_COM_FORMAT, &CLS_ComPage::OnBnClickedButtonComFormat)
	ON_CBN_SELCHANGE(IDC_COMBO_COM_NO, &CLS_ComPage::OnCbnSelchangeComboComNo)
	ON_BN_CLICKED(IDC_BUTTON_COM_SEND, &CLS_ComPage::OnBnClickedButtonComSend)
	ON_BN_CLICKED(IDC_BTN_DLSEND, &CLS_ComPage::OnBnClickedBtnDlsend)
	ON_CBN_SELCHANGE(IDC_CMB_MEM, &CLS_ComPage::OnCbnSelchangeCmbMem)
END_MESSAGE_MAP()


// CLS_ComPage message handlers

BOOL CLS_ComPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();
	
	m_cboBaudRate.ResetContent();
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
	
	m_cboDeviceName.ResetContent();
	m_cboDeviceName.AddString(_T("RL704"));
	m_cboDeviceName.AddString(_T("T324/328V20"));
	m_cboDeviceName.AddString(_T("CSR_IK1"));
	m_cboDeviceName.AddString(_T("CSR68ND"));
	m_cboDeviceName.AddString(_T("T550"));
	m_cboDeviceName.AddString(_T("CSR_AD"));
	m_cboDeviceName.SetCurSel(0);

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
	
	m_cboStopBit.ResetContent();
	m_cboStopBit.AddString(IntToString(1));
	m_cboStopBit.AddString(IntToString(2));
	m_cboStopBit.SetCurSel(0);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_COM_DATA);
	pEdit->SetLimitText(3068);
	pEdit->SetWindowText(_T("00,01,02,03,04,05,06,07"));

	m_cboComType.ResetContent();
	m_cboComType.AddString("0:485");
	m_cboComType.AddString("1:232");
	m_cboComType.AddString("2:422");
	m_cboComType.SetCurSel(0);

	SetDlgItemTextEx(IDC_BTN_DLSEND, IDS_CFG_COM_DLSEND);
	SetDlgItemTextEx(IDC_STATIC_REM, IDS_CFG_COM_SENDREM);
	
	return TRUE; 
}

void CLS_ComPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID != _iLogonID)
	{
		m_iLogonID = _iLogonID;

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

		CString strCom;
		int iComIndex = -1;
		m_cboComNo.ResetContent();
		for (int i = 0; i < iComPortCounts; ++i)
		{
			if ((iComPortStatus >> i) & 1)
			{
				strCom.Format(_T("COM%d"),i+1);
				iComIndex = m_cboComNo.AddString(strCom);
				m_cboComNo.SetItemData(iComIndex,i+1);
			}
		}
		m_cboComNo.SetCurSel(0);
	}
	
	UI_UpdateComFormat();
}

void CLS_ComPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_ComPage::OnBnClickedButtonComFormat()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iComIndex = m_cboComNo.GetCurSel();
	if (iComIndex < 0)
	{
		AddLog(LOG_TYPE_MSG,"","please select a correct com num");
		return;
	}

	int iRet = -1;
	COMFORMAT comformat = {0};
	comformat.iSize = sizeof(COMFORMAT);
	int iComNo = (int)m_cboComNo.GetItemData(iComIndex);
	int iWorkMode = m_cboWorkMode.GetCurSel()+1;
	if (7 == iWorkMode)//ATM串口最多设置1个
	{
		for (int i = 0; i < m_cboComNo.GetCount(); ++i)
		{
			comformat.iComNo = (int)m_cboComNo.GetItemData(i);
			if (comformat.iComNo == iComNo)
			{
				continue;
			}

			iRet = NetClient_GetComFormat_V2(m_iLogonID, &comformat);
			if(0 == iRet && iWorkMode == comformat.iWorkMode)
			{
				AddLog(LOG_TYPE_MSG,"","can not set another ATM COM(%d)",comformat.iComNo);
				return;
			}
		}
	}
	int iBaudRate = GetDlgItemInt(IDC_COMBO_BAUD_RATE);
	char cParityBit = (char)m_cboParityBit.GetItemData(m_cboParityBit.GetCurSel());
	int iDataBit = GetDlgItemInt(IDC_COMBO_DATA_BIT);
	int iStopBit = GetDlgItemInt(IDC_COMBO_STOP_BIT);
	sprintf_s(comformat.cComFormat,"%d,%c,%d,%d",iBaudRate,cParityBit,iDataBit,iStopBit);
	comformat.iComNo = iComNo;
	comformat.iWorkMode = iWorkMode;
	CString strDeviceName;
	strDeviceName.Format("%d",m_cboDeviceName.GetCurSel()+1);
	strcpy_s(comformat.cDeviceName,sizeof(comformat.cDeviceName),strDeviceName.GetBuffer());
	comformat.iComType = m_cboComType.GetCurSel();

	iRet = NetClient_SetComFormat_V2(m_iLogonID,&comformat);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetComFormat_V2(%d,%d,NULL,%s,%d)"
			,m_iLogonID,comformat.iComNo,comformat.cComFormat,comformat.iWorkMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetComFormat_V2(%d,%d,NULL,%s,%d)"
			,m_iLogonID,comformat.iComNo,comformat.cComFormat,comformat.iWorkMode);
	}
}

void CLS_ComPage::UI_UpdateDialog()
{
	InsertString(m_cboParityBit,0,IDS_CFG_COM_PARITY_NONE);
	InsertString(m_cboParityBit,1,IDS_CFG_COM_PARITY_ODD);
	InsertString(m_cboParityBit,2,IDS_CFG_COM_PARITY_EVEN);

	InsertString(m_cboWorkMode,0,IDS_CFG_PTZ_WORKMODE_PROTOCOL);
	InsertString(m_cboWorkMode,1,IDS_CFG_PTZ_WORKMODE_TRANSPARENT);
	InsertString(m_cboWorkMode,2,IDS_CFG_PTZ_WORKMODE_INDUSTRIAL_APPLICATIONS);
	InsertString(m_cboWorkMode,3,IDS_CFG_PTZ_WORKMODE_7601B_SERIAL);
	InsertString(m_cboWorkMode,4,IDS_CFG_PTZ_WORKMODE_485_KEYBOARD);
	InsertString(m_cboWorkMode,5,IDS_CFG_PTZ_WORKMODE_GPS);
	InsertString(m_cboWorkMode,6,IDS_CFG_PTZ_WORKMODE_ATM);

	SetDlgItemTextEx(IDC_STATIC_COM_NO,IDS_CFG_PTZ_COM_NO);
	SetDlgItemTextEx(IDC_STATIC_BAUD_RATE,IDS_CFG_COM_BAUD_RATE);
	SetDlgItemTextEx(IDC_STATIC_PARITY_BIT,IDS_CFG_COM_PARITY_BIT);
	SetDlgItemTextEx(IDC_STATIC_DATA_BIT,IDS_CFG_COM_DATA_BIT);
	SetDlgItemTextEx(IDC_STATIC_STOP_BIT,IDS_CFG_COM_STOP_BIT);
	SetDlgItemTextEx(IDC_STATIC_WORK_MODE,IDS_CFG_PTZ_WORKMODE);
	SetDlgItemTextEx(IDC_BUTTON_COM_FORMAT,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_COM_DATA,IDS_CFG_PTZ_DATA);
	SetDlgItemTextEx(IDC_BUTTON_COM_SEND,IDS_CFG_PTZ_SEND);
	SetDlgItemTextEx(IDC_STATIC_COMTYPE,IDS_MENU_COM_COMTYPE);
	SetDlgItemTextEx(IDC_STATIC_DEVICE_NAME,IDS_CFG_COM_DEVICE_NAME);	

}

void CLS_ComPage::UI_UpdateComFormat()
{
	int iComIndex = m_cboComNo.GetCurSel();
	if (iComIndex < 0)
	{
		return;
	}

	COMFORMAT comformat = {0};
	comformat.iSize = sizeof(COMFORMAT);
	comformat.iComNo = (int)m_cboComNo.GetItemData(iComIndex);
	int iRet = NetClient_GetComFormat_V2(m_iLogonID, &comformat);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetComFormat_V2(%d,%d,%s,%d)"
			,m_iLogonID,comformat.iComNo,comformat.cComFormat,comformat.iWorkMode);

 		int iDeviceIndex = atoi(comformat.cDeviceName)-1;
// 		if (iDeviceIndex<0 || iDeviceIndex >5)
// 		{
// 			return ;
// 		}
		m_cboDeviceName.SetCurSel(iDeviceIndex);
		int iBaudRate = 0;
		char cParityBit = 0;
		int iDataBit = 0;
		int iStopBit = 0;
		sscanf_s(comformat.cComFormat,"%d,%c,%d,%d",&iBaudRate,&cParityBit,sizeof(char),&iDataBit,&iStopBit);

		//m_cboBaudRate.SelectString(-1,IntToString(iBaudRate));
		SetDlgItemInt(IDC_COMBO_BAUD_RATE,iBaudRate);

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
		m_cboWorkMode.SetCurSel(comformat.iWorkMode-1);
		m_cboComType.SetCurSel(comformat.iComType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetComFormat_V2(%d,%d,%s,%d)"
			,m_iLogonID,comformat.iComNo,comformat.cComFormat,comformat.iWorkMode);
	}
	
}

void CLS_ComPage::OnCbnSelchangeComboComNo()
{
	UI_UpdateComFormat();
}

void CLS_ComPage::OnBnClickedButtonComSend()
{
	int iComIndex = m_cboComNo.GetCurSel();
	if (iComIndex < 0)
		return;

	CString strData;
	GetDlgItemText(IDC_EDIT_COM_DATA,strData);
	strData.Replace(_T(","),_T(""));
	strData.Replace(_T(" "),_T(""));
	strData.Replace(_T("\r"),_T(""));
	strData.Replace(_T("\n"),_T(""));
	char* pucData = (LPSTR)(LPCTSTR)strData;
	char ucBuf[1024] = {0};
	int iLen = strData.GetLength()/2;
	if (iLen >= 1024)
	{
		iLen = 1023;
	}
	for (int i = 0; i < iLen; ++i)
	{
		sscanf_s(pucData+i*2,"%2x",ucBuf+i);
	}

	CString strOut = Bytes2HexString((unsigned char*)ucBuf,iLen);
	int iComNo = (int)m_cboComNo.GetItemData(iComIndex);
	int iRet = NetClient_ComSend(m_iLogonID,(unsigned char *)ucBuf,iLen,iComNo);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_ComSend(%d,%s,%d,%d)"
			,m_iLogonID,(LPSTR)(LPCTSTR)strOut,iLen,iComNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_ComSend(%d,%s,%d,%d)"
			,m_iLogonID,(LPSTR)(LPCTSTR)strOut,iLen,iComNo);
	}
}

void CLS_ComPage::OnBnClickedBtnDlsend()
{
	// TODO: Add your control notification handler code here
	int iComIndex = m_cboComNo.GetCurSel();
	if (iComIndex < 0)
	{
		return;
	}

	CString strData;
	GetDlgItemText(IDC_EDIT_COM_DATA, strData);
	strData.Replace(_T(","),_T(""));
	strData.Replace(_T(" "),_T(""));
	strData.Replace(_T("\r"),_T(""));
	strData.Replace(_T("\n"),_T(""));
	char* pucData = (LPSTR)(LPCTSTR)strData;

	//char ucBuf[1024] = {0};
	char cDlSend[28] = {0xF6,0x0D,0x00,0x53,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int iLen = strData.GetLength()/2;
	if (iLen >= 8)
	{
		iLen = 8;
	}

	for (int i = 0; i < iLen; ++i)
	{
		sscanf_s(pucData+i*2, "%2x", cDlSend+5+i);
	}

	int iAddRes = 0;
	for (int iAddIndex = 1; iAddIndex < 14; ++iAddIndex)
	{
		iAddRes += cDlSend[iAddIndex];
	}
	cDlSend[13] = iAddRes & 0x7F;
	CString strOut = Bytes2HexString((unsigned char*)cDlSend, 14);
	int iComNo = (int)m_cboComNo.GetItemData(iComIndex);

	int iRet = NetClient_ComSend(m_iLogonID, (unsigned char*)cDlSend, 14, iComNo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_ComSend(%d,%s,%d,%d)"
			,m_iLogonID,(LPSTR)(LPCTSTR)strOut,iLen,iComNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_ComSend(%d,%s,%d,%d)"
			,m_iLogonID,(LPSTR)(LPCTSTR)strOut,iLen,iComNo);
	}

	int iAlreadAddNo = m_cboDlMem.GetCount();
	if (iAlreadAddNo < 100)
	{
		char cMem[25] = "0";
		memcpy(cMem, (LPSTR)(LPCTSTR)strOut+15, sizeof(cMem)-1);
		for(int iIndex = 0; iIndex < iAlreadAddNo; ++iIndex)
		{
			CString cstrCmp;
			m_cboDlMem.GetLBText(iIndex, cstrCmp);
			if (0 == strcmp(cMem, cstrCmp))
			{
				return;
			}
		}

		m_cboDlMem.AddString(cMem);
	}

}

void CLS_ComPage::OnCbnSelchangeCmbMem()
{
	// TODO: Add your control notification handler code here
	int iIndex = m_cboDlMem.GetCurSel();
	CString cstrMem;
	m_cboDlMem.GetLBText(iIndex, cstrMem);

	SetDlgItemText(IDC_EDIT_COM_DATA, cstrMem);
}
