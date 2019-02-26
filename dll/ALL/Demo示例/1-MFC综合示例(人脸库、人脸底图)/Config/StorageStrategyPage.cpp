// StorageStrategyPage.cpp : implementation file
//

#include "stdafx.h"
#include "StorageStrategyPage.h"

#define	MAX_DISK_NUM	24
#define MAX_CHANNEL_NO	64
#define DISK_GROUP_NO	8
#define STRATEGY_DISKGROUP	0
#define STRATEGY_DISKQUOTA	1
#define ALL_CHANNEL_NO  65535
// CLS_StorageStrategyPage dialog

IMPLEMENT_DYNAMIC(CLS_StorageStrategyPage, CDialog)

CLS_StorageStrategyPage::CLS_StorageStrategyPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_StorageStrategyPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	memset(m_strDiskGroup, 0, sizeof(m_strDiskGroup));
	memset(m_strDiskQuota, 0, sizeof(m_strDiskQuota));
	m_iCurStrategy = 0;
	memset(m_iChannelEnable, 0, sizeof(m_iChannelEnable));
	m_iPageNo = 0;
	m_iMaxLinkNum = 0;
}

CLS_StorageStrategyPage::~CLS_StorageStrategyPage()
{
}

void CLS_StorageStrategyPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STORAGE_STRATEGY, m_cboStorageStrategy);
	DDX_Control(pDX, IDC_COMBO_DISKGROUP_NO, m_cboGroupNo);
	DDX_Control(pDX, IDC_CHECK1, m_chkDiskNo[0]);
	DDX_Control(pDX, IDC_CHECK2, m_chkDiskNo[1]);
	DDX_Control(pDX, IDC_CHECK3, m_chkDiskNo[2]);
	DDX_Control(pDX, IDC_CHECK4, m_chkDiskNo[3]);
	DDX_Control(pDX, IDC_CHECK5, m_chkDiskNo[4]);
	DDX_Control(pDX, IDC_CHECK6, m_chkDiskNo[5]);
	DDX_Control(pDX, IDC_CHECK7, m_chkDiskNo[6]);
	DDX_Control(pDX, IDC_CHECK8, m_chkDiskNo[7]);
	int iIndex = 0;
	for(int i = 8; i < MAX_DISK_NUM_EX; ++i)
	{
		iIndex = i -8;
		DDX_Control(pDX, IDC_CHECK75+iIndex, m_chkDiskNo[i]);	
	}
	//由于控件中间ID被占分两段初始化
	for(int i = 0; i < 16; ++i)
	{
		DDX_Control(pDX, IDC_CHECK9+i, m_chkChannelNo[i]);
	}
	for(int i = 16; i < LEN_64; ++i)
	{
		iIndex = 9+i;
		DDX_Control(pDX, IDC_CHECK9+iIndex, m_chkChannelNo[i]);
	}
	DDX_Control(pDX, IDC_COMBO_CHANNEL_NO, m_cboChannelNo);
	DDX_Control(pDX, IDC_EDIT_RECORD_QUOTA, m_edtRecQuota);
	DDX_Control(pDX, IDC_EDIT_PICTURE_QUOTA, m_edtPicQuota);
	DDX_Control(pDX, IDC_EDIT_RECORD_USED, m_edtRecUsed);
	DDX_Control(pDX, IDC_EDIT_PICTURE_USED, m_edtPicUsed);
	DDX_Control(pDX, IDC_CBO_CHN_RANGE, m_cboChnIndex);
}


BEGIN_MESSAGE_MAP(CLS_StorageStrategyPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_STORAGE_STRATEGY, &CLS_StorageStrategyPage::OnCbnSelchangeComboStorageStrategy)
	ON_BN_CLICKED(IDC_BUTTON_STRATEGY_SET, &CLS_StorageStrategyPage::OnBnClickedButtonStrategySet)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLS_StorageStrategyPage::OnBnClickedButtonSave)
	ON_CBN_SELCHANGE(IDC_COMBO_DISKGROUP_NO, &CLS_StorageStrategyPage::OnCbnSelchangeComboDiskgroupNo)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_NO, &CLS_StorageStrategyPage::OnCbnSelchangeComboChannelNo)
	ON_CBN_SELCHANGE(IDC_CBO_CHN_RANGE, &CLS_StorageStrategyPage::OnCbnSelchangeCboChnRange)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHECK9,IDC_CHECK74,&CLS_StorageStrategyPage::OnBnClickedChkChannel)
