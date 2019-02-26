// AuthorityLocalPage.cpp : implementation file
//author zhy 2013.04.09

#include "stdafx.h"
#include "AuthorityLocalPage.h"

#define HAND_CLEAR_ALARM	7
#define RECORD_PLAYBACK		8
#define LOG_SEARCH			9
#define ALARM_SET			10
#define CHANNEL_MANAGEMENT	11
#define PARAM_SET			12
#define SYSTEM_SET			13
#define USER_MANAGEMENT		14

// CLS_AuthorityLocalPage dialog

IMPLEMENT_DYNAMIC(CLS_AuthorityLocalPage, CDialog)

CLS_AuthorityLocalPage::CLS_AuthorityLocalPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AuthorityLocalPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iAuthority = 0;
	m_bIsAdmin = TRUE;
}

CLS_AuthorityLocalPage::~CLS_AuthorityLocalPage()
{
}

void CLS_AuthorityLocalPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USER_CHOISE, m_cboUserChoise);
	DDX_Control(pDX, IDC_CHECK_HAND_CLEAR_ALARM, m_chkLocalRight[0]);
	DDX_Control(pDX, IDC_CHECK_RECORD_PLAYBACK, m_chkLocalRight[1]);
	DDX_Control(pDX, IDC_CHECK_LOG_SEARCH, m_chkLocalRight[2]);
	DDX_Control(pDX, IDC_CHECK_ALARM_SET, m_chkLocalRight[3]);
	DDX_Control(pDX, IDC_CHECK_CHANNEL_MANAGEMENT, m_chkLocalRight[4]);
	DDX_Control(pDX, IDC_CHECK_PARAM_SET, m_chkLocalRight[5]);
	DDX_Control(pDX, IDC_CHECK_SYSTEM_SET, m_chkLocalRight[6]);
	DDX_Control(pDX, IDC_CHECK_USER_MANAGEMENT, m_chkLocalRight[7]);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	DDX_Control(pDX, IDC_CHECK_ALL, m_chkAll);
}


BEGIN_MESSAGE_MAP(CLS_AuthorityLocalPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_CHOISE, &CLS_AuthorityLocalPage::OnCbnSelchangeComboUserChoise)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CLS_AuthorityLocalPage::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLS_AuthorityLocalPage::OnBnClickedButtonSet)
END_MESSAGE_MAP()

// CLS_AuthorityLocalPage message handlers
BOOL CLS_AuthorityLocalPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();
	return TRUE;
}

void CLS_AuthorityLocalPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	UI_UpdateUserList();
	UI_UpdateEnableList();
	UI_UpdateLocalAuthority();
}

void CLS_AuthorityLocalPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_AuthorityLocalPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_USER_CHOISE, IDS_USER_CHOISE);
	SetDlgItemTextEx(IDC_STATIC_LOCAL_RIGHT, IDS_CFG_LOCAL_RIGHT);
	SetDlgItemTextEx(IDC_CHECK_HAND_CLEAR_ALARM, IDS_CFG_RIGHT_HAND_CLEAR_ALARM);
	SetDlgItemTextEx(IDC_CHECK_RECORD_PLAYBACK, IDS_CFG_RIGHT_RECORD_PLAYTIME);
	SetDlgItemTextEx(IDC_CHECK_LOG_SEARCH, IDS_CFG_RIGHT_LOG_SEARCH);
	SetDlgItemTextEx(IDC_CHECK_ALARM_SET, IDS_CFG_RIGHT_ALARM_SET);
	SetDlgItemTextEx(IDC_CHECK_CHANNEL_MANAGEMENT, IDS_CFG_RIGHT_CHANNEL_MANAGEMENT);
	SetDlgItemTextEx(IDC_CHECK_PARAM_SET, IDS_CFG_RIGHT_PARAM_SET);
	SetDlgItemTextEx(IDC_CHECK_SYSTEM_SET, IDS_CFG_RIGHT_SYSTEM_SET);
	SetDlgItemTextEx(IDC_CHECK_USER_MANAGEMENT, IDS_CFG_RIGHT_USER_MANAGEMENT);
	SetDlgItemTextEx(IDC_BUTTON_SET, IDS_CFG_RIGHT_SET);
	SetDlgItemTextEx(IDC_CHECK_ALL, IDS_CFG_RIGHT_ALL_CHANNEL);


}

