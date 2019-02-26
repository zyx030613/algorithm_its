#pragma once
#include "../BasePage.h"
#include "afxwin.h"

#define MAX_ILLEGAL_TYPE		21

class CLS_DLG_ITSRoadwayCaptureCfg : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DLG_ITSRoadwayCaptureCfg)

public:
	CLS_DLG_ITSRoadwayCaptureCfg(CWnd* pParent = NULL);   
	virtual ~CLS_DLG_ITSRoadwayCaptureCfg();

	enum { IDD = IDD_DLG_ITS_ROADWAY_CAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()

private:
	int m_iLogonID;
	int m_iChannel;

private:
	CButton m_chkIllegalType[MAX_ILLEGAL_TYPE];
	CComboBox m_cboRoadwayId;
	CComboBox m_cboSceneId;
	CComboBox m_cboLinkCapType;
	CComboBox m_cboTimeRangeIndex;
	CComboBox m_cboCarType;
	CDateTimeCtrl m_timeStartTime;
	CDateTimeCtrl m_timeEndTime;

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnCbnSelchangeCboLinkCapType();
	afx_msg void OnCbnSelchangeCboRoadwanyId();
	afx_msg void OnCbnSelchangeCboSceneId();
	afx_msg void OnCbnSelchangeCboTimerangeIndex();
	afx_msg void OnCbnSelchangeCboCarType();
	afx_msg void OnBnClickedBtnLaneCaptureSet();

private:
	void UI_UpdateDialog();
	void ShowLinkTimeRange(BOOL _blShow);
	void ShowLinkCarType(BOOL _blShow);
	void MoveWidgetCorrect();
	void UI_UpdateParam();
	int UI_UpdateRelateTimeRangePara();
	int UI_UpdateRelateCarTypePara();
	int SetCapRelateTimeRange();
	int SetCapRelateCarType();
	void UI_UpdateTimeWidget(int _iTime);
	int GetTimeWidgetValue();
	void UI_UpdateCapTypeWidget(int _iIllegalType);
	int GetCapTypeWidgetValue();
};
