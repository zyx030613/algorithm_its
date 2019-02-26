// ECOPImgDisposalPage.cpp : implementation file
//

#include "stdafx.h"
#include "ECOPImgDisposalPage.h"


// CLS_ECOPImgDisposalPage dialog

IMPLEMENT_DYNAMIC(CLS_ECOPImgDisposalPage, CDialog)

CLS_ECOPImgDisposalPage::CLS_ECOPImgDisposalPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ECOPImgDisposalPage::IDD, pParent)
{
	m_iLogonID = -1;

}

CLS_ECOPImgDisposalPage::~CLS_ECOPImgDisposalPage()
{
}

void CLS_ECOPImgDisposalPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_CHECK_IMGDISPOSAL_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_EDIT_QUALITY, m_edtQuality);
	DDX_Control(pDX, IDC_EDIT_SATURATION, m_edtSaturation);
	DDX_Control(pDX, IDC_EDIT_BRIGHTEN, m_edtBrighten);
	DDX_Control(pDX, IDC_EDIT_CONTRAST, m_edtContrast);
	DDX_Control(pDX, IDC_EDIT_GAMMA, m_edtGamma);
	DDX_Control(pDX, IDC_EDIT_ACUTANCE, m_edtAcutance);
	DDX_Control(pDX, IDC_EDIT_IMGENHANCE, m_edtImgEnhance);
	DDX_Control(pDX, IDC_BUTTON_IMGDISPOSAL, m_btnImgDisposal);
}


BEGIN_MESSAGE_MAP(CLS_ECOPImgDisposalPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ECOPImgDisposalPage::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BUTTON_IMGDISPOSAL, &CLS_ECOPImgDisposalPage::OnBnClickedButtonImgdisposal)
END_MESSAGE_MAP()


// CLS_ECOPImgDisposalPage message handlers
BOOL CLS_ECOPImgDisposalPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	m_edtQuality.SetLimitText(3);
	m_edtSaturation.SetLimitText(3);
	m_edtBrighten.SetLimitText(3);
	m_edtContrast.SetLimitText(3);
	m_edtGamma.SetLimitText(2);
	m_edtAcutance.SetLimitText(3);
	m_edtImgEnhance.SetLimitText(3);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ECOPImgDisposalPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateImgDisposal();
}

void CLS_ECOPImgDisposalPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ECOPImgDisposalPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_IMGDISPOSAL,IDS_CONFIG_ECOP_IMGDISPOSAL);
	SetDlgItemTextEx(IDC_CHECK_IMGDISPOSAL_ENABLE,IDS_CONFIG_ECOP_IMGDISPOSAL_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_QUALITY,IDS_CONFIG_ECOP_QUALITY);
	SetDlgItemTextEx(IDC_STATIC_SATURATION,IDS_CONFIG_ECOP_SATURATION);
	SetDlgItemTextEx(IDC_STATIC_BRIGHTEN,IDS_CONFIG_ECOP_BRIGHTEN);
	SetDlgItemTextEx(IDC_STATIC_CONTRAST,IDS_CONFIG_ECOP_CONTRAST);
	SetDlgItemTextEx(IDC_STATIC_GAMMA,IDS_CONFIG_ECOP_GAMMA);
	SetDlgItemTextEx(IDC_STATIC_ACUTANCE,IDS_CONFIG_ECOP_ACUTANCE);
	SetDlgItemTextEx(IDC_STATIC_IMGENHANCE,IDS_CONFIG_ECOP_IMGENHANCE);
	SetDlgItemTextEx(IDC_BUTTON_IMGDISPOSAL,IDS_SET);
}

BOOL CLS_ECOPImgDisposalPage::UI_UpdateImgDisposal()
{
	if (m_iLogonID < 0)
		return FALSE;

	TImgDisposal tDisposal = {0};
	tDisposal.iChannelID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetImgDisposal(m_iLogonID,&tDisposal,sizeof(tDisposal));
	if (0 == iRet)
	{
		//m_cboRoadwayID.SetCurSel(tDisposal.iChannelID);
		m_chkEnable.SetCheck(tDisposal.iStartUp?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_QUALITY, tDisposal.iQuality);
		SetDlgItemInt(IDC_EDIT_SATURATION, tDisposal.iSaturation);
		SetDlgItemInt(IDC_EDIT_BRIGHTEN, tDisposal.iBrighten);
		SetDlgItemInt(IDC_EDIT_CONTRAST, tDisposal.iContrast);
		SetDlgItemInt(IDC_EDIT_GAMMA, tDisposal.iGamma);
		SetDlgItemInt(IDC_EDIT_ACUTANCE, tDisposal.iAcutance);
		SetDlgItemInt(IDC_EDIT_IMGENHANCE, tDisposal.iImgEnhanceLevel);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetImgDisposal (%d,%d)",m_iLogonID,sizeof(tDisposal));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetImgDisposal (%d,%d)",m_iLogonID,sizeof(tDisposal));
	}
	return TRUE;
}
void CLS_ECOPImgDisposalPage::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateImgDisposal();
}

void CLS_ECOPImgDisposalPage::OnBnClickedButtonImgdisposal()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TImgDisposal tDisposal = {0};
	tDisposal.iChannelID = m_cboRoadwayID.GetCurSel();
	tDisposal.iStartUp = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	tDisposal.iQuality = GetDlgItemInt(IDC_EDIT_QUALITY);
	tDisposal.iSaturation = GetDlgItemInt(IDC_EDIT_SATURATION);
	tDisposal.iBrighten = GetDlgItemInt(IDC_EDIT_BRIGHTEN);
	tDisposal.iContrast = GetDlgItemInt(IDC_EDIT_CONTRAST);
	tDisposal.iGamma = GetDlgItemInt(IDC_EDIT_GAMMA);
	tDisposal.iAcutance = GetDlgItemInt(IDC_EDIT_ACUTANCE);
	tDisposal.iImgEnhanceLevel = GetDlgItemInt(IDC_EDIT_IMGENHANCE);
	int iRet = NetClient_SetImgDisposal(m_iLogonID,&tDisposal,sizeof(tDisposal));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetImgDisposal (%d,%d)",m_iLogonID,sizeof(tDisposal));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetImgDisposal (%d,%d)",m_iLogonID,sizeof(tDisposal));
	}
}
