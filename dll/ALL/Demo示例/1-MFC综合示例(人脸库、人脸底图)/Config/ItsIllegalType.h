#pragma once
#include "../BasePage.h"
#include "afxwin.h"

#define ILLEAGLE_ID_NUMBER  16    //违法ID的数量
#define MAX_PRIORITY		100   //优先等级
#define LANE_ID				3	  //车道号
#define ILLEAGLE_NUMBER		16	  //违法代码
// Cls_ItsIllegalTppe 对话框

class Cls_ItsIllegalTppe : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsIllegalTppe)

public:
	Cls_ItsIllegalTppe(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cls_ItsIllegalTppe();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_ILLEGAL_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnIllegaiSet();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	void UI_UpdateNumber();
	BOOL UI_UpdateIllegal();
private:
	int m_iLogonID;
	int m_iChannel;
	CEdit m_editIllegalName;
	CComboBox m_cboIllegalID;
	CComboBox m_cboPriority;
public:
	CStatic m_stcIlleagleNumber;
	CComboBox m_cboIlleagleNumber;
	CStatic m_stcLaneId;
	CComboBox m_cobLaneId;
	//afx_msg void OnCbnSelchangeCboLaneId();
	afx_msg void OnCbnSelchangeCboIlleagleNumber();
	afx_msg void OnCbnSelchangeCboLaneId();
};
