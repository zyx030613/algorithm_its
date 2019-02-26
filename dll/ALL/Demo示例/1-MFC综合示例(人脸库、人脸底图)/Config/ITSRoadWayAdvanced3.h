#pragma once
#include "../BasePage.h"
#include "afxwin.h"

// CLS_ITSRoadWayAdvanced3 对话框

class CLS_ITSRoadWayAdvanced3 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSRoadWayAdvanced3)

public:
	CLS_ITSRoadWayAdvanced3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ITSRoadWayAdvanced3();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_ROADWAY_ADVANCED3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedBtnTriggerSet();
	afx_msg void OnBnClickedBtnInfoSet();
	afx_msg void OnCbnSelchangeCboRoadnum();
	afx_msg void OnBnClickedBtnParamSet();
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateTrigger();
	BOOL UI_UpdateRadarInfo();
	BOOL UI_UpdateParam();
	BOOL UI_UpdateRoadway();
private:
	CComboBox m_cboRoadSum;
	CComboBox m_cboRoadNum;
	CEdit m_edtRadarMtachTm;
	CEdit m_edtMax;
	CEdit m_edtMin;
	int m_iLogonID;
	int m_iChannel;
	CComboBox m_cboRadarAreaID;
	CEdit m_edtRadarRightRect;
	CEdit m_edtRadarLeftRect;
	CEdit m_edtRadarLine;
	CComboBox m_cboAreaID;
	CEdit m_edtRectNum;
	CComboBox m_cboAreaNum;
	CEdit m_edtRect;
public:
	afx_msg void OnCbnSelchangeCboAreaid();
	afx_msg void OnCbnSelchangeCboRadarAreaid();
	afx_msg void OnCbnSelchangeCboRoadsum();
	CButton m_chkRoadwayNo;
	afx_msg void OnBnClickedCheckRoadwayno();
};
