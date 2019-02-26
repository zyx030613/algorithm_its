// NTPPage.cpp : implementation file
//

#include "stdafx.h"
#include "NTPPage.h"

#define NTP_TEST_SUCCEED 1
#define NTP_TEST_FAIL 2
// CLS_NTPPage dialog

IMPLEMENT_DYNAMIC(CLS_NTPPage, CDialog)

CLS_NTPPage::CLS_NTPPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_NTPPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_NTPPage::~CLS_NTPPage()
{
}

void CLS_NTPPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NTPIP, m_edtNTPIp);
	DDX_Control(pDX, IDC_EDIT_NTPPORT, m_edtNTPPort);
	DDX_Control(pDX, IDC_EDIT_NTPINTERVAL, m_edtInterval);
	DDX_Control(pDX, IDC_BUTTON_NTP, m_btnNTP);
}


BEGIN_MESSAGE_MAP(CLS_NTPPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NTP, &CLS_NTPPage::OnBnClickedButtonNtp)
	ON_BN_CLICKED(IDC_BTN_LAN_NTP_TEST, &CLS_NTPPage::OnBnClickedBtnLanNtpTest)
END_MESSAGE_MAP()


// CLS_NTPPage message handlers
BOOL CLS_NTPPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtNTPIp.SetLimitText(31);
	m_edtNTPPort.SetLimitText(5);
	m_edtInterval.SetLimitText(8);
	UI_UpdateDialog();

	return TRUE;
}

void CLS_NTPPage::OnChannelChanged(int _iLogonID,int _iChannelNo, int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? 0 : _iChannelNo;

	UI_UpdateNTP();
}

void CLS_NTPPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_NTPPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_NTPIP, IDS_CONFIG_NTP_IP);
	SetDlgItemTextEx(IDC_STATIC_INTERVAL, IDS_CONFIG_ECOP_INTERVAL);
	SetDlgItemTextEx(IDC_BUTTON_NTP, IDS_SET);
	SetDlgItemTextEx(IDC_STXT_LAN_NTP_PORT, IDS_LOGON_PORT);
	SetDlgItemTextEx(IDC_BTN_LAN_NTP_TEST, IDS_LOG_TEST);

}

void CLS_NTPPage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	int iMsgType = LOWORD(_iWparam);
	switch(iMsgType)
	{
	case WCM_LASTERROR_INFO:
		{
			int iLParam = (int)_iLParam;
			NotifyResult(iLParam);
		}
		break;   
	default:
		break;
	}
}

void CLS_NTPPage::NotifyResult(int _iLParam)
{
	if (EC_NET_NTP_TEST_RESULT != _iLParam)
	{
		return;
	}

	DevLastError tDecLastError = {0};
	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_DEV_LASTERROR, m_iChannelNo, &tDecLastError, sizeof(tDecLastError));
	
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_RecvCommand(%d,%d)",m_iLogonID,m_iChannelNo);
		goto EXIT_FUNC;
	}

	if (EC_NET_NTP_TEST_RESULT != tDecLastError.iErrorID)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_RecvCommand(%d,%d),iErrId(%d)",m_iLogonID,m_iChannelNo, tDecLastError.iErrorID);
		goto EXIT_FUNC;
	}

	int iResult = _ttoi(tDecLastError.cErrorInfo);
	switch(iResult)
	{
	case NTP_TEST_SUCCEED:
		{
			AddLog(LOG_TYPE_SUCC,"","LogonId(%d) ErrId(%d), %s", m_iLogonID, tDecLastError.iErrorID, GetTextEx(IDS_NTP_TEST_SUCCEED));
			break;
		}
	case NTP_TEST_FAIL:
		{
			AddLog(LOG_TYPE_FAIL,"","LogonId(%d) ErrId(%d), %s", m_iLogonID, tDecLastError.iErrorID, GetTextEx(IDS_NTP_TEST_FAIL));
			break;
		}
	default:
		break;
	}

EXIT_FUNC:
	return;
}

BOOL CLS_NTPPage::UI_UpdateNTP()
{
	if (m_iLogonID < 0)
		return FALSE;

	char cNTPIP[32] = {0};
	unsigned short usNTPPort;
	int iInterval;
	int iRet = NetClient_GetNTPInfo(m_iLogonID, cNTPIP, &usNTPPort, &iInterval);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_NTPIP, cNTPIP);
		SetDlgItemInt(IDC_EDIT_NTPPORT, usNTPPort);
		SetDlgItemInt(IDC_EDIT_NTPINTERVAL, iInterval);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetNTPInfo(%d,%s,%d,%d)",m_iLogonID,cNTPIP,usNTPPort,iInterval);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetNTPInfo(%d,%s,%d,%d)",m_iLogonID,cNTPIP,usNTPPort,iInterval);
	}
	return TRUE;
}

void CLS_NTPPage::OnBnClickedButtonNtp()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	char cNTPIP[32] = {0};
	GetDlgItemText(IDC_EDIT_NTPIP, cNTPIP, 32);
	int iNTPPort = GetDlgItemInt(IDC_EDIT_NTPPORT);
	int iInterval = GetDlgItemInt(IDC_EDIT_NTPINTERVAL);
	if (iNTPPort < 0 || iNTPPort > 65535)
	{
		AddLog(LOG_TYPE_MSG,"","Please input a valid NTP port between 0 and 65535");
		return;
	}
	if (iInterval < 0 || iInterval > 65535)
	{
		AddLog(LOG_TYPE_MSG,"","Please input a valid interval between 0 and 65535");
		return;
	}

	unsigned short usNTPPort = iNTPPort;
	int iRet = NetClient_SetNTPInfo(m_iLogonID, cNTPIP, usNTPPort, iInterval);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetNTPInfo(%d,%s,%d,%d)",m_iLogonID,cNTPIP,usNTPPort,iInterval);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetNTPInfo(%d,%s,%d,%d)",m_iLogonID,cNTPIP,usNTPPort,iInterval);
	}
}

void CLS_NTPPage::OnBnClickedBtnLanNtpTest()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iNTPPort = GetDlgItemInt(IDC_EDIT_NTPPORT);
	if (iNTPPort < 0 || iNTPPort > 65535)
	{
		AddLog(LOG_TYPE_MSG,"","Please input a valid NTP port between 0 and 65535");
		return;
	}

	NTPTest tNTPTest = {0};
	char cNTPIP[LEN_32] = {0};
	GetDlgItemText(IDC_EDIT_NTPIP, cNTPIP, LEN_32);
	strncpy(tNTPTest.cServerIP, cNTPIP, LEN_32);
	tNTPTest.iServerPort = GetDlgItemInt(IDC_EDIT_NTPPORT);
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_NTP_TEST,  m_iChannelNo, &tNTPTest, sizeof(tNTPTest));
	if (RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SendCommand(%d,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetNTPInfo(%d,%d)",m_iLogonID,m_iChannelNo);
	}
}

