#ifndef _BURN_H8_PAGE_H
#define _BURN_H8_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_BurnH8 dialog

class CLS_BurnH8Page : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_BurnH8Page)

public:
	CLS_BurnH8Page(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_BurnH8Page();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_BURN_H8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);

	afx_msg void OnBnClickedButtonH8SetConfig();
	afx_msg void OnCbnSelchangeComboh8CmdId();
	afx_msg void OnCbnSelchangeComboH8GramSeq();

	void UI_UpdateDialogText();
	void UpdateLifeMonitorConfigInfo();
	void UpdateLifeMonitorHBRealInfo();
	void UpdateLifeMonitorGramRealInfo();
private:
	int m_iLogonID;
	CComboBox m_cboMonitorType;
	CComboBox m_cboMonitorStatus;
	CEdit m_edtRealValue1;
	CEdit m_edtRealValue2;
	CEdit m_edtRealValue3;
	CEdit m_edtRealValue4;
	CComboBox m_cboGramID;
	CComboBox m_cboGramSeq;
	CEdit m_edtGramRate;
	CEdit m_edtTotalPoints;
	CEdit m_edtPointsValue;
	CComboBox m_cboCfgMonitorType;
	CComboBox m_cboCfgCmdID;
	CComboBox m_cboCfgCmdContent;	
public:
	afx_msg void OnCbnSelchangeComboh8MonitorType();
	afx_msg void OnCbnSelchangeComboH8GramId();
	afx_msg void OnCbnSelchangeComboh8MonitorTypeCfg();
};

#endif
