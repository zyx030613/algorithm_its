#ifndef _ATM_PAGE_H_
#define _ATM_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"



// CLS_ATMPage dialog

class CLS_ATMPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ATMPage)

public:
	CLS_ATMPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ATMPage();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
// Dialog Data
	enum { IDD = IDD_DLG_CFG_ATM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	CEdit m_edtOsdEnable;
	CEdit m_edtOsdX;
	CEdit m_edtOsdY;
	CComboBox m_cmbInformWay;
	CComboBox m_cmbProtocolName;
	CEdit m_edtSrcIP;
	CEdit m_edtSrcPort;
	CEdit m_edtDestIP;
	CEdit m_edtDestPort;
private:
	void UI_UpdateATMInfo();
	void UI_UpdateDialog();
	void UI_UpdateATMInfo(int _iInformWay);
public:
	afx_msg void OnBnClickedButtonAtminfoSet();
private:
	CComboBox m_cmbComNo;
	CComboBox m_cmbWorkMode;
	CEdit m_edtComFormat;
public:
	afx_msg void OnCbnSelchangeComboAtmInformway();
};

#endif