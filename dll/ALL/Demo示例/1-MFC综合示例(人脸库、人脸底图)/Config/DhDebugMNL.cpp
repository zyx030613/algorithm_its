
#include "stdafx.h"
#include "NetClientDemo.h"
#include "DhDebugMNL.h"
#include "../Common/CommonFun.h"
#include "..\\Include\\NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;
// CLS_DhDebugMNL 对话框

#define DEFAULT_DELAY_TIME	20
#define DEFAULT_DATA	10


IMPLEMENT_DYNAMIC(CLS_DhDebugMNL, CDialog)

CLS_DhDebugMNL::CLS_DhDebugMNL(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_DhDebugMNL::IDD, pParent)
{
	m_iLogonID = -1;
	m_iInportNo = 0;
}

CLS_DhDebugMNL::~CLS_DhDebugMNL()
{
}

void CLS_DhDebugMNL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN_MNL_TIME, m_spinDelayTime);
}


BEGIN_MESSAGE_MAP(CLS_DhDebugMNL, CDialog)
	ON_BN_CLICKED(IDC_BTN_MNL_SET, &CLS_DhDebugMNL::OnBnClickedBtnMnlSet)
END_MESSAGE_MAP()


// CLS_DhDebugMNL 消息处理程序

BOOL CLS_DhDebugMNL::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_MNL_NUM, IDS_CONFIG_LINK_DEV_NUM);
	SetDlgItemTextEx(IDC_STC_MNL_NAME, IDS_CONFIG_DH_NAME);
	SetDlgItemTextEx(IDC_STC_MNL_DATA, IDS_CONFIG_DH_DATA);
	SetDlgItemTextEx(IDC_STC_MNL_TIME, IDS_CONFIG_DH_SUSTAIN_TIME);
	SetDlgItemTextEx(IDC_BTN_MNL_SET, IDS_CONFIG_LINK_SURE);

	m_spinDelayTime.SetRange(0,100);
	m_spinDelayTime.SetBuddy(GetDlgItem(IDC_EDT_SWITCH_SUSTAIN_TIME));	

	UpdateDialog();

	return TRUE;
}

BOOL CLS_DhDebugMNL::Init( int _iLogonID, int _iInportNo )
{
	m_iLogonID = _iLogonID;
	m_iInportNo = _iInportNo;
	return TRUE;
}

BOOL CLS_DhDebugMNL::UpdateDialog()
{
	SetDlgItemInt(IDC_CBO_MNL_NUM,m_iInportNo+1);

	AlarmInConfig tConfig = {sizeof(tConfig)};
	//tConfig.iInterfaceNo = m_iInportNo;
	int iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_CONFIG,&tConfig);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDT_MNL_NAME,tConfig.cName);

		AnalogInfo tSimuInfo;
		StringToStruct(tConfig.cParam, &tSimuInfo);
		if (strlen(tSimuInfo.cUnit) > 0)
		{
			CString strUnit;
			strUnit.Format(_T("%s(%s)"),GetText(IDS_POWER_ENV_DUBUG_DATA),tSimuInfo.cUnit);
			SetDlgItemText(IDC_STC_MNL_DATA, strUnit);
		}

	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugMNL::UpdateDialog] GetAlarmConfig(%d,%d,,CMD_ALARM_IN_CONFIG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}

	AlarmInDebug tDebug = {sizeof(tDebug)};
	iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_DEBUG,&tDebug);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDT_MNL_DATA,DEFAULT_DELAY_TIME);///////////?
		SetDlgItemInt(IDC_EDT_MNL_TIME,DEFAULT_DATA);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugMNL::UpdateDialog] GetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}
	return TRUE;
}

