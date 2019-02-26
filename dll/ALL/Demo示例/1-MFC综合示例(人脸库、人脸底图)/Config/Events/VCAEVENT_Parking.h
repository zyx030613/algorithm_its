#pragma once

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Hover.h"
#include "afxwin.h"
// CLS_VCAEVENT_Parking 对话框

class CLS_VCAEVENT_Parking : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Parking)

public:
	CLS_VCAEVENT_Parking(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_Parking();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_PARKING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UpdateUIText();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnParkSet();
	afx_msg void OnBnClickedBtnParkDraw();
	void UpdatePageUI();
	void CleanText();
private:
	CButton m_chkEventValid;
	CButton m_chkAlarmRule;
	CButton m_chkAlarmStat;
	CButton m_chkTargetBox;
	CEdit m_edtAlarmTime;
	CEdit m_edtSpeedShrehold;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;
	CEdit m_edtPointArea;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboUnalarmColor;

public:
	afx_msg void OnEnChangeEdtParkAlarmTime();
	afx_msg void OnEnChangeEdtParkMinSize();
	afx_msg void OnEnChangeEdtParkMaxSize();
	afx_msg void OnEnChangeEdtParkSpeedShrehold();
};
