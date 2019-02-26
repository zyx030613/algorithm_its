#ifndef _ECOP_CAPTURE_PAGE_H
#define _ECOP_CAPTURE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"


// CLS_ECOPCapturePage dialog

class CLS_ItsRoadwayCommon3 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsRoadwayCommon3)

public:
	CLS_ItsRoadwayCommon3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ItsRoadwayCommon3();

// Dialog Data
	enum { IDD = IDD_DLG_ITS_ROADWAY_COMMON3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateCapture();
	void UI_UpdateChnLight();
	void UI_UpdateCapDelay();
	BOOL UI_UpdateRoadway();

private:
	CComboBox m_cboRoadwayID;
	CEdit m_edtCaptureType;
	CEdit m_edtFirstPlace;
	CEdit m_edtSecondPlace;
	CEdit m_edtThirdPlace;
	CButton m_btnCapture;
	int m_iLogonID;
public:
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedButtonCapture();
	afx_msg void OnBnClickedButtonChnlight();
	CComboBox m_cboComNo;
	CEdit m_edtLightID;
	CEdit m_edtFloodID;
	afx_msg void OnBnClickedBtnFifthCapDelay();
	afx_msg void OnBnClickedBtnCapDelay();
	CComboBox m_cboFirstCapDelay;
	CComboBox m_cboSecondCapDelay;
	CComboBox m_cboThirdCapDelay;
	CComboBox m_cboFourthCapDelay;
	CComboBox m_cboFifthCapDelay;
private:
	CComboBox m_cboFlashModel;
public:
	CButton m_chkRoadwayNo;
	afx_msg void OnBnClickedCheckRoadwayno();
};

#endif