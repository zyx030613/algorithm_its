// Config\HDPage.cpp : implementation file
//

#include "stdafx.h"
#include "HDPage.h"

// CLS_HDPage dialog

IMPLEMENT_DYNAMIC(CLS_HDPage, CDialog)

CLS_HDPage::CLS_HDPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_HDPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_HDPage::~CLS_HDPage()
{
}

void CLS_HDPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_HD_AAE, m_chkAutoApertureEnable);
	DDX_Control(pDX, IDC_CHECK_WDE, m_chkWidthDynamicEnable);
	DDX_Control(pDX, IDC_CHECK_HD_APE, m_chkApheliotropicEnable);
	DDX_Control(pDX, IDC_COMBO_HD_ET, m_cmbExposalTime);
	DDX_Control(pDX, IDC_COMBO_HD_SHUTTER, m_cmbShutter);
	DDX_Control(pDX, IDC_EDIT_HEARTBEATSVR, m_edtEAV);
	DDX_Control(pDX, IDC_CHECK_HD_EXPRECT_SET, m_chkExprectSet);
	DDX_Control(pDX, IDC_CHECK_HD_APRECT_SET, m_chkAprectSet);
	DDX_Control(pDX, IDC_EDIT_HD_EXPRECT_LEFT, m_edtExprectLeft);
	DDX_Control(pDX, IDC_EDIT_HD_EXPRECT_TOP, m_edtExprectTop);
	DDX_Control(pDX, IDC_EDIT_HD_EXPRECT_RIGHT, m_edtExprectRight);
	DDX_Control(pDX, IDC_EDIT_HD_EXPRECT_BOTTOM, m_edtExprectBottom);
	DDX_Control(pDX, IDC_COMBO_HD_AUTOPLUS, m_cmbAutoPlus);
	DDX_Control(pDX, IDC_COMBO_HD_TEMPLATEID, m_cmbTemplateID);
	DDX_Control(pDX, IDC_EDIT1, m_edtTemplateName);
	DDX_Control(pDX, IDC_EDIT_HD_APRECT_LEFT, m_edtAprectLeft);
	DDX_Control(pDX, IDC_EDIT_HD_APRECT_TOP, m_edtAprectTop);
	DDX_Control(pDX, IDC_EDIT_HD_APRECT_RIGHT, m_edtAprectRight);
	DDX_Control(pDX, IDC_EDIT_HD_APRECT_BOTTOM, m_edtAprectBottom);
	DDX_Control(pDX, IDC_COMBO_APERTURE, m_cboApertureType);
}


BEGIN_MESSAGE_MAP(CLS_HDPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HD_AAESET, &CLS_HDPage::OnBnClickedButtonHdAaeset)
	ON_BN_CLICKED(IDC_BUTTON_HD_EAVSET, &CLS_HDPage::OnBnClickedButtonHdEavset)
	ON_BN_CLICKED(IDC_BUTTON_HD_WDESET, &CLS_HDPage::OnBnClickedButtonHdWdeset)
	ON_BN_CLICKED(IDC_BUTTON_HD_APESET, &CLS_HDPage::OnBnClickedButtonHdApeset)
	ON_BN_CLICKED(IDC_BUTTON_HD_ET, &CLS_HDPage::OnBnClickedButtonHdEt)
	ON_BN_CLICKED(IDC_BUTTON_HD_SHUTTERSET, &CLS_HDPage::OnBnClickedButtonHdShutterset)
	ON_BN_CLICKED(IDC_CHECK_HD_EXPRECT_SET, &CLS_HDPage::OnBnClickedCheckHdExprectSet)
	ON_BN_CLICKED(IDC_CHECK_HD_APRECT_SET, &CLS_HDPage::OnBnClickedCheckHdAprectSet)
	ON_BN_CLICKED(IDC_BUTTON_HD_SETEXPRECT, &CLS_HDPage::OnBnClickedButtonHdSetexprect)
	ON_BN_CLICKED(IDC_BUTTON_HD_SETAPRECT, &CLS_HDPage::OnBnClickedButtonHdSetaprect)
	ON_BN_CLICKED(IDC_BUTTON_HD_SETAUTOPLUS, &CLS_HDPage::OnBnClickedButtonHdSetautoplus)
	ON_CBN_SELCHANGE(IDC_COMBO_HD_TEMPLATEID, &CLS_HDPage::OnCbnSelchangeComboHdTemplateid)
	ON_BN_CLICKED(IDC_BUTTON_HD_SETTEMPLATENAME, &CLS_HDPage::OnBnClickedButtonHdSettemplatename)
	ON_BN_CLICKED(IDC_BUTTON_HD_SETTEMPLATEMAP, &CLS_HDPage::OnBnClickedButtonHdSettemplatemap)
	ON_BN_CLICKED(IDC_BTN_HD_APRETURE_SET, &CLS_HDPage::OnBnClickedBtnHdApretureSet)
