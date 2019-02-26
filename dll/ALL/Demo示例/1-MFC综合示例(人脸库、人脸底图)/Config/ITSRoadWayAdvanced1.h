#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_ITSRoadWayAdvanced1 对话框

class CLS_ITSRoadWayAdvanced1 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSRoadWayAdvanced1)

public:
	CLS_ITSRoadWayAdvanced1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ITSRoadWayAdvanced1();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_ROADWAY_ADVANCED1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	int m_iLogonID;
	unsigned short m_usRangeTimeStartH[MAX_PRESET_COUNT][MAX_AREA_COUNT];
	unsigned short m_usRangeTimeStartM[MAX_PRESET_COUNT][MAX_AREA_COUNT];
	unsigned short m_usRangeTimeEndH[MAX_PRESET_COUNT][MAX_AREA_COUNT];
	unsigned short m_usRangeTimeEndM[MAX_PRESET_COUNT][MAX_AREA_COUNT];

	CEdit m_edtPointx[4];
	CEdit m_edtPointy[4];

	void UI_UpdateDialog();
	void GetCoorEditShow( POINT *_ptPoint, int _iN0, int flag );
	void UI_UpdateIllegalpark();
	void UI_UpdateCarPermi();
	BOOL UI_UpdateRoadway();
public:
	afx_msg void OnBnClickedBtnSetIllegalpark();
	CComboBox m_cboPreset;
	CDateTimeCtrl m_dtcFrom;
	CDateTimeCtrl m_dtcTo;
	CComboBox m_cboTimeRange;
	CComboBox m_cboArea;
	CEdit m_edtParkTime;
	CEdit m_edtSensitivity;
	CEdit m_edtTime;
	afx_msg void OnBnClickedBtnSetCarPermi();
	CComboBox m_cboRuleId;
	CComboBox m_cboCarType;
	CComboBox m_cboRoadwayID;
	CButton m_chkRegionEn;
	CButton m_chkEventCheckEn;
	afx_msg void OnCbnSelchangeCboRoadwayid();
	afx_msg void OnCbnSelchangeCboCarType();
	CButton m_chkRoadwayNo;
	afx_msg void OnBnClickedCheckRoadwayno();
};
