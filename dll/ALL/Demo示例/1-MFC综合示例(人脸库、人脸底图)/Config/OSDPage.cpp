// OSDPage.cpp : implementation file
//

#include "stdafx.h"
#include "OSDPage.h"

// CLS_OSDPage dialog

IMPLEMENT_DYNAMIC(CLS_OSDPage, CDialog)

CLS_OSDPage::CLS_OSDPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_OSDPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
	m_iColor = 0;
	m_bDateTime = false;
	m_bLogo = false;
	m_iFontDbLattice = FALSE;
}

CLS_OSDPage::~CLS_OSDPage()
{
}

void CLS_OSDPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_CHANNELTITLE, m_chkChannelTitle);
	DDX_Control(pDX, IDC_EDIT_CHANNELTITLE, m_edtChannelTitle);
	DDX_Control(pDX, IDC_BUTTON_CHANNELTITLE, m_btnChannelTitle);
	DDX_Control(pDX, IDC_SLIDER_DIAPHANEITY, m_sldDiaphaneity);
	DDX_Control(pDX, IDC_EDIT_DATETIME_XPOS, m_edtDateTimePosX);
	DDX_Control(pDX, IDC_EDIT_DATETIME_YPOS, m_edtDateTimePosY);
	DDX_Control(pDX, IDC_EDIT_CHANNELTITLE_XPOS, m_edtChannelTitlePosX);
	DDX_Control(pDX, IDC_EDIT_CHANNELTITLE_YPOS, m_edtChannelTitlePosY);
	DDX_Control(pDX, IDC_BUTTON_LOGO, m_btnLogo);
	DDX_Control(pDX, IDC_EDIT_LOGO_XPOS, m_edtLogoPosX);
	DDX_Control(pDX, IDC_EDIT_LOGO_YPOS, m_edtLogoPosY);
	DDX_Control(pDX, IDC_BUTTON_DRAWTEXT, m_btnDrawText);
	DDX_Control(pDX, IDC_EDIT_OSD_TEXT, m_edtDrawText);
	DDX_Control(pDX, IDC_EDIT_DRAWTEXT_XPOS, m_edtDrawTextPosX);
	DDX_Control(pDX, IDC_EDIT_DRAWTEXT_YPOS, m_edtDrawTextPosY);
	DDX_Control(pDX, IDC_BUTTON_TEXTCMD, m_btnTextCmd);
	DDX_Control(pDX, IDC_CHECK_DATETIME, m_chkDateTime);
	DDX_Control(pDX, IDC_CHECK_LOGO, m_chkLogo);
	DDX_Control(pDX, IDC_BUTTON_DATETIME, m_btnDateTime);
	DDX_Control(pDX, IDC_BUTTON_LOGO, m_btnLogo);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_btnColor);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_stxtProgress);
	DDX_Control(pDX, IDC_EDIT_ALPHA, m_edtAlpha);
	DDX_Control(pDX, IDC_BUTTON_ALPHA, m_btnAlpha);
	DDX_Control(pDX, IDC_COMBO_OSDTYPE, m_cboOSDType);
	DDX_Control(pDX, IDC_CHECK_BKCOLOR, m_chkBackgroundColor);
	DDX_Control(pDX, IDC_BUTTON_OSDCOLOR, m_btnOSDColor);
	DDX_Control(pDX, IDC_BUTTON_OSDSET, m_btnOSDSet);
	DDX_Control(pDX, IDC_COMBO_OSDFONTSIZE, m_cboFontSize);
	DDX_Control(pDX, IDC_EDIT_OSDFONWID, m_edtFontWid);
	DDX_Control(pDX, IDC_EDIT_OSDFONHIGH, m_edtFontHigh);
	DDX_Control(pDX, IDC_EDIT_CHANNTITLEEX, m_edtChanTitleEx);
	DDX_Control(pDX, IDC_EDIT_CHANTITLCOLOEX, m_edtChanTitlColoEx);
	DDX_Control(pDX, IDC_COMBO_DEVCOMNAME, m_cboDevComNameType);
	DDX_Radio(pDX, IDC_RADIO_OSD_FONT_DB_TYPE_VECTOR, m_iFontDbLattice);
	DDX_Control(pDX, IDC_EDIT_DEVCOMNAME, m_edtChannelCommonName);
}


