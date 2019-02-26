#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgUniqueAlertCustom.h"

IMPLEMENT_DYNAMIC(CLS_DlgUniqueAlertCustom, CDialog)

CLS_DlgUniqueAlertCustom::CLS_DlgUniqueAlertCustom(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgUniqueAlertCustom::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgUniqueAlertCustom::~CLS_DlgUniqueAlertCustom()
{
}

void CLS_DlgUniqueAlertCustom::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgUniqueAlertCustom, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgUniqueAlertCustom::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	return TRUE;
}

void CLS_DlgUniqueAlertCustom::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
	}
}

void CLS_DlgUniqueAlertCustom::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
}

void CLS_DlgUniqueAlertCustom::OnLanguageChanged( int _iLanguage )
{
}

