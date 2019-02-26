// ITSBayonetData.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ITSBayonetData.h"

#define SUB_FUNC_TYPE_ITS				1	 //ITS business
#define SUB_FUNC_TYPE_ITS_SNAPTYPE		2    // 抓拍类型
#define SUB_FUNC_TYPE_ITS_CARTYPE		3    // 车辆类型
#define SUB_FUNC_TYPE_ITS_DIRECTION		4    // 行驶方向
#define SUB_FUNC_TYPE_ITS_CARCOLOR		5    // 车身颜色
#define SUB_FUNC_TYPE_ITS_PICNAME		7    // 图片名称格式
#define SUB_FUNC_TYPE_ITS_VERSION		8    // 平台版本
#define SUB_FUNC_TYPE_ITS_CARBRAND_MIN	10    // 车辆品牌
#define SUB_FUNC_TYPE_ITS_CARBRAND_MAX	30    // 车辆品牌   使用的左闭右开区间

enum n_ITSDataRecord
{
	n_ITSDataRecordCaptureTime,		//抓拍时间
	n_ITSDataRecordRoad,	        //路口/地点
	n_ITSDataRecordChannel,		    //车道检测区域
	n_ITSDataRecordDirection,	    //行驶方向
	n_ITSDataRecordPlate,	        //车牌号码
	n_ITSDataRecordCarType,         //车辆类型
	n_ITSDataRecordCarLogo,         //车辆品牌
	n_ITSDataRecordCarColor,        //车身颜色
	n_ITSDataRecordUploadStatus,    //上传状态
};

CString GetCarDirectionString(int _iDirection)
{
	CString cstr;
	CString cstrCarDirection[] = {GetTextEx(IDS_ITS_STAR_NVR_EAST_TO_WEST), GetTextEx(IDS_ITS_STAR_NVR_WEST_TO_EAST)
		, GetTextEx(IDS_ITS_STAR_NVR_SOUTH_TO_NORTH), GetTextEx(IDS_ITS_STAR_NVR_COME_IN), GetTextEx(IDS_ITS_STAR_NVR_GO_AWAY)};
	if (_iDirection >= 0 && _iDirection < sizeof(cstrCarDirection)/sizeof(CString))
	{
		cstr = cstrCarDirection[_iDirection];
	}
	return cstr;
}

CString GetCarTypeString(int _iCarType)
{
	CString cstr;
	CString cstrCarType[] = {GetTextEx(IDS_UNKNOW_CAR_TYPE), 
		GetTextEx(IDS_MUNI_COACH), 
		GetTextEx(IDS_SAMLL_CAR), 
		GetTextEx(IDS_MICROBUS), 
		GetTextEx(IDS_BIG_TRUCK), 
		GetTextEx(IDS_SMALL_TRUCK), 
		GetTextEx(IDS_ITS_ER_SAN_LUN_CHE), 
		GetTextEx(IDS_PEDESTRIAN)};
	if (_iCarType >= 0 && _iCarType < sizeof(cstrCarType)/sizeof(CString))
	{
		cstr = cstrCarType[_iCarType];
	}
	return cstr;
}

CString GetCarBrandString(int _iCarType)
{
	CString cstr;
	//1:大众   2:奥迪   3:丰田   4:本田     5:奔驰    6:雪佛兰   7:奇瑞      8:别克      9:长城     10:现代
	//	11:日产  12:福特  13:宝马  14:雪铁龙  15:起亚   16:铃木    17:马自达   18:比亚迪 20:标致
	//	21:长安  22:雷克萨斯 23:中华 24:斯柯达 25:海马 26:夏利 27:五菱 28:东风 29:哈飞 30:一汽
	//	31:宝骏  32:帝豪  33:名爵 34:东南 35:皇冠 36:金杯 37:三菱 38:荣威 39:吉利 40:英伦
	//	41:全球鹰 42:哈飞赛豹 43:长丰 44:威旺 45:北京 46:新凯 47:广汽吉奥 48:玛莎拉蒂 49:罗孚 50:奥斯丁
	//	51:玛柯斯 52:克莱斯勒道奇 53:克莱斯勒顺风 54:通用庞蒂克 55:捷豹 56:奥兹曙光 57:阿尔法 58:兰博基尼 59:布加迪 60:林肯
	//	61:法拉利 62:昌河 63:菲亚特 64:福田 65:讴歌 66:莲花 67:华普 68:红旗 69:瑞麒 70:奔腾
	//	71:威麟 72:众泰 73:力帆 74:北京吉普 75:中兴 76:开瑞 77:路虎 78:迈巴赫 79:雷诺 80:欧宝
	//	81:野马 82:JEEP  83:依维柯  84:英菲尼迪 85:斯巴鲁 86:阿斯顿马丁 87:安凯 88:保时捷 89:宾利 90:福迪
	//	91:福汽启腾 92:吉姆斯 93:观致 94:广汽传祺 95:双龙 96:海格 97:悍马 98:华泰 99:黄海 100:九龙
	//	101:理念 102:SMART 103:陆风 104:纳智捷 105:欧朗 106:启辰
	//	999:未知
	CString cstrCarBrand[] = {"","大众","奥迪","丰田","本田","奔驰","雪佛兰","奇瑞","别克","长城","现代"};
	if (_iCarType >= 0 && _iCarType < sizeof(cstrCarBrand)/sizeof(CString))
	{
		cstr = cstrCarBrand[_iCarType];
	}
	return cstr;
}

#define DATAQUERY_UPLOAD_OK               1
#define DATAQUERY_UPLOAD_NO               0
CString GetUploadStatusString(int _iUploadStatus)
{
	CString strUpdataStatus;
	switch(_iUploadStatus)
	{
	case DATAQUERY_UPLOAD_OK:
		strUpdataStatus =  GetTextEx(IDS_ITS_UPLOAD_OK);
		break;
	case DATAQUERY_UPLOAD_NO:
		strUpdataStatus =  GetTextEx(IDS_ITS_NO_UPLOAD);
		break;
	default:
		strUpdataStatus =  GetTextEx(IDS_ITS_NO_UPLOAD);
		break;
	}
	return strUpdataStatus;
}

CString GetCarColorString(int _iCarColor)
{
	CString cstr;
	CString cstrCarColor[] = {"", GetTextEx(IDS_VCA_COL_WHITE), GetTextEx(IDS_VCA_COL_GRAY), GetTextEx(IDS_VCA_COL_YELLOW), GetTextEx(IDS_VCA_COL_PINK)
		, GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_GREEN), GetTextEx(IDS_VCA_COL_BLUE)
		, GetTextEx(IDS_VCA_COL_BROWN), GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_SILVER), GetTextEx(IDS_VCA_COL_CYAN)};
	if (_iCarColor >= 0 && _iCarColor < sizeof(cstrCarColor)/sizeof(CString))
	{
		cstr = cstrCarColor[_iCarColor];
	}
	return cstr;
}

int SplitStrToVector(std::string _strSource, char _cSplit, std::vector<string> &_vecResult)
{
	_vecResult.clear();

	int iRet = -1;
	int iStart = 0;
	int iEnd = 0; 
	iStart = 0;
	iEnd = (int)_strSource.find_first_of(_cSplit,iStart);
	while(( std::string::npos != iStart) && (std::string::npos != iEnd))
	{
		if(iStart == iEnd)
			break;
		_vecResult.push_back(_strSource.substr(iStart, iEnd - iStart));
		iStart = iEnd + 1;
		iEnd = (int)_strSource.find_first_of(_cSplit, iStart); 
	}

	if(iStart < _strSource.length())
	{
		_vecResult.push_back(_strSource.substr(iStart, _strSource.length()));
	}

	iRet = (int)_vecResult.size();

	return iRet;
}

