// .\Config\DeviceDiskInfo.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include ".\Config\DeviceDiskInfo.h"


// CDeviceDiskInfo dialog

IMPLEMENT_DYNAMIC(CDeviceDiskInfo, CDialog)

CDeviceDiskInfo::CDeviceDiskInfo(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CDeviceDiskInfo::IDD, pParent)
{
	m_iLogonID = -1;
	m_IsFormating = 0;
}

CDeviceDiskInfo::~CDeviceDiskInfo()
{
}

void CDeviceDiskInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USBDEVICENO, m_cboUsbDeviceNo);
	DDX_Control(pDX, IDC_COMBO_NFSDEVIENO, m_cboNFSDeviceNo);
	DDX_Control(pDX, IDC_COMBO_SATADEVICENO, m_cboSataDeviceNo);
	DDX_Control(pDX, IDC_COMBO_ESATADEVICENO, m_cboESataDeviceNo);
	DDX_Control(pDX, IDC_COMBO_SDDEVICENO, m_cboSdDeviceNo);
	DDX_Control(pDX, IDC_COMBO_USBUSAGE, m_cboUsbUsage);
	DDX_Control(pDX, IDC_COMBO_NFSUSAGE, m_cboNFSUsage);
	DDX_Control(pDX, IDC_COMBO_SATAUSAGE, m_cboSataUsage);
	DDX_Control(pDX, IDC_COMBO_ESATAUSAGE, m_cboESataUsage);
	DDX_Control(pDX, IDC_COMBO_SDUSAGE, m_cboSdUsage);
	DDX_Control(pDX, IDC_COMBO_USBSTATUS, m_cboUsbStatus);
	DDX_Control(pDX, IDC_COMBO_NFSSTATUS, m_cboNFSStatus);
	DDX_Control(pDX, IDC_COMBO_SATASTATUS, m_cboSataStatus);
	DDX_Control(pDX, IDC_COMBO_ESATASTATUS, m_cboESataStatus);
	DDX_Control(pDX, IDC_COMBO_SDSTATUS, m_cboSdStatus);
	DDX_Control(pDX, IDC_COMBO_USBPARTNUM, m_cboUsbPartNum);
	DDX_Control(pDX, IDC_COMBO_SATAPARTNUM, m_cboSataPartNum);
	DDX_Control(pDX, IDC_COMBO_ESATAPARTNUM, m_cboESataPartNum);
	DDX_Control(pDX, IDC_COMBO_SDPARTNUM, m_cboSdPartNum);
	DDX_Control(pDX, IDC_COMBO_ESATAMODE, m_cboESataMode);
	DDX_Control(pDX, IDC_PROGRESS_PART, m_ProgressPartDisk);
}


BEGIN_MESSAGE_MAP(CDeviceDiskInfo, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_USBDEVICENO, &CDeviceDiskInfo::OnCbnSelchangeComboUsbdeviceno)
	ON_CBN_SELCHANGE(IDC_COMBO_NFSDEVIENO, &CDeviceDiskInfo::OnCbnSelchangeComboNfsdevieno)
	ON_CBN_SELCHANGE(IDC_COMBO_SATADEVICENO, &CDeviceDiskInfo::OnCbnSelchangeComboSatadeviceno)
	ON_CBN_SELCHANGE(IDC_COMBO_ESATADEVICENO, &CDeviceDiskInfo::OnCbnSelchangeComboEsatadeviceno)
	ON_CBN_SELCHANGE(IDC_COMBO_SDDEVICENO, &CDeviceDiskInfo::OnCbnSelchangeComboSddeviceno)
	ON_BN_CLICKED(IDC_BUTTON_USB_SET, &CDeviceDiskInfo::OnBnClickedButtonUsbSet)
	ON_BN_CLICKED(IDC_BUTTON_NFS_SET, &CDeviceDiskInfo::OnBnClickedButtonNfsSet)
	ON_BN_CLICKED(IDC_BUTTON_SATASET, &CDeviceDiskInfo::OnBnClickedButtonSataset)
	ON_BN_CLICKED(IDC_BUTTON_ESATASET, &CDeviceDiskInfo::OnBnClickedButtonEsataset)
	ON_BN_CLICKED(IDC_BUTTON_SD_SET, &CDeviceDiskInfo::OnBnClickedButtonSdSet)
	ON_BN_CLICKED(IDC_BUTTON_USB_PART, &CDeviceDiskInfo::OnBnClickedButtonUsbPart)
	ON_BN_CLICKED(IDC_BUTTON_SATA_PART, &CDeviceDiskInfo::OnBnClickedButtonSataPart)
	ON_BN_CLICKED(IDC_BUTTON_ESATA_PART, &CDeviceDiskInfo::OnBnClickedButtonEsataPart)
	ON_BN_CLICKED(IDC_BUTTON_SD_PART, &CDeviceDiskInfo::OnBnClickedButtonSdPart)
	ON_BN_CLICKED(IDC_BUTTON_USB_CLEARDISK, &CDeviceDiskInfo::OnBnClickedButtonUsbCleardisk)
	ON_BN_CLICKED(IDC_BUTTON_SATA_CLEARDISK, &CDeviceDiskInfo::OnBnClickedButtonSataCleardisk)
	ON_BN_CLICKED(IDC_BUTTON_ESATA_CLEARDISK, &CDeviceDiskInfo::OnBnClickedButtonEsataCleardisk)
	ON_BN_CLICKED(IDC_BUTTON_SD_CLEARDISK, &CDeviceDiskInfo::OnBnClickedButtonSdCleardisk)
	ON_BN_CLICKED(IDC_BUTTON_NFS_MAP, &CDeviceDiskInfo::OnBnClickedButtonNfsMap)
