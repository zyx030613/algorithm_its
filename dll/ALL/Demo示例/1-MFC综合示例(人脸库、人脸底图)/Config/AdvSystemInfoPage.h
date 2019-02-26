#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_AdvSystemInfoPage dialog

class CLS_AdvSystemInfoPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AdvSystemInfoPage)

public:
	CLS_AdvSystemInfoPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AdvSystemInfoPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ADVANCE_SYSTEM_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()

private:
	
	int  m_iLogonID;
	int m_iChannelNo;
	BOOL m_blTelnetClose;

	void UI_UpdateText();
	void UI_UpdateTimeFormat();
	void UI_UpdateConnInfoList();
	void UpdateConnInfoList();
	void UI_UpdateAlgType();

public:
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnLanguageChanged(int _iLanguage);
	void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	
public:
	CComboBox m_ComboBoxTimeFormat;
	CComboBox m_ComboBoxConnInfo;
	CListCtrl m_lstCtConnectInfo;
	CComboBox m_ComboBoxSeparate;
	CComboBox m_cboTimeMode;
	CButton m_chkWeekDis;
	CComboBox m_cboAlgorithmType;

	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonAdvSysSetTime();
	afx_msg void OnBnClickedButtonAdvSysDefault();
	afx_msg void OnBnClickedButtonAdvSysReboot();
	afx_msg void OnBnClickedButtonAdvSysShutdown();
	afx_msg void OnBnClickedButtonTimeFormatSet();
	afx_msg void OnCbnSelchangeComboConnectInfo();
	afx_msg void OnBnClickedButtonAdvSysRefresh();
	afx_msg void OnBnClickedRadioAdvSysTelnetSet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedSetAlgType();
	afx_msg void OnBnClickedButtonCalibrate();
};
