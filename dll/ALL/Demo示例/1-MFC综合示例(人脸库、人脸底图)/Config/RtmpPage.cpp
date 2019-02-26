
#include "stdafx.h"
#include "RtmpPage.h"

#define RTMP_PUSH_MAIN_STREAM		1
#define RTMP_PUSH_SUB_STREAM		2

#define LIVE_ADDRESS_LIMIT_TEXT		255
#define LIVE_AUTH_KEY_LIMIT_TEXT	50


IMPLEMENT_DYNAMIC(CLS_RtmpPage, CDialog)

CLS_RtmpPage::CLS_RtmpPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_RtmpPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_RtmpPage::~CLS_RtmpPage()
{
}

void CLS_RtmpPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_STREAM_TYPE, m_cboPushStreamType);


	DDX_Control(pDX, IDC_CHECK_NET_LIVE, m_chkLiveEnable);
	DDX_Control(pDX, IDC_EDIT_LIVEADDR, m_edtLiveAddr);
	DDX_Control(pDX, IDC_EDIT_AUTH_KEY, m_edtAuthKey);
}


BEGIN_MESSAGE_MAP(CLS_RtmpPage, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_RTMP_SET, &CLS_RtmpPage::OnBnClickedBtnRtmpSet)
END_MESSAGE_MAP()


BOOL CLS_RtmpPage::OnInitDialog()		
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	return TRUE;
}


void CLS_RtmpPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	
	UI_UpdateRtmpInfo();
}

void CLS_RtmpPage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo >= 0) ? _iChannelNo : 0;

	UI_UpdateRtmpInfo();
}

void CLS_RtmpPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_RtmpPage::UI_UpdateDialog()
{

	int iCurIndex = m_cboPushStreamType.GetCurSel();
	m_cboPushStreamType.ResetContent();
	m_cboPushStreamType.SetItemData(m_cboPushStreamType.AddString(GetTextEx(IDS_MAJOR)), RTMP_PUSH_MAIN_STREAM);
	m_cboPushStreamType.SetItemData(m_cboPushStreamType.AddString(GetTextEx(IDS_MINOR)), RTMP_PUSH_SUB_STREAM);
	iCurIndex = (iCurIndex < m_cboPushStreamType.GetCount() && iCurIndex >= 0) ? iCurIndex : 0;
	m_cboPushStreamType.SetCurSel(0);

	SetDlgItemTextEx(IDC_BTN_RTMP_SET, IDS_SET);
 	SetDlgItemTextEx(IDC_CHECK_NET_LIVE, IDS_CONFIG_FTP_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_LIVEADDR, IDS_LIVE_ADDR);
	SetDlgItemTextEx(IDC_STATIC_AUTH_KEY, IDS_LIVE_AUTH_KEY);
	SetDlgItemTextEx(IDC_STATIC_STREAM_TYPE, IDS_CONFIG_ADV_STREAMTYPE);

	m_edtLiveAddr.SetLimitText(LIVE_ADDRESS_LIMIT_TEXT);
	m_edtAuthKey.SetLimitText(LIVE_AUTH_KEY_LIMIT_TEXT);

}

void CLS_RtmpPage::UI_UpdateRtmpInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_RtmpPage::UI_UpdateRtmpInfo] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	int iBytesReturned = 0;
	RtmpInfo tRtmpInfo = {0};
	tRtmpInfo.iBufSize = sizeof(RtmpInfo);
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_RTMP_URL_INFO, 0, &tRtmpInfo, sizeof(RtmpInfo), &iBytesReturned);
	if (RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_GetDevConfig:RTMP_URL_INFO] Get fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_GetDevConfig:RTMP_URL_INFO] Get success!");

		m_chkLiveEnable.SetCheck(tRtmpInfo.iRtmpEnable);
		m_cboPushStreamType.SetCurSel(GetCboSel(&m_cboPushStreamType, tRtmpInfo.iRtmpChnNo));
		m_edtLiveAddr.SetWindowText(tRtmpInfo.cRtmpUrl);
		m_edtAuthKey.SetWindowText(tRtmpInfo.cRtmpKey);
	}

	return;
}

void CLS_RtmpPage::OnBnClickedBtnRtmpSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_RtmpPage::OnBnClickedBtnRtmpSet] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	RtmpInfo tRtmpInfo = {0};
	tRtmpInfo.iBufSize = sizeof(RtmpInfo);
	tRtmpInfo.iRtmpEnable = (BST_CHECKED == m_chkLiveEnable.GetCheck()) ? 1 : 0;
	tRtmpInfo.iRtmpChnNo = m_cboPushStreamType.GetItemData(m_cboPushStreamType.GetCurSel());
	m_edtLiveAddr.GetWindowText(tRtmpInfo.cRtmpUrl,sizeof(tRtmpInfo.cRtmpUrl));
	m_edtAuthKey.GetWindowText(tRtmpInfo.cRtmpKey,sizeof(tRtmpInfo.cRtmpKey));
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_RTMP_URL_INFO, 0, &tRtmpInfo, sizeof(RtmpInfo));
	if (RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SetDevConfig:RTMP_URL_INFO] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SetDevConfig:RTMP_URL_INFO] Set success!");
	}
	return;
}
