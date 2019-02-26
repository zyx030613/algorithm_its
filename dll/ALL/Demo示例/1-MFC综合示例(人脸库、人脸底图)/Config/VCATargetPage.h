#pragma once
#include "afxwin.h"

#include "../BasePage.h"


// CLS_VCATargetPage dialog

class CLS_VCATargetPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCATargetPage)

public:
	CLS_VCATargetPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCATargetPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VCA_TARGET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int		m_iLogonID;
	int		m_iChannelNO;
	int		m_iStreamNO;

	vca_TVCAParam *m_pVcaParam;
	
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);

	int		RestartVCALib(int _iLogonID, int _iChannel = -1);
	void	UpdatePageUI();
	void	UpdateUIText();
	bool	IsDigistChannel(int _iChannelNO);
public:
	CComboBox m_cboVCAVideoSz;
	afx_msg void OnBnClickedCheckVcaEnable();

	virtual BOOL OnInitDialog();
	CButton m_chkDisplayTarget;
	CComboBox m_cboTargetColor;
	CButton m_chkDisplayTrace;
	CComboBox m_cboAlarmColor;
	CEdit m_edtTagetTraceLen;
	afx_msg void OnBnClickedButtonVcaTargetSet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeComboVcaVideosz();
	afx_msg void OnCbnSelchangeComboVcaEnable();
private:
	CComboBox m_cboEnable;
	CComboBox m_cboSensitivity;
public:
	afx_msg void OnBnClickedCheckVcaDisplayTrace();
};
