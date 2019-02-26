#pragma once
#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"


// CLS_VCAEVENT_SluiceGate dialog

class CLS_VCAEVENT_SluiceGate : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_SluiceGate)

public:
	CLS_VCAEVENT_SluiceGate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_SluiceGate();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_SLUICEGATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void UI_UpdateDialog();
	void UI_UpdateSdkParam();
	void OnLanguageChanged();
	afx_msg void OnBnClickedBtnDrawSluiceGate1();
	afx_msg void OnBnClickedBtnDrawSluiceGate2();
	afx_msg void OnBnClickedBtnDrawSluiceGate3();
	afx_msg void OnBnClickedBtnDrawSluiceGate4();
	afx_msg void OnBnClickedBtnDrawSluiceGate5();
	void DrawOnVideo(CEdit& _edtSluiceGate, int* _piPointCount);
	afx_msg void OnBnClickedBtnSluicegateSet();
	afx_msg void OnEnChangeEdtSluicegateCount();
private:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayAlarmCount;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboAreaColor;
	CComboBox m_cboSluiceGateType;
	CEdit m_edtSluiceGateCount;
	CEdit m_edtSluiceGate1;
	CEdit m_edtSluiceGate2;
	CEdit m_edtSluiceGate3;
	CEdit m_edtSluiceGate4;
	CEdit m_edtSluiceGate5;
	CSpinButtonCtrl m_spinSluiceGateCount;	
	int		m_iPointCount[MAX_VCA_SLUICEGATE_COUNT];
	CButton m_chkSluiceGate1;
	CButton m_chkSluiceGate2;
	CButton m_chkSluiceGate3;
	CButton m_chkSluiceGate4;
	CButton m_chkSluiceGate5;
};
