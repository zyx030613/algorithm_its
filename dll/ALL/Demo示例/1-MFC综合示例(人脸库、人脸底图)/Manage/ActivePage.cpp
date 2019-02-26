// ActivePage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ActivePage.h"
#include "../LogonActive.h"
#include "../Include/PROXY_INTERFACE.h"
using namespace PROXY_INTERFACE;

#define COLUMN_FACTORYID	0
#define COLUMN_LANIP		1
#define COLUMN_STATE		2

#define MSG_UPDATE_NVSLST		(WM_USER + 1111)

HWND CLS_ActivePage::s_hWnd = NULL;

const CString CONST_cstrMsg1_CH = "1、使用新主动模式前请先设置【本地监听端口】。\r\n";
const CString CONST_cstrMsg2_CH = "2、demo默认使用带目录服务器的新主动模式，带目录服务器的新主动模式需要设置【配置参数】才能登陆设备。\r\n";
const CString CONST_cstrMsg3_CH = "3、如果使用不带目录服务器的新主动模式，请不要选择【目录服务器】选择框，不需要设置【配置参数】。\r\n";
const CString CONST_cstrMsg4_CH = "4、点击【刷新】按钮，列表框可显示在线设备列表。\r\n";
const CString CONST_cstrMsg5_CH = "5、双击列表框某一条目可弹出登录对话框，输入正确的用户名和密码，可登陆该设备。";
const CString CONST_cstrUsrMsg_CH = CONST_cstrMsg1_CH + CONST_cstrMsg2_CH + CONST_cstrMsg3_CH + CONST_cstrMsg4_CH + CONST_cstrMsg5_CH;

const CString CONST_cstrMsg1_EN = "1. Before using the new active mode, please set the local [listening port] first.\r\n";
const CString CONST_cstrMsg2_EN = "2. The demo uses the new active mode with the directory server by default. The new active mode with the directory server needs to set [configuration parameters] to log in to the device.\r\n";
const CString CONST_cstrMsg3_EN = "3. If you use the new active mode without a directory server, please do not select the [Directory Server] selection box, and you do not need to set [Configuration Parameters].\r\n";
const CString CONST_cstrMsg4_EN = "4. Click the [Refresh] button. The list box displays the online device list. \r\n";
const CString CONST_cstrMsg5_EN = "5. Double-click on an item in the list box to pop up the login dialog. Enter the correct user name and password to log in to the device.";
const CString CONST_cstrUsrMsg_EN = CONST_cstrMsg1_EN + CONST_cstrMsg2_EN + CONST_cstrMsg3_EN + CONST_cstrMsg4_EN + CONST_cstrMsg5_EN;

// CLS_ActivePage dialog

IMPLEMENT_DYNAMIC(CLS_ActivePage, CDialog)

CLS_ActivePage::CLS_ActivePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ActivePage::IDD, pParent)
{
	CString strFile;
	strFile.Format("%s%s", ExtractFilePath(), "ActiveConfig.ini");
	m_iniFile.SetFileName(strFile.GetString());

	m_iRegID = -1;
}

CLS_ActivePage::~CLS_ActivePage()
{
}

void CLS_ActivePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_REG_SERVER, m_chkRegServer);
	DDX_Control(pDX, IDC_EDIT_MNG_ACT_LOCA_IP, m_edtLocalIp);
	DDX_Control(pDX, IDC_EDIT_MNG_ACT_DSM_IP, m_edtDsmIp);
	DDX_Control(pDX, IDC_EDIT_MNG_ACT_DSM_PORT, m_edtDsmPort);
	DDX_Control(pDX, IDC_LIST_ACTIVE_REGISTER_LIST, m_lstNvsLst);
	DDX_Control(pDX, IDC_EDIT_ACTIVE_LISTEN_PORT, m_edtActivePort);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_NAME, m_edtRegAccountName);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_PWD, m_edtRegAccountPwd);
	DDX_Control(pDX, IDC_EDIT_ACTIVE_USER_MSG, m_edtUsrMsg);
	DDX_Control(pDX, IDC_EDIT_MNG_ACTIVE_LOCAL_PORT, m_edtLocalPort);
}


