#ifndef _UDP_PAGE_H
#define _UDP_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_UDPPage dialog

class CLS_UDPPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_UDPPage)

public:
	CLS_UDPPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_UDPPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_UDP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();

private:
	CEdit m_edtNVSIp;
	CEdit m_edtNVSPort;
	CEdit m_edtChannelNo;
	CEdit m_edtChannelNum;
	CEdit m_edtStreamType;
	CEdit m_edtUDPPort;
	CButton m_btnUDP;
	int m_iLogonID;

public:
	afx_msg void OnBnClickedButtonGetport();
};

#endif