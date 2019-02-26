#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "VCAEventBasePage.h"

// CLS_VCAEVENT_Running 对话框

class CLS_VCAEVENT_Running : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Running)

public:
	CLS_VCAEVENT_Running(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_Running();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_RUNNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UpdateUIText();
	void CleanText();
	void UpdatePageUI();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnRunSet();
	afx_msg void OnBnClickedBtnRunDraw();

private:
	CButton m_chkEventValid;
	CButton m_chkAlarmRule;
	CButton m_chkAlarmStat;
	CButton m_chkTargetBox;
	CEdit m_edtMaxDistance;
	CEdit m_edtMinDistance;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;
	CEdit m_edtAreaDraw;
public:
	CComboBox m_cboAlarmColor;
	CComboBox m_cboUnalarmColor;
	CComboBox m_cboRunTargetType;
	afx_msg void OnEnChangeEdtRunMaxDistance();
	afx_msg void OnEnChangeEdtRunMinDistance();
	afx_msg void OnEnChangeEdtRunMinSize();
	afx_msg void OnEnChangeEdtRunMaxSize();
};
