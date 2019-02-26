// 3GDVRPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "3GDVRPage.h"


// CLS_3GDVRPage dialog

IMPLEMENT_DYNAMIC(CLS_3GDVRPage, CDialog)

CLS_3GDVRPage::CLS_3GDVRPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_3GDVRPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_3GDVRPage::~CLS_3GDVRPage()
{
}

void CLS_3GDVRPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_3GDVR_ONTIME, m_edtOnTime);
	DDX_Control(pDX, IDC_EDIT_3GDVR_OFFTIME, m_edtOffTime);
	DDX_Control(pDX, IDC_EDIT_3GDVR_SIMNUM, m_edtSimNum);
	DDX_Control(pDX, IDC_EDIT_3GDVR_FINALFILTER, m_edtFinalFilter);
	DDX_Control(pDX, IDC_COMBO_3GDVR_FTPUPLOADMODE, m_cboFtpUploadMode);
	DDX_Control(pDX, IDC_CHECK_3GDVR_OVERLAY, m_chkGpsOverlayEnable);
	DDX_Control(pDX, IDC_CHECK_3GDVR_GSV, m_chkGpsFilterGSV);
	DDX_Control(pDX, IDC_CHECK_3GDVR_GSA, m_chkGpsFilterGSA);
	DDX_Control(pDX, IDC_CHECK_3GDVR_GLL, m_chkGpsFilterGLL);
	DDX_Control(pDX, IDC_CHECK_3GDVR_VTG, m_chkGpsFilterVTG);
	DDX_Control(pDX, IDC_CHECK_3GDVR_RMC, m_chkGpsFilterRMC);
	DDX_Control(pDX, IDC_CHECK_3GDVR_GGA, m_chkGpsFilterGGA);
	DDX_Control(pDX, IDC_CHECK_3GDVR_NONE, m_chkGpsFilterNone);
	DDX_Control(pDX, IDC_CHECK_3GDVR_ALL, m_chkGpsFilterAll);
}


BEGIN_MESSAGE_MAP(CLS_3GDVRPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_3GDVR_TIMESET, &CLS_3GDVRPage::OnBnClickedButton3GDVRTimeSet)
	ON_BN_CLICKED(IDC_BUTTON_3GDVR_GPSOVERLAY, &CLS_3GDVRPage::OnBnClickedButton3GDVRGpsOverlay)
	ON_BN_CLICKED(IDC_BUTTON_3GDVR_GPSFILTER, &CLS_3GDVRPage::OnBnClickedButton3GDVRGpsFilter)
	ON_BN_CLICKED(IDC_BUTTON_3GDVR_FTPUPLOADMODE, &CLS_3GDVRPage::OnBnClickedButton3GDVRFtpUploadMode)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_GSV, &CLS_3GDVRPage::OnBnClickedCheck3GDVRGsv)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_GSA, &CLS_3GDVRPage::OnBnClickedCheck3GDVRGsa)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_GLL, &CLS_3GDVRPage::OnBnClickedCheck3GDVRGll)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_VTG, &CLS_3GDVRPage::OnBnClickedCheck3GDVRVtg)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_RMC, &CLS_3GDVRPage::OnBnClickedCheck3GDVRRmc)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_GGA, &CLS_3GDVRPage::OnBnClickedCheck3GDVRGga)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_NONE, &CLS_3GDVRPage::OnBnClickedCheck3GDVRNone)
	ON_BN_CLICKED(IDC_CHECK_3GDVR_ALL, &CLS_3GDVRPage::OnBnClickedCheck3GDVRAll)
END_MESSAGE_MAP()

void CLS_3GDVRPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

	UI_Update3GDVRInfo();
}

void CLS_3GDVRPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

// CLS_3GDVRPage message handlers