END_MESSAGE_MAP()


// CDeviceDiskInfo message handlers

void CDeviceDiskInfo::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	UI_UpdateSurface();
}

void CDeviceDiskInfo::OnLanguageChanged( int _iLanguage )
{
    UI_UpdateSurface();
}

void CDeviceDiskInfo::UI_UpdateSurface()
{
	m_ProgressPartDisk.ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(FALSE);
	SetDlgItemTextEx(IDC_STATIC_USBDEVICE, IDS_CONFIG_STORAGE_USBDEVICE);
	SetDlgItemTextEx(IDC_STATIC_NFSDEVICE, IDS_CONFIG_STORAGE_NFSDEVICE);
	SetDlgItemTextEx(IDC_STATIC_SATADEVICE, IDS_CONFIG_STORAGE_SATADEVICE);
	SetDlgItemTextEx(IDC_STATIC_ESATADEVICE, IDS_CONFIG_STORAGE_ESATADEVICE);
	SetDlgItemTextEx(IDC_STATIC_SDDEVICE, IDS_CONFIG_STORAGE_SDDEVICE);
	SetDlgItemTextEx(IDC_STATIC_USBNO, IDS_CONFIG_STORAGE_DEVICENO);
	SetDlgItemTextEx(IDC_STATIC_NFSDEVICENO, IDS_CONFIG_STORAGE_DEVICENO);
	SetDlgItemTextEx(IDC_STATIC_SATADEVICENO, IDS_CONFIG_STORAGE_DEVICENO);
	SetDlgItemTextEx(IDC_STATIC_ESATADEVICENO, IDS_CONFIG_STORAGE_DEVICENO);
	SetDlgItemTextEx(IDC_STATIC_SDNO, IDS_CONFIG_STORAGE_DEVICENO);
	SetDlgItemTextEx(IDC_STATIC_USBUSAGE, IDS_CONFIG_STORAGE_USAGE);
	SetDlgItemTextEx(IDC_STATIC_NFSUSAGE, IDS_CONFIG_STORAGE_USAGE);
	SetDlgItemTextEx(IDC_STATIC_SATAUSAGE, IDS_CONFIG_STORAGE_USAGE);
	SetDlgItemTextEx(IDC_STATIC_ESATAUSAGE, IDS_CONFIG_STORAGE_USAGE);
	SetDlgItemTextEx(IDC_STATIC_SDUSAGE, IDS_CONFIG_STORAGE_USAGE);
	SetDlgItemTextEx(IDC_BUTTON_USB_SET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_NFS_SET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_SATASET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_ESATASET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_SD_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_USBTOTALSIZE, IDS_CONFIG_STORAGE_TOTALSIZE);
	SetDlgItemTextEx(IDC_STATIC_NFSTOTALSIZE, IDS_CONFIG_STORAGE_TOTALSIZE);
	SetDlgItemTextEx(IDC_STATIC_SATATOTALSIZE, IDS_CONFIG_STORAGE_TOTALSIZE);
	SetDlgItemTextEx(IDC_STATIC_ESATATOTALSIZE, IDS_CONFIG_STORAGE_TOTALSIZE);
	SetDlgItemTextEx(IDC_STATIC_SDTOTALSIZE, IDS_CONFIG_STORAGE_TOTALSIZE);
	SetDlgItemTextEx(IDC_STATIC_USBFREESIZE, IDS_CONFIG_STORAGE_FREESIZE);
	SetDlgItemTextEx(IDC_STATIC_NFSFREESIZE, IDS_CONFIG_STORAGE_FREESIZE);
	SetDlgItemTextEx(IDC_STATIC_SATAFREESIZE, IDS_CONFIG_STORAGE_FREESIZE);
	SetDlgItemTextEx(IDC_STATIC_ESATAFREESIZE, IDS_CONFIG_STORAGE_FREESIZE);
	SetDlgItemTextEx(IDC_STATIC_SDFREESIZE, IDS_CONFIG_STORAGE_FREESIZE);
	SetDlgItemTextEx(IDC_STATIC_USBSTATUS, IDS_CONFIG_STORAGE_DISKSTATUS);
	SetDlgItemTextEx(IDC_STATIC_NFSSTATUS, IDS_CONFIG_STORAGE_DISKSTATUS);
	SetDlgItemTextEx(IDC_STATIC_SATASTATUS, IDS_CONFIG_STORAGE_DISKSTATUS);
	SetDlgItemTextEx(IDC_STATIC_ESATASTATUS, IDS_CONFIG_STORAGE_DISKSTATUS);
	SetDlgItemTextEx(IDC_STATIC_SDSTATUS, IDS_CONFIG_STORAGE_DISKSTATUS);
    SetDlgItemTextEx(IDC_STATIC_USBPARTNUM, IDS_CONFIG_STORAGE_PARTNUM);
	SetDlgItemTextEx(IDC_STATIC_NFSPATH, IDS_CONFIG_STORAGE_PATH);
	SetDlgItemTextEx(IDC_STATIC_SATAPARTNUM, IDS_CONFIG_STORAGE_PARTNUM);
	SetDlgItemTextEx(IDC_STATIC_ESATAPARTNUM, IDS_CONFIG_STORAGE_PARTNUM);
	SetDlgItemTextEx(IDC_STATIC_SDPARTNUM, IDS_CONFIG_STORAGE_PARTNUM);
	SetDlgItemTextEx(IDC_BUTTON_USB_PART, IDS_CONFIG_STORAGE_PART);
	SetDlgItemTextEx(IDC_BUTTON_NFS_MAP, IDS_CONFIG_STORAGE_MAP);
	SetDlgItemTextEx(IDC_BUTTON_SATA_PART, IDS_CONFIG_STORAGE_PART);
	SetDlgItemTextEx(IDC_BUTTON_ESATA_PART, IDS_CONFIG_STORAGE_PART);
	SetDlgItemTextEx(IDC_BUTTON_SD_PART, IDS_CONFIG_STORAGE_PART);
	SetDlgItemTextEx(IDC_BUTTON_USB_CLEARDISK,  IDS_CONFIG_STORAGE_CLEARDISK);
	SetDlgItemTextEx(IDC_BUTTON_SATA_CLEARDISK,  IDS_CONFIG_STORAGE_CLEARDISK);
	SetDlgItemTextEx(IDC_BUTTON_ESATA_CLEARDISK,  IDS_CONFIG_STORAGE_CLEARDISK);
	SetDlgItemTextEx(IDC_BUTTON_SD_CLEARDISK,  IDS_CONFIG_STORAGE_CLEARDISK);
	SetDlgItemTextEx(IDC_STATIC_ESATAMODE, IDS_CONFIG_STORAGE_DISKMODE);
	//SetDlgItemTextEx(IDC_BUTTON_ESATAFORMAT, IDS_CONFIG_STORAGE_FORMAT);
	int iCurSel1 = m_cboUsbDeviceNo.GetCurSel();
	iCurSel1 = ((-1 == iCurSel1)?0:iCurSel1);
	int iCurSel2 = m_cboNFSDeviceNo.GetCurSel();
	iCurSel2 = ((-1 == iCurSel2)?0:iCurSel2);
    int iCurSel3 = m_cboSataDeviceNo.GetCurSel();
	iCurSel3 = ((-1 == iCurSel3)?0:iCurSel3);
	int iCurSel4 = m_cboESataDeviceNo.GetCurSel();
	iCurSel4 = ((-1 == iCurSel4)?0:iCurSel4);
	int iCurSel5 = m_cboSdDeviceNo.GetCurSel();
	iCurSel5 = ((-1 == iCurSel5)?0:iCurSel5);
	int iDeviceNoSel[] = {iCurSel1, iCurSel2, iCurSel3, iCurSel4,iCurSel5};
	UI_UpdateDeviceNo(iDeviceNoSel, 5);

	int iUsbUsageSel = m_cboUsbUsage.GetCurSel();
	iUsbUsageSel = (-1 == iUsbUsageSel)?0:iUsbUsageSel;
	int iNFSUsageSel = m_cboNFSUsage.GetCurSel();
	iNFSUsageSel = (-1 == iNFSUsageSel)?0:iNFSUsageSel;
	int iSataUsageSel = m_cboSataUsage.GetCurSel();
	iSataUsageSel = (-1 == iSataUsageSel)?0:iSataUsageSel;
	int iESataUsageSel = m_cboESataUsage.GetCurSel();
	iESataUsageSel = (-1 == iESataUsageSel)?0:iESataUsageSel;
	int iSdUsageSel = m_cboSdUsage.GetCurSel();
	iSdUsageSel = (-1 == iSdUsageSel)?0:iSdUsageSel;
	int iUsageSel[] = {iUsbUsageSel, iNFSUsageSel, iSataUsageSel, iSdUsageSel};
    UI_UpdateUsage(iUsageSel, 5);

	int iUsbStatusSel = m_cboUsbStatus.GetCurSel();
	iUsbStatusSel = (-1 == iUsbStatusSel)?0:iUsbStatusSel;
	int iNFSStatusSel = m_cboNFSStatus.GetCurSel();
	iNFSStatusSel = (-1 == iNFSStatusSel)?0:iNFSStatusSel;
	int iSataStatusSel = m_cboSataStatus.GetCurSel();
	iSataStatusSel = (-1 == iSataStatusSel)?0:iSataStatusSel;
	int iESataStatusSel = m_cboESataStatus.GetCurSel();
	iESataStatusSel = (-1 == iESataStatusSel)?0:iESataStatusSel;
	int iStatusSel[] = {iUsbStatusSel, iNFSStatusSel, iSataStatusSel, iESataStatusSel};
	int iSdStatusSel = m_cboSdStatus.GetCurSel();
	iSdStatusSel = (-1 == iSdStatusSel)?0:iSdStatusSel;
	UI_UpdateStatus(iStatusSel, 5);

	int iUsbPartNumSel = m_cboUsbPartNum.GetCurSel();
	iUsbPartNumSel = (-1 == iUsbPartNumSel)?0:iUsbPartNumSel;
	int iSataPartNumSel = m_cboSataPartNum.GetCurSel();
	iSataPartNumSel = (-1 == iSataPartNumSel)?0:iSataPartNumSel;
	int iESataPartNumSel = m_cboESataPartNum.GetCurSel();
	iESataPartNumSel = (-1 == iESataPartNumSel)?0:iESataPartNumSel;
	int iSdPartNumSel = m_cboSdPartNum.GetCurSel();
	iSdPartNumSel = (-1 == iSdPartNumSel)?0:iSdPartNumSel;
	int iPartNumSel[] = {iUsbPartNumSel, iSataPartNumSel, iESataPartNumSel,iSdPartNumSel};
	UI_UpdatePartNum(iStatusSel, 4);

	int iModeSel = m_cboESataMode.GetCurSel();
	iModeSel = (-1 == iModeSel)?0:iModeSel;
	UI_UpdateMode(iModeSel);
	UpdateDiskInfo();
}


