#pragma once
#include "BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"


// CWifiPage dialog

class CWifiPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CWifiPage)

public:
	CWifiPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWifiPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_WIFI };
     
	void UI_UpdateSurface();

	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser );
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonSearch();
	virtual BOOL OnInitDialog();
	void UI_UpdateWifiCard(int _iCurSel);
	void UI_UpdateState(int _iCurSel);
	void UI_UpdateWorkMode();
	void UI_UpdateEncryption(int _iCurSel);
	void UI_UpdateKeyType(int _iCurSel);
	void UI_UpdatePwdType(int _iCurSel);
	void UI_UpdateKeyNum(int _iCurSel);
	void UI_UpdateWifiList();
	void UI_UpdateWifiDhcp();
	CComboBox m_cboWifiCard;
	CComboBox m_cboWifiState;
	CComboBox m_cboWifiWorkMode;
	CComboBox m_cboEncryption;
	CComboBox m_cboKeyType;
	CComboBox m_cboKeyNum;
	CComboBox m_cboPwdType;
	CListCtrl m_lstWifiList;
	int m_iLogonID;
	int m_iWifiWorkMode;
	afx_msg void OnBnClickedButtonSetwifi();
	void UpdateDeviceInfo();
	afx_msg void OnBnClickedButtonWifimode();
	afx_msg void OnBnClickedButtonSetapdhcp();
	afx_msg void OnHdnItemdblclickListWifilist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckDhcp();
	afx_msg void OnBnClickedCheckApdhcp();
	CButton m_chkDhcp;
	CButton m_chkApDhcp;
};
