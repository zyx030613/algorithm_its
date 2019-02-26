#ifndef _ITSTIMERANGE_PAGE_H
#define _ITSTIMERANGE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_ITSTimeRangePage dialog

class CLS_ITSTimeRangePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSTimeRangePage)

public:
	CLS_ITSTimeRangePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSTimeRangePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_TIMERANGE };

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
	void UI_UpdateLoopmode();
	void UI_UpdateDevicetype();
	void UI_UpdateSwitchDelay();

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
	CButton m_chkFlashLamp;
	CButton m_btnFlashLamp;
	CEdit m_edtBlockX;
	CEdit m_edtBlockY;
	CButton m_btnBlock;
	CComboBox m_cboDetectMode;
	CButton m_btnDetectMode;
	CComboBox m_cboLoopMode;
	CButton m_btnLoopMode;
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
	afx_msg void OnBnClickedCheckFlashlamp();
	afx_msg void OnCbnSelchangeComboBlock();
	afx_msg void OnBnClickedButtonBlock();
	afx_msg void OnBnClickedButtonDetectmode();
	afx_msg void OnBnClickedButtonLoopmode();
	afx_msg void OnBnClickedButtonDevicetype();
	afx_msg void OnBnClickedButtonSwitchDelay();
	afx_msg void OnCbnSelchangeComboCameraparam();
	afx_msg void OnBnClickedButtonCamera();
};

#endif