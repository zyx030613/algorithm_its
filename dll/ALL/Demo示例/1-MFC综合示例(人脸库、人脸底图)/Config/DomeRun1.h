#ifndef _DOME_RUN1_PAGE_H_
#define _DOME_RUN1_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "Preview/DeviceControl.h"
#include "Preview/ActionControl.h"
// CLS_DomeRun dialog

class CLS_DomeRun1 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeRun1)

public:
	CLS_DomeRun1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeRun1();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_RUN1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData);
	void UI_UpdateDialogText();
	void UpdateFocusMode();
	void UpdateCruiseInfo();
	void UpdateScanDate();
	void ChangeComboScanState();
	void SetDomeMenu( TDomeParam& _tParam );
	int  GetDomeMenu( TDomeParam& _tParam );
	void DevControl(int _iType, int _iPresetNo);
	bool IsDigistChannel( int _iChannelNO);
	afx_msg void OnCbnSelchangeComboPresetNo();
	afx_msg void OnBnClickedButtonPresetCall();
	afx_msg void OnBnClickedButtonPresetSet();
	afx_msg void OnBnClickedButtonDelPreset();
	afx_msg void OnCbnSelchangeComboCruiseNo();
	afx_msg void OnBnClickedButtonCruiseCall();
	afx_msg void OnBnClickedButtonAddpreset();
	afx_msg void OnBnClickedButtonDelpreset();
	afx_msg void OnCbnSelchangeComboScanNo();
	afx_msg void OnCbnSelchangeComboScanType();
	afx_msg void OnBnClickedButtonScanCall();
	afx_msg void OnBnClickedButtonScanBrodrLeft();
	afx_msg void OnBnClickedButtonScanBroderRight();
	afx_msg void OnCbnSelchangeComboCruiseTime();
	
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboPresetNo;
	CComboBox m_cboFocusMode;
	CComboBox m_cboCruiseNo;
	CEdit m_edtCruiseList;
	CComboBox m_cboPreset;
	CComboBox m_cboScanNo;
	CComboBox m_cboScanType;
	CComboBox m_cboScanSpeed;
	CComboBox m_cboVerStep;
	st_PTZCruise m_ptzCruise;		//自动巡航预置位信息
	int m_iCruiseNum;				//当前巡航点的预置位个数
	CComboBox m_cboCruiseTime;
	CLS_DeviceControl m_tDevCtrl;
	int	m_iCruiseSpeed;		        //自动巡航速度
};

#endif
