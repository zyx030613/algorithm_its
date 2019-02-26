// ItsFocusAid.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsFocusAid.h"


// Cls_ItsFocusAid 对话框

IMPLEMENT_DYNAMIC(Cls_ItsFocusAid, CDialog)

Cls_ItsFocusAid::Cls_ItsFocusAid(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsFocusAid::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
	m_iCommand = -1;
}

Cls_ItsFocusAid::~Cls_ItsFocusAid()
{
}

void Cls_ItsFocusAid::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cboAreaSum);
	DDX_Control(pDX, IDC_EDIT_X2, m_editX[1]);
	DDX_Control(pDX, IDC_EDIT_Y2, m_editY[1]);
	DDX_Control(pDX, IDC_EDIT_X3, m_editX[2]);
	DDX_Control(pDX, IDC_EDIT_Y3, m_editY[2]);
	DDX_Control(pDX, IDC_EDIT_X4, m_editX[3]);
	DDX_Control(pDX, IDC_EDIT_Y4, m_editY[3]);
	DDX_Control(pDX, IDC_EDIT_X5, m_editX[4]);
	DDX_Control(pDX, IDC_EDIT_Y5, m_editY[4]);
	DDX_Control(pDX, IDC_EDIT_X1, m_editX[0]);
	DDX_Control(pDX, IDC_EDIT_Y1, m_editY[0]);
	DDX_Control(pDX, IDC_CBO_AREAID, m_cboAreaID);
}


BEGIN_MESSAGE_MAP(Cls_ItsFocusAid, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_AREA_SET, &Cls_ItsFocusAid::OnBnClickedBtnAreaSet)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cls_ItsFocusAid::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_START_FOCUS, &Cls_ItsFocusAid::OnBnClickedBtnStartFocus)
	ON_CBN_SELCHANGE(IDC_CBO_AREAID, &Cls_ItsFocusAid::OnCbnSelchangeCboAreaid)
END_MESSAGE_MAP()


// Cls_ItsFocusAid 消息处理程序

BOOL Cls_ItsFocusAid::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_cboAreaSum.AddString("1");
	m_cboAreaSum.AddString("2");
	m_cboAreaSum.AddString("3");
	m_cboAreaSum.AddString("4");
	m_cboAreaSum.AddString("5");
	UI_UpdateDialog();
	return TRUE; 
}
void Cls_ItsFocusAid::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	m_iChannel = _iChannelNo;

	
	UI_UpdateDialog();
}
void Cls_ItsFocusAid::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}
void Cls_ItsFocusAid::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_AREA_SUM, IDS_ITS_AREA_SUM);
	SetDlgItemTextEx(IDC_BTN_AREA_SET, IDS_ITS_AREA_SET);
	SetDlgItemTextEx(IDC_BTN_START_FOCUS, IDS_ITS_START_FOCUS);
	SetDlgItemTextEx(IDC_STC_RECT_AREA, IDS_ITS_RECT_AREA);
	SetDlgItemTextEx(IDC_STC_FOCUSMAG, IDS_ITS_FOCUS_AID);
	SetDlgItemTextEx(IDC_STC_AREAID, IDS_ITS_AREAID);
	for(int i = 0; i < ITS_AREAID_SUM; i++)
	{
		CString strNo;
		strNo.Format("%d", i);
		InsertString(m_cboAreaID, i, strNo);
	}
	m_cboAreaID.SetCurSel(0);
	m_cboAreaSum.SetCurSel(0);
	UI_UpdateArea();
	OnCbnSelchangeCombo1();
}
void Cls_ItsFocusAid::OnBnClickedBtnAreaSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iNum = m_cboAreaSum.GetCurSel();
	ITS_AreaInfo tAreaInfo = {0};
	tAreaInfo.iBufSize = sizeof(tAreaInfo);
	tAreaInfo.iRegionID = m_cboAreaID.GetCurSel();
	for (int i=0; i<ITS_AREA_SUM; i++)
	{
		if (i <= iNum)
		{
			tAreaInfo.stTPoint[i].iX = GetDlgItemInt(m_editX[i].GetDlgCtrlID());
			tAreaInfo.stTPoint[i].iY = GetDlgItemInt(m_editY[i].GetDlgCtrlID());
		} 
	}
	tAreaInfo.iCount = ITS_AREA_SUM;
	tAreaInfo.iType = 1;
	tAreaInfo.iEnabled = 1;
	tAreaInfo.iBufSize = sizeof(tAreaInfo);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_AREAINFO_CMD_SET, m_iChannel, &tAreaInfo, sizeof(tAreaInfo));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_AREAINFO_CMD_SET](%d)", m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_AREAINFO_CMD_SET](%d), error(%d)", m_iChannel, GetLastError());
	}
}
void Cls_ItsFocusAid::OnCbnSelchangeCombo1()
{
	int iNum = m_cboAreaSum.GetCurSel();
	for (int i=0; i<ITS_AREA_SUM; i++)
	{
		if (i <= iNum)
		{
			m_editX[i].ShowWindow(SW_SHOW); 
			m_editY[i].ShowWindow(SW_SHOW);
		} 
		else
		{
			m_editX[i].ShowWindow(SW_HIDE); 
			m_editY[i].ShowWindow(SW_HIDE);
		}
	}
}
BOOL Cls_ItsFocusAid::UI_UpdateArea()
{
	if(m_iLogonID < 0)
		return FALSE;
	ITS_AreaInfo tAreaInfo = {0};
	tAreaInfo.iBufSize = sizeof(tAreaInfo);
	tAreaInfo.iRegionID = m_cboAreaID.GetCurSel();
	tAreaInfo.iType = 1;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_AREAINFO_CMD_GET, m_iChannel, &tAreaInfo, sizeof(tAreaInfo));
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_X1, tAreaInfo.stTPoint[0].iX);
		SetDlgItemInt(IDC_EDIT_Y1, tAreaInfo.stTPoint[0].iY);
		SetDlgItemInt(IDC_EDIT_X2, tAreaInfo.stTPoint[1].iX);
		SetDlgItemInt(IDC_EDIT_Y2, tAreaInfo.stTPoint[1].iY);
		SetDlgItemInt(IDC_EDIT_X3, tAreaInfo.stTPoint[2].iX);
		SetDlgItemInt(IDC_EDIT_Y3, tAreaInfo.stTPoint[2].iY);
		SetDlgItemInt(IDC_EDIT_X4, tAreaInfo.stTPoint[3].iX);
		SetDlgItemInt(IDC_EDIT_Y4, tAreaInfo.stTPoint[3].iY);
		SetDlgItemInt(IDC_EDIT_X5, tAreaInfo.stTPoint[4].iX);
		SetDlgItemInt(IDC_EDIT_Y5, tAreaInfo.stTPoint[4].iY);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_AREAINFO_CMD_GET](%d,%d)", m_iCommand, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_AREAINFO_CMD_GET](%d,%d), error(%d)", m_iCommand, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void Cls_ItsFocusAid::OnBnClickedBtnStartFocus()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	m_iCommand = FOCUS_COMMANDTYPE_FINISHED;
	int iRet = NetClient_SendCommand(m_iLogonID,  COMMAND_ID_ITS_FOCUS,  m_iChannel,  &m_iCommand,  sizeof(m_iCommand));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SendCommand[COMMAND_ID_ITS_FOCUS](%d,%d)", m_iCommand, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SendCommand[COMMAND_ID_ITS_FOCUS](%d,%d), error(%d)", m_iCommand, m_iChannel, GetLastError());
	}
}

void Cls_ItsFocusAid::OnCbnSelchangeCboAreaid()
{
	UI_UpdateArea();
}
