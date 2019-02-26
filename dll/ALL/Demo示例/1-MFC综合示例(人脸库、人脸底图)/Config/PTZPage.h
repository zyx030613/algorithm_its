#ifndef _PTZ_PAGE_H_
#define _PTZ_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_PTZPage dialog

class CLS_PTZPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_PTZPage)

public:
	CLS_PTZPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PTZPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_PTZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedButtonDeviceType();
	afx_msg void OnBnClickedButtonPtzFormat();

private:
	void UI_UpdateDialog();
	void UI_UpdateWindow();

private:
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboProtocolName;
	CComboBox m_cboComNo;
	CSpinButtonCtrl m_spinAddress;
	CComboBox m_cboBaudRate;
	CComboBox m_cboParityBit;
	CComboBox m_cboDataBit;
	CComboBox m_cboStopBit;
	CButton m_chkEnable;
	CEdit m_edtPresetIndex;
	CEdit m_edtIdleTime;
	CButton m_btnAutoBack;
public:
	afx_msg void OnBnClickedButtonAutoback();
private:
	CSpinButtonCtrl m_spinPreset;
	CSpinButtonCtrl m_spinIdleTime;
public:
	afx_msg void OnBnClickedChnptzEnable();
};

#endif
