// AdvUpgrade.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "AdvUpgrade.h"


// CLS_AdvUpgrade dialog

//高级选项参数配置导出	
#define CFGFILE_NUM 7
const char* CONST_pcConfigFile[CFGFILE_NUM] = {"config_server.ini", 
									"config_pdcover.dat",
									"extendword.txt",
									"config_ptz.dat",
									"config_right.dat",
									"config_dg.dat",
									"config_burn.dat"};


IMPLEMENT_DYNAMIC(CLS_AdvUpgrade, CDialog)
HWND g_UpgradeMsgHwnd = NULL;
CLS_AdvUpgrade::CLS_AdvUpgrade(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AdvUpgrade::IDD, pParent)
	, m_szKernelFile(_T(""))
	, m_szWebBoxFile(_T(""))
{
	m_iLogonID = -1;
}

CLS_AdvUpgrade::~CLS_AdvUpgrade()
{
}

void CLS_AdvUpgrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrlUpgradeBin);
	DDX_Control(pDX, IDC_PROGRESS2, m_ProgressCtrlUpgradeBox);
	DDX_Text(pDX, IDC_EDIT_ADV_UPGREAD_BIN, m_szKernelFile);
	DDX_Text(pDX, IDC_EDIT_ADV_UPGREAD_BOX, m_szWebBoxFile);
	DDX_Control(pDX, IDC_EDT_CONFIG_PATH, m_edtConfigPath);
}


BEGIN_MESSAGE_MAP(CLS_AdvUpgrade, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADV_BACKUP_KERNEL, &CLS_AdvUpgrade::OnBnClickedButtonAdvBackupKernel)
	ON_BN_CLICKED(IDC_BUTTON_ADV_UPGRADE_BIN, &CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeBin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ADV_UPGRADE_SELECT_BIN, &CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeSelectBin)
	ON_BN_CLICKED(IDC_BUTTON_ADV_UPGRADE_SELECT_BOX, &CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeSelectBox)
	ON_BN_CLICKED(IDC_BUTTON_ADV_UPGRADE_CLEAR_BIN, &CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeClearBin)
	ON_BN_CLICKED(IDC_BUTTON_ADV_UPGRADE_CLEAR_BOX, &CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeClearBox)
	ON_BN_CLICKED(IDC_BUTTON_ADV_UPGRADE_BOX, &CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeBox)
	ON_MESSAGE(WM_UPGRADE_MESSAGE, &CLS_AdvUpgrade::OnMessgeProcess)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_BROWSE, &CLS_AdvUpgrade::OnBnClickedButtonConfigBrowse)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_INPUT, &CLS_AdvUpgrade::OnBnClickedButtonConfigInput)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_OUTPUT, &CLS_AdvUpgrade::OnBnClickedButtonConfigOutput)
END_MESSAGE_MAP()


// CLS_AdvUpgrade message handlers
int CALLBACK OutputPathCallbackProc(HWND hwnd, UINT uMsg, LPARAM wParam, LPARAM lParam)   
{   
	if  (uMsg == BFFM_INITIALIZED )
	{   
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lParam);   
	}   
	return 0;  
}


void CLS_AdvUpgrade::OnBnClickedButtonAdvBackupKernel()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return ;
	}
	int iRet = NetClient_BackupKernel(m_iLogonID); 
	if (iRet < 0 )
	{
		PDEVICE_INFO Device = FindDevice(m_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_FAIL, "","NetClient_BackupKernel(%s, %d)", Device->cIP, m_iLogonID);
		}
	}
}

void CLS_AdvUpgrade::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	UpdateUpgradeProgress();
}

void CLS_AdvUpgrade::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	switch(_wParam)
	{
	case WCM_BUCKUP_KERNEL:
		UI_UpdateBackupStatus(_iLogonID, (int)_iLParam);
	case WCM_ERR_ORDER:
		DeleteUpgrade(_iLogonID);
	}
}

