#pragma once
#include "VCAEventAdvParamBase.h"
#include "afxwin.h"


// CLS_VCAAdvParamWld dialog

class CLS_VCAAdvParamWld : public CLS_VCAEventAdvParamBase
{
	DECLARE_DYNAMIC(CLS_VCAAdvParamWld)

public:
	CLS_VCAAdvParamWld(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAAdvParamWld();

// Dialog Data
	enum { IDD = IDD_DLG_VCAPARAM_ADV_WLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void UI_UpdateDialog();
	void OnLanguageChanged();
	void UI_UpdateSdkParam();
	afx_msg void OnBnClickedBtnVcaWldAdvParaSet();
private:
	CEdit m_edtWavePeriod;
};
