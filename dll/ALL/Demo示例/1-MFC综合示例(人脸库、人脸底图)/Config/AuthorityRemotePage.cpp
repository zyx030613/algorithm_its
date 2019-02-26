// AuthorityRemotePage.cpp : implementation file
//author zhy 2013.04.09

#include "stdafx.h"
#include "AuthorityRemotePage.h"

#define HAND_CLEAR_ALARM	15
#define POWEROFF_RESTART	16			
#define RECORD				17
#define LOG_SEARCH			18
#define ALARM_SET			19
#define CHANNEL_MANAGEMENT	20
#define PARAM_SET			21
#define SYSTEM_SET			22
#define USER_MANAGEMENT		23
#define TALKBACK			24

// CLS_AuthorityRemotePage dialog

IMPLEMENT_DYNAMIC(CLS_AuthorityRemotePage, CDialog)

CLS_AuthorityRemotePage::CLS_AuthorityRemotePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AuthorityRemotePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iAuthority = 0;
	m_bIsAdmin = TRUE;
}

CLS_AuthorityRemotePage::~CLS_AuthorityRemotePage()
{
}

void CLS_AuthorityRemotePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USER_CHOISE, m_cboUserChoise);
	DDX_Control(pDX, IDC_CHECK_HAND_CLEAR_ALARM, m_chkRemoteRight[0]);
	DDX_Control(pDX, IDC_CHECK_RESTART, m_chkRemoteRight[1]);
	DDX_Control(pDX, IDC_CHECK_RECORD, m_chkRemoteRight[2]);
	DDX_Control(pDX, IDC_CHECK_LOG_SEARCH, m_chkRemoteRight[3]);
	DDX_Control(pDX, IDC_CHECK_ALARM_SET, m_chkRemoteRight[4]);
	DDX_Control(pDX, IDC_CHECK_CHANNEL_MANAGEMENT, m_chkRemoteRight[5]);
	DDX_Control(pDX, IDC_CHECK_PARAM_SET, m_chkRemoteRight[6]);
	DDX_Control(pDX, IDC_CHECK_SYSTEM_SET, m_chkRemoteRight[7]);
	DDX_Control(pDX, IDC_CHECK_USER_MANAGEMENT, m_chkRemoteRight[8]);
	DDX_Control(pDX, IDC_CHECK_TALKBACK, m_chkRemoteRight[9]);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	DDX_Control(pDX, IDC_CHECK_ALL, m_chkAll);
}


BEGIN_MESSAGE_MAP(CLS_AuthorityRemotePage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_CHOISE, &CLS_AuthorityRemotePage::OnCbnSelchangeComboUserChoise)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CLS_AuthorityRemotePage::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLS_AuthorityRemotePage::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BTN_VCACARCHECK_EN, &CLS_AuthorityRemotePage::OnBnClickedBtnVcacarcheckEn)
	ON_BN_CLICKED(IDC_BTN_VCACARCHECK_DISEN, &CLS_AuthorityRemotePage::OnBnClickedBtnVcacarcheckDisen)
	ON_BN_CLICKED(IDC_BTN_SNAPSHOT, &CLS_AuthorityRemotePage::OnBnClickedBtnSnapshot)
END_MESSAGE_MAP()

// CLS_AuthorityRemotePage message handlers
BOOL CLS_AuthorityRemotePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();
	return TRUE;
}

void CLS_AuthorityRemotePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	UI_UpdateUserList();
	UI_UpdateEnableList();
	UI_UpdateRemoteAuthority();
}

