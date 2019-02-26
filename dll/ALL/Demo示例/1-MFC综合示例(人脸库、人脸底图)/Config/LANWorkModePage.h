#ifndef _LAN_WOKEMODE_PAGE_H
#define _LAN_WOKEMODE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_LANWorkModePage dialog

class CLS_LANWorkModePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_LANWorkModePage)

public:
	CLS_LANWorkModePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_LANWorkModePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_LAN_WORKMODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateLanNum();
	BOOL UI_UpdateWokeMode();
	BOOL UI_UpdateLansetMode();
	BOOL UI_UpdateMtu();

private:
	CComboBox m_cboWokeMode;
	CComboBox m_cboLanNo;
	CButton m_btnWokeMode;
	int m_iLogonID;
public:
	afx_msg void OnBnClickedButtonWorkmode();
	CEdit m_edtMtu;
	afx_msg void OnBnClickedButtonMtu();
	afx_msg void OnBnClickedButtonLansetmode();
	CComboBox m_cboLansetMode;
};

#endif