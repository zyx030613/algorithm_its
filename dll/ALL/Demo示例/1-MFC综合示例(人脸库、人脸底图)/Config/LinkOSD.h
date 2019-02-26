#pragma once
#include "afxwin.h"
#include "NetClientTypes.h"

// CLS_DlgLinkOsd dialog
typedef struct __tagParamData
{	
	char cIP[LEN_32];
	int iChannelNo;
	int iAreaNo; 
	int iColor;
	int iAlarmInfo;
	int iAlarmTime;
	int iAlarmCustom;
	char cText[LEN_256];
}ParamData;


#define MAX_OSD_CHANNELNUM 64
#define MAX_OSD_BLOCKNUM 16
#define MAX_COLOUR_NUM 5

class CLS_LinkOSD : public CDialog
{
	DECLARE_DYNAMIC(CLS_LinkOSD)

public:
	CLS_LinkOSD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_LinkOSD();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_LINK_OSD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitDlgData();
	CEdit m_edtDevIP;
	CComboBox m_cboOSDCH;
	CComboBox m_cboOSDArea;
	CComboBox m_cboOSDColor;
	CButton m_chkAlarmInfo;
	CButton m_cboAlarmTime;
	CButton m_chkUserDefine;
	CEdit m_edtUserDefine;

	CString m_cstrDevIP;
	CString m_cstrUserDefine;

	void SetDlgInfo(AlarmInLink* _pAlarmInLink);
	void GetDlgInfo(AlarmInLink* _pAlarmInLink);

	BOOL StringToStruct(CString _strSrc,ParamData* _pDest);
	BOOL StructToString(ParamData* _pSrc,CString& _strDest);

};