BEGIN_MESSAGE_MAP(CLS_OSDPage, CLS_BasePage)

	ON_BN_CLICKED(IDC_BUTTON_CHANNELTITLE, &CLS_OSDPage::OnBnClickedButtonChanneltitle)
	ON_NOTIFY(BCN_DROPDOWN, IDC_CHECK_DATETIME, &CLS_OSDPage::OnBnDropDownCheckDatetime)
	ON_NOTIFY(BCN_DROPDOWN, IDC_CHECK_LOGO, &CLS_OSDPage::OnBnDropDownCheckLogo)
	ON_BN_CLICKED(IDC_BUTTON_LOGO,  CLS_OSDPage::OnBnClickedButtonLogo)
	ON_BN_CLICKED(IDC_BUTTON_DRAWTEXT, &CLS_OSDPage::OnBnClickedButtonDrawtext)
	ON_BN_CLICKED(IDC_BUTTON_TEXTCMD, &CLS_OSDPage::OnBnClickedButtonTextcmd)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DIAPHANEITY, &CLS_OSDPage::OnNMCustomdrawSliderDiaphaneity)
	ON_BN_CLICKED(IDC_BUTTON_DATETIME, &CLS_OSDPage::OnBnClickedButtonDatetime)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CLS_OSDPage::OnBnClickedButtonColor)
	ON_NOTIFY(BCN_DROPDOWN, IDC_CHECK_CHANNELTITLE, &CLS_OSDPage::OnBnDropDownCheckChanneltitle)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_ALPHA, &CLS_OSDPage::OnBnClickedButtonAlpha)
	ON_BN_CLICKED(IDC_BUTTON_OSDSET, &CLS_OSDPage::OnBnClickedButtonOsdset)
	ON_CBN_SELCHANGE(IDC_COMBO_OSDTYPE, &CLS_OSDPage::OnCbnSelchangeComboOsdtype)
	ON_BN_CLICKED(IDC_BUTTON_OSDFONTSIZE, &CLS_OSDPage::OnBnClickedButtonOsdfontsize)
	ON_CBN_SELCHANGE(IDC_COMBO_OSDFONTSIZE, &CLS_OSDPage::OnCbnSelchangeComboOsdfontsize)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVCOMNAME, &CLS_OSDPage::OnCbnSelchangeComboDevcomname)
	ON_BN_CLICKED(IDC_RADIO_OSD_FONT_DB_TYPE_VECTOR, &CLS_OSDPage::OnBnClickedRadioOsdFontDbTypeVector)
	ON_BN_CLICKED(IDC_RADIO_OSD_FONT_DB_TYPE_LATTICE, &CLS_OSDPage::OnBnClickedRadioOsdFontDbTypeVector)
END_MESSAGE_MAP()


// CLS_OSDPage message handlers

BOOL CLS_OSDPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_chkDateTime.SetCheck(BST_UNCHECKED);
	m_chkLogo.SetCheck(BST_UNCHECKED);

	m_edtChannelTitle.SetLimitText(LEN_64);
	m_edtChannelCommonName.SetLimitText(LEN_64);

	m_edtChannelTitlePosX.SetLimitText(7);
	m_edtChannelTitlePosY.SetLimitText(7);
	m_edtDateTimePosX.SetLimitText(7);
	m_edtDateTimePosY.SetLimitText(7);
	m_edtLogoPosX.SetLimitText(7);
	m_edtLogoPosY.SetLimitText(7);
	m_edtDrawText.SetLimitText(511);

	m_sldDiaphaneity.SetRange(0, 100, TRUE);
	m_sldDiaphaneity.SetPos(0);
	m_sldDiaphaneity.SetTicFreq(10);

	m_btnOSDColor.SetChildNum(0);
	m_btnOSDColor.SetColor(0,RGB(0,0,0));

	m_edtAlpha.SetLimitText(10);

// 	m_cboFontSize.AddString(GetTextEx(IDS_CONFIG_OSD_FONTSIZEADAPT));
// 	for (int i=1; i<=5; i++)
// 	{
// 		CString strNo;
// 		strNo.Format("%d",i);
// 		m_cboFontSize.AddString(strNo);
// 	}
// 	m_cboFontSize.AddString(GetTextEx(IDS_CONFIG_OSD_DEFINEFONTSIZE));
// 	m_cboFontSize.SetCurSel(1);
	SetDlgItemInt(IDC_EDIT_OSDFONWID, 0);
	SetDlgItemInt(IDC_EDIT_OSDFONHIGH, 0);
	m_edtFontWid.EnableWindow(FALSE);
	m_edtFontHigh.EnableWindow(FALSE);

	m_cboDevComNameType.AddString(GetTextEx(IDS_PLAYBACK_FILE_TYPE_VIDEO));
	m_cboDevComNameType.AddString(GetTextEx(IDS_FUNC_ALARMIN));
	m_cboDevComNameType.AddString(GetTextEx(IDS_FUNC_ALARMOUT));
 	m_cboDevComNameType.SetCurSel(0);
	UI_UpdateDialog();
	
	m_cboOSDType.SetCurSel(0);
	return TRUE;
}

void CLS_OSDPage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
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
	if (_iStreamNo < 0)
	{
		m_iStreamNo = 0;
	}
	else
	{
		m_iStreamNo = _iStreamNo;
	}
	
	UI_UpdateChannelTitle();
	UI_UpdateDateTime();
	UI_UpdateLogo();
	UI_UpdateDrawText();
	UI_UpdateDiaphaneity();
	UI_UpdateAlpha();
	UI_UpdateColor();
	UI_UpdateFontSize();
	UI_UpdateFontDbType();
}

void CLS_OSDPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_OSDPage::OnBnDropDownCheckChanneltitle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	UI_UpdateChannelTitle();
	*pResult = 0;
}

