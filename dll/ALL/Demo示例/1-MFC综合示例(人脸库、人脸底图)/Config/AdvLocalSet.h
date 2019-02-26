
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "../BasePage.h"

#define NORMAL_USE			0
#define RIVER_USE			1

#define VCAFPGA_RESERVR 0
#define VCAFPGA_TEMPERATURE 1
#define VCAFPGA_TIME 2

class CLS_AdvLocalSet : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AdvLocalSet)

public:
	CLS_AdvLocalSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_AdvLocalSet();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_ADVANCE_LOCAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
//控件变量
public:
	CComboBox m_cboLogonMode;
	CComboBox m_cboDemoUseRule;

//成员变量
private:
	int m_iLogonID;
	int m_iChannelNo;

//功能函数
public:
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData);

	void UI_UpdateDialog();
	void LoadSdkWorkMode();
	void LoadDemoUseRule();

	void UI_UpdateVcaFpga();
	void UI_UpdateVcaFpgaQueryInfo();
//系统消息
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnLogonMode();
	afx_msg void OnBnClickedButtonSetDemoUseRule();
	
	CComboBox m_cboVcaFpgaQueryInfo;
	CComboBox m_cboVcaFpga;
	afx_msg void OnBnClickedBtnVcafpgaSet();
	afx_msg void OnBnClickedBtnVcafpgaQueryinfoSet();
	afx_msg void OnCbnSelchangeCboVcafpgaQueryinfo();
	afx_msg void OnCbnSelchangeCboVcafpga();
};
