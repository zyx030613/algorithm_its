#ifndef _DOME_HD_PARAM2_PAGE_H_
#define _DOME_HD_PARAM2_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "./Events/VideoViewForDraw.h"
// CLS_DomeHDParam2 dialog

class CLS_DomeHDParam2 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeHDParam2)

public:
	CLS_DomeHDParam2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeHDParam2();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_HD_PARAM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	void UI_UpdateDialogText();
	void UpdateDomeHDPara(int _iTemplateID = -1, int _iType = -1);
	int SetDomeHDPara(int _iType, int _iAutoEnable, int _iParam1, int _iParam2, int _iParam3, int _iParam4);
	afx_msg void OnCbnSelchangeComboCurrentTemp();
	afx_msg void OnCbnSelchangeComboFocusMode();
	afx_msg void OnCbnSelchangeComboFocustype();
	afx_msg void OnCbnSelchangeComboMinFocusDis();
	afx_msg void OnCbnSelchangeComboSmartir();
	afx_msg void OnCbnSelchangeComboDaynight();
	afx_msg void OnCbnSelchangeComboSencitivity();
	afx_msg void OnCbnSelchangeComboInfrared();
	afx_msg void OnCbnSelchangeComboBacklight();
	afx_msg void OnCbnSelchangeComboRange();
	afx_msg void OnCbnSelchangeComboWideDynamic();
	afx_msg void OnCbnSelchangeComboSencitivityW();
	afx_msg void OnCbnSelchangeComboWhitebalance();
	afx_msg void OnNMCustomdrawSliderRed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderBlue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderGreen(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnParam2SetWhiteBalance();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboTempleID;
	CComboBox m_cmbFocusMode;
	CComboBox m_cboFocusType;
	CComboBox m_cboMinFocusDst;
	CComboBox m_cboSmartIR;
	CComboBox m_cboDayNight;
	CComboBox m_cboSencitivity;
	CComboBox m_cboInfrared;
	CComboBox m_cboBackLight;
	CComboBox m_cboBackLightRange;
	CComboBox m_cboWideDynamic;
	CComboBox m_cboSencitivityW;
	CComboBox m_cboWhiteBalance;
	CSliderCtrl m_slidRed;
	CSliderCtrl m_slidBlue;
	CButton m_btnSetWhiteBalance;
	CSliderCtrl m_slidGreen;
public:

	CStatic m_stcWideSensityDegree;
	CSliderCtrl m_sldWideSensityDegree;
	afx_msg void OnNMCustomdrawSldParam2WideSensityDegree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnParam2SetWideSensityDegree();
private:
	CEdit m_edtBackLightArea;
	CLS_VideoViewForDraw* m_pDlgVideoView;
public:
	afx_msg void OnBnClickedButtonBacklightDraw();
};

#endif
