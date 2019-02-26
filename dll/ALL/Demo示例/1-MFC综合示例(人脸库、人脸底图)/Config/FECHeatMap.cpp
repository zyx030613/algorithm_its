
#include "stdafx.h"
#include "NetClientDemo.h"
#include "FECHeatMap.h"

#define QUERY_ALL_CHANNEL		0xff

IMPLEMENT_DYNAMIC(CLS_FECHeatMap, CDialog)

CLS_FECHeatMap::CLS_FECHeatMap(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_FECHeatMap::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_FECHeatMap::~CLS_FECHeatMap()
{
}

void CLS_FECHeatMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_TIME_HEAT_MAP, m_lstTimeHeatMap);
	DDX_Control(pDX, IDC_TIME_TIME_MAP_BEGAIN_TIME, m_dtimeTimeMapBeginTime);
	DDX_Control(pDX, IDC_CBO_PRECISION_TYPE, m_cboPrecisionType);
	DDX_Control(pDX, IDC_DTIME_SPACEMAP_BEGIN_TIME, m_dtimeSpaceMapBeginTime);
	DDX_Control(pDX, IDC_DTIME_SPACEMAP_END_TIME, m_dtimeSpaceMapEndTime);
	DDX_Control(pDX, IDC_CBO_REPORT_QUERRY_TYPE, m_cboReportQueryType);
	DDX_Control(pDX, IDC_TIME_TIME_MAP_END_TIME, m_dtimeTimeMapEndTime);
}

BEGIN_MESSAGE_MAP(CLS_FECHeatMap, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_QUERY_TIME_MAP, &CLS_FECHeatMap::OnBnClickedBtnQueryTimeMap)
	ON_BN_CLICKED(IDC_BTN_QUERY_SPACE_MAP, &CLS_FECHeatMap::OnBnClickedBtnQuerySpaceMap)
	ON_CBN_SELCHANGE(IDC_CBO_REPORT_QUERRY_TYPE, &CLS_FECHeatMap::OnCbnSelchangeCboReportQuerryType)
END_MESSAGE_MAP()

BOOL CLS_FECHeatMap::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	InitDlgWidget();
	UI_UpdateDialog();
	return TRUE;
}

void CLS_FECHeatMap::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_FECHeatMap::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? FLAG_QUERY_ALL_CHANNEL : _iChannelNo;
} 

void CLS_FECHeatMap::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser )
{
	//TODO
}

void CLS_FECHeatMap::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	if (_iLogonID != m_iLogonID)
	{
		return;
	}

	switch (_iParaType)
	{
	case PARA_REPORT_QUERY:
		UpdateReportQueryMap((ReportQueryResult*)_pPara);
		break;
	case PARA_HEATMAP_GET:
		UpdateSpaceHeatMap();
		break;

	}
}

void CLS_FECHeatMap::InitDlgWidget()
{
	SetDlgItemTextEx(IDC_GP_DNVR_CHANNEL_STATE, IDS_CONFIG_DNVR_CHANNEL_STATE);
	DWORD dwStyle = m_lstTimeHeatMap.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;  
	m_lstTimeHeatMap.SetExtendedStyle(dwStyle);
	InsertColumn(m_lstTimeHeatMap, n_LTHMC_OccurTime, GetTextEx(IDS_LOG_TIME), LVCFMT_CENTER, n_LTHMCW_OccurTime);
	InsertColumn(m_lstTimeHeatMap, n_LTHMC_ChannelNo, GetTextEx(IDS_CONFIG_FTP_CHANNEL), LVCFMT_CENTER, n_LTHMCW_ChannelNo);
	InsertColumn(m_lstTimeHeatMap, n_LTHMC_LogContent, GetTextEx(IDS_CFG_LOG_DVR_LOGCONTENT), LVCFMT_CENTER, n_LTHMCW_LogContent);
	m_lstTimeHeatMap.DeleteAllItems();

	m_dtimeTimeMapBeginTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_dtimeTimeMapEndTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_dtimeSpaceMapBeginTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_dtimeSpaceMapEndTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	
	CTime timeSysTime = CTime::GetCurrentTime();   
	m_dtimeTimeMapBeginTime.SetTime(&timeSysTime);
	m_dtimeTimeMapEndTime.SetTime(&timeSysTime);
	m_dtimeSpaceMapBeginTime.SetTime(&timeSysTime);
	m_dtimeSpaceMapEndTime.SetTime(&timeSysTime);
}

