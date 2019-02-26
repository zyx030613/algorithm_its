#pragma once
#include "BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_StorageSmartPage 对话框

class CLS_StorageSmartPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_StorageSmartPage)

public:
	CLS_StorageSmartPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_StorageSmartPage();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_STORAGE_SMART };
//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboSmartDisk;
	CListCtrl m_lstSmartDisk;
	CButton m_chkSmartEnable;
public:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	int m_iSmartDiskSel;
	
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);

	void InitDlgData();
	void UI_UpdateSurface();
	void UI_UpdateSmartInfo(DiskSmartMsg* _pstSmartMsg);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeCboSmartDisk();
	afx_msg void OnBnClickedChkSmartDiskEnable();
	CButton m_chkSmartAssess;
	afx_msg void OnBnClickedChkSmartDiskAssess();
};
