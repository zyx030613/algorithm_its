#ifndef _DDNS_PAGE_H
#define _DDNS_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_DDNSPage dialog

class CLS_DDNSPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DDNSPage)

public:
	CLS_DDNSPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DDNSPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DDNS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateDDNS();

private:
	CEdit m_edtUserName;
	CEdit m_edtPassword;
	CEdit m_edtNvsName;
	CComboBox m_cboDDNSServer;
	CEdit m_edtDDNSPort;
	CButton m_chkEnable;
	CButton m_btnDDNS;
	int m_iLogonID;

public:
	afx_msg void OnBnClickedButtonDdns();
};

#endif