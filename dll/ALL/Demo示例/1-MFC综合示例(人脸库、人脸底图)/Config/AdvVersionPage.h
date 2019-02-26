#pragma once
#include "../BasePage.h"


// CLS_AdvVersionPage dialog

class CLS_AdvVersionPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AdvVersionPage)

public:
	CLS_AdvVersionPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AdvVersionPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ADVANCE_VERSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnLanguageChanged(int _iLanguage);
	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	int m_iChannelNo;
	void UI_UpdateText();
	void UI_UpdateParam();
	
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedEditAdvanceSet();
};
