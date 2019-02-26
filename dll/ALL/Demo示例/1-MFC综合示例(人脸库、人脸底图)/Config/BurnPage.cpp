// BurnPage.cpp : implementation file
//

#include "stdafx.h"
#include "BurnPage.h"


// CLS_BurnPage dialog

IMPLEMENT_DYNAMIC(CLS_BurnPage, CDialog)

CLS_BurnPage::CLS_BurnPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_BurnPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_BurnPage::~CLS_BurnPage()
{
}

void CLS_BurnPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BURNMODE, m_cboBurnMode);
	DDX_Control(pDX, IDC_EDIT_CHANNELBITS, m_edtChannelBits);
	DDX_Control(pDX, IDC_EDIT_CDROM_BITS, m_edtCDRomBits);
	DDX_Control(pDX, IDC_COMBO_DISK_TYPE, m_cboDiskType);
	DDX_Control(pDX, IDC_COMBO_BURNSPEED, m_cboBurnSpeed);
	DDX_Control(pDX, IDC_EDIT_BURN_HOUR, m_edtBurnHour);
	DDX_Control(pDX, IDC_EDIT_RESSPACE, m_edtResSpace);
	DDX_Control(pDX, IDC_EDIT_DVDNAME, m_edtDvdName);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	DDX_Control(pDX, IDC_COMBO_CDROM_ID, m_cboCDRomID);
	DDX_Control(pDX, IDC_EDIT_FLAGBYBITS, m_edtFlagByBits);
	DDX_Control(pDX, IDC_COMBO_BURNSTATUS, m_cboBurnStatus);
	DDX_Control(pDX, IDC_EDIT_TOTALSPACE, m_edtTotalSpace);
	DDX_Control(pDX, IDC_EDIT_FREESPACE, m_edtFreeSpace);
	DDX_Control(pDX, IDC_EDIT_RESERVED, m_edtReserved);
	DDX_Control(pDX, IDC_BUTTON_STARTBURN, m_btnStartBurn);
	DDX_Control(pDX, IDC_BUTTON_STOPBURN, m_btnStopBurn);
	DDX_Control(pDX, IDC_COMBO_BURN_FILE_MODE, m_cboBurnFileMode);
}


BEGIN_MESSAGE_MAP(CLS_BurnPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_BURNMODE, &CLS_BurnPage::OnCbnSelchangeComboBurnmode)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLS_BurnPage::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_STARTBURN, &CLS_BurnPage::OnBnClickedButtonStartburn)
	ON_BN_CLICKED(IDC_BUTTON_STOPBURN, &CLS_BurnPage::OnBnClickedButtonStopburn)
	ON_CBN_SELCHANGE(IDC_COMBO_CDROM_ID, &CLS_BurnPage::OnCbnSelchangeComboCdromId)
END_MESSAGE_MAP()


// CLS_BurnPage message handlers
BOOL CLS_BurnPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtChannelBits.SetLimitText(10);
	m_edtCDRomBits.SetLimitText(10);
	m_edtBurnHour.SetLimitText(2);
	m_edtResSpace.SetLimitText(4);
	m_edtDvdName.SetLimitText(MAX_DVDNAME_LEN);
	m_edtFlagByBits.SetLimitText(10);
	m_edtTotalSpace.SetLimitText(10);
	m_edtFreeSpace.SetLimitText(10);

	m_cboBurnMode.SetCurSel(0);
	m_cboBurnSpeed.AddString("4");
	m_cboBurnSpeed.AddString("6");
	m_cboBurnSpeed.AddString("8");
	m_cboBurnSpeed.AddString("16");

	UI_UpdateDialog();

	return TRUE;
}

void CLS_BurnPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateCount();
	UI_UpdateMode();
	UI_UpdateStatus();
}

