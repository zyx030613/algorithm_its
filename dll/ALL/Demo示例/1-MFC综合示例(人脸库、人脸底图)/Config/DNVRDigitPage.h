#ifndef _DNVR_DIGIT_PAGE_H
#define _DNVR_DIGIT_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_DNVRDigitPage dialog

class CLS_DNVRDigitPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DNVRDigitPage)

public:
	CLS_DNVRDigitPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DNVRDigitPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DNVR_DIGIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateDigit();
	BOOL UI_UpdateIPCPnp();

private:
	CButton m_chkDigitEnable;
	CComboBox m_cboConnectMode;
	CEdit m_edtIPIDDDNS;
	CEdit m_edtProxyIP;
	CComboBox m_cboDeviceChan;
	CEdit m_edtDevicePort;
	CComboBox m_cboStreamType;
	CComboBox m_cboNetMode;
	CComboBox m_cboPTZProtocol;
	CEdit m_edtPTZAddr;
	CEdit m_edtUserName;
	CEdit m_edtPassword;
	CEdit m_edtEncryptKey;
	CComboBox m_cboServerType;
	CComboBox m_cboIPCPnP;
	CButton m_btnDigit;
	CEdit m_edtComSend;
	CButton m_btnComSend;
	int m_iLogonID;
	int m_iChannelNo;

public:
	afx_msg void OnCbnSelchangeComboIpcpnp();
	afx_msg void OnBnClickedButtonDigit();
	afx_msg void OnBnClickedButtonComsend();
	afx_msg void OnStnClickedStaticIpidddns();
};
#endif