void CLS_OSDPage::OnBnClickedButtonChanneltitle()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	char cChannelTitle[65];
	GetDlgItemText(IDC_EDIT_CHANNELTITLE, cChannelTitle, 64);
	if(strchr(cChannelTitle,';'))
	{
		AddLog(LOG_TYPE_MSG,"","The semicolon can not be contained in the channel title");
		return;
	}

	int iColor = GetDlgItemInt(IDC_EDIT_CHANTITLCOLOEX);
	int iRet = NetClient_SetOsdText(m_iLogonID, m_iChannelNo, (unsigned char *)cChannelTitle, iColor);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOsdText(%d,%d,%s,%d)",m_iLogonID,m_iChannelNo,cChannelTitle,iColor);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOsdText(%d,%d,%s,%d)",m_iLogonID,m_iChannelNo,cChannelTitle,iColor);
	}

	char cChanTitEx[65];
	GetDlgItemText(IDC_EDIT_DEVCOMNAME, cChanTitEx, 64);
	TDevCommonName tDevComName = {0};
	tDevComName.m_iSize = sizeof(TDevCommonName);
	int iIndex = m_cboDevComNameType.GetCurSel();
	if (iIndex < 0 || iIndex > 2)
	{
		return;
	}
	tDevComName.m_iChannelType = iIndex;
	memcpy_s(tDevComName.m_cChanneleName, sizeof(tDevComName.m_cChanneleName), cChanTitEx, 64);
	iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DEV_COMMONNAME, m_iChannelNo, &tDevComName, sizeof(tDevComName));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d,%s,%d)",m_iLogonID, m_iChannelNo, tDevComName.m_cChanneleName, tDevComName.m_iChannelType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d,%s,%d)",m_iLogonID,m_iChannelNo, tDevComName.m_cChanneleName, tDevComName.m_iChannelType);
	}

	int iPosX = 0;
	int iPosY = 0;
	int iEnable;
	iPosX = GetDlgItemInt(IDC_EDIT_CHANNELTITLE_XPOS);
	iPosY = GetDlgItemInt(IDC_EDIT_CHANNELTITLE_YPOS);
	if (iPosY < 0 || iPosX < 0)
	{
		MessageBox(GetTextEx(IDS_POS_ERROR));
		return;
	}
	CString strPosY;
	GetDlgItemText(IDC_EDIT_CHANNELTITLE_YPOS, strPosY);
	if (strPosY.GetLength() <= 0)
	{
		iPosY = -1;
	}
	if (BST_CHECKED == m_chkChannelTitle.GetCheck())
	{
		iEnable = 1;
	}
	else
	{
		iEnable = 0;
	}

	iRet = NetClient_SetOsdType(m_iLogonID, m_iChannelNo, iPosX, iPosY, OSDTYPE_TITLE, iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOsdType(%d,%d,%d,%d,2,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY, iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOsdType(%d,%d,%d,%d,2,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY, iEnable);
	}
}

void CLS_OSDPage::OnBnDropDownCheckDatetime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	UI_UpdateDateTime();

	*pResult = 0;
}

void CLS_OSDPage::OnBnClickedButtonDatetime()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iPosX = 0;
	int iPosY = 0;
	int iEnable = 0;
	iPosX = GetDlgItemInt(IDC_EDIT_DATETIME_XPOS);
	iPosY = GetDlgItemInt(IDC_EDIT_DATETIME_YPOS);
	if (iPosY < 0 || iPosX < 0)
	{
		MessageBox(GetTextEx(IDS_POS_ERROR));
		return;
	}
	CString strPosY;
	GetDlgItemText(IDC_EDIT_DATETIME_YPOS, strPosY);
	if (strPosY.GetLength() <= 0)
	{
		iPosY = -1;
	}
	if (BST_CHECKED == m_chkDateTime.GetCheck())
	{
		iEnable = 1;
	}
	else
	{
		iEnable = 0;
	}
	int iRet = NetClient_SetOsdType(m_iLogonID, m_iChannelNo, iPosX, iPosY, OSDTYPE_TIME, iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOsdType(%d,%d,%d,%d,1,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY, iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOsdType(%d,%d,%d,%d,1,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY, iEnable);
	}
}

void CLS_OSDPage::OnBnDropDownCheckLogo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	UI_UpdateLogo();

	*pResult = 0;
}

void CLS_OSDPage::OnParamChangeNotify(int m_iLogonID, int m_iChannelNo, int _iParaType,void* _pPara,int _iUser)
{
	switch(_iParaType)
	{
	case PARA_SETLOGOOK:
		{
			int iRet = MessageBox(GetTextEx(IDS_CONFIG_LAN_MESSAGETEXT), GetTextEx(IDS_CONFIG_PROMPT),MB_OKCANCEL);
			if (IDOK == iRet)
			{
				iRet = NetClient_Reboot(m_iLogonID);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_Reboot(%d)",m_iLogonID);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_Reboot(%d)",m_iLogonID);
				}
			}
		}
		break;
	default:
		break;
	}
}