END_MESSAGE_MAP()

// CLS_StorageStrategyPage message handlers

BOOL CLS_StorageStrategyPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i=0; i<MAX_DISK_NUM_EX; i++)
	{
		m_chkDiskNo[i].SetCheck(BST_UNCHECKED);
	}
	for (int i=0; i<MAX_CHANNEL_NO; i++)
	{
		m_chkChannelNo[i].SetCheck(BST_UNCHECKED);
	}

	m_cboGroupNo.ResetContent();
	for (int i=1; i<=DISK_GROUP_NO; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboGroupNo.AddString(strNo);
	}
	m_cboGroupNo.SetCurSel(0);

	m_edtRecQuota.SetLimitText(4);
	m_edtPicQuota.SetLimitText(4);

	UI_UpdateDialog();
	UI_UpdateStrategyType();

	return TRUE;
}

void CLS_StorageStrategyPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}

	int iChannelNum = 0;
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	m_cboChannelNo.ResetContent();
	for (int i=1; i<=iChannelNum; i++)
	{
		CString strNo;
		strNo.Format("Channel%d", i);
		m_cboChannelNo.AddString(strNo);
	}
	m_cboChannelNo.SetCurSel(0);
	int iEnableValue = -1;
	int iStrategyType = -1;
	iRet = NetClient_GetCommonEnable(m_iLogonID, CI_STORAGE_DISK_GROUP, 0x7FFFFFFF, &iEnableValue);
	if (iRet == 0)
	{
		m_iCurStrategy = iEnableValue?STRATEGY_DISKGROUP:STRATEGY_DISKQUOTA;
		m_cboStorageStrategy.SetCurSel(m_iCurStrategy);
		m_iModeType = m_iCurStrategy;
	}
	UI_UpdateStrategyType();
	UI_UpdateDiskGroup();
	UI_UpdateDiskQuota();

}

void CLS_StorageStrategyPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_StorageStrategyPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_STORAGE_STRATEGY, IDS_CONFIG_STORAGE_STRATEGY);
	SetDlgItemTextEx(IDC_STATIC_DISKGROUP, IDS_CONFIG_STORAGE_DISKGROUP);
	SetDlgItemTextEx(IDC_STATIC_DISKQUOTA, IDS_CONFIG_STORAGE_DISKQUOTA);
	SetDlgItemTextEx(IDC_STATIC_DISKGROUP_NO, IDS_CONFIG_STORAGE_GROUPNO);
	SetDlgItemTextEx(IDC_STATIC_DISK_NO, IDS_CONFIG_STORAGE_DISKNO);
	//SetDlgItemTextEx(IDC_STATIC_DISK_NO2, IDS_CONFIG_STORAGE_CHANNEL1_8);
	//SetDlgItemTextEx(IDC_STATIC_DISK_NO3, IDS_CONFIG_STORAGE_CHANNEL9_16);
	//SetDlgItemTextEx(IDC_STATIC_DISK_NO4, IDS_CONFIG_STORAGE_CHANNEL17_24);
	//SetDlgItemTextEx(IDC_STATIC_DISK_NO5, IDS_CONFIG_STORAGE_CHANNEL25_32);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_NO, IDS_CONFIG_STORAGE_CHANNELNO);
	SetDlgItemTextEx(IDC_STATIC_RECORD_QUOTA, IDS_CONFIG_STORAGE_RECORD_QUOTA);
	SetDlgItemTextEx(IDC_STATIC_PICTURE_QUOTA, IDS_CONFIG_STORAGE_PICTURE_QUOTA);
	SetDlgItemTextEx(IDC_BUTTON_STRATEGY_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_RECORD_USED, IDS_CONFIG_STORAGE_QUOTA_USED);
	SetDlgItemTextEx(IDC_STATIC_PICTURE_USED, IDS_CONFIG_STORAGE_QUOTA_USED);
	SetDlgItemTextEx(IDC_STATIC_TOTALSIZE, IDS_CONFIG_STORAGE_TOTAL_SIZE);
	SetDlgItemTextEx(IDC_BUTTON_SAVE, IDS_CONFIG_STORAGE_SAVE);

	SetDlgItemTextEx(IDC_STATIC_CHN_RANGE, IDS_CHOICE_CHANNEL_RANGE);

	InsertString(m_cboStorageStrategy,0,IDS_CONFIG_STORAGE_DISKGROUP);
	InsertString(m_cboStorageStrategy,1,IDS_CONFIG_STORAGE_DISKQUOTA);
	m_cboStorageStrategy.SetCurSel(0);

	for (int i = 0; i < 3; ++i)
	{
		CString cstrChnRange;
		cstrChnRange.Format("%d-%d", 64*i, 64*(i+1));
		m_cboChnIndex.AddString(cstrChnRange);
	}

}

