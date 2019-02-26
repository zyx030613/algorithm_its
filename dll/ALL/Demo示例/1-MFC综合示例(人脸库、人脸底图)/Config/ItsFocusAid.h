#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#define ITS_AREA_SUM 5//����������Ҳ������Ķ���
#define ITS_AREAID_SUM 8 //����������
#define FOCUS_COMMANDTYPE_FINISHED 2
// Cls_ItsFocusAid �Ի���

class Cls_ItsFocusAid : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsFocusAid)

public:
	Cls_ItsFocusAid(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cls_ItsFocusAid();

// �Ի�������
	enum { IDD = IDD_DLG_ITS_FOCUS_AID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedBtnAreaSet();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedBtnStartFocus();

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateArea();
private:
	int m_iLogonID;
	int m_iChannel;
	int m_iCommand;
	CComboBox m_cboAreaSum;
	CEdit m_editX[ITS_AREA_SUM];
	CEdit m_editY[ITS_AREA_SUM];
	CComboBox m_cboAreaID;
public:
	afx_msg void OnCbnSelchangeCboAreaid();
};
