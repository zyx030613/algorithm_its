#ifndef _DNVR_ALM_SCH_PAGE_H
#define _DNVR_ALM_SCH_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_DNVRAlmSchPage dialog

class CLS_DNVRAlmSchPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DNVRAlmSchPage)

public:
	CLS_DNVRAlmSchPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DNVRAlmSchPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DNVR_ALMSCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateType();
	void CheckSchedtime(int _iIndex);

private:
	CComboBox m_cboType;
	CComboBox m_cboInPort;
	CButton m_chkInPort;
	CComboBox m_cboWeekday;
	CDateTimeCtrl m_dtcStartTime[4];
	CDateTimeCtrl m_dtcEndTime[4];
	CButton m_chkTime[4];
	CButton m_btnAllDay;
	CButton m_btnInPort;
	CComboBox m_cboOutPort;
	CButton m_chkOutPort;
	CComboBox m_cboOutWeekday;
	CDateTimeCtrl m_dtcOutStartTime[4];
	CDateTimeCtrl m_dtcOutEndTime[4];
	CButton m_chkOutTime[4];
	CButton m_btnOutAllDay;
	CButton m_btnOutPort;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iChangeLanguage;

public:
	afx_msg void OnBnClickedCheckInport();
	afx_msg void OnCbnSelchangeComboWeekday();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnBnClickedCheckTime1();
	afx_msg void OnBnClickedCheckTime2();
	afx_msg void OnBnClickedCheckTime3();
	afx_msg void OnBnClickedCheckTime4();
	afx_msg void OnBnClickedButtonAllday();
	afx_msg void OnBnClickedButtonInport();
	afx_msg void OnCbnSelchangeComboOutport();
	afx_msg void OnCbnSelchangeComboOutWeekday();
	afx_msg void OnBnClickedCheckOutport();
	afx_msg void OnBnClickedCheckOutTime1();
	afx_msg void OnBnClickedCheckOutTime2();
	afx_msg void OnBnClickedCheckOutTime3();
	afx_msg void OnBnClickedCheckOutTime4();
	afx_msg void OnBnClickedButtonOutAllday();
	afx_msg void OnBnClickedButtonOutport();
	afx_msg void OnCbnSelchangeComboInport();
};

#endif