void CLS_OSDPage::OnBnClickedButtonLogo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iPosX = 0;
	int iPosY = 0;
	int iEnable = 0;
	iPosX = GetDlgItemInt(IDC_EDIT_LOGO_XPOS);
	iPosY = GetDlgItemInt(IDC_EDIT_LOGO_YPOS);

	if (iPosY < 0 || iPosX < 0)
	{
		MessageBox(GetTextEx(IDS_POS_ERROR));
		return;
	}
	CString strPosY;
	GetDlgItemText(IDC_EDIT_LOGO_YPOS, strPosY);
	if (strPosY.GetLength() <= 0)
	{
		iPosY = -1;
	}
	if (BST_CHECKED == m_chkLogo.GetCheck())
	{
		iEnable = 1;
	}
	else
	{
		iEnable = 0;
	}
	int iRet = NetClient_SetOsdType(m_iLogonID, m_iChannelNo, iPosX, iPosY, OSDTYPE_LOGO, iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOsdType(%d,%d,%d,%d,3,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY, iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOsdType(%d,%d,%d,%d,3,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY, iEnable);
	}
	
	
	CFileDialog clsFileDlg(TRUE, "bmp", "*.bmp", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, ".bmp(*.bmp)|*.bmp|");
	iRet = (int)clsFileDlg.DoModal();
	if (IDOK == iRet)
	{
		CString strLogoFileName = clsFileDlg.GetPathName(); 
		iRet = NetClient_SetOsdLOGO(m_iLogonID, m_iChannelNo, (unsigned char *)(LPSTR)(LPCSTR)strLogoFileName, 0x00FFFFFF);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetOsdLOGO(%d,%d,%s)",m_iLogonID, m_iChannelNo, (LPSTR)(LPCSTR)strLogoFileName);

		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetOsdLOGO(%d,%d,%s)",m_iLogonID, m_iChannelNo, (LPSTR)(LPCSTR)strLogoFileName);
		}
	}
}

void CLS_OSDPage::OnBnClickedButtonDrawtext()
{
	DrawTextOnVideo(1);
}

void CLS_OSDPage::OnBnClickedButtonTextcmd()
{
	DrawTextOnVideo(0);
}

void CLS_OSDPage::OnNMCustomdrawSliderDiaphaneity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iDiaphaneity = m_sldDiaphaneity.GetPos();
	SetDlgItemInt(IDC_STATIC_PROGRESS, iDiaphaneity);
	
	*pResult = 0;
}

void CLS_OSDPage::OnBnClickedButtonColor()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	CColorDialog clsColorDlg;
	int iRet = (int)clsColorDlg.DoModal();
	if (IDOK == iRet)
	{
 		m_iColor = clsColorDlg.GetColor();
		int iTypeNo = m_cboOSDType.GetCurSel()+1;
		try
		{
			m_btnOSDColor.RemoveChild(0);
			m_btnOSDColor.AddChild(0);
			m_btnOSDColor.SetColor(0,RGB(GetRValue(m_iColor), GetGValue(m_iColor),GetBValue(m_iColor)));
		}
		catch (CException* e)
		{
			e->ReportError();
			e->Delete();
		}
	}
}

