#ifndef _REMOTE_FILE_TAB_H
#define _REMOTE_FILE_TAB_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "CLS_DownloadFile.h"
#include <list>
using namespace std;

// CLS_RemoteFilePage dialog

#define MAX_PAGESIZE    20
#define TIMER_QUERY_DOWNLOAD_PROGRESS 1
#include "FilePlayReviewPage.h"
class CLS_RemoteFilePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_RemoteFilePage)

public:
	CLS_RemoteFilePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_RemoteFilePage();

// Dialog Data
	enum { IDD = IDD_DLG_PBK_REMOTE_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnLanguageChanged(int );
	virtual void OnLogoffDevice(int _iLogonID);
	DECLARE_MESSAGE_MAP()

private:
	void Update_UI_Text();
	void Update_UI_Query_Result();
	void Update_UI_IPAndID();
	void ResetQuery();

	void QueryFile();
	void QueryDownloadProgress();
	BOOL IsFileInDownLoadList(int _iLogonID, CString _szFileName, unsigned long * _iConnID,CLS_DownloadFile** _pFile = NULL);
	BOOL IsFileInPlayBackList(int _iLogonID, CString _szFileName, int* _piCurrentDevPlayPageNum = NULL);
	void DeleteDownload(unsigned long  _ulConnID);
	void DeleteDownload(const int _iLogonID, int _iFlag);
	void ProcessDownloadFinished(unsigned long _ulID);
	void ProcessErrorOrder(const int _iLogonID);
	void ProcessDownloadFault(unsigned long _ulID);
	void ProcessDownloadInterrupt(unsigned long _ulID);
	CString GetFileNameByConID(unsigned long  _ulConnID);
	void OpenFile(unsigned long  _ulConnID);



public:

	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;

	int m_iTotalCount;
	int m_iCurrentCount;
	int m_iCurrentPage;
	int m_iTotalPage;

	CString m_szFileName;
	list<CLS_DownloadFile *> m_lstDownloadFile;
	list<CLS_FilePlayReviewPage *> m_lstPlayPage;

	CComboBox m_ComboFileType;
	CComboBox m_ComboRecType;
	CComboBox m_ComboChannelNo;
	CDateTimeCtrl m_DTQueryBeginTime;
	CDateTimeCtrl m_DTQueryEndTime;
	CEdit m_EditOSD;
	CListCtrl m_ListQueryFile;
	CComboBox m_ComboQueryPage;
	CComboBox m_cboAlarmType;
	CComboBox m_cboAlarmPort;
	CImageList imageList;
	CComboBox m_cboReqMode;
	CDateTimeCtrl m_DTRecordingDate;
	CListCtrl m_lstMoonInfoList;
	CComboBox m_cboDownloadFileType;
	CComboBox m_cboStreamNo;

	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnPlayPageDestory(WPARAM wParam, LPARAM lParam);			//视频播放窗口销毁
	afx_msg void OnBnClickedButtonPlayback();
	afx_msg void OnCbnSelchangeComboChannel();
	afx_msg void OnCbnSelchangeComboFileType();
	afx_msg void OnCbnSelchangeComboRecType();
	afx_msg void OnCbnSelchangeComboQueryPage();
	afx_msg void OnBnClickedButtonPrepage();
	afx_msg void OnBnClickedButtonNextPage();
	afx_msg void OnBnClickedButtonFirstPage();
	afx_msg void OnBnClickedButtonLastPage();
	afx_msg void OnDtnDatetimechangeDatetimepickerQueryBegintime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerQueryEndtime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListQueryFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonStopDownload();
	afx_msg void OnBnClickedButtonPauseDownload();
	afx_msg void OnBnClickedButtonContinueDownload();
	afx_msg void OnLvnItemchangedListQueryFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPlaybackMoonRefresh();

	void OnNetFileLockFiles( WPARAM wParam, LPARAM lParam );
	void OnLogonNotify( int _ulLogonID, int _iStatus );
	void UpdateMoonInfo();
	void RefreshMoonInfo();
private:
	CButton m_chkBreakNetContinue;
public:
	afx_msg void OnBnClickedButtonBreakNetContinue();
private:
	CButton m_chkBatchQuery;
};

#endif
