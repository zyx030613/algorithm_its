// AppendOSDPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "AppendOSDPage.h"


// CLS_AppendOSDPage dialog

IMPLEMENT_DYNAMIC(CLS_AppendOSDPage, CDialog)

CLS_AppendOSDPage::CLS_AppendOSDPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AppendOSDPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNO = 0;
	m_iColor = 0;
}

CLS_AppendOSDPage::~CLS_AppendOSDPage()
{
}

void CLS_AppendOSDPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OSD_AREA, m_cboOSDArea);
	DDX_Control(pDX, IDC_EDIT_Diaphaneity, m_edtDiaphaneity);
	DDX_Control(pDX, IDC_COMBO_FONT_SIZE, m_cboFontSize);
	DDX_Control(pDX, IDC_EDIT_X_COR, m_edt_X_Value);
	DDX_Control(pDX, IDC_EDIT_Y_COR, m_edt_Y_Value);
	DDX_Control(pDX, IDC_EDIT_OSD_CONTENT, m_edtOSDContent);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_btnColor);
	DDX_Control(pDX, IDC_CHECK_BACKCOLOR_SHOW, m_chkBackColorShow);
	DDX_Control(pDX, IDC_CHECK_BACK_COLOR_ADD, m_chkBackColorAdd);
}


BEGIN_MESSAGE_MAP(CLS_AppendOSDPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_COLOR, &CLS_AppendOSDPage::OnBnClickedButtonSelectColor)
	ON_BN_CLICKED(IDC_BUTTON_APPEND_OSD_SET, &CLS_AppendOSDPage::OnBnClickedButtonAppendOsdSet)
	ON_BN_CLICKED(IDC_CHECK_BACKCOLOR_SHOW, &CLS_AppendOSDPage::OnBnClickedCheckBackcolorShow)
	ON_BN_CLICKED(IDC_CHECK_BACK_COLOR_ADD, &CLS_AppendOSDPage::OnBnClickedCheckBackColorAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_OSD_AREA, &CLS_AppendOSDPage::OnCbnSelchangeComboOsdArea)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_AppendOSDPage message handlers

BOOL CLS_AppendOSDPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialog();
	m_btnColor.SetChildNum(0);
	m_btnColor.SetColor(0,RGB(0,0,0));
	m_cboOSDArea.SetCurSel(0);
	m_cboFontSize.SetCurSel(0);
	m_edtDiaphaneity.SetLimitText(16);
	m_edt_X_Value.SetLimitText(16);
	m_edt_Y_Value.SetLimitText(16);
	m_edtOSDContent.SetLimitText(256);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_AppendOSDPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo =  _iChannelNo;
	}

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO = _iStreamNo;
	}
}

void CLS_AppendOSDPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_AppendOSDPage::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	TAppendOSD strTAppendOSD = {0};
	strTAppendOSD.iSize = sizeof(TAppendOSD);
	int iBytesReturned = 0;
	strTAppendOSD.iLayNo = m_cboOSDArea.GetCurSel() + 1;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_APPEND_OSD, m_iChannelNo, &strTAppendOSD, sizeof(TAppendOSD), &iBytesReturned);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_AppendOSDPage::NetClient_GetDevConfig] Get fail,error = %d", GetLastError());
	}
	else
	{
		strTAppendOSD.iPosX = (strTAppendOSD.iPosX >= 0) ? strTAppendOSD.iPosX : 0;
		strTAppendOSD.iPosY = (strTAppendOSD.iPosY >= 0) ? strTAppendOSD.iPosY : 0;

		SetDlgItemInt(IDC_EDIT_Diaphaneity, strTAppendOSD.iDiaphaneity);
		m_cboFontSize.SetCurSel(strTAppendOSD.iFontSize - 1);
		SetDlgItemInt(IDC_EDIT_X_COR, strTAppendOSD.iPosX);
		SetDlgItemInt(IDC_EDIT_Y_COR, strTAppendOSD.iPosY);
		CString strMoreText(strTAppendOSD.pcText);
		strMoreText.Replace(_T("\n"),_T("\r\n"));	
		m_edtOSDContent.SetWindowText(strMoreText);
		m_btnColor.RemoveChild(0);
		m_btnColor.AddChild(0);
		m_btnColor.SetColor(0,RGB(GetRValue(strTAppendOSD.iColor), GetGValue(strTAppendOSD.iColor),GetBValue(strTAppendOSD.iColor)));
		m_iColor = strTAppendOSD.iColor;
	}
}

void CLS_AppendOSDPage::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_APPEND_OSD:
		UpdatePageUI();
		break;
	default:
		break;
	}
}