void CLS_FECHeatMap::InsertListItemText(int _iIndex, ReportQueryInfo _tQueryInfo)
{
	m_lstTimeHeatMap.InsertItem(_iIndex, "");
	CString cstrTime;
	cstrTime.Format("%d-%d-%d  %d:%d:%d", _tQueryInfo.tOccurTime.iYear, _tQueryInfo.tOccurTime.iMonth, 
										  _tQueryInfo.tOccurTime.iDay, _tQueryInfo.tOccurTime.iHour, 
										  _tQueryInfo.tOccurTime.iMinute, _tQueryInfo.tOccurTime.iSecond);
	m_lstTimeHeatMap.SetItemText(_iIndex, n_LTHMC_OccurTime, cstrTime);
	m_lstTimeHeatMap.SetItemText(_iIndex, n_LTHMC_ChannelNo, IntToString(_tQueryInfo.iChannelNo));

	int iCurQueryType = m_cboReportQueryType.GetItemData(m_cboReportQueryType.GetCurSel());
	float fiLogContent = ((float)_ttoi(_tQueryInfo.cLogContent) - 1000)/10;

	switch (iCurQueryType)
	{
	case REPORT_QUERY_TYPE_TEMPERATURE:
	case REPORT_QUERY_TYPE_HUMIDNESS:
		{
			_gcvt_s(_tQueryInfo.cLogContent, MAX_REPORT_CONTENT_LOG_LEN, fiLogContent, LEN_8);
		}
		break;
	default:
		break;
	}

	m_lstTimeHeatMap.SetItemText(_iIndex, n_LTHMC_LogContent, _tQueryInfo.cLogContent);
}

void CLS_FECHeatMap::UI_UpdateDialog()
{
	SetListCtrlColumn(m_lstTimeHeatMap, n_LTHMC_OccurTime, GetTextEx(IDS_LOG_TIME));
	SetListCtrlColumn(m_lstTimeHeatMap, n_LTHMC_ChannelNo, GetTextEx(IDS_CONFIG_FTP_CHANNEL));
	SetListCtrlColumn(m_lstTimeHeatMap, n_LTHMC_LogContent, GetTextEx(IDS_CFG_LOG_DVR_LOGCONTENT));

	int iTempIndex = m_cboPrecisionType.GetCurSel();
	m_cboPrecisionType.ResetContent();
	m_cboPrecisionType.SetItemData(m_cboPrecisionType.AddString(GetTextEx(IDS_CONFIG_ADV_INTERVALHOUR)), REPORT_QUERY_PRECISION_HOUR);
	m_cboPrecisionType.SetItemData(m_cboPrecisionType.AddString(GetTextEx(IDS_CONFIG_DAY)), REPORT_QUERY_PRECISION_DAY);
	m_cboPrecisionType.SetItemData(m_cboPrecisionType.AddString(GetTextEx(IDS_VCA_MONTH)), REPORT_QUERY_PRECISION_MONTH);
	m_cboPrecisionType.SetItemData(m_cboPrecisionType.AddString(GetTextEx(IDS_VCA_YEAR)), REPORT_QUERY_PRECISION_YEAR);
	m_cboPrecisionType.SetItemData(m_cboPrecisionType.AddString(GetTextEx(IDS_TEN_MINUTES)), REPORT_QUERY_PRECISION_TEN_MINUTES);
	m_cboPrecisionType.SetCurSel((iTempIndex > 0) ? iTempIndex : 0);
	
	iTempIndex = m_cboReportQueryType.GetCurSel();
	m_cboReportQueryType.ResetContent();
	m_cboReportQueryType.SetItemData(m_cboReportQueryType.AddString(GetTextEx(IDS_TIME_HEAT_MAP)), REPORT_QUERY_TYPE_TIME);
	m_cboReportQueryType.SetItemData(m_cboReportQueryType.AddString(GetTextEx(IDS_POWER_ENV_DEBUG_TEMPERATURE)), REPORT_QUERY_TYPE_TEMPERATURE);
	m_cboReportQueryType.SetItemData(m_cboReportQueryType.AddString(GetTextEx(IDS_POWER_ENV_DEBUG_HUMIDITY)), REPORT_QUERY_TYPE_HUMIDNESS);
	iTempIndex = (iTempIndex < 0 || iTempIndex >= m_cboReportQueryType.GetCount()) ? 0 : iTempIndex;
	m_cboReportQueryType.SetCurSel(iTempIndex);
	OnCbnSelchangeCboReportQuerryType();

	SetDlgItemTextEx(IDC_GRP_TIME_HEAT_MAP, IDS_REPORT_QUERY);
	SetDlgItemTextEx(IDC_STC_REPORT_TYPE, IDS_REPORT_QUERY);
	SetDlgItemTextEx(IDC_GRP_SPACE_HEAT_MAP, IDS_SPACE_HEAT_MAP);
	SetDlgItemTextEx(IDC_STC_TIMEMAP_BEGIN_TIME, IDS_CFG_3G_NORMAL_STARTTIME);
	SetDlgItemTextEx(IDC_STC_TIMEMAP_END_TIME, IDS_PLAYBACK_DOWNLOAD_ENDTIME);
	SetDlgItemTextEx(IDC_STC_PRECISION_TYPE, IDS_PRECISION_TYPE);
	SetDlgItemTextEx(IDC_BTN_QUERY_TIME_MAP, IDS_PLAYBACK_QUERY);
	SetDlgItemTextEx(IDC_STC_SPACEMAP_BEGIN_TIME, IDS_CFG_3G_NORMAL_STARTTIME);
	SetDlgItemTextEx(IDC_STC_SPACEMAP_END_TIME, IDS_PLAYBACK_DOWNLOAD_ENDTIME);
	SetDlgItemTextEx(IDC_BTN_QUERY_SPACE_MAP, IDS_PLAYBACK_QUERY);
}

