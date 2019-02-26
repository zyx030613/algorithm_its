
#include "stdafx.h"
#include "NetClientDemo.h"
#include "StorageDiskManagePage.h"

#define CKECK_RESULT 0
#define TESTTYPE_KEY_AREA 1
#define TESTTYPE_COMPLETE 2

#define TIMER_DISK_CHECK_TIMER		1001
#define TIMER_DISK_CHECK_TIME		5000

#define DISK_CHECK_ACTION_PAUSE		0
#define DISK_CHECK_ACTION_RESUME	1
#define DISK_CHECK_ACTION_CANCEL	2

#define DISK_CHECK_STATE_CHECKING	1
#define DISK_CHECK_STATE_PAUSE		2
#define DISK_CHECK_STATE_CANCEL		3
#define DISK_CHECK_STATE_CANCEL_VALUDE 0
// CLS_StorageSmartPage 对话框

IMPLEMENT_DYNAMIC(CLS_StorageDiskManagePage, CDialog)

CLS_StorageDiskManagePage::CLS_StorageDiskManagePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_StorageDiskManagePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_StorageDiskManagePage::~CLS_StorageDiskManagePage()
{
}

void CLS_StorageDiskManagePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_STORAGE_DISKNO, m_cboDiskNo);
	DDX_Control(pDX, IDC_COM_STORAGE_CHECKWAY, m_cboCheckWay);
}


BEGIN_MESSAGE_MAP(CLS_StorageDiskManagePage, CLS_BasePage)
	ON_WM_SHOWWINDOW()	
	ON_BN_CLICKED(IDC_BUTTON_STORAGE_QUERY, &CLS_StorageDiskManagePage::OnBnClickedButtonStorageQuery)
	ON_BN_CLICKED(IDC_BTN_STORAGE_BEGIN, &CLS_StorageDiskManagePage::OnBnClickedBtnStorageBegin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STORAGE_SUSPEND, &CLS_StorageDiskManagePage::OnBnClickedBtnStorageSuspend)
	ON_BN_CLICKED(IDC_BTN_STORAGE_CANCEL, &CLS_StorageDiskManagePage::OnBnClickedBtnStorageCancel)
END_MESSAGE_MAP()

BOOL CLS_StorageDiskManagePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateSurface();
	
	
	return TRUE;
}

void CLS_StorageDiskManagePage::OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser)
{
	if (m_iLogonID != _ulLogonID)
	{
		return;
	}
	int iMsgType = LOWORD(_iWparam);
	CString strMsg;
	switch(iMsgType)
	{
		case WCM_BADBCLOCK_SIZE:
			{
				QueryDiskBLockSize();
			}
			break;
		case WCM_BADBCLOCK_TEST:
			{
				DiskBadBlockTest();
			}
			break;
		case WCM_BADBCLOCK_TEST_STATE:
			{
				DiskBadBlockTestInfo();
			}
			break;
		default:
			break;
	}
}


void CLS_StorageDiskManagePage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		UI_UpdateSurface();
		//OnCbnSelchangeCboSmartDisk();//默认显示第一个磁盘的SMART信息
	}
	else
	{
		KillTimer(TIMER_DISK_CHECK_TIMER);
	}

}

void CLS_StorageDiskManagePage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;

	//MessageBox("Hello!");
	UI_UpdateSurface();
}

void CLS_StorageDiskManagePage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateSurface();
}

void CLS_StorageDiskManagePage::QueryDiskBLockSize()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_StorageDiskManagePage::QueryDiskBLockSize] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	BadBlockSize tBadBlockSize = {0};
	tBadBlockSize.iSize = sizeof(BadBlockSize);
	tBadBlockSize.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_SIZE, m_iChannelNo, &tBadBlockSize, sizeof(BadBlockSize));

	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_GendCommand:STORAGE_QUERY] Get fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
	}
	else
	{
		//m_cboQosType.SetCurSel(GetCboSel(&m_cboQosType, tQosValue.iType));
		SetDlgItemInt(IDC_EDIT_STORAGE_CELLVOLUME, tBadBlockSize.lBlockSize);
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_GendCommand:STORAGE_QUERY] Get success!");
	}
}
void CLS_StorageDiskManagePage::DiskBadBlockTest()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_StorageDiskManagePage::DiskBadBlockTest] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	BadBlockTest tBadBlockTest = {0};
	tBadBlockTest.iSize = sizeof(BadBlockTest);
	tBadBlockTest.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
	tBadBlockTest.iType = (int)m_cboCheckWay.GetItemData(m_cboCheckWay.GetCurSel());
	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_ACTION, m_iChannelNo, &tBadBlockTest, sizeof(BadBlockTest));

	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_GendCommand:STORAGE_BEGIN] Get fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
	}
	else
	{
		//m_cboQosType.SetCurSel(GetCboSel(&m_cboQosType, tQosValue.iType));		
		int iRes = tBadBlockTest.iResult;
		if (iRes < CKECK_RESULT)
		{
			//MessageBox("无法正常开启坏道检测");
			AddLog(LOG_TYPE_FAIL, "", "[NetClient_GendCommand:STORAGE_BEGIN] Begin fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
		}
		else
		{
			AddLog(LOG_TYPE_SUCC, "", "[NetClient_GendCommand:STORAGE_BEGIN] Begin success!");
			//SetDlgItemInt(IDC_EDIT_STORAGE_CELLVOLUME, tBadBlockSize.lBlockSize);
		}
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_GendCommand:STORAGE_BEGIN] Get success!");
	}
}

