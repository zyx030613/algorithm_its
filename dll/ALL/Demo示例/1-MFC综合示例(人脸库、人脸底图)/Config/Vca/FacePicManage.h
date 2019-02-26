#pragma once


#include "../BasePage.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

class CLS_DlgCfgFacePicMng : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgCfgFacePicMng)

public:
	CLS_DlgCfgFacePicMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DlgCfgFacePicMng();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_VCA_FACE_PIC_MNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

//控件变量
public:
	CEdit			m_edtName;	
	CEdit			m_edtCarNum;
	CEdit			m_edtPicPath;
	CStatic			m_stcPageNo;
	CComboBox 		m_cboLibKey;
	CComboBox 		m_cboSex;
	CComboBox 		m_cboNation;
	CComboBox 		m_cboProvience;
	CComboBox 		m_cboCity;
	CComboBox 		m_cboCardType;
	CComboBox 		m_cboModeState;
	CComboBox 		m_cboPageNo;
	CComboBox		m_cboModeType;
	CStatic			m_stcProcess;
	CListCtrl 		m_lstFacePic;
	CDateTimeCtrl	m_dtBirthBeg;
	CDateTimeCtrl	m_dtBirthEnd;
	CProgressCtrl	m_proModeProcess;

private:
	FaceQuery		m_tQueryInfo;
	int				m_iCurPage;
	int				m_iTolalPage;
	FaceQueryResult m_tQueryResult[FACE_MAX_PAGE_COUNT];
	FaceModeling	m_tModeInfo;

	void UI_UpdataText();
	void UI_Init();
	void UI_Updata();
	void UI_UpdateListItem(FaceInfo& _tInfo, int iLibIndex=-1);
	void ShowPage(int _iPageNo);
	bool SetVcaStatue(int _iStatus);

public:
	void OnLanguageChanged(int _iLanguage);
	void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnFacePicLibQuery();
	afx_msg void OnBnClickedBtnFacePicQuery();
	afx_msg void OnBnClickedBtnFacePicPageBeg();
	afx_msg void OnBnClickedBtnFacePicPagePre();
	afx_msg void OnBnClickedBtnFacePicPageNxt();
	afx_msg void OnBnClickedBtnFacePicPageEnd();
	afx_msg void OnCbnSelchangeCboFacePicPageNo();
	afx_msg void OnBnClickedBtnFacePicPath();
	afx_msg void OnBnClickedBtnFacePicAdd();
	afx_msg void OnBnClickedBtnFacePicMdy();
	afx_msg void OnBnClickedBtnFacePicDel();
	afx_msg void OnNMClickLstFacePicInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnFacePicMode();
	afx_msg void OnBnClickedBtnFacePicModeStop();
	afx_msg LRESULT	OnModeFinish(WPARAM wParam, LPARAM lParam);		
};
