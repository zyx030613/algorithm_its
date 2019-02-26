#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#include "ChanCheck.h"
// CLS_VCAAlarmLinkPage dialog

class CLS_VCAAlarmLinkPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCAAlarmLinkPage)

public:
	CLS_VCAAlarmLinkPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAAlarmLinkPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VCA_ALARM_LINK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	DECLARE_MESSAGE_MAP()

private:

	int m_iLogonID;
	int m_iChannelNo;
	int m_iMaxLinkNum;
	CLS_ChanCheck* m_pclsChanCheck;
	int GetChkLinkChannel(TAlarmLinkParam_V3& _tLink);
	void UI_UpdateAlarmLinkType();
	void UI_UpdateAlarmLink();
	void UI_UpdateAlarmLinkEx();
	void UI_Clear();
	void UI_UpdateText();
	void UI_UpdateChanCheck();
	void UI_UpdateHDTemplateName();
	void UI_UpdateSceneAndTemplateMap();
	void UI_UpdateLaserVoice();

public:
	CComboBox m_cboSinglePic;
	CComboBox m_cboEnbale;
	CComboBox m_cboLinkPTZType;
	CComboBox m_cboPtzNo;
	CComboBox m_cboAlarmLinkRule;
	CComboBox m_cboEvent;
	CComboBox m_cboChannel;
	CComboBox m_cboAlarmLinkType;
	CComboBox m_cboAlarmLinkScene;
	CButton m_chkChannelEnable[32];
	CComboBox m_cboHDTemplate;
	CComboBox m_cboLaserVioce;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboVcaAlarmRule();
	afx_msg void OnCbnSelchangeComboVcaAlarmLink();
	afx_msg void OnCbnSelchangeEditVcaAlarmLinkPtzType();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnCbnSelchangeEditVcaAlarmLinkPtzChannel();
	afx_msg void OnBnClickedButtonSceneTempMapSet();
	afx_msg void OnCbnSelchangeComboAlarmLinkScene();
	
	afx_msg void OnBnClickedBtnLaserviocePlay();
};
