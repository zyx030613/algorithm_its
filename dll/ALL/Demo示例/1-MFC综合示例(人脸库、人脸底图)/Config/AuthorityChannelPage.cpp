// AuthorityChannelPage.cpp : implementation file
//author zhy 2013.04.09

#include "stdafx.h"
#include "AuthorityChannelPage.h"

#define LOCAL_PTZ			0
#define LOCAL_PLAYBACK		1
#define REMOTE_PTZ			2
#define REMOTE_PLAYBACK		3
#define REMOTE_PREVIEW		4
#define LOCAL_HAND_OPERATE	5
#define REMOTE_HAND_OPERATE 6
#define LOCAL_PREVIEW_CHANNEL 26

// CLS_AuthorityChannelPage dialog

IMPLEMENT_DYNAMIC(CLS_AuthorityChannelPage, CDialog)

CLS_AuthorityChannelPage::CLS_AuthorityChannelPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AuthorityChannelPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iAuthority = 0;
	for (int i=0; i<CHANNEL_AUTHORITY_NUM; i++)
	{
		m_iSaveFlag[i] = 0;
	}
	m_bIsAdmin = TRUE;
}

CLS_AuthorityChannelPage::~CLS_AuthorityChannelPage()
{
}

void CLS_AuthorityChannelPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RIGHT_OPTION, m_cboRightOption);
	DDX_Control(pDX, IDC_CHECK_ALL, m_btnAllChannel);
	DDX_Control(pDX, IDC_CHECK_RIGHT_0, m_chkChannel[0]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_1, m_chkChannel[1]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_2, m_chkChannel[2]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_3, m_chkChannel[3]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_4, m_chkChannel[4]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_5, m_chkChannel[5]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_6, m_chkChannel[6]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_7, m_chkChannel[7]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_8, m_chkChannel[8]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_9, m_chkChannel[9]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_10, m_chkChannel[10]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_11, m_chkChannel[11]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_12, m_chkChannel[12]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_13, m_chkChannel[13]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_14, m_chkChannel[14]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_15, m_chkChannel[15]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_16, m_chkChannel[16]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_17, m_chkChannel[17]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_18, m_chkChannel[18]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_19, m_chkChannel[19]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_20, m_chkChannel[20]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_21, m_chkChannel[21]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_22, m_chkChannel[22]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_23, m_chkChannel[23]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_24, m_chkChannel[24]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_25, m_chkChannel[25]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_26, m_chkChannel[26]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_27, m_chkChannel[27]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_28, m_chkChannel[28]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_29, m_chkChannel[29]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_30, m_chkChannel[30]);
	DDX_Control(pDX, IDC_CHECK_RIGHT_31, m_chkChannel[31]);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	DDX_Control(pDX, IDC_COMBO_USER_CHOISE, m_cboUserChoise);
}


BEGIN_MESSAGE_MAP(CLS_AuthorityChannelPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_CHOISE, &CLS_AuthorityChannelPage::OnCbnSelchangeComboUserChoise)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT_OPTION, &CLS_AuthorityChannelPage::OnCbnSelchangeComboRightOption)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CLS_AuthorityChannelPage::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLS_AuthorityChannelPage::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLS_AuthorityChannelPage::OnBnClickedButtonSet)
END_MESSAGE_MAP()

// CLS_AuthorityChannelPage message handlers
BOOL CLS_AuthorityChannelPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();
	return TRUE;
}

void CLS_AuthorityChannelPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	UI_UpdateUserList();
	UI_UpdateAutOptionList(); 
	UI_UpdateChannelAuthority();
}

