// DSMPage.cpp : implementation file
//

#include "stdafx.h"
#include "DSMPage.h"
#include "NvsDSMPage.h"
#include "DnsDSMPage.h"
#include "../Include/NSLOOK_INTERFACE.h"

// CLS_DSMPage dialog

IMPLEMENT_DYNAMIC(CLS_DSMPage, CDialog)

CLS_DSMPage::CLS_DSMPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DSMPage::IDD, pParent)
{
	for (int i = 0; i < DSM_MAX; ++i)
	{
		m_pPage[i] = NULL;
	}
	m_pCurrent = NULL;
	m_iRegID = -1;

	memset(m_cRegUser, 0, sizeof(m_cRegUser));
	memset(m_cRegPwd, 0, sizeof(m_cRegPwd));
}

CLS_DSMPage::~CLS_DSMPage()
{
}

void CLS_DSMPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_DSM, m_tabDSM);
}


BEGIN_MESSAGE_MAP(CLS_DSMPage, CLS_BasePage)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DSM, &CLS_DSMPage::OnTcnSelchangeTabDsm)
	ON_BN_CLICKED(IDC_BTN_SERVER_LOGON, &CLS_DSMPage::OnBnClickedBtnServerLogon)
	ON_BN_CLICKED(IDC_BTN_SERVER_VERSION, &CLS_DSMPage::OnBnClickedBtnServerVersion)
END_MESSAGE_MAP()


// CLS_DSMPage message handlers

BOOL CLS_DSMPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SERVER_IP);
	pEdit->SetLimitText(15);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SERVER_PORT);
	pEdit->SetLimitText(10);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	pEdit->SetLimitText(31);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
	pEdit->SetLimitText(31);

	m_tabDSM.InsertItem(DSM_NVS,_T("NVS"));
	m_tabDSM.InsertItem(DSM_DNS,_T("DNS"));

	SetDlgItemText(IDC_EDIT_SERVER_IP,_T("127.0.0.1"));
	SetDlgItemText(IDC_EDIT_SERVER_PORT,_T("6004"));
	SetDlgItemText(IDC_EDIT_USERNAME,_T("QQ"));
	SetDlgItemText(IDC_EDIT_PASSWORD,_T("QQQQ"));

	UI_UpdateDialog();

	ShowBasePage(0);

	if (DLL_LOAD_SUCCESS == CLS_NsLook_Interface::LoadDLL())
	{
		NSLook_Startup();
	}
	else
	{
		MessageBox(_T("error in load nslook.dll"),_T(""),MB_TOPMOST|MB_OK);
		this->EnableWindow(FALSE);
	}
	EnableDSMWindow(FALSE);

	return TRUE;  
}

void CLS_DSMPage::OnDestroy()
{
	CLS_BasePage::OnDestroy();

	for (int i = 0; i < DSM_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->DestroyWindow();
			delete m_pPage[i];
			m_pPage[i] = NULL;
		}
	}
	m_pCurrent = NULL;

	NSLook_Cleanup();
	CLS_NsLook_Interface::FreeDLL();
}

int CLS_DSMPage::ShowBasePage( int _iIndex )
{
	if (_iIndex < DSM_MIN || _iIndex >= DSM_MAX)
	{
		return -1;
	}
	if (NULL == m_pPage[_iIndex])
	{
		switch(_iIndex)
		{
		case DSM_NVS:
			{
				m_pPage[_iIndex] = new CLS_NvsDSMPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_MNG_DSM_NVS,this);
			}
			break;
		case DSM_DNS:
			{
				m_pPage[_iIndex] = new CLS_DnsDSMPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_MNG_DSM_DNS,this);
			}
			break;
		}

		if (m_pPage[_iIndex])
		{
			RECT rcShow = {0};
			GetDlgItem(IDC_TAB_DSM)->GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			rcShow.left += 1;
			rcShow.top += 22;
			rcShow.right -= 1;
			rcShow.bottom -= 1;
			m_pPage[_iIndex]->MoveWindow(&rcShow);
		}
		else
		{
			return -1;
		}
	}

	if(m_pCurrent)
	{
		m_pCurrent->ShowWindow(SW_HIDE);
	}
	m_pCurrent = m_pPage[_iIndex];
	m_pCurrent->OnChannelChanged(m_iRegID,(int)m_cRegUser,(int)m_cRegPwd);
	m_pCurrent->ShowWindow(SW_SHOW);

	return 0;
}

