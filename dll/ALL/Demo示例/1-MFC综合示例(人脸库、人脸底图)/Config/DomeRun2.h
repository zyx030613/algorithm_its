#ifndef _DOME_RUN2_PAGE_H_
#define _DOME_RUN2_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_DomeRun2 dialog

class CLS_DomeRun2 : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeRun2)

public:
	CLS_DomeRun2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeRun2();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_RUN2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData);
	void UI_UpdateDialogText();
	void UpdateSchemaPathInfo();
	void UpdateLimitInfo();
	void SetDomeMenu( TDomeParam& _tParam );
	int  GetDomeMenu( TDomeParam& _tParam );
	afx_msg void OnCbnSelchangeComboSchemapathNo();
	afx_msg void OnBnClickedButtonSchemapathCall();
	afx_msg void OnBnClickedButtonSchemapathStartRec();
	afx_msg void OnBnClickedButtonSchemapathStopRec();
	afx_msg void OnBnClickedButtonDelschemapath();
	afx_msg void OnCbnSelchangeComboAreaNo();
	afx_msg void OnBnClickedButtonAreaBrodrLeft();
	afx_msg void OnBnClickedButtonAreaBroderRight();
	afx_msg void OnBnClickedButtonDelarea();
	afx_msg void OnBnClickedCheckLimitEnabel();
	afx_msg void OnBnClickedButtonLimitSet();
	afx_msg void OnBnClickedButtonLimitDelete();
	afx_msg void OnBnClickedButtonZero();
	afx_msg void OnBnClickedButtonNorth();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboSchemaPathNo;
	CComboBox m_cboAreaNo;
	CButton m_chkLimitEnable;
	CComboBox m_cboLimitStatus;
	bool m_blSchemaPath;		//是否录制模式路径
};

#endif