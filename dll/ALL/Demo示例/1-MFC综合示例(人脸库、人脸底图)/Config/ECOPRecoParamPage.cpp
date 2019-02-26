// Config\ECOPRecoParamPage.cpp : implementation file
//

#include "stdafx.h"
#include "ECOPRecoParamPage.h"


// CLS_ECOPRecoParamPage dialog

IMPLEMENT_DYNAMIC(CLS_ECOPRecoParamPage, CDialog)

CLS_ECOPRecoParamPage::CLS_ECOPRecoParamPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ECOPRecoParamPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_ECOPRecoParamPage::~CLS_ECOPRecoParamPage()
{
}

void CLS_ECOPRecoParamPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_CHECK_RECOPARAM_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_EDIT_MAXPLATE, m_edtMaxPlate);
	DDX_Control(pDX, IDC_EDIT_MAXPLATEWIDTH, m_edtMaxPlateWidth);
	DDX_Control(pDX, IDC_EDIT_MINPLATEWIDTH, m_edtMinPlateWidth);
	DDX_Control(pDX, IDC_EDIT_ENGINENUM, m_edtEngineNum);
	DDX_Control(pDX, IDC_EDIT_AREATYPE, m_edtAreaType);
	DDX_Control(pDX, IDC_EDIT_PLATETYPE, m_edtPlateType);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_edtSpeed);
	DDX_Control(pDX, IDC_EDIT_MAXSKIP, m_edtMaxSkip);
	DDX_Control(pDX, IDC_EDIT_MINVALID, m_edtMinValid);
	DDX_Control(pDX, IDC_EDIT_FRAMEPERCENT, m_edtFramePercent);
	DDX_Control(pDX, IDC_EDIT_MINCAPDIFF, m_edtMinCapDiff);
	DDX_Control(pDX, IDC_EDIT_CALIINFO, m_edtCaliInfo);
	DDX_Control(pDX, IDC_BUTTON_RECOPARAM, m_btnRecoParam);
}


BEGIN_MESSAGE_MAP(CLS_ECOPRecoParamPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ECOPRecoParamPage::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BUTTON_RECOPARAM, &CLS_ECOPRecoParamPage::OnBnClickedButtonRecoparam)
END_MESSAGE_MAP()


// CLS_ECOPRecoParamPage message handlers
BOOL CLS_ECOPRecoParamPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	m_edtMaxPlate.SetLimitText(10);
	m_edtMaxPlateWidth.SetLimitText(10);
	m_edtMinPlateWidth.SetLimitText(10);
	m_edtEngineNum.SetLimitText(2);
	m_edtAreaType.SetLimitText(2);
	m_edtPlateType.SetLimitText(2);
	m_edtSpeed.SetLimitText(2);
	m_edtMaxSkip.SetLimitText(4);
	m_edtMinValid.SetLimitText(4);
	m_edtFramePercent.SetLimitText(4);
	m_edtMinCapDiff.SetLimitText(4);
	m_edtCaliInfo.SetLimitText(75);
	UI_UpdateDialog();

	return TRUE;
}

void CLS_ECOPRecoParamPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateRecoParam();
}

void CLS_ECOPRecoParamPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ECOPRecoParamPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_RECOPARAM,IDS_CONFIG_ECOP_RECOPARAM);
	SetDlgItemTextEx(IDC_CHECK_RECOPARAM_ENABLE,IDS_CONFIG_ECOP_RECOPARAM_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_MAXPLATE,IDS_CONFIG_ECOP_MAXPLATE);
	SetDlgItemTextEx(IDC_STATIC_MAXPLATEWIDTH,IDS_CONFIG_ECOP_MAXPLATEWIDTH);
	SetDlgItemTextEx(IDC_STATIC_MINPLATEWIDTH,IDS_CONFIG_ECOP_MINPLATEWIDTH);
	SetDlgItemTextEx(IDC_STATIC_ENGINENUM,IDS_CONFIG_ECOP_ENGINENUM);
	SetDlgItemTextEx(IDC_STATIC_AREATYPE,IDS_CONFIG_ECOP_AREATYPE);
	SetDlgItemTextEx(IDC_STATIC_PLATETYPE,IDS_CONFIG_ECOP_PLATETYPE);
	SetDlgItemTextEx(IDC_STATIC_SPEED,IDS_CONFIG_ECOP_SPEED);
	SetDlgItemTextEx(IDC_STATIC_MAXSKIP,IDS_CONFIG_ECOP_MAXSKIP);
	SetDlgItemTextEx(IDC_STATIC_MINVALID,IDS_CONFIG_ECOP_MINVALID);
	SetDlgItemTextEx(IDC_STATIC_FRAMEPERCENT,IDS_CONFIG_ECOP_FRAMEPERCENT);
	SetDlgItemTextEx(IDC_STATIC_MINCAPDIFF,IDS_CONFIG_ECOP_MINCAPDIFF);
	SetDlgItemTextEx(IDC_STATIC_CALIINFO,IDS_CONFIG_ECOP_CALIINFO);
	SetDlgItemTextEx(IDC_BUTTON_RECOPARAM,IDS_SET);

}

