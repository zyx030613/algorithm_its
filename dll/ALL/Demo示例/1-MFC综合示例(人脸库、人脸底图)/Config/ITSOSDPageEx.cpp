
#include "stdafx.h"
#include "ITSOSDPageEx.h"

#define MAX_TIME_OSD_LENGTH				8
#define MIN_FORMAT_EDT_NO				IDC_EDT_YEAR_LEFT
#define MAX_FORMAT_EDT_NO				IDC_EDT_MILLISCOND_RIGHT
#define MAX_LEN_CH						(8)


IMPLEMENT_DYNAMIC(CLS_ITSOSDPageEx, CDialog)

CLS_ITSOSDPageEx::CLS_ITSOSDPageEx(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSOSDPageEx::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ITSOSDPageEx::~CLS_ITSOSDPageEx()
{
}

void CLS_ITSOSDPageEx::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CLS_ITSOSDPageEx, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_TIME_PREVIEW, &CLS_ITSOSDPageEx::OnBnClickedBtnTimePreview)
	ON_BN_CLICKED(IDC_BTN_SET_TIME_TYPE, &CLS_ITSOSDPageEx::OnBnClickedBtnSetTimeType)
	ON_CONTROL_RANGE(EN_CHANGE,MIN_FORMAT_EDT_NO,MAX_FORMAT_EDT_NO,&CLS_ITSOSDPageEx::OnFormatEditChange)
END_MESSAGE_MAP()

BOOL CLS_ITSOSDPageEx::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSOSDPageEx::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if(_iChannelNo < 0)
	{
		m_iChannel = 0;
	}
	else
	{
		m_iChannel = _iChannelNo;
	}

	UI_UpdateDialog();
	UI_UpdateOsdInfo();
	UI_UpdateDateTime();
}

void CLS_ITSOSDPageEx::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSOSDPageEx::UI_UpdateDialog()
{
	((CEdit*)GetDlgItem(IDC_EDT_YEAR_LEFT))->SetLimitText(MAX_TIME_OSD_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDT_MONTH_LEFT))->SetLimitText(MAX_TIME_OSD_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDT_DAY_LEFT))->SetLimitText(MAX_TIME_OSD_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDT_HOUR_LEFT))->SetLimitText(MAX_TIME_OSD_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDT_MINUTE_LEFT))->SetLimitText(MAX_TIME_OSD_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDT_SECOND_LEFT))->SetLimitText(MAX_TIME_OSD_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDT_MILLISCOND_LEFT))->SetLimitText(MAX_TIME_OSD_LENGTH);
	((CEdit*)GetDlgItem(IDC_EDT_MILLISCOND_RIGHT))->SetLimitText(MAX_TIME_OSD_LENGTH);

	SetDlgItemTextEx(IDC_STATIC_MAINOSD_EX, IDS_CONFIG_OSD);
	SetDlgItemTextEx(IDC_STC_TIME_TYPE, IDS_TIME_FORMAT);
	SetDlgItemTextEx(IDC_BTN_TIME_PREVIEW, IDS_PREVIEW);
	SetDlgItemTextEx(IDC_STC_TIME_PREVIEW, IDS_PREVIEW);
	SetDlgItemTextEx(IDC_BTN_SET_TIME_TYPE, IDS_SET);
}

void CLS_ITSOSDPageEx::UI_UpdateDateTime()
{
	SYSTEMTIME tSysTime;
	GetLocalTime(&tSysTime);
	SetDlgItemInt(IDC_EDT_YEAR, tSysTime.wYear);
	SetDlgItemInt(IDC_EDT_MONTH, tSysTime.wMonth);
	SetDlgItemInt(IDC_EDT_DAY, tSysTime.wDay);
	SetDlgItemInt(IDC_EDT_HOUR, tSysTime.wHour);
	SetDlgItemInt(IDC_EDT_MINUTE, tSysTime.wMinute);
	SetDlgItemInt(IDC_EDT_SECOND, tSysTime.wSecond);
	SetDlgItemInt(IDC_EDT_MILLISCOND, tSysTime.wMilliseconds);

	CString cstrTimePreview;

	for (int iId = IDC_EDT_YEAR; iId <= IDC_EDT_MILLISCOND_RIGHT; iId++)
	{
		CString cstrTemp;
		GetDlgItemText(iId, cstrTemp);
		cstrTimePreview += cstrTemp;
	}

	SetDlgItemText(IDC_EDT_TIME_PREVIEW, cstrTimePreview);
}

