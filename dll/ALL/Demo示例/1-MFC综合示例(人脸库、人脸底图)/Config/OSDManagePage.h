#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "OSDEdit.h"
#include "..\BasePage.h"
#include "..\Common\CommonFun.h"

class  CLS_OSDManagePage : public CLS_BasePage
{
	DECLARE_DYNAMIC( CLS_OSDManagePage)

public:
	 CLS_OSDManagePage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_OSDManagePage();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_OSD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iLogonID;
	CListCtrl m_lstOSDInfo;
	CComboBox m_cboOverlayType;
	CLS_OSDEdit *m_pclsOSDEdit;
	virtual BOOL OnInitDialog();
	void OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo);
	BOOL UpdateUI();
	BOOL UpdateInputList();
	afx_msg void OnCbnSelchangeCboOsdNum();
	void UpdateOSDInfo(int _iID,int _iOsdNo);
	afx_msg void OnBnClickedBtnOsdAdd();
	afx_msg void OnNMClickLstOsd(NMHDR *pNMHDR, LRESULT *pResult);
	int GetFreeOsdNo(int iDevNo);
	virtual void OnLanguageChanged(int _iLanguage);
};
