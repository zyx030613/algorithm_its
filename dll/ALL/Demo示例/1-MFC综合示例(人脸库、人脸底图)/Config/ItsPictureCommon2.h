#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

#define MANUL				0
#define AUTO_SIMPLE			1
#define AUTO_DIFFCULT		2
#define ITS_TYPE_NUM 14
#define ITS_JPEG_MIN_VALUE 0
#define ITS_JPEG_MAX_VALUE 100
#define ITS_LIMIT_MIN 64
#define ITS_LIMIT_MAX 8192
#define ITS_MAX_HOUR 24
#define ITS_MAX_MINUTE 59
// Cls_ItsPictureCommon2 对话框

class Cls_ItsPictureCommon2 : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsPictureCommon2)

public:
	Cls_ItsPictureCommon2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cls_ItsPictureCommon2();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_PICTURE_COMMON2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	int m_iLogonID;
	int m_iChannelNo;
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
private:
	void  UI_UpdateDialog();
	void  UI_UpdateTimeAgcFlash();
	void  UI_UpdateBacklightSet();
	void  UI_UpdateCap();
	void  UI_UpdatePic();
	void  CheckEnable();
	void  UI_UpdatePageEnable();
	void  UI_UpdateDenoise();
public:
	CButton m_chkFlashLamp;
	afx_msg void OnBnClickedBtnBacklightSet();
	CButton m_chkFlashLampAuto;
	CButton m_chkStrobe;
	CButton m_chkStrobeAuto;
	afx_msg void OnBnClickedButtonTimerange2();
	CComboBox m_cboTimeRangeIndex2;
	CButton m_chkTimeRangeIndex2;
	CEdit m_edtTimeRange2;
	CButton m_btnTimeRange2;
	afx_msg void OnBnClickedChkCapEnable();
	afx_msg void OnNMCustomdrawSldLightExpect(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_chkCapEnable;
	afx_msg void OnNMCustomdrawSldExpoUpperLimit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldGainUpperLimit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPicSizeLimitSet();
	afx_msg void OnStnClickedStaPicSizeLimit2();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRdoAuto();
	afx_msg void OnBnClickedRdoManul();
	CComboBox m_cboDenoise3D;
	CEdit m_edtDenoise2D;
	int m_rdoHand;
	int m_rdoEasy;
	int m_rdoDiffcult;
	afx_msg void OnBnClickedRadio1();
	CComboBox m_cboSelectForm;
	afx_msg void OnBnClickedStaticCapture();
	afx_msg void OnBnClickedButton1();
	CButton m_btnSetDenoise;
	afx_msg void OnBnClickedBtnSetDenoise();
	//afx_msg void OnCbnSelchangeCboLevel();
	afx_msg void OnBnClickedBtnSet();
	CButton m_btnSet;
	afx_msg void OnCbnSelchangeComboTimerangeindex2();
	CSliderCtrl m_sldLightExpect;
	CSliderCtrl m_sldExpoUpperLimit;
	CSliderCtrl m_sldGainUpperLimit;
	afx_msg void OnBnClickedCheckTimerangeindex2();
	CButton m_btnSetLight;
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_edtDenoise3D;
	CEdit m_edtDenoiseValue;
	afx_msg void OnStnClickedStc3dLevel();
	afx_msg void OnCbnSelchangeCboLevel();
};
