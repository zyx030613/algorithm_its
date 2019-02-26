#ifndef _PLAYBACK_WINDOW_H
#define _PLAYBACK_WINDOW_H

#include "afxcmn.h"
#include "../BasePage.h"

// CLS_PlaybackWindow dialog

enum PLAYBACK_PAGE_INDEX
{
	PLAYBACK_MIN = 0,
	PLAYBACK_REMOTE_BY_FILE = PLAYBACK_MIN,
	PLAYBACK_REMOTE_BY_TIME,
	PLAYBACK_REMOTE_ATM,
	PLAYBACK_MAX
};

class CLS_PlaybackWindow : public CLS_BaseWindow
{
	DECLARE_DYNAMIC(CLS_PlaybackWindow)

public:
	CLS_PlaybackWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PlaybackWindow();

// Dialog Data
	enum { IDD = IDD_DLG_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLogoffDevice(int _iLogonID);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnLanguageChanged(int );
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTabPlayback(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

private:
	int ShowBasePage( int _iIndex );
	void UI_UpdateText();

private:
	CTabCtrl m_tabPlayback;
	CLS_BasePage* m_pPage[PLAYBACK_MAX];
	CLS_BasePage* m_pCurrent;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;

};

#endif