int GetDataDictionary(int _iLogonID, int _iChanelNO, int _iDataType, std::vector<pair<int,CString>> &_vecResult)
{
	int iRet = RET_FAILED;
	std::vector<string> vecItem;
	std::vector<string> vecOneData;
	string strParam;
	FuncAbilityLevel stFuncAbilityLevel = {0};
	stFuncAbilityLevel.iSize = sizeof(FuncAbilityLevel);
	stFuncAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_ITS;
	stFuncAbilityLevel.iSubFuncType = _iDataType;
	int iReturnByte = -1;
	iRet = NetClient_GetDevConfig(_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, _iChanelNO,
		&stFuncAbilityLevel, sizeof(stFuncAbilityLevel), 
		&iReturnByte);
	if (RET_SUCCESS == iRet)
	{
		strParam = stFuncAbilityLevel.cParam;		
	}
	else
	{
		goto END;
	}

	_vecResult.clear();
	// 将数据词典拆分为多条记录。 1：内容，2：内容，3：内容
	int iCount = SplitStrToVector(strParam, ',', vecItem);
	if(iCount <= 0)
	{
		goto END;
	}
	for (int i = 0; i < vecItem.size(); i++)
	{
		std::pair<int,CString> pairOne;
		int iSplitCount = SplitStrToVector(vecItem[i], ':', vecOneData);
		if (iSplitCount > 0 && 2 == vecOneData.size())
		{
			pairOne.first  = atoi(vecOneData[0].c_str());
			pairOne.second.Format("%s", vecOneData[1].c_str());
			_vecResult.push_back(pairOne);
		}
		else
		{
			break;
		}
	}

	iRet = RET_SUCCESS;

END:
	return iRet;
}

// CLS_ITSBayonetData dialog

IMPLEMENT_DYNAMIC(CLS_ITSBayonetData, CDialog)

CLS_ITSBayonetData::CLS_ITSBayonetData(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSBayonetData::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	memset(m_tItsCross, 0, MAX_ITS_CROSS_COUNT * sizeof(ITSCrossInfo));
	memset(m_tItsLane, 0, MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT * sizeof(ITSLaneInfo));
	memset(m_tRecordArray, 0, sizeof(m_tRecordArray));
	m_iSelectIndex = 0;

	m_iTotalRecordCount = 0;   // 总查询条数
	m_iTotalPageCount  = 0;   // 界面分成m_iTotalPageCount页显示
	m_iCurrentPageNo   = 0;   // 界面显示的当前页码
	m_iBeginIndex = 0;
	m_iEndIndex = MAX_ITS_QUERYDATA_PAGE_SIZE;
}

CLS_ITSBayonetData::~CLS_ITSBayonetData()
{
}

void CLS_ITSBayonetData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATE_DATAQUERY_START_DAY, m_dtpBeginDate);
	DDX_Control(pDX, IDC_TIME_DATAQUERY_START_HOUR, m_dtpBeginTime);
	DDX_Control(pDX, IDC_DATE_DATAQUERY_END_DAY, m_dtpEndDate);
	DDX_Control(pDX, IDC_TIME_DATAQUERY_END_HOUR, m_dtpEndTime);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_UPLOADSTATE, m_cboUploadState);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_CROSS, m_cboCross);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_LANE, m_cboLane);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_CARTYPE, m_cboQueryCarType);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_CARBRAND, m_cboQueryCarBrand);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_DIRECTION, m_cboDirection);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_CARCOLOR, m_cboQueryCarColor);
	DDX_Control(pDX, IDC_CBO_DATAQUERY_PLATE, m_cboQueryPlate);
	DDX_Control(pDX, IDC_EDT_DATAQUERY_CARPLATENUM, m_edtQueryPlate);
	DDX_Control(pDX, IDC_EDIT_ITS_CARPLATE_MODIFY, m_edtModifyPlate);
	DDX_Control(pDX, IDC_CBO_MODIFY_CARTYPE, m_cboModifyCarType);
	DDX_Control(pDX, IDC_CBO_MODIFY_CARBRAND, m_cboModifyCarBrand);
	DDX_Control(pDX, IDC_CBO_MODIFY_CARCOLOR, m_cboModifyCarColor);
	DDX_Control(pDX, IDC_CBO_MODIFY_ILLEGALTYPE, m_cboModifyIllegalType);
	DDX_Control(pDX, IDC_EDIT_ITS_MODIFY_PICNAME, m_edtModifyPicName);
	DDX_Control(pDX, IDC_LST_DATAQUERY_RECORD, m_lstQueryRecord);
	DDX_Control(pDX, IDC_CBO_QUERY_ILLEGALTYPE, m_cboQueryIllegalType);
}


BEGIN_MESSAGE_MAP(CLS_ITSBayonetData, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ITS_QUERY_BAYONET_DATA, &CLS_ITSBayonetData::OnBnClickedButtonItsQueryBayonetData)
	ON_BN_CLICKED(IDC_BTN_DATAQUERY_FIRSTPAGE, &CLS_ITSBayonetData::OnBnClickedBtnDataqueryFirstpage)
	ON_BN_CLICKED(IDC_BTN_DATAQUERY_PREPAGE, &CLS_ITSBayonetData::OnBnClickedBtnDataqueryPrepage)
	ON_BN_CLICKED(IDC_BTN_DATAQUERY_NEXTPAGE, &CLS_ITSBayonetData::OnBnClickedBtnDataqueryNextpage)
	ON_BN_CLICKED(IDC_BTN_DATAQUERY_ENDPAGE, &CLS_ITSBayonetData::OnBnClickedBtnDataqueryEndpage)
	ON_BN_CLICKED(IDC_BUTTON_ITS_MODIFY_BAYONET_DATA, &CLS_ITSBayonetData::OnBnClickedButtonItsModifyBayonetData)
	ON_BN_CLICKED(IDC_BUTTON_ITS_QUERY_TOTAL_COUNT, &CLS_ITSBayonetData::OnBnClickedButtonItsQueryTotalCount)
	ON_CBN_SELCHANGE(IDC_CBO_DATAQUERY_PLATE, &CLS_ITSBayonetData::OnCbnSelchangeCboDataqueryPlate)
	ON_NOTIFY(NM_CLICK, IDC_LST_DATAQUERY_RECORD, &CLS_ITSBayonetData::OnNMClickLstDataqueryRecord)
	ON_BN_CLICKED(IDC_BUTTON_ITS_DELETE_BAYONET_DATA, &CLS_ITSBayonetData::OnBnClickedButtonItsDeleteBayonetData)
END_MESSAGE_MAP()


// CLS_ITSBayonetData message handlers

