#pragma once
#include "VCAEventBasePage.h"
#include "afxwin.h"

// CLS_VCAEVENT_AudioDiagnose �Ի���
#define		MAX_

class CLS_VCAEVENT_AudioDiagnose : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_AudioDiagnose)

public:
	CLS_VCAEVENT_AudioDiagnose(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_VCAEVENT_AudioDiagnose();

// �Ի�������
	enum { IDD = IDD_DLG_VCAEVENT_AUDIODIAGNOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboUnAlarmColor;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboEnableType;
	CComboBox m_cboLevel;
	CButton m_chkDisplayRule;
	CButton m_chkEnableType;
public:
	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnVcaAudioSet();
	CButton m_chkType[VCA_AUDIO_MAX];
	afx_msg void OnBnClickedChkVcaType();
};