void CLS_AuthorityRemotePage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_AuthorityRemotePage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_USER_CHOISE, IDS_USER_CHOISE);
	SetDlgItemTextEx(IDC_STATIC_REMOTE_RIGHT, IDS_CFG_REMOTE_RIGHT);
	SetDlgItemTextEx(IDC_CHECK_HAND_CLEAR_ALARM, IDS_CFG_RIGHT_HAND_CLEAR_ALARM);
	SetDlgItemTextEx(IDC_CHECK_RESTART, IDS_CFG_RIGHT_SHUTDOWN_RESTART);
	SetDlgItemTextEx(IDC_CHECK_RECORD, IDS_CFG_RIGHT_RECORD);
	SetDlgItemTextEx(IDC_CHECK_TALKBACK, IDS_CFG_RIGHT_TALKBACK);
	SetDlgItemTextEx(IDC_CHECK_TALKBACK, IDS_CFG_RIGHT_TALKBACK);
	SetDlgItemTextEx(IDC_CHECK_LOG_SEARCH, IDS_CFG_RIGHT_LOG_SEARCH);
	SetDlgItemTextEx(IDC_CHECK_ALARM_SET, IDS_CFG_RIGHT_ALARM_SET);
	SetDlgItemTextEx(IDC_CHECK_CHANNEL_MANAGEMENT, IDS_CFG_RIGHT_CHANNEL_MANAGEMENT);
	SetDlgItemTextEx(IDC_CHECK_PARAM_SET, IDS_CFG_RIGHT_PARAM_SET);
	SetDlgItemTextEx(IDC_CHECK_SYSTEM_SET, IDS_CFG_RIGHT_SYSTEM_SET);
	SetDlgItemTextEx(IDC_CHECK_USER_MANAGEMENT, IDS_CFG_RIGHT_USER_MANAGEMENT);
	SetDlgItemTextEx(IDC_BUTTON_SET, IDS_CFG_RIGHT_SET);
	SetDlgItemTextEx(IDC_CHECK_ALL, IDS_CFG_RIGHT_ALL_CHANNEL);

	SetDlgItemTextEx(IDC_STATIC, IDS_INTELLIGENT_ANALYSIS_OF_SECNE_CHANGES);
	SetDlgItemTextEx(IDC_STATIC_CAR_TEST, IDS_CAR_TEST);
	SetDlgItemTextEx(IDC_STATIC_QUALITY, IDS_CAPTURE_QUALITY);
	SetDlgItemTextEx(IDC_BTN_VCACARCHECK_EN, IDS_CONFIG_FTP_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_BTN_VCACARCHECK_DISEN, IDS_CONFIG_FTP_SNAPSHOT_DISABLE);
	SetDlgItemTextEx(IDC_BTN_SNAPSHOT, IDS_SCENE_CAPTURE);
}

BOOL CLS_AuthorityRemotePage::UI_UpdateRemoteAuthority()
{
	if (m_iLogonID < 0 || !m_bIsAdmin)
		return FALSE;

	UI_UpdateEnableList();
	USER_AUTHORITY strUserAut = {0};
	int iUserAutSize = sizeof(USER_AUTHORITY);
	strUserAut.iNeedSize = sizeof(USER_AUTHORITY);
	int iIsChooseAll = 1;
	CString strName;
	int iCurUser = m_cboUserChoise.GetCurSel();
	m_cboUserChoise.GetLBText(iCurUser, strName);
	if (strName.IsEmpty())
	{
		return FALSE;
	}
	int iRet = NetClient_GetUserAuthority(m_iLogonID, (LPSTR)(LPCSTR)strName, &strUserAut, iUserAutSize);
	if (iRet==0)
	{
		for (int i=0; i<REMOTE_AUTHORITY_NUM; i++)
		{
			if (strUserAut.strAutInfo[HAND_CLEAR_ALARM+i].uiList[0] == 1)
			{
				m_chkRemoteRight[i].SetCheck(BST_CHECKED);
			}
			else
			{
				m_chkRemoteRight[i].SetCheck(BST_UNCHECKED);
				m_chkAll.SetCheck(BST_UNCHECKED);
				if (m_iIsAllowSet[i] == 1)
				{
					iIsChooseAll = 0;
				}
			}
		}
	}
	if (iIsChooseAll == 1)
	{
		m_chkAll.SetCheck(BST_CHECKED);
	}
	return TRUE;
}

BOOL CLS_AuthorityRemotePage::UI_UpdateUserList()
{
	if (m_iLogonID < 0)
		return FALSE;

	m_cboUserChoise.ResetContent();
	int iUserNum = 0;
	char cUserName[128] = {0};
	char cPassword[128]	= {0};
	int iAuthority = 0;
	//所有已登陆的用户
	int iRet = NetClient_GetUserNum(m_iLogonID, &iUserNum);
	if (iRet <0)
	{
		m_bIsAdmin = FALSE;
		return FALSE;
	}
	m_bIsAdmin = TRUE;
	for (int i=0; i<iUserNum; i++)
	{
		//int iRet = -1;
		if (NetClient_GetUserInfo(m_iLogonID, i, cUserName, cPassword, &iAuthority) == 0)
		{
			m_cboUserChoise.InsertString(i, cUserName);	
		}
	}
	m_cboUserChoise.SetCurSel(0);
	return TRUE;
}

