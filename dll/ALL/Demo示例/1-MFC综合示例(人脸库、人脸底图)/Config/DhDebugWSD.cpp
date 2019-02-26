
#include "stdafx.h"
#include "NetClientDemo.h"
#include "DhDebugWSD.h"
#include "../Common/CommonFun.h"
#include "..\\Include\\NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;
// CLS_DhDebugWSD 对话框


#define MIN_TEMPERATURE	-30.00
#define MAX_TEMPERATURE	100.00
#define DEFAULT_TEMPERATURE	25.00
#define MIN_HUMITURE	0.00
#define MAX_HUMITURE	100.00
#define DEFAULT_HUMITURE	50.00
#define DEFAULT_DELAY_TIME	20


IMPLEMENT_DYNAMIC(CLS_DhDebugWSD, CDialog)

CLS_DhDebugWSD::CLS_DhDebugWSD(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_DhDebugWSD::IDD, pParent)
{
	m_iLogonID = -1;
	m_iInportNo = 0;
}

CLS_DhDebugWSD::~CLS_DhDebugWSD()
{
}

void CLS_DhDebugWSD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN_WSD_TIME, m_spinDelayTime);
}


BEGIN_MESSAGE_MAP(CLS_DhDebugWSD, CDialog)
	ON_BN_CLICKED(IDC_BTN_WSD_SET, &CLS_DhDebugWSD::OnBnClickedBtnWsdSet)
END_MESSAGE_MAP()


// CLS_DhDebugWSD 消息处理程序

BOOL CLS_DhDebugWSD::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_WSD_NUM, IDS_CONFIG_LINK_DEV_NUM);
	SetDlgItemTextEx(IDC_STC_WSD_NAME, IDS_CONFIG_DH_NAME);
	SetDlgItemTextEx(IDC_STC_WSD_TEMPERATURE, IDS_CONFIG_DH_TEMPETATURE);
	SetDlgItemTextEx(IDC_STC_WSD_HUMIDITY, IDS_CONFIG_DH_HUMIDITY);
	SetDlgItemTextEx(IDC_STC_WSD_TIME, IDS_CONFIG_DH_SUSTAIN_TIME);
	SetDlgItemTextEx(IDC_BTN_WSD_SET, IDS_CONFIG_LINK_SURE);

	m_spinDelayTime.SetRange(0,100);
	m_spinDelayTime.SetBuddy(GetDlgItem(IDC_EDT_SWITCH_SUSTAIN_TIME));	

	UpdateDialog();

	return TRUE;
}

BOOL CLS_DhDebugWSD::Init( int _iLogonID, int _iInportNo )
{
	m_iLogonID = _iLogonID;
	m_iInportNo = _iInportNo;
	return TRUE;
}

BOOL CLS_DhDebugWSD::UpdateDialog()
{
	SetDlgItemInt(IDC_CBO_WSD_NUM,m_iInportNo+1);

	AlarmInConfig tConfig = {sizeof(tConfig)};
	int iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_CONFIG,&tConfig);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDT_WSD_NAME,tConfig.cName);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugWSD::UpdateDialog] GetAlarmConfig(%d,%d,,CMD_ALARM_IN_CONFIG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}

	AlarmInDebug tDebug = {sizeof(tDebug)};
	iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_DEBUG,&tDebug);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugWSD::UpdateDialog] GetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}

	//使用默认值
	SetDlgItemInt(IDC_EDT_WSD_TIME,DEFAULT_DELAY_TIME);

	CString strTemperature;
	strTemperature.Format( _T("%0.2f"), DEFAULT_TEMPERATURE );
	SetDlgItemText(IDC_EDT_WSD_TEMPERATURE,strTemperature);
	CString strHumidity;
	strHumidity.Format( _T("%0.2f"),DEFAULT_HUMITURE );
	SetDlgItemText(IDC_EDT_WSD_HUMIDITY,strHumidity);
	return TRUE;
}

void CLS_DhDebugWSD::OnBnClickedBtnWsdSet()
{
	CString strTemperature;
	GetDlgItemText(IDC_EDT_WSD_TEMPERATURE,strTemperature);

	CString strHumiture;
	GetDlgItemText(IDC_EDT_WSD_HUMIDITY,strHumiture);
	double fHumidity = atof((LPSTR)(LPCTSTR)strHumiture);
//	int iTemperature = GetDlgItemInt(IDC_EDT_WSD_TEMPERATURE);//?值怎么设置
	int iHumiture = GetDlgItemInt(IDC_EDT_WSD_HUMIDITY);//值怎么设置?
	AlarmInDebug tDebug = {sizeof(tDebug)};
	tDebug.iDelayTime = GetDlgItemInt(IDC_EDT_WSD_TIME);

	double fTemperature = atof((LPSTR)(LPCTSTR)strTemperature);

	HumitureTest tData = {0};
	tData.iType = ALARM_INTERFACE_TYPE_COM - 1;
	tData.iTemperature = (int)fTemperature*100+10000;
	tData.iHumidity = (int)fHumidity*100+10000;
	CString strParam;
	StructToString(&tData,strParam);	
	memcpy(tDebug.cParam,(LPSTR)(LPCTSTR)strParam,strParam.GetLength()+1);


	int iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iInportNo,-1,CMD_ALARM_IN_DEBUG,&tDebug);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","[CLS_DhDebugWSD::OnBnClickedBtnWsdSet] SetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) success! Error(0x%08x)"
			,m_iLogonID,m_iInportNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_DhDebugWSD::OnBnClickedBtnWsdSet] SetAlarmConfig(%d,%d,,CMD_ALARM_IN_DEBUG) failed! Error(0x%08x)"
			,m_iLogonID,m_iInportNo,GetLastError());
	}
	EndDialog(IDCLOSE);
}

BOOL CLS_DhDebugWSD::StructToString( HumitureTest* _pSrc,CString& _strDest )
{
	if (NULL == _pSrc)
	{
		return FALSE;
	}

	_strDest.Format("type=%d,tem=%d,hum=%d", _pSrc->iType, _pSrc->iTemperature, _pSrc->iHumidity);

	return TRUE;

}