void CLS_StorageStrategyPage::UI_UpdateStrategyType()
{
	int iStrategyType = m_cboStorageStrategy.GetCurSel();
	if (STRATEGY_DISKGROUP == iStrategyType)
	{
		GetDlgItem(IDC_STATIC_DISKGROUP)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DISKGROUP_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DISKGROUP_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DISK_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DISK_NO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DISK_NO3)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DISK_NO4)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DISK_NO5)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DISKQUOTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_CHANNEL_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CHANNEL_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECORD_QUOTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECORD_QUOTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_GB1)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_PICTURE_QUOTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PICTURE_QUOTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_GB2)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECORD_USED)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_PICTURE_USED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECORD_USED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PICTURE_USED)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_TOTALSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TOTALSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_GB3)->EnableWindow(FALSE);

		for (int i=0; i<MAX_DISK_NUM_EX; i++)
		{
			m_chkDiskNo[i].EnableWindow(TRUE);
		}
		for (int i=0; i<MAX_CHANNEL_NO; i++)
		{
			m_chkChannelNo[i].EnableWindow(TRUE);
		}
	}
	else if (STRATEGY_DISKQUOTA == iStrategyType)
	{
		GetDlgItem(IDC_STATIC_DISKGROUP)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DISKGROUP_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DISKGROUP_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DISK_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DISK_NO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DISK_NO3)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DISK_NO4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DISK_NO5)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DISKQUOTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_CHANNEL_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_CHANNEL_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_RECORD_QUOTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RECORD_QUOTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_GB1)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PICTURE_QUOTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PICTURE_QUOTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_GB2)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_RECORD_USED)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PICTURE_USED)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RECORD_USED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PICTURE_USED)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_TOTALSIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TOTALSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_GB3)->EnableWindow(TRUE);


		for (int i=0; i<MAX_DISK_NUM_EX; i++)
		{
			m_chkDiskNo[i].EnableWindow(FALSE);
		}
		for (int i=0; i<MAX_CHANNEL_NO; i++)
		{
			m_chkChannelNo[i].EnableWindow(FALSE);
		}
	}
}
void CLS_StorageStrategyPage::OnCbnSelchangeComboStorageStrategy()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iChannelNum = 0;
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	m_cboChannelNo.ResetContent();
	for (int i=1; i<=iChannelNum; i++)
	{
		CString strNo;
		strNo.Format("Channel%d", i);
		m_cboChannelNo.AddString(strNo);
	}
	m_cboChannelNo.SetCurSel(0);

	UI_UpdateStrategyType();
	UI_UpdateDiskGroup();
	UI_UpdateDiskQuota();
}

