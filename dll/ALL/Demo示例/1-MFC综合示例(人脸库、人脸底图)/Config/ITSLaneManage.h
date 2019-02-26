#ifndef _ITS_LANE_MANAGE_H_
#define _ITS_LANE_MANAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_ITSLaneManage dialog

class CLS_ITSLaneManage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSLaneManage)

public:
	CLS_ITSLaneManage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSLaneManage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_STAR_NVR_LANE_MNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID, int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData);
	void UI_UpdateDialogText();
	void UI_UpdateCrossInfo(int _iMsgType = 0);
	void UI_UpdateLaneInfo(int _iMsgType = 0);
	void ShowMsgToUser(int _iMsgType, int _iResult);
	int GetIndexByNumber(CComboBox &_cboComboBox, CString _cstrNumber);
	int GetCrossIndexByCrossNumber(CString _cstrCrossNumber);
	int GetLaneIndexByLaneID(int _iLaneID);
	afx_msg void OnBnClickedButtonItsAddCross();
	afx_msg void OnBnClickedButtonItsDeleteCross();
	afx_msg void OnBnClickedButtonItsModifyCross();
	afx_msg void OnBnClickedButtonItsAddLane();
	afx_msg void OnBnClickedButtonItsDeleteLane();
	afx_msg void OnBnClickedButtonItsModifyLane();
private:
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboItsCross;
	CEdit m_edtItsCrossNumber;
	CEdit m_edtItsCrossName;
	CComboBox m_cboItsLane;
	CEdit m_edtItsLaneNumber;
	CEdit m_edtItsLaneName;
	CComboBox m_cboItsCrossByLane;
	CComboBox m_cboItsTravelDirection;
	CComboBox m_cboItsLaneType;
	CEdit m_edtItsCameraNumber;
	CEdit m_edtItsCheckRegion;

	ITSCrossInfo m_tItsCross[MAX_ITS_CROSS_COUNT];
	ITSLaneInfo m_tItsLane[MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT];
public:
	afx_msg void OnCbnSelchangeComboItsCross();
	afx_msg void OnCbnSelchangeComboItsLane();
};

#endif
