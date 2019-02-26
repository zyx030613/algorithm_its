#ifndef _HD_SCHEDULE_PAGE_H_
#define _HD_SCHEDULE_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_HDSchedule dialog

class CLS_HDSchedule : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_HDSchedule)

public:
	CLS_HDSchedule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_HDSchedule();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_HD_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateDialogText();
	void UpdateHDSchedulePara();
	afx_msg void OnBnClickedButtonScheduleSet();
	afx_msg void OnCbnSelchangeComboSchedule(UINT _uiID);	
	afx_msg void OnBnClickedChkSchedule(UINT _uiID);
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CDateTimeCtrl m_timeSchedStart[MAX_ITS_TIMERANGE];
	CDateTimeCtrl m_timeSchedStop[MAX_ITS_TIMERANGE];
	CComboBox m_cboSchedule[MAX_ITS_TIMERANGE];
	CButton m_chkSchedule[MAX_ITS_TIMERANGE];
};

#endif