void CLS_3GDVRPage::OnBnClickedButton3GDVRTimeSet()
{
	// TODO: Add your control notification handler code here
	TDVR3GInfo dvr3G = {0};
	dvr3G.iPowerDelayOnTime = GetDlgItemInt(IDC_EDIT_3GDVR_ONTIME);
	dvr3G.iPowerDelayOffTime = GetDlgItemInt(IDC_EDIT_3GDVR_OFFTIME);
	if (dvr3G.iPowerDelayOnTime < 0 || dvr3G.iPowerDelayOnTime > 999 || dvr3G.iPowerDelayOffTime < 0 || dvr3G.iPowerDelayOnTime > 999)
	{
		AddLog(LOG_TYPE_FAIL,"","Para error!");
		return;
	}
	int iRet = NetClient_Set3GConfig(m_iLogonID, DVR3G_CMD_SET_POWERDELAY, m_iChannelNo, &dvr3G, sizeof(dvr3G));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","Set3GConfig -DVR3G_CMD_SET_POWERDELAY- Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","Set3GDialog Success!LogonID(%d)",m_iLogonID);
	}
	
}

void CLS_3GDVRPage::OnBnClickedButton3GDVRGpsOverlay()
{
	// TODO: Add your control notification handler code here
	TDVR3GInfo dvr3G = {0};
	dvr3G.iGpsOverlay[m_iChannelNo] = m_chkGpsOverlayEnable.GetCheck();
	int iRet = NetClient_Set3GConfig(m_iLogonID, DVR3G_CMD_SET_GPSOVERLAY, m_iChannelNo, &dvr3G, sizeof(dvr3G));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","Set3GConfig -DVR3G_CMD_SET_GPSOVERLAY- Error!LogonID(%d), ChannelNo(%d),Error(0x%08x)",m_iLogonID,m_iChannelNo,::GetLastError());
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","Set3GDialog Success!LogonID(%d)",m_iLogonID);
	}
}

void CLS_3GDVRPage::OnBnClickedButton3GDVRGpsFilter()
{
	// TODO: Add your control notification handler code here
	TDVR3GInfo dvr3G = {0};
	dvr3G.iGpsFilter = GetDlgItemInt(IDC_EDIT_3GDVR_FINALFILTER);
	int iRet = NetClient_Set3GConfig(m_iLogonID, DVR3G_CMD_SET_GPSFILTER, m_iChannelNo, &dvr3G, sizeof(dvr3G));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","Set3GConfig -DVR3G_CMD_SET_GPSFILTER- Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","Set3GDialog Success!LogonID(%d)",m_iLogonID);
	}
}

void CLS_3GDVRPage::OnBnClickedButton3GDVRFtpUploadMode()
{
	// TODO: Add your control notification handler code here
	int iMode = m_cboFtpUploadMode.GetCurSel();
	TDVR3GInfoEx dix = {0};
	dix.iFtpUploadMode = iMode;
	int iRet = NetClient_Set3GConfig(m_iLogonID, DVR3G_CMD_SET_FTPUPLOAD_MODE, -1, &dix, sizeof(dix));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","Set3GConfig -DVR3G_CMD_SET_FTPUPLOAD_MODE- Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","Set3GDialog Success!LogonID(%d)",m_iLogonID);
	}
}