void CLS_ITSOSDPageEx::OnBnClickedBtnTimePreview()
{
	UI_UpdateDateTime();
}

void CLS_ITSOSDPageEx::UI_UpdateOsdInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage LogId(%d)", m_iLogonID);
		return;
	}

	if (m_iChannel < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage ChannelNo(%d)", m_iChannel);
		return;
	}

	ItsOsdTimeFormat tItsOsdTimeFormat = {0};
	tItsOsdTimeFormat.iSize = sizeof(ItsOsdTimeFormat);
	
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_OSDTIMEFORMAT, m_iChannel, &tItsOsdTimeFormat, sizeof(ItsOsdTimeFormat));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[OSDTIMEFORMAT](%d, %d)", m_iLogonID, m_iChannel);
		return;
	}

	AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[OSDTIMEFORMAT](%d, %d)", m_iLogonID, m_iChannel);

	SetDlgItemText(IDC_EDT_YEAR_LEFT, tItsOsdTimeFormat.cYearText);
	SetDlgItemText(IDC_EDT_MONTH_LEFT, tItsOsdTimeFormat.cMonText);
	SetDlgItemText(IDC_EDT_DAY_LEFT, tItsOsdTimeFormat.cDayText);
	SetDlgItemText(IDC_EDT_HOUR_LEFT, tItsOsdTimeFormat.cHourText);
	SetDlgItemText(IDC_EDT_MINUTE_LEFT, tItsOsdTimeFormat.cMinText);
	SetDlgItemText(IDC_EDT_SECOND_LEFT, tItsOsdTimeFormat.cSecText);
	SetDlgItemText(IDC_EDT_MILLISCOND_LEFT, tItsOsdTimeFormat.cMilsecText1);
	SetDlgItemText(IDC_EDT_MILLISCOND_RIGHT, tItsOsdTimeFormat.cMilsecText2);
}

void CLS_ITSOSDPageEx::OnBnClickedBtnSetTimeType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage LogId(%d)", m_iLogonID);
		return;
	}

	if (m_iChannel < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Illeage ChannelNo(%d)", m_iChannel);
		return;
	}

	ItsOsdTimeFormat tItsOsdTimeFormat = {0};
	tItsOsdTimeFormat.iSize = sizeof(ItsOsdTimeFormat);
	CString cstrTempDate;
	GetDlgItemText(IDC_EDT_YEAR_LEFT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cYearText, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);
	GetDlgItemText(IDC_EDT_MONTH_LEFT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cMonText, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);
	GetDlgItemText(IDC_EDT_DAY_LEFT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cDayText, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);
	GetDlgItemText(IDC_EDT_HOUR_LEFT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cHourText, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);
	GetDlgItemText(IDC_EDT_MINUTE_LEFT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cMinText, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);
	GetDlgItemText(IDC_EDT_SECOND_LEFT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cSecText, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);
	GetDlgItemText(IDC_EDT_MILLISCOND_LEFT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cMilsecText1, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);
	GetDlgItemText(IDC_EDT_MILLISCOND_RIGHT, cstrTempDate);
	memcpy_s(tItsOsdTimeFormat.cMilsecText2, LEN_8, (LPSTR)(LPCSTR)cstrTempDate, LEN_8);

	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_OSDTIMEFORMAT, m_iChannel, &tItsOsdTimeFormat, sizeof(ItsOsdTimeFormat));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[OSDTIMEFORMAT](%d, %d)", m_iLogonID, m_iChannel);
		return;
	}

	AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[OSDTIMEFORMAT](%d, %d)", m_iLogonID, m_iChannel);
}

void CLS_ITSOSDPageEx::OnFormatEditChange( UINT _uiID )
{
	CString cstrTempFormat;
	CEdit* pedtFormat = ((CEdit*)GetDlgItem(_uiID));
	pedtFormat->GetWindowText(cstrTempFormat);
	
	int iMaxLen = pedtFormat->GetLimitText();
	int iTempLen = cstrTempFormat.GetLength();

	char cTempBuf[MAX_LEN_CH] = {0};
	FillStringBufferGb2312(cTempBuf, MAX_LEN_CH, (LPSTR)(LPCTSTR)cstrTempFormat, iTempLen);
	cstrTempFormat = cTempBuf;

	pedtFormat->SetWindowText(cstrTempFormat);
	pedtFormat->SetSel(iMaxLen, iMaxLen);
	return;
}
