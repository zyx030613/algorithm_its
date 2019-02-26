#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
// CLS_VCAEVENT_Perimeter dialog

class CLS_VCAEVENT_Perimeter : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Perimeter)

public:
	CLS_VCAEVENT_Perimeter(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_Perimeter();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_PERIMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CButton m_chkDisplayRule;
	CButton m_chkDisplayState;
	CComboBox m_cboTargetCheck;
	CEdit m_edtMinDis;
	CEdit m_edtMinTime;
	CComboBox m_cboColor;
	CComboBox m_cboAlarmColor;
	CEdit m_edtDirection;
	CComboBox m_cboIndentify;
	CEdit m_edtPointNum;
	CEdit m_edtPoints;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonPerimeterset();

	void OnLanguageChanged();
private:
	void UpdatePageUI();
	void UpdateUIText();
	void CleanText();
public:
	afx_msg void OnBnClickedButtonPerimeterstop();
	afx_msg void OnBnClickedButtonPerimeterstart();
	afx_msg void OnBnClickedCheckDisplayrule();
};