BOOL CLS_3GDVRPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtOnTime.SetLimitText(10);
	m_edtOffTime.SetLimitText(10);
	m_edtSimNum.SetLimitText(30);
	m_edtFinalFilter.SetLimitText(10);

	m_cboFtpUploadMode.AddString(_T("0-Auto"));
	m_cboFtpUploadMode.AddString(_T("1-Manual"));

	m_edtOnTime.SetDlgItemInt(IDC_EDIT_3GDVR_ONTIME, 0);
	m_edtOffTime.SetDlgItemInt(IDC_EDIT_3GDVR_OFFTIME, 0);
	m_cboFtpUploadMode.SetCurSel(0);

	m_edtFinalFilter.SetWindowText(_T("0"));
	m_edtOnTime.SetWindowText(_T("0"));
	m_edtOffTime.SetWindowText(_T("0"));

	UI_UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_3GDVRPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_3G_DVR_DELAY, IDS_CFG_3G_DVR_DELAY);
	SetDlgItemTextEx(IDC_STATIC_3GDVR_ONTIME, IDS_CFG_3G_DVR_ONTIME);
	SetDlgItemTextEx(IDC_STATIC_3G_OFFTIME, IDS_CFG_3G_DVR_OFFTIME);
	SetDlgItemTextEx(IDC_BUTTON_3GDVR_TIMESET, IDS_CFG_3G_DVR_DELAYSET);
	SetDlgItemTextEx(IDC_STATIC_3GDVR_SIMNUM, IDS_CFG_3G_DVR_SIMNUM);
	SetDlgItemTextEx(IDC_STATIC_3G_DVR_GPS, IDS_CFG_3G_DVR_GPSOVERLAY);
	SetDlgItemTextEx(IDC_STATIC_3GDVR_CHANNEL, IDS_CFG_3G_DVR_CHANNEL);
	SetDlgItemTextEx(IDC_CHECK_3GDVR_OVERLAY, IDS_CFG_3G_DVR_OVERLAYENABLE);
	SetDlgItemTextEx(IDC_BUTTON_3GDVR_GPSOVERLAY, IDS_CFG_3G_DVR_GPSSET);
	SetDlgItemTextEx(IDC_STATIC_3G_DVR_GPSFILTER, IDS_CFG_3G_DVR_GPSFILTER);
	SetDlgItemTextEx(IDC_CHECK_3GDVR_NONE, IDS_CFG_3G_DVR_FILTER_NONE);
	SetDlgItemTextEx(IDC_CHECK_3GDVR_ALL, IDS_CFG_3G_DVR_FILTER_ALL);
	SetDlgItemTextEx(IDC_STATIC_3GDVR_FINALFILTER, IDS_CFG_3G_DVR_FINALFILTER);
	SetDlgItemTextEx(IDC_BUTTON_3GDVR_GPSFILTER, IDS_CFG_3G_DVR_FILTERSET);
	SetDlgItemTextEx(IDC_STATIC_3GDVR_FTPUPLOADMODE, IDS_CFG_3G_DVR_FTPUPLOADMODE);
	SetDlgItemTextEx(IDC_BUTTON_3GDVR_FTPUPLOADMODE, IDS_CFG_3G_DVR_UPLOADSET);
}

