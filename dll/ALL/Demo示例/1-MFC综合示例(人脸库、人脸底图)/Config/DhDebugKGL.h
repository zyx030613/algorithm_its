#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "..\\Include\\NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;

// CLS_DhDebugKGL �Ի���

typedef struct __tagSwitchTest
{	
	int iType;
	int iState; 
}SwitchTest;


class CLS_DhDebugKGL : public CDialog
{
	DECLARE_DYNAMIC(CLS_DhDebugKGL)

public:
	CLS_DhDebugKGL(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_DhDebugKGL();

// �Ի�������
	enum { IDD = IDD_DLG_CFG_DH_DEBUG_KGL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iLogonID;
	int m_iInportNo;
	CComboBox m_cboInportState;
	CSpinButtonCtrl m_spinDelayTime;
	virtual BOOL OnInitDialog();
	BOOL Init(int _iLogonID, int _iInportNo);
	BOOL UpdateDialog();
	afx_msg void OnBnClickedBtnSwitchSet();

	BOOL StructToString(SwitchTest* _pSrc,CString& _strDest);
	BOOL StringToStruct(CString _strSrc,SwitchTest* _pDest);

};
