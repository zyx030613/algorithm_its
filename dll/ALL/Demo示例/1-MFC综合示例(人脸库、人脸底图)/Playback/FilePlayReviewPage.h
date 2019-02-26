#pragma once

#include "../BasePage.h"
#include "afxcmn.h"
#include "../Include/PLAYSDKM4_INTERFACE.h"
#include "afxdtctl.h"
// CLS_FilePlayReviewPage dialog
#define TIMER_PLAY_REVIEW_CHECK_PROGRESS 1
#define TIMER_CHEACK_CONTINUE_DOWNLOAD 2
#define PLAYSDKMSG 5678
#define INVALID_ID (-1)

#define WM_PLAY_PAGE_DESTORY			(WM_USER + 3001)
#define MAX_PLAY_PAGE_NUM				5		//最多同时播放5路


enum DWONLOAD_TYPE
{
	DownloadByFile = 0,
	DownloadByTime,
	SuperPlayBackByFile,
	SuperPlayBackByTime
};
using namespace PLAYSDK_INTERFACE;
class CLS_FilePlayReviewPage : public  CDialog
{
	DECLARE_DYNAMIC(CLS_FilePlayReviewPage)

public:
	CLS_FilePlayReviewPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_FilePlayReviewPage();

// Dialog Data
	enum { IDD = IDD_DLG_PBK_REVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int m_iLogonID;
	CString m_szFileName;
	NVS_FILE_TIME m_begintime;
	NVS_FILE_TIME m_endtime;
	int  m_iDownloadType;
	CWnd* m_phParentHwnd;
	void UI_UpdateText();
	void UI_UpdateProgress();
	void UI_UpdateProgressByFile();
	void UI_UpdateProgressByTime();
	void StartDownload();

	void StartPlay();
	void StopPlay();

	void InitDownloadByFile();
	void InitDownloadByTime();
	void StartDownloadByFile();
	void StartDownloadByTime();
	void ResetDownloadPage();
	void ProccessDownloadMsg(int _iResourceID);
	void ProcessStreamSearchEnd();
	void ProcessPlayDecrypt(int _iDecryptCode);
	void ContinueDownload();
	void ProcessVodEnd();

public:
	void SetDownloadParam(int _iLogonID, CString _szRemoteFileName);
	void SetDownloadParamEx(int _iLogonID, CString _szRemoteFileName);
	void SetDownloadParam(int _iLogonID, int _iChannelNo, NVS_FILE_TIME * _BeginTime, NVS_FILE_TIME *_EndTime);
	void SetDownloadParamEx(int _iLogonID, int _iChannelNo, NVS_FILE_TIME * _BeginTime, NVS_FILE_TIME *_EndTime);
	void OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser );
	void PauseDownload();
	void StartSuperPlayBackByFile();
	void StartSuperPlayBackByTime();
	CString GetFilename();
	int		GetLogonID();

public:
	int  m_iDownloadPause;
	unsigned long m_ulConnID;	
	int m_iPlayerID;
	int m_iVideoHigth;
	int m_iVideoWidth;
	HWND m_hWndVideo;
	int m_iChannelNo;
	int m_iDownloadSpeed;
	unsigned char m_cDataBuffer[1024*1024];
	int  m_iDataLen;
	CProgressCtrl m_ProgressDownload;
	CProgressCtrl m_ProgressPlay;
    int m_iPlayState;
	CDateTimeCtrl m_DTLocate;
	
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonLocate();
	afx_msg void OnBnClickedButtonDownloadSpeed();
	afx_msg LRESULT OnPlaySDKMsg( WPARAM _wParam, LPARAM _lParam);
	afx_msg void OnBnClickedButtonDecrypt();
	afx_msg void OnNMThemeChangedDatetimepickerPbkLocateTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerPbkLocateTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPlaySpeed();
	afx_msg void OnBnClickedBtnOsd();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnFastForward();
	afx_msg void OnBnClickedBtnFastBackward();
	afx_msg void OnBnClickedBtnSeek();
	afx_msg void OnBnClickedBtnSlowforward();
protected:
	virtual void OnCancel();

};

void AbsSecondsToNvsFileTime(NVS_FILE_TIME* _fileTime,long _tTime);
unsigned int NvsFileTimeToAbsSeconds(NVS_FILE_TIME * _pFileTime);

