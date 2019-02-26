#pragma once

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

class CLS_DlgCfgFaceLibMng : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgCfgFaceLibMng)

public:
	CLS_DlgCfgFaceLibMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DlgCfgFaceLibMng();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_VCA_FACE_LIB_MNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

//控件变量
public:
	CEdit		m_edtName;
	CEdit		m_edtDescrip;
	CStatic		m_stcValue;
	CComboBox	m_cboDispath;
	CSliderCtrl m_sldReg;
	CListCtrl	m_lstLibInfo;

//
private:
	void UI_UpdataText();
	void UI_Init();
	void UI_UpdataList();
	void UI_UpdateListItem(FaceLibInfo& sLibInfo, int iLibIndex = -1);

public:
	void OnLanguageChanged(int _iLanguage);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnFaceLibAdd();
	afx_msg void OnNMCustomdrawSldFaceLibReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnFaceLibMdy();
	afx_msg void OnBnClickedBtnFaceLibDel();
	afx_msg void OnLvnItemchangedLstFaceLib(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnFaceLibQuery();
};
