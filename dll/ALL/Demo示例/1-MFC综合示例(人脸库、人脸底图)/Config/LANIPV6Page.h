#ifndef _LAN_IPV6_PAGE_H
#define _LAN_IPV6_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"


// CLS_LANIPV6Page dialog

class CLS_LANIPV6Page : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_LANIPV6Page)

public:
	CLS_LANIPV6Page(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_LANIPV6Page();

	// Dialog Data
	enum { IDD = IDD_DLG_CFG_LAN_IPV6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateLanNum();
	BOOL UI_UpdateIPV6();

private:
	CComboBox m_cboLanNo;
	CEdit m_edtIP;
	CEdit m_edtPreFixLen;
	CEdit m_edtGateway;
	CEdit m_edtDNS;
	CEdit m_edtBackDNS;
	CEdit m_edtReserved;
	CButton m_btnIPV6;
	int m_iLogonID;
public:
	afx_msg void OnBnClickedButtonIpv6();
	afx_msg void OnCbnSelchangeComboIpv6Lanno();
};

#endif