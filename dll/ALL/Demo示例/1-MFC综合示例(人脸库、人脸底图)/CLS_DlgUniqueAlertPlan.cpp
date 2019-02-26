#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgUniqueAlertPlan.h"

IMPLEMENT_DYNAMIC(CLS_DlgUniqueAlertPlan, CDialog)

CLS_DlgUniqueAlertPlan::CLS_DlgUniqueAlertPlan(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgUniqueAlertPlan::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgUniqueAlertPlan::~CLS_DlgUniqueAlertPlan()
{
}

void CLS_DlgUniqueAlertPlan::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgUniqueAlertPlan, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgUniqueAlertPlan::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	return TRUE;
}

void CLS_DlgUniqueAlertPlan::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
	}
}

void CLS_DlgUniqueAlertPlan::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
}

void CLS_DlgUniqueAlertPlan::OnLanguageChanged( int _iLanguage )
{
}

