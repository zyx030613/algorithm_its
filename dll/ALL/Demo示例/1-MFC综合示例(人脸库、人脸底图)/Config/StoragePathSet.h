#ifndef _STORAGE_PATH_SET_H_
#define _STORAGE_PATH_SET_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_VideoEncodeSlicePage dialog

class CLS_StoragePathSetPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_StoragePathSetPage)

public:
	CLS_StoragePathSetPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_StoragePathSetPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_STORAGE_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonSetPath();

private:
	BOOL UI_UpdateStoragePathType();
	void UI_UpdateDialog();

private:
	CComboBox m_cboPathType;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	
};

#endif