void CLS_OSDPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_CHECK_CHANNELTITLE, IDS_CONFIG_OSD_CHANNELTITLE);
	SetDlgItemTextEx(IDC_STATIC_CHANNELTITLE_POS, IDS_CONFIG_OSD_CHANNELTITLE_POS);
	SetDlgItemTextEx(IDC_BUTTON_CHANNELTITLE, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DEVCOMNAME, IDS_CONFIG_OSD_CHANNELANOTHERNAME);
	SetDlgItemTextEx(IDC_STATIC_OSD_COLOR, IDS_CONFIG_OSD_COLORTWOO);
	SetDlgItemTextEx(IDC_CHECK_DATETIME, IDS_CONFIG_OSD_DATETIME);
	SetDlgItemTextEx(IDC_BUTTON_DATETIME, IDS_SET);
	SetDlgItemTextEx(IDC_CHECK_LOGO, IDS_CONFIG_OSD_LOGO);
	SetDlgItemTextEx(IDC_BUTTON_LOGO, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_DRAWTEXT, IDS_CONFIG_OSD_DRAWTEXT);
	SetDlgItemTextEx(IDC_BUTTON_TEXTCMD, IDS_CONFIG_OSD_TEXTCMD);
	SetDlgItemTextEx(IDC_STATIC_DIAPHANEITY, IDS_CONFIG_OSD_DIAPHANEITY);
	SetDlgItemTextEx(IDC_BUTTON_COLOR, IDS_CONFIG_OSD_CHOOSE_COLOR);
	SetDlgItemTextEx(IDC_STATIC_OSDTYPE, IDS_CONFIG_OSD_TYPE);
	SetDlgItemTextEx(IDC_CHECK_BKCOLOR, IDS_CONFIG_OSD_BKGROUNDDISPLAY);
	SetDlgItemTextEx(IDC_BUTTON_OSDSET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_OSDFONTSIZE, IDS_CONFIG_OSD_FONTSIZE);
	SetDlgItemTextEx(IDC_BUTTON_OSDFONTSIZE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_ALPHA, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_ALPHA, IDS_CONFIG_OSD_ALPHA);

	SetDlgItemTextEx(IDC_STATIC_OSDFONWID, IDS_CONFIG_OSD_WIDTH);
	SetDlgItemTextEx(IDC_STATIC_OSDFONHIGH, IDS_CONFIG_OSD_HIGHT);

	SetDlgItemTextEx(IDC_STATIC_OSD_FONT_DB_TYPE, IDS_OSD_FONG_DB_TYPE);
	SetDlgItemTextEx(IDC_RADIO_OSD_FONT_DB_TYPE_VECTOR, IDS_OSD_FONT_DB_TYPE_VECTOR);
	SetDlgItemTextEx(IDC_RADIO_OSD_FONT_DB_TYPE_LATTICE, IDS_OSD_FONT_DB_TYPE_LATTICE);

	InsertString(m_cboOSDType,0,IDS_CONFIG_OSD_CHANNELTITLE);
	InsertString(m_cboOSDType,1,IDS_CONFIG_OSD_DATETIME);
	InsertString(m_cboOSDType,2,IDS_CONFIG_OSD_LOGO);
	InsertString(m_cboOSDType,3,IDS_CONFIG_OSD_ADDITIONALCHAR);
	InsertString(m_cboOSDType,4,IDS_CONFIG_OSD_ITS);
	
	m_cboDevComNameType.ResetContent();
	m_cboDevComNameType.AddString(GetTextEx(IDS_PLAYBACK_FILE_TYPE_VIDEO));
	m_cboDevComNameType.AddString(GetTextEx(IDS_FUNC_ALARMIN));
	m_cboDevComNameType.AddString(GetTextEx(IDS_FUNC_ALARMOUT));
	m_cboDevComNameType.SetCurSel(0);

	m_cboFontSize.ResetContent();
	m_cboFontSize.AddString(GetTextEx(IDS_CONFIG_OSD_FONTSIZEADAPT));
	for (int i=1; i<=5; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboFontSize.AddString(strNo);
	}
	m_cboFontSize.AddString(GetTextEx(IDS_CONFIG_OSD_DEFINEFONTSIZE));
	m_cboFontSize.SetCurSel(1);

}