void CLS_AppendOSDPage::UI_UpdateDialog()
{
	//InsertString(m_cboEncryptType,0,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_TYPE_NONE);
	//InsertString(m_cboEncryptType,1,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_TYPE_AES);
	m_cboOSDArea.ResetContent();
	m_cboOSDArea.AddString(_T("Area1"));
	m_cboOSDArea.AddString(_T("Area2"));
	m_cboOSDArea.AddString(_T("Area3"));
	m_cboOSDArea.AddString(_T("Area4"));
	m_cboOSDArea.AddString(_T("Area5"));
	//目前只支持五块
//	m_cboOSDArea.AddString(_T("Area6"));
//	m_cboOSDArea.AddString(_T("Area7"));

	m_cboFontSize.ResetContent();
	m_cboFontSize.AddString(_T("1"));
	m_cboFontSize.AddString(_T("2"));
	m_cboFontSize.AddString(_T("3"));
	m_cboFontSize.AddString(_T("4"));
	m_cboFontSize.AddString(_T("5"));
	
	
	SetDlgItemTextEx(IDC_STATIC_OSD_AREA,IDS_CFG_OSD_CHARSADD);
	SetDlgItemTextEx(IDC_STATIC_DIAPHANEITY, IDS_CONFIG_OSD_DIAPHANEITY);
	SetDlgItemTextEx(IDC_STATIC_FONT_SIZE, IDS_CONFIG_OSD_FONTSIZE);
	SetDlgItemTextEx(IDC_STATIC_X_COR, IDS_CONFIG_ATM_OSDX);
	SetDlgItemTextEx(IDC_STATIC_Y_COR, IDS_CONFIG_COORDS_Y);
	SetDlgItemTextEx(IDC_CHECK_BACKCOLOR_SHOW, IDS_CONFIG_OSD_BKGROUNDDISPLAY);
	SetDlgItemTextEx(IDC_CHECK_BACK_COLOR_ADD, IDS_CFG_OSD_BACKADD);
	SetDlgItemTextEx(IDC_BUTTON_SELECT_COLOR, IDS_CONFIG_OSD_CHOOSE_COLOR);
	SetDlgItemTextEx(IDC_BUTTON_APPEND_OSD_SET, IDS_CFG_3G_NORMAL_SET);

}

void CLS_AppendOSDPage::OnBnClickedButtonSelectColor()
{
	// TODO: Add your control notification handler code here
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
		try
		{
			m_btnColor.RemoveChild(0);
			m_btnColor.AddChild(0);
			m_btnColor.SetColor(0,RGB(GetRValue(m_iColor), GetGValue(m_iColor),GetBValue(m_iColor)));
		}
		catch (CException* e)
		{
			e->ReportError();
			e->Delete();
		}
	}
}

void CLS_AppendOSDPage::OnBnClickedButtonAppendOsdSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	if (m_chkBackColorShow.GetCheck() == BST_CHECKED)
	{
		m_iColor |= 0x02000000;
		m_chkBackColorAdd.SetCheck(BST_UNCHECKED);
	}
	else if (m_chkBackColorAdd.GetCheck() == BST_CHECKED)
	{
		m_iColor |= 0x01000000;
		m_chkBackColorShow.SetCheck(BST_UNCHECKED);
	}
	else
	{
		m_iColor &= 0x00FFFFFF;
	}

	TAppendOSD strAppendOSD= {0};
	strAppendOSD.iSize = sizeof(TAppendOSD);
	strAppendOSD.iLayNo = m_cboOSDArea.GetCurSel() + 1;
	strAppendOSD.iColor = m_iColor;
	strAppendOSD.iDiaphaneity = GetDlgItemInt(IDC_EDIT_Diaphaneity);
	strAppendOSD.iFontSize = m_cboFontSize.GetCurSel() + 1;
	
	CString strDrawText;
	m_edtOSDContent.GetWindowText(strDrawText);
	int iPosX = GetDlgItemInt(IDC_EDIT_X_COR);
	int iPosY = GetDlgItemInt(IDC_EDIT_Y_COR);

	if (iPosY < 0 || iPosX < 0)
	{
		MessageBox(GetTextEx(IDS_POS_ERROR));
		return;
	}

	strAppendOSD.iPosX = iPosX;
	strAppendOSD.iPosY = iPosY;

#define MAX_TEXT_LEN 512
	char cMoreText[MAX_TEXT_LEN] = {0};
	char cTemp[MAX_TEXT_LEN] = {0};		
	int iCount = 0;
	for(int i = 0;i < m_edtOSDContent.GetLineCount(); ++i)
	{
		int len = m_edtOSDContent.GetLine(i,cTemp,MAX_TEXT_LEN);
		cTemp[len] = '\0';//要手动添加结束符
		memcpy_s(cMoreText+iCount,len+1,cTemp,len);		
		iCount += len;
		cMoreText[iCount++] = '\n';
	}
	cMoreText[--iCount] = '\0';

	memcpy(strAppendOSD.pcText, cMoreText, MAX_OSD_LENGTH);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_APPEND_OSD, m_iChannelNo, &strAppendOSD, sizeof(TAppendOSD));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_AppendOSDPage::OnBnClickedButtonAppendOsdSet] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[CLS_AppendOSDPage::OnBnClickedButtonAppendOsdSet] set success!");
	}
}

void CLS_AppendOSDPage::OnBnClickedCheckBackcolorShow()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chkBackColorShow.GetCheck())
	{
		m_chkBackColorAdd.SetCheck(BST_UNCHECKED);
	}
}

void CLS_AppendOSDPage::OnBnClickedCheckBackColorAdd()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chkBackColorAdd.GetCheck())
	{
		m_chkBackColorShow.SetCheck(BST_UNCHECKED);
	}
}

void CLS_AppendOSDPage::OnCbnSelchangeComboOsdArea()
{
	// TODO: Add your control notification handler code here
	UpdatePageUI();
}

void CLS_AppendOSDPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	UpdatePageUI();
}