BOOL CLS_AuthorityLocalPage::UI_UpdateLocalAuthority()
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
	int iRet = NetClient_GetUserAuthority(m_iLogonID, (LPSTR)(LPCSTR)strName, &strUserAut, iUserAutSize);
	if (iRet==0)
	{
		for (int i=0; i<LOCAL_AUTHORITY_NUM; i++)
		{
			if (strUserAut.strAutInfo[HAND_CLEAR_ALARM+i].uiList[0] == 1)
			{
				m_chkLocalRight[i].SetCheck(BST_CHECKED);
			}
			else
			{
				m_chkLocalRight[i].SetCheck(BST_UNCHECKED);
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

BOOL CLS_AuthorityLocalPage::UI_UpdateUserList()
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

BOOL CLS_AuthorityLocalPage::UI_UpdateEnableList()
{
	if (m_iLogonID < 0)
		return FALSE;

	for (int i=0; i<LOCAL_AUTHORITY_NUM; i++)
	{
		m_chkLocalRight[i].EnableWindow(false);
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
					case RECORD_PLAYBACK:
						{
							GetDlgItem(IDC_CHECK_RECORD_PLAYBACK)->EnableWindow(true);
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
void CLS_AuthorityLocalPage::OnCbnSelchangeComboUserChoise()
{
	// TODO: Add your control notification handler code here
	UI_UpdateLocalAuthority();
}

void CLS_AuthorityLocalPage::OnBnClickedCheckAll()
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
							m_chkLocalRight[0].SetCheck(BST_CHECKED);
						}
						break;
					case RECORD_PLAYBACK:
						{
							m_chkLocalRight[1].SetCheck(BST_CHECKED);
						}
						break;
					case LOG_SEARCH:
						{
							m_chkLocalRight[2].SetCheck(BST_CHECKED);
						}
						break;
					case ALARM_SET:
						{
							m_chkLocalRight[3].SetCheck(BST_CHECKED);
						}
						break;
					case CHANNEL_MANAGEMENT:
						{
							m_chkLocalRight[4].SetCheck(BST_CHECKED);
						}
						break;
					case PARAM_SET:
						{
							m_chkLocalRight[5].SetCheck(BST_CHECKED);
						}
						break;
					case SYSTEM_SET:
						{
							m_chkLocalRight[6].SetCheck(BST_CHECKED);
						}
						break;
					case USER_MANAGEMENT:
						{
							m_chkLocalRight[7].SetCheck(BST_CHECKED);
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
		for (int i=0; i<LOCAL_AUTHORITY_NUM; i++)
		{
			m_chkLocalRight[i].SetCheck(BST_UNCHECKED);
		}
	}
}

void CLS_AuthorityLocalPage::OnBnClickedButtonSet()
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
	for (int i=0; i<LOCAL_AUTHORITY_NUM; i++)
	{
		if (m_chkLocalRight[iAuthorityIndex].GetCheck() == BST_CHECKED)
		{
			strUserAut.strAutInfo[iAuthorityIndex].iLevel = HAND_CLEAR_ALARM+i;
			strUserAut.strAutInfo[iAuthorityIndex].uiList[0] = 1;
		}
		else 
		{
			strUserAut.strAutInfo[iAuthorityIndex].iLevel = HAND_CLEAR_ALARM+i;
			strUserAut.strAutInfo[iAuthorityIndex].uiList[0] = 0;
		}
		if (m_iIsAllowSet[iAuthorityIndex] == 1)
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
