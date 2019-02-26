#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_VCAEVENT_OnDutyDetect 对话框

class CLS_VCAEVENT_OnDutyDetect : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_OnDutyDetect)

public:
	CLS_VCAEVENT_OnDutyDetect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_OnDutyDetect();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_ONDUTY_DETECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UpdateUIText();
	void CleanText();
	void UpdatePageUI();

	int DrawArea(int _iAreaNum);

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnOndutySet();
	afx_msg void OnBnClickedBtnOndutyDrawArea1();
	afx_msg void OnBnClickedBtnOndutyDrawArea2();
	afx_msg void OnBnClickedBtnOndutyDrawArea3();
	afx_msg void OnBnClickedBtnOndutyDrawArea4();
private:
	CButton m_chkEventValid;
	CButton m_chkAlarmRule;
	CButton m_chkAlarmStat;
	CButton m_chkTargetBox;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboUnalarmColor;
	CEdit m_edtMainArea1;
	CEdit m_edtMainArea2;
	CEdit m_edtMainArea3;
	CEdit m_edtMainArea4;
	CEdit m_edtLeaveAlarmTime;
	CEdit m_edtReturnUnalarmTime;
	CEdit m_edtAreaNum;
	CEdit m_edtSensitivity;
	CEdit m_edtMaxSize;
	CEdit m_edtMinSize;
	CEdit m_edtOndutyNum;
	CSpinButtonCtrl m_spinLeaveAlarmTime;
	CSpinButtonCtrl m_spinReturnUnalarmTime;
	CSpinButtonCtrl m_spinAreaNum;
public:
	afx_msg void OnEnChangeEdtOndutyNum();
	afx_msg void OnEnChangeEdtOndutyMinSize();
	afx_msg void OnEnChangeEdtOndutyMaxSize();
	afx_msg void OnEnChangeEdtOndutyAreaNum();
	afx_msg void OnEnChangeEdtOndutySensitivity();
	int ChangeToTwoPoints(char* _pcPointBufIn, CString& _cstrPointBufOut);
};