BOOL CDeviceDiskInfo::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ProgressPartDisk.SetRange(0, 100);
	m_ProgressPartDisk.ShowCaret();
	SetDlgItemText(IDC_PROGRESS_PART, "ClearDisk Failed");
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDeviceDiskInfo::UI_UpdateDeviceNo( int* _piCurSel, int _iCurSelNum )
{
	if (_iCurSelNum != 5)
	{
		return;
	}
	m_cboUsbDeviceNo.ResetContent();
	m_cboNFSDeviceNo.ResetContent();
	m_cboSataDeviceNo.ResetContent();
	m_cboESataDeviceNo.ResetContent();
	m_cboSdDeviceNo.ResetContent();
	for (int i = 0; i < 16; i++)
	{
		CString szDeviceNo;
		szDeviceNo.Format("%d", (i+1));
		if (i < 1)
		{
			m_cboNFSDeviceNo.AddString(szDeviceNo);
			m_cboESataDeviceNo.AddString(szDeviceNo);
			m_cboSdDeviceNo.AddString(szDeviceNo);
		}
		if (i < 4)
		{
			m_cboUsbDeviceNo.AddString(szDeviceNo);
		}
		m_cboSataDeviceNo.AddString(szDeviceNo);
	}
	m_cboUsbDeviceNo.SetCurSel(_piCurSel[0]);
	m_cboNFSDeviceNo.SetCurSel(_piCurSel[1]);
	m_cboSataDeviceNo.SetCurSel(_piCurSel[2]);
	m_cboESataDeviceNo.SetCurSel(_piCurSel[3]);
	m_cboSdDeviceNo.SetCurSel(_piCurSel[4]);
}

