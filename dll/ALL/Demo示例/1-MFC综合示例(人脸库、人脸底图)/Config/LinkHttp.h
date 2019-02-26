#ifndef _LAN_LINK_HTTP_H_
#define _LAN_LINK_HTTP_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_LinkHttp dialog

class CLS_LinkHttp : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_LinkHttp)

public:
	CLS_LinkHttp(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_LinkHttp();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_LAN_HTTP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData);
	void UI_UpdateDialogText();
	void UI_UpdateLinkHttpInfo();
	void GetInfoByDialog(LinkHttpInfo* _ptInfo);
	afx_msg void OnCbnSelchangeComboLinkHttpIndex();
	afx_msg void OnBnClickedButtonLinkHttpSet();
	afx_msg void OnBnClickedButtonLinkHttpTest();
private:
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboLinkHttpIndex;
	CComboBox m_cboLinkHttpParaNum;
	CButton m_chkLinkHttpEnable;
	CEdit m_edtLinkHttpRecordName;
	CEdit m_edtRecordDecription;
	CEdit m_edtLinkHttpUserName;
	CEdit m_edtLinkHttpPassword;
	CEdit m_edtLinkHttpIpAddress;
	CEdit m_edtLinkHttpPort;
	CEdit m_edtLinkHttpPara1;
	CEdit m_edtLinkHttpPara2;
	CEdit m_edtLinkHttpPara3;
	CEdit m_edtLinkHttpPara4;

};

#endif
