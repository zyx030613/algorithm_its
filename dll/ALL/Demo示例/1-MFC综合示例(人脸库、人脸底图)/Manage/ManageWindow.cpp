// ManageWindow.cpp : implementation file
//

#include "stdafx.h"
#include "ManageWindow.h"
#include "NetAdminPage.h"
#include "DSMPage.h"
#include "ActivePage.h"


// CLS_ManageWindow dialog

IMPLEMENT_DYNAMIC(CLS_ManageWindow, CDialog)

CLS_ManageWindow::CLS_ManageWindow(CWnd* pParent /*=NULL*/)
	: CLS_BaseWindow(CLS_ManageWindow::IDD, pParent)
{
	for (int i = 0; i < MANAGE_MAX; ++i)
	{
		m_pPage[i] = NULL;
	}
	m_pCurrent = NULL;

	CString strFile;
	strFile.Format("%s%s", ExtractFilePath(), "ActiveConfig.ini");
	m_iniFile.SetFileName(strFile.GetString());
	m_iActiveShowType = 0;
}

CLS_ManageWindow::~CLS_ManageWindow()
{
}

void CLS_ManageWindow::DoDataExchange(CDataExchange* pDX)
{
	CLS_BaseWindow::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MANAGE, m_tabManage);
}


BEGIN_MESSAGE_MAP(CLS_ManageWindow, CLS_BaseWindow)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MANAGE, &CLS_ManageWindow::OnTcnSelchangeTabManage)
END_MESSAGE_MAP()

// CLS_ManageWindow message handlers

BOOL CLS_ManageWindow::OnInitDialog()
{
	CLS_BaseWindow::OnInitDialog();

	m_tabManage.InsertItem(MANAGE_ADMIN, _T("NetAdmin"));
	m_iActiveShowType = m_iniFile.ReadInteger("ActiveType", "ShowType", 0);
	if (MANAGE_ACTIVE == m_iActiveShowType)
	{
		m_tabManage.InsertItem(MANAGE_ACTIVE,_T("Active"));
	}
	else if (MANAGE_DSM == m_iActiveShowType)
	{
		m_tabManage.InsertItem(MANAGE_DSM,_T("DSM"));
	}
	else
	{
		m_tabManage.InsertItem(MANAGE_ACTIVE,_T("Active"));
		m_tabManage.InsertItem(MANAGE_DSM,_T("DSM"));
	}

	ShowBasePage(0);

	return TRUE;  
}

void CLS_ManageWindow::OnDestroy()
{
	CLS_BaseWindow::OnDestroy();

	for (int i = 0; i < MANAGE_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->DestroyWindow();
			delete m_pPage[i];
			m_pPage[i] = NULL;
		}
	}
	m_pCurrent = NULL;
}

int CLS_ManageWindow::ShowBasePage( int _iIndex )
{
	if (_iIndex < MANAGE_MIN || _iIndex >= MANAGE_MAX)
	{
		return -1;
	}
	if (NULL == m_pPage[_iIndex])
	{
		switch(_iIndex)
		{
		case MANAGE_ADMIN:
			{
				m_pPage[_iIndex] = new CLS_NetAdminPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_MNG_ADMIN,this);
			}
			break;
		case MANAGE_ACTIVE:
			{
				m_pPage[_iIndex] = new CLS_ActivePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_MNG_ACTIVE,this);
			}
			break;
		case MANAGE_DSM:
			{
				m_pPage[_iIndex] = new CLS_DSMPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_MNG_DSM,this);
			}
			break;
		}

		if (m_pPage[_iIndex])
		{
			RECT rcShow = {0};
			GetDlgItem(IDC_TAB_MANAGE)->GetWindowRect(&rcShow);
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
	m_pCurrent->ShowWindow(SW_SHOW);

	return 0;
}

void CLS_ManageWindow::OnTcnSelchangeTabManage(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iSelIndex = m_tabManage.GetCurSel();
	if (iSelIndex > 0 && MANAGE_DSM == m_iActiveShowType)
	{
		iSelIndex = MANAGE_DSM;
	}

	ShowBasePage(iSelIndex);

	*pResult = 0;
}

void CLS_ManageWindow::OnLanguageChanged( int _iLanguage )
{
	for (int i = 0; i < MANAGE_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->OnLanguageChanged(_iLanguage);
		}
	}
}