void CLS_AdvUpgrade::UI_UpdateBackupStatus(int _iLogonID, int _iStatus)
{
	if (_iStatus)
	{
		PDEVICE_INFO Device = FindDevice(_iLogonID);
		if (Device)
		{
			AddLog(LOG_TYPE_MSG, "","Backup Success(IP:%s, LogonID:%d)", Device->cIP, _iLogonID);
		}
	}
	else
	{
		PDEVICE_INFO  Device = FindDevice(_iLogonID);	
		if (Device)
		{
			AddLog(LOG_TYPE_MSG, "","Backup Error(IP:%s, LogonID:%d)", Device->cIP, _iLogonID);
		}
	}
}
void CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeBin()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return ;
	}
	if (IsInUpGradeList())
	{
		return;
	}
	UpdateData(TRUE);
	if (m_szKernelFile != "")
	{
		int iMBRet = MessageBox("关闭对讲", _T(""), MB_OKCANCEL);
		if (iMBRet == IDOK)
		{
			StopTalk();
			int iRet = NetClient_Upgrade_V4(m_iLogonID, m_szKernelFile.GetBuffer(), UPGRADE_PROGRAM, (UPGRADE_NOTIFY_V4) KernelGrageNotify);
			if (iRet < 0 )
			{
				PDEVICE_INFO Device = FindDevice(m_iLogonID);	
				if (Device)
				{
					AddLog(LOG_TYPE_FAIL, "","NetClient_UpgradeProgram(%s, %d)", Device->cIP, m_iLogonID);
				}
			}
			else
			{
				stUpgradeParam *tmpUpgrade = new stUpgradeParam();
				tmpUpgrade->m_iUpgradeType = UPGRADE_KERNEL;
				tmpUpgrade->m_iLogonID = m_iLogonID;
				m_lstUpgrade.push_back(tmpUpgrade);
			}
		}
	}
}

BOOL CLS_AdvUpgrade::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpDate_Text();
	// TODO:  Add extra initialization here
	m_ProgressCtrlUpgradeBin.SetRange(1, 100);
	m_ProgressCtrlUpgradeBin.SetPos(1);
	m_ProgressCtrlUpgradeBox.SetRange(1, 100);
	m_ProgressCtrlUpgradeBox.SetPos(1);
	SetTimer(TIMER_CHECK_UPGRADE_PROGRESS, 1000, NULL);
	g_UpgradeMsgHwnd = m_hWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLS_AdvUpgrade::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CLS_BasePage::DestroyWindow();
}

void CLS_AdvUpgrade::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_CHECK_UPGRADE_PROGRESS)
	{
		UpdateUpgradeProgress();
	}
	CLS_BasePage::OnTimer(nIDEvent);
}

void CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeSelectBin()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, _T(".bin"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("bin文件(*.bin)|*.bin|所有文件(*.*)|*.*||"));
	if (IDOK == fileDlg.DoModal())
	{
		if (fileDlg.GetFileExt() != _T("bin"))
		{
			return;
		}
		m_szKernelFile = fileDlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeSelectBox()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, _T(".box"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("(*.box)|*.box|所有文件(*.*)|*.*||"));
	if (IDOK == fileDlg.DoModal())
	{
		if (fileDlg.GetFileExt() != _T("box"))
		{
			return;
		}
		m_szWebBoxFile = fileDlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeClearBin()
{
	// TODO: Add your control notification handler code here
	m_szKernelFile = "";
	UpdateData(FALSE);
}

void CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeClearBox()
{
	// TODO: Add your control notification handler code here
	m_szWebBoxFile = "";
	UpdateData(FALSE);
}

void CLS_AdvUpgrade::OnBnClickedButtonAdvUpgradeBox()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		return ;
	}
	if (IsInUpGradeList())
	{
		return;
	}
	UpdateData(TRUE);
	if (m_szWebBoxFile != "")
	{
		int iMBRet = MessageBox("关闭对讲", _T(""), MB_OKCANCEL);
		if (iMBRet == IDOK)
		{
			StopTalk();
			int iRet = NetClient_Upgrade_V4(m_iLogonID, m_szWebBoxFile.GetBuffer(), UPGRADE_WEB, (UPGRADE_NOTIFY_V4)WebUpGrageNotify);
			if (iRet < 0 )
			{
				PDEVICE_INFO Device = FindDevice(m_iLogonID);	
				if (Device)
				{
					AddLog(LOG_TYPE_FAIL, "","NetClient_UpgradeWebPage(%s, %d)", Device->cIP, m_iLogonID);
				}
			}
			else
			{
				stUpgradeParam *tmpUpgrade = new stUpgradeParam();
				tmpUpgrade->m_iUpgradeType = UPGRADE_WEBPAGE;
				tmpUpgrade->m_iLogonID = m_iLogonID;
				m_lstUpgrade.push_back(tmpUpgrade);
			}
		}
	}
}

BOOL CLS_AdvUpgrade::IsInUpGradeList()
{
	BOOL bIn = FALSE;
	for (list<stUpgradeParam*>::iterator it = m_lstUpgrade.begin();it != m_lstUpgrade.end();it++)
	{
		stUpgradeParam *tmpUpgrade = *it;
		if (tmpUpgrade->m_iLogonID == m_iLogonID)
		{
			bIn = TRUE;
			break;
		}
	}
	return bIn;
}

