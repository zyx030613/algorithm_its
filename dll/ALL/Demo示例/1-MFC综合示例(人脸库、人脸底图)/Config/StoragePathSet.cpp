// CLS_StoragePathSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "StoragePathSet.h"

#define PTAH_TYPE_SDUSB 1
#define PTAH_TYPE_NFS   2
#define PTAH_TYPE_FTP   3

// CLS_StoragePathSetPage dialog

IMPLEMENT_DYNAMIC(CLS_StoragePathSetPage, CDialog)

CLS_StoragePathSetPage::CLS_StoragePathSetPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_StoragePathSetPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_StoragePathSetPage::~CLS_StoragePathSetPage()
{
}

void CLS_StoragePathSetPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_STORAGE_PATH, m_cboPathType);
}

BEGIN_MESSAGE_MAP(CLS_StoragePathSetPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_STORAGE_SET, &CLS_StoragePathSetPage::OnBnClickedButtonSetPath)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CLS_VideoEncodeSlicePage message handlers

BOOL CLS_StoragePathSetPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();
	m_cboPathType.SetCurSel(0);

	return TRUE; 
}

void CLS_StoragePathSetPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	UI_UpdateStoragePathType();

}

void CLS_StoragePathSetPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if (_iStreamNo < 0)
	{
		m_iStreamNo = 0;
	}
	else
	{
		m_iStreamNo = _iStreamNo;
	}
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	
	UI_UpdateStoragePathType();
}

void CLS_StoragePathSetPage::OnBnClickedButtonSetPath()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	if (m_iStreamNo > BASIC_STREAM_TYPES)
	{
		AddLog(LOG_TYPE_MSG,"","Illegal stream number %d", m_iStreamNo);
		return;
	}
	LocalStorePath tLocalStorePath = {0};
	tLocalStorePath.iSize = sizeof(tLocalStorePath);
	tLocalStorePath.iEnable = m_cboPathType.GetItemData(m_cboPathType.GetCurSel());
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_LOCAL_STORE_PATH, m_iChannelNo, &tLocalStorePath, sizeof(tLocalStorePath));
	if (RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_LOCAL_STORE_PATH](%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,tLocalStorePath.iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_LOCAL_STORE_PATH](%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo);
	}
}

BOOL CLS_StoragePathSetPage::UI_UpdateStoragePathType()
{
	if (m_iLogonID < 0)
		return FALSE;
	if (m_iStreamNo > BASIC_STREAM_TYPES)
	{
		AddLog(LOG_TYPE_MSG,"","Illegal stream number %d", m_iStreamNo);
		return FALSE;
	}
	LocalStorePath tLocalStorePath = {0};
	tLocalStorePath.iSize = sizeof(tLocalStorePath);
	int iByteReturn = -1;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_LOCAL_STORE_PATH, m_iChannelNo, &tLocalStorePath, sizeof(tLocalStorePath), &iByteReturn);
	if (RET_FAILED == iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_LOCAL_STORE_PATH](%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo);
	}
	else
	{
		m_cboPathType.SetCurSel(GetCboSel(&m_cboPathType, tLocalStorePath.iEnable));
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_LOCAL_STORE_PATH](%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,tLocalStorePath.iEnable);
	}
	return TRUE;
}

void CLS_StoragePathSetPage::UI_UpdateDialog()
{
	m_cboPathType.ResetContent();
	m_cboPathType.SetItemData(m_cboPathType.AddString("SD/USB"), PTAH_TYPE_SDUSB);
	m_cboPathType.SetItemData(m_cboPathType.AddString("NFS"), PTAH_TYPE_NFS);
	m_cboPathType.SetItemData(m_cboPathType.AddString("FTP"), PTAH_TYPE_FTP);
	m_cboPathType.SetCurSel(0);

	SetDlgItemTextEx(IDC_STXT_STORAGE_PATH, IDS_STORAGE_PATH);
	SetDlgItemTextEx(IDC_STXT_PATH_CHOOSE, IDS_PATH_CHOOSE);
	SetDlgItemTextEx(IDC_BTN_STORAGE_SET, IDS_SET);
}

void CLS_StoragePathSetPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
	UI_UpdateStoragePathType();
}

