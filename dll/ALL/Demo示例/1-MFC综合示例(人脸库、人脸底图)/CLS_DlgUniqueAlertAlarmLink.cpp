#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgUniqueAlertAlarmLink.h"

IMPLEMENT_DYNAMIC(CLS_DlgUniqueAlertAlarmLink, CDialog)

CLS_DlgUniqueAlertAlarmLink::CLS_DlgUniqueAlertAlarmLink(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgUniqueAlertAlarmLink::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgUniqueAlertAlarmLink::~CLS_DlgUniqueAlertAlarmLink()
{
}

void CLS_DlgUniqueAlertAlarmLink::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgUniqueAlertAlarmLink, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgUniqueAlertAlarmLink::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	return TRUE;
}

void CLS_DlgUniqueAlertAlarmLink::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
	}
}

void CLS_DlgUniqueAlertAlarmLink::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
}

void CLS_DlgUniqueAlertAlarmLink::OnLanguageChanged( int _iLanguage )
{
}
