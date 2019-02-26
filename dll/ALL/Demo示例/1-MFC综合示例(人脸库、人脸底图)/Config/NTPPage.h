#ifndef _NTP_PAGE_H
#define _NTP_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"


// CLS_NTPPage dialog

class CLS_NTPPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_NTPPage)

public:
	CLS_NTPPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_NTPPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_NTP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateDialog();
	BOOL UI_UpdateNTP();
	void NotifyResult(int _iLParam);

	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	afx_msg void OnBnClickedButtonNtp();
	afx_msg void OnBnClickedBtnLanNtpTest();

private:
	CEdit m_edtNTPIp;
	CEdit m_edtNTPPort;
	CEdit m_edtInterval;
	CButton m_btnNTP;
	int m_iLogonID;
	int m_iChannelNo;
};

#endif