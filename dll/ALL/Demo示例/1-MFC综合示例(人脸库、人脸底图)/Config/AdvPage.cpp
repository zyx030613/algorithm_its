// Config\AdvPage.cpp : implementation file
//

#include "stdafx.h"
#include "AdvPage.h"
#include <string>

// CLS_AdvPage dialog

IMPLEMENT_DYNAMIC(CLS_AdvPage, CDialog)

CLS_AdvPage::CLS_AdvPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AdvPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
}

CLS_AdvPage::~CLS_AdvPage()
{
}

void CLS_AdvPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADV_CPU, m_edtAdvCPU);
	DDX_Control(pDX, IDC_EDIT_ADV_MEM, m_edtAdvMEM);
	DDX_Control(pDX, IDC_EDIT_ADV_FLASH, m_edtAdvFlash);
	DDX_Control(pDX, IDC_CHECK_ADV_CPUCHECK, m_chkCPUcheck);
	DDX_Control(pDX, IDC_EDIT_ADV_INTERVAL, m_edtInternaiTime);
	DDX_Control(pDX, IDC_EDIT_ADV_STARTPOS, m_edtStartPos);
	DDX_Control(pDX, IDC_EDIT_ADV_LENGTH, m_edtLength);
	DDX_Control(pDX, IDC_EDIT_ADV_DATATEXT, m_edtDataText);
	DDX_Control(pDX, IDC_CHECK_ADV_ENABLE, m_chkTRebootEnable);
	DDX_Control(pDX, IDC_EDIT_ADV_PORT, m_edtClientPort);
	DDX_Control(pDX, IDC_COMBO_ADV_STREAMTYPE, m_cmbStreamType);
	DDX_Control(pDX, IDC_EDIT_ADV_CLIENTIP, m_edtClientIP);
	DDX_Control(pDX, IDC_COMBO_ADV_STREAMTYPE, m_cmbStreamType);
	DDX_Control(pDX, IDC_EDIT_ADV_INTERVALDAYS, m_edtIntervalDays);
	DDX_Control(pDX, IDC_EDIT_ADDV_HOUR, m_edtIntervalHour);
	DDX_Control(pDX, IDC_EDIT_INSERT_DATA, m_edtUserDefData);
	DDX_Control(pDX, IDC_COMBO_INSERT_TYPE, m_cboUserDefType);
	DDX_Control(pDX, IDC_CHECK_MAIN_STREAM, m_chkMainStream);
	DDX_Control(pDX, IDC_CHECK_SUB_STREAM, m_chkSubStream);
	DDX_Control(pDX, IDC_CHECK_MAIN_SUB, m_chkMainSub);
	DDX_Control(pDX, IDC_COMBO_ARBOOTWEEK, m_cboArbootWeek);
}


BEGIN_MESSAGE_MAP(CLS_AdvPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADV_GETSYSINFO, &CLS_AdvPage::OnBnClickedButtonAdvGetsysinfo)
	//ON_BN_CLICKED(IDC_BUTTON_SET_CPUENABLE, &CLS_AdvPage::OnBnClickedButtonSetCpuenable)
	ON_BN_CLICKED(IDC_BUTTON_USERDATASET, &CLS_AdvPage::OnBnClickedUserData)
	
	ON_BN_CLICKED(IDC_BUTTON__ADV_TREBOOTSET, &CLS_AdvPage::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON_ADV_STREAMSET, &CLS_AdvPage::OnBnClickedButtonAdvStreamset)
	ON_BN_CLICKED(IDC_BUTTON_INSET_SET, &CLS_AdvPage::OnBnClickedButtonInsetSet)
	ON_BN_CLICKED(IDC_CHECK_MAIN_STREAM, &CLS_AdvPage::OnBnClickedCheckMainStream)
	ON_BN_CLICKED(IDC_CHECK_SUB_STREAM, &CLS_AdvPage::OnBnClickedCheckSubStream)
	ON_BN_CLICKED(IDC_CHECK_MAIN_SUB, &CLS_AdvPage::OnBnClickedCheckMainSub)
	ON_BN_CLICKED(IDC_BUTTON_ARBOOTSET, &CLS_AdvPage::OnBnClickedButtonArbootset)
	ON_CBN_SELCHANGE(IDC_COMBO_ARBOOTWEEK, &CLS_AdvPage::OnCbnSelchangeComboArbootweek)
