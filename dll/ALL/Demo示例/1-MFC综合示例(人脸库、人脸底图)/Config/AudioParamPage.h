#ifndef _AUDIO_PARAM_PAGE_H_
#define _AUDIO_PARAM_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_AudioParamPage dialog

class CLS_AudioParamPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AudioParamPage)

public:
	CLS_AudioParamPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AudioParamPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_AUDIO_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();	
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedButtonAudioEncoder();
	afx_msg void OnBnClickedButtonAudioSample();

private:
	void UI_UpdateDialog();
	void UI_UpdateAudioEncoder();
	void UI_UpdateAudioSample();
	void UI_UpdateVolumeOut();
	void UI_UpdateCurrentVolume();
	void UI_UpdateMaxVolume();

private:
	CComboBox m_cboVolumeOutType;
	CSliderCtrl m_sldVolumeOutValue;
	CComboBox m_cboAudioEncoder;
	CComboBox m_cboAudioSample;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iCurrentSceneId;
	CComboBox m_cboSceneId;
	CButton m_chkGetAudio;

public:
	void CommandGetAudio(int _iSceneId, int _iState);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);
	afx_msg void OnBnClickedBtnVolumeOutSet();
	afx_msg void OnCbnSelchangeCboVolumeOutType();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedBtnPlayAudioPlay();
	afx_msg void OnEnChangeEdtPlayAudioNo();
	afx_msg void OnBnClickedChkGetaudioEnable();
	afx_msg void OnCbnSelchangeCboSceneId();
	afx_msg void OnBnClickedBtnSetMaxVolume();
	afx_msg void OnEnChangeEdtMaxVolume();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

#endif
