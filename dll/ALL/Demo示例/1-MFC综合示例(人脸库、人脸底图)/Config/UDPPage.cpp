// UDPPage.cpp : implementation file
//

#include "stdafx.h"
#include "UDPPage.h"


// CLS_UDPPage dialog

IMPLEMENT_DYNAMIC(CLS_UDPPage, CDialog)

CLS_UDPPage::CLS_UDPPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_UDPPage::IDD, pParent)
{

}

CLS_UDPPage::~CLS_UDPPage()
{
}

void CLS_UDPPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NVSIP, m_edtNVSIp);
	DDX_Control(pDX, IDC_EDIT_NVSPORT, m_edtNVSPort);
	DDX_Control(pDX, IDC_EDIT_CHANNELNO, m_edtChannelNo);
	DDX_Control(pDX, IDC_EDIT_CHANNELNUM, m_edtChannelNum);
	DDX_Control(pDX, IDC_EDIT_STREAMTYPE, m_edtStreamType);
	DDX_Control(pDX, IDC_EDIT_UDPPORT, m_edtUDPPort);
	DDX_Control(pDX, IDC_BUTTON_GETPORT, m_btnUDP);
}


BEGIN_MESSAGE_MAP(CLS_UDPPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_GETPORT, &CLS_UDPPage::OnBnClickedButtonGetport)
END_MESSAGE_MAP()


// CLS_UDPPage message handlers
BOOL CLS_UDPPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_edtNVSIp.SetLimitText(15);
	m_edtNVSPort.SetLimitText(5);
	m_edtChannelNo.SetLimitText(5);
	m_edtChannelNum.SetLimitText(5);
	m_edtStreamType.SetLimitText(5);
	m_edtUDPPort.SetLimitText(5);

	SetDlgItemText(IDC_EDIT_NVSIP,"192.168.1.251");
	SetDlgItemText(IDC_EDIT_NVSPORT,"3000");
	SetDlgItemText(IDC_EDIT_CHANNELNO,"0");
	SetDlgItemText(IDC_EDIT_CHANNELNUM,"1");
	SetDlgItemText(IDC_EDIT_STREAMTYPE,"0");


	
	UI_UpdateDialog();

	return TRUE;
}

void CLS_UDPPage::OnChannelChanged(int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;

}

void CLS_UDPPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_UDPPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_UDPPORT, IDS_CONFIG_UDP_PORT);
	SetDlgItemTextEx(IDC_STATIC_NVSIP, IDS_CONFIG_UDP_NVSIP);
	SetDlgItemTextEx(IDC_STATIC_CHANNELNO, IDS_CONFIG_UDP_CHANNELNO);
	SetDlgItemTextEx(IDC_STATIC_CHANNELNUM, IDS_CONFIG_UDP_CHANNELNUM);
	SetDlgItemTextEx(IDC_STATIC_STREAMTYPE, IDS_CONFIG_UDP_STREAMTYPE);
	SetDlgItemTextEx(IDC_STATIC_UDPPORT1, IDS_CONFIG_UDP_PORT);
	SetDlgItemTextEx(IDC_BUTTON_GETPORT, IDS_CONFIG_UDP_GETPORT);
}

void CLS_UDPPage::OnBnClickedButtonGetport()
{
	char cNVSIP[16] = {0};
	GetDlgItemText(IDC_EDIT_NVSIP, cNVSIP, 16);
	//CString cNVSIP;
	//m_edtNVSIp.GetWindowText(cNVSIP);
	int iNVSPort = GetDlgItemInt(IDC_EDIT_NVSPORT);
	int iChannelNo = GetDlgItemInt(IDC_EDIT_CHANNELNO);
	int iChannelNum = GetDlgItemInt(IDC_EDIT_CHANNELNUM);
	int iStreamType = GetDlgItemInt(IDC_EDIT_STREAMTYPE);
	unsigned long uIP = ntohl(inet_addr(cNVSIP));
	int iRealChannel = iChannelNo + iStreamType*iChannelNum;
	int iUDPPort = iNVSPort+(iRealChannel<<12)+(uIP&0x00000FFF);
	SetDlgItemInt(IDC_EDIT_UDPPORT, iUDPPort);
}
