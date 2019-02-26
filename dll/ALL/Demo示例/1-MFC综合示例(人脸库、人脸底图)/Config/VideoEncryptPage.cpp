// Config/VideoEncrypt.cpp : implementation file
//

#include "stdafx.h"
#include "VideoEncryptPage.h"


// CLS_VideoEncrypt dialog

IMPLEMENT_DYNAMIC(CLS_VideoEncryptPage, CDialog)

CLS_VideoEncryptPage::CLS_VideoEncryptPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VideoEncryptPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_VideoEncryptPage::~CLS_VideoEncryptPage()
{
}

void CLS_VideoEncryptPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENCRYPT_TYPE, m_cboEncryptType);
	DDX_Control(pDX, IDC_EDIT_ENCRYPT_KEY, m_edtEncryptKey);
	DDX_Control(pDX, IDC_EDIT_DECRYPT_KEY, m_edtDecryptKey);
}


BEGIN_MESSAGE_MAP(CLS_VideoEncryptPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, &CLS_VideoEncryptPage::OnBnClickedButtonEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CLS_VideoEncryptPage::OnBnClickedButtonDecrypt)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_VideoEncrypt message handlers

BOOL CLS_VideoEncryptPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtEncryptKey.SetLimitText(16);
	m_edtDecryptKey.SetLimitText(16);

	UI_UpdateDialog();

	m_cboEncryptType.SetCurSel(0);

	return TRUE; 
}

void CLS_VideoEncryptPage::OnDestroy()
{
	CLS_BasePage::OnDestroy();

	// TODO: Add your message handler code here
}

void CLS_VideoEncryptPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

}

void CLS_VideoEncryptPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo =  _iChannelNo + (_iChannelNo + 1)* _iStreamNo;
	}

	UI_UpdateVideoEncrypt();
	//UI_UpdateVideoDecrypt();
}

void CLS_VideoEncryptPage::OnBnClickedButtonEncrypt()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	CString strKey;
	m_edtEncryptKey.GetWindowText(strKey);
	TVideoEncrypt tEncrypt = {0};
	tEncrypt.iChannel = m_iChannelNo;
	tEncrypt.iType = m_cboEncryptType.GetCurSel();
	if (tEncrypt.iType < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid encrypt type(%d)",tEncrypt.iType);
		return;
	}
	else if (tEncrypt.iType > 0)
	{
		if(FALSE == IsValidKey((LPSTR)(LPCTSTR)strKey))
		{
			AddLog(LOG_TYPE_MSG,"","Invalid encrypt key(%s)!",(LPCSTR)(LPCTSTR)strKey);
			return;
		}
		strcpy_s(tEncrypt.cPassword,sizeof(tEncrypt.cPassword),(LPCSTR)(LPCTSTR)strKey);
	}

	int iRet = NetClient_SetVideoEncrypt(m_iLogonID, m_iChannelNo, &tEncrypt, sizeof(tEncrypt));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoEncrypt(%d,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoEncrypt(%d,%d)",m_iLogonID,m_iChannelNo);
	}

	if(0 == tEncrypt.iType)
	{
		m_edtEncryptKey.SetWindowText(NULL);
	}
}

void CLS_VideoEncryptPage::OnBnClickedButtonDecrypt()
{
	if (m_iLogonID < 0)
		return;

	CString strKey;
	TVideoDecrypt tDecrypt = {0};
	tDecrypt.iChannel = m_iChannelNo;
	m_edtDecryptKey.GetWindowText(strKey);
	strcpy_s(tDecrypt.cDecryptKey,sizeof(tDecrypt.cDecryptKey),(LPCSTR)(LPCTSTR)strKey);

	int iRet = NetClient_SetVideoDecrypt(m_iLogonID, m_iChannelNo, &tDecrypt, sizeof(tDecrypt));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoDecrypt(%d,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoDecrypt(%d,%d)",m_iLogonID,m_iChannelNo);
	}
	m_edtDecryptKey.SetWindowText(NULL);
}

BOOL CLS_VideoEncryptPage::IsValidKey( char* _pcPwd )
{
	char* pcPwd = _pcPwd;
	while(pcPwd && *pcPwd)
	{
		if (*pcPwd == '_'
			|| *pcPwd >= '0' && *pcPwd <= '9'
			|| *pcPwd >= 'A' && *pcPwd <= 'Z'
			|| *pcPwd >= 'a' && *pcPwd <= 'z')
		{
			++pcPwd;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CLS_VideoEncryptPage::UI_UpdateVideoEncrypt()
{
	if (m_iLogonID < 0)
		return FALSE;

	TVideoEncrypt tEncrypt = {0};
	tEncrypt.iChannel = m_iChannelNo;
	int iRet = NetClient_GetVideoEncrypt(m_iLogonID, m_iChannelNo, &tEncrypt, sizeof(tEncrypt));
	if (iRet == 0)
	{
		m_cboEncryptType.SetCurSel(tEncrypt.iType);
		m_edtEncryptKey.SetWindowText(tEncrypt.cPassword);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoEncrypt(%d,%d,,)",m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoEncrypt(%d,%d,,)",m_iLogonID, m_iChannelNo);
	}

	return TRUE;
}

BOOL CLS_VideoEncryptPage::UI_UpdateVideoDecrypt()
{
	if (m_iLogonID < 0)
		return FALSE;

	TVideoDecrypt tDecrypt = {0};
	tDecrypt.iChannel = m_iChannelNo;
	int iRet = NetClient_GetVideoDecrypt(m_iLogonID, m_iChannelNo, &tDecrypt, sizeof(tDecrypt));
	if (iRet == 0)
	{
		m_edtDecryptKey.SetWindowText(tDecrypt.cDecryptKey);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoDecrypt(%d,%d,,)",m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoDecrypt(%d,%d,,)",m_iLogonID, m_iChannelNo);
	}

	return TRUE;
}

void CLS_VideoEncryptPage::UI_UpdateDialog()
{
	InsertString(m_cboEncryptType,0,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_TYPE_NONE);
	InsertString(m_cboEncryptType,1,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_TYPE_AES);

	SetDlgItemTextEx(IDC_STATIC_ENCRYPT_TYPE,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_TYPE);
	SetDlgItemTextEx(IDC_STATIC_ENCRYPT_KEY,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_KEY);
	SetDlgItemTextEx(IDC_BUTTON_ENCRYPT,IDS_OK);
	SetDlgItemTextEx(IDC_STATIC_DECRYPT_KEY,IDS_CFG_VIDEO_ENCRYPT_DECRYPT_KEY);
	SetDlgItemTextEx(IDC_BUTTON_DECRYPT,IDS_OK);
}

void CLS_VideoEncryptPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