BEGIN_MESSAGE_MAP(CLS_ActivePage, CDialog)
	ON_BN_CLICKED(IDC_CHECK_REG_SERVER, &CLS_ActivePage::OnBnClickedCheckRegServer)
	ON_BN_CLICKED(IDC_BUTTONMNG_ACTIVE_SET, &CLS_ActivePage::OnBnClickedButtonListenPortSet)
	ON_BN_CLICKED(IDC_BUTTON_DIRECTORY_SET, &CLS_ActivePage::OnBnClickedButtonDirectorySet)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_REGISTER_LIST, &CLS_ActivePage::OnBnClickedButtonRefreshRegisterList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACTIVE_REGISTER_LIST, &CLS_ActivePage::OnNMDblclkListActiveRegisterList)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(MSG_UPDATE_NVSLST, &CLS_ActivePage::OnNvsLstMsg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLS_ActivePage message handlers

BOOL CLS_ActivePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	s_hWnd = this->GetSafeHwnd();

	m_edtActivePort.SetLimitText(LEN_16);
	m_edtLocalIp.SetLimitText(LEN_64);
	m_edtLocalPort.SetLimitText(LEN_16);
	m_edtDsmIp.SetLimitText(LEN_64);
	m_edtDsmPort.SetLimitText(LEN_32);
	m_edtRegAccountName.SetLimitText(LEN_64);
	m_edtRegAccountPwd.SetLimitText(LEN_64);
	m_edtUsrMsg.SetLimitText(LEN_1024);
	m_chkRegServer.SetCheck(BST_CHECKED);
	
	ReadConfig();

	m_lstNvsLst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	UI_UpdateDialogText();

	LoadProxySDK();

	if (DLL_LOAD_SUCCESS == CLS_NsLook_Interface::LoadDLL())
	{
		NSLook_Startup();
	}
	else
	{
		MessageBox(_T("error in load nslook.dll"), _T(""), MB_TOPMOST|MB_OK);
		this->EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_ActivePage::ReadConfig()
{
	int iListenPort = m_iniFile.ReadInteger("LocalConfig", "ListenPort", 5004);
	SetDlgItemInt(IDC_EDIT_ACTIVE_LISTEN_PORT, iListenPort);

	int iLocalPort = m_iniFile.ReadInteger("LocalConfig", "WanPort", 5555);
	CString cstrWanIP = m_iniFile.ReadString("LocalConfig", "WanIP", "0.0.0.0");
	SetDlgItemInt(IDC_EDIT_MNG_ACTIVE_LOCAL_PORT, iLocalPort);
	SetDlgItemText(IDC_EDIT_MNG_ACT_LOCA_IP, cstrWanIP);

	int iRegPort = m_iniFile.ReadInteger("RegisterConfig", "RegPort", 6004);
	SetDlgItemInt(IDC_EDIT_MNG_ACT_DSM_PORT, iRegPort);
	CString cstrRegIP = m_iniFile.ReadString("RegisterConfig", "RegIP", "0.0.0.0");
	SetDlgItemText(IDC_EDIT_MNG_ACT_DSM_IP, cstrRegIP);
	CString cstrRegAccount = m_iniFile.ReadString("RegisterConfig", "RegAccount", "QQ");
	SetDlgItemText(IDC_EDIT_ACCOUNT_NAME, cstrRegAccount);
	CString cstrRegRegPassword = m_iniFile.ReadString("RegisterConfig", "RegPassword", "QQQQ");
	SetDlgItemText(IDC_EDIT_ACCOUNT_PWD, cstrRegRegPassword);
}

void CLS_ActivePage::WriteConfig()
{
	m_iniFile.WriteInteger("ActiveType", "ShowType", 0);

	int iListenPort = GetDlgItemInt(IDC_EDIT_ACTIVE_LISTEN_PORT);
	m_iniFile.WriteInteger("LocalConfig", "ListenPort", iListenPort);

	int iLocalPort = GetDlgItemInt(IDC_EDIT_MNG_ACTIVE_LOCAL_PORT);
	m_iniFile.WriteInteger("LocalConfig", "WanPort", iLocalPort);
	CString cstrWanIP;
	GetDlgItemText(IDC_EDIT_MNG_ACT_LOCA_IP, cstrWanIP);
	m_iniFile.WriteString("LocalConfig", "WanIP", (char*)(LPCTSTR)cstrWanIP);

	int iRegPort = GetDlgItemInt(IDC_EDIT_MNG_ACT_DSM_PORT);
	m_iniFile.WriteInteger("RegisterConfig", "RegPort", iRegPort);
	CString cstrRegIP;
	GetDlgItemText(IDC_EDIT_MNG_ACT_DSM_IP, cstrRegIP);
	m_iniFile.WriteString("RegisterConfig", "RegIP", (char*)(LPCTSTR)cstrRegIP);
	CString cstrRegAccount;
	GetDlgItemText(IDC_EDIT_ACCOUNT_NAME, cstrRegAccount);
	m_iniFile.WriteString("RegisterConfig", "RegAccount", (char*)(LPCTSTR)cstrRegAccount);
	CString cstrRegRegPassword;
	GetDlgItemText(IDC_EDIT_ACCOUNT_PWD, cstrRegRegPassword);
	m_iniFile.WriteString("RegisterConfig", "RegPassword", (char*)(LPCTSTR)cstrRegRegPassword);
}

void CLS_ActivePage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
	if (1 == _iLanguage)
	{
		m_edtUsrMsg.SetWindowText(CONST_cstrUsrMsg_EN);
	}
	else
	{
		m_edtUsrMsg.SetWindowText(CONST_cstrUsrMsg_CH);
	}

	OnBnClickedButtonRefreshRegisterList();
}

void CLS_ActivePage::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_MNG_ACTIVE_LOCAL_IP, IDS_MNG_LOCAL_IP);
	SetDlgItemTextEx(IDC_STATIC_MNG_ACT_DSM_IP, IDS_MNG_DSM_IP);
	SetDlgItemTextEx(IDC_STATIC_MNG_ACT_DSM_PORT, IDS_MNG_DSM_PORT);
	SetDlgItemTextEx(IDC_STATIC_MNG_ACT_BAK_DSM_IP, IDS_MNG_BAK_DSM_IP);
	SetDlgItemTextEx(IDC_STATIC_MNG_ACT_DSM_BAK_PORT,IDS_MNG_BAK_DSM_PORT);
	SetDlgItemTextEx(IDC_BUTTONMNG_ACTIVE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_REFRESH_REGISTER_LIST, IDS_MNG_ADMIN_REFRESH);
	SetDlgItemTextEx(IDC_STATIC_ACTIVE_LISTEN_PORT, IDS_ACTIVE_LISTEN_PORT);
	SetDlgItemTextEx(IDC_STATIC_ACTIVE_USER_MSG, IDS_MNG_ACTIVE_USR_MSG);
	SetDlgItemTextEx(IDC_CHECK_REG_SERVER, IDS_MNG_ACTIVE_REGISTER);
	SetDlgItemTextEx(IDC_STATIC_CFG_ACTIVE_PARA, IDS_MNG_ACTIVE_SET_PARA);
	SetDlgItemTextEx(IDC_STATIC_ACCOUNT_NAME, IDS_MNG_ACTIVE_DSM_NAME);
	SetDlgItemTextEx(IDC_STATIC_ACCOUNT_PWD, IDS_MNG_ACTIVE_DSM_PWD);
	SetDlgItemTextEx(IDC_STATIC_ACTIVE_NVS_TOTAL_COUNT, IDS_MNG_ACTIVE_ONLINE_COUNT);
	SetDlgItemTextEx(IDC_BUTTON_DIRECTORY_SET, IDS_SET);

	InsertColumn(m_lstNvsLst, COLUMN_FACTORYID, IDS_MNG_ADMIN_FACTORY_ID, LVCFMT_LEFT, 260);
	InsertColumn(m_lstNvsLst, COLUMN_LANIP, IDS_MNG_DNS_LAN_IP, LVCFMT_CENTER, 140);
	InsertColumn(m_lstNvsLst, COLUMN_STATE, IDS_CONFIG_WIFI_STATE, LVCFMT_CENTER, 80);
	m_edtUsrMsg.SetWindowText(CONST_cstrUsrMsg_CH);
}

