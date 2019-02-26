#pragma once
#include "VCAEventBasePage.h"
#include "afxwin.h"


// CLS_VCAEVENT_Lisence 对话框

class CLS_VCAEVENT_Lisence : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Lisence)

public:
	CLS_VCAEVENT_Lisence(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_Lisence();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_LIENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboFirstChar;
	CComboBox m_cboFirstLetter;
	CSliderCtrl m_sldVLoopSensitivity;

	CStringArray m_arrayProvince;//省简称串组

	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnLisenceSet();
	afx_msg void OnBnClickedBtnLisenceDraw();
	CEdit m_edtLisenceAreaPoints;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
