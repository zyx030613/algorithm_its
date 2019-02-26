#pragma once

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_VCAAdvanceParam dialog

class CLS_VCAAdvanceParam : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCAAdvanceParam)

public:
	CLS_VCAAdvanceParam(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAAdvanceParam();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VCA_ADV_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int		m_iLogonID;
	int		m_iChannelNo;
	int		m_iStreamNo;

	CButton m_chkVCAEnable;
	CEdit m_edtTarMinSize;
	CEdit m_edtTarMaxSize;
	CEdit m_edtTarMinWidth;
	CEdit m_edtTarMaxWidth;
	CEdit m_edtTarMinHeight;
	CEdit m_edtTarMaxHeight;
	CEdit m_edtTarMinWHRadio;
	CEdit m_edtTarMaxWHRadio;
	CEdit m_edtTarMinSpeed;
	CEdit m_edtTarMaxSpeed;
	CComboBox m_cboSensitivity;
	CComboBox m_cboEnable;
	CComboBox m_cboSceneNum;
	CSliderCtrl m_sldForegrdMinDiff;
	CSliderCtrl m_sldForegrdMaxDiff;
	CSliderCtrl m_sldBackgrdUpdateSpeed;
	CSliderCtrl m_sldTargetAffirmFrame;
	CSliderCtrl m_sldBlendBackgrdTime;
	CSliderCtrl m_sldTargetMergeSensi;

public:
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual BOOL OnInitDialog();

	void	UpdatePageUI();
	void	UpdateUIText();

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedCheckVcaEnable();
	afx_msg void OnBnClickedButtonAdvparamset();
	afx_msg void OnCbnSelchangeComboVcaEnable();
	afx_msg void OnNMCustomdrawSldAdvParaForegroundMinDiff(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldAdvParaForegroundMaxDiff(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldAdvParaBackgroundUpdateSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldAdvParaTargetAffirmFrameNum(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldAdvParaBlendBackgroundTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldAdvParaTargetMergeSensitivity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCboVcaSceneNum();
	afx_msg void OnCbnSelchangeComboSensitivity();
	afx_msg void OnNMCustomdrawSldTarMinsize(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CSliderCtrl m_sldMinSize;
	CSliderCtrl m_sldMaxSize;
	CSliderCtrl m_sldMinWidth;
	CSliderCtrl m_sldMaxWidth;
	CSliderCtrl m_sldMinHeight;
	CSliderCtrl m_sldMaxHeight;
	CSliderCtrl m_sldMinWHRadio;
	CSliderCtrl m_sldMaxWHRadio;
	CSliderCtrl m_sldMinSpeed;
	CSliderCtrl m_sldMaxSpeed;
public:
	afx_msg void OnNMCustomdrawSldTarMaxsize(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMinwidth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMaxwidth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMinheight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMaxheight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMinwhradio(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMaxwhradio(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMinspeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldTarMaxspeed(NMHDR *pNMHDR, LRESULT *pResult);
};
