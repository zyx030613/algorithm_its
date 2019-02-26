#ifndef _DSM_PAGE_H
#define _DSM_PAGE_H

#include "../BasePage.h"

enum DSM_PAGE_INDEX
{
	DSM_MIN = 0,
	DSM_NVS = DSM_MIN,
	DSM_DNS,
	DSM_MAX
};
// CLS_DSMPage dialog

class CLS_DSMPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DSMPage)

public:
	CLS_DSMPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DSMPage();

// Dialog Data
	enum { IDD = IDD_DLG_MNG_DSM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnDestroy();
	afx_msg void OnTcnSelchangeTabDsm(NMHDR *pNMHDR, LRESULT *pResult);

private:
	int ShowBasePage( int _iIndex );
	void EnableDSMWindow(BOOL _bEnable);
	void UI_UpdateDialog();

private:
	CTabCtrl m_tabDSM;
	CLS_BasePage* m_pPage[DSM_MAX];
	CLS_BasePage* m_pCurrent;
	int m_iRegID;
	char m_cRegUser[32];
	char m_cRegPwd[32];
	
public:
	afx_msg void OnBnClickedBtnServerLogon();
	afx_msg void OnBnClickedBtnServerVersion();
	
};

#endif
