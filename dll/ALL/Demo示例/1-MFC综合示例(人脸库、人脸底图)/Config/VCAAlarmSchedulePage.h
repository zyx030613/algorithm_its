#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"
#define MAX_HOUR	24
#define MAX_MINUTE	60
// CLS_VCAAlarmSchedulePage dialog

class CLS_VCAAlarmSchedulePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCAAlarmSchedulePage)

public:
	CLS_VCAAlarmSchedulePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAAlarmSchedulePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VCA_ALARM_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	int m_iChannelNo;
public:
	void OnLanguageChanged(int _iLanguage);
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void UI_UpdateAlarmSchedule();
	void UI_UpdateAlarmEnable();
	void UI_UpdateText();
	void SetAlarmSchedule(int iWeek);
	void UI_Clear();
public:
	CComboBox m_CboSceneId;
	CComboBox m_cboRuleID;
	CComboBox m_cboEvent;
	CComboBox m_cboEnbale;
	CComboBox m_cboWeek;
	CDateTimeCtrl m_dtBeginTime[4];
	CDateTimeCtrl m_dtEndTime[4];
	BOOL m_chkEnbale[4];
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAlarmScheduleSet();
	afx_msg void OnCbnSelchangeComboAlarmScheduleRule();
	afx_msg void OnBnClickedButtonAlarmScheduleAllday();
	afx_msg void OnCbnSelchangeComboAlarmScheduleWeek();
	afx_msg void OnBnClickedButtonAlarmScheduleEnable();
	
	afx_msg void OnCbnSelchangeComboScheduleScene();
	afx_msg void OnCbnSelchangeComboSddeviceno();
	afx_msg void OnCbnSelchangeComboAlarmScheduleEnable();
};