END_MESSAGE_MAP()


// CLS_AdvPage message handlers
BOOL CLS_AdvPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	SetDlgItemInt(IDC_EDIT_ADV_STARTPOS, 0);
	SetDlgItemInt(IDC_EDIT_ADV_LENGTH, 32);
	m_cmbStreamType.SetCurSel(0);
	m_edtInternaiTime.SetLimitText(4);
	m_edtStartPos.SetLimitText(2);
	m_edtLength.SetLimitText(2);
	m_edtIntervalDays.SetLimitText(3);
	m_edtIntervalHour.SetLimitText(4);
	m_edtClientIP.SetLimitText(16);
	m_edtClientPort.SetLimitText(5);
	m_edtDataText.SetLimitText(32*3);
	m_edtUserDefData.SetLimitText(MAX_INSERT_STREAM_LEN -1);
	UI_UpdateLanguage();
	UI_UpdateStreamInsertDataInfo();
	m_cboUserDefType.SetCurSel(1);

	return TRUE;
}

void CLS_AdvPage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
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
	
	UI_UpdateSystemInfo();
	UI_UpdateTRebootInfo();
	UI_UpdateARBootInfo();
	UI_UpdateSendStreamInfo();
	UI_UpdateUserData();
	UI_UpdateStreamInsertDataInfo();
}

void CLS_AdvPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateLanguage();
}
void CLS_AdvPage::OnBnClickedButtonAdvGetsysinfo()
{
	UI_UpdateSystemInfo();
}

void CLS_AdvPage::OnBnClickedButtonSetCpuenable()
{
	int iCheck = m_chkCPUcheck.GetCheck();
	int iInternal = GetDlgItemInt(IDC_EDIT_ADV_INTERVAL);
	int iRet = NetClient_CPUCheckEnabled(iCheck, iInternal);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_CPUCheckEnabled(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_CPUCheckEnabled(%d)",m_iLogonID);
	}
}

void CLS_AdvPage::OnBnClickedUserData()
{
	if (m_iLogonID < 0)
		return;

	int iOffset = GetDlgItemInt(IDC_EDIT_ADV_STARTPOS);
	if (iOffset < 0 || iOffset >= 32)
	{
		AddLog(LOG_TYPE_SUCC,"","please input a valid offset(%d)",iOffset);
		return;
	}

	int iLength = GetDlgItemInt(IDC_EDIT_ADV_LENGTH);
	if(iOffset+iLength > 32)
	{
		AddLog(LOG_TYPE_SUCC,"","please input a valid length(%d)",iLength);
		return;
	}

	CString strData;
	GetDlgItemText(IDC_EDIT_ADV_DATATEXT,strData);
	strData.Replace(_T(","),_T(""));
	strData.Replace(_T(" "),_T(""));
	strData.Replace(_T("\r"),_T(""));
	strData.Replace(_T("\n"),_T(""));
	char* pucData = (LPSTR)(LPCTSTR)strData;
	char ucBuf[32*2] = {0};
	int iLen = strData.GetLength()/2;
	if (iLen > iLength)
	{
		iLen = iLength;
	}
	for (int i = 0; i < iLen; ++i)
	{
		sscanf_s(pucData+i*2,"%2x",ucBuf+i);
	}

	CString strOut = Bytes2HexString((unsigned char*)ucBuf,iLength);
	int iRet = NetClient_WriteUserData(m_iLogonID, iOffset, (unsigned char*)ucBuf, iLength);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_WriteUserData(%d,%d,%s,%d)"
			,m_iLogonID,iOffset,(LPSTR)(LPCTSTR)strOut,iLength);

		SetDlgItemText(IDC_EDIT_ADV_DATATEXT,strOut);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_WriteUserData(%d,%d,%s,%d)"
			,m_iLogonID,iOffset,(LPSTR)(LPCTSTR)strOut,iLength);
	}
}