BOOL CLS_ECOPRecoParamPage::UI_UpdateRecoParam()
{
	if (m_iLogonID < 0)
		return FALSE;

	ITS_RecoParamEx tRecognize = {0};
	tRecognize.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetITSRecoParam(m_iLogonID,&tRecognize,sizeof(tRecognize));
	if (0 == iRet)
	{
		//m_cboRoadwayID.SetCurSel(tRecognize.iRoadwayID);
		m_chkEnable.SetCheck(tRecognize.iEnable?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_MAXPLATE, tRecognize.iMaxPlateNO);
		SetDlgItemInt(IDC_EDIT_MAXPLATEWIDTH, tRecognize.iMaxPlateWidth);
		SetDlgItemInt(IDC_EDIT_MINPLATEWIDTH, tRecognize.iMinPlateWidth);
		SetDlgItemInt(IDC_EDIT_ENGINENUM, tRecognize.iEngineNum);
		SetDlgItemInt(IDC_EDIT_AREATYPE, tRecognize.iAreaType);
		SetDlgItemInt(IDC_EDIT_PLATETYPE, tRecognize.iPlateType);
		SetDlgItemInt(IDC_EDIT_SPEED, tRecognize.iSpeed);
		SetDlgItemInt(IDC_EDIT_MAXSKIP, tRecognize.iMaxSkip);
		SetDlgItemInt(IDC_EDIT_MINVALID, tRecognize.iMinValid);
		SetDlgItemInt(IDC_EDIT_FRAMEPERCENT, tRecognize.iFramePercent);
		SetDlgItemInt(IDC_EDIT_MINCAPDIFF, tRecognize.iMinCapDiff);
		SetDlgItemText(IDC_EDIT_CALIINFO, tRecognize.cCaliInfo);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRecoParam (%d,%d)",m_iLogonID,sizeof(tRecognize));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRecoParam (%d,%d)",m_iLogonID,sizeof(tRecognize));
	}
	return TRUE;
}


void CLS_ECOPRecoParamPage::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateRecoParam();
}

void CLS_ECOPRecoParamPage::OnBnClickedButtonRecoparam()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_RecoParamEx tRecognize = {0};
	tRecognize.iRoadwayID = m_cboRoadwayID.GetCurSel();
	tRecognize.iEnable = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	tRecognize.iMaxPlateNO = GetDlgItemInt(IDC_EDIT_MAXPLATE);
	tRecognize.iMaxPlateWidth = GetDlgItemInt(IDC_EDIT_MAXPLATEWIDTH);
	tRecognize.iMinPlateWidth = GetDlgItemInt(IDC_EDIT_MINPLATEWIDTH);
	tRecognize.iEngineNum = GetDlgItemInt(IDC_EDIT_ENGINENUM);
	tRecognize.iAreaType = GetDlgItemInt(IDC_EDIT_AREATYPE);
	tRecognize.iPlateType = GetDlgItemInt(IDC_EDIT_PLATETYPE);
	tRecognize.iSpeed = GetDlgItemInt(IDC_EDIT_SPEED);
	tRecognize.iMaxSkip = GetDlgItemInt(IDC_EDIT_MAXSKIP);
	tRecognize.iMinValid = GetDlgItemInt(IDC_EDIT_MINVALID);
	tRecognize.iFramePercent = GetDlgItemInt(IDC_EDIT_FRAMEPERCENT);
	tRecognize.iMinCapDiff = GetDlgItemInt(IDC_EDIT_MINCAPDIFF);
	GetDlgItemText(IDC_EDIT_CALIINFO, tRecognize.cCaliInfo, 75);
	int iRet = NetClient_SetITSRecoParam(m_iLogonID,&tRecognize,sizeof(tRecognize));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRecoParam (%d,%d)",m_iLogonID,sizeof(tRecognize));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRecoParam (%d,%d)",m_iLogonID,sizeof(tRecognize));
	}
}