void CLS_DhDebugMNL::OnBnClickedBtnMnlSet()
{
	int iData = GetDlgItemInt(IDC_EDT_MNL_DATA);//?数据值怎么设置
	AlarmInDebug tDebug = {sizeof(tDebug)};
	tDebug.iDelayTime = GetDlgItemInt(IDC_EDT_MNL_TIME);

	AnalogTest tData = {0};
	tData.iType = ALARM_INTERFACE_TYPE_ANALOG - 1;
	CString cstrDate = "";
	GetDlgItemText(IDC_EDT_MNL_DATA, cstrDate);
	double fData = atof((LPSTR)(LPCTSTR)cstrDate);
	tData.iData = (int)fData * 100 + 10000;
	CString strParam;
	StructToString(&tData,strParam);	
	memcpy(tDebug.cParam,(LPSTR)(LPCTSTR)strParam,strParam.GetLength()+1);

	int iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_DEBUG,&tDebug);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","[CLS_DhDebugMNL::OnBnClickedBtnSure] SetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) success! Error(0x%08x)"
			,m_iLogonID,m_iInportNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugMNL::OnBnClickedBtnSure] SetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}
	EndDialog(IDCLOSE);
}

BOOL CLS_DhDebugMNL::StringToStruct( CString _cstrSrc,AnalogInfo* _strctDest )
{
	if (NULL == _strctDest)
	{
		return FALSE;
	}

	static int s_iParamNum = 0;
	while(1)
	{
		int iIndex = _cstrSrc.Find(',');
		if (iIndex < 0)
		{
			s_iParamNum = 0;
			break;
		}

		s_iParamNum++;
		CString cstrParam = _cstrSrc.Left(iIndex);

		int iParamIndex = cstrParam.Find('=');
		if (iParamIndex < 0)
		{
			return FALSE;
		}
		CString strKey = cstrParam.Left(iParamIndex);
		CString strValue = cstrParam.Right(cstrParam.GetLength()-iParamIndex-1);

		switch (s_iParamNum)
		{
		case 1:
			strcpy(_strctDest->cUnit,strValue.GetBuffer());
			break;
		case 2:
			_strctDest->iCollectTime = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 3:
			_strctDest->iRangeUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 4:
			_strctDest->iRangeUpValue = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 5:
			_strctDest->iRangeDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 6:
			_strctDest->iRangeDownValue = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 7:
			_strctDest->iAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;		
		case 8:
			_strctDest->iAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 9:
			_strctDest->iDisAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 10:
			_strctDest->iDisAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		default:
			break;
		}

		_cstrSrc = _cstrSrc.Right(_cstrSrc.GetLength()-iIndex-1);
	}

// 	CLS_TString tData;
// 	tData.Split(_strSrc);
// 	strcpy_s(_pDest->cUnit,(LPSTR)(LPCTSTR)tData.GetValue(_T("unit")));
// 	_pDest->iCollectTime = tData.GetIntValue(_T("interval"));
// 	_pDest->iRangeUpLevel = tData.GetIntValue(_T("disuplimit"));
// 	_pDest->iRangeUpValue = tData.GetIntValue(_T("disupvalue"));
// 	_pDest->iRangeDownLevel = tData.GetIntValue(_T("dislowlimit"));
// 	_pDest->iRangeDownValue = tData.GetIntValue(_T("dislowvalue"));
// 	_pDest->iAlarmUpLevel = tData.GetIntValue(_T("alarmup"));
// 	_pDest->iAlarmDownLevel = tData.GetIntValue(_T("alarmlow"));
// 	_pDest->iDisAlarmUpLevel = tData.GetIntValue(_T("elimup"));
// 	_pDest->iDisAlarmDownLevel = tData.GetIntValue(_T("elimlow"));

	return TRUE;
}

BOOL CLS_DhDebugMNL::StructToString( AnalogTest* _pSrc,CString& _strDest )
{
	if (NULL == _pSrc)
	{
		return FALSE;
	}
	_strDest.Format("type=%d,data=%d", _pSrc->iType, _pSrc->iData);
	return TRUE;
}