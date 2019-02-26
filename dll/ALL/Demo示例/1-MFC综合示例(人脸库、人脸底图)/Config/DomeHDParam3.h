#ifndef _DOME_HD_PARAM3_PAGE_H_
#define _DOME_HD_PARAM3_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_DomeHDParam3 dialog

class CLS_DomeHDParam3 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeHDParam3)

public:
	CLS_DomeHDParam3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeHDParam3();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_HD_PARAM3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UI_UpdateDialogText();
	void UpdateDomeHDPara(int _iTemplateID = -1, int _iType = -1);
	int SetDomeHDPara(int _iType, int _iAutoEnable, int _iParam1, int _iParam2, int _iParam3, int _iParam4);
	afx_msg void OnCbnSelchangeCboVideoStyle();
	afx_msg void OnCbnSelchangeComboInoutdoorMode();
	afx_msg void OnCbnSelchangeCboThroughMist();
	afx_msg void OnNMCustomdrawSliderMistStrength(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCboStronglight();
	afx_msg void OnNMCustomdrawSliderBigLight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboDnr();
	afx_msg void OnNMCustomdrawSliderNoiseLevel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderTimeDomainNoise(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSpaceDomainNoise(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCboAutoContrast();
	afx_msg void OnCbnSelchangeComboSencitivityAutoContrast();
	afx_msg void OnCbnSelchangeCboLightless();
	afx_msg void OnCbnSelchangeCboNightStrenth();
	afx_msg void OnCbnSelchangeCboVideoFrost();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboTempleID;
	CComboBox m_cboImageStyle;
	CComboBox m_cboInOutDoorMode;
	CComboBox m_cboThroughMist;
	CSliderCtrl m_slidMistStrength;
	CComboBox m_cboStrongLight;
	CSliderCtrl m_slidBigLight;
	CComboBox m_cboDNR;
	CSliderCtrl m_slidTimeDomainNoise;
	CSliderCtrl m_slidSpaceDomainNoise;
	CSliderCtrl m_slidNoiseLevel;
	CComboBox m_cboAutoContrast;
	CComboBox m_cboSencitivityAutoContrast;
	CComboBox m_cboNightStrength;
	CComboBox m_cboLightness;
	CComboBox m_cboVidoeFrost;
	CButton m_btnSetLightInhibition;
public:
	afx_msg void OnBnClickedBtnParam3SetLightInhibition();
	CButton m_btnSetThroughMist;
	afx_msg void OnBnClickedBtnParam3SetThroughMist();
	CButton m_btnParam3SetDnr;
	afx_msg void OnBnClickedBtnParam3SetDnr();
	afx_msg void OnCbnSelchangeComboCurrentTemp();
};

#endif