BOOL CLS_OSDPage::UI_UpdateChannelTitle()
{
	if (m_iLogonID < 0)
		return FALSE;

	OSD_TEXT pOsdTest = {0};
	int iRet = NetClient_GetOsdTextEx(m_iLogonID, m_iChannelNo, &pOsdTest, sizeof(pOsdTest));
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_CHANNELTITLE, (LPCTSTR)(pOsdTest.ucOSDText));
		SetDlgItemText(IDC_EDIT_CHANNTITLEEX, (LPCTSTR)(pOsdTest.ucOSDText));
		SetDlgItemInt(IDC_EDIT_CHANTITLCOLOEX, pOsdTest.uiTextColor);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOsdTextEx(%d,%d,%s,%d)",m_iLogonID, m_iChannelNo, pOsdTest.ucOSDText, pOsdTest.uiTextColor);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOsdTextEx(%d,%d,%s,%d)",m_iLogonID,m_iChannelNo, pOsdTest.ucOSDText, pOsdTest.uiTextColor);
	}

	int iBytesReturned = 0;
	TDevCommonName tDevComName = {0};
	tDevComName.m_iSize = sizeof(TDevCommonName);
	int iIndex = m_cboDevComNameType.GetCurSel();
	if (iIndex < 0 || iIndex > 2)
	{
		return -1;
	}
	tDevComName.m_iChannelType = iIndex;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DEV_COMMONNAME, m_iChannelNo, &tDevComName, sizeof(tDevComName), &iBytesReturned);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_DEVCOMNAME, (LPCTSTR)(tDevComName.m_cChanneleName));
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(%d,%d,%s,%d)",m_iLogonID, m_iChannelNo, tDevComName.m_cChanneleName, tDevComName.m_iChannelType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(%d,%d,%s,%d)",m_iLogonID,m_iChannelNo, tDevComName.m_cChanneleName, tDevComName.m_iChannelType);
	}
	int iPosX;
	int iPosY;
	int iEnable;
	iRet = NetClient_GetOsdType(m_iLogonID, m_iChannelNo, OSDTYPE_TITLE, &iPosX, &iPosY, &iEnable);
	if (0 == iRet)
	{
		iPosX = (iPosX >= 0) ? iPosX : 0;
		iPosY = (iPosY >= 0) ? iPosY : 0;
		SetDlgItemInt(IDC_EDIT_CHANNELTITLE_XPOS, iPosX);
		SetDlgItemInt(IDC_EDIT_CHANNELTITLE_YPOS, iPosY);
		if (1 == iEnable)
		{
			m_chkChannelTitle.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkChannelTitle.SetCheck(BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOsdType(%d,%d,2,%d,%d,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOsdType(%d,%d,2,%d,%d,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,iEnable);
	}

	return TRUE;
}

BOOL CLS_OSDPage::UI_UpdateDateTime()
{
	if (m_iLogonID < 0)
		return FALSE;
	
	int iPosX;
	int iPosY;
	int iEnable;
	int iRet = NetClient_GetOsdType(m_iLogonID, m_iChannelNo, OSDTYPE_TIME, &iPosX, &iPosY, &iEnable);
	if (0 == iRet)
	{
		iPosX = (iPosX >= 0) ? iPosX : 0;
		iPosY = (iPosY >= 0) ? iPosY : 0;
		SetDlgItemInt(IDC_EDIT_DATETIME_XPOS, iPosX);
		SetDlgItemInt(IDC_EDIT_DATETIME_YPOS, iPosY);
		if (1 == iEnable)
		{
			m_chkDateTime.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkDateTime.SetCheck(BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOsdType(%d,%d,1,%d,%d,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOsdType(%d,%d,1,%d,%d,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,iEnable);
	}

	return TRUE;
}

BOOL CLS_OSDPage::UI_UpdateLogo()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iPosX;
	int iPosY;
	int iEnable;
	int iRet = NetClient_GetOsdType(m_iLogonID, m_iChannelNo, OSDTYPE_LOGO, &iPosX, &iPosY, &iEnable);
	if (0 == iRet)
	{
		iPosX = (iPosX >= 0) ? iPosX : 0;
		iPosY = (iPosY >= 0) ? iPosY : 0;
		SetDlgItemInt(IDC_EDIT_LOGO_XPOS, iPosX);
		SetDlgItemInt(IDC_EDIT_LOGO_YPOS, iPosY);
		if (1 == iEnable)
		{
			m_chkLogo.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkLogo.SetCheck(BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOsdType(%d,%d,3,%d,%d,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOsdType(%d,%d,3,%d,%d,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,iEnable);
	}

	return TRUE;
}

BOOL CLS_OSDPage::UI_UpdateDrawText()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iPosX = 0;
	int iPosY = 0;
	char cDrawText[512] = {0};
 	int iRet = NetClient_GetTextOnVideo(m_iLogonID, m_iChannelNo, &iPosX, &iPosY, cDrawText, m_iStreamNo);
 	if (0 == iRet)
 	{
		iPosX = (iPosX >= 0) ? iPosX : 0;
		iPosY = (iPosY >= 0) ? iPosY : 0;
 		SetDlgItemInt(IDC_EDIT_DRAWTEXT_XPOS, iPosX);
 		SetDlgItemInt(IDC_EDIT_DRAWTEXT_YPOS, iPosY);
		CString strMoreText(cDrawText);
		strMoreText.Replace(_T("\n"),_T("\r\n"));	
 		m_edtDrawText.SetWindowText(strMoreText);
 		AddLog(LOG_TYPE_SUCC,"","NetClient_GetTextOnVideo(%d,%d,%d,%d,%s,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,cDrawText,m_iStreamNo);
 	}
 	else
 	{
 		AddLog(LOG_TYPE_FAIL,"","NetClient_GetTextOnVideo(%d,%d,%d,%d,%s,%d)",m_iLogonID,m_iChannelNo,iPosX,iPosY,cDrawText,m_iStreamNo);
 	}
	return TRUE;
}

BOOL CLS_OSDPage::UI_UpdateDiaphaneity()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iDiaphaneity;
	int iRet = NetClient_GetOsdDiaphaneity(m_iLogonID, m_iChannelNo, &iDiaphaneity);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_STATIC_PROGRESS, iDiaphaneity);
		m_sldDiaphaneity.SetPos(iDiaphaneity);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOsdDiaphaneity(%d,%d,%d)",m_iLogonID,m_iChannelNo,iDiaphaneity);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOsdDiaphaneity(%d,%d,%d)",m_iLogonID,m_iChannelNo,iDiaphaneity);
	}
	return TRUE;
}


void CLS_OSDPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (SB_ENDSCROLL == nSBCode)
	{
		int iCtrlID = pScrollBar->GetDlgCtrlID();
		switch(iCtrlID)
		{
		case IDC_SLIDER_DIAPHANEITY:
			{
				int iDiaphaneity = m_sldDiaphaneity.GetPos();
				int iRet = NetClient_SetOsdDiaphaneity(m_iLogonID, m_iChannelNo, iDiaphaneity);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_SetOsdDiaphaneity(%d,%d,%d)",m_iLogonID, m_iChannelNo, iDiaphaneity);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_SetOsdDiaphaneity(%d,%d,%d)",m_iLogonID, m_iChannelNo, iDiaphaneity);
				}
			}
			break;
		default:
			break;
		}
	}

	CLS_BasePage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CLS_OSDPage::OnBnClickedButtonAlpha()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iOSDAlpha= GetDlgItemInt(IDC_EDIT_ALPHA);
	int iRet = NetClient_SetOSDAlpha(m_iLogonID,m_iChannelNo,iOSDAlpha);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOSDAlpha (%d,%d,%d)",m_iLogonID,m_iChannelNo,iOSDAlpha);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOSDAlpha (%d,%d,%d)",m_iLogonID,m_iChannelNo,iOSDAlpha);
	}
}