void CLS_ActivePage::OnBnClickedCheckRegServer()
{
	if (BST_CHECKED == m_chkRegServer.GetCheck())
	{
		GetDlgItem(IDC_STATIC_CFG_ACTIVE_PARA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MNG_ACTIVE_LOCAL_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MNG_ACT_LOCA_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MNG_ACT_DSM_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MNG_ACT_DSM_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MNG_ACT_DSM_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MNG_ACT_DSM_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ACCOUNT_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ACCOUNT_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ACCOUNT_PWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ACCOUNT_PWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_DIRECTORY_SET)->ShowWindow(SW_SHOW);
	} 
	else
	{
		GetDlgItem(IDC_STATIC_CFG_ACTIVE_PARA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MNG_ACTIVE_LOCAL_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MNG_ACT_LOCA_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MNG_ACT_DSM_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MNG_ACT_DSM_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MNG_ACT_DSM_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MNG_ACT_DSM_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ACCOUNT_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ACCOUNT_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ACCOUNT_PWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ACCOUNT_PWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_DIRECTORY_SET)->ShowWindow(SW_HIDE);
	}
}

void CLS_ActivePage::OnBnClickedButtonListenPortSet()
{
	int iActivePort = GetDlgItemInt(IDC_EDIT_ACTIVE_LISTEN_PORT);
	int iRet = NetClient_SetPort( iActivePort, iActivePort);
	if (RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetPort (%d, %d)", iActivePort, iActivePort);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetPort (%d, %d)", iActivePort, iActivePort);
	}

	if (NetClient_ProxyStart)
	{
		NetClient_ProxyStart(iActivePort,1);
	}

	WriteConfig();
}

