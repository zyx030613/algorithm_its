#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_VCAEVENT_PersonStat 对话框

class CLS_VCAEVENT_PersonStat : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_PersonStat)

public:
	CLS_VCAEVENT_PersonStat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_PersonStat();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_PERSON_STAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();
	void CleanText();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnPerStatSet();
	afx_msg void OnBnClickedStcPerBtnPolygonAreaDraw();
	afx_msg void OnBnClickedBtnPerStatLineAreaDraw();
	afx_msg void OnEnChangeEdtPerStatSensitivity();
	afx_msg void OnEnChangeEdtPerStatAimMinSize();
	afx_msg void OnEnChangeEdtPerStatAimMaxSize();
private:
	int m_iLineAreaPointNum;
	CButton m_chkEventValid;
	CButton m_chkAlarmRule;
	CButton m_chkAlarmStat;
	CButton m_chkTargetBox;
	CComboBox m_cboDetectStyle;
	CComboBox m_cboDetectMode;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboUnalarmColor;
	CComboBox m_cboPolygonPointNum;
	CEdit m_edtPolygonArea;
	CEdit m_edtLineArea;
	CEdit m_edtSensitivity;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;
public:
	afx_msg void OnCbnSelchangeCboPerStatDetectStyle();
};
