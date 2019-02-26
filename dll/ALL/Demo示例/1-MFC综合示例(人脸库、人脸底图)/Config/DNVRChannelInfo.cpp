// DNVRChannelInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DNVRChannelInfo.h"

// CLS_DNVRChannelInfo 对话框

IMPLEMENT_DYNAMIC(CLS_DNVRChannelInfo, CDialog)

CLS_DNVRChannelInfo::CLS_DNVRChannelInfo(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DNVRChannelInfo::IDD, pParent)
{
	m_iChannel = -1;
}

CLS_DNVRChannelInfo::~CLS_DNVRChannelInfo()
{
}

void CLS_DNVRChannelInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_DNVR_CHANNEL_STATE, m_lstChannelState);
}

BEGIN_MESSAGE_MAP(CLS_DNVRChannelInfo, CLS_BasePage)
END_MESSAGE_MAP()

BOOL CLS_DNVRChannelInfo::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	return TRUE;
}

void CLS_DNVRChannelInfo::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DNVRChannelInfo::OnChannelChanged( int _iLogonID,int/* _iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	UI_UpdateDialog();
}

void CLS_DNVRChannelInfo::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData )
{
	if (_iLogonID != m_iLogonID)
	{
		return;
	}

	if (PARA_CHANNEL_CONNECT_STATE == _iParaType)
	{
		UI_UpdateConnectState(_iChannelNo);
		AddLog(LOG_TYPE_SUCC,"","[CHN_CONNECT_STATE] Channel(%d) change!", _iChannelNo);
	}
}

void CLS_DNVRChannelInfo::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_GP_DNVR_CHANNEL_STATE, IDS_CONFIG_DNVR_CHANNEL_STATE);
	int iColumn = 0;
	DWORD dwStyle = m_lstChannelState.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;  
	m_lstChannelState.SetExtendedStyle(dwStyle);
	InsertColumn(m_lstChannelState, iColumn++, GetTextEx(IDS_ITS_CHANNELID), LVCFMT_LEFT, 80);
	InsertColumn(m_lstChannelState, iColumn++, GetTextEx(IDS_LOG_STATUS), LVCFMT_LEFT, 200);

	m_lstChannelState.DeleteAllItems();
 
	CString cstrState;

	int iChannelNum = -1;
	int iRet= NetClient_GetChannelNum(m_iLogonID, &iChannelNum);

	for (int i = 0; i < iChannelNum; ++i)
	{
		UI_UpdateConnectState(i);
	}
}

void CLS_DNVRChannelInfo::UI_UpdateConnectState(int _iChannel)
{
	if (_iChannel < 0 || _iChannel > m_lstChannelState.GetItemCount())
	{
		return;
	}

	if (_iChannel == m_lstChannelState.GetItemCount())
	{
		m_lstChannelState.InsertItem(_iChannel, IntToString(_iChannel +1));
	}

	CString strpcChannelState;
	int iStatus = -1;
	int iRetBytes = -1;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_CHN_CONNECT_STATE, _iChannel, (void*)&iStatus, sizeof(iStatus), &iRetBytes);
	if( RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[CHN_CONNECT_STATE] (%d,%d)", m_iLogonID, _iChannel);
		if (-1 == iStatus)
		{
			strpcChannelState = GetTextEx(IDS_UNKNOW_CONNECT);
		}
		else if (1 == iStatus)
		{
			strpcChannelState = GetTextEx(IDS_CONFIG_WIFI_ONLINE);
		}
		else
		{
			strpcChannelState = GetTextEx(IDS_CONFIG_WIFI_OFFLINE);
		}

		m_lstChannelState.SetItemText(_iChannel, 0, IntToString(_iChannel +1));
		m_lstChannelState.SetItemText(_iChannel, 1, strpcChannelState);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[CHN_CONNECT_STATE] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}

}
