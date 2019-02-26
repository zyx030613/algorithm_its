#pragma once

#include "../BasePage.h"
#include "afxwin.h"

#define MAX_PIC_NUM		8	//多画面个数

class CLS_DNVRCreateFree : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DNVRCreateFree)

public:
	CLS_DNVRCreateFree(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DNVRCreateFree();

	enum { IDD = IDD_DLG_CFG_DNVR_CREATEFREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	VoViewSegment m_stViewSegInfo[MAX_VO_NUM+1];

	CComboBox m_cboDevideId;
	CComboBox m_cboPicCount;
	CComboBox m_cboChanNo[MAX_PIC_NUM];
	CEdit m_edtCoordsX[MAX_PIC_NUM];
	CEdit m_edtCoordsY[MAX_PIC_NUM];
	CEdit m_edtWidth[MAX_PIC_NUM];
	CEdit m_edtHeight[MAX_PIC_NUM];

	void UI_UpdateDialog();
	void SetWidgetEnable(int _iPicNo);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

	afx_msg void OnCbnSelchangeComboPicCount();
	afx_msg void OnCbnSelchangeComboChanNo(UINT _ID);
	afx_msg void OnBnClickedButtonCreatefreeSetAll();
	afx_msg void OnBnClickedButton1Getparam();
	afx_msg void OnEdtCheckLegal(UINT _ID);
	afx_msg void OnCbnSelchangeComboOutputDeviceId();
};