BOOL CLS_ITSBayonetData::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	//初始化地点list
	m_lstQueryRecord.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordCaptureTime, GetTextEx(IDS_CAO_TIME), LVCFMT_CENTER, 130);//抓拍时间
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordRoad, GetTextEx(IDS_ROAD_ID), LVCFMT_CENTER, 130);//路口/地点
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordChannel, GetTextEx(IDS_ITS_STAR_NVR_CHECK_REGION), LVCFMT_CENTER, 60);//车道检测区域
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordDirection, GetTextEx(IDS_ITS_STAR_NVR_TRAVEL_DIRECTION), LVCFMT_CENTER, 120);//行驶方向
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordPlate, GetTextEx(IDS_CONFIG_ITS_LICENSE), LVCFMT_CENTER, 120);//车牌号码
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordCarType, GetTextEx(IDS_ITS_CAR_TYPE), LVCFMT_CENTER, 160);//车辆类型
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordCarLogo, GetTextEx(IDS_ITS_CAR_BRAND), LVCFMT_CENTER, 60);//车辆品牌
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordCarColor, GetTextEx(IDS_CONFIG_ITS_OSD_CARCOLOR), LVCFMT_CENTER, 60);//车身颜色
	m_lstQueryRecord.InsertColumn(n_ITSDataRecordUploadStatus, GetTextEx(IDS_ITS_UPLOAD_STATE), LVCFMT_CENTER, 60);//上传状态

	CTime timeNow = CTime::GetCurrentTime();
	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 0, 0, 0);
	m_dtpBeginDate.SetFormat(_T("yyyy-MM-dd"));
	m_dtpBeginDate.SetTime(&timeNow);
	m_dtpBeginTime.SetFormat(_T("HH:mm:ss"));
	m_dtpBeginTime.SetTime(&timeNow);

	m_dtpEndDate.SetFormat(_T("yyyy-MM-dd"));
	m_dtpEndDate.SetTime(&timeNow);
	m_dtpEndTime.SetFormat(_T("HH:mm:ss"));
	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 23, 59, 59);
	m_dtpEndTime.SetTime(&timeNow);

	CString cstrCarPlate[] = {"川","鄂","赣","甘","挂","桂","贵","黑","沪","冀",
		"吉","晋","津","京","警","军","空","辽","鲁","蒙",
		"闽","宁","黔","青","琼","陕","蜀","苏","台","皖",
		"湘","新","渝","豫","云","藏","浙"};
	m_cboQueryPlate.ResetContent();
	for (int i= 0 ; i < sizeof(cstrCarPlate)/sizeof(CString); ++i)
	{
		m_cboQueryPlate.AddString(cstrCarPlate[i]);
	}
	m_cboQueryPlate.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

#define _DATA_DICTIONARY_
void CLS_ITSBayonetData::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	UI_UpdateStaticDialogText();
	GetCrossInfo();
	GetLaneInfo();

#ifdef _DATA_DICTIONARY_
	InitIllegalTypeCbo();
	InitCarTypeCbo();
	InitCarBrandCbo();
	InitCarColorCbo();
	InitCarDirectionCbo();
#else
	UI_UpdateQueryDialogText();
	UI_UpdateModifyDialogText();
#endif	
}

void CLS_ITSBayonetData::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateStaticDialogText();
	UI_UpdateQueryDialogText();
	UI_UpdateModifyDialogText();
	ShowQueryCountToUser(_iLanguage);
}

void CLS_ITSBayonetData::UI_UpdateStaticDialogText()
{
	SetDlgItemTextEx(IDC_STC_DATAQUERY_START, IDS_CFG_3G_NORMAL_STARTTIME);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_END, IDS_CONFIG_HOLIDAY_END_TIME);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_UPLOADSTATE, IDS_ITS_UPLOAD_STATE);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_CROSS, IDS_ROAD_ID);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_LANE, IDS_ITS_STAR_NVR_CHECK_REGION);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_CARTYPE, IDS_ITS_CAR_TYPE);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_CARBRAND, IDS_ITS_CAR_BRAND);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_DIRECTION, IDS_ITS_STAR_NVR_TRAVEL_DIRECTION);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_CARCOLOR, IDS_CONFIG_ITS_OSD_CARCOLOR);
	SetDlgItemTextEx(IDC_STC_DATAQUERY_CARPLATE, IDS_CONFIG_ITS_LICENSE);
	SetDlgItemTextEx(IDC_STC_QUERY_ILLEGALTYPE, IDS_CONFIG_ITS_OSD_ILLEGALTYPE);
	SetDlgItemTextEx(IDC_BUTTON_ITS_QUERY_BAYONET_DATA, IDS_CFG_LOG_DVR_QUERY);
	SetDlgItemTextEx(IDC_BTN_DATAQUERY_FIRSTPAGE, IDS_CFG_LOG_DVR_FIRSTPAGE);
	SetDlgItemTextEx(IDC_BTN_DATAQUERY_PREPAGE, IDS_CFG_LOG_DVR_PREPAGE);
	SetDlgItemTextEx(IDC_BTN_DATAQUERY_NEXTPAGE, IDS_CFG_LOG_DVR_NEXTPAGE);
	SetDlgItemTextEx(IDC_BTN_DATAQUERY_ENDPAGE, IDS_CFG_LOG_DVR_LASTPAGE);
	SetDlgItemTextEx(IDC_BUTTON_ITS_QUERY_TOTAL_COUNT, IDS_ITS_QUERY_TOTAL_COUNT);

	SetDlgItemTextEx(IDC_STC_DATAQUERY_CARPLATE_MODIFY, IDS_CONFIG_ITS_LICENSE);
	SetDlgItemTextEx(IDC_STC_DATADETAIL_PICNAME, IDS_ITS_PICTURE_NAME);
	SetDlgItemTextEx(IDC_STC_MODIFY_CARTYPE, IDS_ITS_CAR_TYPE);
	SetDlgItemTextEx(IDC_STC_MODIFY_CARBRAND, IDS_ITS_CAR_BRAND);
	SetDlgItemTextEx(IDC_STC_MODIFY_CARCOLOR, IDS_CONFIG_ITS_OSD_CARCOLOR);
	SetDlgItemTextEx(IDC_STC_MODIFY_ILLEGALTYPE, IDS_CONFIG_ITS_OSD_ILLEGALTYPE);
	SetDlgItemTextEx(IDC_BUTTON_ITS_MODIFY_BAYONET_DATA, IDS_MODIFY);
	SetDlgItemTextEx(IDC_BUTTON_ITS_DELETE_BAYONET_DATA, IDS_DELETE);

	m_cboUploadState.ResetContent();
	m_cboUploadState.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboUploadState.SetItemData(0, PARAM_CHANNEL_ALL);
	m_cboUploadState.InsertString(1, GetTextEx(IDS_ITS_UPLOAD_OK));
	m_cboUploadState.SetItemData(1, 0);
	m_cboUploadState.InsertString(2, GetTextEx(IDS_ITS_NO_UPLOAD));
	m_cboUploadState.SetItemData(2, 1);
	m_cboUploadState.SetCurSel(0);
}

