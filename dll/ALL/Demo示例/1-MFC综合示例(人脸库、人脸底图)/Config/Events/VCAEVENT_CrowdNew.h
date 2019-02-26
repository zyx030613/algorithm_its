#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_VCAEVENT_CrowdNew �Ի���

class CLS_VCAEVENT_CrowdNew : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_CrowdNew)

public:
	CLS_VCAEVENT_CrowdNew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_VCAEVENT_CrowdNew();

// �Ի�������
	enum { IDD = IDD_DLG_VCAEVENT_CROWD_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();
	afx_msg void OnBnClickedBtnCrowdNewSet();
	afx_msg void OnBnClickedBtnCrowdNewDraw();
	afx_msg void OnEnChangeEdtCrowdNewSensitibity();
private:
	CButton m_chkEventValid;
	CButton m_chkAlarmRule;
	CButton m_chkAlarmStat;
	CButton m_chkTargetBox;
	CEdit m_edtSustainTime;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboUnalarmColor;
	CEdit m_edtArea;
	CEdit m_edtSensitivity;
};
