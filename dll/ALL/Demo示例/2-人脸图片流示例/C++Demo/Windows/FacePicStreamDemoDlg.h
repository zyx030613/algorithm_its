
// ITSFaceSnapDemoDlg.h : 头文件
//
#include "resource.h"
#include "DlgPicPanel.h"
#include "NetClientTypes.h"
#include <list>
using namespace std;

#pragma once

#define MAX_SNAP_NUM	27
#define MAX_SNAP_FACEPIC_NUM	200000	//小图本地最多存200000张


class CFacePicStreamDemoDlg : public CDialog
{
// 构造
public:
	CFacePicStreamDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

	virtual ~CFacePicStreamDemoDlg();	//析构函数

// 对话框数据
	enum { IDD = IDD_FACEPICSTREAMDEMO_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()

private:
	CString GetSaveFacePicName(FacePicStream* _ptData, int _iFaceIndex, int _iAlaramType=-1);

public:
	afx_msg void OnBnClickedButtonStartRecv();
	afx_msg void OnCbnSelchangeComboSnapNum();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonLogOn();
	afx_msg void OnBnClickedButtonStopRecv();
	afx_msg void OnBnClickedButtonLogOff();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int InitUIInfo(); //初始化界面信息
	int MultiScreen(int _iRows);    //动态创建人脸小图视频框
	int ShowPicWindow(int _iRows);  //界面显示人脸小图数
	int CloseThreadFunction();     //子线程关闭函数
	int InitSDK();					//初始化NVSSDK
	int InitLoglist();				//初始化日志打印
	void StartRecvPicStream();
	void StopRecvPicStream();
	static int __stdcall OnPicStreamNotify(unsigned int _uiRecvID, long _lCommand, void* _pvBuf, int _iBufLen, void* _pvUser);
	void ProcessPicStream(unsigned int _uiRecvID, long _lCommand, void* _pvBuf, int _iBufLen);
	afx_msg void OnBnClickedRadioDirectMode();
	afx_msg void OnBnClickedRadioActiveMode();
	static DWORD WINAPI DealDataThread(void* _pvPara);
	int  CloseThread();
	void DealPicData();
	int ShowPicture(CWnd* _pDlgWindow, int _DataLen, unsigned char* _pucPicData);
	int DealFacePicData(FacePicStream* _ptData);	
	int DealFullPicData(FacePicStream* _ptData);
	int SavePicture(int _DataLen, unsigned char* _pucPicData, CString _strPicName);
	int	DrawBackGround();
	void FreePicData(FacePicStream* _ptData);

private:
	CDlgPicPanel* m_pDlgPicPanel[MAX_SNAP_NUM];
	CStatic m_staticBigPic;
	CComboBox m_cboSnapNum;
	int m_iFaceIndex;
	int m_iSaveFacePicCount;
	HBRUSH       m_brushMainBack;   //背景颜色画刷
	CIPAddressCtrl m_ipaddDevIp;
	CEdit  m_editDevPort;
	CEdit  m_editUserName;
	CEdit  m_editPassword;
	CEdit  m_edtFactoryID;
	CListCtrl m_lstLog;
	HANDLE m_hThread;
	bool   m_bTermiThread;
	CRITICAL_SECTION m_CriticalSec;
	int m_iLogonID;
	unsigned int m_uiRecvID;
	char m_cDevIP[16];
	BOOL m_blISDrawBlack;
	BOOL m_blFullScreen;
	CWnd* m_hParentWnd;	
	RECT m_rcOldWindowRect;
	int m_iConnetMode;
	CButton m_RdoDirectMode;
	CButton m_RdoActiveMode;
	list <FacePicStream*> m_lstPicData;
	bool m_blRecvData;
};



