#ifndef _REPORT_FORM_H
#define _REPORT_FORM_H

#include "BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

// CLS_ReportForm dialog

class CLS_ReportForm : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ReportForm)

public:
	CLS_ReportForm(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ReportForm();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_REPORT_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, int _lParam,int _iUserData);
	void UI_UpdateDialog();
	void UI_UpdateReportForm();
	void UI_UpdateFuncAbilityLevel();
	afx_msg void OnCbnSelchangeComboMainFuncType();
	afx_msg void OnCbnSelchangeComboSubFuncType();
	afx_msg void OnCbnSelchangeComboFormType();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	CComboBox m_cboMainFuncType;
	CComboBox m_cboSubFuncType;
	CComboBox m_cboFormType;
	CEdit m_edtFuncAbility;
	CEdit m_edtTotalNum;
	CEdit m_edtCurrentNum;
	CDateTimeCtrl m_dtpBeginDate;
	CDateTimeCtrl m_dtpBeginTime;
	CDateTimeCtrl m_dtpEndDate;
	CDateTimeCtrl m_dtpEndTime;
	CListCtrl m_lstReportForm;
};

#endif