END_MESSAGE_MAP()


// CLS_HDPage message handlers
BOOL CLS_HDPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_edtEAV.SetLimitText(10);
	m_edtExprectLeft.SetLimitText(10);
	m_edtExprectTop.SetLimitText(10);
	m_edtExprectRight.SetLimitText(10);
	m_edtExprectBottom.SetLimitText(10);
	m_edtAprectLeft.SetLimitText(10);
	m_edtAprectTop.SetLimitText(10);
	m_edtAprectRight.SetLimitText(10);
	m_edtAprectBottom.SetLimitText(10);
	m_edtTemplateName.SetLimitText(63);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE1))-> SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE2))-> SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE3))-> SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE4))-> SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE5))-> SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE6))-> SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE7))-> SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_EDIT_HD_TIMERANGE8))-> SetLimitText(10);
	m_cmbAutoPlus.ResetContent();
	CString strAutoPlus;
	for (int i=0; i<=255; i++)
	{
		strAutoPlus.Format("%d",i);
		m_cmbAutoPlus.AddString(strAutoPlus);
	}
	UI_UpdateLanguage();
	return TRUE;
}

void CLS_HDPage::OnChannelChanged(int _iLogonID, int _iChannelNo, int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	UI_UpdateAperture();
	UI_UpdateInfo();
	UI_UpdateTemplate();
}

void CLS_HDPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateLanguage();
}
void CLS_HDPage::OnBnClickedButtonHdAaeset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iEnable = m_chkAutoApertureEnable.GetCheck();
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 0, &iEnable, sizeof(iEnable));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d)HdAaeset", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d)HdAaeset", m_iLogonID);
}


void CLS_HDPage::OnBnClickedButtonHdEavset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iValve = GetDlgItemInt(IDC_EDIT_HEARTBEATSVR);
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 1, &iValve, sizeof(iValve));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d)HdEavset", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d)HdEavset", m_iLogonID);
}

void CLS_HDPage::OnBnClickedButtonHdWdeset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iEnable = m_chkWidthDynamicEnable.GetCheck();
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 2, &iEnable, sizeof(iEnable));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d,0,2)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d,0,2)", m_iLogonID);
}

void CLS_HDPage::OnBnClickedButtonHdApeset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iEnable = m_chkApheliotropicEnable.GetCheck();
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 3, &iEnable, sizeof(iEnable));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d,0,3)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d,0,3)", m_iLogonID);
}

void CLS_HDPage::OnBnClickedButtonHdEt()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iValue = m_cmbExposalTime.GetCurSel();
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 4, &iValue, sizeof(iValue));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d,0,4)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d,0,4)", m_iLogonID);
}

void CLS_HDPage::OnBnClickedButtonHdShutterset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iValue = m_cmbShutter.GetCurSel();
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 5, &iValue, sizeof(iValue));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d,0,5)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d,0,5)", m_iLogonID);
}

