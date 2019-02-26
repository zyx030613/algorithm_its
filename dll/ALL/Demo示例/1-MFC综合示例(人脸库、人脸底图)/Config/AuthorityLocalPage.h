#ifndef _AUTHORITY_LOCAL_PAGE_H
#define _AUTHORITY_LOCAL_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

#define LOCAL_AUTHORITY_NUM			8
#define CHANNEL_OPTION_NUM			10
#define SUPPORT_MAX_CHANNEL			32

// CLS_AuthorityLocalPage dialog

class CLS_AuthorityLocalPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AuthorityLocalPage)

public:
	CLS_AuthorityLocalPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AuthorityLocalPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_AUTHORITY_LOCAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateLocalAuthority();
	BOOL UI_UpdateUserList();
	BOOL UI_UpdateEnableList();

private:
	int m_iLogonID;
	CComboBox m_cboUserChoise;
	CButton m_chkLocalRight[LOCAL_AUTHORITY_NUM];
	CButton m_btnSet;
	CButton m_chkAll;
	int m_iAuthority;
	int m_iIsAllowSet[LOCAL_AUTHORITY_NUM];			//1允许设置，0不允许设置
	BOOL m_bIsAdmin;
public:
	afx_msg void OnCbnSelchangeComboUserChoise();
	afx_msg void OnBnClickedCheckAll();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedCheckHandClearAlarm();
};
#endif