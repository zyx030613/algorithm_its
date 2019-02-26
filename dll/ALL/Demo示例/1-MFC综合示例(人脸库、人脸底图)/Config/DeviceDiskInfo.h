#pragma once
#include "BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"


// CDeviceDiskInfo dialog

class CDeviceDiskInfo : public CLS_BasePage
{
	DECLARE_DYNAMIC(CDeviceDiskInfo)

public:
	CDeviceDiskInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeviceDiskInfo();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_STORAGE_DISKINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	void UI_UpdateSurface();
private:
	int m_iLogonID;
public:
	virtual BOOL OnInitDialog();
	void UI_UpdateDeviceNo( int* _piCurSel, int _iCurSelNum );
	void UI_UpdateUsage( int* _piCurSel, int _iCurSelNum );
	void UI_UpdateStatus( int* _piCurSel, int _iCurSelNum );
	void UI_UpdatePartNum( int* _piCurSel, int _iCurSelNum );
	void UI_UpdateMode( int _iModeSel );
	void UpdateDiskInfo();
	int  SetUsage( int _iDiskNo, int _iUsage);
	int DiskPart(int _iDiskNo, int _iPartNum, int _iFormatNow);
	CComboBox m_cboUsbDeviceNo;
	CComboBox m_cboNFSDeviceNo;
	CComboBox m_cboSataDeviceNo;
	CComboBox m_cboESataDeviceNo;
	CComboBox m_cboSdDeviceNo;
	CComboBox m_cboUsbUsage;
	CComboBox m_cboNFSUsage;
	CComboBox m_cboSataUsage;
	CComboBox m_cboESataUsage;
	CComboBox m_cboSdUsage;
	CComboBox m_cboUsbStatus;
	CComboBox m_cboNFSStatus;
	CComboBox m_cboSataStatus;
	CComboBox m_cboESataStatus;
	CComboBox m_cboSdStatus;
	CComboBox m_cboUsbPartNum;
	CComboBox m_cboSataPartNum;
	CComboBox m_cboESataPartNum;
	CComboBox m_cboSdPartNum;
	CComboBox m_cboESataMode;
	afx_msg void OnCbnSelchangeComboUsbdeviceno();
	afx_msg void OnCbnSelchangeComboNfsdevieno();
	afx_msg void OnCbnSelchangeComboSatadeviceno();
	afx_msg void OnCbnSelchangeComboEsatadeviceno();
	afx_msg void OnCbnSelchangeComboSddeviceno();
	afx_msg void OnBnClickedButtonUsbSet();
	afx_msg void OnBnClickedButtonNfsSet();
	afx_msg void OnBnClickedButtonSataset();
	afx_msg void OnBnClickedButtonEsataset();
	afx_msg void OnBnClickedButtonSdSet();
	afx_msg void OnBnClickedButtonUsbPart();
	afx_msg void OnBnClickedButtonSataPart();
	afx_msg void OnBnClickedButtonEsataPart();
	afx_msg void OnBnClickedButtonSdPart();
	afx_msg void OnBnClickedButtonUsbCleardisk();
	afx_msg void OnBnClickedButtonSataCleardisk();
	afx_msg void OnBnClickedButtonEsataCleardisk();
	afx_msg void OnBnClickedButtonSdCleardisk();
	afx_msg void OnBnClickedButtonNfsMap();
	CProgressCtrl m_ProgressPartDisk;
	int m_IsFormating;
	int ClearDisk(int _iDiskNo);
	int DiskFormat(int _iDiskNo, int _iFsType);
	
};
