// LS_UserPage.cpp : implementation file
//

#include "stdafx.h"
#include "UserPage.h"


// CLS_UserPage dialog

IMPLEMENT_DYNAMIC(CLS_UserPage, CDialog)

CLS_UserPage::CLS_UserPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_UserPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_UserPage::~CLS_UserPage()
{
}

void CLS_UserPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERINFO, m_lstUserInfo);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_edtUserName);
	DDX_Control(pDX, IDC_EDIT_OLDPASSWORD, m_edtOldPwd);
	DDX_Control(pDX, IDC_EDIT_NEWPASSWORD, m_edtNewPwd);
	DDX_Control(pDX, IDC_COMBO_AUTHORITY, m_cboAuthority);
	DDX_Control(pDX, IDC_EDIT_MAXUSER, m_edtMaxUser);
}


BEGIN_MESSAGE_MAP(CLS_UserPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_ADDUSER, &CLS_UserPage::OnBnClickedButtonAdduser)
	ON_BN_CLICKED(IDC_BUTTON_MODIFYPASSWORD, &CLS_UserPage::OnBnClickedButtonModifypassword)
	ON_BN_CLICKED(IDC_BUTTON_DELETEUSER, &CLS_UserPage::OnBnClickedButtonDeleteuser)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLS_UserPage::OnBnClickedButtonSet)
	ON_LBN_SELCHANGE(IDC_LIST_USERINFO, &CLS_UserPage::OnLbnSelchangeListUserinfo)
END_MESSAGE_MAP()

void CLS_UserPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		return;
	}

	UI_UpdateUserList();
	UI_UpdateCurUserInfo();
	UI_UpdateMaxUserCount();
}

void CLS_UserPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}
// CLS_UserPage message handlers

BOOL CLS_UserPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtUserName.SetLimitText(15);
	m_edtNewPwd.SetLimitText(15);
	m_edtOldPwd.SetLimitText(15);
	m_edtMaxUser.SetLimitText(5);

	UI_UpdateDialog();

	m_cboAuthority.SetCurSel(AUT_BROWSE_CTRL);

	return TRUE;  
}

void CLS_UserPage::OnBnClickedButtonAdduser()
{
	int iLogonID = m_iLogonID;
	if (iLogonID < 0)
		return;

	int iRet;
	int iUserNum = 0;
	int iAuthority = 0;
	iRet = NetClient_GetUserNum(m_iLogonID,&iUserNum);
	if(iUserNum >= 8)
	{
		AddLog(LOG_TYPE_MSG,"","Failure!User number is over 8!");
		return;
	}

	CString strUserName;
	CString strPassword;
	m_edtUserName.GetWindowText(strUserName);
	m_edtNewPwd.GetWindowText(strPassword);
	iAuthority = m_cboAuthority.GetCurSel()+1;
	iRet = NetClient_AddUser(m_iLogonID,(LPSTR)(LPCTSTR)strUserName,(LPSTR)(LPCTSTR)strPassword,iAuthority);

	if(iRet == 0)                   
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_AddUser(%d,%s,%s,%d)",m_iLogonID,strUserName,strPassword,iAuthority);
		Sleep(1000);
		UI_UpdateUserList();
		UI_UpdateCurUserInfo();
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NetClient_AddUser(%d,%s,%s,%d)",iRet,m_iLogonID,strUserName,strPassword,iAuthority);
	}
}

void CLS_UserPage::OnBnClickedButtonModifypassword()
{
	char cUserName[16];
	char cPassword[16];
	int iAuthority;
	CString strUserName;
	CString strOldPassword;
	CString strNewPassword;
	m_edtUserName.GetWindowText(strUserName);
	m_edtOldPwd.GetWindowText(strOldPassword);
	m_edtNewPwd.GetWindowText(strNewPassword);
	
	int iIndex = m_lstUserInfo.FindStringExact(-1, strUserName);
	if (iIndex == LB_ERR)
	{
		//AddLog(LOG_TYPE_MSG,"","No User!(%s)",strUserName);
		return;
	}

	int iRet = NetClient_GetUserInfo(m_iLogonID,iIndex,cUserName,cPassword,&iAuthority);
	if(iRet == 0)
	{
		if (strOldPassword != cPassword)
		{
			AddLog(LOG_TYPE_MSG,"","Please input correct old password!");
		}
		else
		{
			int iRet = NetClient_ModifyPwd(m_iLogonID,(LPSTR)(LPCTSTR)strUserName,(LPSTR)(LPCTSTR)strNewPassword);
			if(0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_ModifyPwd(%d,%s,%s)",m_iLogonID,strUserName,strNewPassword);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","(%d)NetClient_ModifyPwd(%d,%s,%s)",iRet,m_iLogonID,strUserName,strNewPassword);
			}
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","(%d)NetClient_GetUserInfo(%d,%d)",iRet,m_iLogonID,iIndex);
	}
}

