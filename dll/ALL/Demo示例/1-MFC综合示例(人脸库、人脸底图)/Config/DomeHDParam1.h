#ifndef _DOME_HD_PARAM1_PAGE_H_
#define _DOME_HD_PARAM1_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_DomeHDParam1 dialog

class CLS_DomeHDParam1 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeHDParam1)

public:
	CLS_DomeHDParam1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeHDParam1();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_HD_PARAM1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UI_UpdateDialogText();
	void UpdateTempName(int _iIndex);
	void UpdateDomeHDPara(int _iTemplateID = -1, int _iType = -1);
	void UpdateApertureType();
	int SetDomeHDPara(int _iType, int _iAutoEnable, int _iParam1, int _iParam2, int _iParam3, int _iParam4);
	void SwitchExpoAutoText(int _iType=1);
	afx_msg void OnCbnSelchangeComboCurrentTemp();
	afx_msg void OnNMCustomdrawSliderSharpness(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderColorIncrease(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderColorPhase(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboGammaset();
	afx_msg void OnNMCustomdrawSliderGammaModify(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadioApertureType();
	afx_msg void OnBnClickedButtonSetTemplateName();
	afx_msg void OnNMCustomdrawSldRegulate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboExpomode();
	afx_msg void OnCbnSelchangeComboShutter();
	afx_msg void OnCbnSelchangeComboAperture();
	afx_msg void OnCbnSelchangeComboAutoAperture();
	afx_msg void OnCbnSelchangeComboGainAuto();
	afx_msg void OnNMCustomdrawSliderGainMax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderGain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderTargetBright(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderAutoSlowExpo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboExpoOffset();
	afx_msg void OnCbnSelchangeComboSensitive();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboTempleID;
	CEdit m_edtTempleName;
	CSliderCtrl m_slipSharpness;
	CSliderCtrl m_slidColorIncrease;
	CSliderCtrl m_slidColorPhase;
	CComboBox m_cboGammaSet;
	CSliderCtrl m_slidGammaModify;
	int m_iApertureTypePiris;
	CSliderCtrl m_sldRegulateAE;
	CComboBox m_cboExpoMode;
	CComboBox m_cboShutter;
	CComboBox m_cboAperture;
	CComboBox m_cboAutoAperture;
	CComboBox m_cboAutoGain;
	CSliderCtrl m_slidMaxGainLimit;
	CSliderCtrl m_slidGain;
	CSliderCtrl m_slidBright;
	CSliderCtrl m_sliderSensUp;
	CComboBox m_cbo_Expo_OffSet;
	CComboBox m_cboSensitive;
public:
	afx_msg void OnBnClickedButtonSharpnessSet();
	afx_msg void OnBnClickedButtonColorincreaseSet();
	afx_msg void OnBnClickedButtonColorphaseSet();
	afx_msg void OnBnClickedButtonGammamodifySet();
	afx_msg void OnBnClickedButtonAeSet();
	afx_msg void OnBnClickedButtonMaxgainlimitSet();
	afx_msg void OnBnClickedButtonGainSet();
	afx_msg void OnBnClickedButtonBrightSet();
	afx_msg void OnBnClickedButtonSensupSet();
};

#endif
