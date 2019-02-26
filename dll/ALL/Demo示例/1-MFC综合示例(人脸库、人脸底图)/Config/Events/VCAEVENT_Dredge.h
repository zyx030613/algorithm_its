#pragma once
#include "afxwin.h"
#include "VCAEventBasePage.h"

// CLS_VCAEVENT_Dredge 对话框

class CLS_VCAEVENT_Dredge : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Dredge)

public:
	CLS_VCAEVENT_Dredge(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_Dredge();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_DREDGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayAlarmNum;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboAreaColor;
	CComboBox m_cboRecgMode;

private:
	void AutoShowParam();
	void CheckValueLimits();
	void SetZoomControl();

public:
	void UI_UpdateDialog();
	void UI_UpdatePage();
	void UI_UpdateZoomControl();
	void OnLanguageChanged();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnDredgeSet();
	afx_msg void OnBnClickedBtnDredgePointsDraw();
	afx_msg void OnBnClickedBtnDredgeStop();
	afx_msg void OnBnClickedBtnDredgeStart();
	afx_msg void OnBnClickedButtonDredgeAuto();
	afx_msg void OnEnChangeEdtZoomControl();

};
