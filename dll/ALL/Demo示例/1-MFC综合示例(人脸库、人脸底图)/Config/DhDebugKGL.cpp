
#include "stdafx.h"
#include "NetClientDemo.h"
#include "DhDebugKGL.h"
#include "../Common/CommonFun.h"
// CLS_DhDebugKGL 对话框

#define DEFAULT_DELAY_TIME	20

IMPLEMENT_DYNAMIC(CLS_DhDebugKGL, CDialog)

CLS_DhDebugKGL::CLS_DhDebugKGL(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_DhDebugKGL::IDD, pParent)
{
	m_iLogonID = -1;
	m_iInportNo = 0;
}

CLS_DhDebugKGL::~CLS_DhDebugKGL()
{
}

void CLS_DhDebugKGL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_SWITCH_STATUS, m_cboInportState);
	DDX_Control(pDX, IDC_SPIN_SWITCH_SUSTAIN_TIME, m_spinDelayTime);
}


BEGIN_MESSAGE_MAP(CLS_DhDebugKGL, CDialog)
	ON_BN_CLICKED(IDC_BTN_SWITCH_SET, &CLS_DhDebugKGL::OnBnClickedBtnSwitchSet)
END_MESSAGE_MAP()


// CLS_DhDebugMNL 消息处理程序

BOOL CLS_DhDebugKGL::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_SWITCH_NUM, IDS_CONFIG_LINK_DEV_NUM);
	SetDlgItemTextEx(IDC_STC_SWITCH_NAME, IDS_CONFIG_DH_NAME);
	SetDlgItemTextEx(IDC_STC_SWITCH_STATUS, IDS_CONFIG_DH_STATUS_SET);
	SetDlgItemTextEx(IDC_STC_SWITCH_SUSTAIN_TIME, IDS_CONFIG_DH_SUSTAIN_TIME);
	SetDlgItemTextEx(IDC_BTN_SWITCH_SET, IDS_CONFIG_LINK_SURE);

	m_cboInportState.AddString(GetTextEx(IDS_OUTPORT_STATE_ON));
	m_cboInportState.AddString(GetTextEx(IDS_OUTPORT_STATE_OFF));
	m_cboInportState.SetCurSel(0);

	m_spinDelayTime.SetRange(0,100);
	m_spinDelayTime.SetBuddy(GetDlgItem(IDC_EDT_SWITCH_SUSTAIN_TIME));	

	UpdateDialog();

	return TRUE;
}

BOOL CLS_DhDebugKGL::Init( int _iLogonID, int _iInportNo )
{
	m_iLogonID = _iLogonID;
	m_iInportNo = _iInportNo;
	return TRUE;
}

BOOL CLS_DhDebugKGL::UpdateDialog()
{
	SetDlgItemInt(IDC_CBO_SWITCH_NUM,m_iInportNo+1);

	AlarmInConfig tConfig = {sizeof(tConfig)};
	int iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_CONFIG,&tConfig);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDT_SWITCH_NAME,tConfig.cName);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugKGL::UpdateDialog] NetClient_GetAlarmConfig(%d,%d,,CMD_ALARM_IN_CONFIG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}

	AlarmInDebug tDebug = {sizeof(tDebug)};
	iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_DEBUG,&tDebug);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugKGL::UpdateDialog] NetClient_GetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}
	//m_cboInportState.SetCurSel(0);//状态值怎么获得?
	SetDlgItemInt(IDC_EDT_SWITCH_SUSTAIN_TIME,DEFAULT_DELAY_TIME);

	return TRUE;
}
void CLS_DhDebugKGL::OnBnClickedBtnSwitchSet()
{
	int iState = m_cboInportState.GetCurSel();//?状态值怎么设置
	AlarmInDebug tDebug = {sizeof(tDebug)};
	tDebug.iDelayTime = GetDlgItemInt(IDC_EDT_SWITCH_SUSTAIN_TIME);

	SwitchTest tData = {0};
	tData.iType = ALARM_INTERFACE_TYPE_SWITCH - 1;
	tData.iState = m_cboInportState.GetCurSel();
	CString strParam;
	StructToString(&tData,strParam);


	memcpy(tDebug.cParam,(LPSTR)(LPCTSTR)strParam,strParam.GetLength()+1);

	int iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_DEBUG,&tDebug);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","[CLS_DhDebugKGL::OnBnClickedBtnSwitchSet] NetClient_SetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) success! Error(0x%08x)"
			,m_iLogonID,m_iInportNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugKGL::OnBnClickedBtnSwitchSet] NetClient_SetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}
	EndDialog(IDCLOSE);
}

BOOL CLS_DhDebugKGL::StructToString( SwitchTest* _pSrc,CString& _strDest )
{
	if (NULL == _pSrc)
	{
		return FALSE;
	}

	_strDest.Format("type=%d,state=%d",_pSrc->iType, _pSrc->iState);

	return TRUE;
}

BOOL CLS_DhDebugKGL::StringToStruct( CString _strSrc,SwitchTest* _pDest )
{
	if (NULL == _pDest)
	{
		return FALSE;
	}

	return TRUE;
}

