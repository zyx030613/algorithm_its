#ifndef _IP_PAGE_H_
#define _IP_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"


// CLS_IPPage dialog

class CLS_IPPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_IPPage)

public:
	CLS_IPPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_IPPage();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPropertyChangeip();
	afx_msg void OnBnClickedCheckPropertyDhcp();
	afx_msg void OnBnClickedCheckPropertyUpnp();
	afx_msg void OnBnClickedButtonFilterSet();
private:
	void GetPropertyEditInfo();
	void GetUpnpInfo();
	void GetDhcpInfo();
	void GetSnmpInfo();
	void GetFilterInfo();
	void GetRegInfo();
	void GetPppoeInfo();
	void GetPortInfo();
	void UI_UpdateDialog();
private:
	int m_iLogonID;
	CButton m_chkDhcp;
private:
	CEdit m_edtPtopertyIP;
	CEdit m_edtPropertyMask;
	CEdit m_edtPropertyDNS;
	CEdit m_edtPropertyBackDNS;
	CEdit m_edtPropertyGateway;
private:
	CButton m_chkUpnp;
private:
	CEdit m_edtFilterIP;
	CEdit m_edtFilterMask;
public:
	afx_msg void OnBnClickedButtonRegSet();
private:
	CEdit m_edtRegID;
	CEdit m_edtRegPassword;
	CEdit m_edtRegNvsname;
	CEdit m_edtRegCenterIP1;
	CEdit m_edtRegCenterIP2;
	CEdit m_edtRegPort1;
	CEdit m_edtRegPort2;
private:
	CEdit m_edtPppoeAccount;
	CEdit m_edtPppoePassword;
	CButton m_chkUsingPppoe;
	CButton m_chkSNMP;
public:
	afx_msg void OnBnClickedCheckUsingpppoe();
	afx_msg void OnBnClickedButtonPppoeset();
	afx_msg void OnBnClickedButtonWebport();
private:
	CEdit m_edtWebport;
	CEdit m_edtProcxyIP;
	CEdit m_edtProcxyPort;
	CEdit m_edtProcxyString;
public:
	afx_msg void OnBnClickedButtonProcxysend();
	afx_msg void OnBnClickedCheckSnmp();
};

#endif
