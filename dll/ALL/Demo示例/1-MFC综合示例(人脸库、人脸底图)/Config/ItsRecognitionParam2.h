#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#define ITS_TYPE_BELTCHECK 9
#define ITS_TYPE_BRANDRECO 8
#define  ITS_TYPE_COFACE_CHECK 11
#define  ITS_TYPE_MAINFACE_CHECK 10
#define  ITS_TYPE_TYPECHECK 7



// CLS_ItsRecognitionParam2 对话框

class CLS_ItsRecognitionParam2 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ItsRecognitionParam2)

public:
	CLS_ItsRecognitionParam2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ItsRecognitionParam2();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_RECOPARAM_2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL UI_UpdateBrandReco();
	BOOL UI_UpdateBeltReco();
	BOOL UI_UpdateMainFaceCheck();
	BOOL UI_UpdateCoFaceCheck();
	BOOL UI_UpdateCarTypeCheck();
	BOOL UI_UpdateReco();
	BOOL UI_UpdatePlateNumber();
	void UI_UpdateFilterPlate();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	int m_iLogonID;
	int m_iChannel;
	void UI_UpdateDialog();
	CComboBox m_cboBrandReco;
	CComboBox m_cboBeltCheck;
	CComboBox m_cboMainFaceCheck;
	CComboBox m_cboCoFaceCheck;
	CComboBox m_cboTypeCheck;
	CEdit m_edtMaxPlateNum;
	CEdit m_edtMaxPlateWTH;
	CEdit m_edtPicThreshold;
	CEdit m_edtMinPlateWTH;
	CEdit m_edtPlateDemarcate;
	CComboBox m_cboLaneNum;
	CEdit m_edtRecognitionType;
	CEdit m_edtConfThreshold;
	CComboBox m_cboRecognitionType;
	CComboBox m_cboPlateType;
	CComboBox m_cboRecoCarType;
	CComboBox m_cboPlateAngle;
	CEdit m_edtSpeed;
	CComboBox m_cboExchangeEnabled;
	CEdit m_edtMaxFrames;
	CEdit m_edtSingleConfLimit;
	CEdit m_edtAlgConfLevel;
	CComboBox m_cboEnableMark;
	CComboBox m_cboRoadWayID;
	CComboBox m_cboIdentify1;
	CComboBox m_cboIdentify2;
	CComboBox m_cboIdentify3;
	CComboBox m_cboIdentify4;
	CComboBox m_cboIdentify5;
	CComboBox m_cboIdentify6;
	CComboBox m_cboIdentify7;
public:
	afx_msg void OnCbnSelchangeCboBrandreco();
	afx_msg void OnCbnSelchangeCboBeltcheck();
	afx_msg void OnCbnSelchangeCboMainfaceCheck();
	afx_msg void OnCbnSelchangeCboCofaceCheck();
	afx_msg void OnCbnSelchangeCboTypecheck();
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedBtnRecoSet();
	afx_msg void OnStnClickedStcRegionType();
	CEdit m_edtEnable;
	afx_msg void OnBnClickedBtnFilterPlateSet();
	CComboBox m_cboFilterPlateType;
	CComboBox m_cboFilterEnableState;
	afx_msg void OnCbnSelchangeCboFilterPlateType();
};
