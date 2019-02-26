#ifndef _DVRLOG_PAGE_H
#define _DVRLOG_PAGE_H

#include "../BasePage.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_DVRLogPage dialog

class CLS_DVRLogPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DVRLogPage)

public:
	CLS_DVRLogPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DVRLogPage();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_LOG_DVR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	int m_iLogonID;
	int m_iChannelNo;
	CListCtrl m_ctlListDVRLog;
	CComboBox m_cboLogType;
	CComboBox m_cboLanguage;
	CDateTimeCtrl m_dtpBeginDate;
	CDateTimeCtrl m_dtpEndDate;
	CDateTimeCtrl m_dtpBeginTime;
	CDateTimeCtrl m_dtpEndTime;
	NVS_LOG_QUERY   m_logQuery;
	int     m_iCurrentPage;
	int     m_iTotalFiles;
	int     m_iTotalPages;   
public:
	afx_msg void OnBnClickedButtonCfgLogDvrQuery();
	afx_msg void OnBnClickedButtonCfgLogdvrFirstpage();
	afx_msg void OnBnClickedButtonCfgLogdvrPrepage();
	afx_msg void OnBnClickedButtonCfgLogdvrNextpage();
	afx_msg void OnBnClickedButtonCfgLogdvrLastpage();
	void UI_UpdateDialog();
	void UI_UpdateTimeRange();
	void UpdateLogFiles(int _iTotal, int _iCount);
	void UI_UpdateLogCount();
	CString TimeToCString(NVS_FILE_TIME _nvsTime);
};

#endif