void CLS_AdvPage::OnBnClickedButton()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iCheck = m_chkTRebootEnable.GetCheck();
	int iIntervalDays = GetDlgItemInt(IDC_EDIT_ADV_INTERVALDAYS);
	int iHour = GetDlgItemInt(IDC_EDIT_ADDV_HOUR);

	int iRet = NetClient_SetDeviceTimerReboot(m_iLogonID, iCheck, iIntervalDays, iHour);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDeviceTimerReboot(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDeviceTimerReboot(%d)",m_iLogonID);
	}
}

void CLS_AdvPage::OnBnClickedButtonAdvStreamset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	CString strClientIP;
	m_edtClientIP.GetWindowText(strClientIP);

	if (IsValidIP(strClientIP) !=1)
	{
		MessageBox("Invalid IP!","",MB_OK|MB_TOPMOST);
	}	
	unsigned short usClientPort = GetDlgItemInt(IDC_EDIT_ADV_PORT);
	int iStreamType = m_cmbStreamType.GetCurSel();

	int iRet = NetClient_SetMediaStreamClient(m_iLogonID, m_iChannelNo, (LPSTR)(LPCTSTR)strClientIP, usClientPort, iStreamType); 
	if (0 == iRet)
	{
		MessageBox(GetTextEx(IDS_SET_RESULT_SUCCEED),"",MB_OK|MB_TOPMOST);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetMediaStreamClient(%d)",m_iLogonID);
	}
	else
	{
		MessageBox(GetTextEx(IDS_SET_RESULT_FAILED),"",MB_OK|MB_TOPMOST);
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetMediaStreamClient(%d)",m_iLogonID);
	}
}

void CLS_AdvPage::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUser)
{
	STR_Para* _strPara;
	_strPara = (STR_Para*) _pPara;
	
	switch(_iParaType)
	{
		
	case PARA_SYSINFO_RESULT:
		{
			SetDlgItemInt(IDC_EDIT_ADV_CPU, (int)_strPara->m_iPara[0]);
			SetDlgItemInt(IDC_EDIT_ADV_MEM, (int)_strPara->m_iPara[1]);
			SetDlgItemInt(IDC_EDIT_ADV_FLASH, (int)_strPara->m_iPara[2]);
		}
		break;
	case PARA_STREAM_DATA:
		{
			UI_UpdateStreamInsertDataInfo();
		}
	default:
		break;
	}
}

void CLS_AdvPage::UI_UpdateTRebootInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iEnable, iInterval, iHour;
	if(0 == NetClient_GetDeviceTimerReboot(m_iLogonID, &iEnable, &iInterval, &iHour))
	{
		m_chkTRebootEnable.SetCheck(iEnable);
		SetDlgItemInt(IDC_EDIT_ADV_INTERVALDAYS, iInterval);
		SetDlgItemInt(IDC_EDIT_ADDV_HOUR, iHour);
	}
}

void CLS_AdvPage::UI_UpdateARBootInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iBytesReturned = 0;
	TAutoRebootSchedule tAutoRebootSchedule = {0};
	tAutoRebootSchedule.iSize = sizeof(tAutoRebootSchedule);
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_AUTOREBOOT, m_iChannelNo, &tAutoRebootSchedule, sizeof(tAutoRebootSchedule), &iBytesReturned);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig faied! Logon id(%d)", m_iLogonID);
		return;
	}
	m_cboArbootWeek.SetCurSel(tAutoRebootSchedule.iWeekDay);
	SetDlgItemInt(IDC_EDIT_ARBOOTHOUR, tAutoRebootSchedule.iHour);
	SetDlgItemInt(IDC_EDIT_ARBOOTMIN, tAutoRebootSchedule.iMinute);
	AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig success! Logon id(%d)", m_iLogonID);
}

void CLS_AdvPage::UI_UpdateSendStreamInfo()
{
	char cIP[16] = {0};
	unsigned short iPort = 0;
	int iType = 0;
	if(0 == NetClient_GetMediaStreamClient(m_iLogonID, m_iChannelNo, cIP, &iPort, &iType))
	{
		m_edtClientIP.SetWindowText(cIP);
		SetDlgItemInt(IDC_EDIT_ADV_PORT, iPort);
		m_cmbStreamType.SetCurSel(iType);
	}
}

