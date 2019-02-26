#pragma once
#include "afxwin.h"

// CLS_OSDEdit �Ի���

class CLS_OSDEdit : public CDialog
{
	DECLARE_DYNAMIC(CLS_OSDEdit)

public:
	CLS_OSDEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_OSDEdit();

// �Ի�������
	enum { IDD = IDD_DLG_CFG_OSD_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iLogonID;
	int m_iDlgType;		//0��ӽ��棬1�༭����
	int m_iDevNo;			//�豸���,ͨ����
	int m_iOSDNo;		//�ַ����ӱ��
	inline void InitOSDParam(int _iDlgFlag, int _iLogonID, int _iDevID, int _iOSDNo)
	{
		m_iLogonID = _iLogonID;
		m_iDlgType = _iDlgFlag;
		m_iDevNo = _iDevID;
		m_iOSDNo = _iOSDNo;
	}
	CEdit m_edtDevName;
	CEdit m_edtDevIP;
	CComboBox m_cboDevCH;
	CComboBox m_cboOSDArea;
	CComboBox m_cboOSDColor;
	virtual BOOL OnInitDialog();
	void InitOSDInfo();
	void UpdateUI();
	CString GetColorStr(int _iColor);
	afx_msg void OnBnClickedBtnOsdSet();
};
