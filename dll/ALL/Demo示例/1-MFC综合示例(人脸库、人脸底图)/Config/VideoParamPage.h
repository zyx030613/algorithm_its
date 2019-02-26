#ifndef _VIDEO_PARAM_PAGE_H
#define _VIDEO_PARAM_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_VideoParamPage dialog

class CLS_VideoParamPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VideoParamPage)

public:
	CLS_VideoParamPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VideoParamPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VIDEO_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateVedioQuality();
	BOOL UI_UpdateFrameRate();
	BOOL UI_UpdateStreamType();
	BOOL UI_UpdatePreferMode();
	BOOL UI_UpdateBitRate();
	BOOL UI_UpdateEncodeMode();
	BOOL UI_UpdateVideoPNMode();
	BOOL UI_UpdateModeMethod();
	BOOL UI_UpdateFrameMode();
	BOOL UI_UpdateIFrameRate();
	BOOL UI_UpdateVencProfileEncoder();
	BOOL UI_UpdateReduceNoise();
	BOOL UI_UpdateSameStream();
	BOOL UI_UpdateVSync();
	BOOL UI_UpdateChannelType();
	void InitVideoSizeMap();
	void UI_UpdateVideoSize();
	void UI_InitVideoEncodeList();		// ”∆µ±‡¬Î∏Ò Ω
	void UI_UpdateSplusMode();

private:
	CComboBox m_cboVideoQuality;
	CComboBox m_cboFrameRate;
	CComboBox m_cboStreamType;
	CComboBox m_cboPreferMode;
	CEdit m_edtBitRate;
	CButton m_btnBitRate;
	CComboBox m_cboVideoSize;
	CButton m_btnVideoSize;
	CComboBox m_cboEncodeMode;
	CComboBox m_cboModeMethod;
	CComboBox m_cboVideoNPMode;
	CButton m_btnVideoNPMode;
	CComboBox m_cboVencType;
	CComboBox m_cboFrameMode;
	CEdit m_edtIFrameRate;
	CButton m_btnIFrameRate;
	CComboBox m_cboVencProfileEncode;
	CButton m_btnDuplicate;
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboReduceNoise;
	CComboBox m_cboBothStreamSame;
	int m_iStreamNo;
	CComboBox m_cboSplusMode;
public:
	afx_msg void OnCbnSelchangeComboVideoquality();
//	afx_msg void OnCbnSelchangeComboFramerate();
	afx_msg void OnCbnSelchangeComboStreamtype();
	afx_msg void OnCbnSelchangeComboPrefermode();
	afx_msg void OnBnClickedButtonBitrate();
	afx_msg void OnBnClickedButtonVideosize();
	afx_msg void OnCbnSelchangeComboEncodemode();
	afx_msg void OnBnClickedButtonVideonpmode();
	afx_msg void OnCbnSelchangeComboVenctype();
	afx_msg void OnBnClickedButtonModemethod();
	afx_msg void OnCbnSelchangeComboFramemode();
	afx_msg void OnBnClickedButtonIframerate();
	afx_msg void OnBnClickedButtonVencprofileEncoder();
	afx_msg void OnBnClickedButtonReduseNoise();
	afx_msg void OnBnClickedButtonSameStream();
	CComboBox m_cboVSync;
	CButton m_btnVSync;
	afx_msg void OnBnClickedButtonVerticalsync();
	afx_msg void OnBnClickedButtonFrameRate();
	afx_msg void OnBnClickedButtonChanneltype();
	CComboBox m_cboChannelType;
private:
	CComboBox m_cboPassageMode;
public:
	afx_msg void OnCbnSelchangeComboVideosizePassage();
	void SetVideoSize(int _iLogonID, int _iChannelNo, int _iStreamNo,int _iVideoSize);
	afx_msg void OnCbnSelchangeComboVideoSplus();
	void UpdateFrameRateCbo();
	afx_msg void OnCbnSelchangeComboVideoNPMode();
};

#endif
