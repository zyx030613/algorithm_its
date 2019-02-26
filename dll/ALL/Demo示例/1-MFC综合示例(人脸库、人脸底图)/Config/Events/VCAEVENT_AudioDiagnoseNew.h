#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_VCAEVENT_AudioDiagnoseNew �Ի���

class CLS_VCAEVENT_AudioDiagnoseNew : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_AudioDiagnoseNew)

public:
	CLS_VCAEVENT_AudioDiagnoseNew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_VCAEVENT_AudioDiagnoseNew();

// �Ի�������
	enum { IDD = IDD_DLG_VCAEVENT_AUDIO_DIAGNOSE_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
//	virtual void PreInitDialog();
public:	
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnAudioNewSet();
private:
	CButton m_chkAlarmStat;
	CComboBox m_cboAlgoType;
	CButton m_chkUse;
	CSliderCtrl m_sldSensitivity;
public:
	afx_msg void OnNMCustomdrawSldAudioNewSensitivity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCboAudioNewAlgoType();
};
