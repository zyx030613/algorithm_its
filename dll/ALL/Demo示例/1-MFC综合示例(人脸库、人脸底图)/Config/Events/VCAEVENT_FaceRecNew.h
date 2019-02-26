#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_VCAEVENT_FaceRecNew 对话框

class CLS_VCAEVENT_FaceRecNew : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_FaceRecNew)

public:
	CLS_VCAEVENT_FaceRecNew(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_FaceRecNew();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_FACEREC_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UpdateUIText();
	void UpdatePageUI();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnFacerecNewSet();
	afx_msg void OnBnClickedBtnFacerecNewPolygonAreaDraw();
	afx_msg void OnNMCustomdrawSldFacerecNewMaxSize(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSldFacerecNewMinSize(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CButton m_chkEnable;
	CEdit m_edtMaxSize;
	CEdit m_edtMinSize;
	CComboBox m_cboAlgoLevel;
	CComboBox m_cboSensitivity;
	CComboBox m_cboPicScal;
	CEdit m_edtSnapSpace;
	CComboBox m_cboSnapTimes;
	CComboBox m_cboPolygonPointNum;
	CEdit m_edtPolygonArea;
	CSliderCtrl m_sldMaxSize;
	CSliderCtrl m_sldMinSize;
	CButton m_chkTargetBox;
};