void CLS_BurnPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_BurnPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_CDROM_COUNT,IDS_CONFIG_BURN_CDROM_COUNT);
	SetDlgItemTextEx(IDC_STATIC_BURNMODE,IDS_CONFIG_BURN_MODE);
	SetDlgItemTextEx(IDC_STATIC_CHANNELBITS,IDS_CONFIG_BURN_CHANNEL_BITS);
	SetDlgItemTextEx(IDC_STATIC_CDROM_BITS,IDS_CONFIG_BURN_CDROM_BITS);
	SetDlgItemTextEx(IDC_STATIC_DISK_TYPE,IDS_CONFIG_BURN_DISK_TYPE);
	SetDlgItemTextEx(IDC_STATIC_BURNSPEED,IDS_CONFIG_BURN_SPEED);
	SetDlgItemTextEx(IDC_STATIC_BURN_HOUR,IDS_CONFIG_BURN_HOUR);
	SetDlgItemTextEx(IDC_STATIC_RESSPACE,IDS_CONFIG_BURN_RESSPACE);
	SetDlgItemTextEx(IDC_STATIC_DVDNAME,IDS_CONFIG_BURN_DVDNAME);
	SetDlgItemTextEx(IDC_BUTTON_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CDROM_ID,IDS_CONFIG_BURN_CDROM_ID);
	SetDlgItemTextEx(IDC_STATIC_FLAGBYBITS,IDS_CONFIG_BURN_FLAG_BY_BITS);
	SetDlgItemTextEx(IDC_STATIC_BURNSTATUS,IDS_CONFIG_BURN_STATUS);
	SetDlgItemTextEx(IDC_STATIC_TOTALSPACE,IDS_CONFIG_BURN_TOTAL_SPACE);
	SetDlgItemTextEx(IDC_STATIC_FREESPACE,IDS_CONFIG_BURN_FREE_SPACE);
	SetDlgItemTextEx(IDC_STATIC_RESERVED,IDS_CONFIG_BURN_RESERVED);
	SetDlgItemTextEx(IDC_BUTTON_STARTBURN,IDS_CONFIG_BURN_START);
	SetDlgItemTextEx(IDC_BUTTON_STOPBURN,IDS_CONFIG_BURN_STOP);
	SetDlgItemTextEx(IDC_STATIC_BURN_FILE_MODE,IDS_BURN_FILE_MODE);

	InsertString(m_cboBurnMode,0,IDS_CONFIG_BURN_MODE_SINGLE);
	InsertString(m_cboBurnMode,1,IDS_CONFIG_BURN_MODE_MUTI);
	InsertString(m_cboBurnMode,2,IDS_CONFIG_BURN_MODE_LOOP);

	InsertString(m_cboDiskType,0,IDS_CONFIG_BURN_DISKTYPE_AUTOTEST);
	InsertString(m_cboDiskType,1,IDS_CONFIG_BURN_DISKTYPE_DVD);
	InsertString(m_cboDiskType,2,IDS_CONFIG_BURN_DISKTYPE_BLUE);

	InsertString(m_cboBurnStatus,0,IDS_CFG_BURN_STATUS_NOT_BURNNING);
	InsertString(m_cboBurnStatus,1,IDS_CFG_BURN_STATUS_BURNNING);
	InsertString(m_cboBurnStatus,2,IDS_CFG_BURN_STATUS_ERROR);
	InsertString(m_cboBurnStatus,3,IDS_CFG_BURN_STATUS_DISK_FULL);
	InsertString(m_cboBurnStatus,4,IDS_CFG_BURN_STATUS_PACKING);
	InsertString(m_cboBurnStatus,5,IDS_CFG_BURN_STATUS_START_OK);
	InsertString(m_cboBurnStatus,6,IDS_CFG_BURN_STATUS_START_FAILED);
	InsertString(m_cboBurnStatus,7,IDS_CFG_BURN_STATUS_UPLOAD);
	InsertString(m_cboBurnStatus,8,IDS_CFG_BURN_STATUS_RESUME);
	InsertString(m_cboBurnStatus,9,IDS_CFG_BURN_STATUS_STOP_OK);
	InsertString(m_cboBurnStatus,10,IDS_CFG_BURN_STATUS_STOP_FAILED);
	InsertString(m_cboBurnStatus,11,IDS_CFG_BURN_STATUS_FORCE_STOP_OK);
	InsertString(m_cboBurnStatus,12,IDS_CFG_BURN_STATUS_FORCE_STOP_FAILED);
	InsertString(m_cboBurnStatus,13,IDS_CFG_BURN_STATUS_INSUFFICIENT_SPACE);

	//0-原模式  1-单一文件模式
	InsertString(m_cboBurnFileMode,0,IDS_H323_ORIGNAL_MODE);
	InsertString(m_cboBurnFileMode,1,IDS_H323_SIGNAL_FILE_MODE);
}

