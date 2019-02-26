#ifndef _DONGHUAN_SET_PAGE_H_
#define _DONGHUAN_SET_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include <string>

#define COM_NUM 10
#define SCHEDULE_NUM 16
#define HOSTINDEX                    0   //��������������

enum ComDevType
{
	n_ComDev_Tem = 1		//��ʪ��
};

enum enu_ComType
{
	enu_485 = 0,
	enu_232 = 1,
	enu_422 = 2
};

enum enu_DlgStyle
{
	enu_Add  = 0,	//���
	enu_Edit = 1	//�༭
};

typedef struct __tagSwitchInfo
{	
	int m_iMode;					//ģʽ���� 
}StrctSwicth;


typedef struct __tagSimuInfo
{
	char		m_cSimuUnit[LEN_16];	//��λ
	int			m_iCollectTime;			//�ɼ����
	double	    m_dbRangeUpLevel;		//��������
	double		m_dbRangeUpValue;		//��������ֵ
	double		m_dbRangeDownLevel;		//��������
	double		m_dbRangeDownValue;		//��������ֵ
	double		m_dbAlarmUpLevel;		//��������
	double		m_dbAlarmDownLevel;		//��������
	double		m_dbDisAlarmUpLevel;	//��������
	double		m_dbDisAlarmDownLevel;	//��������
}StrctSimu;


typedef struct __tagTemInfo
{
	double	   m_dbTemAlarmUpLevel;		//�¶ȱ�������
	double	   m_dbTemAlarmDownLevel;	//�¶ȱ�������
	double	   m_dbTemDisAlarmUpLevel;	//�¶���������
	double	   m_dbTemDisAlarmDownLevel;//�¶���������
	double	   m_dbHulAlarmUpLevel;		//ʪ�ȱ�������
	double	   m_dbHulAlarmDownLevel;	//ʪ�ȱ�������
	double	   m_dbHulDisAlarmUpLevel;	//ʪ����������
	double	   m_dbHulDisAlarmDownLevel;//ʪ����������
}StrctTem;

typedef struct __tagComInfo
{
	int		   m_iAddr;					//��ַ
	int		   m_iDevType;				//�豸��ַ
	StrctTem   m_strctTem;				//��ʪ��
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
	vector<int> m_vecExtDevNo;	//��¼�Ѿ����ڵı��
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
