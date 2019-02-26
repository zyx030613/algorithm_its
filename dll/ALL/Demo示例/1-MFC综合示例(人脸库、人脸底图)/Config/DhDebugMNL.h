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
	char	cUnit[LEN_16];		//��λ
	int		iCollectTime;		//�ɼ����
	int		iRangeUpLevel;		//��������
	int		iRangeUpValue;		//��������ֵ
	int		iRangeDownLevel;	//��������
	int		iRangeDownValue;	//��������ֵ
	int		iAlarmUpLevel;		//��������
	int		iAlarmDownLevel;	//��������
	int		iDisAlarmUpLevel;	//��������
	int		iDisAlarmDownLevel;	//��������
}AnalogInfo;

// CLS_DhDebugMNL �Ի���

class CLS_DhDebugMNL : public CDialog
{
	DECLARE_DYNAMIC(CLS_DhDebugMNL)

public:
	CLS_DhDebugMNL(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_DhDebugMNL();

// �Ի�������
	enum { IDD = IDD_DLG_CFG_DH_DEBUG_MNL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