void CDeviceDiskInfo::UI_UpdateUsage( int* _piCurSel, int _iCurSelNum )
{
	if (_iCurSelNum != 5)
	{
		return;
	}
	m_cboUsbUsage.ResetContent();
	m_cboNFSUsage.ResetContent();
	m_cboSataUsage.ResetContent();
	m_cboESataUsage.ResetContent();
	m_cboSdUsage.ResetContent();

	m_cboUsbUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_RECORD));
	m_cboUsbUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_BACKUP));
	m_cboUsbUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_REDUNDANCY));
	m_cboUsbUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_READONLY));
	m_cboNFSUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_RECORD));
	m_cboNFSUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_BACKUP));
	m_cboNFSUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_REDUNDANCY));
	m_cboNFSUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_READONLY));
	m_cboSataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_RECORD));
	m_cboSataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_BACKUP));
	m_cboSataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_REDUNDANCY));
	m_cboSataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_READONLY));
	m_cboESataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_RECORD));
	m_cboESataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_BACKUP));
	m_cboESataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_REDUNDANCY));
	m_cboESataUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_READONLY));
	m_cboSdUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_RECORD));
	m_cboSdUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_BACKUP));
	m_cboSdUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_REDUNDANCY));
	m_cboSdUsage.AddString(GetTextEx(IDS_CONFIG_STORAGE_READONLY));

	m_cboUsbUsage.SetCurSel(_piCurSel[0]);
	m_cboNFSUsage.SetCurSel(_piCurSel[1]);
	m_cboSataUsage.SetCurSel(_piCurSel[2]);
	m_cboESataUsage.SetCurSel(_piCurSel[3]);
	m_cboSdUsage.SetCurSel(_piCurSel[4]);
}

