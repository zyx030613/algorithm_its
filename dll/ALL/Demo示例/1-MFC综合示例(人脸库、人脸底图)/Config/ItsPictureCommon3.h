#ifndef _ECOP_IMGDISPOSAL_PAGE_H
#define _ECOP_IMGDISPOSAL_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#define ITS_MAX_HOUR 24
#define ITS_MAX_MINUTE 59
// CLS_ECOPImgDisposalPage dialog

class CLS_ItsPictureCommon3 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsPictureCommon3)

public:
	CLS_ItsPictureCommon3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ItsPictureCommon3();

// Dialog Data
	enum { IDD = IDD_DLG_ITS_PICTURE_COMMON3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	void UI_UpdateImgDisposal();
	void UI_UpdateTimeAgcFlash();
	void UI_UpdateBackuplight();
	void UI_UpdatePageEnable();

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
	int m_iChannelNo;

	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedButtonImgdisposal();
	afx_msg void OnBnClickedBtnBackuplight();
	afx_msg void OnBnClickedButtonTimerange3();
	CButton m_chkTimeRangeIndex3;
private:
	CComboBox m_cboTimeRangeIndex3;
public:
	afx_msg void OnCbnSelchangeComboTimerangeindex3();
	CButton m_btnSetExtraLight;
	afx_msg void OnBnClickedCheckTimerangeindex3();
};

#endif