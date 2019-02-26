// Preview\EZoomView.cpp : implementation file
//

#include "stdafx.h"
#include "EZoomView.h"
#include "Common/CommonFun.h"
#include "Include/NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;

// CLS_EZoomView dialog

IMPLEMENT_DYNAMIC(CLS_EZoomView, CDialog)

CLS_EZoomView::CLS_EZoomView(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_EZoomView::IDD, pParent)
{
	m_uiConnID = -1;
	m_iEZoomID = -1;
}

CLS_EZoomView::~CLS_EZoomView()
{

}

void CLS_EZoomView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLS_EZoomView, CDialog)
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CLS_EZoomView::AddEZoom( unsigned int _uiConnID, RECT* _prcVideo )
{
	if (INVALID_CONNECT_ID != m_uiConnID || NULL == _prcVideo)
	{
		return FALSE;
	}

	RECT rcShow = {0};
	m_iEZoomID = NetClient_EZoomAdd(_uiConnID,GetDlgItem(IDC_STATIC_EZOOM)->GetSafeHwnd(), rcShow,1);
	if (m_iEZoomID < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NetClient_EZoomAdd(%u,,,1)",m_iEZoomID,_uiConnID);
		return FALSE;
	}

	AddLog(LOG_TYPE_SUCC,"","(%d)NetClient_EZoomAdd(%u,,,1)",m_iEZoomID,_uiConnID);
	int iRet = NetClient_EZoomSet(_uiConnID,m_iEZoomID,*_prcVideo);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_EZoomSet(%u,%d,[%d,%d,%d,%d])"
			,_uiConnID,m_iEZoomID,_prcVideo->left,_prcVideo->top,_prcVideo->right,_prcVideo->bottom);
		return FALSE;
	}
	
	AddLog(LOG_TYPE_FAIL,"","NetClient_EZoomSet(%u,%d,[%d,%d,%d,%d])"
		,_uiConnID,m_iEZoomID,_prcVideo->left,_prcVideo->top,_prcVideo->right,_prcVideo->bottom);

	m_uiConnID = _uiConnID;
	MoveWindow(_prcVideo);
	ShowWindow(SW_SHOW);
	
	return TRUE;
}

BOOL CLS_EZoomView::DeleteEZoom( unsigned int _uiConnID,BOOL _bForceClose)
{
	if ( _bForceClose || m_uiConnID == _uiConnID )
	{
		int iRet = NetClient_EZoomRemove(m_uiConnID,m_iEZoomID);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_EZoomRemove(%u,%d)",_uiConnID,m_iEZoomID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_EZoomRemove(%u,%d)",_uiConnID,m_iEZoomID);
		}
		m_uiConnID = INVALID_CONNECT_ID;
		m_iEZoomID = -1;
		return TRUE;
	}
	
	return FALSE;
}

void CLS_EZoomView::OnClose()
{
	DeleteEZoom(m_uiConnID);
	CDialog::OnClose();
}

void CLS_EZoomView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	RECT rcShow = {0};
	GetClientRect(&rcShow);
	GetDlgItem(IDC_STATIC_EZOOM)->MoveWindow(&rcShow);
}
