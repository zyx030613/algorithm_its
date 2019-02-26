#ifndef _MANAGE_WINDOW_H
#define _MANAGE_WINDOW_H

#include "../BasePage.h"
#include "../Common/Ini.h"

enum MANAGE_PAGE_INDEX
{
	MANAGE_MIN = 0,
	MANAGE_ADMIN = MANAGE_MIN,
	MANAGE_ACTIVE,
	MANAGE_DSM,
	MANAGE_MAX
};

// CLS_ManageWindow dialog

class CLS_ManageWindow : public CLS_BaseWindow
{
	DECLARE_DYNAMIC(CLS_ManageWindow)

public:
	CLS_ManageWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ManageWindow();

// Dialog Data
	enum { IDD = IDD_DLG_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnDestroy();
	afx_msg void OnTcnSelchangeTabManage(NMHDR *pNMHDR, LRESULT *pResult);

private:
	int ShowBasePage( int _iIndex );

private:
	CTabCtrl m_tabManage;
	CLS_BasePage* m_pPage[MANAGE_MAX];
	CLS_BasePage* m_pCurrent;
	CIniFile  m_iniFile;
	int m_iActiveShowType;

};

#endif
