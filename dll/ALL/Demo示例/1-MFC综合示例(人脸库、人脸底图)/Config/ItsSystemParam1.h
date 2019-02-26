#ifndef _ECOP_OTHER_PAGE_H
#define _ECOP_OTHER_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

#define HOUR_LIMIT			23
#define MINUTE_LIMIT		59
#define SWITCH_TIME_MIN		5
#define SWITCH_TIME_MAX		1440

// CLS_ECOPOtherPage dialog

class CLS_ItsSystemParam1 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsSystemParam1)

public:
	CLS_ItsSystemParam1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ItsSystemParam1();

// Dialog Data
	enum { IDD = IDD_DLG_ITS_SYSTEMPARAM1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateOther();
	BOOL UI_UpdateDayAndNight();
	void UI_UpdateDetectmode();
	void UI_UpdateSwitchDelay();
	//BOOL UI_UpdateSn();

private:
	CComboBox m_cboRoadwayID;
	CButton m_chkEnable;
	CComboBox m_cboSnType;
	CEdit m_edtSn;
	CEdit m_edtLocalRet;
	CButton m_btnSn;
	CEdit m_edtSystemType;
	CButton m_btnSystem;
	int m_iLogonID;
	int m_iChannel;

public:
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedCheckWatermarkEnable();
	afx_msg void OnBnClickedButtonSn();
	afx_msg void OnBnClickedButtonSystem();
	/*afx_msg void OnCbnSelchangeComboSnType();*/
	afx_msg void OnBnClickedButtonDetectmode();
	afx_msg void OnBnClickedButtonSwitchDelay();
	CComboBox m_cboDetectMode;
	CButton m_btnDetectMode;
	CEdit m_edtSwitchTime;
	CEdit m_edtDelayTime;
	CButton m_btnSwitchDelay;
	CStatic m_gpTestMode;
	CStatic m_gpTimeSet;
	CStatic m_gpDayNight;
	CStatic m_stcTimeSegment;
	CEdit m_edtTimeSegment;
	CButton m_btnSetDayNight;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnStnClickedStcTimesegment();
	CStatic m_stcDayStart;
	CEdit m_edtDayStart;
	CStatic m_stcNightStart;
	CEdit m_edtNightStart;
	CButton m_btnSetDayNightTime;
	CStatic m_stcSwitchPart;
	CEdit m_edtSwitchPart;
	CButton m_btn_SetTimePart;
	afx_msg void OnBnClickedBtnSetSwitchInterval();
	afx_msg void OnBnClickedBtnSetDayAndNight();
	CEdit m_edtDayStartMin;
	CEdit m_edtNightStartMin;
	CStatic m_stcDayPoint;
	CStatic m_stcNightPoint;
	CButton m_btnSetTimePart;
	afx_msg void OnCbnSelchangeComboSnType();
};

#endif