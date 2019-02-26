#ifndef _LAN_PORT_MAPPING_H_
#define _LAN_PORT_MAPPING_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_LinkHttp dialog

class CLS_PortMapping : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_PortMapping)

public:
	CLS_PortMapping(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PortMapping();

	// Dialog Data
	enum { IDD = IDD_DLG_CFG_LAN_PORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo);
	void GetInfoByDialog(RouteNat *_pRouteNatInfo);

private:
	void UI_UpdateDialogText();
	void UI_UpdatePortMapInfo();

public:
	afx_msg void OnBnClickedBtnLanPortSet();

private:
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboPortType;
	CButton m_chkLanPortEnalbe;
	CButton m_btnLanPortSet;
	CEdit m_edtLanMapPort;
public:
	afx_msg void OnCbnSelchangeComboLanPortPorttype();
};

#endif