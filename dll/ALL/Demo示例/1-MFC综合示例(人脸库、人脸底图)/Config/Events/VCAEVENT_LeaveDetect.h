#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"

// CLS_VCAEVENT_LeaveDetect dialog

class CLS_VCAEVENT_LeaveDetect : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_LeaveDetect)

public:
	CLS_VCAEVENT_LeaveDetect(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_LeaveDetect();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_LEAVE_DETECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CButton m_chkDisplayRule;
	CButton m_chkDiaplayState;
	CEdit m_edtAreaNum;
	CEdit m_edtArea1PointNum;
	CEdit m_edtArea1Points;
	CEdit m_edtArea2PointNum;
	CEdit m_edtArea2Points;
	CEdit m_edtArea3PointNum;
	CEdit m_edtArea3Points;
	CEdit m_edtArea4PointNum;
	CEdit m_edtArea4Points;
	CEdit m_edtLeaveAlarmTime;
	CEdit m_edtRuturnClearAlarmTime;
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonArea1Draw();
	afx_msg void OnBnClickedButtonArea2Draw();
	afx_msg void OnBnClickedButtonArea3Draw();
	afx_msg void OnBnClickedButtonArea4Draw();
	afx_msg void OnBnClickedButtonLeavedetectSet();
	void UpdatePageUI();
	void UpdateUIText();
	void CleanText();
	
private:
	CComboBox m_cboAreaColor;
	CComboBox m_cboAlarmAreaColor;
public:
	afx_msg void OnBnClickedButtonLeavedetectStop();
	afx_msg void OnBnClickedButtonLeavedetectStart();
};
