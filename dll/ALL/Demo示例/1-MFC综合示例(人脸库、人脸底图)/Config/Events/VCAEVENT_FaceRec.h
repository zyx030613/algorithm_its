#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
// CLS_VCAEVENT_FaceRec dialog

class CLS_VCAEVENT_FaceRec : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_FaceRec)

public:
	CLS_VCAEVENT_FaceRec(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_FaceRec();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_FACEREC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_chkFaceRecValid;
	CComboBox m_cboColor;
	CComboBox m_cboAlarmColor;
	CEdit m_edtPointNum;
	CEdit m_edtPoints;
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonFaceRecset();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void CleanText();

	void OnLanguageChanged();
private:
	void UpdatePageUI();
	void UpdateUIText();
	//void GetPolyFromString(CString _strPoints, int _iPointNum, vca_TPolygon& _stPoly);
public:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayState;
	afx_msg void OnBnClickedButtonFacerecstop();
	afx_msg void OnBnClickedButtonFacerecstart();
};
