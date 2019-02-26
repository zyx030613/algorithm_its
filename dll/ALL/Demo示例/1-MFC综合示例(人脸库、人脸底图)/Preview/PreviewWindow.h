#ifndef _PREVIEW_WINDOW_H
#define _PREVIEW_WINDOW_H

#include "afxwin.h"
#include "../BaseWindow.h"
#include "../VideoView.h"
#include "afxcmn.h"
#include "DeviceControl.h"
// CLS_PreviewWindow dialog

#define MAX_VIDEO_NUM 196
#define TIMER_REVERSE 1

typedef void (*VIDED_CHANGED_NOTIFY)(void* _pVideo,void* _pUserData);

class CLS_PreviewWindow : public CLS_BaseWindow
{
	DECLARE_DYNAMIC(CLS_PreviewWindow)

public:
	CLS_PreviewWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PreviewWindow();

// Dialog Data
	enum { IDD = IDD_DLG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	CLS_VideoView* GetCurrentVideoView();
	CLS_VideoView* GetFreeVideoView();
	void SetVideoChangedNotify(VIDED_CHANGED_NOTIFY _cbkNotify,void* _pUserData);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeComboWindowNum();
	afx_msg void OnCbnSelchangeComboNetdelay();
	afx_msg void OnNMCustomdrawSliderBrightness(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderContrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSaturation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderHue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderVolume(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDefaut();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedChkAudio();
	afx_msg void OnBnClickedChkTalk();
	afx_msg void OnBnClickedChkRecord();
	afx_msg void OnBnClickedBtnSnatch();
	afx_msg void OnBnClickedChkLight();
	afx_msg void OnBnClickedChkPower();
	afx_msg void OnBnClickedChkRain();
	afx_msg void OnBnClickedButtonAssistantOn();
	afx_msg void OnBnClickedButtonAssistantOff();
	afx_msg void OnBnClickedButtonSetPreset();
	afx_msg void OnBnClickedButtonCallPreset();
	afx_msg void OnBnClickedBtnForceIframe();
	afx_msg void OnBnClickedCheckHorAuto();
	afx_msg LRESULT OnTalkEnd(WPARAM wParam, LPARAM lParam);
	static void DecodeYuvNotify(unsigned int _ulID,unsigned char *_cData, int _iLen, const FRAME_INFO *_pFrameInfo, void* _iUser);
	void DecodeYuvNotify(unsigned int _ulID,unsigned char *_cData, int _iLen, const FRAME_INFO *_pFrameInfo);
	CTreeCtrl* GetDeviceTreeCtrl();

	static void __stdcall RawVideoAndAudioNotify(unsigned long _ulID, unsigned char* _ucData, int _iSize, RAWFRAME_INFO* _pRawFrameInfo, void* _pContext);
	void RawVideoAndAudio(unsigned long _ulID, unsigned char* _ucData, int _iSize, RAWFRAME_INFO* _pRawFrameInfo);

private:
	int ShowVideoWindow(int _iRows);
	int ShowMultiplyWindow();
	int ShowSingleWindow();
	int ShowFullWindow();
	void OnVideoViewClicked(int _iID);
	void OnVideoViewDblclk(int _iID);
	void UI_UpdateDialog();
	void UI_UpdateWindow();
	void SetVideoParam();
	void SetAudioVolume();
	void UI_UpdateTalk();
	void TalkNotify(int _iLogonID,int _iTalkStatus);
	void InterTalkNotify(unsigned int _uiConnID);
	void OnRecord(UINT nID);
	CString MakeFileName(int _iType = -1);
	BOOL UI_UpdatePTZ();
	BOOL TransparentControl(int _iAction,int _iAddress,int _iSpeed,int _iPreset);
	BOOL ProtocolControl(int _iAction,int _iParam1,int _iParam2,int _iEPTZ);
	void OnSnatch( UINT nID );
	void OnTalk( UINT nID );
	void ResumeRecord(unsigned int _uiConnID);
	static DWORD WINAPI ThreadInputTalking(LPVOID pParam);

public:
	static HWND s_hWnd;

private:
	VIDED_CHANGED_NOTIFY m_cbkVideoChanged;
	void* m_pUserData;
	CLS_VideoView* m_pVideo[MAX_VIDEO_NUM+1];
	CLS_DeviceControl m_tDevCtrl;
	CComboBox m_cboWindowNum;
	CComboBox m_cboNetDelay;
	CSliderCtrl m_sldBrightness;
	CSliderCtrl m_sldContrast;
	CSliderCtrl m_sldSatuation;
	CSliderCtrl m_sldHue;
	CSliderCtrl m_sldSpeed;
	CSliderCtrl m_sldVolume;
	CSpinButtonCtrl m_spinPreset;
	CEdit m_edtPreset;
	CComboBox m_cboAssistant;
	CToolTipCtrl m_tipCtrl;
	int m_iCurrentVideo;
	int m_iRows;
	int m_iLogonID;
	int m_iChannelNo;
	//ptz control
	int m_iComNo;
	int m_iAddress;
	int m_iWorkMode;
	char m_cDeviceType[64];
	int m_iClickNum;//点击次数； 多窗口0 单窗口1 全屏2	
	HWND m_hReverse;
	CRITICAL_SECTION m_csCriticalSession;

};

#endif