void CLS_StorageStrategyPage::OnBnClickedButtonStrategySet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	OnBnClickedButtonSave();

	int iStrategyType = m_cboStorageStrategy.GetCurSel();
	int iRet = -1;
	if (iStrategyType == STRATEGY_DISKGROUP)
	{
		int iDiskGroupNum = 0;
		DISK_GROUP strDiskGroup[MAX_DISK_GROUP_NUM] = {0};

		for (int i=0; i<MAX_DISK_GROUP_NUM; i++)
		{
			if (m_strDiskGroup[i].uiDiskNO[0] != 0)
			{
				memcpy(&strDiskGroup[iDiskGroupNum++], &m_strDiskGroup[i], sizeof(DISK_GROUP));
			}
		}
		iRet = NetClient_SetDiskGroup(m_iLogonID, strDiskGroup, iDiskGroupNum);
		if (0 == iRet)
		{
			iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_GROUP, 0x7FFFFFFF, 1);
			if (iRet != 0)
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetCommonEnable(%d,%d)",m_iLogonID,CI_STORAGE_DISK_GROUP);
			}
			iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_QUOTA, 0x7FFFFFFF, 0);
			if (iRet != 0)
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetCommonEnable(%d,%d)",m_iLogonID,CI_STORAGE_DISK_QUOTA);
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDiskGroup(%d,%d)",m_iLogonID, iDiskGroupNum);
		}
	}
	else if (iStrategyType == STRATEGY_DISKQUOTA)
	{
		int iChannelNo = m_cboChannelNo.GetCurSel();
		DISK_QUOTA strDiskQuota = {0};
		strDiskQuota.iSize = sizeof(DISK_QUOTA);
		int iBufSize = sizeof(DISK_QUOTA);
		strDiskQuota.iRecordQuota = GetDlgItemInt(IDC_EDIT_RECORD_QUOTA);
		strDiskQuota.iPictureQuota = GetDlgItemInt(IDC_EDIT_PICTURE_QUOTA);

		iRet = NetClient_SetDiskQuota(m_iLogonID, iChannelNo, &strDiskQuota, iBufSize);
		if (0 == iRet)
		{
			iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_GROUP, 0x7FFFFFFF, 0);		
			if (iRet != 0)
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetCommonEnable(%d,%d)",m_iLogonID,CI_STORAGE_DISK_GROUP);
			}
			iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_QUOTA, 0x7FFFFFFF, 1);
			if (iRet != 0)
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetDiskQuota(%d,%d)",m_iLogonID,CI_STORAGE_DISK_QUOTA);
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDiskGroup(%d,%d,%d)",m_iLogonID, iChannelNo, iBufSize);
		}
	}
}