void CLS_FECHeatMap::OnCbnSelchangeCboReportQuerryType()
{
	m_lstTimeHeatMap.DeleteAllItems();

	int iQueryType = m_cboReportQueryType.GetItemData(m_cboReportQueryType.GetCurSel());

	CString cstrLogContent;
	switch (iQueryType)
	{
	case REPORT_QUERY_TYPE_TIME:
		cstrLogContent = GetTextEx(IDS_CONFIG_DH_SUSTAIN_TIME);
		break;
	case REPORT_QUERY_TYPE_TEMPERATURE:
		cstrLogContent = GetTextEx(IDS_POWER_ENV_DEBUG_TEMPERATURE) + _T("(℃)");
		break;
	case REPORT_QUERY_TYPE_HUMIDNESS:
		cstrLogContent = GetTextEx(IDS_CONFIG_DH_HUMIDITY) + _T("(RH)");
		break;
	default:
		cstrLogContent = GetTextEx(IDS_CFG_LOG_DVR_LOGCONTENT);
	}
	SetListCtrlColumn(m_lstTimeHeatMap, n_LTHMC_LogContent, cstrLogContent);
}

void CLS_FECHeatMap::OnBnClickedBtnQueryTimeMap()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FECHeatMap::QueryTimeMap] Illegal LogonID(%d)", m_iLogonID);
		return;
	}

	m_lstTimeHeatMap.DeleteAllItems();
	
	ReportQuery tReportQuery = {0};
	tReportQuery.iSize = sizeof(ReportQuery);
	tReportQuery.iReportType = m_cboReportQueryType.GetItemData(m_cboReportQueryType.GetCurSel());
	tReportQuery.iReportPre = (int)m_cboPrecisionType.GetItemData(m_cboPrecisionType.GetCurSel());

	CTime timeBeginTime;
	m_dtimeTimeMapBeginTime.GetTime(timeBeginTime);
	tReportQuery.tBeginTime.iYear = timeBeginTime.GetYear();
	tReportQuery.tBeginTime.iMonth = timeBeginTime.GetMonth();
	tReportQuery.tBeginTime.iDay = timeBeginTime.GetDay();
	tReportQuery.tBeginTime.iHour = timeBeginTime.GetHour();
	tReportQuery.tBeginTime.iMinute = timeBeginTime.GetMinute();
	tReportQuery.tBeginTime.iSecond = timeBeginTime.GetSecond();

	CTime timeEndTime;
	m_dtimeTimeMapEndTime.GetTime(timeEndTime);
	tReportQuery.tEndTime.iYear = timeEndTime.GetYear();
	tReportQuery.tEndTime.iMonth = timeEndTime.GetMonth();
	tReportQuery.tEndTime.iDay = timeEndTime.GetDay();
	tReportQuery.tEndTime.iHour = timeEndTime.GetHour();
	tReportQuery.tEndTime.iMinute = timeEndTime.GetMinute();
	tReportQuery.tEndTime.iSecond = timeEndTime.GetSecond();

	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_REPORT_QUERY, m_iChannelNo, (void*)&tReportQuery, sizeof(ReportQuery));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SendCommand ReportQuery(%d,%d)",m_iLogonID, m_iChannelNo);
		goto EXIT_FUNC;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SendCommand ReportQuery(%d,%d)",m_iLogonID, m_iChannelNo);
	}

EXIT_FUNC:
	return;
}

