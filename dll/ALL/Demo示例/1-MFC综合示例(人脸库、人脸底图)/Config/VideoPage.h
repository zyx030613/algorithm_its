#ifndef _VIDEO_PAGE_H_
#define _VIDEO_PAGE_H_

#include "../VideoView.h"
#include "../BasePage.h"
// CLS_VideoPage dialog

class CLS_VideoPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VideoPage)

public:
	CLS_VideoPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VideoPage();
	BOOL ShowVideo(int _iLogonID,int _iChannelNo,int _iStreamNo);
	BOOL CloseVideo();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CLS_VideoView* m_pVideo;
	unsigned int m_uConnID;

};
#endif