BOOL CLS_StorageStrategyPage::UI_UpdateDiskGroup()
{
	if (m_iLogonID < 0)
		return FALSE;

	for (int i=0; i<MAX_DISK_GROUP_NUM; i++)
	{
		m_chkDiskNo[i].EnableWindow(TRUE);
	}
	int iCount= -1;
	int iChannelNum = 0;
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	int iCommonRet = NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_FORBIDCHN, 0x7FFFFFFF, &iCount);
	iChannelNum -= iCount;
	m_iMaxLinkNum = iChannelNum;
	for (int i=0; i<MAX_CHANNEL_NO; i++)
	{
		if (i>=iChannelNum)
		{
			m_chkChannelNo[i].EnableWindow(FALSE);
		}
	}

	NVS_STORAGEDEV storage;
	iRet = NetClient_NetFileGetDiskInfoEx(m_iLogonID, &storage, sizeof(storage));
	if (iRet == 0)
	{
		for (int i=0; i<MAX_DISK_NUM_EX; i++)
		{
			if (storage.m_strctSATA[i].m_u16Status == 0 || storage.m_strctSATA[i].m_u16Usage == 1)
			{
				//i号磁盘为无磁盘或为备份磁盘
				m_chkDiskNo[i].EnableWindow(FALSE);
			}
		}
	}
	//改为大路数处理方式
	//DISK_GROUP strDiskGroup[MAX_DISK_GROUP_NUM] = {0};
	//iRet = NetClient_GetDiskGroup(m_iLogonID, strDiskGroup, MAX_DISK_GROUP_NUM);
	//if (iRet == 0)
	//{
	//	int iGroupNo = m_cboGroupNo.GetCurSel();
	//	int iIndex = 0;
	//	while (iIndex < MAX_DISK_GROUP_NUM)
	//	{
	//		if (strDiskGroup[iIndex].iGroupNO == iGroupNo)
	//		{
	//			for (int i=0; i<64; i++)
	//			{
	//				if (strDiskGroup[iIndex].uiDiskNO[i/32]>>(i%32) & 1)
	//				{
	//					m_chkDiskNo[i].SetCheck(BST_CHECKED);
	//				}
	//			}
	//			for (int i=0; i<iChannelNum; i++)
	//			{
	//				if (strDiskGroup[iIndex].uiChannelNO[i/32]>>(i%32) & 1)
	//				{
	//					m_chkChannelNo[i].SetCheck(BST_CHECKED);
	//				}
	//			}
	//			iIndex++;
	//			continue;
	//		}
	//		for (int i=0; i<64; i++)
	//		{
	//			if (strDiskGroup[iIndex].uiDiskNO[i/32]>>(i%32) & 1)
	//			{
	//				//把除了当前选中的盘组号的其他盘组使用的磁盘灰掉。
	//				m_chkDiskNo[i].EnableWindow(FALSE);
	//			}
	//		}
	//		iIndex++;
	//	}
	//}
	//改为大路数处理方式
	for (int i=0; i<LEN_16; i++)
	{
		m_iChannelEnable[i] = 0;
	}
	m_iPageNo = 1;
	
	//NetClient_GetChannelNum(m_iLogonID, &m_iMaxLinkNum);
	
	DISK_GROUP strDiskGroup[MAX_DISK_GROUP_NUM] = {0};
	for (int i=0; i<MAX_DISK_GROUP_NUM; ++i)
	{
		strDiskGroup[i].iSize = sizeof(DISK_GROUP);
	}

	iRet = NetClient_GetDiskGroup(m_iLogonID, strDiskGroup, MAX_DISK_GROUP_NUM);
	if (iRet == 0)
	{
		int iIndex = 0;
		int iGroupNo = m_cboGroupNo.GetCurSel();
		int iDiskState = -1;
		bool bSelect = false;
		while (iIndex < MAX_DISK_GROUP_NUM)
		{
			if (strDiskGroup[iIndex].iGroupNO == iGroupNo && !bSelect)
			{
				bSelect = true;
	
				for (int i=0; i<MAX_DISK_NUM_EX; i++)
				{
					if (strDiskGroup[iIndex].uiDiskNO[i/32]>>(i%32) & 1)
					{
						if (m_chkDiskNo[i].IsWindowEnabled())
						{
							m_chkDiskNo[i].SetCheck(BST_CHECKED);
						}
					}
				}

				for(int i=0; i< 4; i++)
				{
					m_iChannelEnable[i] = strDiskGroup[iIndex].uiChannelNO[i];
				}
				for(int i=4; i< LEN_16; i++)
				{
					m_iChannelEnable[i] = strDiskGroup[iIndex].uiChannelNOEx[i-4];
				}

				iIndex++;

				continue;
			}

			//把除了当前选中的盘组号的其他盘组使用的磁盘灰掉。
			for (int i=0; i< MAX_DISK_NUM_EX; i++)
			{
				if (strDiskGroup[iIndex].uiDiskNO[i/32]>>(i%32) & 1)
				{
					m_chkDiskNo[i].EnableWindow(FALSE);
				}
			}
			iIndex++;
		}
	}

	ChannelCheck();
	return TRUE;
}

BOOL CLS_StorageStrategyPage::UI_UpdateDiskQuota()
{
	if (m_iLogonID < 0)
		return FALSE;

	DISK_QUOTA strDiskQuota = {0};
	strDiskQuota.iSize = sizeof(DISK_QUOTA);
	int iBufSize = sizeof(DISK_QUOTA);
	int iChannelNo = m_cboChannelNo.GetCurSel();
	int iRet = NetClient_GetDiskQuotaState(m_iLogonID, iChannelNo, CMD_DISK_QUOTA_MAX_USED, &strDiskQuota, iBufSize);
	if (iRet == 0)
	{
		SetDlgItemInt(IDC_EDIT_RECORD_QUOTA, strDiskQuota.iRecordQuota);
		SetDlgItemInt(IDC_EDIT_PICTURE_QUOTA, strDiskQuota.iPictureQuota);
	}
	int iTotalDiskSize = 0;
	iRet = NetClient_GetDiskQuotaState(m_iLogonID, iChannelNo, CMD_DISK_QUOTA_TOTAL, &iTotalDiskSize, sizeof(iTotalDiskSize));
	if (iRet == 0)
	{
		if (iChannelNo == m_cboChannelNo.GetCurSel())
		{
			SetDlgItemInt(IDC_EDIT_TOTALSIZE, iTotalDiskSize );
		}
	}
	m_strDiskQuota[iChannelNo].iSize = sizeof(DISK_QUOTA_USED);
	int iUsedBufSize = sizeof(DISK_QUOTA_USED);
	iRet = NetClient_GetDiskQuotaState(m_iLogonID, iChannelNo, CMD_DISK_QUOTA_CURRENT_USED, &m_strDiskQuota[iChannelNo], iUsedBufSize);
	if (iRet == 0)
	{
		if (iChannelNo == m_cboChannelNo.GetCurSel())
		{
			SetDlgItemText(IDC_EDIT_RECORD_USED, m_strDiskQuota[iChannelNo].cRecordQuota );
			SetDlgItemText(IDC_EDIT_PICTURE_USED, m_strDiskQuota[iChannelNo].cPictureQuota );
		}
	}

	if (m_cboStorageStrategy.GetCurSel() == STRATEGY_DISKQUOTA)
	{
		for (int i=0; i<MAX_DISK_NUM_EX; i++)
		{
			m_chkDiskNo[i].EnableWindow(FALSE);
		}
		for (int i=0; i<MAX_CHANNEL_NO; i++)
		{
			m_chkChannelNo[i].EnableWindow(FALSE);
		}
	}
	return TRUE;
}

