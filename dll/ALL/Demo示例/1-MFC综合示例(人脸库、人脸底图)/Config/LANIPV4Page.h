#ifndef _LAN_IPV4_PAGE_H
#define _LAN_IPV4_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"


// CLS_LANIPV4Page dialog

class CLS_LANIPV4Page : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_LANIPV4Page)

public:
	CLS_LANIPV4Page(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_LANIPV4Page();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_LAN_IPV4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedButtonIpv4();
	afx_msg void OnCbnSelchangeComboIpv4Lanno();
	afx_msg void OnBnClickedCheckDhcp();

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateLanNum();
	BOOL UI_UpdateIPV4();
	BOOL UI_UpdateDHCP();
	void DHCPEnable(BOOL bEnable);

private:
	CComboBox m_cboLanNo;
	CEdit m_edtLanType;
	CEdit m_edtIP;
	CEdit m_edtMask;
	CEdit m_edtGateway;
	CEdit m_edtDNS;
	CEdit m_edtBackDNS;
	CEdit m_edtReserved;
	CButton m_btnIPV4;
	int m_iLogonID;
};

#endif