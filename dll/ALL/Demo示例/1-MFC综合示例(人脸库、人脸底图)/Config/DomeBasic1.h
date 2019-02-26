#ifndef _DOME_BASIC1_PAGE_H_
#define _DOME_BASIC1_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_DomeBasic dialog

class CLS_DomeBasicInfo : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeBasicInfo)

public:
	CLS_DomeBasicInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeBasicInfo();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_BASIC1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateDialogText();
	void UI_UpdateDomeMenuInfo();
	void UI_UpdateDomePTZInfo();
	void UI_UpdateVideoFlipType();
	int SetDomeMenu(int _iType, int _iParam1 = 0, int _iParam2 = 0, int _iParam3 = 0, int _iParam4 = 0);
	int GetDomeMenu(TDomeParam& _tParam);
	int SetDomePTZ(int _iType, int _iEnable = 0, int _iParam1 = 0, int _iParam2 = 0);
	int GetDomePTZ(int _iType, int _iParam1, int _iParam2, DOMEPTZ *_pDomePtz);
	afx_msg void OnBnClickedCheckAutoFlip();
	afx_msg void OnBnClickedCheckPresetFreeze();
	afx_msg void OnBnClickedCheckDigistZoom();
	afx_msg void OnBnClickedChkPresetSnap();
	afx_msg void OnBnClickedChkScaleZoom();
	afx_msg void OnBnClickedChkScanVideo();
	afx_msg void OnBnClickedChkModelpathVideo();
	afx_msg void OnCbnSelchangeCboAngleSet();
	afx_msg void OnCbnSelchangeComboManualSpeedRating();
	afx_msg void OnCbnSelchangeComboZoomSpeedRating();
	afx_msg void OnCbnSelchangeCboHeatMode();
	afx_msg void OnCbnSelchangeComboTimeAutoStop();
	afx_msg void OnCbnSelchangeComboPresetSpeedRating();
	afx_msg void OnCbnSelchangeCboDadoPriority();
	afx_msg void OnNMCustomdrawSldPriDelayTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCbo485();
	afx_msg void OnCbnSelchangeCboNoElectricityMemory();
	afx_msg void OnCbnSelchangeCboVideoTurn();
	afx_msg void OnBnClickedCheckAwateAction();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CButton m_chkAutoFlip;
	CButton m_chkPresetFrozen;
	CButton m_chkDigistZoom;
	CButton m_chkPresetSnap;
	CButton m_chkScaleZoom;
	CButton m_chkScanVideo;
	CButton m_chkModelPathVideo;
	CComboBox m_cboAngleSet;
	CComboBox m_cboManualSpeed;
	CComboBox m_cboZoomSpeed;
	CComboBox m_cboHeatMode;
	CComboBox m_cboAutoStopTime;
	CComboBox m_cboPresetSpeed;
	CComboBox m_cboDadoPRI;
	CSliderCtrl m_sldPRIDelayTime;
	CComboBox m_cbo485;
	CComboBox m_cboNoElectricityMemory;
	CComboBox m_cboVideoTurn;
	CComboBox m_cboAwateAction;
	CButton m_chkAwateAction;
	CComboBox m_cboAwateTime;
	bool m_blIsInfrared;		//ÊÇ·ñÎªºìÍâÇò
public:
	afx_msg void OnBnClickedButtonSetWaiteAction();
	afx_msg void OnBnClickedBtnPriDelayTime();
	CButton m_btnPriDelayTime;
};

#endif
