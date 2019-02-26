// E:\SVN\186\SDK_ALL\trunk\Demo\NetClientDemo\Config\LinkHttp.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "LinkHttp.h"


// CLS_LinkHttp dialog

IMPLEMENT_DYNAMIC(CLS_LinkHttp, CDialog)

CLS_LinkHttp::CLS_LinkHttp(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_LinkHttp::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_LinkHttp::~CLS_LinkHttp()
{
}

void CLS_LinkHttp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LINK_HTTP_INDEX, m_cboLinkHttpIndex);
	DDX_Control(pDX, IDC_COMBO_LINK_HTTP_PARANUM, m_cboLinkHttpParaNum);
	DDX_Control(pDX, IDC_CHECK_LINK_HTTP_ENABLE, m_chkLinkHttpEnable);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_RECORDNAME, m_edtLinkHttpRecordName);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_DESCRIPTION, m_edtRecordDecription);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_USERNAME, m_edtLinkHttpUserName);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_PASSWORD, m_edtLinkHttpPassword);
	DDX_Control(pDX, IDC_EDITLINK_HTTP_IP_ADDRESSS, m_edtLinkHttpIpAddress);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_PORT, m_edtLinkHttpPort);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_PARA1, m_edtLinkHttpPara1);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_PARA2, m_edtLinkHttpPara2);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_PARA3, m_edtLinkHttpPara3);
	DDX_Control(pDX, IDC_EDIT_LINK_HTTP_PARA4, m_edtLinkHttpPara4);
}


BEGIN_MESSAGE_MAP(CLS_LinkHttp, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_LINK_HTTP_INDEX, &CLS_LinkHttp::OnCbnSelchangeComboLinkHttpIndex)
	ON_BN_CLICKED(IDC_BUTTON_LINK_HTTP_SET, &CLS_LinkHttp::OnBnClickedButtonLinkHttpSet)
	ON_BN_CLICKED(IDC_BUTTON_LINK_HTTP_TEST, &CLS_LinkHttp::OnBnClickedButtonLinkHttpTest)
END_MESSAGE_MAP()


// CLS_LinkHttp message handlers

BOOL CLS_LinkHttp::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtLinkHttpRecordName.SetLimitText(LEN_32);
	m_edtRecordDecription.SetLimitText(LEN_64);
	m_edtLinkHttpUserName.SetLimitText(LEN_32);
	m_edtLinkHttpPassword.SetLimitText(LEN_32);
	m_edtLinkHttpIpAddress.SetLimitText(LEN_64);
	m_edtLinkHttpPort.SetLimitText(LEN_8);
	m_edtLinkHttpPara1.SetLimitText(LEN_64);
	m_edtLinkHttpPara2.SetLimitText(LEN_64);
	m_edtLinkHttpPara3.SetLimitText(LEN_64);
	m_edtLinkHttpPara4.SetLimitText(LEN_64);

	for (int i=0; i<MAX_LINK_HTTP_INDEX; ++i)
	{
		m_cboLinkHttpIndex.AddString(IntToCString(i));
	}
	m_cboLinkHttpIndex.SetCurSel(0);

	for (int i=0; i<MAX_LINK_HTTP_PARA_NUM; ++i)
	{
		m_cboLinkHttpParaNum.AddString(IntToCString(i + 1));
	}
	m_cboLinkHttpParaNum.SetCurSel(0);

	UI_UpdateDialogText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_LinkHttp::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
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
	UI_UpdateLinkHttpInfo();
}

void CLS_LinkHttp::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialogText();
	UI_UpdateLinkHttpInfo();
}

void CLS_LinkHttp::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (_ulLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)", _ulLogonID);
		return;
	}

	int iMessage = _iWparam & 0xFFFF;
	switch (iMessage)
	{
	case WCM_HTTP_TEST_CMD:
		{
			if (0 == (int)_iLParam)
			{
				MessageBox("Test Success!", _T(""));
			}
			else if (1 == (int)_iLParam)
			{
				MessageBox("Test Failed!", _T(""));
			}
			else
			{
				AddLog(LOG_TYPE_MSG,"","Invalid result(%d)", (int)_iLParam);
			}
		}
		break;
	default:
		break;
	}
}

void CLS_LinkHttp::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	if (_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)", _iLogonID);
		return;
	}

	if (_iChannelNo == m_iChannelNo)//只刷新参数改变的通道
	{
		switch(_iParaType)
		{
		case PARA_LINK_HTTP_INFO:
			{
				UI_UpdateLinkHttpInfo();
			}
			break;
		default:
			break;
		}
	}
}

void CLS_LinkHttp::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_INDEX, IDS_SMART_INDEX);
	SetDlgItemTextEx(IDC_CHECK_LINK_HTTP_ENABLE, IDS_ITS_ENABLED);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_RECORDNAME, IDS_LINKHTTP_RECORDNAME);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_DESCRIPTION, IDS_LINKHTTP_RECODDESCRPTION);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_USERNAME, IDS_CFG_USER_NAME);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_PASSWORD, IDS_CFG_3G_ADV_PASSWORD);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_IP_DOMINNAME, IDS_LINKHTTP_IP_DOMINNAME);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_PORT, IDS_LOGON_PORT);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_PARANUM, IDS_LINKHTTP_LINKPARANUM);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_PARA1, IDS_CONFIG_ITS_TIMERANGE_PARAM1);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_PARA2, IDS_CONFIG_ITS_TIMERANGE_PARAM2);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_PARA3, IDS_CONFIG_ITS_TIMERANGE_PARAM3);
	SetDlgItemTextEx(IDC_STATIC_LINK_HTTP_PARA4, IDS_CONFIG_ITS_TIMERANGE_PARAM4);
	SetDlgItemTextEx(IDC_BUTTON_LINK_HTTP_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_LINK_HTTP_TEST, IDS_LOG_TEST);
}

