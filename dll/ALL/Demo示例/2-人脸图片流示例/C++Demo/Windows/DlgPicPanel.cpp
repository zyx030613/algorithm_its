// DlgPicPanel.cpp : implementation file
//

#include "stdafx.h"
#include "FacePicStreamDemoDlg.h"
#include "DlgPicPanel.h"


// CDlgPicPanel dialog

IMPLEMENT_DYNAMIC(CDlgPicPanel, CDialog)

CDlgPicPanel::CDlgPicPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPicPanel::IDD, pParent)
{
	m_brushMainBack	= ::CreateSolidBrush(RGB(0,0,0));
	m_iIndex = -1;
	m_iISDrawBlack = -1;
}

CDlgPicPanel::~CDlgPicPanel()
{
}

void CDlgPicPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPicPanel, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgPicPanel message handlers

HBRUSH CDlgPicPanel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
 	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
 
 	// TODO:  Change any attributes of the DC here
 	switch(nCtlColor)
 	{
 	case CTLCOLOR_STATIC:
 	case CTLCOLOR_EDIT:
 	case CTLCOLOR_BTN:
 	case CTLCOLOR_LISTBOX:
 	case CTLCOLOR_MSGBOX:
 	case CTLCOLOR_SCROLLBAR:
 		break;
 	case CTLCOLOR_DLG:
 		//hbr =m_brushMainBack;
 		if(pWnd->m_hWnd == m_hWnd)
 		{ 
 			pDC->SetBkColor(RGB(0,0,0)); 
 			return (HBRUSH)m_brushMainBack; 
 		}
		break;
 	default:;
 	}
 	// TODO:  Return a different brush if the default is not desired
 	return hbr;

}

BOOL CDlgPicPanel::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return true;
		case VK_ESCAPE:
			{
				CFacePicStreamDemoDlg * pITSFaceSnapDemoDlg = (CFacePicStreamDemoDlg*)GetParent();
			}
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CDlgPicPanel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FASE
}

void CDlgPicPanel::SetPanelID( int nID )
{
	m_iIndex = nID;
}

int CDlgPicPanel::GetPanelID()
{
	return m_iIndex;
}

void CDlgPicPanel::OnPaint()
{
	CPaintDC dc(this);
	if (IS_DROW == m_iISDrawBlack)
	{
		CRect  rect;
		GetClientRect(rect);
		dc.FillSolidRect(rect,RGB(0,0,0));
	}
}
