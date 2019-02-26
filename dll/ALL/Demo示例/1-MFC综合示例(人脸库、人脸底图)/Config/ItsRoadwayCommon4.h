#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#define ITS_LINE_ID_MAX 101
#define ITS_LINE_TYPE_MAX 18
// CLS_ItsRoadwayCommon4 对话框

class CLS_ItsRoadwayCommon4 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsRoadwayCommon4)

public:
	CLS_ItsRoadwayCommon4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ItsRoadwayCommon4();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_ROADWAY_COMMON4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLineSet();

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	int m_iLogonID;
	int m_iChannel;
	void UI_UpdateDialog();
	void UI_UpdateLineSet();
	void UI_UpdateCapType();
	void UI_UpdateLineSet2();
	BOOL UI_UpdateRoadway();
public:
	CComboBox m_cboRoadwayID4;
	CComboBox m_cboLineId;
	CButton m_chkEnable;
	CComboBox m_cboLineType;
	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedBtnCapType();
	CButton m_chkBayonet;
	CButton m_chkRedLight;
	CButton m_chkRetroGrade;
	CButton m_chkSpeed;
	CButton m_chkForbidLeft;
	CButton m_chkForbidRight;
	CButton m_chkYellowLine;
	CButton m_chkNonMotor;
	CButton m_chkNotGuide;
	CButton m_chkForbidStraight;
	CButton m_chkBusWay;
	CButton m_chkPressWayLine;
	CButton m_chkWaitturnRed;
	CButton m_chkIllegalPark;
	CButton m_chkMixCapSpeed;
	CComboBox m_cmbCarType;
	CComboBox m_cmbStrategy;
	CComboBox m_cmbRedlightCap;
	CComboBox m_cmbTrailCapPlace;
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedBtnLineSet2();
private:
	CButton m_chkBack;
	CButton m_chkTurn;
	CButton m_chkRush;
	CButton m_chkMax;
	CButton m_chkRideCapture;
public:
	afx_msg void OnBnClickedButton1();
	CButton m_btnSetCarLane;
	afx_msg void OnBnClickedBtnSetCarLane();
	CButton m_chkRoadwayNo;
	afx_msg void OnBnClickedCheckRoadwayno();
	afx_msg void OnCbnSelchangeCmbLineId();
};
