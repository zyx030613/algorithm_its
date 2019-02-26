#ifndef _LANGUAGE_PAGE_H
#define _LANGUAGE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"


// CLS_LanguagePage dialog

class CLS_LanguagePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_LanguagePage)

public:
	CLS_LanguagePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_LanguagePage();

	// Dialog Data
	enum { IDD = IDD_DLG_CFG_LANGUAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedButtonCurlanguage();
	afx_msg void OnBnClickedButtonTimezone();

private:
	BOOL UI_UpdateLanguage();
	BOOL UI_UpdateTimeZone();
	void UI_UpdateDialog();

private:
	CComboBox m_cboCurLanguage;
	CButton m_btnCurLanguage;
	CComboBox m_cboTimeZone;
	CButton m_btnTimeZone;
	CListCtrl m_lstLanguage;
	int m_iLogonID;
	
};

#endif
