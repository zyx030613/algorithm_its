#ifndef _FTP_PAGE_H
#define _FTP_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_FTPPage dialog

class CLS_FTPPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_FTPPage)

public:
	CLS_FTPPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_FTPPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_FTP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateSnapShot();
	BOOL UI_UpdateLinkSend();
	BOOL UI_UpdateTimeSend();
	BOOL UI_UpdateFtpUpdate();

private:
	CComboBox m_cboEnable;
	CEdit m_edtQValue;
	CEdit m_edtInterval;
	CEdit m_edtPictureSize;
	CButton m_btnSnapShot;
	CButton m_chkLinkSendEnable;
	CButton m_chkEmail;
	CButton m_chkFtp;
	CButton m_chkTimeSendEnable;
	CComboBox m_cboTimeSendFileType;
	CDateTimeCtrl m_dtcTimeSend;
	CButton m_btnTimeSend;
	CEdit m_edtAddr;
	CEdit m_edtPort;
	CEdit m_edtPath;
	CEdit m_edtUser;
	CEdit m_edtPassword;
	CEdit m_edtUsage;
	CButton m_btnUpdate;
	int m_iLogonID;
	int m_iChannelNo;
public:
	afx_msg void OnBnClickedButtonFtpChannel();
	afx_msg void OnBnClickedButtonFtpSnapshot();
	afx_msg void OnBnClickedButtonLinksend();
	afx_msg void OnBnClickedButtonTimesend();
	afx_msg void OnBnClickedButtonFtpUpdate();
};

#endif