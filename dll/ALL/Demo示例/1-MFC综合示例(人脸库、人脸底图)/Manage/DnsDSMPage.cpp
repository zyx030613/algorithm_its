// DnsDSMPage.cpp : implementation file
//

#include "stdafx.h"
#include "DnsDSMPage.h"
#include "../LogonView.h"

#define MSG_DNS		(WM_USER + 1103)

HWND CLS_DnsDSMPage::s_hWnd = NULL;

// CLS_DnsDSMPage dialog

IMPLEMENT_DYNAMIC(CLS_DnsDSMPage, CDialog)

CLS_DnsDSMPage::CLS_DnsDSMPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DnsDSMPage::IDD, pParent)
{
	m_iRegID = -1;
	memset(m_cRegUser,0,sizeof(m_cRegUser));
	memset(m_cRegPwd,0,sizeof(m_cRegPwd));
}

CLS_DnsDSMPage::~CLS_DnsDSMPage()
{

}

void CLS_DnsDSMPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DSM_DNS, m_lvDNS);
	DDX_Control(pDX, IDC_CBO_DSM_DNS_QUERY_TYPE, m_cboQueryType);
	DDX_Control(pDX, IDC_CBO_DSM_DNS_PAGE, m_cboPage);
}


BEGIN_MESSAGE_MAP(CLS_DnsDSMPage, CLS_BasePage)
	ON_WM_DESTROY()
	ON_MESSAGE(MSG_DNS,&CLS_DnsDSMPage::OnDnsMsg)
	ON_BN_CLICKED(IDC_BTN_DSM_DNS_REFRESH, &CLS_DnsDSMPage::OnBnClickedBtnDsmDnsRefresh)
	ON_CBN_SELCHANGE(IDC_CBO_DSM_DNS_PAGE, &CLS_DnsDSMPage::OnCbnSelchangeCboDsmDnsPage)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DSM_DNS, &CLS_DnsDSMPage::OnNMClickListDsmDns)
	ON_CBN_SELCHANGE(IDC_CBO_DSM_DNS_QUERY_TYPE, &CLS_DnsDSMPage::OnCbnSelchangeCboDsmDnsQueryType)
	ON_BN_CLICKED(IDC_BTN_DSM_DNS_QUERY, &CLS_DnsDSMPage::OnBnClickedBtnDsmDnsQuery)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DSM_DNS, &CLS_DnsDSMPage::OnNMDblclkListDsmDns)
END_MESSAGE_MAP()


// CLS_DnsDSMPage message handlers

BOOL CLS_DnsDSMPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	s_hWnd = this->GetSafeHwnd();
	((CEdit*)GetDlgItem(IDC_EDIT_DSM_DNS_ID))->SetLimitText(31);
	m_lvDNS.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	UI_UpdateDialog();

	m_cboQueryType.SetCurSel(0);

	m_lvDNS.SetSortType(3,SORT_TYPE_IP);
	m_lvDNS.SetSortType(4,SORT_TYPE_IP);
	m_lvDNS.SetSortType(5,SORT_TYPE_INT);
	m_lvDNS.SetSortType(6,SORT_TYPE_INT);
	
	return TRUE; 
}

void CLS_DnsDSMPage::OnDestroy()
{
	CLS_BasePage::OnDestroy();

	// TODO: Add your message handler code here
}

void CLS_DnsDSMPage::OnChannelChanged( int _iRegID,int _iRegUser,int _iRegPwd )
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

void CLS_DnsDSMPage::UI_UpdateDialog()
{
	InsertColumn(m_lvDNS,0,IDS_MNG_ADMIN_FACTORY_ID,LVCFMT_LEFT,160);
	InsertColumn(m_lvDNS,1,IDS_MNG_NVS_NAME,LVCFMT_LEFT,80);	
	InsertColumn(m_lvDNS,2,IDS_MNG_NVS_TYPE,LVCFMT_LEFT,80);
	InsertColumn(m_lvDNS,3,IDS_MNG_DNS_LAN_IP,LVCFMT_LEFT,90);
	InsertColumn(m_lvDNS,4,IDS_MNG_DNS_WAN_IP,LVCFMT_LEFT,90);
	InsertColumn(m_lvDNS,5,IDS_LOGON_PORT,LVCFMT_LEFT,80);
	InsertColumn(m_lvDNS,6,IDS_MNG_ADMIN_CHANNEL_NUM,LVCFMT_LEFT,80);
	InsertColumn(m_lvDNS,7,IDS_MNG_DNS_REGISTER_TIME,LVCFMT_LEFT,120);
	
	InsertString(m_cboQueryType,0,IDS_MNG_ADMIN_FACTORY_ID);
	InsertString(m_cboQueryType,1,IDS_MNG_NVS_NAME);

	SetDlgItemTextEx(IDC_STATIC_DSM_DNS_COUNT,IDS_MNG_NVS_COUNT);
	SetDlgItemTextEx(IDC_STATIC_DSM_DNS_PAGE,IDS_MNG_DNS_PAGE_NO);
	SetDlgItemTextEx(IDC_BTN_DSM_DNS_REFRESH,IDS_MNG_ADMIN_REFRESH);
	SetDlgItemTextEx(IDC_BTN_DSM_DNS_QUERY,IDS_MNG_NVS_QUERY);

}

