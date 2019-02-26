#pragma once

#include "afxwin.h"
#include "VCAEventBasePage.h"

// CLS_VCAEVENT_TripwireEx dialog

class CLS_VCAEVENT_TripwireEx : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_TripwireEx)

public:
	CLS_VCAEVENT_TripwireEx(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_TripwireEx();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_TRIPWIRE_EX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	void UpdatePageUI();
	void UpdateUIText();
	void CleanText();

public:
	afx_msg void OnBnClickedButtonTwexSet();
	afx_msg void OnBnClickedButtonTwexDraw();
	CComboBox m_cbo_twex_TargetType;
	CComboBox m_cbo_twex_AlarmColor;
	CComboBox m_cbo_twex_Color;
	CButton m_chk_twex_DisplayRule;
	CButton m_chk_twex_DisplayState;
	CButton m_chk_twex_TripWireType;
	CEdit m_edt_twex_MiniSize;
	CEdit m_edt_twex_MaxSize;
	CEdit m_edt_twex_Direction;
	CEdit m_edt_twex_PointNum;
	CEdit m_edt_twex_Points;
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonTwexStop();
	afx_msg void OnBnClickedButtonTwexStart();
};
