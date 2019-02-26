// ItsIllegalTppe.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsIllegalType.h"


#define MAX_ILLEGAL_NAME_LEN		80

IMPLEMENT_DYNAMIC(Cls_ItsIllegalTppe, CDialog)

Cls_ItsIllegalTppe::Cls_ItsIllegalTppe(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsIllegalTppe::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

Cls_ItsIllegalTppe::~Cls_ItsIllegalTppe()
{
}

void Cls_ItsIllegalTppe::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ILLEGAL_NAME, m_editIllegalName);
	DDX_Control(pDX, IDC_CBO_ILLEGAL_ID, m_cboIllegalID);
	DDX_Control(pDX, IDC_CBO_PRIORITY, m_cboPriority);
	DDX_Control(pDX, IDC_STC_ILLEAGLE_NUMBER, m_stcIlleagleNumber);
	DDX_Control(pDX, IDC_CBO_ILLEAGLE_NUMBER, m_cboIlleagleNumber);
	DDX_Control(pDX, IDC_STC_LANE_ID, m_stcLaneId);
	DDX_Control(pDX, IDC_CBO_LANE_ID, m_cobLaneId);
}


BEGIN_MESSAGE_MAP(Cls_ItsIllegalTppe, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_ILLEGAI_SET, &Cls_ItsIllegalTppe::OnBnClickedBtnIllegaiSet)
	ON_CBN_SELCHANGE(IDC_CBO_ILLEAGLE_NUMBER, &Cls_ItsIllegalTppe::OnCbnSelchangeCboIlleagleNumber)
	ON_CBN_SELCHANGE(IDC_CBO_LANE_ID, &Cls_ItsIllegalTppe::OnCbnSelchangeCboLaneId)
END_MESSAGE_MAP()


// Cls_ItsIllegalTppe 消息处理程序

BOOL Cls_ItsIllegalTppe::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();

	m_editIllegalName.SetLimitText(MAX_ILLEGAL_NAME_LEN);
	return TRUE;  // return TRUE unless you set the focus to a control
	
}
void Cls_ItsIllegalTppe::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	m_iChannel = _iChannelNo;
	if(m_iChannel < 0)
	{
		m_iChannel = 0;
	}
	if (!UI_UpdateIllegal())
	{
		UI_UpdateNumber();
	}
}
void Cls_ItsIllegalTppe::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
	UI_UpdateIllegal();
	UI_UpdateNumber();
}
void Cls_ItsIllegalTppe::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_ILLEGAL_TYPE, IDS_ITS_ILLEGAL_TYPE);
	SetDlgItemTextEx(IDC_STC_ILLEGAL_NAME, IDS_ITS_ILLEGAL_NAME);
	SetDlgItemTextEx(IDC_STC_PRIORITY, IDS_ITS_PRIORITY);
	SetDlgItemTextEx(IDC_BTN_ILLEGAI_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STC_ILLEGAL_ID, IDS_ITS_ILLEGAL_ID);
	SetDlgItemTextEx(IDC_STC_LANE_ID, IDS_ITS_LANE_ID);
	SetDlgItemTextEx(IDC_STC_ILLEAGLE_NUMBER, IDS_ITS_ILLEAGLE_TYPE_NUMBER);
	for(int i = 0; i < ILLEAGLE_ID_NUMBER; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboIllegalID, i, strNo);
	}
	for(int i = 0; i <= MAX_PRIORITY; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboPriority, i, strNo);
	}
	for(int i = 0;i <= LANE_ID; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cobLaneId, i, strNo);
	}
	for(int i = 0;i < ILLEAGLE_NUMBER; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboIlleagleNumber, i, strNo);
	}
	m_cboIlleagleNumber.SetCurSel(1);
	m_cobLaneId.SetCurSel(0);
}
void Cls_ItsIllegalTppe::OnBnClickedBtnIllegaiSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITSIllegalType tIllegalType = {0};
	tIllegalType.iBufSize = sizeof(tIllegalType);
	tIllegalType.iLaneID = m_cobLaneId.GetCurSel();
	tIllegalType.iTypeID = m_cboIlleagleNumber.GetCurSel() + 1;
	CString str1;
	GetDlgItemText(IDC_EDIT_ILLEGAL_NAME, str1);
	strcpy_s(tIllegalType.pcName, str1);
	CString str2;
	GetDlgItem(IDC_CBO_ILLEGAL_ID)->GetWindowText(str2);
	strcpy_s(tIllegalType.cMarkID, str2);
	tIllegalType.iPriority = m_cboPriority.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_ILLEGAL, m_iChannel, &tIllegalType, sizeof(tIllegalType));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_ILLEGAL] (%d,%d)",m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_ILLEGAL] (%d,%d), error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL Cls_ItsIllegalTppe::UI_UpdateIllegal()
{
	if(m_iLogonID < 0)
		return FALSE;

	ITSIllegalType tIllegalType = {0};
	tIllegalType.iBufSize = sizeof(tIllegalType);
	tIllegalType.iLaneID = m_cobLaneId.GetCurSel();
	tIllegalType.iTypeID = m_cboIlleagleNumber.GetCurSel() + 1;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_ILLEGAL, m_iChannel, &tIllegalType, sizeof(tIllegalType));
	if(iRet == 0)
	{
		CString str;
		str.Format("%s", tIllegalType.cMarkID);
		m_cboIllegalID.SetCurSel(_ttoi(str));
		m_cboPriority.SetCurSel(tIllegalType.iPriority);

		CString cstrTempName = tIllegalType.pcName;
		m_editIllegalName.SetWindowText(cstrTempName);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_ILLEGAL] (%d,%d)",m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_ILLEGAL] (%d,%d), error(%d)",m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
 	return TRUE;
}

void Cls_ItsIllegalTppe::UI_UpdateNumber()
{
	CString csNumberName[] =
	{
		GetTextEx(IDS_ITS_PARA_BAYONET_CAMERA),
		GetTextEx(IDS_ITS_PARA_BAYONET_CAMERA),
		GetTextEx(IDS_ITS_WRONG_DIRECTION),
		GetTextEx(IDS_ITS_RED_LIGHT),
		GetTextEx(IDS_ITS_INTRANCE),
		GetTextEx(IDS_ITS_CROSS_THE_LINE),
		GetTextEx(IDS_ITS_BAN_ORDER),
		GetTextEx(IDS_ITS_AMBLE),
		GetTextEx(IDS_ITS_OVERSPEED),
		GetTextEx(IDS_ITS_ILLEAGLE_TURN_HEAD),
		GetTextEx(IDS_ITS_CAR_USE_THE_BUS_LANE),
		GetTextEx(IDS_ITS_ILLEAGLE_BACK_CAR),
		GetTextEx(IDS_ITS_ILLEAGLE_CHANGE_LANE),
		GetTextEx(IDS_ITS_MIXED_ENABLE)
	};
	int iSelect = m_cboIlleagleNumber.GetCurSel();
	GetDlgItem(IDC_EDIT_ILLEGAL_NAME)->SetWindowText(csNumberName[iSelect]);
}

void Cls_ItsIllegalTppe::OnCbnSelchangeCboIlleagleNumber()
{
	UI_UpdateNumber();
	UI_UpdateIllegal();
}

void Cls_ItsIllegalTppe::OnCbnSelchangeCboLaneId()
{
	UI_UpdateNumber();
	UI_UpdateIllegal();
}
