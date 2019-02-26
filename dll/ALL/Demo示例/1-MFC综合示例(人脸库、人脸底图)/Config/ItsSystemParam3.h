#pragma once
#include "../BasePage.h"
#include "afxwin.h"

#define ORGAN_CODE	1

// CLS_ItsSystemParam3 对话框

class CLS_ItsSystemParam3 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsSystemParam3)

public:
	CLS_ItsSystemParam3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ItsSystemParam3();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_SYSTEMPARAM3 };

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
	void UI_UpdateData1();
	void UI_UpdateData2();
	void UI_UpdateData3();
	void UI_UpdateData4();
	void UI_UpdateCode();
public:
	CStatic m_gpDeviceNumber;
	CStatic m_stcDeviceNumber;
	CEdit m_edtDeviceNumber;
	CButton m_btnDeviceNumber;
	CStatic m_gpOrganMessage;
	CStatic m_stcOrganCode;
	CEdit m_edtOrganCode;
	CButton m_btnOrganCode;
	afx_msg void OnBnClickedBtnOrganCode();
	CEdit m_edtOrganCode1;
	afx_msg void OnBnClickedButton3();
	CStatic m_gpCapture;
	CStatic m_stcChannelNumner;
	CComboBox m_cboChannelNumber;
	CStatic m_stcCaptureMode;
	CComboBox m_cboCaptureMode;
	CStatic m_stcPictureQuality;
	CEdit m_edtPictureQuality;
	CStatic m_stcTime;
	CEdit m_edtTime;
	CStatic m_stcPictureSize;
	CStatic m_stcPictureNumber;
	CEdit m_edtPictureNumber;
	CEdit m_edtPictureSize;
	CButton m_btnSetCapture;
	afx_msg void OnStnClickedStcCaptureMode();
	afx_msg void OnBnClickedBtnSetCapture();
	CButton m_btnSetCode;
	afx_msg void OnBnClickedBtnSetCode();
	CStatic m_gpSecurityCode;
	CStatic m_stcStartBit;
	CEdit m_edtStartBit;
	CStatic m_stcLength;
	CEdit m_edtLength;
	CButton m_btnSetSecurityCode;
	afx_msg void OnBnClickedBtnSetSecurityCode();
	CStatic m_stcDeviceTypeNumber;
	CEdit m_edtDeviceTypeNumber;
	CComboBox m_cboDeviceType;
	afx_msg void OnBnClickedBtnDeviceNumber();
	afx_msg void OnCbnSelchangeCboChannelNumber();
	afx_msg void OnCbnSelchangeCboCaptureMode();
};
