#ifndef _ECOP_RECOPARAM_PAGE_H
#define _ECOP_RECOPARAM_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ECOPRecoParamPage dialog

class CLS_ECOPRecoParamPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ECOPRecoParamPage)

public:
	CLS_ECOPRecoParamPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ECOPRecoParamPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ECOP_RECOPARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateRecoParam();

private:
	CComboBox m_cboRoadwayID;
	CButton m_chkEnable;
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
	int m_iLogonID;

public:
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedButtonRecoparam();
};

#endif
