#ifndef _VIDEO_ENCRYPT_PAGE_H_
#define _VIDEO_ENCRYPT_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_VideoEncryptPage dialog

class CLS_VideoEncryptPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VideoEncryptPage)

public:
	CLS_VideoEncryptPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VideoEncryptPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VIDEO_ENCRYPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonEncrypt();
	afx_msg void OnBnClickedButtonDecrypt();

private:
	BOOL IsValidKey( char* _pcPwd );
	BOOL UI_UpdateVideoEncrypt();
	BOOL UI_UpdateVideoDecrypt();
	void UI_UpdateDialog();

private:
	CComboBox m_cboEncryptType;
	CEdit m_edtEncryptKey;
	CEdit m_edtDecryptKey;
	int m_iLogonID;
	int m_iChannelNo;
	
};

#endif