void CLS_AuthorityChannelPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_AuthorityChannelPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_USER_CHOISE, IDS_USER_CHOISE);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL_RIGHT, IDS_CFG_CHANNEL_RIGHT);
	SetDlgItemTextEx(IDC_STATIC_RIGHT_OPTION, IDS_CFG_RIGHT_OPTION);
	SetDlgItemTextEx(IDC_CHECK_ALL, IDS_CFG_RIGHT_ALL_CHANNEL);
	SetDlgItemTextEx(IDC_STATIC_0_7, IDS_CFG_RIGHT_CHANNEL0_7);
	SetDlgItemTextEx(IDC_STATIC_8_15, IDS_CFG_RIGHT_CHANNEL8_15);
	SetDlgItemTextEx(IDC_STATIC_16_23, IDS_CFG_RIGHT_CHANNEL16_23);
	SetDlgItemTextEx(IDC_STATIC_24_31, IDS_CFG_RIGHT_CHANNEL24_31);
	SetDlgItemTextEx(IDC_BUTTON_SAVE, IDS_CFG_CHANNEL_AUTHORITY_SAVE);
	SetDlgItemTextEx(IDC_BUTTON_SET, IDS_CFG_RIGHT_SET);
	

	m_cboRightOption.ResetContent();
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_PTZ)), LOCAL_PTZ);
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_PLAYBACK)), LOCAL_PLAYBACK);
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_PTZ)), REMOTE_PTZ);
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_PLAYBACK)), REMOTE_PLAYBACK);
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_PREVIEW)), REMOTE_PREVIEW);
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_HAND_OPERATE)), LOCAL_HAND_OPERATE);
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_HAND_OPERATE)), REMOTE_HAND_OPERATE);
	m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_PREVIEW)), LOCAL_PREVIEW_CHANNEL);
	m_cboRightOption.SetCurSel(0);
}

BOOL CLS_AuthorityChannelPage::UI_UpdateChannelAuthority()
{
	if (m_iLogonID < 0 || !m_bIsAdmin)
		return FALSE;

	USER_AUTHORITY strUserAut = {0};
	int iUserAutSize = sizeof(USER_AUTHORITY);
	strUserAut.iNeedSize = sizeof(USER_AUTHORITY);
	CString strName;
	int iCurUser = m_cboUserChoise.GetCurSel();
	m_cboUserChoise.GetLBText(iCurUser, strName);
	int iRet = NetClient_GetUserAuthority(m_iLogonID, (LPSTR)(LPCSTR)strName, &strUserAut, iUserAutSize);
	if (iRet==0)
	{
		m_btnAllChannel.SetCheck(BST_UNCHECKED);
		int iCurOption = m_cboRightOption.GetCurSel();
		bool bIsAllSelect = true;
		int iChannelNum = 0;
		int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
		if (iChannelNum < 0 || iChannelNum > SUPPORT_MAX_CHANNEL)
		{
			iChannelNum = SUPPORT_MAX_CHANNEL;
		}
		for (int i=0; i<CHANNEL_AUTHORITY_NUM; i++)
		{
			if (strUserAut.strAutInfo[i].iLevel == iCurOption)
			{
				for(int j=0; j<iChannelNum; j++)
				{
					m_chkChannel[j].SetCheck(((strUserAut.strAutInfo[i].uiList[0]>>j) & 1)?BST_CHECKED:BST_UNCHECKED);
					if (m_chkChannel[j].GetCheck() == BST_UNCHECKED)
					{
						bIsAllSelect = false;
					}
				}
				break;
			}
		}
		if (bIsAllSelect)
		{
			m_btnAllChannel.SetCheck(BST_CHECKED);
		}
	}
	return TRUE;
}

BOOL CLS_AuthorityChannelPage::UI_UpdateUserList()
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

