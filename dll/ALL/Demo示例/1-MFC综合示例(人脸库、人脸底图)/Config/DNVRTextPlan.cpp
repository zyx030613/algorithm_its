// DNVRAlmSchPage.cpp : implementation file
//

#include "stdafx.h"
#include "DNVRTextPlan.h"
#define MAX_TEXTPLAN_ID 16

// CLS_DNVRAlmSchPage dialog

IMPLEMENT_DYNAMIC(CLS_DNVRTextPlan, CDialog)

CLS_DNVRTextPlan::CLS_DNVRTextPlan(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DNVRTextPlan::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_DNVRTextPlan::~CLS_DNVRTextPlan()
{
}

void CLS_DNVRTextPlan::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_TEXTPLAN_CALIAS, m_edtTextPlancAlias);
	DDX_Control(pDX, IDC_CBO_TEXTPLAN_ID, m_cboTextPlaniId);
	DDX_Control(pDX, IDC_EDT_TEXTPLAN_CTEXT, m_edtTextPlancText);
}


BEGIN_MESSAGE_MAP(CLS_DNVRTextPlan, CLS_BasePage)

	ON_CBN_SELCHANGE(IDC_CBO_TEXTPLAN_ID, &CLS_DNVRTextPlan::OnCbnSelchangeCboTextplaniid)
	ON_BN_CLICKED(IDC_BTN_TEXTPLAN_SET, &CLS_DNVRTextPlan::OnBnClickedBtnTextplanSet)
END_MESSAGE_MAP()


// CLS_DNVRAlmSchPage message handlers
BOOL CLS_DNVRTextPlan::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_cboTextPlaniId.ResetContent();
	for (int i=0; i<MAX_TEXTPLAN_ID; i++)
	{
		CString strTextPlanID;
		strTextPlanID.Format("%d",i+1);
		m_cboTextPlaniId.AddString(strTextPlanID);
	}

	UI_UpdateDialog();
	
	return TRUE;
}

void CLS_DNVRTextPlan::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}

	UI_UpdateDialog();

}

void CLS_DNVRTextPlan::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DNVRTextPlan::UI_UpdateDialog()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iBytesReturned = 0;
	TextPlan tTextPlan = {0};
	tTextPlan.iSize = sizeof(tTextPlan);
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_TEXT_PLAN, m_iChannelNo, &tTextPlan, sizeof(tTextPlan), &iBytesReturned);
	m_cboTextPlaniId.SetCurSel(tTextPlan.iPlanId);
	SetDlgItemText(IDC_EDT_TEXTPLAN_CALIAS, tTextPlan.cAlias);
	SetDlgItemText(IDC_EDT_TEXTPLAN_CTEXT, tTextPlan.cText);

	SetDlgItemTextEx(IDC_BTN_TEXTPLAN_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STXT_TEXTPLAN_ID,IDS_CONFIG_DNVR_TEXTPLAN_ID);
	SetDlgItemTextEx(IDC_STXT_TEXTPLAN_CALIAS,IDS_CONFIG_DNVR_TEXTPLAN_CALIAS);
	SetDlgItemTextEx(IDC_STXT_TEXTPLAN_CTEXT,IDS_CONFIG_DNVR_TEXTPLAN_CTEXT);
	if( RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[TEXT_PLAN] (%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[TEXT_PLAN] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}

}

void CLS_DNVRTextPlan::OnCbnSelchangeCboTextplaniid()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iBytesReturned = 0;
	TextPlan tTextPlan = {0};
	tTextPlan.iPlanId = m_cboTextPlaniId.GetCurSel();
	tTextPlan.iSize = sizeof(tTextPlan);
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_TEXT_PLAN, m_iChannelNo, &tTextPlan, sizeof(tTextPlan), &iBytesReturned);
	SetDlgItemText(IDC_EDT_TEXTPLAN_CALIAS, tTextPlan.cAlias);
	SetDlgItemText(IDC_EDT_TEXTPLAN_CTEXT, tTextPlan.cText);
	if( RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[TEXT_PLAN] (%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[TEXT_PLAN] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_DNVRTextPlan::OnBnClickedBtnTextplanSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TextPlan tTextPlan = {0};
	tTextPlan.iPlanId = m_cboTextPlaniId.GetCurSel();
	CString strCalias;
	CString strCtext;
	GetDlgItemText(IDC_EDT_TEXTPLAN_CALIAS, strCalias);
	GetDlgItemText(IDC_EDT_TEXTPLAN_CTEXT, strCtext);
	strncpy(tTextPlan.cAlias, strCalias.GetBuffer(),LEN_64);
	strncpy(tTextPlan.cText, strCtext.GetBuffer(),LEN_512);
	tTextPlan.iSize = sizeof(tTextPlan);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_TEXT_PLAN, m_iChannelNo, &tTextPlan, sizeof(tTextPlan));
	if( RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[TEXT_PLAN] (%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[TEXT_PLAN] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