void CLS_StorageDiskManagePage::DiskBadBlockTestInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_StorageDiskManagePage::DiskBadBlockTestInfo] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	BadBlockTestState tBadBlockTestState = {0};
	tBadBlockTestState.iSize = sizeof(BadBlockTestState);
	tBadBlockTestState.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
	int iStateRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_TEST_STATE, m_iChannelNo, &tBadBlockTestState, sizeof(BadBlockTestState));

	if (iStateRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand:STORAGE_BEGIN] State Get fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
	}
	else
	{
		SetDlgItemInt(IDC_EDIT_STORAGE_STATE, tBadBlockTestState.iState);
		SetDlgItemInt(IDC_EDIT_STORAGE_SCHEDULE, tBadBlockTestState.iProgress);
		SetDlgItemInt(IDC_EDIT_STORAGE_ERRORNUM, tBadBlockTestState.iErrorCount);
		SetDlgItemInt(IDC_EDIT_STORAGE_CHECKOPSITION, tBadBlockTestState.iCurrentLoc);
		int iType = tBadBlockTestState.iTestType;
		if (TESTTYPE_KEY_AREA == iType)
		{
			m_cboCheckWay.SetCurSel(0);
		}
		if (TESTTYPE_COMPLETE == iType)
		{
			m_cboCheckWay.SetCurSel(1);
		}
		
		int iState = tBadBlockTestState.iState;	
		switch (iState)
		{
		case DISK_CHECK_STATE_PAUSE:
			{
				GetDlgItem(IDC_BTN_STORAGE_SUSPEND)->SetWindowText(GetTextEx(IDS_CFG_STORAGE_DISKMAG_RESUME));
				SetDlgItemInt(IDC_EDIT_STORAGE_STATE, tBadBlockTestState.iState);
				SetDlgItemInt(IDC_EDIT_STORAGE_SCHEDULE, tBadBlockTestState.iProgress);
				SetDlgItemInt(IDC_EDIT_STORAGE_ERRORNUM, tBadBlockTestState.iErrorCount);
				SetDlgItemInt(IDC_EDIT_STORAGE_CHECKOPSITION, tBadBlockTestState.iCurrentLoc);
			}
			break;
		case DISK_CHECK_STATE_CANCEL:
			{
				GetDlgItem(IDC_BTN_STORAGE_SUSPEND)->SetWindowText(GetTextEx(IDS_CFG_STORAGE_DISKMAG_PAUSE));
				GetDlgItem(IDC_EDIT_STORAGE_STATE)->SetWindowText(NULL);
				GetDlgItem(IDC_EDIT_STORAGE_SCHEDULE)->SetWindowText(NULL);
				GetDlgItem(IDC_EDIT_STORAGE_ERRORNUM)->SetWindowText(NULL);
				GetDlgItem(IDC_EDIT_STORAGE_CHECKOPSITION)->SetWindowText(NULL);
			}
			break;
		case DISK_CHECK_STATE_CHECKING:
			{
				GetDlgItem(IDC_BTN_STORAGE_SUSPEND)->SetWindowText(GetTextEx(IDS_CFG_STORAGE_DISKMAG_PAUSE));
				SetDlgItemInt(IDC_EDIT_STORAGE_STATE, tBadBlockTestState.iState);
				SetDlgItemInt(IDC_EDIT_STORAGE_SCHEDULE, tBadBlockTestState.iProgress);
				SetDlgItemInt(IDC_EDIT_STORAGE_ERRORNUM, tBadBlockTestState.iErrorCount);
				SetDlgItemInt(IDC_EDIT_STORAGE_CHECKOPSITION, tBadBlockTestState.iCurrentLoc);
			}
			break;
		default:
			break;
		}

		//AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand:STORAGE_BEGIN] State Get success!");
	}


}


