#pragma once
#include "afxwin.h"
#include "NetClientTypes.h"

// CLS_LinkOut 对话框
#define MAX_CHANNELS 16


class CLS_LinkOut : public CDialog
{
	DECLARE_DYNAMIC(CLS_LinkOut)

public:
	CLS_LinkOut(int _iLogonID, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_LinkOut();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_LINK_OUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_chkSelAll;
	CButton m_chkCH[16];

	void SetDlgInfo(char* _cParam,int _iSize);
	void GetDlgInfo(char* _cParam,int _iSize);

	void SetData(AlarmInLink* _pAlarmInLink);
	BOOL GetData(AlarmInLink* _pAlarmInLink);

	afx_msg void OnBnClickedChkSelectAll();
	afx_msg void OnBnClickedChkChannel(UINT _uiID);	

protected:
	int	 m_iLogonID;	
};
