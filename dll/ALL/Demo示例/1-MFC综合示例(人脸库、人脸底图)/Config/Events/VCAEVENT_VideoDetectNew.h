#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_VCAEVENT_VideoDetectNew �Ի���

class CLS_VCAEVENT_VideoDetectNew : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_VideoDetectNew)

public:
	CLS_VCAEVENT_VideoDetectNew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_VCAEVENT_VideoDetectNew();

// �Ի�������
	enum { IDD = IDD_DLG_VCAEVENT_VIDEO_DETECT_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnVideoNewSet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();
private:
	CButton m_chkAlarmStat;
	CComboBox m_cboAlgoType;
	CButton m_chkUse;
	CSliderCtrl m_sldSensitivity;
	CSliderCtrl m_sldDetectTime;
public:
	afx_msg void OnNMCustomdrawSldSensitivity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldVideoNewDetectTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCboVideoNewAlgoType();
};
