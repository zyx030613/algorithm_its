#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
// CLS_VCAEVENT_OSC dialog

class CLS_VCAEVENT_Abandum : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Abandum)

public:
	CLS_VCAEVENT_Abandum(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_Abandum();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_ABANDUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CButton m_chkDisplayRule;
	CButton m_chkDisplayState;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;
	CEdit m_edtMinTime;
	CComboBox m_cboColor;
	CComboBox m_cboAlarmColor;
	CEdit m_edtMainRegion;
	CEdit m_edtSubRegion1;
	CEdit m_edtSubRegoin2;
	CEdit m_edtSubRegion3;
	CButton m_chkValid;

	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonAbandumset();
	void OnLanguageChanged();

private:
	void UpdatePageUI();
	void UpdateUIText();
	
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void CleanText();
	afx_msg void OnBnClickedButtonAbandumStop();
	afx_msg void OnBnClickedButtonAbandumStart();
};
