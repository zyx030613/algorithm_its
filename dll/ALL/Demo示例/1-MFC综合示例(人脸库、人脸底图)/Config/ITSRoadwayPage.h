#ifndef _ITSROADWAY_PAGE_H
#define _ITSROADWAY_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_ITSRoadwayPage dialog

class CLS_ITSRoadwayPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSRoadwayPage)

public:
	CLS_ITSRoadwayPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSRoadwayPage();

// Dialog Data
	enum { IDD = IDD_DLG_ITS_ROADWAY_COMMON1  };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateRoadway();
	void UI_UpdateVirtualLoop();
	void UI_UpdateLoopmode();

private:
	CComboBox m_cboRoadwayNo;
	CButton m_chkRoadwayNo;
	CButton m_btnRoadway;
	CEdit m_edtRoadwayName;
	CEdit m_edtRoadwayDirection;
	CEdit m_edtComportNo;
	CEdit m_edtSpeedLoopNo;
	CEdit m_edtCaptureLoopNo;
	CButton m_btnLoop;
	CEdit m_edtLoopMaxTime;
	CEdit m_edtLoopMinTime;
	CEdit m_edtLoopDelayTime;
	CButton m_btnTime;
	CEdit m_edtLoopDistance;
	CEdit m_edtSpeedLimit;
	CEdit m_edtSpeedModify;
	CButton m_btnSpeed;
	CEdit m_edtRecRange;
	CEdit m_edtSence;
	CButton m_btnRecRange;
	CComboBox m_cboLoopID;
	CComboBox m_cboDayNight;
	CButton m_btnVirtualLoop;
	int m_iLogonID;
	int m_iChannelNo;
	CToolTipCtrl m_tipCtrl;
	CButton m_btnLoopMode;
	CComboBox m_cboLoopMode;
public:
	afx_msg void OnCbnSelchangeComboRoadwayno();
	afx_msg void OnBnClickedButtonRoadway();
	afx_msg void OnBnClickedButtonLoop();
	afx_msg void OnBnClickedButtonTime();
	afx_msg void OnBnClickedButtonSpeed();
	afx_msg void OnBnClickedButtonRecrange();
	afx_msg void OnCbnSelchangeComboLoopid();
	afx_msg void OnCbnSelchangeComboDaynight();
	afx_msg void OnBnClickedButtonVirtualloop();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEditLoopdistance();
	afx_msg void OnStnClickedStaticLoopmode();
	afx_msg void OnStnClickedStaticRoadwayname();
	afx_msg void OnBnClickedButtonLoopmode();
};

#endif