#pragma once
#include "afxcmn.h"


typedef struct __tagHumitureTest
{	
	int iType;
	int iTemperature; 
	int iHumidity;
}HumitureTest;

// CLS_DhDebugWSD 对话框

class CLS_DhDebugWSD : public CDialog
{
	DECLARE_DYNAMIC(CLS_DhDebugWSD)

public:
	CLS_DhDebugWSD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DhDebugWSD();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_DH_DEBUG_WSD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	int m_iInportNo;
	CSpinButtonCtrl m_spinDelayTime;
	BOOL UpdateDialog();
public:
	virtual BOOL OnInitDialog();
	BOOL Init(int _iLogonID, int _iInportNo);
	afx_msg void OnBnClickedBtnWsdSet();
	BOOL StructToString(HumitureTest* _pSrc,CString& _strDest);
};
