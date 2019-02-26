#ifndef _PU_PAGE_H
#define _PU_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_PUPage dialog

class CLS_PUPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_PUPage)

public:
	CLS_PUPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PUPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_OPTION_PU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedButtonManageinfo();
	afx_msg void OnBnClickedButtonDeviceid();
	afx_msg void OnEnChangeEditAccesspass();

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateManagerInfo();
	BOOL UI_UpdateDeviceID();
	BOOL UI_UpdateIdentiCode();
	BOOL UI_UpdateBarCode();

private:
	CEdit m_edtRegisterSvr;
	CEdit m_edtRegisterSvrPort;
	CEdit m_edtHeartbeatSvr;
	CEdit m_edtHeartbeatSvrPort;
	CEdit m_edtAlarmSvr;
	CEdit m_edtAlarmSvrPort;
	CButton m_btnManageInfo;
	CEdit m_edtDeviceID;
	CEdit m_edtDeviceName;
	CEdit m_edtVSPPort;
	CEdit m_edtVAPPort;
	CEdit m_edtAccessPass;
	CEdit m_edtMD5;
	CButton m_btnDeviceID;
	int m_iLogonID;
public:
	afx_msg void OnBnClickedBtnIdentiCode();
	afx_msg void OnBnClickedBtnBarcodeSet();
};

#endif