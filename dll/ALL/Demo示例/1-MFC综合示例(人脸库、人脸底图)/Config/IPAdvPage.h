#pragma once


#include "../BasePage.h"
#include "afxwin.h"

// CLS_IPAdvPage dialog

class CLS_IPAdvPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_IPAdvPage)

public:
	CLS_IPAdvPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_IPAdvPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_IPADV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateIpInfo();
private:
	int m_iLogonID;
public:
	afx_msg void OnBnClickedButtonFilterSet();
	CEdit m_edtFilterIP;
	CEdit m_edtFilterMask;
	CComboBox m_cboFilterType;
	CEdit m_edtIpString;
};