void CLS_AdvPage::UI_UpdateUserData()
{
	int iOffset = GetDlgItemInt(IDC_EDIT_ADV_STARTPOS);
	if (iOffset < 0 || iOffset >= 32)
	{
		AddLog(LOG_TYPE_MSG, "", "please input a valid offset(%d)", iOffset);
		return;
	}
	
	unsigned char ucBuf[32] = {0};
	int iLength = GetDlgItemInt(IDC_EDIT_ADV_LENGTH);
	if(iOffset+iLength <= 32)
	{
		int iRet =  NetClient_ReadUserData(m_iLogonID, iOffset, ucBuf, iLength);
		if(0 == iRet)
		{
			CString strOut = Bytes2HexString((unsigned char*)ucBuf,iLength);
			m_edtDataText.SetWindowText(strOut);
			AddLog(LOG_TYPE_SUCC, "","NetClient_ReadUserData(%d,%d,%s,%d)", iLength,iOffset,strOut,iLength);
		}
		else
		{
			m_edtDataText.SetWindowText(_T(""));
			AddLog(LOG_TYPE_FAIL, "","NetClient_ReadUserData(%d,%d,%s,%d)", iLength,iOffset,"",iLength);
		}
	}
	else
	{
		AddLog(LOG_TYPE_MSG, "", "please input a valid length(%d)", iLength);
	}
}

void CLS_AdvPage::UI_UpdateLanguage()
{
	SetDlgItemTextEx(IDC_STATIC_ADV_DEVICEINFO, IDS_CONFIG_ADV_DEVICEINFO);
	SetDlgItemTextEx(IDC_BUTTON_ADV_GETSYSINFO, IDS_CONFIG_ADV_GETSYSINFO);
	SetDlgItemTextEx(IDC_STATIC_ADV_grpClient, IDS_CONFIG_ADV_CLIENT);
	SetDlgItemTextEx(IDC_CHECK_ADV_CPUCHECK, IDS_CONFIG_ADV_CPUCHECK);
	SetDlgItemTextEx(IDC_STATIC_ADV_INTERVAL, IDS_CONFIG_ADV_INTERVALTIME);
	SetDlgItemTextEx(IDC_STATIC_ADV_STARTPOS, IDS_CONFIG_ADV_STARTPOS);
	SetDlgItemTextEx(IDC_STATIC_ADV_LENGTH, IDS_CONFIG_ADV_LENGTH);
	SetDlgItemTextEx(IDC_STATIC_ADV_DATATEXT, IDS_CONFIG_ADV_DATATEXT);
	SetDlgItemTextEx(IDC_STATIC_ADV_TIMERREBOOT, IDS_CONFIG_ADV_TIMERREBOOT);
	SetDlgItemTextEx(IDC_STATIC_ADV_INTERVALDAYS, IDS_CONFIG_ADV_INTERVALDAYS);
	SetDlgItemTextEx(IDC_STATIC_ADV_HOUR, IDS_CONFIG_ADV_INTERVALHOUR);
	SetDlgItemTextEx(IDC_CHECK_ADV_ENABLE, IDS_CONFIG_ADV_TIMERENABLE);
	SetDlgItemTextEx(IDC_STATIC_ADV_SEND, IDS_CONFIG_ADV_SENDSTREAM);
	SetDlgItemTextEx(IDC_STATIC_ADV_CLIENTIPPORT, IDS_CONFIG_ADV_IPORPORT);
	SetDlgItemTextEx(IDC_STATIC_ADV_STREAMTYPE, IDS_CONFIG_ADV_STREAMTYPE);
	SetDlgItemTextEx(IDC_STATIC_ADV_USERDATA, IDS_CONFIG_ADV_USERDATA);
	SetDlgItemTextEx(IDC_BUTTON_SETREC,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_USERDATASET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON__ADV_TREBOOTSET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_ADV_STREAMSET,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_REUSERDATA,IDS_CONFIG_ADV_REUSERDATA);
	SetDlgItemTextEx(IDC_STATIC_USER_INSERTDATA, IDS_CFG_ADV_USERDATA);
	SetDlgItemTextEx(IDC_STATIC_INSERT_DATA, IDS_CFG_ADV_INSERT_DATA);
	SetDlgItemTextEx(IDC_BUTTON_INSET_SET, IDS_CFG_ADV_INSERT_SET);
	SetDlgItemTextEx(IDC_STATIC_TYPE,IDS_CFG_ADV_INSERT_TYPE);
	InsertString(m_cboUserDefType,0,IDS_CFG_ADV_CBO_DEF);
	InsertString(m_cboUserDefType,1,IDS_CFG_ADV_CBO_DATA);
	SetDlgItemTextEx(IDC_CHECK_MAIN_STREAM, IDS_MAJOR);
	SetDlgItemTextEx(IDC_CHECK_SUB_STREAM, IDS_MINOR);
	SetDlgItemTextEx(IDC_CHECK_MAIN_SUB, IDS_MAJOR_MINOR);
	SetDlgItemTextEx(IDC_STATIC_ADV_ARBOOT, IDS_CONFIG_ADV_AUTOREBOOT);
	SetDlgItemTextEx(IDC_STATIC_ARBOOTWEEK, IDS_CONFIG_STORAGE_WEEKDAY);
	SetDlgItemTextEx(IDC_STATIC_ARBOOTHOUR, IDS_CONFIG_ADV_INTERVALHOUR);
	SetDlgItemTextEx(IDC_STATIC_ARBOOTMIN,  IDS_CONFIG_WIFI_MINUTE);
	SetDlgItemTextEx(IDC_BUTTON_ARBOOTSET, IDS_SET);

	InsertString(m_cboArbootWeek, 0, IDS_CONFIG_STORAGE_SUNDAY);
	InsertString(m_cboArbootWeek, 1, IDS_CONFIG_STORAGE_MONDAY);
	InsertString(m_cboArbootWeek, 2, IDS_CONFIG_STORAGE_TUESDAY);
	InsertString(m_cboArbootWeek, 3, IDS_CONFIG_STORAGE_WEDNESDAY);
	InsertString(m_cboArbootWeek, 4, IDS_CONFIG_STORAGE_THURSDAY);
	InsertString(m_cboArbootWeek, 5, IDS_CONFIG_STORAGE_FRIDAY);
	InsertString(m_cboArbootWeek, 6, IDS_CONFIG_STORAGE_SATURDAY);
	InsertString(m_cboArbootWeek, 7, IDS_CONFIG_STORAGE_ALLDAY_SET);
	InsertString(m_cboArbootWeek, 8, IDS_CONFIG_ADV_NEVER);

}