BOOL CLS_OSDPage::UI_UpdateAlpha()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iAlpha;
	int iRet = NetClient_GetOSDAlpha(m_iLogonID, m_iChannelNo,&iAlpha);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_ALPHA, iAlpha);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOSDAlpha (%d,%d,%d)",m_iLogonID,m_iChannelNo,iAlpha);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOSDAlpha (%d,%d,%d)",m_iLogonID,m_iChannelNo,iAlpha);
	}
	return TRUE;
}

BOOL CLS_OSDPage::UI_UpdateColor()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iTypeNo = m_cboOSDType.GetCurSel() + 1;
	int iRet = NetClient_GetOSDTypeColor(m_iLogonID, m_iChannelNo, iTypeNo, &m_iColor);
	if (0 == iRet)
	{
		m_chkBackgroundColor.SetCheck((m_iColor & 0x02000000)?BST_CHECKED:BST_UNCHECKED);
		try
		{ 
			m_btnOSDColor.RemoveChild(0);
			m_btnOSDColor.AddChild(0);
			m_btnOSDColor.SetColor(0,RGB(GetRValue(m_iColor), GetGValue(m_iColor),GetBValue(m_iColor)));
		}
		catch (CException* e)
		{
			e->ReportError();
			e->Delete();
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOSDTypeColor(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, m_iColor);				
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOSDTypeColor(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, m_iColor);				
	}
	return TRUE;
}
void CLS_OSDPage::OnBnClickedButtonOsdset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	if (m_chkBackgroundColor.GetCheck() == BST_CHECKED)
	{
		m_iColor |= 0x02000000;
	}
	else
	{
		m_iColor &= 0x00FFFFFF;
	}
	int iTypeNo = m_cboOSDType.GetCurSel()+1;
	int iColorRet = NetClient_SetOSDTypeColor(m_iLogonID, m_iChannelNo, iTypeNo, m_iColor);
	if (0 == iColorRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOSDTypeColor(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, m_iColor);				
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOSDTypeColor(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, m_iColor);				
	}
}

void CLS_OSDPage::OnCbnSelchangeComboOsdtype()
{
	UI_UpdateColor();
	UI_UpdateFontSize();
	UI_UpdateFontDbType();
}

BOOL CLS_OSDPage::UI_UpdateFontSize()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iTypeNo = m_cboOSDType.GetCurSel()+1;
	int iSize = 0;
	int iRet = NetClient_GetOSDTypeFontSize(m_iLogonID, m_iChannelNo, iTypeNo, &iSize);
	if (0 == iRet)
	{
		if(iSize <= 5)
		{
			m_cboFontSize.SetCurSel(iSize);  
		}
		else
		{
			int iWidth = (iSize >> 16)&0xFF;
			int iHight = iSize & 0xFF;
			m_cboFontSize.SetCurSel(6); 
			SetDlgItemInt(IDC_EDIT_OSDFONWID, iWidth);
			SetDlgItemInt(IDC_EDIT_OSDFONHIGH, iHight);
		}

		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOSDTypeFontSize(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, iSize);				
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOSDTypeFontSize(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, iSize);				
	}

	return TRUE;
}

void CLS_OSDPage::OnBnClickedButtonOsdfontsize()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iTypeNo = m_cboOSDType.GetCurSel()+1;
	int iSize = m_cboFontSize.GetCurSel();
	if (6 == iSize)
	{
		int iFonWid = GetDlgItemInt(IDC_EDIT_OSDFONWID);
		int iFonHig = GetDlgItemInt(IDC_EDIT_OSDFONHIGH);
		if (iFonWid > 0xFFFF || iFonHig > 0xFFFF)
		{
			MessageBox("字符宽高超限", "提示", MB_OK);
			return;
		}
		iSize = (iFonWid << 16) | iFonHig;
	} 

	int iChlNo = m_iChannelNo;
	if (SUB_STREAM == m_iStreamNo)
	{
		int iChannelCount = 0;
		NetClient_GetChannelNum(m_iLogonID, &iChannelCount);
		iChlNo = m_iChannelNo + iChannelCount;
	}

	int iRet = NetClient_SetOSDTypeFontSize(m_iLogonID, iChlNo, iTypeNo, iSize);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOSDTypeFontSize(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, iSize);				
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOSDTypeFontSize(%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iTypeNo, iSize);				
	}
}

void CLS_OSDPage::DrawTextOnVideo( int _iStore )
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	CString strDrawText;
	m_edtDrawText.GetWindowText(strDrawText);
	int iPosX = GetDlgItemInt(IDC_EDIT_DRAWTEXT_XPOS);
	int iPosY = GetDlgItemInt(IDC_EDIT_DRAWTEXT_YPOS);
	if (iPosY < 0 || iPosX < 0)
	{
		MessageBox(GetTextEx(IDS_POS_ERROR));
		return;
	}