void CLS_StorageStrategyPage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser)
{
	if (_ulLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",_ulLogonID);
		return;
	}

	int iMessage = _iWparam & 0xFFFF;
	switch (iMessage)
	{
	case WCM_DISK_QUOTA:
		{
			UpdateDiskQuota(_iWparam);
			break;
		}
	}
}
void CLS_StorageStrategyPage::OnBnClickedButtonSave()
{
	int iGroupIndex = m_cboGroupNo.GetCurSel();
	int iGroupNo = iGroupIndex;
	memset(&m_strDiskGroup[iGroupIndex], 0, sizeof(DISK_GROUP));
	m_strDiskGroup[iGroupIndex].iGroupNO = iGroupNo;
	for (int i=0; i<MAX_DISK_GROUP_NUM; i++)
	{
		if (m_chkDiskNo[i].GetCheck() == BST_CHECKED)
		{
			m_strDiskGroup[iGroupIndex].uiDiskNO[0] |= 1<<i; //0~7 1008~10017
		}
	}
	//int iChannelNum = 0;
	//int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	//if (iRet == 0)
	//{
	//	for (int i=0; i<iChannelNum; i++)
	//	{
	//		if (m_chkChannelNo[i].GetCheck() == BST_CHECKED)
	//		{
	//			m_strDiskGroup[iGroupIndex].uiChannelNO[i/32] |= 1<<(i%32);
	//		}
	//	}
	//}
	for(int i=0; i< 4; i++)
	{
		m_strDiskGroup[iGroupIndex].uiChannelNO[i] = m_iChannelEnable[i];
	}
	for(int i=4; i< LEN_16; i++)
	{
		m_strDiskGroup[iGroupIndex].uiChannelNOEx[i-4] = m_iChannelEnable[i];
	}

	int iRet = NetClient_SetDiskGroup(m_iLogonID, m_strDiskGroup, iGroupNo);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDiskGroup LogonID(%d),Channel(%d),Error(0x%08x)", m_iLogonID, 0,GetLastError());
	}
	else
	{
		iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_GROUP, 0x7FFFFFFF, 1);
		iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_QUOTA, 0x7FFFFFFF, 0);

		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDiskGroup(%d,%d)", m_iLogonID, 0);
	}
}

void CLS_StorageStrategyPage::OnCbnSelchangeComboDiskgroupNo()
{
	
	for (int i=0; i< MAX_DISK_NUM_EX; i++)      //MAX_DISK_GROUP_NUM
	{
		m_chkDiskNo[i].SetCheck(BST_UNCHECKED);
	}

	for (int i=0; i<MAX_CHANNEL_NO; i++)
	{
		m_chkChannelNo[i].SetCheck(BST_UNCHECKED);
	}
	UI_UpdateDiskGroup();
}

void CLS_StorageStrategyPage::OnCbnSelchangeComboChannelNo()
{
	UI_UpdateDiskQuota();
}

