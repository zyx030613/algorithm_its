#pragma once
#include "../BasePage.h"
#include "afxwin.h"

#define ITS_CAR_CHECK				1
#define ITS_LOOP					2
#define ITS_TEMPRETURE				3
#define ITS_SIGNAL_CHECK			4

#define ITS_ONLINE					0
#define ITS_OFFLINE					1
#define ITS_ERR						2

#define ITS_SYNC_FALSE				0
#define ITS_SYNC_TRUE				1
#define ITS_RED_LIGHT_NUM_MAX		8

#define MAX_ITS_LOOP_NUM			10			//LOOP 0~9

// Cls_ItsStateQuery 对话框

class Cls_ItsStateQuery : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsStateQuery)

public:
	Cls_ItsStateQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cls_ItsStateQuery();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_STATE_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	int m_iChannelNo;

public:
	virtual BOOL OnInitDialog();
	CStatic m_gpStatis;
	CStatic m_gpCameraStatis;
	CStatic m_gpSignalStatis;
	CStatic m_gpCarStatis;
	CStatic m_stcCameraTem;
	CStatic m_stcTemValue;
	CStatic m_stcSignalStatis;
	CStatic m_stcSignalValue;
	CButton m_btnUpdateSigSta;
	CButton m_btnUpdateCamTem;
	CStatic m_stcCarStatis;
	CStatic m_stcCarStaValue;
	CStatic m_stcRollStatis;
	CEdit m_edtRollValue;
	CButton m_btnUpdateCarSta;
	CListBox m_listRedLightSync;
	CButton m_btnUpdateRoll;
	CListBox m_listLoopTriggerMsg;
	CButton m_chkLoopSerialNum[MAX_ITS_LOOP_NUM];

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnUpdateCamtem();
	afx_msg void OnBnClickedBtnPicQuity();
	afx_msg void OnBnClickedBtnRedLight();
	afx_msg void OnBnClickedBtnUpdateSigsta();
	afx_msg void OnBnClickedBtnUpdateCarStatis();
	afx_msg void OnBnClickedBtnUpdateRoll();
	afx_msg void OnBnClickedBtnShowLoopMsg();

public:
	virtual void OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser );
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);
	void SetState(int _ID, int iState);
	void OnChannelChanged( int _iLogonID,int _iChannelNo, int _iStreamNo);
	void OnLanguageChanged( int _iLanguage);
	void UI_UpdateDialog();
	void UI_UpdateLoopTriggerMsg(int iLoopId);


};
