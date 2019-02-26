#pragma once
#include "../BasePage.h"
#include "afxdtctl.h"
#include "FilePlayReviewPage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_RemoteByTimePage dialog
#define TIMER_DOWNLOAD_BY_TIME 1
class CLS_RemoteByTimePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_RemoteByTimePage)

public:
	CLS_RemoteByTimePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_RemoteByTimePage();

// Dialog Data
	enum { IDD = IDD_DLG_PBK_REMOTE_BY_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	unsigned int m_ulConnID;
	int m_iLogonID;
	NVS_FILE_TIME   m_timeBegin ;
	NVS_FILE_TIME   m_timeEnd;
	list<CLS_FilePlayReviewPage *> m_lstPlayPage;
	CComboBox m_cboDownloadFileType;
	CComboBox m_cboStreamNo;
	CDateTimeCtrl m_DTDownloadBeginTime;
	CDateTimeCtrl m_DTDownloadEndTime;
	CComboBox m_ComboChannelNo;
	CProgressCtrl m_ProgressDownload;
	CComboBox m_cboDownloadFileFlag;

	void UI_UpdateText();
	void Update_UI_IPAndID();
	void QueryDownloadProgress();
	void ProccessDownloadMsg(int _iResourceID);

public:
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnLanguageChanged(int );
	virtual void OnLogoffDevice(int _iLogonID);

	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg LRESULT OnPlayPageDestory(WPARAM wParam, LPARAM lParam);			//视频播放窗口销毁
	afx_msg void OnBnClickedButtonPlayByTimeDownload();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPlaybackByTimePlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedBtnSuperVodByTime();
};