void CLS_StorageDiskManagePage::UI_UpdateSurface()
{
	m_cboDiskNo.ResetContent();

	for(int i = 0; i < DISK_SATA_NUM+DISK_SATA_EX_NUM; i++)
	{
		int iDiskId = i;
		if (i >= DISK_SATA_NUM)
		{
			iDiskId = i + DISK_SATA_EX;
		}
		m_cboDiskNo.InsertString(i, "SATA"+IntToCString(i+1));
		m_cboDiskNo.SetItemData(i, iDiskId);
	}
	m_cboDiskNo.SetCurSel(0);

	m_cboCheckWay.ResetContent();
	m_cboCheckWay.SetItemData(m_cboCheckWay.AddString(GetTextEx(IDS_STORAGE_MANAGE_KEYZONE)), 1);
	m_cboCheckWay.SetItemData(m_cboCheckWay.AddString(GetTextEx(IDS_STORAGE_MANAGE_ALL)), 2);
	m_cboCheckWay.SetCurSel(0);

	//转换中英文
	//SetDlgItemTextEx(IDC_STC_SMART_DISK, IDS_SMART_DISK);
	SetDlgItemTextEx(IDC_STC_STORAGE_DISKNO, IDS_SMART_DISK);
	SetDlgItemTextEx(IDC_STC_STORAGE_CELLCONTAIN, IDS_STORAGE_MANAGE_CELLVOLUME);
	SetDlgItemTextEx(IDC_STC_STORAGE_CELLVOLUME, IDS_STORAGE_MANAGE_CELLVOLUME);
	SetDlgItemTextEx(IDC_BUTTON_STORAGE_QUERY, IDS_PBK_QUERY);
	SetDlgItemTextEx(IDC_STC_STORAGE_BADBLOCKCHECK, IDS_STORAGE_MANAGE_BADBLOCK);
	SetDlgItemTextEx(IDC_STC_STORAGE_CHECKWAY, IDS_STORAGE_MANAGE_CHECKWAY);
	SetDlgItemTextEx(IDC_BTN_STORAGE_BEGIN, IDS_CFG_LOG_DVR_BEGIN);
	SetDlgItemTextEx(IDC_STC_STORAGE_CHECKSTATE, IDS_STORAGE_MANAGE_CHECKSTATE);
	SetDlgItemTextEx(IDC_STC_STORAGE_STATE, IDS_STORAGE_MANAGE_STATE);
	SetDlgItemTextEx(IDC_STC_STORAGE_SCHEDULE, IDS_STORAGE_PROGRESS);
	SetDlgItemTextEx(IDC_STC_STORAGE_ERRORNUM, IDS_STORAGE_MANAGE_ERRORNUM);
	SetDlgItemTextEx(IDC_STC_STORAGE_CHECKOPSITION, IDS_STORAGE_MANAGE_CURRENTLOCATION);
	//SetDlgItemTextEx(IDC_CHK_SMART_DISK_ENABLE, IDS_SMART_ENABLE);

	CString cstrBtnPauseText;
	GetDlgItem(IDC_BTN_STORAGE_SUSPEND)->GetWindowText(cstrBtnPauseText);
	if (0 == cstrBtnPauseText.Compare(GetTextEx(IDS_CFG_STORAGE_DISKMAG_PAUSE)))
	{
		SetDlgItemTextEx(IDC_BTN_STORAGE_SUSPEND, IDS_CFG_STORAGE_DISKMAG_RESUME);
	}
	else
	{
		SetDlgItemTextEx(IDC_BTN_STORAGE_SUSPEND, IDS_CFG_STORAGE_DISKMAG_PAUSE);
	}
	SetDlgItemTextEx(IDC_BTN_STORAGE_CANCEL, IDS_CFG_STORAGE_DISKMAG_CANCEL);
	
}

void CLS_StorageDiskManagePage::OnBnClickedButtonStorageQuery()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_StorageDiskManagePage::OnBnClickedButtonStorageQuery] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	BadBlockSize tBadBlockSize = {0};
	tBadBlockSize.iSize = sizeof(BadBlockSize);
	tBadBlockSize.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_SIZE, m_iChannelNo, &tBadBlockSize, sizeof(BadBlockSize));

	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand:STORAGE_QUERY] Set fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
	}
	else
	{
		//m_cboQosType.SetCurSel(GetCboSel(&m_cboQosType, tQosValue.iType));
		//SetDlgItemInt(IDC_EDIT_STORAGE_CELLVOLUME, tBadBlockSize.lBlockSize);
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand:STORAGE_QUERY] Set success!");
	}

}

