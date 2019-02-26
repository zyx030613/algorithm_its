#pragma once
#include "../BasePage.h"
#include "afxwin.h"


// CLS_Storage_ANR dialog

class CLS_StorageANR : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_StorageANR)

public:
	CLS_StorageANR(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_StorageANR();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_STORAGE_ANR };
public:
	void UI_UpdateDialogTest();
	virtual void OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_cboDisconnectRec;
	int m_iLogonID;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnStorageAnrSet();
};
