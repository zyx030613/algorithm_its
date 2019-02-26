#ifndef _DNS_DSM_PAGE_H
#define _DNS_DSM_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "../Include/NSLOOK_INTERFACE.h"
#include "../Common/SortListCtrl.h"


// CLS_DnsDSMPage dialog

class CLS_DnsDSMPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DnsDSMPage)

public:
	CLS_DnsDSMPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DnsDSMPage();

// Dialog Data
	enum { IDD = IDD_DLG_MNG_DSM_DNS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iRegID,int _iRegUser,int _iRegPwd);
	virtual void OnLanguageChanged(int _iLanguage);
	static int __stdcall DnsNotify(int _iCount,REG_DNS *_pDNS);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnDsmDnsRefresh();
	afx_msg LRESULT OnDnsMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCbnSelchangeCboDsmDnsPage();
	afx_msg void OnNMClickListDsmDns(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCboDsmDnsQueryType();
	afx_msg void OnBnClickedBtnDsmDnsQuery();
	afx_msg void OnNMDblclkListDsmDns(NMHDR *pNMHDR, LRESULT *pResult);

private:
	void UI_UpdateDialog();
	void Refresh();
	void AddDns(REG_DNS* _pDns);
	CString GetNvsType(int _iNvsType);

public:
	static HWND s_hWnd;

private:
	CSortListCtrl m_lvDNS;
	int m_iRegID;
	char m_cRegUser[32];
	char m_cRegPwd[32];
	CComboBox m_cboQueryType;
	CComboBox m_cboPage;
	
};

#endif