void CDeviceDiskInfo::UI_UpdateStatus( int* _piCurSel, int _iCurSelNum )
{
	if (_iCurSelNum != 5)
	{
		return;
	}
	m_cboUsbStatus.ResetContent();
	m_cboNFSStatus.ResetContent();
	m_cboSataStatus.ResetContent();
	m_cboESataStatus.ResetContent();
	m_cboSdStatus.ResetContent();

	m_cboUsbStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNMOUNTED));
	m_cboUsbStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNFORMATED));
	m_cboUsbStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_FORMATED));
	m_cboUsbStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_MOUNTED));
	m_cboUsbStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_USING));

	m_cboNFSStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNMOUNTED));
	m_cboNFSStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNFORMATED));
	m_cboNFSStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_FORMATED));
	m_cboNFSStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_MOUNTED));
	m_cboNFSStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_USING));

	m_cboSataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNMOUNTED));
	m_cboSataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNFORMATED));
	m_cboSataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_FORMATED));
	m_cboSataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_MOUNTED));
	m_cboSataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_USING));

	m_cboESataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNMOUNTED));
	m_cboESataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNFORMATED));
	m_cboESataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_FORMATED));
	m_cboESataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_MOUNTED));
	m_cboESataStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_USING));

	m_cboSdStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNMOUNTED));
	m_cboSdStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_UNFORMATED));
	m_cboSdStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_FORMATED));
	m_cboSdStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_MOUNTED));
	m_cboSdStatus.AddString(GetTextEx(IDS_CONFIG_STORAGE_USING));

	m_cboUsbStatus.SetCurSel(_piCurSel[0]);
	m_cboNFSStatus.SetCurSel(_piCurSel[1]);
	m_cboSataStatus.SetCurSel(_piCurSel[2]);
	m_cboESataStatus.SetCurSel(_piCurSel[3]);
	m_cboSdStatus.SetCurSel(_piCurSel[4]);
}

void CDeviceDiskInfo::UI_UpdatePartNum( int* _piCurSel, int _iCurSelNum )
{
	if (_iCurSelNum != 4)
	{
		return;
	}
	m_cboUsbPartNum.ResetContent();
	m_cboSataPartNum.ResetContent();
	m_cboESataPartNum.ResetContent();
	m_cboSdPartNum.ResetContent();
	for (int i = 0; i < 4; i++)
	{
		CString szPartNum;
		szPartNum.Format("%d", (i+1));
		m_cboUsbPartNum.AddString(szPartNum);
		m_cboSataPartNum.AddString(szPartNum);
		m_cboESataPartNum.AddString(szPartNum);
		m_cboSdPartNum.AddString(szPartNum);
	}
	m_cboUsbPartNum.SetCurSel(_piCurSel[0]);
	m_cboSataPartNum.SetCurSel(_piCurSel[1]);
	m_cboESataPartNum.SetCurSel(_piCurSel[2]);
	m_cboSdPartNum.SetCurSel(_piCurSel[3]);
}

void CDeviceDiskInfo::UI_UpdateMode( int _iModeSel )
{
	m_cboESataMode.ResetContent();
	m_cboESataMode.AddString(GetTextEx(IDS_CONFIG_STORAGE_PARTNOFORMAT));
	m_cboESataMode.AddString(GetTextEx(IDS_CONFIG_STORAGE_PARTFORMAT));
	m_cboESataMode.SetCurSel(_iModeSel);
}