void CLS_ITSBayonetData::UI_UpdateQueryDialogText()
{
	m_cboDirection.ResetContent();
	m_cboDirection.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboDirection.SetItemData(0, PARAM_CHANNEL_ALL);
	m_cboDirection.InsertString(1, GetTextEx(IDS_ITS_STAR_NVR_EAST_TO_WEST));
	m_cboDirection.SetItemData(1, 0);
	m_cboDirection.InsertString(2, GetTextEx(IDS_ITS_STAR_NVR_WEST_TO_EAST));
	m_cboDirection.SetItemData(2, 1);
	m_cboDirection.InsertString(3, GetTextEx(IDS_ITS_STAR_NVR_SOUTH_TO_NORTH));
	m_cboDirection.SetItemData(3, 2);
	m_cboDirection.InsertString(4, GetTextEx(IDS_ITS_STAR_NVR_NORTH_TO_SOUTH));
	m_cboDirection.SetItemData(4, 3);
	m_cboDirection.InsertString(5, GetTextEx(IDS_ITS_STAR_NVR_COME_IN));
	m_cboDirection.SetItemData(5, 4);
	m_cboDirection.InsertString(6, GetTextEx(IDS_ITS_STAR_NVR_GO_AWAY));
	m_cboDirection.SetItemData(6, 5);
	m_cboDirection.SetCurSel(0);

	m_cboQueryCarType.ResetContent();
	m_cboQueryCarType.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));//
	m_cboQueryCarType.SetItemData(0, PARAM_CHANNEL_ALL);
	m_cboQueryCarType.InsertString(1, GetTextEx(IDS_UNKNOW_CAR_TYPE));//未知车型
	m_cboQueryCarType.SetItemData(1, 0);
	m_cboQueryCarType.InsertString(2, GetTextEx(IDS_MUNI_COACH));//公交或大客车
	m_cboQueryCarType.SetItemData(2, 1);
	m_cboQueryCarType.InsertString(3, GetTextEx(IDS_SAMLL_CAR));//小汽车
	m_cboQueryCarType.SetItemData(3, 2);
	m_cboQueryCarType.InsertString(4, GetTextEx(IDS_MICROBUS));//面包车
	m_cboQueryCarType.SetItemData(4, 4);
	m_cboQueryCarType.InsertString(5, GetTextEx(IDS_BIG_TRUCK));//大货车
	m_cboQueryCarType.SetItemData(5, 5);
	m_cboQueryCarType.InsertString(6, GetTextEx(IDS_SMALL_TRUCK));//小货车
	m_cboQueryCarType.SetItemData(6, 6);
	m_cboQueryCarType.InsertString(7, GetTextEx(IDS_ITS_ER_SAN_LUN_CHE));//二、三轮车
	m_cboQueryCarType.SetItemData(7, 7);
	m_cboQueryCarType.InsertString(8, GetTextEx(IDS_PEDESTRIAN));//行人
	m_cboQueryCarType.SetItemData(8, 8);
	m_cboQueryCarType.SetCurSel(0);

	m_cboQueryCarBrand.ResetContent();
	m_cboQueryCarBrand.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboQueryCarBrand.SetItemData(0, PARAM_CHANNEL_ALL);
	m_cboQueryCarBrand.InsertString(1, "大众");
	m_cboQueryCarBrand.SetItemData(1, 1);
	m_cboQueryCarBrand.InsertString(2, "奥迪");
	m_cboQueryCarBrand.SetItemData(2, 2);
	m_cboQueryCarBrand.InsertString(3, "丰田");
	m_cboQueryCarBrand.SetItemData(3, 3);
	m_cboQueryCarBrand.InsertString(4, "本田");
	m_cboQueryCarBrand.SetItemData(4, 4);
	m_cboQueryCarBrand.InsertString(5, "奔驰");
	m_cboQueryCarBrand.SetItemData(5, 5);
	m_cboQueryCarBrand.InsertString(6, "雪佛兰");
	m_cboQueryCarBrand.SetItemData(6, 6);
	m_cboQueryCarBrand.InsertString(7, "奇瑞");
	m_cboQueryCarBrand.SetItemData(7, 7);
	m_cboQueryCarBrand.InsertString(8, "别克");
	m_cboQueryCarBrand.SetItemData(8, 8);
	m_cboQueryCarBrand.InsertString(9, "长城");
	m_cboQueryCarBrand.SetItemData(9, 9);
	m_cboQueryCarBrand.InsertString(10, "现代");
	m_cboQueryCarBrand.SetItemData(10, 10);
	m_cboQueryCarBrand.SetCurSel(0);

	m_cboQueryCarColor.ResetContent();
	m_cboQueryCarColor.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboQueryCarColor.SetItemData(0, PARAM_CHANNEL_ALL);
	m_cboQueryCarColor.InsertString(1, GetTextEx(IDS_VCA_COL_WHITE));
	m_cboQueryCarColor.SetItemData(1, 1);
	m_cboQueryCarColor.InsertString(2, GetTextEx(IDS_VCA_COL_GRAY));
	m_cboQueryCarColor.SetItemData(2, 2);
	m_cboQueryCarColor.InsertString(3, GetTextEx(IDS_VCA_COL_YELLOW));
	m_cboQueryCarColor.SetItemData(3, 3);
	m_cboQueryCarColor.InsertString(4, GetTextEx(IDS_VCA_COL_PINK));
	m_cboQueryCarColor.SetItemData(4, 4);
	m_cboQueryCarColor.InsertString(5, GetTextEx(IDS_VCA_COL_RED));
	m_cboQueryCarColor.SetItemData(5, 5);
	m_cboQueryCarColor.InsertString(6, GetTextEx(IDS_VCA_COL_MAGENTA));
	m_cboQueryCarColor.SetItemData(6, 6);
	m_cboQueryCarColor.InsertString(7, GetTextEx(IDS_VCA_COL_GREEN));
	m_cboQueryCarColor.SetItemData(7, 7);
	m_cboQueryCarColor.InsertString(8, GetTextEx(IDS_VCA_COL_BLUE));
	m_cboQueryCarColor.SetItemData(8, 8);
	m_cboQueryCarColor.InsertString(9, GetTextEx(IDS_VCA_COL_BROWN));
	m_cboQueryCarColor.SetItemData(9, 9);
	m_cboQueryCarColor.InsertString(10, GetTextEx(IDS_VCA_COL_BLACK));
	m_cboQueryCarColor.SetItemData(10, 10);
	m_cboQueryCarColor.InsertString(11, GetTextEx(IDS_VCA_COL_SILVER));
	m_cboQueryCarColor.SetItemData(11, 11);
	m_cboQueryCarColor.InsertString(12, GetTextEx(IDS_VCA_COL_CYAN));
	m_cboQueryCarColor.SetItemData(12, 12);
	m_cboQueryCarColor.InsertString(13, GetTextEx(IDS_UNKNOW_CAR_TYPE));
	m_cboQueryCarColor.SetItemData(13, 26);
	m_cboQueryCarColor.SetCurSel(0);

	m_cboQueryIllegalType.ResetContent();
	m_cboQueryIllegalType.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboQueryIllegalType.SetItemData(0, PARAM_CHANNEL_ALL);
	m_cboQueryIllegalType.SetCurSel(0);
}

