#ifndef _AUTHORITY_REMOTE_PAGE_H
#define _AUTHORITY_REMOTE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

#define REMOTE_AUTHORITY_NUM		10
#define CHANNEL_OPTION_NUM			10
#define SUPPORT_MAX_CHANNEL			32

// CLS_AuthorityRemotePage dialog

class CLS_AuthorityRemotePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AuthorityRemotePage)

public:
	CLS_AuthorityRemotePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AuthorityRemotePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_AUTHORITY_REMOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateRemoteAuthority();
	BOOL UI_UpdateUserList();
	BOOL UI_UpdateEnableList();

private:
	int m_iLogonID;
	CComboBox m_cboUserChoise;
	CButton m_chkRemoteRight[REMOTE_AUTHORITY_NUM];
	CButton m_btnSet;
	CButton m_chkAll;
	int m_iAuthority;
	int m_iIsAllowSet[REMOTE_AUTHORITY_NUM];			//1允许设置，0不允许设置
	BOOL m_bIsAdmin;

public:
	afx_msg void OnCbnSelchangeComboUserChoise();
	afx_msg void OnBnClickedCheckAll();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedBtnVcacarcheckEn();
	afx_msg void OnBnClickedBtnVcacarcheckDisen();
	afx_msg void OnBnClickedBtnSnapshot();
};
#endif