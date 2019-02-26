#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#define  ITS_MERGE_TYPE_ZERO 1 //一张图片合成
#define ITS_MERGE_TYPE_ONE 2 //两张图片合成
#define  ITS_MERGE_TYPE_TWO 3  //三张图片合成
#define ITS_ENABLE_TYPE 6 //交通使能专用类型
// Cls_ItsCompoPic 对话框

class Cls_ItsCompoPic : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsCompoPic)

public:
	Cls_ItsCompoPic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cls_ItsCompoPic();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_COMPO_PIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	BOOL UI_UpdatePic();
	BOOL UI_UpdateCompo();
	BOOL UI_UpdateCutout();
	BOOL UI_UpdateTwo();
	BOOL UI_UpdateOne();
	void UI_UpdatePicRecv();

private:
	int m_iLogonID;
	int m_iChannel;
	void UI_UpdateDialog();
public:
	
	afx_msg void OnBnClickedBtnPicset();
	afx_msg void OnBnClickedBtnComposet();
	afx_msg void OnBnClickedStcCompoPic();
	afx_msg void OnBnClickedBtnCutoutSet();
	afx_msg void OnBnClickedChkPicenable();
	afx_msg void OnBnClickedBtnTwoset();
	afx_msg void OnBnClickedBtnOneset();
private:
	CEdit m_editPicRate;
	CComboBox m_cboOneImage;
	CComboBox m_cboTwoImage;
	CComboBox m_cboThreeImage;
	CComboBox m_cboCutoutType;
	CComboBox m_cboCutoutRange;
	CButton m_btnCompoSet;
	CButton m_btnCutoutSet;
	CButton m_chkPicEnable;
	CButton m_btnOneSet;
	CButton m_btnTwoSet;	
public:
	afx_msg void OnBnClickedBtnPicReceive();
};
