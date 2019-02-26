
#pragma once
#include "afxwin.h"
#include "LinkOut.h"
#include "LinkBSF.h"
#include "LinkOSD.h"
#include "NetClientTypes.h"
#include "../include/NVSSDK_INTERFACE.h"
#include "afxcmn.h"
// CLS_LinkDevSetEdit 对话框
#define  DLGNUM		2 

#define ROW_STEP    25


enum enuParamType
{
	enOSD = 1

};

typedef struct
{        
	int iAlarmType;
	char cName[MAX_NAME_LEN + 1];     
}LinkAlarmType;

class CLS_LinkDevSetEdit : public CDialog
{
	DECLARE_DYNAMIC(CLS_LinkDevSetEdit)

public:
	CLS_LinkDevSetEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_LinkDevSetEdit();
// 对话框数据
	enum { IDD = IDD_DLG_CFG_LINK_EDIT };

public:
	int m_iDlgFlag;		//0添加界面，1编辑界面
	int m_iLogonID;
	int m_iDevType;		//联动设置界面编号所属的类型，0:开关量，1:模拟量，2:串口
	int m_iDevNo;		//联动设置界面的编号
	int m_iActionNo;//动作列表中动作编号一列的编号
	bool m_bAlarmTypeFlag;

	inline void InitLinkDevParam(int _iDlgFlag, int _iLogonID, int _iDevType, int _iChNo, int _iActionNo)
	{
		m_iDlgFlag = _iDlgFlag;
		m_iLogonID = _iLogonID;
		m_iDevType = _iDevType;
		m_iDevNo =	_iChNo;
		m_iActionNo = _iActionNo;
	}
	AlarmInLink m_LinkInfo;
	CDialog* m_clsDlg[DLGNUM];
	CLS_LinkOut *m_pclsLinkOut;
	CLS_LinkOSD *m_pclsLinkOsd;
	CLS_LinkBSF* m_pclsLinkBsf;
	CComboBox m_cboAlarmType;
	CComboBox m_cboLinkType;
	CEdit m_edtActionName;
	CComboBox m_cboRecoverType;
	CEdit m_edtLinkTime;
	CSpinButtonCtrl m_spinLinkTime;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL UpdateUI();
	void InitDlg();
	void ShowWidget(int _iLinkType);
	void SetWidgetInfo(int _iLinkType);
	void GetWidgetInfo(int _iLinkType);
	afx_msg void OnBnClickedBtnLinkSure();	
	afx_msg void OnCbnSelchangeCboLinkType();
	void UpdateAlarmType();

	CDialog* m_pDlgLink[DH_ALARM_LINK_TYPE_MAX];

	void UpdateLinkType(int _iType);
	int GetAlarmType(int _iID,LinkAlarmType* _pType,int _iBufLen);

	afx_msg void OnCbnSelchangeCboAlarmType();
};
