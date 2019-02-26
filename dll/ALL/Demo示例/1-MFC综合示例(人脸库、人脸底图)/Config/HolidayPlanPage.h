#ifndef _HOLIDAYPLAN_PAGE_H
#define _HOLIDAYPLAN_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_HolidayPlanPage dialog

class CLS_HolidayPlanPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_HolidayPlanPage)

public:
	CLS_HolidayPlanPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_HolidayPlanPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_STORAGE_HOLIDAY_PLAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateSchedule();
	BOOL UI_UpdateMode();
	void UI_UpdateWindowMode( BOOL _bShow);

private:
	int m_iLogonID;
	CComboBox m_cboPlanID;
	CComboBox m_cboMode;
	CComboBox m_cboStartMonth;
	CComboBox m_cboStartWeek;
	CComboBox m_cboStartDayOfWeek;
	CComboBox m_cboEndMonth;
	CComboBox m_cboEndWeek;
	CComboBox m_cboEndDayOfWeek;
	CDateTimeCtrl m_timeStart;
	CDateTimeCtrl m_timeEnd;

public:
	afx_msg void OnCbnSelchangeComboPlanId();
	afx_msg void OnCbnSelchangeComboMode();
	afx_msg void OnBnClickedButtonHolidayPlanSchedule();
	afx_msg void OnDtnDatetimechangeDatetimepickerStartTime(NMHDR *pNMHDR, LRESULT *pResult);
};
#endif