void CLS_StorageStrategyPage::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData )
{
	int iRetMsg = 0;
	switch (_iParaType)
	{
	case PARA_DISKGROUP:
		{
			if (STRATEGY_DISKGROUP != m_iModeType)
			{
				int iRet = MessageBox(GetTextEx(IDS_REBOOT_DEVICE_CHOOSE),_T(""),MB_TOPMOST|MB_OKCANCEL);
				if (iRet == IDOK)
				{
 					iRet = NetClient_Reboot(m_iLogonID);
					if (0 == iRet)
					{
						m_iModeType = STRATEGY_DISKGROUP;
 					}
					else
					{
						AddLog(LOG_TYPE_FAIL,"","[NetClient_Reboot] failed!LogonID(%d),Error(0x%08x)",
							m_iLogonID,GetLastError());
					}
				}
				else
				{
					int iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_GROUP, 0x7FFFFFFF, 0);
					iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_QUOTA, 0x7FFFFFFF, 1);
				}
			}
		}
		break;
	case PARA_DISKQUOTA:
		{
			if (STRATEGY_DISKQUOTA != m_iModeType)
			{
				int iRet = MessageBox(GetTextEx(IDS_REBOOT_DEVICE_CHOOSE),_T(""),MB_TOPMOST|MB_OKCANCEL);
				if (iRet == IDOK)
				{
					iRet = NetClient_Reboot(m_iLogonID);
					if (0 == iRet)
					{
						m_iModeType = STRATEGY_DISKQUOTA;
					}
					else
					{
						AddLog(LOG_TYPE_FAIL,"","[NetClient_Reboot] failed!LogonID(%d),Error(0x%08x)",
							m_iLogonID,GetLastError());
					}
				}
				else
				{
					int iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_GROUP, 0x7FFFFFFF, 1);
					iRet = NetClient_SetCommonEnable(m_iLogonID, CI_STORAGE_DISK_QUOTA, 0x7FFFFFFF, 0);
				}
			}
		}
		break;
	}
}

void CLS_StorageStrategyPage::ChannelCheck()
{
	for (int i=0; i<LEN_64; i++)
	{
		if ((m_iPageNo-1)*LEN_64+i<m_iMaxLinkNum)
		{
			m_chkChannelNo[i].SetCheck(1<<i&m_iChannelEnable[(m_iPageNo-1)*2+i/LEN_32]?TRUE:FALSE);
		}
		else
		{
			m_chkChannelNo[i].SetCheck(FALSE);
		}
	}
}

void CLS_StorageStrategyPage::OnCbnSelchangeCboChnRange()
{
	// TODO: Add your control notification handler code here
	int iIndex = m_cboChnIndex.GetCurSel(); //cb@150430
	if (0 == iIndex)
	{
		m_iPageNo = 1; 
		SetDlgItemText(IDC_STATIC_DISK_NO2, "ChannelNo(1-8)");
		SetDlgItemText(IDC_STATIC_DISK_NO3, "ChannelNo(9-16)");
		SetDlgItemText(IDC_STATIC_DISK_NO4, "ChannelNo(17-24)");
		SetDlgItemText(IDC_STATIC_DISK_NO5, "ChannelNo(25-32)");
		SetDlgItemText(IDC_STATIC_DISK_NO6, "ChannelNo(33-40)");
		SetDlgItemText(IDC_STATIC_DISK_NO7, "ChannelNo(41-48)");
		SetDlgItemText(IDC_STATIC_DISK_NO8, "ChannelNo(49-56)");
		SetDlgItemText(IDC_STATIC_DISK_NO9, "ChannelNo(57-64)");
	}
	else if (1 == iIndex)
	{
		m_iPageNo = 2;
		SetDlgItemText(IDC_STATIC_DISK_NO2, "ChannelNo(65-72)");
		SetDlgItemText(IDC_STATIC_DISK_NO3, "ChannelNo(73-80)");
		SetDlgItemText(IDC_STATIC_DISK_NO4, "ChannelNo(81-88)");
		SetDlgItemText(IDC_STATIC_DISK_NO5, "ChannelNo(89-96)");
		SetDlgItemText(IDC_STATIC_DISK_NO6, "ChannelNo(97-104)");
		SetDlgItemText(IDC_STATIC_DISK_NO7, "ChannelNo(105-112)");
		SetDlgItemText(IDC_STATIC_DISK_NO8, "ChannelNo(113-120)");
		SetDlgItemText(IDC_STATIC_DISK_NO9, "ChannelNo(121-128)");
	}
	else if (2 == iIndex)
	{
		m_iPageNo = 3;
		SetDlgItemText(IDC_STATIC_DISK_NO2, "ChannelNo(129-136)");
		SetDlgItemText(IDC_STATIC_DISK_NO3, "ChannelNo(137-144)");
		SetDlgItemText(IDC_STATIC_DISK_NO4, "ChannelNo(145-152)");
		SetDlgItemText(IDC_STATIC_DISK_NO5, "ChannelNo(153-160)");
		SetDlgItemText(IDC_STATIC_DISK_NO6, "ChannelNo(161-168)");
		SetDlgItemText(IDC_STATIC_DISK_NO7, "ChannelNo(169-176)");
		SetDlgItemText(IDC_STATIC_DISK_NO8, "ChannelNo(177-184)");
		SetDlgItemText(IDC_STATIC_DISK_NO9, "ChannelNo(185-192)");
	}
	ChannelCheck();
}


