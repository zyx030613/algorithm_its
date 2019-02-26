// NvsDSMPage.cpp : implementation file
//

#include "stdafx.h"
#include "NvsDSMPage.h"
#include "../LogonView.h"

#define MSG_NVS		(WM_USER + 1102)

HWND CLS_NvsDSMPage::s_hWnd = NULL;

// CLS_NvsDSMPage dialog

IMPLEMENT_DYNAMIC(CLS_NvsDSMPage, CDialog)

CLS_NvsDSMPage::CLS_NvsDSMPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_NvsDSMPage::IDD, pParent)
{
	m_iRegID = -1;
	memset(m_cRegUser,0,sizeof(m_cRegUser));
	memset(m_cRegPwd,0,sizeof(m_cRegPwd));	
}

CLS_NvsDSMPage::~CLS_NvsDSMPage()
{

}

void CLS_NvsDSMPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DSM_NVS, m_lvNVS);
	DDX_Control(pDX, IDC_CBO_DSM_NVS_QUERY_TYPE, m_cboQueryType);
	DDX_Control(pDX, IDC_CBO_DSM_NVS_PAGE, m_cboPage);
}


BEGIN_MESSAGE_MAP(CLS_NvsDSMPage, CLS_BasePage)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DSM_NVS_REFRESH, &CLS_NvsDSMPage::OnBnClickedBtnDsmNvsRefresh)
	ON_MESSAGE(MSG_NVS,&CLS_NvsDSMPage::OnNvsMsg)
	ON_BN_CLICKED(IDC_BTN_DSM_NVS_QUERY, &CLS_NvsDSMPage::OnBnClickedBtnDsmNvsQuery)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DSM_NVS, &CLS_NvsDSMPage::OnNMDblclkListDsmNvs)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DSM_NVS, &CLS_NvsDSMPage::OnNMClickListDsmNvs)
	ON_BN_CLICKED(IDC_BTN_GET_COUNT, &CLS_NvsDSMPage::OnBnClickedBtnGetCount)
END_MESSAGE_MAP()


// CLS_NvsDSMPage message handlers

BOOL CLS_NvsDSMPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	s_hWnd = this->GetSafeHwnd();

	((CEdit*)GetDlgItem(IDC_EDIT_DSM_NVS_ID))->SetLimitText(31);

	m_lvNVS.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	UI_UpdateDialog();

	m_cboQueryType.SetCurSel(0);

	m_lvNVS.SetSortType(3,SORT_TYPE_IP);
	m_lvNVS.SetSortType(4,SORT_TYPE_IP);
	m_lvNVS.SetSortType(5,SORT_TYPE_INT);

	return TRUE;  
}

void CLS_NvsDSMPage::OnDestroy()
{
	CLS_BasePage::OnDestroy();

	// TODO: Add your message handler code here
}

void CLS_NvsDSMPage::OnChannelChanged( int _iRegID,int _iRegUser,int _iRegPwd )
{
	m_iRegID = _iRegID;
	if (0 != _iRegUser)
	{
		memcpy_s(m_cRegUser,sizeof(m_cRegUser),(char*)_iRegUser,sizeof(m_cRegUser));
	}
	if (0 != _iRegPwd)
	{
		memcpy_s(m_cRegPwd,sizeof(m_cRegPwd),(char*)_iRegPwd,sizeof(m_cRegPwd));
	}
}

void CLS_NvsDSMPage::OnBnClickedBtnDsmNvsRefresh()
{
	//解决刷新卡顿异常
	if (m_iRegID >= 0)
	{
		NSLook_LogoffServer(m_iRegID);
	}
	m_iRegID = NSLook_LogonServer(m_cRegIP, m_iRegPort, true);

	Sleep(1000);

	Refresh();
}

