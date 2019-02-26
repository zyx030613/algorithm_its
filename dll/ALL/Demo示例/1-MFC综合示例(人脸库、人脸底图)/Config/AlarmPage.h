#ifndef _ALARM_PAGE_H
#define _ALARM_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_AlarmPage dialog

class CLS_AlarmPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AlarmPage)

public:
	CLS_AlarmPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AlarmPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateServer();
	BOOL UI_UpdateThreshold();
	BOOL UI_UpdateAlarmTrigger();
	BOOL UI_UpdatePrecedeDelaySnap();
	BOOL UI_UpdateAlarmLinkInterval();

private:
	CEdit m_edtAlarmServerIp;
	CEdit m_edtAlarmServerPort;
	CButton m_btnAlarmServerIp;
	CEdit m_edtComServerIp;
	CEdit m_edtComServerPort;
	CButton m_btnComServer;
	CSliderCtrl m_sldMotionDetectThreshold;
	CButton m_btnMotionDetectThreshold;
	CStatic m_stxtProgress;
	CEdit m_edtCpu;
	CEdit m_edtMem;
	CButton m_btnThreshold;
	int m_iLogonID;
	int m_iChannelNo;
	CSliderCtrl m_sldAudioLoseSensitivity;
	// 报警联动暂停时间间隔 联动类型
	CComboBox m_cboAlarmLinkType;

public:
	afx_msg void OnBnClickedButtonAlarmserver();
	afx_msg void OnBnClickedButtonComserver();
	afx_msg void OnNMCustomdrawSliderMotiondetectthreshold(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonMotiondetectthreshold();
	afx_msg void OnBnClickedButtonThreshold();
	afx_msg void OnBnClickedButtonAudiolosesensitivity();
	afx_msg void OnNMCustomdrawSliderAudiolosesensitivity(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedBtnPrecedeDelaySnapSet();
	afx_msg void OnBnClickedBtnAlarmLinkIntervalSet();
};

#endif