void CLS_ITSBayonetData::UI_UpdateModifyDialogText()
{
	m_cboModifyCarType.ResetContent();
	m_cboModifyCarType.InsertString(0, GetTextEx(IDS_UNKNOW_CAR_TYPE));//未知车型
	m_cboModifyCarType.SetItemData(0, 0);
	m_cboModifyCarType.InsertString(1, GetTextEx(IDS_MUNI_COACH));//公交或大客车
	m_cboModifyCarType.SetItemData(1, 1);
	m_cboModifyCarType.InsertString(2, GetTextEx(IDS_SAMLL_CAR));//小汽车
	m_cboModifyCarType.SetItemData(2, 2);
	m_cboModifyCarType.InsertString(3, GetTextEx(IDS_MICROBUS));//面包车
	m_cboModifyCarType.SetItemData(3, 4);
	m_cboModifyCarType.InsertString(4, GetTextEx(IDS_BIG_TRUCK));//大货车
	m_cboModifyCarType.SetItemData(4, 5);
	m_cboModifyCarType.InsertString(5, GetTextEx(IDS_SMALL_TRUCK));//小货车
	m_cboModifyCarType.SetItemData(5, 6);
	m_cboModifyCarType.InsertString(6, GetTextEx(IDS_ITS_ER_SAN_LUN_CHE));//二、三轮车
	m_cboModifyCarType.SetItemData(6, 7);
	m_cboModifyCarType.InsertString(7, GetTextEx(IDS_PEDESTRIAN));//行人
	m_cboModifyCarType.SetItemData(7, 8);
	m_cboModifyCarType.SetCurSel(0);

	m_cboModifyCarBrand.ResetContent();
	m_cboModifyCarBrand.InsertString(0, "大众");
	m_cboModifyCarBrand.SetItemData(0, 1);
	m_cboModifyCarBrand.InsertString(1, "奥迪");
	m_cboModifyCarBrand.SetItemData(1, 2);
	m_cboModifyCarBrand.InsertString(2, "丰田");
	m_cboModifyCarBrand.SetItemData(2, 3);
	m_cboModifyCarBrand.InsertString(3, "本田");
	m_cboModifyCarBrand.SetItemData(3, 4);
	m_cboModifyCarBrand.InsertString(4, "奔驰");
	m_cboModifyCarBrand.SetItemData(4, 5);
	m_cboModifyCarBrand.InsertString(5, "雪佛兰");
	m_cboModifyCarBrand.SetItemData(5, 6);
	m_cboModifyCarBrand.InsertString(6, "奇瑞");
	m_cboModifyCarBrand.SetItemData(6, 7);
	m_cboModifyCarBrand.InsertString(7, "别克");
	m_cboModifyCarBrand.SetItemData(7, 8);
	m_cboModifyCarBrand.InsertString(8, "长城");
	m_cboModifyCarBrand.SetItemData(8, 9);
	m_cboModifyCarBrand.InsertString(9, "现代");
	m_cboModifyCarBrand.SetItemData(9, 10);
	m_cboModifyCarBrand.SetCurSel(0);

	m_cboModifyCarColor.ResetContent();
	m_cboModifyCarColor.InsertString(0, GetTextEx(IDS_VCA_COL_WHITE));
	m_cboModifyCarColor.SetItemData(0, 1);
	m_cboModifyCarColor.InsertString(1, GetTextEx(IDS_VCA_COL_GRAY));
	m_cboModifyCarColor.SetItemData(1, 2);
	m_cboModifyCarColor.InsertString(2, GetTextEx(IDS_VCA_COL_YELLOW));
	m_cboModifyCarColor.SetItemData(2, 3);
	m_cboModifyCarColor.InsertString(3, GetTextEx(IDS_VCA_COL_PINK));
	m_cboModifyCarColor.SetItemData(3, 4);
	m_cboModifyCarColor.InsertString(4, GetTextEx(IDS_VCA_COL_RED));
	m_cboModifyCarColor.SetItemData(4, 5);
	m_cboModifyCarColor.InsertString(5, GetTextEx(IDS_VCA_COL_MAGENTA));
	m_cboModifyCarColor.SetItemData(5, 6);
	m_cboModifyCarColor.InsertString(6, GetTextEx(IDS_VCA_COL_GREEN));
	m_cboModifyCarColor.SetItemData(6, 7);
	m_cboModifyCarColor.InsertString(7, GetTextEx(IDS_VCA_COL_BLUE));
	m_cboModifyCarColor.SetItemData(7, 8);
	m_cboModifyCarColor.InsertString(8, GetTextEx(IDS_VCA_COL_BROWN));
	m_cboModifyCarColor.SetItemData(8, 9);
	m_cboModifyCarColor.InsertString(9, GetTextEx(IDS_VCA_COL_BLACK));
	m_cboModifyCarColor.SetItemData(9, 10);
	m_cboModifyCarColor.InsertString(10, GetTextEx(IDS_VCA_COL_SILVER));
	m_cboModifyCarColor.SetItemData(10, 11);
	m_cboModifyCarColor.InsertString(11, GetTextEx(IDS_VCA_COL_CYAN));
	m_cboModifyCarColor.SetItemData(11, 12);
	m_cboModifyCarColor.InsertString(12, GetTextEx(IDS_UNKNOW_CAR_TYPE));
	m_cboModifyCarColor.SetItemData(12, 26);
	m_cboModifyCarColor.SetCurSel(0);
}

void CLS_ITSBayonetData::GetCrossInfo()
{
	int iCrossCount = 0;
	int iBufSize = MAX_ITS_CROSS_COUNT * sizeof(m_tItsCross);
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_GETCROSSCOUNT, m_iChannelNo, &iCrossCount, sizeof(int));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_GETCROSSCOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_GETCROSSCOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
		goto END;
	}

	memset(m_tItsCross, 0, MAX_ITS_CROSS_COUNT * sizeof(m_tItsCross));
	iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CROSSINFO, m_iChannelNo, &m_tItsCross, iBufSize);
	if(RET_SUCCESS == iRet)
	{
		m_cboCross.ResetContent();
		for (int i = 0; i < iCrossCount; ++i)
		{
			m_cboCross.AddString(m_tItsCross[i].cCrossNumber);
		}
		m_cboCross.SetCurSel(0);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO] (%d, %d)", m_iLogonID, m_iChannelNo);
	}

END:
	return;
}

void CLS_ITSBayonetData::GetLaneInfo()
{
	int iLaneCount = 0;
	int iBufSize = MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT * sizeof(ITSLaneInfo);
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_GETLANECOUNT, m_iChannelNo, &iLaneCount, sizeof(int));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_GETLANECOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_GETLANECOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
		goto END;
	}

	memset(m_tItsLane, 0, iBufSize);
	iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_LANEINFO, m_iChannelNo, m_tItsLane, iBufSize);
	if(RET_SUCCESS == iRet)
	{
		m_cboLane.ResetContent();
		CString cLaneID;
		for (int i = 0; i < iLaneCount; ++i)
		{
			cLaneID.Format("%d", m_tItsLane[i].iLaneID);
			m_cboLane.InsertString(i, cLaneID);
			m_cboLane.SetItemData(i, m_tItsLane[i].iLaneID);
		}
		m_cboLane.SetCurSel(0);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO] (%d, %d)", m_iLogonID, m_iChannelNo);
	}

END:
	return;
}

void CLS_ITSBayonetData::InitIllegalTypeCbo()
{
	m_cboQueryIllegalType.ResetContent();
	m_cboModifyIllegalType.ResetContent();
	m_cboQueryIllegalType.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboQueryIllegalType.SetItemData(0, PARAM_CHANNEL_ALL);

	std::vector<pair<int,CString>> vecIllegalType;
	int iRet = GetDataDictionary(m_iLogonID, m_iChannelNo, SUB_FUNC_TYPE_ITS_SNAPTYPE, vecIllegalType);
	if (RET_SUCCESS != iRet)
	{
		goto END;
	}

	for(int i=0; i < vecIllegalType.size(); i++)
	{
		int iIllegalType = vecIllegalType[i].first;
		CString cstrIllegalType = vecIllegalType[i].second;

		int iIndex1 = m_cboQueryIllegalType.InsertString(i + 1, cstrIllegalType);
		m_cboQueryIllegalType.SetItemData(iIndex1, iIllegalType);

		int iIndex2 = m_cboModifyIllegalType.InsertString(i + 1, cstrIllegalType);
		m_cboModifyIllegalType.SetItemData(iIndex2, iIllegalType);
	}

	m_cboQueryIllegalType.SetCurSel(0);
	m_cboModifyIllegalType.SetCurSel(0);

END:
	return;
}

