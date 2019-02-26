#pragma once
#include "../BasePage.h"
#include "afxwin.h"

// CLS_ItsRoadwayCommon2 对话框

#define LEFT_BOUND	1
#define RIGHT_BOUND	2
#define BOTH_BOUND	3

class CLS_ItsRoadwayCommon2 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsRoadwayCommon2)

public:
	CLS_ItsRoadwayCommon2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ItsRoadwayCommon2();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_ROADWAY_COMMON2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iLogonID;

	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

	afx_msg void OnBnClickedBtnSpeedlimit();
private:
	void UI_UpdateDialog();
	void UI_UpdateSpeedlimit();
	void UI_UpdateCarProperty();
	BOOL UI_UpdateRoadway();
	void UI_UpdateSpeedUse();
public:
	CComboBox m_cboRoadwayId;
	CComboBox m_cboCarType;
	afx_msg void OnBnClickedBtnCarProperty();
	CButton m_chkRoadwayEnable;
	CComboBox m_cboCarUpDown;
	CComboBox m_cboCarUse;
	CComboBox m_cboCarBoun;
	afx_msg void OnBnClickedBtnCarchannel3();
	afx_msg void OnCbnSelchangeCmbRoadwayid();
	afx_msg void OnCbnSelchangeCmbCarType();
	CButton m_chkRoadwayNo;
	afx_msg void OnBnClickedCheckRoadwayno();
	CEdit m_edtSpeedLow;
	CEdit m_edtSpeedHigh;
	CEdit m_edtErrorSpeedLow;
	CEdit m_edtErrorSpeedHigh;
	CEdit m_edtImNotGoodAtEnglish;
	CEdit m_edtPercent;
	CButton m_btnSetSpeed;
};
