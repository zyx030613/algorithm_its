#ifndef _CHAN_CHECK_PAGE_H_
#define _CHAN_CHECK_PAGE_H_
#include "afxwin.h"
#include "../BasePage.h"

#define MAX_CHAN_PAGE	64
#define MAX_PAGE_NUM	3

class CLS_ChanCheck : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ChanCheck)

public:
	CLS_ChanCheck(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ChanCheck();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_CHANNEL_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
//控件变量
public:
	CStatic m_stcChanNo[MAX_CHAN_PAGE];
	CButton m_chkChan[MAX_CHAN_PAGE];
	CButton m_chkSelALl;
	CComboBox m_cboPage;

	int m_iCurrentPage;
	int m_iChanNum;
	int	m_iEnable[MAX_BITSET_COUNT];
public:
	void InitData(int _iChanNum, int* _iEnable);
	void OnCheckAll(BOOL _blChk);
	void OnShowPage(int _iPage);//0开始表示第一页
	void OnChanCheck();
	void GetChanValue(int * _iEnable);
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedChkSelectAll();
	afx_msg void OnCbnSelchangeCboChPage();
	afx_msg void OnBnClickedBtnFtontPage();
	afx_msg void OnBnClickedBtnNextPage();
	afx_msg void OnBnClickedChkChan(UINT _uiID);
};

#endif
