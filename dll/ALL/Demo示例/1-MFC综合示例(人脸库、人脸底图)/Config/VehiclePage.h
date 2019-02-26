#pragma once
#include "BasePage.h"
#include "afxcmn.h"


// CLS_VehiclePage dialog

class CLS_VehiclePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VehiclePage)

public:
	CLS_VehiclePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VehiclePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VEHICLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheckGpsCalibration();
	afx_msg void OnBnClickedButtonVoltageThreshold();
private:
	void UI_UpdateDialog();
	void UI_UpdateVehicle();
	void UI_UpdateGpsCalibration();
	void UI_UpdateGpsModuleType();	
	void UI_UpdateSatelliteNum();
	void UI_UpdateSignalIntensity();
	void UI_UpdateSupplyVoltage();
	void UI_UpdateTemperature();
	void UI_UpdateAlarmThreshold();
	void UI_UpdateShutdownThreshold();
private:
	int m_iLogonID;
	CComboBox m_cboGpsType;
	CProgressCtrl m_progressGpsSignal;
	CSpinButtonCtrl m_spinAlarmValue;
	CSpinButtonCtrl m_spinShutdownValue;
	CToolTipCtrl m_tipCtrl;
	
};
