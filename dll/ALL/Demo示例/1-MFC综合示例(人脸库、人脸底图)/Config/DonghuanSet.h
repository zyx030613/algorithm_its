#ifndef _DONGHUAN_SET_PAGE_H_
#define _DONGHUAN_SET_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include <string>

#define COM_NUM 10
#define SCHEDULE_NUM 16
#define HOSTINDEX                    0   //报警主机索引号

enum ComDevType
{
	n_ComDev_Tem = 1		//温湿度
};

enum enu_ComType
{
	enu_485 = 0,
	enu_232 = 1,
	enu_422 = 2
};

enum enu_DlgStyle
{
	enu_Add  = 0,	//添加
	enu_Edit = 1	//编辑
};

typedef struct __tagSwitchInfo
{	
	int m_iMode;					//模式设置 
}StrctSwicth;


typedef struct __tagSimuInfo
{
	char		m_cSimuUnit[LEN_16];	//单位
	int			m_iCollectTime;			//采集间隔
	double	    m_dbRangeUpLevel;		//量程上限
	double		m_dbRangeUpValue;		//量程上限值
	double		m_dbRangeDownLevel;		//量程下限
	double		m_dbRangeDownValue;		//量程下限值
	double		m_dbAlarmUpLevel;		//报警上限
	double		m_dbAlarmDownLevel;		//报警下限
	double		m_dbDisAlarmUpLevel;	//消警上限
	double		m_dbDisAlarmDownLevel;	//消警下限
}StrctSimu;


typedef struct __tagTemInfo
{
	double	   m_dbTemAlarmUpLevel;		//温度报警上限
	double	   m_dbTemAlarmDownLevel;	//温度报警下限
	double	   m_dbTemDisAlarmUpLevel;	//温度消警上限
	double	   m_dbTemDisAlarmDownLevel;//温度消警下限
	double	   m_dbHulAlarmUpLevel;		//湿度报警上限
	double	   m_dbHulAlarmDownLevel;	//湿度报警下限
	double	   m_dbHulDisAlarmUpLevel;	//湿度消警上限
	double	   m_dbHulDisAlarmDownLevel;//湿度消警下限
}StrctTem;

typedef struct __tagComInfo
{
	int		   m_iAddr;					//地址
	int		   m_iDevType;				//设备地址
	StrctTem   m_strctTem;				//温湿度
}StrctCom;


// CDonghuanSet dialog

class CLS_DonghuanSet : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DonghuanSet)

public:
	CLS_DonghuanSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DonghuanSet();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DONGHUAN_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UI_UpdateDialogText();
	void UI_UpdateSDKInfo();
	void UpdateListInfo(int _iAlarmINo);
	void UpdateItemInfo(int _iChlNo, AlarmInConfig* _pAlarmInfo, int _iEnable);
	void DeleteComItem(int _iChlNo, AlarmInConfig* _pAlarmInfo);
	void UpdateStoreIntervalTime();
	void UpdateAlarmReciveServer();
	void GetDevUpdateInfo(AlarmInConfig* _pAlarmInfo, int _iEnable, string& _strDevName
		, string& _strScheduleName, string& _strEnable);
	void GetComInfo(int _iComNo, string& _strComName);
	void OperateInfo(int _iPos);
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
public:
	afx_msg void OnBnClickedButtonDonghuanAdd();
private:
	CListCtrl m_lstPowerDevInfo;
	CEdit m_edtIntervelTime;
	int		m_iSelectIndex;

//	CLS_PEDevSimuEdit* m_PeDevSimuEdit;
public:
	afx_msg void OnBnClickedButtonIntervalTimeSet();
	afx_msg void OnNMClickListDonghuanList(NMHDR *pNMHDR, LRESULT *pResult);
	vector<int> m_vecExtDevNo;	//记录已经存在的编号
	void	GetComTypeLastName(int _iComNo, string& _strLastComName);
	void	GetComTypeFirstName(int _iComNo, string& _strFirstName);


	BOOL	StructToString(StrctSwicth* _strctSrc, CString& _cstrDest);
	BOOL	StructToString(StrctSimu* _strctSrc, CString& _cstrDest);
	BOOL	StructToString(StrctCom* _strctSrc, CString& _cstrDest);
	BOOL	StringToStruct(CString _cstrSrc,StrctSwicth* _strctDest);
	BOOL	StringToStruct(CString _cstrSrc,StrctSimu* _strctDest);
	BOOL	StringToStruct(CString _cstrSrc,StrctCom* _strctDest);

	afx_msg void OnBnClickedBtnAlarmReceiveSave();
private:
	CEdit m_edtIP;
	CEdit m_edtPort;

};

#endif