BOOL CLS_BurnPage::UI_UpdateCount()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iCount = 0;
	int iRet = NetClient_GetCDBurnConfig(m_iLogonID, -1, CDBURN_CMD_GET_CDROMCOUNT, &iCount, sizeof(iCount));
	if (0 == iRet)
	{
		if (m_cboCDRomID.GetCount() != iCount)
		{
			m_cboCDRomID.ResetContent();
			for (int i=0; i<iCount; ++i)
			{
				CString strCDRomID;
				strCDRomID.Format("%d",i);
				m_cboCDRomID.AddString(strCDRomID);
			}
			m_cboCDRomID.SetCurSel(0);
		}
		AddLog(LOG_TYPE_SUCC,"","UI_UpdateCount (%d,%d)",m_iLogonID,sizeof(iCount));
	}
	else
	{
		m_cboCDRomID.ResetContent();
		AddLog(LOG_TYPE_FAIL,"","UI_UpdateCount (%d,%d)",m_iLogonID,sizeof(iCount));
	}
	return TRUE;
}

void CLS_BurnPage::OnCbnSelchangeComboBurnmode()
{

}

BOOL CLS_BurnPage::UI_UpdateMode()
{
	if (m_iLogonID < 0)
		return FALSE;

	TCDBurnPolicy tcdBurnPolicy = {0};
	tcdBurnPolicy.iCDRomID = m_cboCDRomID.GetCurSel();
	int iRet = NetClient_GetCDBurnConfig(m_iLogonID, -1, CDBURN_CMD_GET_MODE, &tcdBurnPolicy, sizeof(tcdBurnPolicy));
	if (0 == iRet)
	{
		m_cboBurnMode.SetCurSel(tcdBurnPolicy.iMode);
		SetDlgItemInt(IDC_EDIT_CHANNELBITS, tcdBurnPolicy.iChannelBits[0],FALSE);
		SetDlgItemInt(IDC_EDIT_CDROM_BITS, tcdBurnPolicy.iDeviceBits[0],FALSE);
		m_cboDiskType.SetCurSel(tcdBurnPolicy.iDiskType);
		if (4 == tcdBurnPolicy.iBurnSpeed)
		{
			m_cboBurnSpeed.SetCurSel(0);
		}
		else if (6 == tcdBurnPolicy.iBurnSpeed)
		{
			m_cboBurnSpeed.SetCurSel(1);
		}
		else if (8 == tcdBurnPolicy.iBurnSpeed)
		{
			m_cboBurnSpeed.SetCurSel(2);
		}
		else if (16 == tcdBurnPolicy.iBurnSpeed)
		{
			m_cboBurnSpeed.SetCurSel(3);
		}
		SetDlgItemInt(IDC_EDIT_BURN_HOUR, tcdBurnPolicy.iBurnHour);
		SetDlgItemInt(IDC_EDIT_RESSPACE, tcdBurnPolicy.iResSpace);
		SetDlgItemText(IDC_EDIT_DVDNAME, tcdBurnPolicy.cDVDName);
		AddLog(LOG_TYPE_SUCC,"","UI_UpdateMode(%d,%d)",m_iLogonID,sizeof(tcdBurnPolicy));
		m_cboBurnFileMode.SetCurSel(tcdBurnPolicy.iBurnFileMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","UI_UpdateMode(%d,%d)",m_iLogonID,sizeof(tcdBurnPolicy));
	}
	return TRUE;
}

void CLS_BurnPage::OnBnClickedButtonSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TCDBurnPolicy tcdBurnPolicy = {0};
	tcdBurnPolicy.iMode = m_cboBurnMode.GetCurSel();
	if (0 == tcdBurnPolicy.iMode)
	{
		tcdBurnPolicy.iCDRomID = m_cboCDRomID.GetCurSel();
		if (tcdBurnPolicy.iCDRomID < 0)
		{
			AddLog(LOG_TYPE_MSG,"","CDRomID(%d)",tcdBurnPolicy.iCDRomID);
			return;
		}
		int iDeviceBits = (1 << tcdBurnPolicy.iCDRomID);
	}
	tcdBurnPolicy.iChannelBits[0] = GetDlgItemInt(IDC_EDIT_CHANNELBITS,NULL,FALSE);
	tcdBurnPolicy.iDeviceBits[0] = GetDlgItemInt(IDC_EDIT_CDROM_BITS,NULL,FALSE);
	tcdBurnPolicy.iDiskType = m_cboDiskType.GetCurSel();
	tcdBurnPolicy.iBurnSpeed = GetDlgItemInt(IDC_COMBO_BURNSPEED);
	tcdBurnPolicy.iBurnHour = GetDlgItemInt(IDC_EDIT_BURN_HOUR);
	tcdBurnPolicy.iResSpace = GetDlgItemInt(IDC_EDIT_RESSPACE);
	GetDlgItemText(IDC_EDIT_DVDNAME, tcdBurnPolicy.cDVDName, MAX_DVDNAME_LEN+1);
	tcdBurnPolicy.iBurnFileMode = m_cboBurnFileMode.GetCurSel();
	int iRet = NetClient_SetCDBurnConfig(m_iLogonID, -1, CDBURN_CMD_SET_MODE, &tcdBurnPolicy, sizeof(tcdBurnPolicy));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCDBurnConfig(%d,%d)",m_iLogonID,sizeof(tcdBurnPolicy));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCDBurnConfig(%d,%d)",m_iLogonID,sizeof(tcdBurnPolicy));
	}
}