void CDeviceDiskInfo::UpdateDiskInfo()
{
	NVS_STORAGEDEV storage;
	int iUSBDevice_No = m_cboUsbDeviceNo.GetCurSel();
	int iNFSDevice_No = m_cboNFSDeviceNo.GetCurSel();
	int iIDEDevice_No = m_cboSataDeviceNo.GetCurSel();
	int iESATADevice_No = m_cboESataDeviceNo.GetCurSel();
	int iSDDevice_No = m_cboSdDeviceNo.GetCurSel();

	BOOL blSataEx = FALSE;
	int iSataExId = 0;
	if (iIDEDevice_No >= DISK_SATA_NUM)
	{
		blSataEx = TRUE;
		iSataExId = iIDEDevice_No - DISK_SATA_NUM;
	}

	if(NetClient_NetFileGetDiskInfoEx(m_iLogonID, &storage, sizeof(storage)) == 0)
	{
		SetDlgItemInt(IDC_EDIT_USBTOTALSIZE, storage.m_strctUSB[iUSBDevice_No].m_u32TotalSpace, FALSE);
		SetDlgItemInt(IDC_EDIT_USBFREESIZE, storage.m_strctUSB[iUSBDevice_No].m_u32FreeSpace, FALSE);
        m_cboUsbUsage.SetCurSel(storage.m_strctUSB[iUSBDevice_No].m_u16Usage);
		m_cboUsbStatus.SetCurSel(storage.m_strctUSB[iUSBDevice_No].m_u16Status);
        m_cboUsbPartNum.SetCurSel(storage.m_strctUSB[iUSBDevice_No].m_u16PartNum-1);

		SetDlgItemInt(IDC_EDIT_NFSTOTALSIZE, storage.m_strctNFS[iNFSDevice_No].m_u32TotalSpace, FALSE);
		SetDlgItemInt(IDC_EDIT_NFSFREESIZE, storage.m_strctNFS[iNFSDevice_No].m_u32FreeSpace, FALSE);
		m_cboNFSUsage.SetCurSel(storage.m_strctNFS[iNFSDevice_No].m_u16Usage);
		m_cboNFSStatus.SetCurSel(storage.m_strctNFS[iNFSDevice_No].m_u16Status);


		NVS_DISKINFO* ptSataInfo = NULL;
		if (blSataEx)
		{
			ptSataInfo = &storage.m_strctSATA_EX[iSataExId];
		}
		else
		{
			ptSataInfo = &storage.m_strctSATA[iIDEDevice_No];
		}
		SetDlgItemInt(IDC_EDIT_SATATOTALSIZE, ptSataInfo->m_u32TotalSpace, FALSE);
		SetDlgItemInt(IDC_EDIT_SATAFREESIZE, ptSataInfo->m_u32FreeSpace, FALSE);
		m_cboSataUsage.SetCurSel(ptSataInfo->m_u16Usage);
		m_cboSataStatus.SetCurSel(ptSataInfo->m_u16Status);
		m_cboSataPartNum.SetCurSel(ptSataInfo->m_u16PartNum-1);


		SetDlgItemInt(IDC_EDIT_ESATATOTALSIZE, storage.m_strctESATA[iESATADevice_No].m_u32TotalSpace, FALSE);
		SetDlgItemInt(IDC_EDIT_ESATAFREESIZE, storage.m_strctESATA[iESATADevice_No].m_u32FreeSpace, FALSE);
		m_cboESataUsage.SetCurSel(storage.m_strctESATA[iESATADevice_No].m_u16Usage);
		m_cboESataStatus.SetCurSel(storage.m_strctESATA[iESATADevice_No].m_u16Status);
		m_cboESataPartNum.SetCurSel(storage.m_strctESATA[iESATADevice_No].m_u16PartNum-1);

		SetDlgItemInt(IDC_EDIT_SDTOTALSIZE, storage.m_strctSD[iSDDevice_No].m_u32TotalSpace, FALSE);
		SetDlgItemInt(IDC_EDIT_SDFREESIZE, storage.m_strctSD[iSDDevice_No].m_u32FreeSpace, FALSE);
		m_cboSdUsage.SetCurSel(storage.m_strctSD[iSDDevice_No].m_u16Usage);
		m_cboSdStatus.SetCurSel(storage.m_strctSD[iSDDevice_No].m_u16Status);
		m_cboSdPartNum.SetCurSel(storage.m_strctSD[iSDDevice_No].m_u16PartNum-1);
	}

	NVS_NFS_DEV nfsDev;
	memset(&nfsDev, 0, sizeof(NVS_NFS_DEV));
	if(NetClient_NetFileGetMapStoreDevice(m_iLogonID, &nfsDev) == 0)
	{
		SetDlgItemText(IDC_EDIT_NFSIP, nfsDev.cDeviceIP);
		SetDlgItemText(IDC_EDIT_NFSPATH, nfsDev.cStorePath);
		//m_cboNFSStatus.SetCurSel(nfsDev.iState);
	}
}

void CDeviceDiskInfo::OnCbnSelchangeComboUsbdeviceno()
{
	UpdateDiskInfo();
}

void CDeviceDiskInfo::OnCbnSelchangeComboNfsdevieno()
{
	UpdateDiskInfo();
}

void CDeviceDiskInfo::OnCbnSelchangeComboSatadeviceno()
{
	UpdateDiskInfo();
}

void CDeviceDiskInfo::OnCbnSelchangeComboEsatadeviceno()
{
	UpdateDiskInfo();
}

void CDeviceDiskInfo::OnCbnSelchangeComboSddeviceno()
{
	UpdateDiskInfo();
}

int CDeviceDiskInfo::SetUsage( int _iDiskNo, int _iUsage)
{
	int iRet = -1;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	else
	{
		if(0 == NetClient_DiskSetUsage(m_iLogonID, _iDiskNo, _iUsage))
		{
		    iRet = 0;
			AddLog(LOG_TYPE_SUCC, "", "NetClient_DiskSetUsage(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_DiskSetUsage(%d),_iDiskNo:%d, _iUsage:%d", m_iLogonID, _iDiskNo, _iUsage);
		}
	}
	return iRet;
}

int CDeviceDiskInfo::DiskPart(int _iDiskNo, int _iPartNum, int _iFormatNow)
{
	int iRet = -1;
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	else
	{	//默认分区后格式化
		BOOL blFormatNow = TRUE;
		if(0 == NetClient_DiskPart(m_iLogonID, _iDiskNo, _iPartNum, blFormatNow))
		{
			iRet = 0;
			AddLog(LOG_TYPE_SUCC, "", "NetClient_DiskPart(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_DiskPart(%d),_iDiskNo:%d, _iPartNum:%d, _iFormatNow:%d", m_iLogonID, _iDiskNo, _iPartNum, _iFormatNow);
		}
	}
	return iRet;
}

int CDeviceDiskInfo::DiskFormat(int _iDiskNo, int _iFsType)
{
	int iRet = -1;
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	else
	{
		if(0 == NetClient_DiskFormat(m_iLogonID, _iDiskNo, _iFsType))
		{
			iRet = 0;
			AddLog(LOG_TYPE_SUCC, "", "NetClient_DiskFormat(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_DiskFormat(%d),_iDiskNo:%d, _iFsType:%d", m_iLogonID, _iDiskNo, _iFsType);
		}
	}
	return iRet;
}

