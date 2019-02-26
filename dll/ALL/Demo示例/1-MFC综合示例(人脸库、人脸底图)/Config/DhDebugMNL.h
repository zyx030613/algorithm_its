#pragma once
#include "afxwin.h"
#include "NetClientTypes.h"

typedef struct __tagAnalogTest
{	
	int iType;
	int iData; 
}AnalogTest;

typedef struct __tagAnalogInfo
{
	char	cUnit[LEN_16];		//单位
	int		iCollectTime;		//采集间隔
	int		iRangeUpLevel;		//量程上限
	int		iRangeUpValue;		//量程上限值
	int		iRangeDownLevel;	//量程下限
	int		iRangeDownValue;	//量程下限值
	int		iAlarmUpLevel;		//报警上限
	int		iAlarmDownLevel;	//报警下限
	int		iDisAlarmUpLevel;	//消警上限
	int		iDisAlarmDownLevel;	//消警下限
}AnalogInfo;

// CLS_DhDebugMNL 对话框

class CLS_DhDebugMNL : public CDialog
{
	DECLARE_DYNAMIC(CLS_DhDebugMNL)

public:
	CLS_DhDebugMNL(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DhDebugMNL();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_DH_DEBUG_MNL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iLogonID;
	int m_iInportNo;
	CSpinButtonCtrl m_spinDelayTime;
	virtual BOOL OnInitDialog();
	BOOL Init(int _iLogonID, int _iInportNo);
	BOOL UpdateDialog();
	afx_msg void OnBnClickedBtnMnlSet();

	BOOL StructToString(AnalogTest* _pSrc,CString& _strDest);
	//BOOL StringToStruct(CString _strSrc,AnalogTest* _pDest);
	BOOL StringToStruct(CString _strSrc,AnalogInfo* _pDest);
};