void CLS_LinkHttp::UI_UpdateLinkHttpInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)", m_iLogonID);
		return;
	}

	LinkHttpInfo tInfo = {0};
	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_LINK_HTTP_INFO, m_iChannelNo, &tInfo, sizeof(LinkHttpInfo), &iReturnByte);
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_GetDevConfig][NET_CLIENT_LINK_HTTP_INFO] Set fail,error = %d", GetLastError());
	}
	else
	{
		m_cboLinkHttpIndex.SetCurSel(tInfo.iIndex);
		m_chkLinkHttpEnable.SetCheck(tInfo.iEnable);
		m_edtLinkHttpRecordName.SetWindowText(tInfo.cRecordName);
		m_edtRecordDecription.SetWindowText(tInfo.cRecordDecription);
		m_edtLinkHttpUserName.SetWindowText(tInfo.cUserName);
		m_edtLinkHttpPassword.SetWindowText(tInfo.cUserPassword);
		m_edtLinkHttpIpAddress.SetWindowText(tInfo.cIpAddress);
		SetDlgItemInt(IDC_EDIT_LINK_HTTP_PORT, tInfo.iPort);
		m_cboLinkHttpParaNum.SetCurSel(tInfo.iParamNum - 1);
		m_edtLinkHttpPara1.SetWindowText(tInfo.cParam[0]);
		m_edtLinkHttpPara2.SetWindowText(tInfo.cParam[1]);
		m_edtLinkHttpPara3.SetWindowText(tInfo.cParam[2]);
		m_edtLinkHttpPara4.SetWindowText(tInfo.cParam[3]);

		AddLog(LOG_TYPE_SUCC, "", "[NetClient_GetDevConfig][NET_CLIENT_LINK_HTTP_INFO] set success!");
	}
}

void CLS_LinkHttp::GetInfoByDialog(LinkHttpInfo* _ptInfo)
{
	if (_ptInfo == NULL)
	{
		return;
	}

	int iIndex = m_cboLinkHttpIndex.GetCurSel();
	int iEnable = m_chkLinkHttpEnable.GetCheck();
	CString cstrRecordName;
	CString cstrRecordDecription;
	CString cstrUserName;
	CString cstrUserPassword;
	CString cstrIpAddress;
	m_edtLinkHttpRecordName.GetWindowText(cstrRecordName);
	m_edtRecordDecription.GetWindowText(cstrRecordDecription);
	m_edtLinkHttpUserName.GetWindowText(cstrUserName);
	m_edtLinkHttpPassword.GetWindowText(cstrUserPassword);
	m_edtLinkHttpIpAddress.GetWindowText(cstrIpAddress);
	int iPort = GetDlgItemInt(IDC_EDIT_LINK_HTTP_PORT);
	int iParamNum = m_cboLinkHttpIndex.GetCurSel() + 1;
	CString cstrParam[MAX_LINK_HTTP_PARA_NUM];
	m_edtLinkHttpPara1.GetWindowText(cstrParam[0]);
	m_edtLinkHttpPara2.GetWindowText(cstrParam[1]);
	m_edtLinkHttpPara3.GetWindowText(cstrParam[2]);
	m_edtLinkHttpPara4.GetWindowText(cstrParam[3]);

	_ptInfo->iBufSize = sizeof(LinkHttpInfo);
	_ptInfo->iIndex = iIndex;
	_ptInfo->iEnable = iEnable;
	strcpy(_ptInfo->cRecordName, cstrRecordName.GetBuffer());
	strcpy(_ptInfo->cRecordDecription, cstrRecordDecription.GetBuffer());
	strcpy(_ptInfo->cUserName, cstrUserName.GetBuffer());
	strcpy(_ptInfo->cUserPassword, cstrUserPassword.GetBuffer());
	strcpy(_ptInfo->cIpAddress, cstrIpAddress.GetBuffer());
	_ptInfo->iPort = iPort;
	_ptInfo->iParamNum = iParamNum;
	strcpy(_ptInfo->cParam[0], cstrParam[0].GetBuffer());
	strcpy(_ptInfo->cParam[1], cstrParam[1].GetBuffer());
	strcpy(_ptInfo->cParam[2], cstrParam[2].GetBuffer());
	strcpy(_ptInfo->cParam[3], cstrParam[3].GetBuffer());
}

void CLS_LinkHttp::OnCbnSelchangeComboLinkHttpIndex()
{
	UI_UpdateLinkHttpInfo();
}

void CLS_LinkHttp::OnBnClickedButtonLinkHttpSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)", m_iLogonID);
		return;
	}

	LinkHttpInfo tInfo = {0};
	GetInfoByDialog(&tInfo);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_LINK_HTTP_INFO, m_iChannelNo, &tInfo, sizeof(LinkHttpInfo));
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SetDevConfig][NET_CLIENT_LINK_HTTP_INFO] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SetDevConfig][NET_CLIENT_LINK_HTTP_INFO] set success!");
	}
}

void CLS_LinkHttp::OnBnClickedButtonLinkHttpTest()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)", m_iLogonID);
		return;
	}

	LinkHttpInfo tInfo = {0};
	GetInfoByDialog(&tInfo);
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_TEST_HTTP, m_iChannelNo, &tInfo, sizeof(LinkHttpInfo));
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand][COMMAND_ID_TEST_HTTP]");
	}
	else 
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand][COMMAND_ID_TEST_HTTP]");
	}
}