void CLS_AdvPage::UI_UpdateSystemInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iRet  = NetClient_GetSysInfo(m_iLogonID);
	if (0 == iRet)
	{
		//AddLog(LOG_TYPE_SUCC,"","NetClient_GetSysInfo(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetSysInfo(%d)",m_iLogonID);
	}
}

void CLS_AdvPage::OnBnClickedButtonInsetSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	CString strUserDefData;
	int iUserDefType = -1;
	m_edtUserDefData.GetWindowText(strUserDefData);
	iUserDefType = m_cboUserDefType.GetCurSel();

	TStreamData StreamData = {0};
	StreamData.iSize = sizeof(TStreamData);
	memcpy(StreamData.cStreamData, (LPSTR)(LPCTSTR)strUserDefData, strUserDefData.GetLength());
	StreamData.iStreamLen = strUserDefData.GetLength();

	int iRet = NetClient_SetStreamInsertData(m_iLogonID, m_iChannelNo, m_iStreamNo, iUserDefType, &StreamData, sizeof(TStreamData));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "SetStreamInsertData faied! Logon id(%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "SetStreamInsertData success! Logon id(%d)", m_iLogonID);
	}
}

void CLS_AdvPage::UI_UpdateStreamInsertDataInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	TStreamData StreamData = {0};
	StreamData.iSize = sizeof(TStreamData);
	int iUserDefType = -1;
	iUserDefType = m_cboUserDefType.GetCurSel();
	int iRet = NetClient_GetStreamInsertData(m_iLogonID, m_iChannelNo, m_iStreamNo, iUserDefType, &StreamData, sizeof(TStreamData));
	if (iRet < 0)
	{
		m_edtUserDefData.SetWindowText(_T(""));
		AddLog(LOG_TYPE_FAIL, "", "GetStreamInsertData faied! Logon id(%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "GetStreamInsertData success! Logon id(%d)", m_iLogonID);
		char cUserDefData[MAX_INSERT_STREAM_LEN + 1] = {0};
		memcpy(cUserDefData, StreamData.cStreamData, StreamData.iStreamLen);
		m_edtUserDefData.SetWindowText(cUserDefData);

		if (INSERTDATA_MAIN_STRAM == m_iStreamNo)
		{
			m_chkMainStream.SetCheck(BST_CHECKED);
			m_chkSubStream.SetCheck(BST_UNCHECKED);
			m_chkMainSub.SetCheck(BST_UNCHECKED);
		}
		else if (INSERTDATA_SUB_STRAM == m_iStreamNo)
		{
			m_chkSubStream.SetCheck(BST_CHECKED);
			m_chkMainStream.SetCheck(BST_UNCHECKED);
			m_chkMainSub.SetCheck(BST_UNCHECKED);
		}
		else if (INSERTDATA_MAIN_SUB == m_iStreamNo)
		{
			m_chkMainSub.SetCheck(BST_CHECKED);
			m_chkMainStream.SetCheck(BST_UNCHECKED);
			m_chkSubStream.SetCheck(BST_UNCHECKED);		
		}
		else
		{
			m_chkMainStream.SetCheck(BST_UNCHECKED);
			m_chkSubStream.SetCheck(BST_UNCHECKED);
			m_chkMainSub.SetCheck(BST_UNCHECKED);
		}
	}
}