void CLS_HDPage::UI_UpdateInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iHDValue =0;
 
	if (0 == NetClient_GetHDCamerEx(m_iLogonID, 0, 0, &iHDValue, sizeof(iHDValue)))
	{
		m_chkAutoApertureEnable.SetCheck(iHDValue);
	}
	if (0 == NetClient_GetHDCamerEx(m_iLogonID, 0, 1, &iHDValue, sizeof(iHDValue)))
	{
		SetDlgItemInt(IDC_EDIT_HEARTBEATSVR, iHDValue);
	}
	if (0 == NetClient_GetHDCamerEx(m_iLogonID, 0, 2, &iHDValue, sizeof(iHDValue)))
	{ 
		m_chkWidthDynamicEnable.SetCheck(iHDValue);
	}
	if (0 == NetClient_GetHDCamerEx(m_iLogonID, 0, 3, &iHDValue, sizeof(iHDValue)))
	{
		m_chkApheliotropicEnable.SetCheck(iHDValue);
	}
	if (0 == NetClient_GetHDCamerEx(m_iLogonID, 0, 4, &iHDValue, sizeof(iHDValue)))
	{
		m_cmbExposalTime.SetCurSel(iHDValue);
	}
	if (0 == NetClient_GetHDCamerEx(m_iLogonID, 0, 5, &iHDValue, sizeof(iHDValue)))
	{
		m_cmbShutter.SetCurSel(iHDValue);
	}

	RECT rct = {0};
	NetClient_GetHDCamerEx(m_iLogonID, 0, 6, &rct, sizeof(rct));
	SetDlgItemInt(IDC_EDIT_HD_EXPRECT_LEFT, rct.left);
	SetDlgItemInt(IDC_EDIT_HD_EXPRECT_TOP, rct.top);
	SetDlgItemInt(IDC_EDIT_HD_EXPRECT_RIGHT, rct.right);
	SetDlgItemInt(IDC_EDIT_HD_EXPRECT_BOTTOM, rct.bottom);

	memset(&rct, 0, sizeof(rct));
	NetClient_GetHDCamerEx(m_iLogonID, 0, 7, &rct, sizeof(rct));
	SetDlgItemInt(IDC_EDIT_HD_APRECT_LEFT, rct.left);
	SetDlgItemInt(IDC_EDIT_HD_APRECT_TOP, rct.top);
	SetDlgItemInt(IDC_EDIT_HD_APRECT_RIGHT, rct.right);
	SetDlgItemInt(IDC_EDIT_HD_APRECT_BOTTOM, rct.bottom);

	int iAutoPlus = 0;
	NetClient_GetHDCamerEx(m_iLogonID, 0, 8, &iAutoPlus, sizeof(iAutoPlus));
	m_cmbAutoPlus.SetCurSel(iAutoPlus);

	ITS_TOTAL_TTemplateMap pa = {0};
	if (NetClient_GetHDTemplateMap(m_iLogonID, m_iChannelNo, &pa, sizeof(pa)) == 0)
	{
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE1, pa.templatemap[0].iTemplateID);
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE2, pa.templatemap[1].iTemplateID);
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE3, pa.templatemap[2].iTemplateID);
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE4, pa.templatemap[3].iTemplateID);
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE5, pa.templatemap[4].iTemplateID);
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE6, pa.templatemap[5].iTemplateID);
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE7, pa.templatemap[6].iTemplateID);
		SetDlgItemInt(IDC_EDIT_HD_TIMERANGE8, pa.templatemap[7].iTemplateID);
	}
}

void CLS_HDPage::OnBnClickedCheckHdExprectSet()
{
	int iCheck = m_chkExprectSet.GetCheck();
	if (BST_CHECKED == iCheck)
	{
		m_chkAprectSet.SetCheck(BST_UNCHECKED);
	}
}

void CLS_HDPage::OnBnClickedCheckHdAprectSet()
{
	int iCheck = m_chkAprectSet.GetCheck();
	if (BST_CHECKED == iCheck)
	{
		m_chkExprectSet.SetCheck(BST_UNCHECKED);
	}
}

void CLS_HDPage::OnBnClickedButtonHdSetexprect()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	RECT rct = {0};
	rct.left = GetDlgItemInt(IDC_EDIT_HD_EXPRECT_LEFT);
	rct.top = GetDlgItemInt(IDC_EDIT_HD_EXPRECT_TOP);
	rct.right = GetDlgItemInt(IDC_EDIT_HD_EXPRECT_RIGHT);
	rct.bottom = GetDlgItemInt(IDC_EDIT_HD_EXPRECT_BOTTOM);

	if (rct.bottom == 0 && rct.left == 0 && rct.right == 0 && rct.top == 0)
	{
	}
	else if(rct.bottom <= rct.top || rct.right  <= rct.left)
	{
		//MessageBox("区域坐标不合法!","",MB_OK|MB_TOPMOST);
		AddLog(LOG_TYPE_MSG, "", "Invalid Parameter(%d)", m_iLogonID);
		return;
	}
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 6, &rct, sizeof(rct));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d,0,6)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d,0,6)", m_iLogonID);
	}
}

