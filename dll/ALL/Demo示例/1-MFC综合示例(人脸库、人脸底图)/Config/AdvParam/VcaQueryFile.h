#pragma once


#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"

class CLS_DlgCfgVcaQueryFile : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgCfgVcaQueryFile)

public:
	CLS_DlgCfgVcaQueryFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DlgCfgVcaQueryFile();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_VCA_QUERY_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	void InitUI();

	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);

	int GetVcaTypeList(int* _piList, int _iMaxCount);

	int GetChanList(QueryChanNo* _pList, int _iMaxCount);

	void ShowPage(int _iPageNo, NetFileQueryVca* _pInfo, BOOL _blFirst = FALSE);

	void ShowChanPage(int _iPageNo);

	QueryChanNo m_tQueryChan[MAX_QUERY_LIST_COUNT];
	NetFileQueryVca m_tQueryInfo;
	int	m_iCurPageNo;
	int m_iTotalPage;

	int m_iCurChanPageNo;
	int m_iTotalChanPage;

//控件变量	
public:		
	CComboBox m_cboFileType;
	CDateTimeCtrl m_dtBeg;
	CDateTimeCtrl m_dtEnd;

	CListCtrl m_lstVcaFile;

	CStatic m_stcPageInfo;
	
	//通道号
	CButton m_chkChanAll;
	CButton m_chkChanNo[LEN_32];
	CStatic m_stcChanNo[LEN_32];
	CComboBox m_cboChanPageNo;
	//智能分析类型
	CButton m_chkVcaTypeAll;
	CButton m_chkVcaTypeTrip;
	CButton m_chkVcaTypeDbTrip;
	CButton m_chkVcaTypeBoundary;
	CButton m_chkVcaTypeLoiter;
	CButton m_chkVcaTypePark;
	CButton m_chkVcaTypeRun;
	CButton m_chkVcaTypeStolen;
	CButton m_chkVcaTypeLeft;
	CButton m_chkVcaTypeFace;
	CButton m_chkVcaTypeAlert;
	CButton m_chkVcaTypeLPR;
	CButton m_chkVcaTypeHelmet;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkVcaTypeAll();
	afx_msg void OnBnClickedBtnQuery();
	
	afx_msg void OnBnClickedBtnPageFirst();
	afx_msg void OnBnClickedBtnPagePre();
	afx_msg void OnBnClickedBtnPageNext();
	afx_msg void OnBnClickedBtnPageLast();
	
	afx_msg void OnBnClickedBtnPreChanPage();
	afx_msg void OnBnClickedBtnNextChanPage();
	afx_msg void OnCbnSelchangeCboChanPage();
	afx_msg void OnBnClickedChekChanAll();
};