void CLS_DnsDSMPage::OnBnClickedBtnDsmDnsRefresh()
{
	m_cboPage.ResetContent();
	int iCount = 0;
	int iRet = NSLook_GetCount(m_iRegID,m_cRegUser,m_cRegPwd,&iCount,TYPE_DNS);
	if(0 == iRet)
	{
		int iPages = (iCount+REG_PAGE_SIZE-1) / REG_PAGE_SIZE;
		for (int i = 1; i <= iPages; ++i)
		{
			m_cboPage.AddString(IntToString(i));
		}
		m_cboPage.SetCurSel(0);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_GetCount(%d,%s,%s,,TYPE_DNS)"
			,iRet,m_iRegID,m_cRegUser,m_cRegPwd);
	}
	SetDlgItemInt(IDC_EDIT_DSM_DNS_COUNT,iCount);
	Refresh();
}

void CLS_DnsDSMPage::Refresh()
{
	m_lvDNS.DeleteAllItems();
	int iPage = m_cboPage.GetCurSel();
	if (iPage < 0)
	{
		return;
	}

	int iRet = NSLook_GetList(m_iRegID,m_cRegUser,m_cRegPwd,iPage,&CLS_DnsDSMPage::DnsNotify,NULL,TYPE_DNS);
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_GetList(%d,%s,%s,%d,,,TYPE_DNS)"
			,iRet,m_iRegID,m_cRegUser,m_cRegPwd,iPage);
	}
}

