#pragma once
#include "BasePage.h"
#include "afxwin.h"


// CLS_IOData �Ի���

class CLS_IOData : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_IOData)

public:
	CLS_IOData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_IOData();
private:
	int m_iLogonId;
	int m_iChannelNo;
	CComboBox m_cboDevType;
	CComboBox m_cboIONo;
	CComboBox m_cboDefaultState;
	CComboBox m_cboWorkState;
// �Ի�������
	enum { IDD = IDD_DLG_ITS_IO_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnCbnSelchangeCombo3();
	void OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo);
	BOOL OnInitDialog();
	void OnLanguageChanged( int _iLanguage);
	void UI_UpdateDialog();
	afx_msg void OnBnClickedBtnSetio();
	CEdit m_edtDutyCycle;
	CEdit m_edtDuration;
	CEdit m_LeadTime;
	CEdit m_edtDouFre;
	afx_msg void OnCbnSelchangeCboIoNo();
};
