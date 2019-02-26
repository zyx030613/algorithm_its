// CLS_VideoEncodeSlicePage.cpp : implementation file
//

#include "stdafx.h"
#include "VideoEncodeSlicePage.h"


// CLS_VideoEncodeSlicePage dialog

IMPLEMENT_DYNAMIC(CLS_VideoEncodeSlicePage, CDialog)

CLS_VideoEncodeSlicePage::CLS_VideoEncodeSlicePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VideoEncodeSlicePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_VideoEncodeSlicePage::~CLS_VideoEncodeSlicePage()
{
}

void CLS_VideoEncodeSlicePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_CFG_VIDEO_ENCODE_SLICE_TYPE, m_cboSliceType);
	DDX_Control(pDX, IDC_EDT_CFG_VIDEO_ENCODE_SLICE_SIZE, m_edtSliceSize);
}

BEGIN_MESSAGE_MAP(CLS_VideoEncodeSlicePage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_VIDEO_ENCODE_SLICE_SET, &CLS_VideoEncodeSlicePage::OnBnClickedButtonSetSlice)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CLS_VideoEncodeSlicePage message handlers

BOOL CLS_VideoEncodeSlicePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtSliceSize.SetLimitText(2);

	UI_UpdateDialog();

	m_cboSliceType.SetCurSel(0);

	return TRUE; 
}

void CLS_VideoEncodeSlicePage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	UI_UpdateVideoEncodeSlice();

}

void CLS_VideoEncodeSlicePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if (_iStreamNo < 0)
	{
		m_iStreamNo = 0;
	}
	else
	{
		m_iStreamNo = _iStreamNo;
	}
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	
	UI_UpdateVideoEncodeSlice();
}

void CLS_VideoEncodeSlicePage::OnBnClickedButtonSetSlice()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	if (m_iStreamNo > BASIC_STREAM_TYPES)
	{
		AddLog(LOG_TYPE_MSG,"","Illegal stream number %d", m_iStreamNo);
		return;
	}
	VencSliceType tVencSliceType = {0};
	tVencSliceType.iSlcSize = GetDlgItemInt(IDC_EDT_CFG_VIDEO_ENCODE_SLICE_SIZE);
	tVencSliceType.iStreamNo = m_iStreamNo;

	tVencSliceType.iType = m_cboSliceType.GetItemData(m_cboSliceType.GetCurSel());
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VENC_SLICE_TYPE, m_iChannelNo, &tVencSliceType, sizeof(tVencSliceType));
	if (RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo);
	}
}

BOOL CLS_VideoEncodeSlicePage::UI_UpdateVideoEncodeSlice()
{
	if (m_iLogonID < 0)
		return FALSE;
	if (m_iStreamNo > BASIC_STREAM_TYPES)
	{
		AddLog(LOG_TYPE_MSG,"","Illegal stream number %d", m_iStreamNo);
		return FALSE;
	}

	VencSliceType tVencSliceType = {0};
	tVencSliceType.iStreamNo = m_iStreamNo;
	int iByteRet = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_VENC_SLICE_TYPE, m_iChannelNo, &tVencSliceType, sizeof(tVencSliceType), &iByteRet);
	if (RET_SUCCESS == iRet)
	{
		m_cboSliceType.SetCurSel(GetCboSel(&m_cboSliceType, tVencSliceType.iType));
		m_edtSliceSize.SetWindowText(IntToCString(tVencSliceType.iSlcSize));
		//SetDlgItemInt(IDC_EDT_CFG_VIDEO_ENCODE_SLICE_SIZE,tVencSliceType.iSlcSize);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(%d,%d,%d)",m_iLogonID, m_iChannelNo, m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(%d,%d,%d)",m_iLogonID, m_iChannelNo, m_iStreamNo);
	}

	return TRUE;
}

void CLS_VideoEncodeSlicePage::UI_UpdateDialog()
{
	m_cboSliceType.ResetContent();
	m_cboSliceType.SetItemData(m_cboSliceType.AddString(GetTextEx(IDS_CONFIG_DNVR_DISABLE)), VENC_SLICE_TYPE_SINGLE);
	m_cboSliceType.SetItemData(m_cboSliceType.AddString(GetTextEx(IDS_CONFIG_VIDEO_ENCODE_SLICE_BYTE)), VENC_SLICE_TYPE_BYTES);
	m_cboSliceType.SetItemData(m_cboSliceType.AddString(GetTextEx(IDS_CONFIG_VIDEO_ENCODE_SLICE_MACRO)), VENC_SLICE_TYPE_MACRO);
	//m_cboSliceType.SetCurSel(0);

	SetDlgItemTextEx(IDC_STXT_SLICE_TYPE, IDS_CONFIG_VIDEO_ENCODE_SLICE_TYPE);
	SetDlgItemTextEx(IDC_STXT_SLICE_SIZE, IDS_CONFIG_VIDEO_ENCODE_SLICE_SIZE);
	SetDlgItemTextEx(IDC_BTN_VIDEO_ENCODE_SLICE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STXT_ENCODE_SLICE, IDS_CONFIG_VIDEO_ENCODE_SLICE);
}

void CLS_VideoEncodeSlicePage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
	UI_UpdateVideoEncodeSlice();
}