int CLS_AdvUpgrade::GetUpGradeType( int _iLogonID )
{
	for (list<stUpgradeParam*>::iterator it = m_lstUpgrade.begin();it != m_lstUpgrade.end();it++)
	{
		stUpgradeParam *tmpUpgrade = *it;
		if (tmpUpgrade->m_iLogonID == m_iLogonID)
		{
			return tmpUpgrade->m_iUpgradeType;
		}
	}	
	return -1;
}

void  CLS_AdvUpgrade::WebUpGrageNotify( int _iLogonID, int _iServerState , int _iUser)
{
	::PostMessage(g_UpgradeMsgHwnd, WM_UPGRADE_MESSAGE, _iLogonID, _iServerState);
}

void  CLS_AdvUpgrade::KernelGrageNotify( int _iLogonID, int _iServerState , int _iUser)
{
	::PostMessage(g_UpgradeMsgHwnd, WM_UPGRADE_MESSAGE, _iLogonID, _iServerState);
}

LRESULT  CLS_AdvUpgrade::OnMessgeProcess(WPARAM wParam, LPARAM lParam)
{
	int iLogonID = (int)wParam;
	int iUpgradeState = (int)lParam;
	int iUpgradeType = GetUpGradeType(iLogonID);
	if(iUpgradeState != PRO_UPGRADE_READY && iUpgradeState != WEB_UPGRADE_READY)
	{
		DeleteUpgrade(iLogonID);
	}

	if (iUpgradeType == UPGRADE_KERNEL)
	{
		if (iUpgradeState == PRO_UPGRADE_OK)
		{
			PDEVICE_INFO Device = FindDevice(iLogonID);	
			if (Device)
			{
				AddLog(LOG_TYPE_MSG, "", "UPGRADE_KERNEL OK(IP:%s, LogonID:%d)", Device->cIP, iLogonID);
			}
		}
		else if(iUpgradeState== PRO_UPGRADE_ERROR)
		{
			PDEVICE_INFO Device = FindDevice(iLogonID);	
			if (Device)
			{
				AddLog(LOG_TYPE_MSG,"", "UPGRADE_KERNEL ERROR(IP:%s, LogonID:%d)", Device->cIP, iLogonID);
			}
		}
		else if(iUpgradeState== PRO_UPGRADE_READY)
		{
			PDEVICE_INFO Device = FindDevice(iLogonID);	
			if (Device)
			{
				AddLog(LOG_TYPE_MSG,"", "UPGRADE_KERNEL READY(IP:%s, LogonID:%d)", Device->cIP, iLogonID);
			}
		}
	}
	else if (iUpgradeType == UPGRADE_WEBPAGE)
	{
		if (iUpgradeState == WEB_UPGRADE_OK)
		{
			PDEVICE_INFO Device = FindDevice(iLogonID);	
			if (Device)
			{
				AddLog(LOG_TYPE_MSG, "", "UPGRADE_WEBPAGE OK(IP:%s, LogonID:%d)", Device->cIP, iLogonID);
			}
		}
		else if (iUpgradeState== WEB_UPGRADE_ERROR)
		{
			PDEVICE_INFO Device = FindDevice(iLogonID);	
			if (Device)
			{
				AddLog(LOG_TYPE_MSG, "", "UPGRADE_WEBPAGE ERROR(IP:%s, LogonID:%d)", Device->cIP, iLogonID);
			}
		}
		else if(iUpgradeState== WEB_UPGRADE_READY)
		{
			PDEVICE_INFO Device = FindDevice(iLogonID);	
			if (Device)
			{
				AddLog(LOG_TYPE_MSG,"", "UPGRADE_WEBPAGE READY(IP:%s, LogonID:%d)", Device->cIP, iLogonID);
			}
		}
	}

	return 0;
}

void CLS_AdvUpgrade::DeleteUpgrade( int _iLogonID )
{
	for (list<stUpgradeParam*>::iterator it = m_lstUpgrade.begin();it != m_lstUpgrade.end();it++)
	{
		stUpgradeParam *tmpUpgrade = *it;
		if (tmpUpgrade->m_iLogonID == m_iLogonID)
		{
			m_lstUpgrade.erase(it);
			delete tmpUpgrade;
			break;
		}
	}
}

void CLS_AdvUpgrade::OnLanguageChanged( int _iLanguage )
{
	UI_UpDate_Text();	
	UpdateUpgradeProgress();
}

