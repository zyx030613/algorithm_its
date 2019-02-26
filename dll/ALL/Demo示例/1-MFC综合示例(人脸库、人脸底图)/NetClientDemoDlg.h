#ifndef _NETCLIENTDEMODLG_H
#define _NETCLIENTDEMODLG_H

#include "BaseWindow.h"
#include "Common/CommonFun.h"
#include "Common/Ini.h"

enum WINDOW_INDEX
{
	WINDOW_MIN = 0,
	WINDOW_PREVIEW = WINDOW_MIN,
	WINDOW_CONFIG,
	WINDOW_PLAYBACK,
	WINDOW_MANAGE,
	WINDOW_MAX
};

enum ICON_INDEXT
{
	ICON_MIN = 0,
	ICON_NOT_LOGON = ICON_MIN,
	ICON_LOGON_SUCCESS,
	ICON_ERROR_ORDER,
	ICON_NOT_CONNECT,
	ICON_CONNECT_SUCCESS,
	ICON_ERROR_DATANET,
	ICON_MAX
};

#define TIMER_DATETIME	1		//timer for system parameter,cpu

// CNetClientDemoDlg dialog
class CNetClientDemoDlg : public CDialog
{
// Construction
public:
	CNetClientDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DLG_MAIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM _wParam,LPARAM _lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	friend void OnVideoChanged(void* _pVideo,void* _pUserData);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMRClickTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnMainMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnParamChangeMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAlarmMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTvnSelchangedTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadioLocalLog();
	afx_msg void OnBnClickedRadioAlarmInfo();
	afx_msg void OnBnClickedBtnLogClear();
	afx_msg void OnCbnSelchangeComboLanguage();
	afx_msg void OnBnClickedBtnLogConfig();
	afx_msg void OnHdnItemclickListLogLocal(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnLogSave();
	afx_msg void OnBnClickedBtnLogTest();
	afx_msg LRESULT OnMainNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnParamChangeNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAlarmNotify(WPARAM wParam, LPARAM lParam);
#ifdef SDK_X64
	static void MainNotify(int _ulLogonID, long _iWparam, void* _plParam,void* _iUser); 
#else
	static void MainNotify(int _ulLogonID, long _iWparam, void* _iParam,void* _iUser); 
#endif
	static void MainNotify_SynchronousMode(int _ulLogonID, int _iWparam, void* _pvLParam,void* _pvUser); 

	static void AlarmNotify(int _ulLogonID, int _iChan, int _iAlarmState,ALARMTYPE _iAlarmType,void* _iUser);
	static void ParamChangeNotify(int _ulLogonID, int _iChan, PARATYPE _iParaType,STR_Para* _strPara,void* _iUser);
	static void ComRecvNotify(int _ulLogonID, char *_cData, int _iLen,int _iComNo,void* _iUser); 
	static void ProxyNotify(int _iLogonID,int _iCmdKey, char* _cData,  int _iLen,void* _iUser);
	CTreeCtrl* GetDeviceTreeCtrl();
	void OnLogoffDevice(int _iLogonID);

private:
	int ShowBaseWindow(int _iIndex);
	void UI_UpdateDateTime();
	void UI_UpdateDeviceInfo(PDEVICE_INFO _pDevice);
	void UI_UpdateDemoVersion();
	void UI_UpdateDialog(int _iLanguge);
	void OnAddDevice();
	void OnAddActiveDevice();
	void OnDeleteDevice();
	void OnLogon();
	void OnLogoff();
	void OnConnect(UINT _uiID);
	void OnDisconnect();
	int SDKInit();
	int SetComDataShow();
	void LogonNotify(int _iLogonID,int _iStatus);
	void VideoArrive(int _iLogonID,int _iChannel,int _iStream);
	void ErrorOrder(int _iLogonID);
	void ErrorDataNet(unsigned int _uConnID);
	void AddAlarmInfo(int _iLogonID,int _iChannel, int _iAlarmType, int _iAlarmState);
	int ChangeChannel(int _iLogonID,int _iChannelNo = 0,int _iStreamNo = 0);
	int ChangeChannel(HTREEITEM _hItem = NULL);
	int ChangeLanguage(int _iLanguage);
	void* GetFreeVideoView();
	int MakeChannel(int _iChannelNo,int _iStreamNo,unsigned int* _puChannel);
	int AnalyzeChannel(unsigned int _uChannel,int* _piChannelNo,int* _piStreamNo);
	int AddChannelItem(int _iChannelNo,int _iChannelType,HTREEITEM _hParent);
	int StretchLogCtrl(BOOL _bStretch);
	void SaveDevice();
	void LoadDevice();
	void PromptLastError(int _iLogonID,int _iChannel, int _iErrorID);
	void SetSdkWorMode();

private:
	CLS_BaseWindow* m_pWindow[WINDOW_MAX];
	CLS_BaseWindow* m_pCurrent;
	CListCtrl m_lvLocalLog;
	CListCtrl m_lvAlarmLog;
	CTreeCtrl m_tvDevice;
	CImageList m_lstImage;	
	CTabCtrl m_tabMain;
	CComboBox m_cboLanguage;
	BOOL m_bLogCtrlStretched;
	BOOL m_bFlagThreeStream;
	int  m_iSDKWorkMode;
};

#endif