void CLS_StorageStrategyPage::OnBnClickedChkChannel( UINT _uiID )
{
	int index = 0;
	//控件ID中间值被占
	if (_uiID <= IDC_CHECK24)
	{
		index = _uiID - IDC_CHECK9;
	}
	else
	{
		index = _uiID - IDC_CHECK9 - 9;
	}
	
	if (m_chkChannelNo[index].GetCheck() == BST_CHECKED)
	{
		m_iChannelEnable[(m_iPageNo-1)*2+index/LEN_32] |= 1<<index;
	} 
	else
	{
		m_iChannelEnable[(m_iPageNo-1)*2+index/LEN_32] &= ~(1<<index);
	}
}

void CLS_StorageStrategyPage::UpdateDiskQuota(int _iWparam)
{
	int iChannelNo = (_iWparam>>16) & 0xFFFF;
	int iTotalDiskSize = 0;
	int iRet = NetClient_GetDiskQuotaState(m_iLogonID, iChannelNo, CMD_DISK_QUOTA_TOTAL, &iTotalDiskSize, sizeof(iTotalDiskSize));
	if (iRet == 0)
	{
		if (iChannelNo == m_cboChannelNo.GetCurSel())
		{
			SetDlgItemInt(IDC_EDIT_TOTALSIZE, iTotalDiskSize );
		}
	}

	if (iChannelNo < MAX_CHANNEL_NUM)
	{
		m_strDiskQuota[iChannelNo].iSize = sizeof(DISK_QUOTA_USED);
		int iBufSize = sizeof(DISK_QUOTA_USED);
		iRet = NetClient_GetDiskQuotaState(m_iLogonID, iChannelNo, CMD_DISK_QUOTA_CURRENT_USED, &m_strDiskQuota[iChannelNo], iBufSize);
		if (RET_SUCCESS == iRet)
		{
			if (iChannelNo == m_cboChannelNo.GetCurSel())
			{
				SetDlgItemText(IDC_EDIT_RECORD_USED, m_strDiskQuota[iChannelNo].cRecordQuota );
				SetDlgItemText(IDC_EDIT_PICTURE_USED, m_strDiskQuota[iChannelNo].cPictureQuota );
			}
		}
	}
	else if (iChannelNo > MAX_CHANNEL_NUM && ALL_CHANNEL_NO == iChannelNo)
	{
		int iGetChannelNum = -1;
		int iRet = NetClient_GetChannelNum(m_iLogonID, &iGetChannelNum);
		int iCurChannelNo = -1;
		for (iCurChannelNo = 0; iCurChannelNo < iGetChannelNum; iCurChannelNo++)
		{
			m_strDiskQuota[iCurChannelNo].iSize = sizeof(DISK_QUOTA_USED);
			int iBufSize = sizeof(DISK_QUOTA_USED);
			iRet = NetClient_GetDiskQuotaState(m_iLogonID, iCurChannelNo, CMD_DISK_QUOTA_CURRENT_USED, &m_strDiskQuota[iCurChannelNo], iBufSize);
			
			if (RET_SUCCESS == iRet)
			{
				if (iCurChannelNo == m_cboChannelNo.GetCurSel())
				{
					SetDlgItemText(IDC_EDIT_RECORD_USED, m_strDiskQuota[iCurChannelNo].cRecordQuota );
					SetDlgItemText(IDC_EDIT_PICTURE_USED, m_strDiskQuota[iCurChannelNo].cPictureQuota );
				}
			}
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","iChanneNo illegal");
	}	
}
