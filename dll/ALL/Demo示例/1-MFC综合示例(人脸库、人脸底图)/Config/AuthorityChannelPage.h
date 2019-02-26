#ifndef _AUTHORITY_CHANNEL_PAGE_H
#define _AUTHORITY_CHANNEL_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

#define CHANNEL_AUTHORITY_NUM		7
#define CHANNEL_OPTION_NUM			10
#define SUPPORT_MAX_CHANNEL			32

// CLS_AuthorityChannelPage dialog

class CLS_AuthorityChannelPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AuthorityChannelPage)

public:
	CLS_AuthorityChannelPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AuthorityChannelPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_AUTHORITY_CHANNEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateChannelAuthority();
	BOOL UI_UpdateUserList();
	BOOL UI_UpdateAutOptionList(); 

private:
	int m_iLogonID;
	CComboBox m_cboUserChoise;
	CComboBox m_cboRightOption;
	CButton m_btnAllChannel;
	CButton m_chkChannel[SUPPORT_MAX_CHANNEL];
	CButton m_btnSet;
	int m_iRightList[CHANNEL_OPTION_NUM][SUPPORT_MAX_CHANNEL];
	int m_iSaveFlag[CHANNEL_OPTION_NUM];
	int m_iChannelNum;
	int m_iAuthority;
	BOOL m_bIsAdmin;

public:
	afx_msg void OnCbnSelchangeComboUserChoise();
	afx_msg void OnCbnSelchangeComboRightOption();
	afx_msg void OnBnClickedCheckAll();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonSet();
};
#endif