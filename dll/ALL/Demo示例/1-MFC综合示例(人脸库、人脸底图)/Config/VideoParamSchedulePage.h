#ifndef _VIDEO_PARAM_SCHEDULE_PAGE_H_
#define _VIDEO_PARAM_SCHEDULE_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"

// CLS_VdieoParamSchedulePage dialog

class CLS_VideoParamSchedulePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VideoParamSchedulePage)

public:
	CLS_VideoParamSchedulePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VideoParamSchedulePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VIDEO_PARAM_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnCbnSelchangeComboSchedule();
	afx_msg void OnBnClickedButtonSchedule();

private:
	void UI_UpdateDialog();
	void UI_UpdateSchedule();
	void UpdateSchedule();
	BOOL SaveSchedule();

private:
	int m_iLogonID;
	int m_iChannelNo;
	STR_VideoParam  m_tSchedule[MAX_TIMESEGMENT]; 
	CComboBox m_cboSchedule;
	CComboBox m_cboColorToGray;
	CDateTimeCtrl m_tmStart;
	CDateTimeCtrl m_tmStop;
	CSliderCtrl m_sldBrightness;
	CSliderCtrl m_sldContrast;
	CSliderCtrl m_sldSaturation;
	CSliderCtrl m_sldHue;
	
public:
	afx_msg void OnNMCustomdrawSliderBrightness(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderContrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSaturation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderHue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonScheduleSave();
};

#endif