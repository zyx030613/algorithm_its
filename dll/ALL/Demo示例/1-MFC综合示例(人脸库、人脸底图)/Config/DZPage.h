#ifndef _DZ_PAGE_H_
#define _DZ_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_DZPage dialog

class CLS_DZPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DZPage)

public:
	CLS_DZPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DZPage();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;

private:
	void UI_UpdateDialog();

public:
	afx_msg void OnBnClickedButtonDzset();
private:
	CEdit m_edtParam1;
	CEdit m_edtParam2;
	CEdit m_edtParam3;
	CEdit m_edtParam4;
	CEdit m_edtParam6;
	CEdit m_edtParam5;
	CEdit m_edtParam7;
	CEdit m_edtParam8;
	CEdit m_edtParam9;
	CEdit m_edtParam10;
	CEdit m_edtParam11;
	CEdit m_edtParam12;
	CEdit m_edtParam13;
	CEdit m_edtParam14;
	CEdit m_edtParam15;
	CEdit m_edtParam16;
	CEdit m_edtParam17;
	CEdit m_edtParam18;
	CEdit m_edtParam19;
	CEdit m_edtParam20;
};

#endif
