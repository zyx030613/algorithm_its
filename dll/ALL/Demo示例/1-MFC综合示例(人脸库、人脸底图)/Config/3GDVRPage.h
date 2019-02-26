#ifndef _3GDVR_PAGE_H_
#define _3GDVR_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_3GDVRPage dialog

class CLS_3GDVRPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_3GDVRPage)

public:
	CLS_3GDVRPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_3GDVRPage();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_3G_DVR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3GDVRTimeSet();
	afx_msg void OnBnClickedButton3GDVRGpsOverlay();
	afx_msg void OnBnClickedButton3GDVRGpsFilter();
	afx_msg void OnBnClickedButton3GDVRFtpUploadMode();
	void SetFiterText();
	void UI_UpdateDialog();
	void UI_Update3GDVRInfo();
private:
	int m_iLogonID;
	int m_iChannelNo;
	CEdit m_edtOnTime;
	CEdit m_edtOffTime;
	CEdit m_edtSimNum;
	CEdit m_edtFinalFilter;
	CComboBox m_cboFtpUploadMode;
public:
	virtual BOOL OnInitDialog();
private:
	CButton m_chkGpsOverlayEnable;
public:
	afx_msg void OnBnClickedCheck3GDVRGsv();
	afx_msg void OnBnClickedCheck3GDVRGsa();
	afx_msg void OnBnClickedCheck3GDVRGll();
	afx_msg void OnBnClickedCheck3GDVRVtg();
	afx_msg void OnBnClickedCheck3GDVRRmc();
	afx_msg void OnBnClickedCheck3GDVRGga();
	afx_msg void OnBnClickedCheck3GDVRNone();
	afx_msg void OnBnClickedCheck3GDVRAll();
private:
	CButton m_chkGpsFilterGSV;
	CButton m_chkGpsFilterGSA;
	CButton m_chkGpsFilterGLL;
	CButton m_chkGpsFilterVTG;
	CButton m_chkGpsFilterRMC;
	CButton m_chkGpsFilterGGA;
	CButton m_chkGpsFilterNone;
	CButton m_chkGpsFilterAll;
};

#endif