int CDeviceDiskInfo::ClearDisk(int _iDiskNo)
{
	int iRet = -1;
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	else
	{
		if(0 == NetClient_ClearDisk(m_iLogonID, _iDiskNo))
		{
			iRet = 0;
			AddLog(LOG_TYPE_SUCC, "", "NetClient_ClearDisk(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_ClearDisk(%d),_iDiskNo:%d", m_iLogonID, _iDiskNo);
		}
	}
	return iRet;
}

void CDeviceDiskInfo::OnBnClickedButtonUsbSet()
{
	int iDiskNo = m_cboUsbDeviceNo.GetCurSel() + 8;
	int iUsage = m_cboUsbUsage.GetCurSel();
	SetUsage(iDiskNo, iUsage);
}

void CDeviceDiskInfo::OnBnClickedButtonNfsSet()
{
	int iDiskNo = m_cboNFSDeviceNo.GetCurSel() + 12;
	int iUsage = m_cboNFSUsage.GetCurSel();
	SetUsage(iDiskNo, iUsage);
}

void CDeviceDiskInfo::OnBnClickedButtonSataset()
{
	int iDiskNo = m_cboSataDeviceNo.GetCurSel();
	int iUsage = m_cboSataUsage.GetCurSel();
	SetUsage(iDiskNo, iUsage);
}

void CDeviceDiskInfo::OnBnClickedButtonEsataset()
{
	int iDiskNo = m_cboESataDeviceNo.GetCurSel() + DNO_ESATA;
	int iUsage = m_cboESataUsage.GetCurSel();
	SetUsage(iDiskNo, iUsage);
}

void CDeviceDiskInfo::OnBnClickedButtonSdSet()
{
	int iDiskNo = m_cboSdDeviceNo.GetCurSel() + DNO_SD;
	int iUsage = m_cboSdUsage.GetCurSel();
	SetUsage(iDiskNo, iUsage);
}

void CDeviceDiskInfo::OnBnClickedButtonUsbPart()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboUsbDeviceNo.GetCurSel() + 8;
	int iPartNum = m_cboUsbPartNum.GetCurSel() + 1;
	if (0 == DiskPart(iDiskNo, iPartNum, 0))
	{
		m_ProgressPartDisk.ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(TRUE);
		SetDlgItemText(IDC_STATIC_PROGRESS, "parting....");
	}
}

void CDeviceDiskInfo::OnBnClickedButtonSataPart()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboSataDeviceNo.GetCurSel();
	if (iDiskNo >= DISK_SATA_NUM)
	{
		iDiskNo = iDiskNo - DISK_SATA_NUM + DISK_SATA_EX;
	}

	int iPartNum = m_cboSataPartNum.GetCurSel();
	if (0 == DiskPart(iDiskNo, iPartNum, 0))
	{
		m_ProgressPartDisk.ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(TRUE);
		SetDlgItemText(IDC_STATIC_PROGRESS, "parting....");
	}
}

void CDeviceDiskInfo::OnBnClickedButtonEsataPart()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboESataDeviceNo.GetCurSel() + DNO_ESATA;
	int iPartNum = m_cboESataPartNum.GetCurSel();
	if (0 == DiskPart(iDiskNo, iPartNum, 0))
	{
		m_ProgressPartDisk.ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(TRUE);
		SetDlgItemText(IDC_STATIC_PROGRESS, "parting....");
	}
}

void CDeviceDiskInfo::OnBnClickedButtonSdPart()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboSdDeviceNo.GetCurSel() + DNO_SD;
	int iPartNum = m_cboSdPartNum.GetCurSel();
	if (0 == DiskPart(iDiskNo, iPartNum, 0))
	{
		m_ProgressPartDisk.ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(TRUE);
		SetDlgItemText(IDC_STATIC_PROGRESS, "parting....");
	}
}

void CDeviceDiskInfo::OnBnClickedButtonUsbCleardisk()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboUsbDeviceNo.GetCurSel() + 8;
	ClearDisk(iDiskNo);
}

void CDeviceDiskInfo::OnBnClickedButtonSataCleardisk()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboSataDeviceNo.GetCurSel();
	if (iDiskNo >= DISK_SATA_NUM)
	{
		iDiskNo = iDiskNo - DISK_SATA_NUM + DISK_SATA_EX;
	}

	ClearDisk(iDiskNo);
}

void CDeviceDiskInfo::OnBnClickedButtonEsataCleardisk()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboESataDeviceNo.GetCurSel() + DNO_ESATA;
	ClearDisk(iDiskNo);
}

void CDeviceDiskInfo::OnBnClickedButtonSdCleardisk()
{
	if(m_IsFormating == 1)
	{
		AddLog(LOG_TYPE_MSG, "", "Formating...Please wait and retry! id(%d)", m_iLogonID);
		return;
	}
	int iDiskNo = m_cboSdDeviceNo.GetCurSel() + DNO_SD;
	ClearDisk(iDiskNo);
}

