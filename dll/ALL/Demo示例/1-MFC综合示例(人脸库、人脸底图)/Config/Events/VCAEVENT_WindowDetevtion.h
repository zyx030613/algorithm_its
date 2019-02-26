#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "VCAEventBasePage.h"
#include "VideoViewForDrawWindowDetection.h"

#define	MAX_DEV_CHANNEL_NUM			512		//最大通道数

class CLS_VCAEVENT_WindowDetection : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_WindowDetection)

public:
	CLS_VCAEVENT_WindowDetection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEVENT_WindowDetection();

// 对话框数据
	enum { IDD = IDD_DLG_VCAEVENT_WINDOW_DETECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnMainNotify( int _iLogonID,int _wParam, void* _lParam, void*_iUserData );
	void OnLanguageChanged();
	void UI_UpdateDialogText();
	void UI_UpdateParam();
	void UI_ShowPolygonInEdit(VCAWindowDetectionPosInfo* _ptPolygonInfo);

private:
	CComboBox m_cboAreaColor;
	CComboBox m_cboAlarmAreaColor;
	CComboBox m_cboTargetType;
	CButton m_chkShowAlarmRule;
	CButton m_chkShowAlarmStat;
	CButton m_chkShowTargetArea;
	CButton m_chkCheckValid;
	CEdit m_edtMinSize;
	CEdit m_edtMaxSize;

	CLS_VideoViewForDrawWindowDetection* m_pDlgDrawVideoView;
	VCAWindowDetectionPosInfo m_tWinPosInfo;		//当前场景规则的画线参数
	CStringArray m_cstrArrayColor;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnProtectSet();
	afx_msg void OnEnChangeEdtProtectMinSize();
	afx_msg void OnEnChangeEdtProtectMaxSize();
	afx_msg void OnEnChangeEdtWindowDetectionSensibility();
	afx_msg void OnBnClickedBtnWindowDetectionDraw();
};

	
	