BOOL CLS_BurnPage::UI_UpdateSet()
{

	return TRUE;
}

BOOL CLS_BurnPage::UI_UpdateStatus()
{
	if (m_iLogonID < 0)
		return FALSE;

	TCDBurnStatus tcdBurnStatus = {0};
	tcdBurnStatus.iCDRomID = m_cboCDRomID.GetCurSel();
	int iRet = NetClient_GetCDBurnConfig(m_iLogonID, -1, CDBURN_CMD_GET_STATUS, &tcdBurnStatus, sizeof(tcdBurnStatus));
	if (0 == iRet)
	{
		//	101对应对下拉框里的第四个，开始刻录成功
		int iState = tcdBurnStatus.iState;
		if (iState >= 101)
		{
			iState -= 97;
		}
		m_cboBurnStatus.SetCurSel(iState);
		SetDlgItemInt(IDC_EDIT_TOTALSPACE, tcdBurnStatus.ulTotal);
		SetDlgItemInt(IDC_EDIT_FREESPACE, tcdBurnStatus.ulFree);
		SetDlgItemText(IDC_EDIT_RESERVED, tcdBurnStatus.cReserved);
		AddLog(LOG_TYPE_SUCC,"","UI_UpdateStatus(%d,%d)",m_iLogonID,sizeof(tcdBurnStatus));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","UI_UpdateStatus(%d,%d)",m_iLogonID,sizeof(tcdBurnStatus));
	}
	return TRUE;
}

void CLS_BurnPage::OnBnClickedButtonStartburn()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCDRomID = m_cboCDRomID.GetCurSel();
	if (iCDRomID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","CDRomID(%d)",iCDRomID);
		return;
	}
	TCBurnStopMode tcBurnStopMode = {0};
	tcBurnStopMode.iDeviceNum = iCDRomID;
	tcBurnStopMode.iFlagByBits = GetDlgItemInt(IDC_EDIT_FLAGBYBITS);
	int iRet = NetClient_SetCDBurnConfig(m_iLogonID, -1, CDBURN_CMD_SET_START, &tcBurnStopMode, sizeof(tcBurnStopMode));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCDBurnConfig(%d,%d)",m_iLogonID,sizeof(tcBurnStopMode));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCDBurnConfig(%d,%d)",m_iLogonID,sizeof(tcBurnStopMode));
	}
}

void CLS_BurnPage::OnBnClickedButtonStopburn()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCDRomID = m_cboCDRomID.GetCurSel();
	if (iCDRomID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","CDRomID(%d)",iCDRomID);
		return;
	}
	int iFlagByBits = GetDlgItemInt(IDC_EDIT_FLAGBYBITS);
	if (iFlagByBits < 0)
	{
		AddLog(LOG_TYPE_MSG,"","FlagByBits(%d)",iFlagByBits);
		return;		
	}
	TCBurnStopMode tcBurnStopMode = {0};
	tcBurnStopMode.iDeviceNum = iCDRomID;
	tcBurnStopMode.iFlagByBits = iFlagByBits;
	int iRet = NetClient_SetCDBurnConfig(m_iLogonID, -1, CDBURN_CMD_SET_STOP, &tcBurnStopMode, sizeof(tcBurnStopMode));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCDBurnConfig(%d,%d)",m_iLogonID,sizeof(tcBurnStopMode));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCDBurnConfig(%d,%d)",m_iLogonID,sizeof(tcBurnStopMode));
	}
}

void CLS_BurnPage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser)
{
	int iMsgType = LOWORD(_iWparam);
	switch(iMsgType)
	{
	case WCM_CDBURN_STATUS:
		{
			int iCDRomID  = (_iWparam>>16)&0xFF;
			if (m_cboCDRomID.GetCurSel() == iCDRomID)
			{
				UI_UpdateStatus();
			}			
		}
		break;
	}
}

void CLS_BurnPage::OnCbnSelchangeComboCdromId()
{
	UI_UpdateStatus();
}
