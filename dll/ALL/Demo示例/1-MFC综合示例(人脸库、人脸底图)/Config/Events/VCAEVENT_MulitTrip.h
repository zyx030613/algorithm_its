#pragma once
#include "VCAEventBasePage.h"
#include "afxwin.h"

// CLS_VCAEVENT_MulitTrip �Ի���

class CLS_VCAEVENT_MulitTrip : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_MulitTrip)

public:
	CLS_VCAEVENT_MulitTrip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_VCAEVENT_MulitTrip();

// �Ի�������
	enum { IDD = IDD_DLG_VCAEVENT_MULIT_TRIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayAlarmNum;
	CButton m_chkIsDoubleDir;
	CComboBox m_cboUnAlarmColor;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboTargetType;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;
	CEdit m_edtMinDbTime;
	CEdit m_edtMaxDbType;
	CEdit m_edtTripwire1PointNum;
	CEdit m_edtTripwire2PointNum;
	CEdit m_edtTripwire1Points;
	CEdit m_edtTripwire2Points;
public:
	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnMulittripSet();
	afx_msg void OnBnClickedBtnMulittripDraw1();
	afx_msg void OnBnClickedBtnMulittripDraw2();
	afx_msg void OnBnClickedBtnMulittripStop();
	afx_msg void OnBnClickedBtnMulittripStart();
};
