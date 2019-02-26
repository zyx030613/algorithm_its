// ECOPLightPage.cpp : implementation file
//

#include "stdafx.h"
#include "ECOPLightPage.h"


// CLS_ECOPLightPage dialog

IMPLEMENT_DYNAMIC(CLS_ECOPLightPage, CDialog)

CLS_ECOPLightPage::CLS_ECOPLightPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ECOPLightPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_ECOPLightPage::~CLS_ECOPLightPage()
{
}

void CLS_ECOPLightPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_COMBO_COMNO, m_cboComNo);
	DDX_Control(pDX, IDC_EDIT_LIGHTID, m_edtLightID);
	DDX_Control(pDX, IDC_EDIT_FLOODID, m_edtFloodID);
	DDX_Control(pDX, IDC_COMBO_LIGHTINFOID, m_cboLightInfoID);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_edtInterval);
	DDX_Control(pDX, IDC_EDIT_ACCEPTDIFF, m_edtAcceptDiff);
}


BEGIN_MESSAGE_MAP(CLS_ECOPLightPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_CHNLIGHT, &CLS_ECOPLightPage::OnBnClickedButtonChnlight)
	ON_BN_CLICKED(IDC_BUTTON_LIGHTINFO, &CLS_ECOPLightPage::OnBnClickedButtonLightinfo)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ECOPLightPage::OnCbnSelchangeComboRoadwayid)
	ON_CBN_SELCHANGE(IDC_COMBO_LIGHTINFOID, &CLS_ECOPLightPage::OnCbnSelchangeComboLightinfoid)
END_MESSAGE_MAP()


// CLS_ECOPLightPage message handlers

BOOL CLS_ECOPLightPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
		m_cboLightInfoID.AddString(strNo);
	}

	m_cboRoadwayID.SetCurSel(0);
	m_cboLightInfoID.SetCurSel(0);

	m_cboComNo.AddString("0--RS232");
	m_cboComNo.AddString("1--RS232");
	m_cboComNo.AddString("2--RS485");
	m_cboComNo.AddString("3");

	m_edtLightID.SetLimitText(2);
	m_edtFloodID.SetLimitText(31);
	m_edtInterval.SetLimitText(4);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ECOPLightPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateChnLight();
	UI_UpdateLightInfo();
}

void CLS_ECOPLightPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ECOPLightPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_CHNLIGHT,IDS_CONFIG_ECOP_CHNLIGHT);
	SetDlgItemTextEx(IDC_STATIC_COMNO,IDS_CONFIG_ECOP_COMNO);
	SetDlgItemTextEx(IDC_STATIC_LIGHTID,IDS_CONFIG_ECOP_LIGHTID);
	SetDlgItemTextEx(IDC_STATIC_FLOODID,IDS_CONFIG_ECOP_FLOADID);
	SetDlgItemTextEx(IDC_BUTTON_CHNLIGHT,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_LIGHTINFO,IDS_CONFIG_ECOP_LIGHTINFO);
	SetDlgItemTextEx(IDC_STATIC_LIGHTINFOID,IDS_CONFIG_ECOP_LIGHTID);
	SetDlgItemTextEx(IDC_STATIC_INTERVAL,IDS_CONFIG_ECOP_INTERVAL);
	SetDlgItemTextEx(IDC_STATIC_ACCEPTDIFF,IDS_CONFIG_ECOP_ACCEPTDIFF);
	SetDlgItemTextEx(IDC_BUTTON_LIGHTINFO,IDS_SET);

}

void CLS_ECOPLightPage::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateChnLight();
}

void CLS_ECOPLightPage::OnBnClickedButtonChnlight()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSRoadwayLight tLight = {0};
	tLight.iRoadwayID = m_cboRoadwayID.GetCurSel();
	tLight.iComNo = m_cboComNo.GetCurSel();
	tLight.iFloodID = GetDlgItemInt(IDC_EDIT_FLOODID);
	GetDlgItemText(IDC_EDIT_LIGHTID, tLight.cLightID, 31);
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_SET_LIGHT,&tLight,sizeof(tLight));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tLight));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tLight));
	}
}

BOOL CLS_ECOPLightPage::UI_UpdateChnLight()
{
	if (m_iLogonID < 0)
		return FALSE;

	TITSRoadwayLight tLight = {0};
	tLight.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_SET_LIGHT,&tLight,sizeof(tLight));
	if (0 == iRet)
	{
		m_cboRoadwayID.SetCurSel(tLight.iRoadwayID);
		m_cboComNo.SetCurSel(tLight.iComNo);
		SetDlgItemInt(IDC_EDIT_FLOODID, tLight.iFloodID);
		SetDlgItemText(IDC_EDIT_LIGHTID, tLight.cLightID);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tLight));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tLight));
	}
	return TRUE;
}

void CLS_ECOPLightPage::OnBnClickedButtonLightinfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSLightInfo tLightInfo = {0};
	tLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	tLightInfo.iTimeInterval = GetDlgItemInt(IDC_EDIT_INTERVAL);

	if (tLightInfo.iTimeInterval>1000)
	{
		tLightInfo.iTimeInterval = 1000;
	}

	tLightInfo.iTimeAcceptDiff = GetDlgItemInt(IDC_EDIT_ACCEPTDIFF);
	int iRet = NetClient_SetITSLightInfo(m_iLogonID,&tLightInfo,sizeof(tLightInfo));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	}
}

BOOL CLS_ECOPLightPage::UI_UpdateLightInfo()
{
	if (m_iLogonID < 0)
		return FALSE;

	TITSLightInfo tLightInfo = {0};
	tLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	int iRet = NetClient_GetITSLightInfo(m_iLogonID,&tLightInfo,sizeof(tLightInfo));
	if (0 == iRet)
	{
		m_cboLightInfoID.SetCurSel(tLightInfo.iLightID);
		SetDlgItemInt(IDC_EDIT_INTERVAL, tLightInfo.iTimeInterval);
		SetDlgItemInt(IDC_EDIT_ACCEPTDIFF, tLightInfo.iTimeAcceptDiff);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	}
	return TRUE;
}

void CLS_ECOPLightPage::OnCbnSelchangeComboLightinfoid()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSLightInfo tLightInfo = {0};
	tLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	int iRet = NetClient_GetITSLightInfo(m_iLogonID,&tLightInfo,sizeof(tLightInfo));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_INTERVAL, tLightInfo.iTimeInterval);
		SetDlgItemInt(IDC_EDIT_ACCEPTDIFF, tLightInfo.iTimeAcceptDiff);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	}
}