BOOL CLS_AuthorityChannelPage::UI_UpdateAutOptionList()
{
	if (m_iLogonID < 0)
		return FALSE;

	m_cboRightOption.ResetContent();
	int iCurUser = m_cboUserChoise.GetCurSel();
	//获得何种用户 1.普通用户2特权用户3超级用户4管理员
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
					case LOCAL_PTZ:
						{
 							int iItemResult = GetCboSel(&m_cboRightOption, LOCAL_PTZ);
 							if (RET_FAILED != iItemResult)
 							{
								m_cboRightOption.DeleteString(iItemResult);
							}
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_PTZ)), LOCAL_PTZ);
						}
						break;
					case LOCAL_PLAYBACK:
						{
							int iItemResult = GetCboSel(&m_cboRightOption, LOCAL_PLAYBACK);
							if (RET_FAILED != iItemResult)
							{
								m_cboRightOption.DeleteString(iItemResult);
							}	
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_PLAYBACK)), LOCAL_PLAYBACK);
						}
						break;
					case REMOTE_PTZ:
						{
							int iItemResult = GetCboSel(&m_cboRightOption, REMOTE_PTZ);
							if (RET_FAILED != iItemResult)
							{
								m_cboRightOption.DeleteString(iItemResult);
							}
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_PTZ)), REMOTE_PTZ);
						}
						break;
					case REMOTE_PLAYBACK:
						{
							int iItemResult = GetCboSel(&m_cboRightOption, REMOTE_PLAYBACK);
							if (RET_FAILED != iItemResult)
							{
								m_cboRightOption.DeleteString(iItemResult);
							}
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_PLAYBACK)), REMOTE_PLAYBACK);
						}
						break;
					case REMOTE_PREVIEW:
						{
							int iItemResult = GetCboSel(&m_cboRightOption, REMOTE_PREVIEW);
							if(RET_FAILED != iItemResult)
							{
								m_cboRightOption.DeleteString(iItemResult);
							}
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_PREVIEW)), REMOTE_PREVIEW);
						}
						break;
					case LOCAL_HAND_OPERATE:
						{
							int iItemResult = GetCboSel(&m_cboRightOption, LOCAL_HAND_OPERATE);
							if(RET_FAILED != iItemResult)
							{
								m_cboRightOption.DeleteString(iItemResult);
							}
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_HAND_OPERATE)), LOCAL_HAND_OPERATE);
						}
						break;
					case REMOTE_HAND_OPERATE:
						{
							int iItemResult = GetCboSel(&m_cboRightOption, REMOTE_HAND_OPERATE);
							if(RET_FAILED != iItemResult)
							{
								m_cboRightOption.DeleteString(iItemResult);
							}
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_REMOTE_HAND_OPERATE)), REMOTE_HAND_OPERATE);
						}
					case LOCAL_PREVIEW_CHANNEL:
						{
							int iItemResult = GetCboSel(&m_cboRightOption, LOCAL_PREVIEW_CHANNEL);
							if(RET_FAILED != iItemResult)
							{
								m_cboRightOption.DeleteString(iItemResult);
							}
							m_cboRightOption.SetItemData(m_cboRightOption.AddString(GetText(IDS_CFG_RIGHT_CHANNEL_LOCAL_PREVIEW)), LOCAL_PREVIEW_CHANNEL);
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
	m_cboRightOption.SetCurSel(0);

	iRet = NetClient_GetChannelNum(m_iLogonID, &m_iChannelNum);
	for (int i=0; i<SUPPORT_MAX_CHANNEL; i++)
	{
		if (i < m_iChannelNum)
		{
			m_chkChannel[i].EnableWindow(true);
		}
		else
		{
			m_chkChannel[i].EnableWindow(false);
		}
	}
	return TRUE;
}
void CLS_AuthorityChannelPage::OnCbnSelchangeComboUserChoise()
{
	// TODO: Add your control notification handler code here
	UI_UpdateAutOptionList();
	UI_UpdateChannelAuthority();	
}

void CLS_AuthorityChannelPage::OnCbnSelchangeComboRightOption()
{
	// TODO: Add your control notification handler code here
	UI_UpdateChannelAuthority();	
	OnBnClickedButtonSave();
}

void CLS_AuthorityChannelPage::OnBnClickedCheckAll()
{
	// TODO: Add your control notification handler code here
	if (!m_bIsAdmin)
		return ;

	int iCurOption = m_cboRightOption.GetCurSel();
	for (int i=0; i<m_iChannelNum && i < SUPPORT_MAX_CHANNEL; i++)
	{
		if (m_btnAllChannel.GetCheck() == BST_CHECKED)
		{
			m_iRightList[iCurOption][i] = 1;
			m_chkChannel[i].SetCheck(BST_CHECKED);
		}
		else
		{
			m_iRightList[iCurOption][i] = 0;
			m_chkChannel[i].SetCheck(BST_UNCHECKED);
		}
	}
}

void CLS_AuthorityChannelPage::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	int iCurOption = m_cboRightOption.GetCurSel();
	for (int i=0; i<32; i++)
	{
		m_iRightList[iCurOption][i] = (m_chkChannel[i].GetCheck()== BST_CHECKED?1:0);
	}
	m_iSaveFlag[iCurOption] = 1;
}

void CLS_AuthorityChannelPage::OnBnClickedButtonSet()
{
	// TODO: Add your control notification handler code here
	if (!m_bIsAdmin)
		return ;

	OnBnClickedButtonSave();
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
	for (int i=0; i<CHANNEL_AUTHORITY_NUM; i++)
	{
		if (m_iSaveFlag[i] == 1)
		{
			strUserAut.strAutInfo[iAuthorityIndex].iLevel = i;
			for (int j=0; j<32; j++)
			{
				strUserAut.strAutInfo[iAuthorityIndex].uiList[0] |= m_iRightList[i][j] << j;
			}
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
