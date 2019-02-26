#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "VCAEventBasePage.h"

// CLS_VCAEVENT_Running �Ի���

class CLS_VCAEVENT_HeatMap : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_HeatMap)

public:
	CLS_VCAEVENT_HeatMap(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_VCAEVENT_HeatMap();

// �Ի�������
	enum { IDD = IDD_DLG_VCAEVENT_HEATMAP };

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
	CButton m_chkCheckValid;
	CEdit m_edtMinDistance;
	CEdit m_edtMinTime;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;

private:
	int	m_iAreaPointNum;			//���ߵ���
	CStringArray cstrArrayColor;

public:
	afx_msg void OnBnClickedBtnHeatMapSet();
	afx_msg void OnBnClickedBtnHeatMapDraw();
	afx_msg void OnEnChangeEdtHeatMapMinSize();
	afx_msg void OnEnChangeEdtHeatMapMaxSize();
};

	
	