void CLS_ActivePage::OnBnClickedButtonDirectorySet()
{
	CString cstrLocalIp;
	int iLocalPort = 0;
	GetDlgItemText(IDC_EDIT_MNG_ACTIVE_LOCA_IP, cstrLocalIp);
	iLocalPort = GetDlgItemInt(IDC_EDIT_MNG_ACTIVE_LOCAL_PORT);

	ActiveNetWanInfo tLocal = {0};
	tLocal.iSize = sizeof(ActiveNetWanInfo);
	strcpy_s(tLocal.cWanIP, sizeof(tLocal.cWanIP), cstrLocalIp.GetBuffer());
	tLocal.iWanPort = iLocalPort;
	int iRet = NetClient_SetDsmConfig(DSM_CMD_SET_NET_WAN_INFO, &tLocal, sizeof(ActiveNetWanInfo));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDsmConfig::DSM_CMD_SET_NET_WAN_INFO");
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDsmConfig::DSM_CMD_SET_NET_WAN_INFO");
	}

	CString cstrDsmIp;
	int iDsmPort = 0;
	GetDlgItemText(IDC_EDIT_MNG_ACT_DSM_IP, cstrDsmIp);
	iDsmPort = GetDlgItemInt(IDC_EDIT_MNG_ACT_DSM_PORT);
	CString cstrAccountName;
	CString cstrAccountPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_NAME, cstrAccountName);
	GetDlgItemText(IDC_EDIT_ACCOUNT_PWD, cstrAccountPwd);
	ActiveDirectoryInfo tDirectory = {0};
	tDirectory.iSize = sizeof(ActiveNetWanInfo);
	strcpy_s(tDirectory.cDsmIP, sizeof(tDirectory.cDsmIP), cstrDsmIp.GetBuffer());
	tDirectory.iDsmPort = iDsmPort;
	strcpy_s(tDirectory.cAccontName, sizeof(tDirectory.cAccontName), cstrAccountName.GetBuffer());
	strcpy_s(tDirectory.cAccontPwd, sizeof(tDirectory.cAccontPwd), cstrAccountPwd.GetBuffer());
	iRet = NetClient_SetDsmConfig(DSM_CMD_SET_DIRECTORY_INFO, &tDirectory, sizeof(ActiveDirectoryInfo));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDsmConfig::DSM_CMD_SET_DIRECTORY_INFO");
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDsmConfig::DSM_CMD_SET_DIRECTORY_INFO");
	}

	WriteConfig();
}

void CLS_ActivePage::OnBnClickedButtonRefreshRegisterList()
{
	if (BST_UNCHECKED == m_chkRegServer.GetCheck())
	{
		UpdateDevLstByLocalServer();
	}
	else
	{
		UpdateDevLstByRegisterServer();
	}
}