void CLS_UserPage::OnBnClickedButtonDeleteuser()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	CString strUserName;
	m_edtUserName.GetWindowText(strUserName);

	int iRet = NetClient_DelUser(m_iLogonID,(LPSTR)(LPCTSTR)strUserName);
    if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DelUser(%d,%s)",m_iLogonID,strUserName);
		Sleep(500);
		UI_UpdateUserList();
		UI_UpdateCurUserInfo();
	}
    else
    {
		AddLog(LOG_TYPE_FAIL,"","(%d)NetClient_DelUser(%d,%s)",iRet,m_iLogonID,strUserName);
    }
}

void CLS_UserPage::OnBnClickedButtonSet()
{
	if (m_iLogonID < 0)
	{
		return;
	}
	int iMaxUser = GetDlgItemInt(IDC_EDIT_MAXUSER);
	if(0 == NetClient_SetMaxConUser(m_iLogonID,iMaxUser))
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetMaxConUser(%d,%d)",m_iLogonID,iMaxUser);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetMaxConUser(%d,%d)",m_iLogonID,iMaxUser);
	}
}

void CLS_UserPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_USERNAME, IDS_CFG_USER_NAME);
	SetDlgItemTextEx(IDC_STATIC_OLDPASSWORD, IDS_CFG_USER_OLDPWD);
	SetDlgItemTextEx(IDC_STATIC_NEWPASSWORD, IDS_CFG_USER_NEWPWD);
	SetDlgItemTextEx(IDC_STATIC_AUTHORITY, IDS_CFG_USER_AUTHORITY);

	SetDlgItemTextEx(IDC_BUTTON_ADDUSER,IDS_CFG_USER_ADD);
	SetDlgItemTextEx(IDC_BUTTON_DELETEUSER,IDS_CFG_USER_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_MODIFYPASSWORD, IDS_CFG_USER_MODIFYPWD);
	SetDlgItemTextEx(IDC_BUTTON_SET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_STATIC_MAXUSER, IDS_CONFIG_USER_MAXCLIENT);
}

void CLS_UserPage::UI_UpdateCurUserInfo()
{
	int iLogonID = m_iLogonID;
	if (iLogonID < 0)
		return;

	char cUserName[16];
	char cPassword[16];
	int iAuthority = 0;
	m_edtNewPwd.SetWindowText(_T(""));
	int iRet =  NetClient_GetCurUserInfo(iLogonID,cUserName,cPassword,&iAuthority);
	if(iRet == 0)
	{
		m_lstUserInfo.SelectString(-1,cUserName);
		m_edtUserName.SetWindowText(cUserName);
		m_edtOldPwd.SetWindowText(cPassword);
		m_cboAuthority.SetCurSel(iAuthority-1);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetUserInfo (%d)",iLogonID);
	}		
}

void CLS_UserPage::OnLbnSelchangeListUserinfo()
{
	int iIndex = m_lstUserInfo.GetCurSel();
	UI_UpdateUserInfo(iIndex);
}

void CLS_UserPage::UI_UpdateUserList()
{
	int iLogonID = m_iLogonID;
	if (iLogonID < 0)
		return;

	int iUserNum = 0;
	char cUserName[16] = {0};
	char cPassword[16] = {0};
	int iAuthority = 0;
	NetClient_GetUserNum(m_iLogonID,&iUserNum);
	m_lstUserInfo.ResetContent();
	for(int i=0;i<iUserNum;i++)
	{
		if(0 == NetClient_GetUserInfo(m_iLogonID,i,cUserName,cPassword,&iAuthority))
		{
			m_lstUserInfo.AddString(cUserName);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetUserInfo(%d,%d)",m_iLogonID,i);
		}
	}
}

void CLS_UserPage::UI_UpdateUserInfo( int _iIndex )
{
	int iLogonID = m_iLogonID;
	if (iLogonID < 0 || _iIndex < 0)
		return;

	char cUserName[16] = {0};
	char cPassword[16] = {0};
	int iAuthority = 0;
	m_edtNewPwd.SetWindowText(_T(""));
	if(0 == NetClient_GetUserInfo(m_iLogonID,_iIndex,cUserName,cPassword,&iAuthority))
	{
		m_edtUserName.SetWindowText(cUserName);
		m_edtOldPwd.SetWindowText(cPassword);
		m_cboAuthority.SetCurSel(iAuthority-1);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetUserInfo(%d,%d)",m_iLogonID,_iIndex);
	}
}

void CLS_UserPage::UI_UpdateMaxUserCount()
{
	if (m_iLogonID < 0)
		return;

	int iMaxConUser;
	int iRet = NetClient_GetMaxGetUser(m_iLogonID, &iMaxConUser);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_MAXUSER, iMaxConUser);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetMaxGetUser (%d,%d)",m_iLogonID,iMaxConUser);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetMaxGetUser (%d,%d)",m_iLogonID,iMaxConUser);
	}
}