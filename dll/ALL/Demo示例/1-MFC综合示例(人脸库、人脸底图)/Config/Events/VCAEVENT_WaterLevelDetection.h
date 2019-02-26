#pragma once
#include "VCAEventBasePage.h"
#include "afxwin.h"
#include <vector>


// CLS_VCAEVENT_WaterLevelDetection dialog

class CLS_VCAEVENT_WaterLevelDetection : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_WaterLevelDetection)

public:
	CLS_VCAEVENT_WaterLevelDetection(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_WaterLevelDetection();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_WATER_LEVEL_DETECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void UI_UpdateDialog();
	void UI_UpdateSdkParam();
	void UI_UpdatePresetScene();
	void OnLanguageChanged();
	afx_msg void OnCbnSelchangeComboWldPresetNo();
	afx_msg void OnBnClickedBtnWldDrawGaugeRect();
	afx_msg void OnBnClickedBtnWldDrawAssistRect();
	afx_msg void OnBnClickedBtnWldDrawGaugeLine();
	afx_msg void OnBnClickedBtnWldDrawReferPoints();
	void GetInfoOnDrawVideo(int* _piPointCount, char* _pcPointsBuf, RECT* _ptRect, int _iDrawType);
	afx_msg void OnBnClickedButtonWldAddPresetScene();
	afx_msg void OnBnClickedButtonWldDeletePresetScene();
	afx_msg void OnBnClickedButtonWldClearPresetScene();
	afx_msg void OnBnClickedButtonWldSet();
	void UI_UpdatePresetSceneText();
private:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayAlarmCount;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboAreaColor;
	CComboBox m_cboGaugeType;
	CComboBox m_cboPresetNo;
	CEdit m_edtSnapIntervel;
	CEdit m_edtBaseValue;
	CEdit m_edtCurPresetID;
	CEdit m_edtPresetValueLow;
	CEdit m_edtPresetValueHigh;
	CEdit m_edtGaugeRect;
	CEdit m_edtAssistRect;
	CEdit m_edtGaugeLine;
	CEdit m_edtReferPoints;
	WaterSamplePoint m_tGetWld;
	vector<WaterPresetInfo> m_vecPresetScene;
	int m_iReferCount;
	CEdit m_edtReferPointValue;
public:
	afx_msg void OnBnClickedButtonVcaWldShowRegion();
	virtual void OnMainNotify(int _ulLogonID, int _iWparam, void* _pvLParam, void* _pvUser);
};