void CLS_ActivePage::OnNMDblclkListActiveRegisterList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (0 == m_lstNvsLst.GetItemCount())
	{
		return;
	}

	DEVICE_INFO tDevInit = {0};
	m_lstNvsLst.GetItemText(pNMItemActivate->iItem, 0, tDevInit.cID, LEN_32);
	strcpy_s(tDevInit.cUserName,sizeof(tDevInit.cUserName),"Admin");
	strcpy_s(tDevInit.cPassword,sizeof(tDevInit.cPassword),"1111");

	CLS_LogonActive clsLogonActive(&tDevInit);
	if(IDOK != clsLogonActive.DoModal())
	{
		return;
	}

	int iOldLogonID = -1;
	PDEVICE_INFO ptDevLogon = clsLogonActive.GetDeviceInfo();
	PDEVICE_INFO ptDevFind = FindDevice(ptDevLogon->cIP,ptDevLogon->iPort, ptDevLogon->cProxy, ptDevLogon->cID, &iOldLogonID);
	if (NULL != ptDevFind)
	{
		if(LOGON_SUCCESS == NetClient_GetLogonStatus(iOldLogonID))
		{
			AddLog(LOG_TYPE_MSG,"","FindDevice(%s,%s) device already exist!"
				,ptDevFind->cIP, ptDevFind->cID);
			return;
		}
	}

	int iServerType = BST_UNCHECKED == m_chkRegServer.GetCheck() ? SERVER_ACTIVE : SERVER_REG_ACTIVE;
	LogonActiveServer tLogonPara = {0};
	tLogonPara.iSize = sizeof(LogonActiveServer);
	strcpy_s(tLogonPara.cUserName, sizeof(tLogonPara.cUserName), ptDevLogon->cUserName);
	strcpy_s(tLogonPara.cUserPwd, sizeof(tLogonPara.cUserPwd), ptDevLogon->cPassword);
	strcpy_s(tLogonPara.cProductID, sizeof(tLogonPara.cProductID), ptDevLogon->cID);
	int iLogonID = NetClient_Logon_V4(iServerType, &tLogonPara, sizeof(LogonActiveServer));
	if (iLogonID >= 0)
	{
		AddLog(LOG_TYPE_SUCC,ptDevLogon->cIP,"(%d)NetClient_Logon_V4",iLogonID);
		if (NULL != ptDevFind)
		{
			return;
		}
		PDEVICE_INFO ptDevNew = AddDevice(iLogonID);
		if (NULL != ptDevNew)
		{
			memcpy_s(ptDevNew, sizeof(DEVICE_INFO), ptDevLogon, sizeof(DEVICE_INFO));
			ptDevNew->hItem = NULL;
			ptDevNew->uiInterTalkID  = -1;
		}
		else
		{
			AddLog(LOG_TYPE_MSG,"","AddDevice(%d) Can not add device", iLogonID);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,ptDevLogon->cIP,"NetClient_Logon_V4(%s)",ptDevLogon->cID);
	}

	*pResult = 0;
}

void CLS_ActivePage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
}

void CLS_ActivePage::OnDestroy()
{
	CLS_BasePage::OnDestroy();
	if (m_iRegID >= 0)
	{
		NSLook_LogoffServer(m_iRegID);
	}
}

void CLS_ActivePage::UpdateDevLstByRegisterServer()
{
	if (m_iRegID >= 0)
	{
		NSLook_LogoffServer(m_iRegID);
	}

	char cRegIP[LEN_64] = {0};
	char cRegUser[LEN_64] = {0};
	char cRegPwd[LEN_64] = {0};
	GetDlgItemText(IDC_EDIT_MNG_ACT_DSM_IP,cRegIP,sizeof(cRegIP));
	int iRegPort = GetDlgItemInt(IDC_EDIT_MNG_ACT_DSM_PORT);
	GetDlgItemText(IDC_EDIT_ACCOUNT_NAME, cRegUser, sizeof(cRegUser));
	GetDlgItemText(IDC_EDIT_ACCOUNT_PWD, cRegPwd, sizeof(cRegPwd));

	m_iRegID = NSLook_LogonServer(cRegIP, iRegPort, true);

	Sleep(1000);

	m_lstNvsLst.DeleteAllItems();
	int iCount = 0;
	int iRet = NSLook_GetCount(m_iRegID, cRegUser, cRegPwd, &iCount,TYPE_NVS);
	if(RET_SUCCESS == iRet)
	{
		iRet = NSLook_GetList(m_iRegID, cRegUser, cRegPwd, 0, NULL, &CLS_ActivePage::NvsLstNotify, TYPE_NVS);
		if (RET_SUCCESS != iRet)
		{
			AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_GetList(%d,%s,%s,,,TYPE_NVS)"
				,iRet,m_iRegID, cRegUser, cRegPwd);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_GetCount(%d,%s,%s,,TYPE_NVS)"
			,iRet,m_iRegID,cRegUser,cRegPwd);
	}

	SetDlgItemInt(IDC_EDIT_ACTIVE_NVS_TOTAL_COUNT, iCount);
}

