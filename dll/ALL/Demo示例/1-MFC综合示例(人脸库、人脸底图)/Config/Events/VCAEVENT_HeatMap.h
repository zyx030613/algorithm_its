#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "VCAEventBasePage.h"

// CLS_VCAEVENT_Running 对话框

class CLS_VCAEVENT_HeatMap : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_HeatMap)

public:
	CLS_VCAEVENT_HeatMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_HeatMap();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_HEATMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UI_UpdateDialogText();
	void UI_UpdateParam();

private:
	CButton m_chkCheckValid;
	CEdit m_edtMinDistance;
	CEdit m_edtMinTime;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;

private:
	int	m_iAreaPointNum;			//划线点数
	CStringArray cstrArrayColor;

public:
	afx_msg void OnBnClickedBtnHeatMapSet();
	afx_msg void OnBnClickedBtnHeatMapDraw();
	afx_msg void OnEnChangeEdtHeatMapMinSize();
	afx_msg void OnEnChangeEdtHeatMapMaxSize();
};

	
	