void CLS_3GDVRPage::UI_Update3GDVRInfo()
{
	TDVR3GInfo dvr3G = {0};
	TDVR3GInfoEx dix = {0};
	if (NetClient_Get3GConfig(m_iLogonID, DVR3G_CMD_GET_POWERDELAY, m_iChannelNo, &dvr3G, sizeof(dvr3G)) == 0)
	{
		SetDlgItemInt(IDC_EDIT_3GDVR_ONTIME, dvr3G.iPowerDelayOnTime);
		SetDlgItemInt(IDC_EDIT_3GDVR_OFFTIME, dvr3G.iPowerDelayOffTime);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get3GConfig -DVR3G_CMD_GET_POWERDELAY- Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}

	if (NetClient_Get3GConfig(m_iLogonID, DVR3G_CMD_GET_SIMNUM, m_iChannelNo, &dvr3G, sizeof(dvr3G)) == 0)
	{
		SetDlgItemText(IDC_EDIT_3GDVR_SIMNUM, dvr3G.cSimNum);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get3GConfig -DVR3G_CMD_GET_SIMNUM- Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}

	if( NetClient_Get3GConfig(m_iLogonID, DVR3G_CMD_GET_GPSOVERLAY, m_iChannelNo, &dvr3G, sizeof(dvr3G)) == 0)
	{
		m_chkGpsOverlayEnable.SetCheck(dvr3G.iGpsOverlay[m_iChannelNo]);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get3GConfig -DVR3G_CMD_GET_GPSOVERLAY- Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}

	if (NetClient_Get3GConfig(m_iLogonID, DVR3G_CMD_GET_GPSFILTER, m_iChannelNo, &dvr3G, sizeof(dvr3G)) == 0)
	{
		SetDlgItemInt(IDC_EDIT_3GDVR_FINALFILTER, dvr3G.iGpsFilter);
		m_chkGpsFilterGSV.SetCheck((dvr3G.iGpsFilter>>5)&1);
		m_chkGpsFilterGSA.SetCheck((dvr3G.iGpsFilter>>4)&1);
		m_chkGpsFilterGLL.SetCheck((dvr3G.iGpsFilter>>3)&1);
		m_chkGpsFilterVTG.SetCheck((dvr3G.iGpsFilter>>2)&1);
		m_chkGpsFilterRMC.SetCheck((dvr3G.iGpsFilter>>1)&1);
		m_chkGpsFilterGGA.SetCheck((dvr3G.iGpsFilter)&1);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get3GConfig -DVR3G_CMD_GET_GPSFILTER- Error!LogonID(%d),Error(0x%08x)",m_iLogonID,::GetLastError());
	}

	if (NetClient_Get3GConfig(m_iLogonID,DVR3G_CMD_GET_FTPUPLOAD_MODE, m_iChannelNo, &dix, sizeof(dix)) ==0)
	{
		m_cboFtpUploadMode.SetCurSel(dix.iFtpUploadMode);
	} 
	else
		AddLog(LOG_TYPE_FAIL,"","Get3GConfig -DVR3G_CMD_GET_FTPUPLOAD_MODE- Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRGsv()
{
	// TODO: Add your control notification handler code here
	SetFiterText();
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRGsa()
{
	// TODO: Add your control notification handler code here
	SetFiterText();
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRGll()
{
	// TODO: Add your control notification handler code here
	SetFiterText();
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRVtg()
{
	// TODO: Add your control notification handler code here
	SetFiterText();
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRRmc()
{
	// TODO: Add your control notification handler code here
	SetFiterText();
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRGga()
{
	// TODO: Add your control notification handler code here
	SetFiterText();
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRNone()
{
	// TODO: Add your control notification handler code here
	if(m_chkGpsFilterNone.GetCheck() == BST_CHECKED)
	{
		m_chkGpsFilterGSV.SetCheck(BST_UNCHECKED);
		m_chkGpsFilterGSA.SetCheck(BST_UNCHECKED);
		m_chkGpsFilterGLL.SetCheck(BST_UNCHECKED);
		m_chkGpsFilterVTG.SetCheck(BST_UNCHECKED);
		m_chkGpsFilterRMC.SetCheck(BST_UNCHECKED);
		m_chkGpsFilterGGA.SetCheck(BST_UNCHECKED);
		m_chkGpsFilterAll.SetCheck(BST_UNCHECKED);
	}
	SetFiterText();
}

void CLS_3GDVRPage::OnBnClickedCheck3GDVRAll()
{
	// TODO: Add your control notification handler code here
	int iCheck =(m_chkGpsFilterAll.GetCheck() == BST_CHECKED )?BST_CHECKED:BST_UNCHECKED;
	m_chkGpsFilterGSV.SetCheck(iCheck);
	m_chkGpsFilterGSA.SetCheck(iCheck);
	m_chkGpsFilterGLL.SetCheck(iCheck);
	m_chkGpsFilterVTG.SetCheck(iCheck);
	m_chkGpsFilterRMC.SetCheck(iCheck);
	m_chkGpsFilterGGA.SetCheck(iCheck);

	SetFiterText();
}

void CLS_3GDVRPage::SetFiterText()
{
	int iFiter = 0;
	iFiter |= m_chkGpsFilterGSV.GetCheck()<<5;
	iFiter |= m_chkGpsFilterGSA.GetCheck()<<4;
	iFiter |= m_chkGpsFilterGLL.GetCheck()<<3;
	iFiter |= m_chkGpsFilterVTG.GetCheck()<<2;
	iFiter |= m_chkGpsFilterRMC.GetCheck()<<1;
	iFiter |= m_chkGpsFilterGGA.GetCheck();
	m_chkGpsFilterNone.SetCheck(0);
	m_chkGpsFilterAll.SetCheck(0);
	SetDlgItemInt(IDC_EDIT_3GDVR_FINALFILTER, iFiter);
}