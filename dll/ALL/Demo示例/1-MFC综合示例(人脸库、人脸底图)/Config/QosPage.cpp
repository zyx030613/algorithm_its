// NTPPage.cpp : implementation file
//

#include "stdafx.h"
#include "QosPage.h"

#define  MIN_QOS_DSCP_VALUE		0
#define  MAX_QOS_DSCP_VALUE		63			


IMPLEMENT_DYNAMIC(CLS_QosPage, CDialog)

CLS_QosPage::CLS_QosPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_QosPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_QosPage::~CLS_QosPage()
{
}

void CLS_QosPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_QOS_TYPE, m_cboQosType);
	DDX_Control(pDX, IDC_EDT_QOS_DSCP, m_edtDSCPValue);
}


BEGIN_MESSAGE_MAP(CLS_QosPage, CDialog)
	ON_BN_CLICKED(IDC_BTN_QOS_SET, &CLS_QosPage::OnBnClickedBtnQosSet)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_CBO_QOS_TYPE, &CLS_QosPage::OnCbnSelchangeCboQosType)
END_MESSAGE_MAP()


BOOL CLS_QosPage::OnInitDialog()		
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	m_edtDSCPValue.SetLimitText(2);
	return TRUE;
}


void CLS_QosPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	
	UI_UpdateQosInfo();
}

void CLS_QosPage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo >= 0) ? _iChannelNo : 0;

	UI_UpdateQosInfo();
}

void CLS_QosPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_QosPage::UI_UpdateDialog()
{
	m_cboQosType.ResetContent();
	m_cboQosType.SetItemData(m_cboQosType.AddString(GetTextEx(IDS_CONFIG_LAN_WOKEMODE_LANSET_RESERVED)), 0);
	m_cboQosType.SetItemData(m_cboQosType.AddString(GetTextEx(IDS_CFG_LAN_QOSTYPE_CODESTRM)), 1);
	m_cboQosType.SetItemData(m_cboQosType.AddString(GetTextEx(IDS_CFG_LAN_QOSTYPE_CMD)), 2);
	m_cboQosType.SetCurSel(0);

	SetDlgItemTextEx(IDC_STC_QOS_TYPE, IDS_CFG_LAN_QOSTYPE);
	SetDlgItemTextEx(IDC_BTN_QOS_SET, IDS_SET);
}

void CLS_QosPage::UI_UpdateQosInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_QosPage::UI_UpdateQosInfo] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	QosValue tQosValue = {0};
	tQosValue.iSize = sizeof(QosValue);
	tQosValue.iType = (int)m_cboQosType.GetItemData(m_cboQosType.GetCurSel());
	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_QOS_VALUE, m_iChannelNo, &tQosValue, sizeof(QosValue), &iReturnByte);

	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_GetDevConfig:QOS_VALUE] Get fail,logid(%d), error(%d)",m_iLogonID, GetLastError());
	}
	else
	{
		//m_cboQosType.SetCurSel(GetCboSel(&m_cboQosType, tQosValue.iType));
		m_edtDSCPValue.SetWindowText(IntToCString(tQosValue.iDSCPValue));
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_GetDevConfig:QOS_VALUE] Get success!");
	}

}

void CLS_QosPage::OnBnClickedBtnQosSet()
{
	int iValue = GetDlgItemInt(IDC_EDT_QOS_DSCP);
	if (iValue > MAX_QOS_DSCP_VALUE || iValue < MIN_QOS_DSCP_VALUE)
	{
		MessageBox(GetTextEx(IDS_CFG_LAN_SETOVER));
		return;
	}

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_QosPage::OnBnClickedBtnQosSet] Invalid logon id(%d)", m_iLogonID);
		return;
	}

	QosValue tQosValue = {0};
	tQosValue.iSize = sizeof(QosValue);
	tQosValue.iType = (int)m_cboQosType.GetItemData(m_cboQosType.GetCurSel());
	tQosValue.iDSCPValue = GetDlgItemInt(IDC_EDT_QOS_DSCP);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_QOS_VALUE, m_iChannelNo, &tQosValue, sizeof(QosValue));
	if (RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SetDevConfig:QOS_VALUE] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SetDevConfig:QOS_VALUE] Set success!");
	}
}

void CLS_QosPage::OnCbnSelchangeCboQosType()
{
	UI_UpdateQosInfo();
}
