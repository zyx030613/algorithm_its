#ifndef _AUTO_TEST_PAGE_H_
#define _AUTO_TEST_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_AutoTestPage dialog


#define  CBO_INDEX_TEMPERATURE_REVISE	0    //温度校正

#define  TEMPERATURE_REVISE_DEF			100    //温度校正

class CLS_AutoTestPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AutoTestPage)

public:
	CLS_AutoTestPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AutoTestPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_AUTO_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateDialogText();
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	void InnerAutoTest(int _iCmd, strAutoTest_Para* _pvTestBuf);
	afx_msg void OnBnClickedButtonMultiLanguage();
	afx_msg void OnBnClickedButtonAutoTestAxis();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CButton m_chkEnglish;		//英文
	CButton m_chkChinese;		//中文
	CButton m_chkTraditional;	//繁体
	CButton m_chkKorean;		//韩语
	CButton m_chkSpanish;		//西班牙
	CButton m_chkItalian;		//意大利
	CButton m_chkRussian;		//俄语
	CButton m_chkTurkish;		//土耳其语
	CButton m_chkThai;			//泰语
	CButton m_chkPolish;		//波兰语
	CButton m_chkHebrew;		//希伯来语
	CButton m_chkFrench;		//法语
	CButton m_chkGerman;		//德语
	CEdit m_edtPixels_X;
	CEdit m_edtPixels_Y;
public:
	afx_msg void OnBnClickedBtnAutotest();
	CComboBox m_cboTestItem;
	CEdit m_edtParaOne;
	CEdit m_ParaTwo;
	CEdit m_edtResult;
};

#endif