void CLS_NvsDSMPage::Refresh()
{
	m_lvNVS.DeleteAllItems();
	m_cboPage.ResetContent();
	int iCount = 0;
	int iRet = NSLook_GetCount(m_iRegID,m_cRegUser,m_cRegPwd,&iCount,TYPE_NVS);
	if(0 == iRet)
	{
		iRet = NSLook_GetList(m_iRegID,m_cRegUser,m_cRegPwd, 0, NULL, &CLS_NvsDSMPage::NvsNotify, TYPE_NVS);
		if (iRet != 0)
		{
				AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_GetList(%d,%s,%s,,,TYPE_NVS)"
					,iRet,m_iRegID,m_cRegUser,m_cRegPwd);
		}
		if (iCount > 0)
		{
			m_cboPage.AddString(_T("1"));
			m_cboPage.SetCurSel(0);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_GetCount(%d,%s,%s,,TYPE_NVS)"
			,iRet,m_iRegID,m_cRegUser,m_cRegPwd);
	}
	SetDlgItemInt(IDC_EDIT_DSM_NVS_COUNT,iCount);
}

int __stdcall CLS_NvsDSMPage::NvsNotify(int _iCount,st_NvsSingle *_regNVS)
{
	__try
	{
		if (_regNVS)
		{
			LRESULT lRet = SendMessageTimeout(s_hWnd,MSG_NVS,(WPARAM)_regNVS,(LPARAM)_iCount,SMTO_NORMAL,3000,NULL);
// 			if (0 == lRet)
// 			{
// 				AddLog(LOG_TYPE_MSG,"","NvsNotify(%#x,%d,%#08x)",_regNVS,_iCount,GetLastError());
// 			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//AddLog(LOG_TYPE_MSG,"","NvsNotify exception");
	}

	return 0;
}

LRESULT CLS_NvsDSMPage::OnNvsMsg( WPARAM wParam, LPARAM lParam )
{
	__try
	{
		st_NvsSingle* pNvs = (st_NvsSingle*)wParam;
		int iCount = (int)lParam;
		for (int i = 0 ; i < iCount; ++i)
		{
			AddNvs(pNvs+i);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		AddLog(LOG_TYPE_MSG,"","AddNvs exception");
	}
	
	return 0;
}

void CLS_NvsDSMPage::AddNvs(st_NvsSingle* _pNvs)
{
	int iItem = -1;
	LVFINDINFO info;
	info.flags = LVFI_STRING;
	info.psz = _pNvs->cFactoryID;
	while ((iItem = m_lvNVS.FindItem(&info,iItem)) != -1)
	{
		CString strIP = m_lvNVS.GetItemText(iItem,3);
		if (0 == strIP.CompareNoCase(_pNvs->cNvsIP))
		{
			return;
		}
	}

	iItem = m_lvNVS.GetItemCount();
	m_lvNVS.InsertItem(iItem,_pNvs->cFactoryID);
	m_lvNVS.SetItemText(iItem,1,_pNvs->cNvsName);
	m_lvNVS.SetItemText(iItem,2,GetNvsType(_pNvs->iNvsType));
	m_lvNVS.SetItemText(iItem,3,_pNvs->cNvsIP);
	m_lvNVS.SetItemText(iItem,4,_T(""));
	m_lvNVS.SetItemText(iItem,5,_T(""));
	
}

void CLS_NvsDSMPage::OnBnClickedBtnDsmNvsQuery()
{
	if (m_iRegID >= 0)
	{
		NSLook_LogoffServer(m_iRegID);
	}
	m_iRegID = NSLook_LogonServer(m_cRegIP, m_iRegPort, true);

	REG_NVS regNVS = {0};
	m_lvNVS.DeleteAllItems();
	GetDlgItemText(IDC_EDIT_DSM_NVS_ID,regNVS.m_stNvs.cFactoryID,sizeof(regNVS.m_stNvs.cFactoryID));
	if (strlen(regNVS.m_stNvs.cFactoryID) <= 0)
	{
		AddLog(LOG_TYPE_MSG,"","NVS ID is empty");
		return;
	}

	int iRet = NSLook_Query(m_iRegID,NULL,&regNVS,TYPE_NVS);
	if(iRet == 0)
	{
		AddNvs(&regNVS.m_stNvs);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_Query(%d,NULL,%#x,TYPE_NVS)"
			,iRet,m_iRegID,&regNVS);
	}
}

void CLS_NvsDSMPage::OnNMDblclkListDsmNvs(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int iCount = m_lvNVS.GetItemCount();
	int iItem = pNMItem->iItem;
	if (iItem >= iCount || iItem < 0)
	{	//超出列表范围
		return;
	}

	if (m_iRegID >= 0)
	{
		NSLook_LogoffServer(m_iRegID);
	}
	m_iRegID = NSLook_LogonServer(m_cRegIP, m_iRegPort, true);
	
	st_LogOnInfo stLogOn = {0};
	//strcpy_s(stLogOn.cDSIP,sizeof(m_cRegIP),m_cRegIP);
	strcpy_s(stLogOn.cUserName,sizeof(m_cRegUser),m_cRegUser);
	strcpy_s(stLogOn.cUserPwd,sizeof(m_cRegPwd),m_cRegPwd);
	m_lvNVS.GetItemText(iItem,0,stLogOn.stNvs.cFactoryID,sizeof(stLogOn.stNvs.cFactoryID));
	m_lvNVS.GetItemText(iItem,1,stLogOn.stNvs.cNvsName,sizeof(stLogOn.stNvs.cNvsName));
	CString strType = m_lvNVS.GetItemText(iItem,2);
	stLogOn.stNvs.iNvsType = GetNvsType(strType);
	m_lvNVS.GetItemText(iItem,3,stLogOn.stNvs.cNvsIP,sizeof(stLogOn.stNvs.cNvsIP));

	st_ProxyInfo stProxy = {0};
	int iRet = NSLook_ConnectNVS(m_iRegID,&stLogOn,&stProxy);
	if (0 == iRet)
	{
		m_lvNVS.SetItemText(iItem,4,stProxy.cProxyIP);
		m_lvNVS.SetItemText(iItem,5,IntToString(stProxy.iProxyPort));
		AddLog(LOG_TYPE_SUCC,"","NSLook_ConnectNVS(%d,%#x,%#x)",m_iRegID,&stLogOn,&stProxy);

		DEVICE_INFO tDevInit = {0};
		strcpy_s(tDevInit.cIP,sizeof(tDevInit.cIP),stLogOn.stNvs.cNvsIP);
		strcpy_s(tDevInit.cID,sizeof(tDevInit.cID),stLogOn.stNvs.cFactoryID);
		strcpy_s(tDevInit.cProxy,sizeof(tDevInit.cProxy),stProxy.cProxyIP);
		tDevInit.iPort = stProxy.iProxyPort;
//#ifdef _DEBUG
		strcpy_s(tDevInit.cUserName,sizeof(tDevInit.cUserName),"Admin");
		strcpy_s(tDevInit.cPassword,sizeof(tDevInit.cPassword),"1111");
//#endif

		CLS_LogonView logon(&tDevInit);
		if(IDOK != logon.DoModal())
		{
			return;
		}

		int iOldLogonID = -1;
		PDEVICE_INFO pDevLogon = logon.GetDeviceInfo();
		PDEVICE_INFO pDevFind = FindDevice(pDevLogon->cIP,pDevLogon->iPort,pDevLogon->cProxy,pDevLogon->cID,&iOldLogonID);
		if (pDevFind)
		{
			if(LOGON_SUCCESS == NetClient_GetLogonStatus(iOldLogonID))
			{
				AddLog(LOG_TYPE_MSG,"","FindDevice(%s,%d,%s,%s) device already exist!"
					,pDevFind->cIP,pDevLogon->iPort,pDevFind->cProxy,pDevFind->cID);
				return;
			}
		}

		int iLogonID = NetClient_LogonEx(pDevLogon->cProxy,pDevLogon->cIP,pDevLogon->cUserName,pDevLogon->cPassword,pDevLogon->cID,pDevLogon->iPort,"UTF-8");
		if (iLogonID >= 0)
		{
			AddLog(LOG_TYPE_SUCC,pDevLogon->cIP,"(%d)NetClient_LogonEx",iLogonID);
			if (pDevFind)
			{
				return;
			}
			PDEVICE_INFO pDevNew = AddDevice(iLogonID);
			if (pDevNew)
			{
				memcpy_s(pDevNew,sizeof(DEVICE_INFO),pDevLogon,sizeof(DEVICE_INFO));
				pDevNew->hItem = NULL;
				pDevNew->uiInterTalkID = -1;
			}
			else
			{
				AddLog(LOG_TYPE_MSG,"","AddDevice(%d) Can not add device",iLogonID);
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,pDevLogon->cIP,"NetClient_LogonEx(%s,%s,,,%s,,)",pDevLogon->cProxy,pDevLogon->cIP,pDevLogon->cID);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_ConnectNVS(%d,%#x,%#x)",iRet,m_iRegID,&stLogOn,&stProxy);
	}

	*pResult = 0;
}

void CLS_NvsDSMPage::OnNMClickListDsmNvs(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	CString strID = m_lvNVS.GetItemText(pNMItem->iItem,0);
	SetDlgItemText(IDC_EDIT_DSM_NVS_ID,strID);

	*pResult = 0;
}

void CLS_NvsDSMPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_NvsDSMPage::UI_UpdateDialog()
{
	InsertColumn(m_lvNVS,0,IDS_MNG_ADMIN_FACTORY_ID,LVCFMT_LEFT,160);
	InsertColumn(m_lvNVS,1,IDS_MNG_NVS_NAME,LVCFMT_LEFT,80);	
	InsertColumn(m_lvNVS,2,IDS_MNG_NVS_TYPE,LVCFMT_LEFT,80);
	InsertColumn(m_lvNVS,3,IDS_MNG_ADMIN_IP,LVCFMT_LEFT,90);
	InsertColumn(m_lvNVS,4,IDS_MNG_NVS_PROXY_IP,LVCFMT_LEFT,90);
	InsertColumn(m_lvNVS,5,IDS_MNG_NVS_PROXY_PORT,LVCFMT_LEFT,80);

	InsertString(m_cboQueryType,0,IDS_MNG_ADMIN_FACTORY_ID);

	SetDlgItemTextEx(IDC_STATIC_DSM_NVS_COUNT,IDS_MNG_NVS_COUNT);
	SetDlgItemTextEx(IDC_STATIC_DSM_NVS_PAGE,IDS_MNG_DNS_PAGE_NO);
	SetDlgItemTextEx(IDC_BTN_DSM_NVS_REFRESH,IDS_MNG_ADMIN_REFRESH);
	SetDlgItemTextEx(IDC_BTN_DSM_NVS_QUERY,IDS_MNG_NVS_QUERY);
}

CString CLS_NvsDSMPage::GetNvsType(int _iNvsType)
{
	CString strNvsType;
	switch(_iNvsType)
	{
	case 0:
		strNvsType.Format(_T("%s"),"T");
		break;
	case 1:
		strNvsType.Format(_T("%s"),"S");
		break;
	case 2:
		strNvsType.Format(_T("%s"),"T+");
		break;
	default:
		strNvsType.Format(_T("%d"),_iNvsType);
		break;
	}
	return strNvsType;
}

int CLS_NvsDSMPage::GetNvsType(CString _strNvsType)
{
	int iNvsType = 0;
	if (_strNvsType.CompareNoCase(_T("T")))
	{
		iNvsType = 0;
	}
	else if (_strNvsType.CompareNoCase(_T("S")))
	{
		iNvsType = 1;
	}
	else if (_strNvsType.CompareNoCase(_T("T+")))
	{
		iNvsType = 2;
	}
	else
	{
		iNvsType = atoi(_strNvsType);
	}
	return iNvsType;
}

void CLS_NvsDSMPage::SetRegisterInfo(RegisterInfo* _ptInfo)
{
	if (NULL == _ptInfo)
	{
		return;
	}

	strcpy_s(m_cRegIP, sizeof(m_cRegIP), _ptInfo->cRegIP);
	m_iRegPort = _ptInfo->iRegPort;
}

void CLS_NvsDSMPage::OnBnClickedBtnGetCount()
{
	if (m_iRegID >= 0)
	{
		NSLook_LogoffServer(m_iRegID);
	}
	m_iRegID = NSLook_LogonServer(m_cRegIP, m_iRegPort, true);

	int iCount = 0;
	int iRet = NSLook_GetCount(m_iRegID, m_cRegUser, m_cRegPwd, &iCount,TYPE_NVS);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_DSM_NVS_COUNT,iCount);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get Nvs Count failed.");
	}
}