void CLS_ITSBayonetData::InitCarTypeCbo()
{
	m_cboQueryCarType.ResetContent();
	m_cboModifyCarType.ResetContent();
	m_cboQueryCarType.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboQueryCarType.SetItemData(0, PARAM_CHANNEL_ALL);

	std::vector<pair<int,CString>> vecCarType;
	int iRet = GetDataDictionary(m_iLogonID, m_iChannelNo, SUB_FUNC_TYPE_ITS_CARTYPE, vecCarType);
	if (RET_SUCCESS != iRet)
	{
		goto END;
	}

	for(int i=0; i < vecCarType.size(); i++)
	{
		int iCarType = vecCarType[i].first;
		CString cstrCarType = vecCarType[i].second;

		int iIndex1 = m_cboQueryCarType.InsertString(i + 1, cstrCarType);
		m_cboQueryCarType.SetItemData(iIndex1, iCarType);

		int iIndex2 = m_cboModifyCarType.InsertString(i + 1, cstrCarType);
		m_cboModifyCarType.SetItemData(iIndex2, iCarType);
	}

	m_cboQueryCarType.SetCurSel(0);
	m_cboModifyCarType.SetCurSel(0);

END:
	return;
}

void CLS_ITSBayonetData::InitCarBrandCbo()
{
	m_cboQueryCarBrand.ResetContent();
	m_cboModifyCarBrand.ResetContent();
	m_cboQueryCarBrand.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboQueryCarBrand.SetItemData(0, PARAM_CHANNEL_ALL);

	std::vector<pair<int,CString>> vecCarBrand;
	int iQueryCount = 1;
	int iModifyCount = 0;
	for (int iSubType = SUB_FUNC_TYPE_ITS_CARBRAND_MIN; iSubType < SUB_FUNC_TYPE_ITS_CARBRAND_MAX; iSubType++)
	{
		int iRet = GetDataDictionary(m_iLogonID, m_iChannelNo, iSubType, vecCarBrand);
		if (RET_SUCCESS != iRet)
		{
			goto END;
		}

		for(int i = 0; i < vecCarBrand.size(); i++)
		{
			int iCarBrand = vecCarBrand[i].first;
			CString cstrCarBrand = vecCarBrand[i].second;

			int iIndex1 = m_cboQueryCarBrand.InsertString(iQueryCount, cstrCarBrand);
			m_cboQueryCarBrand.SetItemData(iIndex1, iCarBrand);
			iQueryCount++;

			int iIndex2 = m_cboModifyCarBrand.InsertString(iModifyCount, cstrCarBrand);
			m_cboModifyCarBrand.SetItemData(iIndex2, iCarBrand);
			iModifyCount++;
		}
	}

	m_cboQueryCarBrand.SetCurSel(0);
	m_cboModifyCarBrand.SetCurSel(0);

END:
	return;
}

void CLS_ITSBayonetData::InitCarColorCbo()
{
	m_cboQueryCarColor.ResetContent();
	m_cboModifyCarColor.ResetContent();
	m_cboQueryCarColor.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboQueryCarColor.SetItemData(0, PARAM_CHANNEL_ALL);

	std::vector<pair<int,CString>> vecCarColor;
	int iRet = GetDataDictionary(m_iLogonID, m_iChannelNo, SUB_FUNC_TYPE_ITS_CARCOLOR, vecCarColor);
	if (RET_SUCCESS != iRet)
	{
		goto END;
	}

	for(int i=0; i < vecCarColor.size(); i++)
	{
		int iCarColor = vecCarColor[i].first;
		CString cstrCarColor = vecCarColor[i].second;

		int iIndex1 = m_cboQueryCarColor.InsertString(i + 1, cstrCarColor);
		m_cboQueryCarColor.SetItemData(iIndex1, iCarColor);

		int iIndex2 = m_cboModifyCarColor.InsertString(i + 1, cstrCarColor);
		m_cboModifyCarColor.SetItemData(iIndex2, iCarColor);
	}

	m_cboQueryCarColor.SetCurSel(0);
	m_cboModifyCarColor.SetCurSel(0);

END:
	return;
}

void CLS_ITSBayonetData::InitCarDirectionCbo()
{
	m_cboDirection.ResetContent();
	m_cboDirection.InsertString(0, GetTextEx(IDS_CONFIG_DNVR_ALL));
	m_cboDirection.SetItemData(0, PARAM_CHANNEL_ALL);

	std::vector<pair<int,CString>> vecDirection;
	int iRet = GetDataDictionary(m_iLogonID, m_iChannelNo, SUB_FUNC_TYPE_ITS_CARCOLOR, vecDirection);
	if (RET_SUCCESS != iRet)
	{
		goto END;
	}

	for(int i=0; i < vecDirection.size(); i++)
	{
		int iDirection = vecDirection[i].first;
		CString cstrDirection = vecDirection[i].second;

		int iIndex = m_cboDirection.InsertString(i + 1, cstrDirection);
		m_cboDirection.SetItemData(iIndex, iDirection);
	}

	m_cboDirection.SetCurSel(0);

END:
	return;
}

void CLS_ITSBayonetData::ShowQueryCountToUser(int _iLanguage)
{
	char cMsg[LEN_64] = {0};
	if (1 == _iLanguage)
	{
		sprintf(cMsg, "CurPage:%d/TotalPage:%d/TotalRecord:%d", m_iCurrentPageNo + 1, m_iTotalPageCount, m_iTotalRecordCount);
	}
	else
	{
		sprintf(cMsg, "当前页%d/共%d页/%d条记录", m_iCurrentPageNo + 1, m_iTotalPageCount, m_iTotalRecordCount);
	}
	GetDlgItem(IDC_STATIC_ITS_QUERYDATA_TEXT)->SetWindowText(cMsg);
}

#define MSG_TYPE_MODIFY_DATA	1
#define MSG_TYPE_DELETE_DATA	2
void CLS_ITSBayonetData::OnMainNotify(int _iLogonID, int _iWparam, void* _iLParam, void* _iUser)
{
	if (_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)", _iLogonID);
		return;
	}

	int iMessage = _iWparam & 0xFFFF;
	int iResult = (int)_iLParam;
	switch (iMessage)
	{
	case WCM_ITS_QUERY_DATA:
		{
			ProcessQueryRecordResult();
			ShowQueryCountToUser();
		}
		break;
	case WCM_ITS_QUERY_TOTALCOUNT:
		{
			m_iTotalRecordCount = iResult;
			m_iTotalPageCount = m_iTotalRecordCount / MAX_ITS_QUERYDATA_PAGE_SIZE;
			if (m_iTotalRecordCount % MAX_ITS_QUERYDATA_PAGE_SIZE > 0)
			{
				m_iTotalPageCount++;
			}
			ShowQueryCountToUser();
		}
		break;
	case WCM_ITS_MODIFYDATA:
		{
			ShowMsgToUser(MSG_TYPE_MODIFY_DATA, iResult);
		}
		break;
	case WCM_ITS_DELETEDATA:
		{
			ShowMsgToUser(MSG_TYPE_DELETE_DATA, iResult);
		}
		break;
	default:
		break;
	}
}

