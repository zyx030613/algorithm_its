#ifndef _VIDEO_DOMESCHEDULE_PAGE_H_
#define _VIDEO_DOMESCHEDULE_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_DomeSchedule dialog

class CLS_DomeSchedule : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeSchedule)

public:
	CLS_DomeSchedule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeSchedule();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UpdatePageUI();
	void UI_UpdateDialog();
	void UI_Clear();
	afx_msg void OnBnClickedButtonDomeScheduleSet();
	afx_msg void OnCbnSelchangeComboWeek();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboWeek;
	CButton m_chkEnbale[MAX_SCHEDULE];
	CDateTimeCtrl m_dtBeginTime[MAX_SCHEDULE];
	CDateTimeCtrl m_dtEndTime[MAX_SCHEDULE];
	CComboBox m_cboSegType[MAX_SCHEDULE];
	CEdit m_edtSegValue[MAX_SCHEDULE];
	
};

#endif
