#ifndef _VIDEO_DOMESTATE_PAGE_H_
#define _VIDEO_DOMESTATE_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"


// CLS_DomeState dialog

class CLS_DomeState : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeState)

public:
	CLS_DomeState(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeState();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_STATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UpdatePageUI();
	void UI_UpdateDialog();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CEdit m_edtCameraState;
	CEdit m_edtHLimit;
	CEdit m_edtVLimit;
	CEdit m_edtInterface;
	CEdit m_edtTmpSensor;
	CEdit m_edtTemperature;
	CEdit m_edtTmpScale;
	CEdit m_edtPublishDate;
public:
	afx_msg void OnBnClickedButtonAskDomeState();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

#endif
