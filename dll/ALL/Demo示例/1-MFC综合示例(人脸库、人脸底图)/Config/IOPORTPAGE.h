#pragma once
#include "afxwin.h"
#include "../BasePage.h"
// CLS_IOPORTPAGE dialog

class CLS_IOPORTPAGE : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_IOPORTPAGE)

public:
	CLS_IOPORTPAGE(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_IOPORTPAGE();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_IOPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateIOPortParam();
private:
	int m_iLogonID;
	int m_iEnable[LEN_16];
	CButton m_chkOutPortEnable[32];
public:
	afx_msg void OnBnClickedAlarminmode();
	CComboBox m_cmbAlarmInPortID;
	CComboBox m_cmbAlarmInModeID;
	afx_msg void OnBnClickedButtonalarmoutmode();
	CComboBox m_cmbAlarmOutModeID;
	//afx_msg void OnBnClickedCheckAlarmoutportEnable();
	//CButton m_chkAlarmOutPortEnable;
	afx_msg void OnBnClickedButtonAlarmlinkSet();
	afx_msg void OnBnClickedButtonStopamodeSet();
	CComboBox m_cmbAlarmOutPortID;
	CComboBox m_cmbStopModeID;
	afx_msg void OnBnClickedCheckAlarmport();
	CComboBox m_cmbInPortChnID;
	CComboBox m_cmbAlarmActiveModeOutPortID;
	CEdit m_edtAlarmDelayTimeID;
	CButton m_chkOutPortEnableID;
	CButton m_chkAlarmPortEnableID;
	CComboBox m_cmbAlarmOutPortStatusID;
	afx_msg void OnCbnSelchangeComboAlarminport();
	afx_msg void OnCbnSelchangeComboalarmoutport();
	afx_msg void OnCbnSelchangeComboIoportNum();
	afx_msg void OnCbnSelchangeComboAlarmoutport();
	afx_msg void OnEnChangeEditDelaytime();
	afx_msg void OnBnClickedButtonAlarmoutportEnableSet();
	afx_msg void OnBnClickedChkChannel(UINT _uiID);
};