void CLS_AdvUpgrade::UI_UpDate_Text()
{
	SetDlgItemText(IDC_STATIC_ADV_UPGRADE_SELECT_BIN, GetTextEx(IDS_ADV_UPGTADE_SELECT_FILE) + "(.bin)");
	SetDlgItemTextEx(IDC_BUTTON_ADV_UPGRADE_SELECT_BIN, IDS_ADV_UPGRADE_BROWSE);
	SetDlgItemTextEx(IDC_BUTTON_ADV_UPGRADE_CLEAR_BIN, IDS_ADV_UPGRADE_CLEAN);
	SetDlgItemTextEx(IDC_BUTTON_ADV_BACKUP_KERNEL, IDS_ADV_BACKUP_KERNEL);
	SetDlgItemTextEx(IDC_BUTTON_ADV_UPGRADE_BIN, IDS_ADV_UPGRADE_UPGRADE);
	SetDlgItemText(IDC_STATIC_ADV_UPGRADE_SELECT_BOX, GetTextEx(IDS_ADV_UPGTADE_SELECT_FILE) + "(.box)");
	SetDlgItemTextEx(IDC_BUTTON_ADV_UPGRADE_SELECT_BOX, IDS_ADV_UPGRADE_BROWSE);
	SetDlgItemTextEx(IDC_BUTTON_ADV_UPGRADE_CLEAR_BOX, IDS_ADV_UPGRADE_CLEAN);
	SetDlgItemTextEx(IDC_BUTTON_ADV_UPGRADE_BOX, IDS_ADV_UPGRADE_UPGRADE);
	SetDlgItemTextEx(IDC_STATIC_UPGRADE_KERNEL, IDS_CONFIG_ADV_UPGRADE_KERNEL);
	SetDlgItemTextEx(IDC_STATIC_UPGRADE_WEB, IDS_CONFIG_ADV_UPGRADE_WEB);
	SetDlgItemTextEx(IDC_STATIC_KERNEL,IDS_CONFIG_UPGRADE_KERNEL);
	SetDlgItemTextEx(IDC_STATIC_WEBPAGE,IDS_CONFIG_UPGRADE_WEBPAGE);
	SetDlgItemTextEx(IDC_STATIC_VERSION_CONFIG,IDS_CONFIG_UPGRADE_VERTICALSYNC);
	SetDlgItemTextEx(IDC_BUTTON_CONFIG_BROWSE,IDS_ADV_UPGRADE_BROWSE);
	SetDlgItemTextEx(IDC_BUTTON_CONFIG_OUTPUT,IDS_VCA_EXPORT);
	SetDlgItemTextEx(IDC_BUTTON_CONFIG_INPUT, IDS_VCA_INPUT);
}

void CLS_AdvUpgrade::UpdateUpgradeProgress()
{
	if (IsInUpGradeList())
	{
		int iUpradeType = GetUpGradeType(m_iLogonID);
		if (iUpradeType == UPGRADE_KERNEL)
		{
			int iProgress = NetClient_GetUpgradePercent(m_iLogonID);
			m_ProgressCtrlUpgradeBin.SetPos(iProgress);
			CString szProgress;
			szProgress.Format("%d", iProgress);
			SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BIN, GetTextEx(IDS_ADV_UPGRADE_COMPLETE) + szProgress +"%");
			SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BOX, "");
			m_ProgressCtrlUpgradeBox.SetPos(0);
		}
		else if (iUpradeType == UPGRADE_WEBPAGE)
		{
			int iProgress = NetClient_GetUpgradePercent(m_iLogonID);
			m_ProgressCtrlUpgradeBox.SetPos(iProgress);
			CString szProgress;
			szProgress.Format("%d", iProgress);
			SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BOX, GetTextEx(IDS_ADV_UPGRADE_COMPLETE) + szProgress +"%");
			SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BIN, "");
			m_ProgressCtrlUpgradeBin.SetPos(0);
		}
		else
		{
			SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BIN, "");
			SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BOX, "");
			m_ProgressCtrlUpgradeBin.SetPos(0);
			m_ProgressCtrlUpgradeBox.SetPos(0);
		}
	}
	else
	{
		SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BIN, "");
		SetDlgItemText(IDC_STATIC_ADV_UPGREAD_STATUS_BOX, "");
		m_ProgressCtrlUpgradeBin.SetPos(0);
		m_ProgressCtrlUpgradeBox.SetPos(0);
	}
}