void CLS_ITSBayonetData::ShowMsgToUser(int _iMsgType, int _iResult)
{
	switch (_iMsgType)
	{
	case MSG_TYPE_MODIFY_DATA:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Modify data success!", "", MB_OK|MB_TOPMOST);
			else
				MessageBox("Modify data faied!", "", MB_OK|MB_TOPMOST);
		}
		break;
	case MSG_TYPE_DELETE_DATA:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Delete data success!", "", MB_OK|MB_TOPMOST);
			else
			{
				char cMsg[LEN_32] = {0};
				sprintf(cMsg, "Delete data faied! Count(%d)", _iResult);
				MessageBox(cMsg, "", MB_OK|MB_TOPMOST);
			}
		}
		break;
	default:
		break;
	}
}

void CLS_ITSBayonetData::GetQueryCondition(ITSQueryData &_strctCaptureQueryCondition)
{
	SYSTEMTIME BeginDate;
	m_dtpBeginDate.GetTime(&BeginDate);
	_strctCaptureQueryCondition.tStartTime.iYear  = BeginDate.wYear;
	_strctCaptureQueryCondition.tStartTime.iMonth = BeginDate.wMonth;
	_strctCaptureQueryCondition.tStartTime.iDay   = BeginDate.wDay;

	SYSTEMTIME BeginTime;
	m_dtpBeginTime.GetTime(&BeginTime);
	_strctCaptureQueryCondition.tStartTime.iMonth  = BeginTime.wHour;
	_strctCaptureQueryCondition.tStartTime.iMinute = BeginTime.wMinute;
	_strctCaptureQueryCondition.tStartTime.iSecond = BeginTime.wSecond;

	SYSTEMTIME EndDate;
	m_dtpEndDate.GetTime(&EndDate);
	_strctCaptureQueryCondition.tStopTime.iYear  = EndDate.wYear;
	_strctCaptureQueryCondition.tStopTime.iMonth = EndDate.wMonth;
	_strctCaptureQueryCondition.tStopTime.iDay   = EndDate.wDay;

	SYSTEMTIME EndTime;
	m_dtpEndTime.GetTime(&EndTime);
	_strctCaptureQueryCondition.tStopTime.iMonth  = EndTime.wHour;
	_strctCaptureQueryCondition.tStopTime.iMinute = EndTime.wMinute;
	_strctCaptureQueryCondition.tStopTime.iSecond = EndTime.wSecond;

	// 上传状态
	if(m_cboUploadState.GetCurSel() <= 0)
	{
		_strctCaptureQueryCondition.iUpload = PARAM_CHANNEL_ALL;
	}
	else
	{
		_strctCaptureQueryCondition.iUpload = (int)m_cboUploadState.GetItemData(m_cboUploadState.GetCurSel());
	}

	// 路口编号
	int iCurSel = m_cboCross.GetCurSel();
	CString cstrCrossNumber;
	m_cboCross.GetWindowText(cstrCrossNumber);
	memcpy(_strctCaptureQueryCondition.cCrossNumber, cstrCrossNumber.GetBuffer(), cstrCrossNumber.GetLength() + 1);

	// 车道
	iCurSel = m_cboLane.GetCurSel();
	_strctCaptureQueryCondition.iLaneID = (int)m_cboLane.GetItemData(iCurSel);

	// 行驶方向
	iCurSel = m_cboDirection.GetCurSel();
	_strctCaptureQueryCondition.iDirection = (int)m_cboDirection.GetItemData(iCurSel);

	// 车牌号码
	CString cstrPlate;
	m_edtQueryPlate.GetWindowText(cstrPlate);
	memcpy(_strctCaptureQueryCondition.cLicense, (LPSTR)(LPCTSTR)cstrPlate, cstrPlate.GetLength()+1);

	// 车辆类型
	iCurSel = m_cboQueryCarType.GetCurSel();
	_strctCaptureQueryCondition.iVehicleType = (int)m_cboQueryCarType.GetItemData(iCurSel);

	// 车辆品牌
	iCurSel = m_cboQueryCarBrand.GetCurSel();
	_strctCaptureQueryCondition.iBrand = (int)m_cboQueryCarBrand.GetItemData(iCurSel);

	// 车身颜色
	iCurSel = m_cboQueryCarColor.GetCurSel();
	_strctCaptureQueryCondition.iColor = (int)m_cboQueryCarColor.GetItemData(iCurSel);

	iCurSel = m_cboQueryIllegalType.GetCurSel();
	_strctCaptureQueryCondition.iIllegal = (int)m_cboQueryIllegalType.GetItemData(iCurSel);

	_strctCaptureQueryCondition.iBeginIndex = m_iBeginIndex;
	_strctCaptureQueryCondition.iEndIndex = m_iEndIndex;
	_strctCaptureQueryCondition.iTotalCount = m_iTotalRecordCount;
}

