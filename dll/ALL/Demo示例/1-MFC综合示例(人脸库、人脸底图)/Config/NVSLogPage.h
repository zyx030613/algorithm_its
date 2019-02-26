#ifndef _NVSLOG_PAGE_H
#define _NVSLOG_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_NVSLogPage dialog

class CLS_NVSLogPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_NVSLogPage)

public:
	CLS_NVSLogPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_NVSLogPage();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_LOG_NVS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	CEdit m_edtLogLevel;
	CEdit m_edtLogfileSize;
	CEdit m_edtLogInfo;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonNVSLogSet();
	afx_msg void OnBnClickedButtonLogNVSRefresh();
	afx_msg void OnBnClickedButtonLogNVSClearLogfile();
	void UI_UpdateDialog();
	void UI_UpdateNVSLogList();
	void UI_UpdateNVSLogInfo();
	afx_msg void OnEnChangeEditLogDvrLoginfo();
	afx_msg void OnBnClickedButtonCfgNvsClearcurrentfile();
};

#endif
