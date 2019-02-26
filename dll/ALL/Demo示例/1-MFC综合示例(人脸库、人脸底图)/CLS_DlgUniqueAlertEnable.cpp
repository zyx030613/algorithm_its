#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgUniqueAlertEnable.h"

IMPLEMENT_DYNAMIC(CLS_DlgUniqueAlertEnable, CDialog)

CLS_DlgUniqueAlertEnable::CLS_DlgUniqueAlertEnable(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgUniqueAlertEnable::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgUniqueAlertEnable::~CLS_DlgUniqueAlertEnable()
{
}

void CLS_DlgUniqueAlertEnable::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgUniqueAlertEnable, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgUniqueAlertEnable::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	return TRUE;
}

void CLS_DlgUniqueAlertEnable::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
	}
}

void CLS_DlgUniqueAlertEnable::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
}

void CLS_DlgUniqueAlertEnable::OnLanguageChanged( int _iLanguage )
{
}

