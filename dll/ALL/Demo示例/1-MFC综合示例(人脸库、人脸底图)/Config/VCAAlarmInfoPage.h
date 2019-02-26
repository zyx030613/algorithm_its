#pragma once
#include "../BasePage.h"
#include "afxcmn.h"
#include "afxwin.h"

// CLS_VCAAlarmInfoPage dialog

class CLS_VCAAlarmInfoPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCAAlarmInfoPage)

public:
	CLS_VCAAlarmInfoPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAAlarmInfoPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VCA_ALARM_INFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	void OnLanguageChanged(int _iLanguage);
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnAlarmNotify(int _iLogonID, int _iChannelNo, int _iAlarmState,int _iAlarmType,int _iUserData);

private:
	int m_iLogonID;
	int m_iChannelNo;

	void UI_UpdateVcaAlarmStatistic();
	void UI_UpdateVcaAlarmInfo(int _iLogonID, int _iAlarmIndex);
	void UI_UpdateText();
	void UI_Clear();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClearRecord();
	afx_msg void OnCbnSelchangeComboVcaAlarmRule();
	afx_msg void OnBnClickedButtonVcaAlarmStatisticClear();
	afx_msg void OnCbnSelchangeCboVcaAlarminfoSceneNum();
	afx_msg void OnCbnSelchangeComboVcaAlarmEvent();

private:
	CComboBox m_cboSceneID;
	CEdit m_edtAlarmTimes;
	CButton m_chkValid;
	CListCtrl m_lstctAlarmInfo;
	CComboBox m_cboRuleID;
	CComboBox m_cboEventID;

};
