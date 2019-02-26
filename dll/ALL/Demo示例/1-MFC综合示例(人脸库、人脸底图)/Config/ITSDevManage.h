#ifndef _ITS_DEV_MANAGE_H_
#define _ITS_DEV_MANAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLS_ITSDevManage dialog

class CLS_ITSDevManage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSDevManage)

public:
	CLS_ITSDevManage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSDevManage();

	enum { IDD = IDD_DLG_CFG_ITS_STAR_NVR_DEV_MNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData);

private:
	void UI_UpdateDialog();
	void SetBayonetDataEnable();				//设置卡口数据使能
	void SetDeviceNum();						//设置设备编号参数
	void UI_UpdateHostId();
	void UI_UpdateBayonetDataEnable();
	void UI_UpdateDigitalChnIp();
	void UI_UpdateDeviceNum();
	void UI_UpdateNvrAnrEnable();

public:
	int m_iLogonId;
	int m_iChannelNo;
	CButton m_chkPicDataEnable;
	CIPAddressCtrl m_ipaddrDigitalChnIp;
	int m_iOrderId[MAX_ITS_DEVICE_COUNT];
	CButton m_chkNvrAnrEnable;
	CEdit m_edtFtpFileName;
	CEdit m_edtFtpPath;
	CEdit m_edtFtpUserName;
	CEdit m_edtFtpPassword;

public:
	afx_msg void OnBnClickedBtnHostNumSet();	//设置主机编号
	afx_msg void OnBnClickedBtnDevEditSet();
	afx_msg void OnBnClickedChkBayonetData();
	afx_msg void OnBnClickedCheckNvrAnr();
	afx_msg void OnBnClickedButtonFtpSet();
};

#endif