void CLS_StorageDiskManagePage::OnBnClickedBtnStorageBegin()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_StorageDiskManagePage::OnBnClickedBtnStorageBegin] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	BadBlockTest tBadBlockTest = {0};
	tBadBlockTest.iSize = sizeof(BadBlockTest);
	tBadBlockTest.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
	tBadBlockTest.iType = m_cboCheckWay.GetCurSel()+1;
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_TEST, m_iChannelNo, &tBadBlockTest, sizeof(BadBlockTest));

	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand:STORAGE_BEGIN] Begin Set fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
	}
	else
	{
		//m_cboQosType.SetCurSel(GetCboSel(&m_cboQosType, tQosValue.iType));
		//SetDlgItemInt(IDC_EDIT_STORAGE_CELLVOLUME, tBadBlockSize.lBlockSize);

		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand:STORAGE_BEGIN] Begin Set success!");
	}

	Sleep(300);
// 	BadBlockTestState tBadBlockTestState = {0};
// 	tBadBlockTestState.iSize = sizeof(BadBlockTestState);
// 	tBadBlockTestState.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
// 	int iStateRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_TEST_STATE, m_iChannelNo, &tBadBlockTestState, sizeof(BadBlockTestState));
// 	
// 	if (iStateRet < RET_SUCCESS)
// 	{
// 		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand:STORAGE_BEGIN] State Set fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
// 	}
// 	else
// 	{
// 		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand:STORAGE_BEGIN] State Set success!");
// 	}

	KillTimer(TIMER_DISK_CHECK_TIMER);
	SetTimer(TIMER_DISK_CHECK_TIMER, TIMER_DISK_CHECK_TIME, NULL);	
}

void CLS_StorageDiskManagePage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (TIMER_DISK_CHECK_TIMER == nIDEvent)
	{
		int iSel = m_cboDiskNo.GetCurSel();
		if (CB_ERR != iSel)
		{
			GetCheckInfo(iSel);
		}
	}
	CLS_BasePage::OnTimer(nIDEvent);
}

void CLS_StorageDiskManagePage::GetCheckInfo(int _iDiskId)
{
	BadBlockTestState stBadBlockTestState = {0};
	stBadBlockTestState.iSize = sizeof(BadBlockTestState);
	stBadBlockTestState.iDiskId = _iDiskId;
	NetClient_SendCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_TEST_STATE, m_iChannelNo, &stBadBlockTestState, sizeof(stBadBlockTestState));
}


void CLS_StorageDiskManagePage::OnBnClickedBtnStorageSuspend()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cboDiskNo.GetCurSel();
	if (-1 == iSel)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_StorageDiskManagePage::OnBnClickedBtnStorageSuspend()][-1 == iSel]");
		return;
	}

	CString cstrBtnPauseText;
	GetDlgItem(IDC_BTN_STORAGE_SUSPEND)->GetWindowText(cstrBtnPauseText);
	
	BadBlockAction stBadBlockAction = {0};
	stBadBlockAction.iSize = sizeof(BadBlockAction);
	stBadBlockAction.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
	if (0 == cstrBtnPauseText.Compare(GetText(IDS_CFG_STORAGE_DISKMAG_PAUSE)))
	{
		stBadBlockAction.iAction = DISK_CHECK_ACTION_PAUSE;
	}
	else
	{
		stBadBlockAction.iAction = DISK_CHECK_ACTION_RESUME;
	}
	
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_ACTION, PARAM_CHANNEL_ALL, &stBadBlockAction, sizeof(stBadBlockAction));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand:PARAM_CHANNEL_ALL] Pause Set failed!");
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand:PARAM_CHANNEL_ALL] Pause Set success!");
	}
	KillTimer(TIMER_DISK_CHECK_TIMER);
	SetTimer(TIMER_DISK_CHECK_TIMER, TIMER_DISK_CHECK_TIME, NULL);	
}

void CLS_StorageDiskManagePage::OnBnClickedBtnStorageCancel()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cboDiskNo.GetCurSel();
	if (-1 == iSel)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_StorageDiskManagePage::OnBnClickedBtnStorageSuspend()][-1 == iSel]");
		return;
	}

	BadBlockAction stBadBlockAction = {0};
	stBadBlockAction.iSize = sizeof(BadBlockAction);
	stBadBlockAction.iDiskId = (int)m_cboDiskNo.GetItemData(m_cboDiskNo.GetCurSel());
	stBadBlockAction.iAction = DISK_CHECK_ACTION_CANCEL;
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_BADBCLOCK_ACTION, PARAM_CHANNEL_ALL, &stBadBlockAction, sizeof(stBadBlockAction));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand:PARAM_CHANNEL_ALL] Cancel Set failed!");
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand:PARAM_CHANNEL_ALL] Cancel Set success!");
	}
	KillTimer(TIMER_DISK_CHECK_TIMER);
	SetTimer(TIMER_DISK_CHECK_TIMER, TIMER_DISK_CHECK_TIME, NULL);	
}