void CDeviceDiskInfo::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (m_iLogonID != _ulLogonID)
	{
		return;
	}
	int iMsgType = LOWORD(_iWparam);
	CString strMsg;
	switch(iMsgType)
	{
	case WCM_DISK_FORMAT_PROGRESS:
		{
			int iParam = ((_iWparam>>16)&0xFF);
			m_ProgressPartDisk.SetPos(iParam);
			CString szParam;
			szParam.Format("%d", iParam);
			m_ProgressPartDisk.ShowWindow(TRUE);
			SetDlgItemText(IDC_STATIC_PROGRESS,"Formating......"+ szParam + "%");
			m_IsFormating = 1;
			if(iParam == 100)
			{
				m_IsFormating = 0;
				m_ProgressPartDisk.ShowWindow(FALSE);
				GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(FALSE);
				strMsg = "Format Success";
			}
			else if (iParam == 201)
			{
				strMsg = "Disk Repair......";
			}
			else if (iParam == 200)
			{
				strMsg = "Disk Repair finish";
			}
			else
			{
				strMsg = "undefined";
				strMsg.Format("%d%%",iParam);
			}
			SetDlgItemText(IDC_STATIC_PROGRESS, strMsg);
		}
		break;

	case WCM_DISK_FORMAT_ERROR:
		{
			int iParam = ((_iWparam>>16)&0xFF);
			if(iParam == 101)
				strMsg = "Format Success";
			else if(iParam == 110)
				strMsg = "Format PARA INVALID";
			else if(iParam == 104)
				strMsg = "Disk INVALID";
			else if(iParam == 147)
				strMsg = "Disk Using";
			else if(iParam == 150)
				strMsg = "Other Formating";
			else if(iParam == 199)
				strMsg = "Format Failed";
			else
				strMsg = "undefined";
			m_IsFormating = 0;
			SetDlgItemText(IDC_STATIC_PROGRESS, strMsg);
		}
		break;
	case WCM_DISK_PART_ERROR:
		{
			int iWParam = ((_iWparam>>16)&0xFF);
			CString szWParam;
			szWParam.Format("%d", iWParam);
			if(iWParam == 110)
				strMsg = "Part PARA INVALID (" + szWParam + ")";
			else if(iWParam == 104)
				strMsg = "Format Disk INVALID (" + szWParam + ")";
			else if(iWParam == 116)
				strMsg = "Get DiskInfo Failed (" + szWParam + ")";
			else if(iWParam == 122)
				strMsg = "Part Failed (" + szWParam + ")";
			else if(iWParam == 101)
			{
				int iTemp = ((_iWparam>>24)&0xFF);
				strMsg = "Part Success (" + szWParam + ")";
				if(iTemp >= 0 && iTemp <= 7 )
					DiskFormat(m_cboSataDeviceNo.GetCurSel(), 0);
				else if(iTemp >= 8 && iTemp <= 11)
					DiskFormat(m_cboUsbDeviceNo.GetCurSel() + 8, 0);
				else if(iTemp >= DNO_ESATA && iTemp < (DNO_ESATA+DISK_ESATA_NUM))
					DiskFormat(m_cboESataDeviceNo.GetCurSel() + DNO_ESATA, 0);
				else if(iTemp >= DNO_SD && iTemp < (DNO_SD+DISK_SD_NUM))
					DiskFormat(m_cboSdDeviceNo.GetCurSel() + DNO_SD, 0);
			}
			else if(iWParam == 150)
				strMsg = "Part Failed, Other Formating (" + szWParam + ")";
			else
				strMsg = "Part Failed, undefined error (" + szWParam + ")";

			SetDlgItemText(IDC_STATIC_PROGRESS, strMsg);
		}
		break;
	case WCM_LOCALSTORE_PROGRESS:
		{
			int iCode = (_iWparam>>16)&0xFF;
			CString szCode;
			szCode.Format("%d", iCode);
	
			m_ProgressPartDisk.ShowWindow(TRUE);
			if (iCode == 101 || iCode < 0)
				SetDlgItemText(IDC_STATIC_PROGRESS, "ClearDisk Failed");
			else if (iCode == 100)
			{
				SetDlgItemText(IDC_STATIC_PROGRESS, "ClearDisk Finished");
			}
			else
			{
				SetDlgItemText(IDC_STATIC_PROGRESS, "ClearDisk Running..." + szCode + "%");
				m_ProgressPartDisk.SetPos(iCode);
			}
			break;
		}
	default:
		break;
	}
}

void CDeviceDiskInfo::OnBnClickedButtonNfsMap()
{
	if (m_iLogonID < -1)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	}
	NVS_NFS_DEV nfsDev;
	memset(&nfsDev, 0, sizeof(NVS_NFS_DEV));
	GetDlgItemText(IDC_EDIT_NFSIP, nfsDev.cDeviceIP, sizeof(nfsDev.cDeviceIP));
	GetDlgItemText(IDC_EDIT_NFSPATH,nfsDev.cStorePath, sizeof(nfsDev.cStorePath));
	if(0 == NetClient_NetFileMapStoreDevice(m_iLogonID, &nfsDev))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileMapStoreDevice(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileMapStoreDevice(%d),ip:%s, path:%s", m_iLogonID, nfsDev.cDeviceIP, nfsDev.cStorePath);
	}
}