int CLS_ActivePage::NvsLstNotify(int _iCount, st_NvsSingle* _ptNvs)
{
	__try
	{
		if (NULL != _ptNvs)
		{
			LRESULT lRet = SendMessageTimeout(s_hWnd, MSG_UPDATE_NVSLST, (WPARAM)_ptNvs, (LPARAM)_iCount, SMTO_NORMAL, 3000, NULL);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//AddLog(LOG_TYPE_MSG,"","NvsLstNotify exception");
	}

	return 0;
}

LRESULT CLS_ActivePage::OnNvsLstMsg(WPARAM wParam, LPARAM lParam)
{
	__try
	{
		st_NvsSingle* ptNvs = (st_NvsSingle*)wParam;
		int iCount = (int)lParam;
		for (int i = 0 ; i < iCount; ++i)
		{
			AddOneNvsItem(ptNvs + i);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		AddLog(LOG_TYPE_MSG,"","AddOneNvsItem exception");
	}

	return 0;
}

void CLS_ActivePage::AddOneNvsItem(st_NvsSingle* _ptNvs)
{
	int iItem = -1;
	LVFINDINFO info;
	info.flags = LVFI_STRING;
	info.psz = _ptNvs->cFactoryID;
	while ((iItem = m_lstNvsLst.FindItem(&info, iItem)) != -1)
	{
		CString strID = m_lstNvsLst.GetItemText(iItem, 0);
		if (0 == strID.CompareNoCase(_ptNvs->cFactoryID))
		{
			return;
		}
	}

	iItem = m_lstNvsLst.GetItemCount();
	m_lstNvsLst.InsertItem(iItem, _ptNvs->cFactoryID);
	m_lstNvsLst.SetItemText(iItem, COLUMN_LANIP, _ptNvs->cNvsIP);
	m_lstNvsLst.SetItemText(iItem, COLUMN_STATE, GetTextEx(IDS_CONFIG_WIFI_ONLINE));
}

void CLS_ActivePage::UpdateDevLstByLocalServer()
{
	m_lstNvsLst.DeleteAllItems();

	char* pcDevList = NULL;
	int iRegisterCount = 0;
	NetClient_GetDsmRegstierInfo(DSM_CMD_GET_REGISTER_COUNT, &iRegisterCount, sizeof(int));
	if (iRegisterCount <= 0)
	{
		AddLog(LOG_TYPE_MSG, "", "iRegisterCount(%d) <= 0", iRegisterCount);
		goto END;
	}

	pcDevList = new char[iRegisterCount * LEN_32];
	if (NULL == pcDevList)
	{
		goto END;
	}
	NetClient_GetDsmRegstierInfo(DSM_CMD_GET_REGISTER_DEVLIST, pcDevList, iRegisterCount * LEN_32);

	for (int iItem = 0; iItem < iRegisterCount; ++iItem)
	{
		char cFactoryID[LEN_32] = {0};
		memcpy(cFactoryID, pcDevList + iItem * LEN_32, LEN_32);
		m_lstNvsLst.InsertItem(iItem, cFactoryID);
		m_lstNvsLst.SetItemText(iItem, COLUMN_LANIP, "192.168.1.2");

		DsmOnline tOnline = {0};
		tOnline.iSize = sizeof(DsmOnline);
		strncpy_s(tOnline.cProductID, LEN_32, cFactoryID, LEN_32);
		NetClient_GetDsmRegstierInfo(DSM_CMD_GET_ONLINE_STATE, &tOnline, sizeof(DsmOnline));
		if (DSM_STATE_ONLINE == tOnline.iOnline)
		{
			m_lstNvsLst.SetItemText(iItem, COLUMN_STATE, GetTextEx(IDS_CONFIG_WIFI_ONLINE));
		}
		else
		{
			m_lstNvsLst.SetItemText(iItem, COLUMN_STATE, GetTextEx(IDS_CONFIG_WIFI_OFFLINE));
		}	
	}

END:
	if (NULL != pcDevList)
	{
		delete []pcDevList;
		pcDevList = NULL;
	}
	SetDlgItemInt(IDC_EDIT_ACTIVE_NVS_TOTAL_COUNT, iRegisterCount);
}
