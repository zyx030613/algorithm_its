#ifndef _SO_PAGE_H_
#define _SO_PAGE_H_

#include "../BasePage.h"

// CLS_SOPage dialog

class CLS_SOPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_SOPage)

public:
	CLS_SOPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_SOPage();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_SO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSoRun();
	afx_msg void OnBnClickedButtonSoStop();
	bool UI_UpdatePlatformApp();
	void UI_UpdateDialog();
private:
	int m_iLogonID;
	CComboBox m_cboPlatformSO;
};

#endif

