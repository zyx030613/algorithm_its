#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#define  ITS_MERGE_TYPE_ZERO 1 //һ��ͼƬ�ϳ�
#define ITS_MERGE_TYPE_ONE 2 //����ͼƬ�ϳ�
#define  ITS_MERGE_TYPE_TWO 3  //����ͼƬ�ϳ�
#define ITS_ENABLE_TYPE 6 //��ͨʹ��ר������
// Cls_ItsCompoPic �Ի���

class Cls_ItsCompoPic : public CLS_BasePage
{
	DECLARE_DYNAMIC(Cls_ItsCompoPic)

public:
	Cls_ItsCompoPic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cls_ItsCompoPic();

// �Ի�������
	enum { IDD = IDD_DLG_ITS_COMPO_PIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	BOOL UI_UpdatePic();
	BOOL UI_UpdateCompo();
	BOOL UI_UpdateCutout();
	BOOL UI_UpdateTwo();
	BOOL UI_UpdateOne();
	void UI_UpdatePicRecv();

private:
	int m_iLogonID;
	int m_iChannel;
	void UI_UpdateDialog();
public:
	
	afx_msg void OnBnClickedBtnPicset();
	afx_msg void OnBnClickedBtnComposet();
	afx_msg void OnBnClickedStcCompoPic();
	afx_msg void OnBnClickedBtnCutoutSet();
	afx_msg void OnBnClickedChkPicenable();
	afx_msg void OnBnClickedBtnTwoset();
	afx_msg void OnBnClickedBtnOneset();
private:
	CEdit m_editPicRate;
	CComboBox m_cboOneImage;
	CComboBox m_cboTwoImage;
	CComboBox m_cboThreeImage;
	CComboBox m_cboCutoutType;
	CComboBox m_cboCutoutRange;
	CButton m_btnCompoSet;
	CButton m_btnCutoutSet;
	CButton m_chkPicEnable;
	CButton m_btnOneSet;
	CButton m_btnTwoSet;	
public:
	afx_msg void OnBnClickedBtnPicReceive();
};
