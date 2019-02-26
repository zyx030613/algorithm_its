#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_VCAEVENT_GoodsLose 对话框

class CLS_VCAEVENT_GoodsLose : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_GoodsLose)

public:
	CLS_VCAEVENT_GoodsLose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_GoodsLose();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_GOODS_LOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual	BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void OnLanguageChanged();
	void UpdateUIText();
	void CleanText();
	void UpdatePageUI();
	int DrawArea(int _iAreaNum );
	afx_msg void OnBnClickedBtnGoodsSet();
	afx_msg void OnEnChangeEdtGoodsMinTime();
	afx_msg void OnEnChangeEdtGoodsMinSize();
	afx_msg void OnEnChangeEdtGoodsMaxSize();
	afx_msg void OnBnClickedBtnGoodsMainArea();
	afx_msg void OnBnClickedBtnGoodsChildarea1();
	afx_msg void OnBnClickedBtnGoodsChildarea2();
	afx_msg void OnBnClickedBtnGoodsChildarea3();

private:
	CButton m_chkEventValid;
	CButton m_chkAlarmRule;
	CButton m_chkAlarmStat;
	CButton m_chkTargetBox;
	CEdit m_edtMinTime;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;
	CComboBox m_cboAlarmColor;
	CComboBox m_cboUnalarmColor;
	CComboBox m_cboChildareaNum;
	CEdit m_edtMainArea;
	CEdit m_edtChildArea1;
	CEdit m_edtChildArea2;
	CEdit m_edtChildArea3;

public:
	afx_msg void OnCbnSelchangeCboGoodsChildareaNum();
};