void CLS_DSMPage::OnTcnSelchangeTabDsm(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowBasePage(m_tabDSM.GetCurSel());

	*pResult = 0;
}

void CLS_DSMPage::OnBnClickedBtnServerLogon()
{
	char cRegIP[16] = {0};
	GetDlgItemText(IDC_EDIT_SERVER_IP,cRegIP,sizeof(cRegIP));
	GetDlgItemText(IDC_EDIT_USERNAME,m_cRegUser,sizeof(m_cRegUser));
	GetDlgItemText(IDC_EDIT_PASSWORD,m_cRegPwd,sizeof(m_cRegPwd));
	int iRegPort = GetDlgItemInt(IDC_EDIT_SERVER_PORT);

	if (m_iRegID >= 0)
	{
		NSLook_LogoffServer(m_iRegID);
	}

	m_iRegID = NSLook_LogonServer(cRegIP, iRegPort, true);
	if (m_iRegID >= 0)
	{
		EnableDSMWindow(TRUE);
		AddLog(LOG_TYPE_SUCC,"","(%d)NSLook_LogonServer(%s,%d,true)",m_iRegID,cRegIP,iRegPort);
	}
	else
	{
		EnableDSMWindow(FALSE);
		AddLog(LOG_TYPE_FAIL,"","(%d)NSLook_LogonServer(%s,%d,true)",m_iRegID,cRegIP,iRegPort);
	}

	if(m_pCurrent)
	{
		m_pCurrent->OnChannelChanged(m_iRegID,(int)m_cRegUser,(int)m_cRegPwd);
		RegisterInfo tInfo = {0};
		strcpy_s(tInfo.cRegUser, sizeof(tInfo.cRegUser), m_cRegUser);
		strcpy_s(tInfo.cRegPwd, sizeof(tInfo.cRegPwd), m_cRegPwd);
		strcpy_s(tInfo.cRegIP, sizeof(tInfo.cRegIP), cRegIP);
		tInfo.iRegPort = iRegPort;
		m_pCurrent->SetRegisterInfo(&tInfo);
	}
}

void CLS_DSMPage::OnBnClickedBtnServerVersion()
{
	LPCSTR cVersion = NSLook_GetServerVersion(m_iRegID);
	if(cVersion)
	{
		SetDlgItemText(IDC_EDIT_SERVER_VERSION,cVersion);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NSLook_GetServerVersion(%d)",m_iRegID);
		SetDlgItemText(IDC_EDIT_SERVER_VERSION,"");
	}
}

void CLS_DSMPage::EnableDSMWindow(BOOL _bEnable)
{
	GetDlgItem(IDC_BTN_SERVER_VERSION)->EnableWindow(_bEnable);
	GetDlgItem(IDC_TAB_DSM)->EnableWindow(_bEnable);
	for (int i = 0; i < DSM_MAX; ++i)
	{
		if(m_pPage[i])
		{
			m_pPage[i]->EnableWindow(_bEnable);
		}
	}
}

void CLS_DSMPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();

	for (int i = 0; i < DSM_MAX; ++i)
	{
		if(m_pPage[i])
		{
			m_pPage[i]->OnLanguageChanged(_iLanguage);
		}
	}
}

void CLS_DSMPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_SERVER_IP,IDS_LOGON_IP);
	SetDlgItemTextEx(IDC_STATIC_DSM_SERVER_PORT,IDS_LOGON_PORT);
	SetDlgItemTextEx(IDC_STATIC_USERNAME,IDS_MNG_ACCOUNT);
	SetDlgItemTextEx(IDC_STATIC_PASSWORD,IDS_LOGON_PASSWORD);
	SetDlgItemTextEx(IDC_BTN_SERVER_LOGON,IDS_MENU_LOGON);
	SetDlgItemTextEx(IDC_BTN_SERVER_VERSION,IDS_MNG_REGSERVER_VERSION);
}