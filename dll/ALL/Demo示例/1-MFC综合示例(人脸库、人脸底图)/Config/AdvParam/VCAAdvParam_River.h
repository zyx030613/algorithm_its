#pragma once
#include "VCAEventAdvParamBase.h"

// CLS_VCAAdvParam_River 对话框

class CLS_VCAAdvParam_River : public CLS_VCAEventAdvParamBase
{
	DECLARE_DYNAMIC(CLS_VCAAdvParam_River)

public:
	CLS_VCAAdvParam_River(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAAdvParam_River();

// 对话框数据
	enum { IDD = IDD_DLG_VCAPARAM_ADV_RIVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void UI_UpdateDialog();
	void UI_Update();
	void OnLanguageChanged();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnAdvparamRiverSet();
private:
	void CheckValueLimits();
};
