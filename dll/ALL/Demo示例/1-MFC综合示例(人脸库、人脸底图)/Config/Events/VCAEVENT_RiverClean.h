#pragma once
#include "VCAEventBasePage.h"
#include "afxwin.h"

class CLS_VCAEVENT_RiverClean : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_RiverClean)

public:
	CLS_VCAEVENT_RiverClean(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_RiverClean();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_RIVER_CLEAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayAlarmNum;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboAreaColor;
	CComboBox m_cboRecgMode;
	int m_iRecgMode;
	
public:
	void UI_UpdateDialog();
	void UI_UpdatePage();
	void OnLanguageChanged();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnRiverSet();	
	afx_msg void OnBnClickedBtnRiverPointsDraw();	
	afx_msg void OnCbnSelchangeCboRiverAlarmColor();
	afx_msg void OnBnClickedBtnRiverStop();
	afx_msg void OnBnClickedBtnRiverStart();
	afx_msg void OnCbnSelchangeCboRiverRecognizeMode();
private:
	void AutoShowParam();
	void CheckValueLimits();
public:
	afx_msg void OnBnClickedButtonReset();
};
