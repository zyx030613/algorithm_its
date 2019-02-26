// PlaybackWindow.cpp : implementation file
//

#include "stdafx.h"
#include "PlaybackWindow.h"
#include "RemoteFilePage.h"
#include "RemoteByTimePage.h"
#include "RemoteATMFilePage.h"

// CLS_PlaybackWindow dialog

IMPLEMENT_DYNAMIC(CLS_PlaybackWindow, CDialog)

CLS_PlaybackWindow::CLS_PlaybackWindow(CWnd* pParent /*=NULL*/)
	: CLS_BaseWindow(CLS_PlaybackWindow::IDD, pParent)
{
	for (int i = 0; i < PLAYBACK_MAX; ++i)
	{
		m_pPage[i] = NULL;
 	}
	m_pCurrent = NULL;
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
}

CLS_PlaybackWindow::~CLS_PlaybackWindow()
{

}

void CLS_PlaybackWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_PLAYBACK, m_tabPlayback);
}


BEGIN_MESSAGE_MAP(CLS_PlaybackWindow, CLS_BaseWindow)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PLAYBACK, &CLS_PlaybackWindow::OnTcnSelchangeTabPlayback)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLS_PlaybackWindow message handlers

void CLS_PlaybackWindow::OnTcnSelchangeTabPlayback(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowBasePage(m_tabPlayback.GetCurSel());

	*pResult = 0;
}

BOOL CLS_PlaybackWindow::OnInitDialog()
{
	CLS_BaseWindow::OnInitDialog();

	UI_UpdateText();
	ShowBasePage(0);
	return TRUE;  
}

int CLS_PlaybackWindow::ShowBasePage( int _iIndex )
{
	if (_iIndex < PLAYBACK_MIN || _iIndex >= PLAYBACK_MAX)
	{
		return -1;
	}
	if (NULL == m_pPage[_iIndex])
	{
		switch(_iIndex)
		{
		case PLAYBACK_REMOTE_BY_FILE:
			{
				m_pPage[_iIndex] = new CLS_RemoteFilePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_PBK_REMOTE_FILE,this);
			}
			break;
		case PLAYBACK_REMOTE_BY_TIME:
			{
				m_pPage[_iIndex] = new CLS_RemoteByTimePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_PBK_REMOTE_BY_TIME,this);
			}
			break;
		case PLAYBACK_REMOTE_ATM:
			{
				m_pPage[_iIndex] = new CLS_RemoteATMFilePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_PBK_REMOTE_ATM_FILE,this);
			}
			break;
		}

		if (m_pPage[_iIndex])
		{
			RECT rcShow = {0};
			GetDlgItem(IDC_TAB_PLAYBACK)->GetWindowRect(&rcShow);
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

		
	m_pCurrent->OnChannelChanged(m_iLogonID,m_iChannelNo,m_iStreamNo);

	m_pCurrent->ShowWindow(SW_SHOW);
	m_pCurrent->ShowWindow(SW_SHOW);

	return 0;
}

void CLS_PlaybackWindow::OnDestroy()
{
	CLS_BaseWindow::OnDestroy();

	for (int i = 0; i < PLAYBACK_MAX; ++i)
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

void CLS_PlaybackWindow::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;

	for (int i = 0; i < PLAYBACK_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->OnChannelChanged(_iLogonID, _iChannelNo, _iStreamNo);
		}
	}
}

void CLS_PlaybackWindow::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	for (int i = 0; i < PLAYBACK_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->OnMainNotify(_ulLogonID, _iWparam, _iLParam, _iUser);
		}
	}
}

void CLS_PlaybackWindow::OnLanguageChanged( int _iLanguage)
{
	
	UI_UpdateText();
	for (int i = 0; i < PLAYBACK_MAX; i++)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->OnLanguageChanged(_iLanguage);
		}
	}
}

void CLS_PlaybackWindow::UI_UpdateText()
{
	//m_tabPlayback.DeleteAllItems();
	InsertItem(m_tabPlayback, PLAYBACK_REMOTE_BY_FILE, IDS_PLAYBACK_PLAY_BY_FILE);
	InsertItem(m_tabPlayback, PLAYBACK_REMOTE_BY_TIME, IDS_PLAYBACK_PLAY_BY_TIME);
	InsertItem(m_tabPlayback, PLAYBACK_REMOTE_ATM, "ATM");	
}

void CLS_PlaybackWindow::OnLogoffDevice( int _iLogonID )
{
	for (int i = 0; i < PLAYBACK_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->OnLogoffDevice(_iLogonID);
		}
	}
}