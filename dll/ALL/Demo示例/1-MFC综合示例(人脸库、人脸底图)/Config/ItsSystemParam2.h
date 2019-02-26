#pragma once
#include "../BasePage.h"
#include "afxwin.h"

// CLS_ItsSystemParam2 对话框

class CLS_ItsSystemParam2 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsSystemParam2)

public:
	CLS_ItsSystemParam2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ItsSystemParam2();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_SYSTEMPARAM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	int m_iLogonID;
	int m_iChannel;
	void UI_UpdateDialog();
	BOOL UI_UpdateUseAroundPicture();
	BOOL UI_UpdateCaptureNumber();
public:
	CStatic m_gpSystem;
	CStatic m_stcSystemType;
	CStatic m_stcElectricPolice;
	CButton m_chkAroundPicture;
	CButton m_btnSetUseAroundPicture;
	CStatic m_stcCorrelationCameraCar;
	CComboBox m_cboCorrelationCameraCar;
	CStatic m_stcAroundCameraType;
	CComboBox m_cboAroundPictureType;
	CStatic m_stcCaptureDirection;
	CComboBox m_cboCaptureDirection;
	CStatic m_stcCorrelationCamera;
	CEdit m_edtCorrelationCamera;
	CButton m_btnSetCorrelation;
	CStatic m_stcCaptureMode;
	CComboBox m_cboCaptureMode;
	CButton m_btnSetCaptureMode;
	CStatic m_stcKKCameraNumber;
	CComboBox m_cboKKCameraNumber;
	CButton m_btnSetKKCameraNumber;
	CStatic m_stcIllegalCaptureNumber;
	CComboBox m_cboIllegalCaptureNumber;
	CButton m_btnSetIllegalCaptureNumber;
	afx_msg void OnBnClickedBtnSetUseAroundPicture();
	afx_msg void OnBnClickedBtnSetIllegalCaptureNumber();
	afx_msg void OnBnClickedBtnSetCaptureMode();
	afx_msg void OnStnClickedStcCurrelationCameraCar();
	CComboBox m_cboCorrelationCameraCarRoad;
private:
	CComboBox m_cboRoadID;
public:
	afx_msg void OnCbnSelchangeCboRoadid();
	afx_msg void OnCbnSelchangeCboCaptureMode();
};
