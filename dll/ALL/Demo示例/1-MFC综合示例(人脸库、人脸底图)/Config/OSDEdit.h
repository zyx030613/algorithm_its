#pragma once
#include "afxwin.h"

// CLS_OSDEdit 对话框

class CLS_OSDEdit : public CDialog
{
	DECLARE_DYNAMIC(CLS_OSDEdit)

public:
	CLS_OSDEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_OSDEdit();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_OSD_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iLogonID;
	int m_iDlgType;		//0添加界面，1编辑界面
	int m_iDevNo;			//设备编号,通道号
	int m_iOSDNo;		//字符叠加编号
	inline void InitOSDParam(int _iDlgFlag, int _iLogonID, int _iDevID, int _iOSDNo)
	{
		m_iLogonID = _iLogonID;
		m_iDlgType = _iDlgFlag;
		m_iDevNo = _iDevID;
		m_iOSDNo = _iOSDNo;
	}
	CEdit m_edtDevName;
	CEdit m_edtDevIP;
	CComboBox m_cboDevCH;
	CComboBox m_cboOSDArea;
	CComboBox m_cboOSDColor;
	virtual BOOL OnInitDialog();
	void InitOSDInfo();
	void UpdateUI();
	CString GetColorStr(int _iColor);
	afx_msg void OnBnClickedBtnOsdSet();
};
