#pragma once
#include "afxwin.h"
#include "VCAEventBasePage.h"


// CLS_VCAEVENT_Fight dialog

class CLS_VCAEVENT_Fight : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Fight)

public:
	CLS_VCAEVENT_Fight(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_Fight();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_FIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UI_UpdateDialogText();
	void UI_UpdateFightArithmetic();
	afx_msg void OnBnClickedBtnFightPointsDraw();
	afx_msg void OnBnClickedBtnFightSet();
private:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayAlarmNum;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboAreaColor;
	CEdit m_edtSensitivity;
	CEdit m_edtAlarmTime;
	CEdit m_edtPointsNum;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