#define MAX_TEXT_LEN 512
	char cMoreText[MAX_TEXT_LEN] = {0};
	char cTemp[MAX_TEXT_LEN] = {0};		
	int iCount = 0;
	for(int i = 0;i < m_edtDrawText.GetLineCount(); ++i)
	{
		int len = m_edtDrawText.GetLine(i,cTemp,MAX_TEXT_LEN);
		cTemp[len] = '\0';//要手动添加结束符
		memcpy_s(cMoreText+iCount,len+1,cTemp,len);		
		iCount += len;
		cMoreText[iCount++] = '\n';
	}
	cMoreText[--iCount] = '\0';

	int iRet = NetClient_DrawTextOnVideo(m_iLogonID, m_iChannelNo, iPosX, iPosY, cMoreText, _iStore, m_iStreamNo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DrawTextOnVideo(%d,%d,%d,%d,%s,%d,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY,cMoreText, _iStore,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DrawTextOnVideo(%d,%d,%d,%d,%s,%d,%d)",m_iLogonID, m_iChannelNo, iPosX, iPosY,cMoreText, _iStore,m_iStreamNo);
	}
}

void CLS_OSDPage::OnCbnSelchangeComboOsdfontsize()
{
	// TODO: Add your control notification handler code here
	if (FONTSIZE_DEFINE != m_cboFontSize.GetCurSel())
	{
		m_edtFontWid.EnableWindow(FALSE);
		m_edtFontHigh.EnableWindow(FALSE);
	} 
	else
	{
		m_edtFontWid.EnableWindow(TRUE);
		m_edtFontHigh.EnableWindow(TRUE);
		//UI_UpdateFontSize();
	}

}

void CLS_OSDPage::OnCbnSelchangeComboDevcomname()
{
	// TODO: Add your control notification handler code here
	int iBytesReturned = 0;
	TDevCommonName tDevComName = {0};
	tDevComName.m_iSize = sizeof(TDevCommonName);
	int iIndex = m_cboDevComNameType.GetCurSel();
	if (iIndex < 0 || iIndex > 2)
	{
		return;
	}
	tDevComName.m_iChannelType = iIndex;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DEV_COMMONNAME, m_iChannelNo, &tDevComName, sizeof(tDevComName), &iBytesReturned);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_DEVCOMNAME, (LPCTSTR)(tDevComName.m_cChanneleName));
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(%d,%d,%s,%d)",m_iLogonID, m_iChannelNo, tDevComName.m_cChanneleName, tDevComName.m_iChannelType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(%d,%d,%s,%d)",m_iLogonID,m_iChannelNo, tDevComName.m_cChanneleName, tDevComName.m_iChannelType);
	}
}

void CLS_OSDPage::UI_UpdateFontDbType()
{
	int iRet = -1;
	int iValueMatrix = 0;
	iRet = NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_OSD_DOT_MATRIX,m_iChannelNo, &iValueMatrix);

	int iValueVector = 0;
	iRet = NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_OSD_VECTOR,m_iChannelNo, &iValueVector);

	if (iValueMatrix ==1 && iValueVector == 0)
	{
		m_iFontDbLattice = 1;
	}
	else if (iValueMatrix == 0 && iValueVector == 1)
	{
		m_iFontDbLattice = 0;
	}
	else
	{
		m_iFontDbLattice = -1;
	}

	UpdateData(FALSE);
}

void CLS_OSDPage::OnBnClickedRadioOsdFontDbTypeVector()
{
	int iFontDb = m_iFontDbLattice;
	UpdateData();
	if (iFontDb == m_iFontDbLattice)
	{
		return;
	}
	int iCmdNew = 0;
	int iCmdOld = 0;
	if(m_iFontDbLattice == 0)//
	{
		iCmdNew = CI_COMMON_ID_OSD_VECTOR;
		iCmdOld = CI_COMMON_ID_OSD_DOT_MATRIX;
	}
	else
	{
		iCmdOld = CI_COMMON_ID_OSD_VECTOR;
		iCmdNew = CI_COMMON_ID_OSD_DOT_MATRIX;
	}

	bool blError = false;
	if(NetClient_SetCommonEnable(m_iLogonID, iCmdOld,m_iChannelNo,0) != 0)
	{
		blError = true;
	}

	if(NetClient_SetCommonEnable(m_iLogonID, iCmdNew,m_iChannelNo,1) != 0)
	{
		blError = true;
	}

	if (!blError)
	{
		int iRet = MessageBox(GetTextEx(IDS_CONFIG_LAN_MESSAGETEXT), GetTextEx(IDS_CONFIG_PROMPT),MB_OKCANCEL);
		if (IDOK == iRet)
		{
			iRet = NetClient_Reboot(m_iLogonID);
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_Reboot(%d)",m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_Reboot(%d)",m_iLogonID);
			}
		}
	}
}

