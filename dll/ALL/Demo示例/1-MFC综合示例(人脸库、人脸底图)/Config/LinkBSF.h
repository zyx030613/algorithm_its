#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "NetClientTypes.h"

#define  MAX_LINKDEVICE_NUM 128
#define  LINK_DEVICE_STEP 32

enum RecoverType{
	n_RecoverType_None,
	n_RecoverType_Delay,
	n_RecoverType_DisAlarm,
	n_RecoverType_DisAlarm_Delay,
};

#define  MAX_LINKTIME_NUM 5
#define  MAX_LINKTIME_LIMIT 65535
#define  DEFAULT_DELAYTIME 1
#define  PARAM_STEP ';'
#define  PARAM_STEP_ADD ";"
#define  DISAPPEARTIME_NO   -255

// CLS_LinkBSF 对话框

class CLS_LinkBSF : public CDialog
{
	DECLARE_DYNAMIC(CLS_LinkBSF)

public:
	CLS_LinkBSF(int _iLogonID, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_LinkBSF();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_LINK_BSF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitDlgData();
	CListCtrl m_lstLinkDevice;
	CComboBox m_cboAlarmClear;

	void SetDlgInfo(char* _cParam,int _iSize);
	void GetDlgInfo(char* _cParam,int _iSize);
	void UpdateLinkDeviceList();

	void DeviceSetCheck(int _iNo, BOOL _blCheck);
	BOOL DeviceGetCheck(int _iNo);
	void CheckDevice(int _iDevice, int _iShift = 0);

	BOOL GetData(AlarmInLink* _pAlarmInLink);
	void SetData(AlarmInLink* _pAlarmInLink);

	bool CheckValue( int _iNum, int _iStart, int _iEnd, CString _strMsg/* = _T("")*/);
	bool CheckValue( int _iNum, int _iStart, int _iEnd, int _iTitle );
	bool CheckValue( double _dbNum, double _dbStart, double _dbEnd, int _iTitle);

	void SetAlarmTypeFlag(bool _bAlarmTypeFlag);

protected:
	int	 m_iLogonID;	
	bool   m_blFullSet;
};
