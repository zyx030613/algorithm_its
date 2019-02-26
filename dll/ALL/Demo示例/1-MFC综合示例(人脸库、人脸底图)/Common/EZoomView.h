#ifndef _EZOOM_VIEW_H
#define _EZOOM_VIEW_H

#include "Resource.h"

#define INVALID_CONNECT_ID		(0xFFFFFFFF)			//	默认的空连接ID
// CLS_EZoomView dialog

class CLS_EZoomView : public CDialog
{
	DECLARE_DYNAMIC(CLS_EZoomView)

public:
	CLS_EZoomView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_EZoomView();
	BOOL CLS_EZoomView::AddEZoom( unsigned int _uiConnID, RECT* _prcVideo);
	BOOL DeleteEZoom(unsigned int _uiConnID,BOOL _bForceClose = FALSE);

// Dialog Data
	enum { IDD = IDD_DLG_EZOOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	unsigned int m_uiConnID;
	int m_iEZoomID;
	
};

#endif
