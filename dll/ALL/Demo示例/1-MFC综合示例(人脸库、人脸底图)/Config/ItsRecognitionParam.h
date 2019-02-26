#ifndef _ECOP_RECOPARAM_PAGE_H
#define _ECOP_RECOPARAM_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ECOPRecoParamPage dialog

class CLS_ItsRecognitionParam : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsRecognitionParam)

public:
	CLS_ItsRecognitionParam(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ItsRecognitionParam();

// Dialog Data
	enum { IDD = IDD_DLG_ITS_RECOPARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	void UI_UpdateEnable();
	void UI_UpdateWordNumber();
	BOOL UI_UpdateRecoParam();
    BOOL UI_UpdateEnableNoPlate();
	BOOL UI_UpdateLicense();
	BOOL UI_UpdateOptimize();

private:
	CComboBox m_cboRoadwayID;
	CComboBox m_cboLicenseType;
	CButton m_chkEnable;
	CButton m_chkNoPlate;
	CEdit m_edtMaxPlate;
	CEdit m_edtMaxPlateWidth;
	CEdit m_edtMinPlateWidth;
	CEdit m_edtEngineNum;
	CEdit m_edtAreaType;
	CEdit m_edtPlateType;
	CEdit m_edtSpeed;
	CEdit m_edtMaxSkip;
	CEdit m_edtMinValid;
	CEdit m_edtFramePercent;
	CEdit m_edtMinCapDiff;
	CEdit m_edtCaliInfo;
	CButton m_btnRecoParam;
	CEdit m_edtFirstChinese;
	CEdit m_edtFirstChineseConfig;
	CEdit m_edtFirstWord;
	CEdit m_edtFirstWordConfig;
	CEdit m_edtWordCount;
	CEdit m_edtWord[MAX_MODIFYCHAR_COUNT];
	int m_iLogonID;
	int m_iChannel;
	CEdit m_edtWordNum[MAX_MODIFYCHAR_COUNT];

public:
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedButtonRecoparam();
	afx_msg void OnBnClickedButtonNoplate();
	afx_msg void OnBnClickedButtonLicense();	
	afx_msg void OnBnClickedButtonOptimize();

	
	afx_msg void OnBnClickedCheckRecoparamEnable();
	afx_msg void OnEnChangeEditWordcount();
	afx_msg void OnCbnSelchangeComboLicenseType();
	afx_msg void OnEnChangeEditFirstchinese();
};

#endif
