#ifndef _HD_COOPER_DOME_H_
#define _HD_COOPER_DOME_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLSCooperDome dialog
typedef enum __tagEDomePTZTypeSel
{
	PRESET_FREEZE_UP_SEL = 0,
	AUTO_FLIP_SEL,
	PRESET_SPEED_LEVE_SEL,
	MANUL_SEPPD_LEVEL_SEL,
	WAIT_ACT_SEL,
	INFRARED_MODE_SEL,
	MAX_DOME_PTZ_TYPE
}EDomePTZType;

class CLS_DomeInfrared : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeInfrared)

public:
	CLS_DomeInfrared(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeInfrared();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_COOPER_DOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeComboCfgDomePtzType();
	afx_msg void OnBnClickedButtonDomePtzSet();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateInfo();
	void UI_UpdateText();
	void UI_CleanText();
private:
	CComboBox m_cboDomePTZType;
	CComboBox m_cboWaitAct;
	CComboBox m_cboAutiomatic;
	CComboBox m_cboSpeedLevel;
	CComboBox m_cboSensitiveThreshold;
	CComboBox m_cboDelayTime;
	CComboBox m_cboControlMode;
	CComboBox m_cboZoomMatch;
	CComboBox m_cboInstantLight;
	CComboBox m_cboShortLight;
	CComboBox m_cboInstantLight2;
	CComboBox m_cboShortLight2;
	CButton m_chkDomePTZEnable;
	CButton m_chkManualOperation;
	CButton m_chkAutomatic;
	CButton m_btnSetControlTime;
	CDateTimeCtrl m_dtpStartTime;
	CDateTimeCtrl m_dtpEndTime;
	CEdit m_edtWaitAct;	
	CEdit m_edtManualOperation;
	CStatic m_stcDelayTime;
	int m_iLogonID;	
	int m_iChannelNo;
public:
	afx_msg void OnBnClickedCheckDomePtzManual();
	afx_msg void OnBnClickedCheckDomePtzAutomatic();
	afx_msg void OnCbnSelchangeCboCfgCooperDomeSensitiveThreshold();	
	afx_msg void OnCbnSelchangeCboCfgCooperDomeDelayTime();	
	afx_msg void OnBnClickedBtnCfgCooperSetControlTime();
	afx_msg void OnBnClickedBtnCfgCooperSetZoomMatch();
	afx_msg void OnCbnSelchangeCboCfgCooperDomeControlMode();
	afx_msg void OnCbnSelchangeCboCfgCooperDomeZoomMathc();
};

#endif