void CLS_ITSBayonetData::SDKQueryData()
{
	ITSQueryData tQuery = {0};

	// 获取查询条件
	GetQueryCondition(tQuery);

	int iRet = NetClient_Query_V4(m_iLogonID, CMD_NETFILE_ITS_QUERY_DATA, m_iChannelNo, &tQuery, sizeof(ITSQueryData));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_Query_V4[CMD_NETFILE_ITS_QUERY_DATA] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_Query_V4[CMD_NETFILE_ITS_QUERY_DATA] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSBayonetData::OnBnClickedButtonItsQueryBayonetData()
{
	m_iTotalRecordCount = 0;   
	m_iTotalPageCount = 0;  
	m_iCurrentPageNo = 0;  
	m_iBeginIndex = 0;
	m_iEndIndex = MAX_ITS_QUERYDATA_PAGE_SIZE;
	SDKQueryData();
}

void CLS_ITSBayonetData::OnBnClickedBtnDataqueryFirstpage()
{
	m_iCurrentPageNo = 0;  
	m_iBeginIndex = 0;
	m_iEndIndex = MAX_ITS_QUERYDATA_PAGE_SIZE;
	SDKQueryData();
}

void CLS_ITSBayonetData::OnBnClickedBtnDataqueryPrepage()
{
	m_iCurrentPageNo--;
	m_iBeginIndex = m_iCurrentPageNo * MAX_ITS_QUERYDATA_PAGE_SIZE;
	m_iEndIndex = m_iBeginIndex  + MAX_ITS_QUERYDATA_PAGE_SIZE;
	SDKQueryData();
}

void CLS_ITSBayonetData::OnBnClickedBtnDataqueryNextpage()
{
	m_iCurrentPageNo++;
	m_iBeginIndex = m_iCurrentPageNo * MAX_ITS_QUERYDATA_PAGE_SIZE;
	m_iEndIndex = m_iBeginIndex  + MAX_ITS_QUERYDATA_PAGE_SIZE;
	SDKQueryData();
}

void CLS_ITSBayonetData::OnBnClickedBtnDataqueryEndpage()
{
	// 现在显示的不是尾页，进行尾页请求
	if (m_iCurrentPageNo != (m_iTotalPageCount - 1))
	{
		m_iCurrentPageNo = m_iTotalPageCount - 1;
		m_iBeginIndex = m_iCurrentPageNo * MAX_ITS_QUERYDATA_PAGE_SIZE;
		m_iEndIndex = m_iBeginIndex  + MAX_ITS_QUERYDATA_PAGE_SIZE;
		SDKQueryData();
	}
}

void CLS_ITSBayonetData::OnBnClickedButtonItsModifyBayonetData()
{
	ITSModifyData tITSModifyData = {0};
	tITSModifyData.iSize = sizeof(ITSModifyData);
	CString cstrPlate;
	m_edtModifyPlate.GetWindowText(cstrPlate);
	memcpy(tITSModifyData.cLicense, cstrPlate.GetBuffer(), cstrPlate.GetLength());//车牌号码
	tITSModifyData.iColor = (int)m_cboModifyCarColor.GetItemData(m_cboModifyCarColor.GetCurSel());//车身颜色
	tITSModifyData.iVehicleType = (int)m_cboModifyCarType.GetItemData(m_cboModifyCarType.GetCurSel());//车辆类型
	tITSModifyData.iBrand = (int)m_cboModifyCarBrand.GetItemData(m_cboModifyCarBrand.GetCurSel());//车辆品牌
	if (m_iSelectIndex < 0 || m_iSelectIndex >= MAX_ITS_QUERYDATA_PAGE_SIZE)
	{
		m_iSelectIndex = 0;
	}
	tITSModifyData.iOrderId = m_tRecordArray[m_iSelectIndex].iOrderId;
	tITSModifyData.iIllegal = (int)m_cboModifyIllegalType.GetItemData(m_cboModifyIllegalType.GetCurSel());
	CString cstrPicName;
	m_edtModifyPicName.GetWindowText(cstrPicName);
	memcpy(tITSModifyData.cPicName, cstrPicName.GetBuffer(), LEN_64);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_MODIFYDATA, PARAM_CHANNEL_ALL, &tITSModifyData, sizeof(ITSModifyData));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_MODIFYDATA] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_MODIFYDATA] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSBayonetData::OnBnClickedButtonItsDeleteBayonetData()
{
	ITSDeleteData tITSDeleteData = {0};
	tITSDeleteData.iSize = sizeof(ITSDeleteData);
	tITSDeleteData.iRecordCount = 1;
	if (m_iSelectIndex < 0 || m_iSelectIndex >= MAX_ITS_QUERYDATA_PAGE_SIZE)
	{
		m_iSelectIndex = 0;
	}
	tITSDeleteData.iOrderId[0] = m_tRecordArray[m_iSelectIndex].iOrderId;
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_DELETEDATA, PARAM_CHANNEL_ALL, &tITSDeleteData, sizeof(ITSDeleteData));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_DELETEDATA] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_DELETEDATA] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSBayonetData::OnBnClickedButtonItsQueryTotalCount()
{
	ITSQueryData tQuery = {0};
	// 获取查询条件
	GetQueryCondition(tQuery);
	int iRet = NetClient_Query_V4(m_iLogonID, CMD_NETFILE_ITS_QUERY_TOTALCOUNT, PARAM_CHANNEL_ALL, &tQuery, sizeof(ITSQueryData));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_Query_V4[CMD_NETFILE_ITS_QUERY_TOTALCOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_Query_V4[CMD_NETFILE_ITS_QUERY_TOTALCOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSBayonetData::OnCbnSelchangeCboDataqueryPlate()
{
	// 车牌省份选择，将其填充到车牌edit中
	CString sPlate;
	m_cboQueryPlate.GetWindowText(sPlate);
	m_edtQueryPlate.SetWindowText(sPlate);	
}

//处理获取查询结果
void CLS_ITSBayonetData::ProcessQueryRecordResult()
{
	int iCurrentCount = 0;
	// 获取本次查询能从sdk读到的条数
	int iRet = NetClient_GetQueryResult_V4(m_iLogonID, CMD_NETFILE_ITS_GETCURRENTCOUNT, INVALID_FLAG, 0, &iCurrentCount, sizeof(int));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetQueryResult_V4[CMD_NETFILE_ITS_GETCURRENTCOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetQueryResult_V4[CMD_NETFILE_ITS_GETCURRENTCOUNT] (%d, %d)", m_iLogonID, m_iChannelNo);
		goto END;
	}

	// 循环获取本次查询结果
	for (int iIndex = 0; iIndex < iCurrentCount && iIndex < MAX_ITS_QUERYDATA_PAGE_SIZE; iIndex++)
	{
		memset(&m_tRecordArray[iIndex], 0, sizeof(ITSQueryDataRecord));
		int iRet = NetClient_GetQueryResult_V4(m_iLogonID, CMD_NETFILE_ITS_GETRESULT, INVALID_FLAG, iIndex, &m_tRecordArray[iIndex], sizeof(ITSQueryDataRecord));
		if(RET_SUCCESS == iRet)
		{
			AddLog(LOG_TYPE_SUCC, "", "NetClient_GetQueryResult_V4[CMD_NETFILE_ITS_GETRESULT] (%d, %d)", m_iLogonID, m_iChannelNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetQueryResult_V4[CMD_NETFILE_ITS_GETRESULT] (%d, %d)", m_iLogonID, m_iChannelNo);
			goto END;
		}

		// 显示本条记录
		int iItem = m_lstQueryRecord.GetItemCount();
		m_lstQueryRecord.InsertItem(iItem, "");
		CString cstrTemp = "";
		cstrTemp.Format("%04hu-%02hu-%02hu %02hu:%02hu:%02hu",
			m_tRecordArray[iIndex].tTime.iYear,
			m_tRecordArray[iIndex].tTime.iMonth,
			m_tRecordArray[iIndex].tTime.iDay,
			m_tRecordArray[iIndex].tTime.iHour,
			m_tRecordArray[iIndex].tTime.iMinute,
			m_tRecordArray[iIndex].tTime.iSecond);

		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordCaptureTime, cstrTemp);//抓拍时间
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordRoad, m_tRecordArray[iIndex].cCrossNumber);//路口/地点
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordChannel, IntToString(m_tRecordArray[iIndex].iLaneID));//车道检测区域
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordDirection, GetCarDirectionString(m_tRecordArray[iIndex].iDirection));//行驶方向
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordPlate, m_tRecordArray[iIndex].cLicense);//车牌号码
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordCarType, GetCarTypeString(m_tRecordArray[iIndex].iVehicleType));//车辆类型
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordCarLogo, GetCarBrandString(m_tRecordArray[iIndex].iBrand));//车辆品牌
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordCarColor, GetCarColorString(m_tRecordArray[iIndex].iColor));//车身颜色
		m_lstQueryRecord.SetItemText(iItem, n_ITSDataRecordUploadStatus, GetUploadStatusString(m_tRecordArray[iIndex].iUpload));//上传状态
	}

END:
	return;
}

void CLS_ITSBayonetData::OnNMClickLstDataqueryRecord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	for (int i = 0; i < m_lstQueryRecord.GetItemCount(); ++i)
	{
		if (LVIS_SELECTED == m_lstQueryRecord.GetItemState(i, LVIS_SELECTED)
			&& i >= 0 && i < MAX_ITS_QUERYDATA_PAGE_SIZE)
		{
			m_iSelectIndex = i;
			m_edtModifyPlate.SetWindowText(m_tRecordArray[i].cLicense);
			m_cboModifyCarType.SetCurSel(m_tRecordArray[i].iVehicleType);
			m_cboModifyCarBrand.SetCurSel(m_tRecordArray[i].iBrand - 1);
			m_cboModifyCarColor.SetCurSel(m_tRecordArray[i].iColor - 1);
			m_cboModifyIllegalType.SetCurSel(m_tRecordArray[i].iIllegal);
			m_edtModifyPicName.SetWindowText(m_tRecordArray[i].cPicName[0]);
		}
	}
	*pResult = 0;
}
