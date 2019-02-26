#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

#define ITS_TRAFFIC_LIGHT_GAIN			4
#define ITS_NO_USE_SIGNAL_TOGHTER		0
#define ITS_SIGNAL_FREQUENCY_VALUE1		50
#define ITS_SIGNAL_FREQUENCY_VALUE2		100
#define MAX_SLIDER_VALUE				100
#define MIN_SLIDER_VALUE				0
#define MAX_ENHANCE_USE_TYPE			2
#define MAX_ENHANCE_TYPE				2
#define CHECK_ENABLE_TRUE				1

// Cls_ItsSignalOther 对话框

class Cls_ItsSignalOther : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsSignalOther)

public:
	Cls_ItsSignalOther(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cls_ItsSignalOther();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_SIGNAL_OTHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnBnClickedBtnSetTrafficRedLightGain();
private:
	int m_iLogonID;	
	int m_iChannelNo;
	CButton m_chkUseOrNot;
	CComboBox m_cboRoadID;
	CSliderCtrl m_sldExposureLevel;
	CSliderCtrl m_sldRedStatus;
	CSliderCtrl m_sldSwayRange;
	CSliderCtrl m_sldDeceteLevel;
	CSliderCtrl m_sldOverExpourseAdjust;
	CSliderCtrl m_sldHalation;
	CComboBox m_cboSmoothEnable;
	CButton m_chkEnhanceUseType[MAX_ENHANCE_USE_TYPE];
	CButton m_chkEnhanceType[MAX_ENHANCE_TYPE];

public:
	afx_msg void OnBnClickedCekStartUse();
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void UpdatePageData1();
	void UpdatePageData2();
	void UpdatePageData3();
	void UI_UpdateDialog();
	void OnLanguageChanged(int _iChangLanguage);
	void UpdateCheck();
	afx_msg void OnBnClickedBtnSetSignalFrequency();
	CButton m_chkSignalTonightUse;
	CComboBox m_cboValue;
	afx_msg void OnBnClickedChkUse();
	afx_msg void OnCbnSelchangeCboRoadid();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
