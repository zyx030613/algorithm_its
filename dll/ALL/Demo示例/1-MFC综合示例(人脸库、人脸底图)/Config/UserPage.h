#ifndef _USER_PAGE_H_
#define _USER_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_UserPage dialog

class CLS_UserPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_UserPage)

public:
	CLS_UserPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_UserPage();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdduser();
	afx_msg void OnBnClickedButtonModifypassword();
	afx_msg void OnBnClickedButtonDeleteuser();
	afx_msg void OnBnClickedButtonSet();
	void UI_UpdateDialog();
	void UI_UpdateCurUserInfo();
	void UI_UpdateUserInfo(int _iIndex);
	void UI_UpdateUserList();
	void UI_UpdateMaxUserCount();
private:
	int m_iLogonID;
	CListBox m_lstUserInfo;
	CEdit m_edtUserName;
	CEdit m_edtOldPwd;
	CEdit m_edtNewPwd;
	CComboBox m_cboAuthority;
	CEdit m_edtMaxUser;
public:
	afx_msg void OnLbnSelchangeListUserinfo();
};

#endif