void CLS_AdvUpgrade::StopTalk()
{
// 	PDEVICE_INFO Device = FindDevice(iLogonID);	
// 	if (Device)
// 	{
// 		AddLog(LOG_TYPE_MSG, "UPGRADE_KERNEL ERROR(IP:%s, LogonID:%d)", Device->cIP, iLogonID);
// 	}	
}

void CLS_AdvUpgrade::OnBnClickedButtonConfigBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "All files(*.*)|*.*|box files(*.box)|*.box||");
	if (IDOK == fileDlg.DoModal())
	{
		if (fileDlg.GetFileExt() != _T("box"))
		{
			AddLog(LOG_TYPE_FAIL, "", "Illegal files!");
			return;
		}

		m_strConfigPath = fileDlg.GetPathName();
		m_edtConfigPath.SetWindowText(m_strConfigPath);
	}
}

void CLS_AdvUpgrade::OnBnClickedButtonConfigInput()
{
	// TODO: Add your control notification handler code here
	CString strPathName;
	m_edtConfigPath.GetWindowText(strPathName);
	if (strPathName.GetLength() >= 128)
	{
		AddLog(LOG_TYPE_FAIL, "", "Illegal system path!");
		return;
	}
	if (strPathName == "")
	{
		AddLog(LOG_TYPE_FAIL, "", "Illegal system path!");
		return;
	}
	if (strPathName.Right(3) == _T("box"))
	{
		NetClient_TalkEnd(m_iLogonID);
		int iRet = NetClient_Upgrade_V4(m_iLogonID, (LPSTR)(LPCTSTR)strPathName, UPGRADE_WEB, (UPGRADE_NOTIFY_V4)WebUpGrageNotify);
		if (iRet == 0)
		{
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "Input faid!");
		}
	}
}

void CLS_AdvUpgrade::OnBnClickedButtonConfigOutput()
{
	// TODO: Add your control notification handler code here
	CString strSystemOutputPath;
	CString strFileName;
	strSystemOutputPath = GetSystemOutputPath();
	COleDateTime m_Date = COleDateTime::GetCurrentTime ();
	strFileName = m_Date.Format("%Y%m%d%H%M%S");
	strFileName = strFileName + ".box";                                 //导出数据的文件名称
	strSystemOutputPath = strSystemOutputPath + "\\" +strFileName;
	if (strSystemOutputPath.GetLength() >= 128)
	{
		AddLog(LOG_TYPE_FAIL, "", "Illegal system path!");
		return;
	}
	if (strSystemOutputPath != "")
	{
		ExportConfig stExportConfig = {0};
		int iReturnByte = 0;
		stExportConfig.iSize = sizeof(ExportConfig);
		int iCount = -1;
		for(int i = 0; i < CFGFILE_NUM; i++)
		{
			if(i < FILE_COUNT)
			{
				strcpy_s(stExportConfig.cFileList[i], CONST_pcConfigFile[i]);
				iCount++;
			}	
		}
		stExportConfig.iCount = iCount;
		strcpy(stExportConfig.cFileOut,(LPSTR)(LPCTSTR)strSystemOutputPath);
		int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_EXPORT_CONFIG, -1, &stExportConfig, sizeof(ExportConfig), &iReturnByte);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "Output faid!");
		}
	}
}

CString CLS_AdvUpgrade::GetSystemOutputPath()
{

	CString sFolder = "";   
	LPMALLOC pMalloc;   
	CString cstrPath = "D:\\";

	if (::SHGetMalloc(&pMalloc)     ==     NOERROR)   
	{   
		BROWSEINFO     bi;   
		char     pszBuffer[MAX_PATH];   
		LPITEMIDLIST     pidl;   

		bi.hwndOwner     =     GetSafeHwnd();   
		bi.pidlRoot     =     NULL;   
		bi.pszDisplayName     =     pszBuffer;   
		bi.lpszTitle     =     _T("");   
		bi.ulFlags     =     BIF_RETURNFSANCESTORS     |     BIF_RETURNONLYFSDIRS;   
		bi.lpfn      = OutputPathCallbackProc;  //回调函数
		bi.lParam    = (LPARAM)(LPCTSTR)cstrPath;   

		if     ((pidl     =     ::SHBrowseForFolder(&bi))     !=     NULL)   
		{   
			if     (::SHGetPathFromIDList(pidl,     pszBuffer))   
			{     
				sFolder.Append(pszBuffer);
				if (sFolder.Right(1).CompareNoCase(_T("\\")))
				{
					sFolder.Append(_T("\\"));
				}

			}   
			pMalloc->Free(pidl);   
		}   
		pMalloc->Release();   
	}
	return sFolder;
}
