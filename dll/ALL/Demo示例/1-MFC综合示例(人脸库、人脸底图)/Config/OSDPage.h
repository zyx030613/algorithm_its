#ifndef _OSD_PAGE_H
#define _OSD_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "../Common/SplitterButton.h"


// CLS_OSDPage dialog
#define  FONTSIZE_DEFINE  6		//定义字符大小

class CLS_OSDPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_OSDPage)

public:
	CLS_OSDPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_OSDPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_OSD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnDropDownCheckChanneltitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonChanneltitle();
	afx_msg void OnBnDropDownCheckDatetime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDatetime();
	afx_msg void OnBnClickedButtonPos();
	afx_msg void OnBnDropDownCheckLogo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonLogo();
	afx_msg void OnBnClickedButtonDrawtext();
	afx_msg void OnBnClickedButtonTextcmd();
	afx_msg void OnNMCustomdrawSliderDiaphaneity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonColor();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonAlpha();
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateChannelTitle();
	BOOL UI_UpdateDateTime();
	BOOL UI_UpdateLogo();
	BOOL UI_UpdateDrawText();
	BOOL UI_UpdateDiaphaneity();
	BOOL UI_UpdateAlpha();
	BOOL UI_UpdateColor();
	BOOL UI_UpdateFontSize();
	void UI_UpdateFontDbType();
	void DrawTextOnVideo(int _iStore);

private:
	CButton m_chkChannelTitle;
	CEdit m_edtChannelTitle;
	CButton m_btnChannelTitle;
	CEdit m_edtChannelTitlePosX;
	CEdit m_edtChannelTitlePosY;
	CButton m_chkDateTime;
	CEdit m_edtDateTimePosX;
	CEdit m_edtDateTimePosY;
	CButton m_btnDateTime;
	CButton m_chkLogo;
	CEdit m_edtLogoPosX;
	CEdit m_edtLogoPosY;
	CButton m_btnLogo;
	CEdit m_edtDrawText;
	CButton m_btnDrawText;
	CEdit m_edtDrawTextPosX;
	CEdit m_edtDrawTextPosY;
	CButton m_btnTextCmd;	
	CSliderCtrl m_sldDiaphaneity;
	CStatic m_stxtProgress;
	CButton m_btnColor;
	CEdit m_edtAlpha;
	CButton m_btnAlpha;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	int m_iColor;
	bool m_bDateTime;
	bool m_bLogo;
	CComboBox m_cboOSDType;
	CButton m_chkBackgroundColor;
	CLS_SplitterButton m_btnOSDColor;
	CButton m_btnOSDSet;
	BOOL m_iFontDbLattice;
public:
	afx_msg void OnBnClickedButtonOsdset();
	afx_msg void OnCbnSelchangeComboOsdtype();
	CComboBox m_cboFontSize;
	afx_msg void OnBnClickedButtonOsdfontsize();
	CEdit m_edtFontWid;
	CEdit m_edtFontHigh;
	afx_msg void OnCbnSelchangeComboOsdfontsize();
	CEdit m_edtChannelName;
	CEdit m_edtDevComName;
	CComboBox m_cboDevComName;
	CEdit m_edtChanTitleEx;
	CEdit m_edtChanTitlColoEx;
	CComboBox m_cboDevComNameType;
	afx_msg void OnCbnSelchangeComboDevcomname();
	afx_msg void OnBnClickedRadioOsdFontDbTypeVector();
private:
	CEdit m_edtChannelCommonName;
};

#endif