void CLS_HDPage::OnBnClickedButtonHdSetaprect()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	RECT rct = {0};
	rct.left = GetDlgItemInt(IDC_EDIT_HD_APRECT_LEFT);
	rct.top = GetDlgItemInt(IDC_EDIT_HD_APRECT_TOP);
	rct.right = GetDlgItemInt(IDC_EDIT_HD_APRECT_RIGHT);
	rct.bottom = GetDlgItemInt(IDC_EDIT_HD_APRECT_BOTTOM);

	if (rct.bottom == 0 && rct.left == 0 && rct.right == 0 && rct.top == 0)
	{
	}
	else if(rct.bottom <= rct.top || rct.right  <= rct.left)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Parameter(%d)", m_iLogonID);
		return;
	}
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 7, &rct, sizeof(rct));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d,0,7)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d,0,7)", m_iLogonID);
	}
}

void CLS_HDPage::OnBnClickedButtonHdSetautoplus()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iAutoPlus = m_cmbAutoPlus.GetCurSel();
	if (iAutoPlus < 0)
	{
		MessageBox("区域坐标不合法!","",MB_OK|MB_TOPMOST);
		return;
	}
	int iRet = NetClient_SetHDCamerEx(m_iLogonID, 0, 8, &iAutoPlus, sizeof(iAutoPlus));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDCamerEx(%d,0,8)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDCamerEx(%d,0,8)", m_iLogonID);
}

void CLS_HDPage::OnCbnSelchangeComboHdTemplateid()
{
	UI_UpdateTemplate();
}

void CLS_HDPage::OnBnClickedButtonHdSettemplatename()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iTemplateID = m_cmbTemplateID.GetCurSel();
	char cTemplateName[32] = {0};
	GetDlgItemText(IDC_EDIT_TEMPLATE_NAME, cTemplateName, 31);
	int iRet = NetClient_SetHDTemplateName(m_iLogonID, iTemplateID, cTemplateName);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDTemplateName(%d)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDTemplateName(%d)", m_iLogonID);
}

void CLS_HDPage::OnBnClickedButtonHdSettemplatemap()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	ITS_TOTAL_TTemplateMap pa = {0};
	pa.templatemap[0].iTemplateID = GetDlgItemInt(IDC_EDIT_HD_TIMERANGE1);
	pa.templatemap[1].iTemplateID = GetDlgItemInt(IDC_EDIT_HD_TIMERANGE2);
	pa.templatemap[2].iTemplateID =	GetDlgItemInt(IDC_EDIT_HD_TIMERANGE3);
	pa.templatemap[3].iTemplateID = GetDlgItemInt(IDC_EDIT_HD_TIMERANGE4);
	pa.templatemap[4].iTemplateID = GetDlgItemInt(IDC_EDIT_HD_TIMERANGE5);
	pa.templatemap[5].iTemplateID = GetDlgItemInt(IDC_EDIT_HD_TIMERANGE6);
	pa.templatemap[6].iTemplateID = GetDlgItemInt(IDC_EDIT_HD_TIMERANGE7);
	pa.templatemap[7].iTemplateID = GetDlgItemInt(IDC_EDIT_HD_TIMERANGE8);

	int iRet = NetClient_SetHDTemplateMap(m_iLogonID, m_iChannelNo, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDTemplateMap(%d)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDTemplateMap(%d)", m_iLogonID);
}

