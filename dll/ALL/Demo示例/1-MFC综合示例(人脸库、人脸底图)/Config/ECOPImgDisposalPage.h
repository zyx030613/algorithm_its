#ifndef _ECOP_IMGDISPOSAL_PAGE_H
#define _ECOP_IMGDISPOSAL_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ECOPImgDisposalPage dialog

class CLS_ECOPImgDisposalPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ECOPImgDisposalPage)

public:
	CLS_ECOPImgDisposalPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ECOPImgDisposalPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ECOP_IMGDISPOSAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateImgDisposal();

public:
	CComboBox m_cboRoadwayID;
	CButton m_chkEnable;
	CEdit m_edtQuality;
	CEdit m_edtSaturation;
	CEdit m_edtBrighten;
	CEdit m_edtContrast;
	CEdit m_edtGamma;
	CEdit m_edtAcutance;
	CEdit m_edtImgEnhance;
	CButton m_btnImgDisposal;
	int m_iLogonID;

	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedButtonImgdisposal();
};

#endif