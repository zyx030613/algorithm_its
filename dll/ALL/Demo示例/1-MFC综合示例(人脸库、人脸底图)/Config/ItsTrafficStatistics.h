#pragma once
#include "../BasePage.h"
#include "afxwin.h"
// Cls_ItsTrafficStatistics 对话框

class Cls_ItsTrafficStatistics : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsTrafficStatistics)

public:
	Cls_ItsTrafficStatistics(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cls_ItsTrafficStatistics();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_TRAFFIC_STATIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);

private:
	int m_iLogonID;
	int m_iChannelNo;
	void UI_UpdateDialog();
	BOOL UI_UpdateStatis();
public:
	CStatic m_gpTrafficStatis;
	CButton m_chkUseTrafficStatis;
	CStatic m_stcPartOfStatis;
	CEdit m_edtInputPart;
	CButton m_btnSetPart;
	CEdit m_edtShowPart;
	CButton m_btnCleanUp;
	afx_msg void OnBnClickedBtnSetPart();
	afx_msg void OnBnClickedBtnCleanUp();
private:
	CComboBox m_cboRoadID;
public:
	afx_msg void OnCbnSelchangeCboRoadid();
};
