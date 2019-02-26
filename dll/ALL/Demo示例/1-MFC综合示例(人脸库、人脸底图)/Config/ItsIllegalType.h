#pragma once
#include "../BasePage.h"
#include "afxwin.h"

#define ILLEAGLE_ID_NUMBER  16    //Υ��ID������
#define MAX_PRIORITY		100   //���ȵȼ�
#define LANE_ID				3	  //������
#define ILLEAGLE_NUMBER		16	  //Υ������
// Cls_ItsIllegalTppe �Ի���

class Cls_ItsIllegalTppe : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsIllegalTppe)

public:
	Cls_ItsIllegalTppe(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cls_ItsIllegalTppe();

// �Ի�������
	enum { IDD = IDD_DLG_ITS_ILLEGAL_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnIllegaiSet();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	void UI_UpdateNumber();
	BOOL UI_UpdateIllegal();
private:
	int m_iLogonID;
	int m_iChannel;
	CEdit m_editIllegalName;
	CComboBox m_cboIllegalID;
	CComboBox m_cboPriority;
public:
	CStatic m_stcIlleagleNumber;
	CComboBox m_cboIlleagleNumber;
	CStatic m_stcLaneId;
	CComboBox m_cobLaneId;
	//afx_msg void OnCbnSelchangeCboLaneId();
	afx_msg void OnCbnSelchangeCboIlleagleNumber();
	afx_msg void OnCbnSelchangeCboLaneId();
};
