#ifndef _ITSTIMERANGE_PAGE_H
#define _ITSTIMERANGE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#define ITS_MAX_HOUR 24
#define ITS_MAX_MINUTE 59
#define HAND_DO			0
#define AUTO_DO			1
#define EXPERT_DO		2
#define REDUCTION_3D	3
#define PARAM_LIMIT0	0
#define PARAM_LIMIT1	1
#define PARAM_LIMIT2	2
#define PARAM_LIMIT3	3
#define PARAM_LIMIT5	5
#define PARAM_LIMIT6	6
#define PARAM_LIMIT17	17
#define PARAM_LIMIT26	26
#define PARAM_LIMIT47	47
#define PARAM_LIMIT64	64
#define PARAM_LIMIT100	100
#define PARAM_LIMIT115	115
#define PARAM_LIMIT200	200
#define PARAM_LIMIT255	255
#define PARAM_LIMIT8192	8192



// CLS_ITSTimeRangePage dialog

class Cls_ItsPictureCommon1 : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsPictureCommon1)

public:
	Cls_ItsPictureCommon1(CWnd* pParent = NULL);   // standard constructor
	virtual ~Cls_ItsPictureCommon1();

// Dialog Data
	enum { IDD = IDD_DLG_ITS_PICTURE_COMMON1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
		
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateTimeAgcFlash();
	BOOL UI_UpdateTimeRangeParam();
	BOOL UI_UpdateBlock();
	BOOL UI_UpdateGPEGQuality();
	void UI_UpdateDetectmode();
	void UI_UpdateDevicetype();
	void UI_UpdateSwitchDelay();
	void UI_UpdateAutoSetDialog();
	void UI_UpdatePageEnable();

private:
	CComboBox m_cboTimeRangeIndex;
	CButton m_chkTimeRangeIndex;
	CEdit m_edtTimeRange;
	CButton m_btnTimeRange;
	CComboBox m_cboType;
	CComboBox m_cboAutoEnable;
	CEdit m_edtParam[4];
	CButton m_btnParam;
	CButton m_chkBit[5];
	CComboBox m_cboBlock;
	CButton m_btnFlashLamp;
	CEdit m_edtBlockX;
	CEdit m_edtBlockY;
	CButton m_btnBlock;
	CComboBox m_cboDetectMode;
	CButton m_btnDetectMode;
	CComboBox m_cboDeviceType;
	CButton m_chkDeviceType;
	CEdit m_edtSwitchTime;
	CEdit m_edtDelayTime;
	CButton m_btnSwitchDelay;
	CComboBox m_cboCameraParam;
	CEdit m_edtValue;
	CButton m_btnCamera;
	int m_iLogonID;
	int m_iChannelNo;

public:
	afx_msg void OnCbnSelchangeComboTimerangeindex();
	afx_msg void OnBnClickedButtonTimerange();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnBnClickedButtonParam();
	afx_msg void OnBnClickedButtonAgcblock();
	afx_msg void OnCbnSelchangeComboBlock();
	afx_msg void OnBnClickedButtonBlock();
	afx_msg void OnBnClickedButtonDetectmode();
	afx_msg void OnBnClickedButtonDevicetype();
	afx_msg void OnBnClickedButtonSwitchDelay();
	afx_msg void OnCbnSelchangeComboCameraparam();
	afx_msg void OnBnClickedButtonCamera();
	afx_msg void OnCbnSelchangeComboDetectmode();
	afx_msg void OnCbnSelchangeComboAutoenable();
	afx_msg void OnEnChangeEditTimerangeParam1();
	CButton m_btnSetArea;
	afx_msg void OnBnClickedCheckTimerangeindex();
};

#endif