BOOL CLS_AuthorityRemotePage::UI_UpdateEnableList()
{
	if (m_iLogonID < 0)
		return FALSE;

	for (int i=0; i<REMOTE_AUTHORITY_NUM; i++)
	{
		m_chkRemoteRight[i].SetCheck(BST_UNCHECKED);
		m_chkRemoteRight[i].EnableWindow(false);
		m_iIsAllowSet[i] = 0;
	}
	int iCurUser = m_cboUserChoise.GetCurSel();
	char cUserName[128] = {0};
	char cPassword[128]	= {0};
	int iRet = NetClient_GetUserInfo(m_iLogonID, iCurUser, cUserName, cPassword, &m_iAuthority);

	GROUP_AUTHORITY strGroupAut = {0};
	strGroupAut.iSize = sizeof(GROUP_AUTHORITY);
	strGroupAut.iGroupNO = m_iAuthority;
	int iBufSize = sizeof(GROUP_AUTHORITY);
	//获得组别列表
	iRet = NetClient_GetGroupAuthority(m_iLogonID, &strGroupAut, iBufSize);
	if (iRet == 0)
	{
		for (int i=0; i<MAX_MODIFY_AUTHORITY_NUM; i++)
		{
			if (i<32)
			{
				if (strGroupAut.uiList[0]>>i & 1)
				{
					switch (i)
					{
					case HAND_CLEAR_ALARM:
						{
							GetDlgItem(IDC_CHECK_HAND_CLEAR_ALARM)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case POWEROFF_RESTART:
						{
							GetDlgItem(IDC_CHECK_RESTART)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case RECORD:
						{
							GetDlgItem(IDC_CHECK_RECORD)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case LOG_SEARCH:
						{
							GetDlgItem(IDC_CHECK_LOG_SEARCH)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case ALARM_SET:
						{
							GetDlgItem(IDC_CHECK_ALARM_SET)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case CHANNEL_MANAGEMENT:
						{
							GetDlgItem(IDC_CHECK_CHANNEL_MANAGEMENT)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case PARAM_SET:
						{
							GetDlgItem(IDC_CHECK_PARAM_SET)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case SYSTEM_SET:
						{
							GetDlgItem(IDC_CHECK_SYSTEM_SET)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case USER_MANAGEMENT:
						{
							GetDlgItem(IDC_CHECK_USER_MANAGEMENT)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					case TALKBACK:
						{
							GetDlgItem(IDC_CHECK_TALKBACK)->EnableWindow(true);
							m_iIsAllowSet[i-HAND_CLEAR_ALARM] = 1;
						}
						break;
					default:
						break;
					}
				}
			}
			//留以后扩展到32个权限时用
			else if (i>=32)
			{
			}
		}
	}
	return TRUE;
}
void CLS_AuthorityRemotePage::OnCbnSelchangeComboUserChoise()
{
	// TODO: Add your control notification handler code here
	UI_UpdateRemoteAuthority();
}

void CLS_AuthorityRemotePage::OnBnClickedCheckAll()
{
	// TODO: Add your control notification handler code here
	if (!m_bIsAdmin)
		return ;

	GROUP_AUTHORITY strGroupAut = {0};
	strGroupAut.iSize = sizeof(GROUP_AUTHORITY);
	strGroupAut.iGroupNO = m_iAuthority;
	int iBufSize = sizeof(GROUP_AUTHORITY);
	//获得组别列表
	int iRet = NetClient_GetGroupAuthority(m_iLogonID, &strGroupAut, iBufSize);

	if (m_chkAll.GetCheck() == BST_CHECKED)
	{
		for (int i=0; i<MAX_MODIFY_AUTHORITY_NUM; i++)
		{
			if (i<32)
			{
				if (strGroupAut.uiList[0]>>i & 1)
				{
					switch (i)
					{
					case HAND_CLEAR_ALARM:
						{
							m_chkRemoteRight[0].SetCheck(BST_CHECKED);
						}
						break;
					case POWEROFF_RESTART:
						{
							m_chkRemoteRight[1].SetCheck(BST_CHECKED);
						}
						break;
					case RECORD:
						{
							m_chkRemoteRight[2].SetCheck(BST_CHECKED);
						}
						break;
					case LOG_SEARCH:
						{
							m_chkRemoteRight[3].SetCheck(BST_CHECKED);
						}
						break;
					case ALARM_SET:
						{
							m_chkRemoteRight[4].SetCheck(BST_CHECKED);
						}
						break;
					case CHANNEL_MANAGEMENT:
						{
							m_chkRemoteRight[5].SetCheck(BST_CHECKED);
						}
						break;
					case PARAM_SET:
						{
							m_chkRemoteRight[6].SetCheck(BST_CHECKED);
						}
						break;
					case SYSTEM_SET:
						{
							m_chkRemoteRight[7].SetCheck(BST_CHECKED);
						}
						break;
					case USER_MANAGEMENT:
						{
							m_chkRemoteRight[8].SetCheck(BST_CHECKED);
						}
						break;
					case TALKBACK:
						{
							m_chkRemoteRight[9].SetCheck(BST_CHECKED);
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int i=0; i<REMOTE_AUTHORITY_NUM; i++)
		{
			m_chkRemoteRight[i].SetCheck(BST_UNCHECKED);
		}
	}
}

void CLS_AuthorityRemotePage::OnBnClickedButtonSet()
{
	// TODO: Add your control notification handler code here
	if (!m_bIsAdmin)
		return ;

	CString strName;
	int iCurUser = m_cboUserChoise.GetCurSel();
	m_cboUserChoise.GetLBText(iCurUser, strName);

	if (strName == _T("Admin"))
	{
		MessageBox(GetTextEx(IDS_USER_Message17), _T(""));
		return;
	}

	USER_AUTHORITY strUserAut = {0};
	int iAuthorityIndex = 0;
	for (int i=0; i<REMOTE_AUTHORITY_NUM; i++)
	{
		if (m_chkRemoteRight[i].GetCheck() == BST_CHECKED)
		{
			strUserAut.strAutInfo[iAuthorityIndex].iLevel = HAND_CLEAR_ALARM+i;
			strUserAut.strAutInfo[iAuthorityIndex].uiList[0] = 1;
		}
		else 
		{
			strUserAut.strAutInfo[iAuthorityIndex].iLevel = HAND_CLEAR_ALARM+i;
			strUserAut.strAutInfo[iAuthorityIndex].uiList[0] = 0;
		}
		if (m_iIsAllowSet[i] == 1)
		{
			iAuthorityIndex++;
		}
	}
	//把该权限组别有的权限无论选还是未选都设向设备，
	//如果可设权限数量超出10，则根据具体次数调用多次TDModifyUserAuthority接口
	int iUserAutSize = sizeof(USER_AUTHORITY);
	strUserAut.iNeedSize = sizeof(AUTHORITY_INFO)*iAuthorityIndex+4;
	int iSendRound = (iAuthorityIndex%10 == 0)?iAuthorityIndex/10:iAuthorityIndex/10+1;
	USER_AUTHORITY strTmpUA = {0};
	if (iSendRound>1)
	{
		//如果可设权限数较多，则选出10的整数倍，这样每次设向设备的结构体大小是一样的。
		//并且设的内容从strUserAut.strAutInfo通过10的倍数按iSendRound移位复制到strTmpUA里即可
		for (int i=0; i<iSendRound-1; i++)
		{
			strTmpUA.iNeedSize = sizeof(AUTHORITY_INFO)*10+4;
			memcpy(strTmpUA.strAutInfo, &strUserAut.strAutInfo[i*10], sizeof(AUTHORITY_INFO)*10);		//根据iSendRound，每次移的起始位置为10*iSendRound
			int iRet = NetClient_ModifyUserAuthority(m_iLogonID, (LPSTR)(LPCSTR)strName, &strTmpUA, iUserAutSize);
		}
		//最后补个不够10个权限内容设到设备中去
		strTmpUA.iNeedSize = sizeof(AUTHORITY_INFO)*(iAuthorityIndex%10)+4;
		memcpy(strTmpUA.strAutInfo, &strUserAut.strAutInfo[(iSendRound-1)*10], sizeof(AUTHORITY_INFO)*(iAuthorityIndex%10));		//最后一次不足10个权限，移的起始位置为iAuthorityIndex-10*iSendRound
		int iRet = NetClient_ModifyUserAuthority(m_iLogonID, (LPSTR)(LPCSTR)strName, &strTmpUA, iUserAutSize);
	}
	else if (iSendRound == 1)
	{
		//可设权限数不超过10的情况 
		int iRet = NetClient_ModifyUserAuthority(m_iLogonID, (LPSTR)(LPCSTR)strName, &strUserAut, iUserAutSize);
	}
}

void CLS_AuthorityRemotePage::OnBnClickedBtnVcacarcheckEn()
{
	// TODO: Add your control notification handler code here
	int iCmd = CI_COMMON_ID_VCACARCHECK;
	int iChn = 0x7FFFFFFF;
	int iEnable = true;
	//NetClient_GetCommonEnable(m_iLogonID, iCmd, iChn, &iEnable);
	NetClient_SetCommonEnable(m_iLogonID, iCmd, iChn, iEnable);
}

void CLS_AuthorityRemotePage::OnBnClickedBtnVcacarcheckDisen()
{
	// TODO: Add your control notification handler code here
	int iCmd = CI_COMMON_ID_VCACARCHECK;
	int iChn = 0x7FFFFFFF;
	int iEnable = false;
	//NetClient_GetCommonEnable(m_iLogonID, iCmd, iChn, &iEnable);
	NetClient_SetCommonEnable(m_iLogonID, iCmd, iChn, iEnable);
}

void CLS_AuthorityRemotePage::OnBnClickedBtnSnapshot()
{
	// TODO: Add your control notification handler code here

	int iChn = 0;
	int iValue = GetDlgItemInt(IDC_EDT_QUALITY);
	NetClient_Snapshot(m_iLogonID, iChn, iValue);
}