int __stdcall CLS_DnsDSMPage::DnsNotify( int _iCount,REG_DNS *_pDNS )
{
	__try
	{
		if (_pDNS)
		{
			LRESULT lRet = SendMessageTimeout(s_hWnd,MSG_DNS,(WPARAM)_pDNS,(LPARAM)_iCount,SMTO_NORMAL,1000,NULL);
// 			if (0 == lRet)
// 			{
// 				AddLog(LOG_TYPE_MSG,"","DnsNotify(%#x,%d,%#x)",_pDNS,_iCount,GetLastError());
// 			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//AddLog(LOG_TYPE_MSG,"","DnsNotify exception");
	}

	return 0;
}

void CLS_DnsDSMPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

LRESULT CLS_DnsDSMPage::OnDnsMsg( WPARAM wParam, LPARAM lParam )
{
	__try
	{
		REG_DNS* pDns = (REG_DNS*)wParam;
		int iCount = (int)lParam;
		for (int i = 0 ; i < iCount; ++i)
		{
			AddDns(pDns+i);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		AddLog(LOG_TYPE_MSG,"","AddDns exception");
	}

	return 0;
}

void CLS_DnsDSMPage::AddDns(REG_DNS* _pDns)
{
	int iItem = -1;
	LVFINDINFO info;
	info.flags = LVFI_STRING;
	info.psz = _pDns->m_stDNSInfo.stNvs.cFactoryID;
	while ((iItem = m_lvDNS.FindItem(&info,iItem)) != -1)
	{
		CString strIP = m_lvDNS.GetItemText(iItem,3);
		if (0 == strIP.CompareNoCase(_pDns->m_stDNSInfo.stNvs.cNvsIP))
		{
			return;
		}
	}

	iItem = m_lvDNS.GetItemCount();
	m_lvDNS.InsertItem(iItem,_pDns->m_stDNSInfo.stNvs.cFactoryID);
	m_lvDNS.SetItemText(iItem,1,_pDns->m_stDNSInfo.stNvs.cNvsName);	
	m_lvDNS.SetItemText(iItem,2,GetNvsType(_pDns->m_stDNSInfo.stNvs.iNvsType));
	m_lvDNS.SetItemText(iItem,3,_pDns->m_stDNSInfo.stNvs.cNvsIP);
	m_lvDNS.SetItemText(iItem,4,_pDns->m_stDNSInfo.m_stReserve.m_cReserved1);
	m_lvDNS.SetItemText(iItem,5,IntToString(_pDns->m_stDNSInfo.m_iPort));
	m_lvDNS.SetItemText(iItem,6,IntToString(_pDns->m_stDNSInfo.m_iChannel));
	m_lvDNS.SetItemText(iItem,7,_pDns->szRegTime);
}

void CLS_DnsDSMPage::OnCbnSelchangeCboDsmDnsPage()
{
	Refresh();
}

void CLS_DnsDSMPage::OnNMClickListDsmDns(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (pNMItem->iItem < 0)
	{
		return;
	}
	int iSubItem = m_cboQueryType.GetCurSel();
	CString strQueryData = m_lvDNS.GetItemText(pNMItem->iItem,iSubItem);
	SetDlgItemText(IDC_EDIT_DSM_DNS_ID,strQueryData);

	*pResult = 0;
}

void CLS_DnsDSMPage::OnCbnSelchangeCboDsmDnsQueryType()
{
	int iItem = m_lvDNS.GetNextItem(-1,LVNI_SELECTED);
	int iSubItem = m_cboQueryType.GetCurSel();
	CString strQueryData = m_lvDNS.GetItemText(iItem,iSubItem);
	SetDlgItemText(IDC_EDIT_DSM_DNS_ID,strQueryData);
}

void CLS_DnsDSMPage::OnBnClickedBtnDsmDnsQuery()
{
	CString strQueryData;
	GetDlgItemText(IDC_EDIT_DSM_DNS_ID,strQueryData);
	if (strQueryData.GetLength() <= 0)
	{
		CString strQueryType;
		m_cboQueryType.GetWindowText(strQueryType);
		AddLog(LOG_TYPE_MSG,"","%s is empty",strQueryType);
		return;
	}
	
	REG_DNS regDNS = {0};
	switch(m_cboQueryType.GetCurSel())
	{
	case 0:
		strcpy_s(regDNS.m_stDNSInfo.stNvs.cFactoryID,sizeof(regDNS.m_stDNSInfo.stNvs.cFactoryID),(LPSTR)(LPCTSTR)strQueryData);
		break;
	case 1:
		strcpy_s(regDNS.m_stDNSInfo.stNvs.cNvsName,sizeof(regDNS.m_stDNSInfo.stNvs.cNvsName),(LPSTR)(LPCTSTR)strQueryData);
		break;
	default:
		AddLog(LOG_TYPE_MSG,"","other query type(%d)",strQueryData.GetLength());
		return;
	}

	strcpy_s(regDNS.m_stDNSInfo.m_cUserName,sizeof(m_cRegUser),m_cRegUser);
	strcpy_s(regDNS.m_stDNSInfo.m_cPwd,sizeof(m_cRegPwd),m_cRegPwd);

	m_lvDNS.DeleteAllItems();
	int iRet = NSLook_Query(m_iRegID,&regDNS,NULL,TYPE_DNS);
	if(iRet == 0)
	{
		AddDns(&regDNS);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_Query(%d,%#x,NULL,TYPE_DNS)"
			,iRet,m_iRegID,&regDNS);
	}
}

void CLS_DnsDSMPage::OnNMDblclkListDsmDns(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	DEVICE_INFO tDevInit = {0};
	m_lvDNS.GetItemText(pNMItem->iItem,0,tDevInit.cID,sizeof(tDevInit.cID));
	m_lvDNS.GetItemText(pNMItem->iItem,3,tDevInit.cIP,sizeof(tDevInit.cIP));
	m_lvDNS.GetItemText(pNMItem->iItem,4,tDevInit.cProxy,sizeof(tDevInit.cProxy));
	CString strPort = m_lvDNS.GetItemText(pNMItem->iItem,5);
	tDevInit.iPort = atoi((LPSTR)(LPCTSTR)strPort);
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
				,pDevFind->cIP,pDevFind->iPort,pDevFind->cProxy,pDevFind->cID);
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

	*pResult = 0;
}

CString CLS_DnsDSMPage::GetNvsType(int _iNvsType)
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
