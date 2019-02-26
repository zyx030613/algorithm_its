#pragma once

#include "afxwin.h"
#include "../BasePage.h"

#define MAX_TRACK_CHK_TYPE			4

class CLS_VCAEvnetsSmartTrack : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCAEvnetsSmartTrack)

public:
	CLS_VCAEvnetsSmartTrack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEvnetsSmartTrack();

	enum { IDD = IDD_DLG_CFG_VCA_EVENTS_SMART_TRACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CEdit 		m_edtTrackMulripe;		// 跟踪倍率
	CEdit 		m_edtDomeHeight;
	CEdit 		m_edtMaxTrackTime;
	CEdit 		m_edtMaxStaticTime;
	CEdit 		m_edtMaxSize;
	CEdit 		m_edtMinSize;
	CButton		m_chkTrack[MAX_TRACK_CHK_TYPE];
	CComboBox	m_cboSenceId;

private:
	int		m_iLogonID;
	int		m_iChannelNo;

public:
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	void	UI_InitDlgItemText();
	void	UI_UpdateTrackLimitStatus();
	void	UI_UpdateTrackArithmatic();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetTrackLimitStatus();
	CComboBox m_cboLimitStatus;
	afx_msg void OnBnClickedBtnSetTrackArithmatic();
	afx_msg void OnCbnSelchangeCboTrackSceneId();
};