void CLS_AdvPage::OnBnClickedCheckMainStream()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chkMainStream.GetCheck())
	{
		m_iStreamNo = 1;
		m_chkSubStream.SetCheck(BST_UNCHECKED);
		m_chkMainSub.SetCheck(BST_UNCHECKED);
	}
}

void CLS_AdvPage::OnBnClickedCheckSubStream()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chkSubStream.GetCheck())
	{
		m_iStreamNo = 2;
		m_chkMainStream.SetCheck(BST_UNCHECKED);
		m_chkMainSub.SetCheck(BST_UNCHECKED);
	}
}

void CLS_AdvPage::OnBnClickedCheckMainSub()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chkMainSub.GetCheck())
	{
		m_iStreamNo = 3;
		m_chkMainStream.SetCheck(BST_UNCHECKED);
		m_chkSubStream.SetCheck(BST_UNCHECKED);
	}
}

void CLS_AdvPage::OnBnClickedButtonArbootset()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	TAutoRebootSchedule tAutoRebootSchedule = {0};
	tAutoRebootSchedule.iSize = sizeof(TAutoRebootSchedule);
	tAutoRebootSchedule.iWeekDay = m_cboArbootWeek.GetCurSel();
	tAutoRebootSchedule.iHour = GetDlgItemInt(IDC_EDIT_ARBOOTHOUR);
	tAutoRebootSchedule.iMinute = GetDlgItemInt(IDC_EDIT_ARBOOTMIN);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_AUTOREBOOT, m_iChannelNo, &tAutoRebootSchedule, sizeof(tAutoRebootSchedule));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig faied! Logon id(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig success! Logon id(%d)", m_iLogonID);
	}
}

void CLS_AdvPage::OnCbnSelchangeComboArbootweek()
{
	// TODO: Add your control notification handler code here
	int iBytesReturned = 0;
	TAutoRebootSchedule tAutoRebootSchedule = {0};
	tAutoRebootSchedule.iWeekDay = m_cboArbootWeek.GetCurSel();
	tAutoRebootSchedule.iSize = sizeof(tAutoRebootSchedule);
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_AUTOREBOOT, m_iChannelNo, &tAutoRebootSchedule, sizeof(tAutoRebootSchedule), &iBytesReturned);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig faied! Logon id(%d)", m_iLogonID);
	}
	else
	{
		SetDlgItemInt(IDC_EDIT_ARBOOTHOUR, tAutoRebootSchedule.iHour);
		SetDlgItemInt(IDC_EDIT_ARBOOTMIN, tAutoRebootSchedule.iMinute);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig success! Logon id(%d)", m_iLogonID);
	}
}
