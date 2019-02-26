#ifndef _ECOP_LIGHT_PAGE_H
#define _ECOP_LIGHT_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ECOPLightPage dialog

class CLS_ItsSignalCheck : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsSignalCheck)

public:
	CLS_ItsSignalCheck(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ItsSignalCheck();

// Dialog Data
	enum { IDD = IDD_DLG_ITS_SIGNAL_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateChnLight();
	BOOL UI_UpdateLightInfo();
	//BOOL UI_UpdateStartlight();
	BOOL UI_UpdateAreaSet();
	BOOL UI_UpdateTimeSet();
	BOOL UI_UpDateArea();

private:
	CComboBox m_cboRoadwayID;
	CComboBox m_cboComNo;
	CEdit m_edtLightID;
	CEdit m_edtFloodID;
	CButton m_btnChnLight;
	CComboBox m_cboLightInfoID;
	CEdit m_edtInterval;
	CEdit m_edtAcceptDiff;
	CButton m_btnLightInfo;
	int m_iLogonID;
	int m_iLightID;
	int m_iChannel;
	//CComboBox m_cboLightArea;
	CButton m_btnStartLight;
	CComboBox m_cboRoadType;

public:
	afx_msg void OnBnClickedButtonLightinfo();
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnCbnSelchangeComboLightinfoid();
	afx_msg void OnBnClickedButtonSignallight();
	afx_msg void OnBnClickedStaticChnlight();
	afx_msg void OnBnClickedBtnLightset();
	
public:
	afx_msg void OnCbnSelchangeComboComno();
	afx_msg void OnCbnSelchangeCboArea();
	afx_msg void OnBnClickedCheckStart();
private:
	CComboBox m_cboLightType;
public:
	//afx_msg void OnBnClickedBtnSetarea();
private:
	
	CButton m_cboSetTime;
public:
	CEdit m_editRedInterval;
private:
	CEdit m_editYellowTime;
	CEdit m_editRedupdate;
public:
	CEdit m_editRedPhase;
	afx_msg void OnBnClickedBtnSettime();
private:
	CComboBox m_cboAreaId;
	CComboBox m_cboRectNum;
	//CEdit m_edtRect;
	CComboBox m_cboLightArea;
public:
	afx_msg void OnBnClickedBtnSetarea();
private:
	CEdit m_edtRect;
public:
	afx_msg void OnCbnSelchangeCboAreatype();
	afx_msg void OnCbnSelchangeCboAreaid();
};

#endif