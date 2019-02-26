#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "../BasePage.h"
// CLS_SerialInfo 对话框

class CLS_SerialInfo : public CDialog
{
	DECLARE_DYNAMIC(CLS_SerialInfo)

public:
	CLS_SerialInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_SerialInfo();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_COM_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboComNo;
	CComboBox m_cboBaudRate;
	CComboBox m_cboParityBit;
	CComboBox m_cboDataBit;
	CEdit m_edtStopBit;
	CComboBox m_cboDevType;
	CEdit m_edtGap;
	CSpinButtonCtrl m_spinGap;
public:	
	int m_iLogonID;
	int m_iComNo;
	inline void InitParam(int _iLogonID, int _iComNO)
	{
		m_iLogonID = _iLogonID;
		m_iComNo = _iComNO;		
	}
	virtual BOOL OnInitDialog();
	void InitWidget();
	void UpdateUI();
	void GetDevTypeName(int _iDevType, string &_strDevName);
	afx_msg void OnBnClickedBtnComSet();	
};