void CLS_HDPage::UI_UpdateLanguage()
{
	SetDlgItemTextEx(IDC_CHECK_HD_AAE, IDS_CONFIG_HD_AUTOAPERTUREENABLE);
	SetDlgItemTextEx(IDC_STATIC_HD_EAV, IDS_CONFIG_HD_ELECTRONAPERTUREVALUE);
	SetDlgItemTextEx(IDC_CHECK_WDE, IDS_CONFIG_HD_WIDTHDYNAMICENABLE);
	SetDlgItemTextEx(IDC_CHECK_HD_APE,IDS_CONFIG_HD_APHELIOTROPICENABLE);
	SetDlgItemTextEx(IDC_STATIC_HD_EXPOSALTIME,IDS_CONFIG_HD_EXPOSALTIME);
	SetDlgItemTextEx(IDC_STATIC_HD_SHUTTER,IDS_CONFIG_HD_SHUTTER);
	SetDlgItemTextEx(IDC_STATIC_HD_EXPOSALAREA,IDS_CONFIG_HD_EXPOSALAREA);
	SetDlgItemTextEx(IDC_CHECK_HD_EXPRECT_SET,IDS_CONFIG_HD_MOUSESET);
	SetDlgItemTextEx(IDC_STATIC_HD_AA,IDS_CONFIG_HD_APHELIOTROPICAREA);
	SetDlgItemTextEx(IDC_CHECK_HD_APRECT_SET, IDS_CONFIG_HD_MOUSESET);
	SetDlgItemTextEx(IDC_STATIC_HD_AUTOINCREASE, IDS_CONFIG_HD_AUTOINCREASE);
	SetDlgItemTextEx(IDC_STATIC_HD_TEMPLATENAME, IDS_CONFIG_HD_TEMPLATENAME);
	SetDlgItemTextEx(IDC_STATIC_HD_TEMPLATEID, IDS_CONFIG_HD_TEMPLATEID);
	SetDlgItemTextEx(IDC_STATIC_HD_TN, IDS_CONFIG_HD_TEMPLATENAME);
	SetDlgItemTextEx(IDC_STATIC_HD_GRP, IDS_CONFIG_HD_GRPTEMPLATEMAP);
	SetDlgItemTextEx(IDC_BUTTON_HD_AAESET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_EAVSET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_WDESET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_APESET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_ET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_SHUTTERSET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_SETEXPRECT, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_SETAPRECT, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_SETAUTOPLUS, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_SETTEMPLATENAME, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_HD_SETTEMPLATEMAP, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_HD_TN, IDS_CONFIG_HD_TEMPLATENAME2);
	SetDlgItemTextEx(IDC_STATIC_APERTURE_TYPE, IDS_HD_APTURE_TYPE);
	SetDlgItemTextEx(IDC_BTN_HD_APRETURE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_WARING, IDS_OLD_HD_WARING);

	InsertString(m_cboApertureType, 0, "DC");
	InsertString(m_cboApertureType, 1, "Piris");
}

void CLS_HDPage::UI_UpdateTemplate()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iTemplateID = m_cmbTemplateID.GetCurSel();
	char cTemplateName[32] = {0};

	int iRet = NetClient_GetHDTemplateName(m_iLogonID, iTemplateID, cTemplateName);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_TEMPLATE_NAME, cTemplateName);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetHDTemplateName(%d)", m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetHDTemplateName(%d)", m_iLogonID);

}

void CLS_HDPage::UI_UpdateAperture()
{
	if (m_iLogonID < 0)
		return;

	ApertureType stAperture = {0};
	stAperture.iBufSize = sizeof(stAperture);
	int iRetSize = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_IRIS_TYPE,0, &stAperture, sizeof(ApertureType), &iRetSize);
	if (0 == iRet)
	{
		m_cboApertureType.SetCurSel(stAperture.iType -1);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(%d,%d,%d,%d,%d)",m_iLogonID,NET_CLIENT_IRIS_TYPE,stAperture.iType,sizeof(ApertureType),iRetSize);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(%d,%d,%d,%d,%d)",m_iLogonID,NET_CLIENT_IRIS_TYPE,stAperture.iType,sizeof(ApertureType),iRetSize);;
	}
	return;
}

void CLS_HDPage::OnBnClickedBtnHdApretureSet()
{
	if (m_iLogonID < 0)
		return ;

	ApertureType stAperture = {0};
	stAperture.iBufSize = sizeof(ApertureType);
	stAperture.iType = m_cboApertureType.GetCurSel() + 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_IRIS_TYPE,0, &stAperture, sizeof(ApertureType));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d,%d,%d)",m_iLogonID,NET_CLIENT_IRIS_TYPE,stAperture.iType,sizeof(ApertureType));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d,%d,%d)",m_iLogonID,NET_CLIENT_IRIS_TYPE,stAperture.iType,sizeof(ApertureType));
	}
}
