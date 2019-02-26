#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "VCAEventBasePage.h"

// CLS_VCAEVENT_Running �Ի���

class CLS_VCAEVENT_Protect : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Protect)

public:
	CLS_VCAEVENT_Protect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_VCAEVENT_Protect();

// �Ի�������
	enum { IDD = IDD_DLG_VCAEVENT_PROTECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	void UI_UpdateDialogText();
	void UI_UpdateParam();

private:
	CComboBox m_cboAreaColor;
	CComboBox m_cboAlarmAreaColor;
	CComboBox m_cboTargetType;
	CComboBox m_cboCheckType;
	CComboBox m_cboLimitDirection;
	CButton m_chkShowAlarmRule;
	CButton m_chkShowAlarmStat;
	CButton m_chkShowTargetArea;
	CButton m_chkCheckValid;
	CEdit m_edtMinDistance;
	CEdit m_edtMinTime;
	CEdit m_edtResortTime;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;
	CEdit m_edtLimitAngle;

private:
	int	m_iAreaPointNum;			//���ߵ���
	CStringArray cstrArrayColor;

public:
	afx_msg void OnBnClickedBtnProtectSet();
	afx_msg void OnBnClickedBtnProtectDraw();
	afx_msg void OnEnChangeEdtProtectMinSize();
	afx_msg void OnEnChangeEdtProtectMaxSize();
};

	
	