void CLS_FECHeatMap::UpdateReportQueryMap(ReportQueryResult* _ptInfo)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FECHeatMap::UpdateTimeHeatMap] Illegal LogonID(%d)", m_iLogonID);
		return;
	}

	ReportQueryResult tReportQueryResult = {0};
	tReportQueryResult.iSize = sizeof(ReportQueryResult);

	//如果直接从回调中可以拿到数据就不再调接口取数据
	if (NULL != _ptInfo && _ptInfo->iSize > 0)
	{
		int iCpySize = min(_ptInfo->iSize, tReportQueryResult.iSize);
		memcpy(&tReportQueryResult, _ptInfo, iCpySize);
		goto EXIT_UPDATE_INTERFACE;
	}

	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_REPORT_QUERY, m_iChannelNo, &tReportQueryResult, sizeof(ReportQueryResult));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FECHeatMap::UpdateTimeHeatMap] ReportQueryResult failed !");
		goto EXIT_FUNC;
	}

EXIT_UPDATE_INTERFACE:
	int iCurQueryType = m_cboReportQueryType.GetItemData(m_cboReportQueryType.GetCurSel());
	if (iCurQueryType != tReportQueryResult.iReportType)
	{
		AddLog(LOG_TYPE_MSG, "", "[CLS_FECHeatMap::UpdateTimeHeatMap] Illegal Msg Type (%d),CurType(%d)!", tReportQueryResult.iReportType, iCurQueryType);
		goto EXIT_FUNC;
	}
	
	int iInfoNum = min(tReportQueryResult.iInfoNum, MAX_REPORT_QUERY_INFO_NUM);
	for (int iIndex = 0; iIndex < iInfoNum; iIndex++)
	{
		InsertListItemText(iIndex, tReportQueryResult.tReportQueryInfo[iIndex]);
	}

EXIT_FUNC:
	return;
}

void CLS_FECHeatMap::OnBnClickedBtnQuerySpaceMap()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FECHeatMap::QuerySpaceMap] Illegal LogonID(%d)", m_iLogonID);
		return;
	}

	HeatMapGet tHeatMapGet = {0};
	tHeatMapGet.iSize = sizeof(HeatMapGet);

	CTime timeBeginTime;
	m_dtimeSpaceMapBeginTime.GetTime(timeBeginTime);
	tHeatMapGet.tBeginTime.iYear = timeBeginTime.GetYear();
	tHeatMapGet.tBeginTime.iMonth = timeBeginTime.GetMonth();
	tHeatMapGet.tBeginTime.iDay = timeBeginTime.GetDay();
	tHeatMapGet.tBeginTime.iHour = timeBeginTime.GetHour();
	tHeatMapGet.tBeginTime.iMinute = timeBeginTime.GetMinute();
	tHeatMapGet.tBeginTime.iSecond = timeBeginTime.GetSecond();

	CTime timeEndTime;
	m_dtimeSpaceMapEndTime.GetTime(timeEndTime);
	tHeatMapGet.tEndTime.iYear = timeEndTime.GetYear();
	tHeatMapGet.tEndTime.iMonth = timeEndTime.GetMonth();
	tHeatMapGet.tEndTime.iDay = timeEndTime.GetDay();
	tHeatMapGet.tEndTime.iHour = timeEndTime.GetHour();
	tHeatMapGet.tEndTime.iMinute = timeEndTime.GetMinute();
	tHeatMapGet.tEndTime.iSecond = timeEndTime.GetSecond();

	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_HEATMAP_GET, m_iChannelNo, (void*)&tHeatMapGet, sizeof(HeatMapGet));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SendCommand HeatMapGet(%d,%d)",m_iLogonID, m_iChannelNo);
		goto EXIT_FUNC;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SendCommand HeatMapGet(%d,%d)",m_iLogonID, m_iChannelNo);
	}

EXIT_FUNC:
	return;
}

void CLS_FECHeatMap::UpdateSpaceHeatMap()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FECHeatMap::UpdateSpaceHeatMap] Illegal LogonID(%d)", m_iLogonID);
		return;
	}

	HeatMapGetResult tHeatMapGetResult = {0};
	tHeatMapGetResult.iSize = sizeof(HeatMapGetResult);

	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_HEATMAP_GET, m_iChannelNo, &tHeatMapGetResult, sizeof(HeatMapGetResult));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FECHeatMap::UpdateTimeHeatMap] ReportQueryResult failed !");
		goto EXIT_FUNC;
	}

	SetDlgItemText(IDC_EDT_SPACE_MAP_URL, tHeatMapGetResult.cUrl);
EXIT_FUNC:
	return;
}

