#pragma once
#include "../BasePage.h"
#include "afxwin.h"

// CLS_ItsAdvanceConf2 对话框

class CLS_ItsAdvanceConf2 :  public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsAdvanceConf2)

public:
	CLS_ItsAdvanceConf2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ItsAdvanceConf2();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_ADVANCE_CONF2 };
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateAdvance();
	BOOL UI_UpdateAlgType();
public:
	afx_msg void OnBnClickedBtnAdvanceSet();
private:
	int m_iLogonID;
	int m_iChannel;
	CComboBox m_cboAlgType;
	CEdit m_edtChannelID;
	CComboBox m_cboAlgoType;
	CComboBox m_cboStartCheck;
	CComboBox m_cboParamEnable;
	CEdit m_edtCarWidth;
	CComboBox m_cboFrameType;
	CComboBox m_cboReliability;
	CEdit m_edtWidth;
	CEdit m_edtHighth;
	CComboBox m_cboModelProp;
	CEdit m_edtMaxSize;
	CEdit m_edtMinSize;
	CEdit m_edtBinarization;
	CComboBox m_cboAnalysisFrame;
	CComboBox m_cboModelAngle;	
	CEdit m_edtImageProp;
public:
	afx_msg void OnBnClickedBtnAlgtypeSet();
};
