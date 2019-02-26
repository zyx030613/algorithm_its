
#include "stdafx.h"
#include "NetClientDemo.h"
#include "FacePicmanage.h"

#define VCA_SUSPEND_STATUS_PAUSE		0
#define VCA_SUSPEND_STATUS_RESUME		1

#define MSG_FACE_MODE_FINISH			(WM_USER+2001)

enum MODING_TYPE
{
	MODING_TYPE_SINGLE = 0,
	MODING_TYPE_BATCH_UNMODELED,
	MODING_TYPE_BATCH_ALL,
	MODING_TYPE_CANCEL
};

struct StrData
{
	CString cstr;
	int		iData;
};

const int CONST_INT_NATION[] = {IDS_UNKNOW_CONNECT,
IDS_NATION_HAN, IDS_NATION_MONGOLS, IDS_NATION_HUI, IDS_NATION_TIBETAN, IDS_NATION_UYGUR, 
IDS_NATION_MIAO, IDS_NATION_YI, IDS_NATION_ZHUANG, IDS_NATION_BUYI, IDS_NATION_KOREAN, 
IDS_NATION_MAN, IDS_NATION_DONG, IDS_NATION_YAO, IDS_NATION_BAI, IDS_NATION_TUJIA, 
IDS_NATION_HANI, IDS_NATION_KAZAKH, IDS_NATION_DAI, IDS_NATION_LI, IDS_NATION_LISU, 
IDS_NATION_WA, IDS_NATION_SHE, IDS_NATION_GAOSHAN, IDS_NATION_LAHU, IDS_NATION_SHUI, 
IDS_NATION_DONGXIANG, IDS_NATION_NAXI, IDS_NATION_JINGPO, IDS_NATION_KEKZ, IDS_NATION_TUZU, 
IDS_NATION_DAUR, IDS_NATION_MULAO, IDS_NATION_QIANG, IDS_NATION_BLANG, IDS_NATION_SALA, 
IDS_NATION_MAONAN, IDS_NATION_GELAO, IDS_NATION_XIBO, IDS_NATION_ACHANG, IDS_NATION_PUMIN, 
IDS_NATION_TAJIKE, IDS_NATION_NU, IDS_NATION_WUZIBIEKE, IDS_NATION_RUSS, IDS_NATION_EWENKE, 
IDS_NATION_BENGLONG, IDS_NATION_BAOAN, IDS_NATION_YUGU, IDS_NATION_JING, IDS_NATION_TATARS, 
IDS_NATION_DULONG, IDS_NATION_ELUNCHUN, IDS_NATION_HEZHE, IDS_NATION_MENBA, IDS_NATION_LUOBA, 
IDS_NATION_ZINUO, IDS_NATION_OTHER, IDS_NATION_FOREIGN};

const StrData CONST_STRDATA_PROVIENCE[] = {{GetTextEx(IDS_UNKNOW_CONNECT), 0},
{"北京市", 11},{"天津市", 12},{"河北省", 13},{"山西省", 14},{"内蒙古自治区", 15},{"辽宁省", 21},{"吉林省", 22},{"黑龙江省", 23},
{"上海市", 31},{"江苏省", 32},{"浙江省", 33},{"安徽省", 34},{"福建省", 35},{"江西省", 36},{"山东省", 37},{"河南省", 41},{"湖北省", 42},
{"湖南省", 43},{"广东省", 44},{"广西壮族自治区", 45},{"海南省", 46},{"四川省", 51},{"贵州省", 52},{"云南省", 53},{"西藏自治区", 54},
{"重庆市", 50},{"陕西省", 61},{"甘肃省", 62},{"青海省", 63},{"宁夏回族自治区", 64},{"新疆维吾尔自治区", 65},{"台湾省", 71},
{"香港特别行政区", 81},{"澳门特别行政区", 82}};

const int CONST_INT_MODE[] = {IDS_UNKNOW_CONNECT, IDS_MODE_SUCC, IDS_MODE_FAIL, IDS_MODE_NOT};
const int CONST_INT_SEX[] = {IDS_UNKNOW_CONNECT, IDS_MALE, IDS_FEMALE};
const int CONST_INT_CARD[] = {IDS_UNKNOW_CONNECT, IDS_CERT_ID, IDS_CERT_OFFICERS, IDS_CERT_PASSPORT};

typedef enum{
	ITEM_PIC_INDEX = 0,					//序号
	ITEM_PIC_NAME,						//name
	ITEM_PIC_SEX,						//性別
	ITEM_PIC_NATION,					//民族
	ITEM_PIC_BIRTH,						//出生日期
	ITEM_PIC_PLACE,						//籍贯
	ITEM_PIC_CARDTYPE,					//证件类型
	ITEM_PIC_CARDNO,					//证件号
	ITEM_PIC_MODESTATE,					//建模状态
}ITEM_FACE_PIC;


IMPLEMENT_DYNAMIC(CLS_DlgCfgFacePicMng, CDialog)

CLS_DlgCfgFacePicMng::CLS_DlgCfgFacePicMng(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgCfgFacePicMng::IDD, pParent)
{
	memset(&m_tQueryInfo, 0, sizeof(m_tQueryInfo));
	memset(&m_tQueryResult, 0, sizeof(m_tQueryResult));
	memset(&m_tModeInfo, 0, sizeof(m_tModeInfo));
	m_iCurPage = 0;
	m_iTolalPage = 0;
	m_iChannelNO = 0;
}

CLS_DlgCfgFacePicMng::~CLS_DlgCfgFacePicMng()
{
}

void CLS_DlgCfgFacePicMng::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_FACE_PIC_INFO, m_lstFacePic);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_KEY, m_cboLibKey);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_SEX, m_cboSex);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_NATION, m_cboNation);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_PROVIENCE, m_cboProvience);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_CITY, m_cboCity);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_CARD_TYPE, m_cboCardType);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_MODE_STATE, m_cboModeState);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_NAME, m_edtName);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_PAGE_NO, m_cboPageNo);
	DDX_Control(pDX, IDC_EDT_FACE_PIC_CARD_NUM, m_edtCarNum);
	DDX_Control(pDX, IDC_EDT_FACE_PIC_PATH, m_edtPicPath);
	DDX_Control(pDX, IDC_STC_FACE_PIC_PAGE_NO, m_stcPageNo);
	DDX_Control(pDX, IDC_DT_FACE_PIC_BEG, m_dtBirthBeg);
	DDX_Control(pDX, IDC_DT_FACE_PIC_END, m_dtBirthEnd);
	DDX_Control(pDX, IDC_CBO_FACE_PIC_MODE_TYPE, m_cboModeType);
	DDX_Control(pDX, IDC_PRO_MODE_PROCESS, m_proModeProcess);
	DDX_Control(pDX, IDC_STC_FACE_PIC_MODE_PROCESS, m_stcProcess);
}


BEGIN_MESSAGE_MAP(CLS_DlgCfgFacePicMng, CLS_BasePage)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_QUERY, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicQuery)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_PAGE_BEG, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPageBeg)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_PAGE_PRE, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPagePre)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_PAGE_NXT, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPageNxt)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_PAGE_END, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPageEnd)
	ON_CBN_SELCHANGE(IDC_CBO_FACE_PIC_PAGE_NO, &CLS_DlgCfgFacePicMng::OnCbnSelchangeCboFacePicPageNo)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_ADD, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicAdd)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_PATH, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPath)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_MDY, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicMdy)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_DEL, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicDel)
	ON_NOTIFY(NM_CLICK, IDC_LST_FACE_PIC_INFO, &CLS_DlgCfgFacePicMng::OnNMClickLstFacePicInfo)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_MODE, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicMode)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_MODE_STOP, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicModeStop)
	ON_MESSAGE(MSG_FACE_MODE_FINISH, &CLS_DlgCfgFacePicMng::OnModeFinish)
	ON_BN_CLICKED(IDC_BTN_FACE_PIC_LIB_QUERY, &CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicLibQuery)
END_MESSAGE_MAP()


BOOL CLS_DlgCfgFacePicMng::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdataText();

	return TRUE; 
}

void CLS_DlgCfgFacePicMng::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
}

void CLS_DlgCfgFacePicMng::OnLanguageChanged(int _iLanguage)
{
	UI_UpdataText();
	ShowPage(m_iCurPage);
}

void CLS_DlgCfgFacePicMng::OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	int iMsgType = LOWORD(_wParam);
	if (WCM_FACE_MODEING == iMsgType) {
		FaceModeResult tRet = *(FaceModeResult*)_iLParam;
		m_stcProcess.SetWindowText(IntToCString(tRet.iIndex)+"/"+IntToCString(tRet.iTotal));
		m_proModeProcess.SetPos((tRet.iIndex)*100/tRet.iTotal);
		if (tRet.iIndex == tRet.iTotal) {		//建模完成	
			PostMessage(MSG_FACE_MODE_FINISH);
		}	
	}
}

LRESULT CLS_DlgCfgFacePicMng::OnModeFinish(WPARAM wParam, LPARAM lParam)
{
	//恢复智能分析算法		
	SetVcaStatue(VCA_SUSPEND_STATUS_RESUME);
	memset(&m_tModeInfo, 0, sizeof(m_tModeInfo));
	ShowPage(m_iCurPage);
	return 0;
}

void CLS_DlgCfgFacePicMng::UI_Init()
{
	//性别
	m_cboSex.ResetContent();
	for (int i = 0; i < (sizeof(CONST_INT_SEX)/sizeof(int)); ++i)
	{
		m_cboSex.InsertString(i, GetTextEx(CONST_INT_SEX[i]));
	}
	m_cboSex.SetCurSel(0);
	//民族
	m_cboNation.ResetContent();
	for (int i = 0; i < (sizeof(CONST_INT_NATION)/sizeof(int)); ++i)
	{
		m_cboNation.InsertString(i,  GetTextEx(CONST_INT_NATION[i]));
	}
	m_cboNation.SetCurSel(0);
	//省份
	m_cboProvience.ResetContent();
	for (int i = 0; i < (sizeof(CONST_STRDATA_PROVIENCE)/sizeof(StrData)); ++i)
	{
		StrData tData = CONST_STRDATA_PROVIENCE[i];
		m_cboProvience.SetItemData(m_cboProvience.AddString(tData.cstr), tData.iData);
	}
	m_cboProvience.SetCurSel(0);
	//todo 城市
	m_cboCity.ResetContent();
	m_cboCity.SetItemData(m_cboCity.AddString("未知"), 0);
	m_cboCity.SetCurSel(0);
	//证件类型
	m_cboCardType.ResetContent();
	for (int i = 0; i < (sizeof(CONST_INT_CARD)/sizeof(int)); ++i)
	{
		m_cboCardType.InsertString(i, GetTextEx(CONST_INT_CARD[i]));
	}
	m_cboCardType.SetCurSel(0);
	//建模状态
	m_cboModeState.ResetContent();
	for (int i = 0; i < (sizeof(CONST_INT_MODE)/sizeof(int)); ++i)
	{
		m_cboModeState.InsertString(i, GetTextEx(CONST_INT_MODE[i]));
	}
	m_cboModeState.SetCurSel(0);
	//出生日期
	COleDateTime tmBeg = COleDateTime::GetCurrentTime();
	tmBeg.ParseDateTime(_T("1970-01-01"));//默认值1970-01-01	
	m_dtBirthBeg.SetTime(tmBeg);
	//列表
	while (m_lstFacePic.GetHeaderCtrl()->GetItemCount() > 0) {
		m_lstFacePic.DeleteColumn(0);
	}
	m_lstFacePic.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_lstFacePic.InsertColumn(ITEM_PIC_INDEX, GetTextEx(IDS_NUM), LVCFMT_LEFT, 40, -1);
	m_lstFacePic.InsertColumn(ITEM_PIC_NAME, GetTextEx(IDS_COMPELATION), LVCFMT_LEFT, 80, -1);
	m_lstFacePic.InsertColumn(ITEM_PIC_SEX, GetTextEx(IDS_GENDER), LVCFMT_LEFT, 60, -1);	
	m_lstFacePic.InsertColumn(ITEM_PIC_NATION, GetTextEx(IDS_NATION), LVCFMT_LEFT, 80, -1);	
	m_lstFacePic.InsertColumn(ITEM_PIC_BIRTH, GetTextEx(IDS_BIRTHDAY), LVCFMT_LEFT, 70, -1);
	m_lstFacePic.InsertColumn(ITEM_PIC_PLACE, GetTextEx(IDS_NATION), LVCFMT_LEFT, 80, -1);
	m_lstFacePic.InsertColumn(ITEM_PIC_CARDTYPE, GetTextEx(IDS_CERT_TYPE), LVCFMT_LEFT, 82, -1);
	m_lstFacePic.InsertColumn(ITEM_PIC_CARDNO, GetTextEx(IDS_CERT_NO), LVCFMT_LEFT, 82, -1);
	m_lstFacePic.InsertColumn(ITEM_PIC_MODESTATE, GetTextEx(IDS_MODE_STATE), LVCFMT_LEFT, 85, -1);
	//建模类型
	m_cboModeType.ResetContent();
	m_cboModeType.InsertString(0, GetTextEx(IDS_MODE_SINGLE));
	m_cboModeType.InsertString(1, GetTextEx(IDS_MODE_BATCH_UNMODE));
	m_cboModeType.InsertString(2, GetTextEx(IDS_MODE_BATCH_ALL));
	m_cboModeType.SetCurSel(0);
	//建模进度
	m_proModeProcess.SetRange(0, 100);
}

void CLS_DlgCfgFacePicMng::UI_UpdataText()
{
	UI_Init();

	SetDlgItemTextEx(IDC_STC_FACE_PIC_KEY, IDS_VCA_FACE_LIB);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_NAME, IDS_COMPELATION);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_SEX, IDS_GENDER);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_NATION, IDS_NATION);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_BIRTH, IDS_BIRTHDAY);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_PROVIENCE, IDS_PROVIENCE);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_CITY, IDS_CITY);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_CARD_TYPE, IDS_CERT_TYPE);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_CARD_NUM, IDS_CERT_NO);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_MODE_STATE, IDS_MODE_STATE);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_QUERY, IDS_PBK_QUERY);
	SetDlgItemTextEx(IDC_STC_FACE_PIC_PATH, IDS_FACE_PIC_PATH);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_MODE, IDS_MODLE);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_ADD, IDS_ADD);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_MDY, IDS_MODIFY);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_DEL, IDS_DELETE);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_PAGE_BEG, IDS_PLAYBACK_FIRST_PAGE);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_PAGE_PRE, IDS_PLAYBACK_PREPAGE);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_PAGE_NXT, IDS_PLAYBACK_NEXT_PAGE);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_PAGE_END, IDS_PLAYBACK_LAST_PAGE);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_MODE_STOP, IDS_STOP);
	SetDlgItemTextEx(IDC_BTN_FACE_PIC_LIB_QUERY, IDS_PLAYBACK_QUERY);
}

void CLS_DlgCfgFacePicMng::UI_Updata()
{
	if (NULL == NetClient_FaceConfig)
	{
		return;
	}

	m_cboLibKey.ResetContent();

	int iPageNo = 0;
	while (TRUE)
	{
		FaceLibQuery tQuery = {0};
		tQuery.iSize = sizeof(FaceLibQuery);
		tQuery.iChanNo = m_iChannelNO;
		tQuery.iPageNo = iPageNo;
		tQuery.iPageCount = FACE_MAX_PAGE_COUNT;

		FaceLibQueryResult tResult[FACE_MAX_PAGE_COUNT] = {0};
		int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_LIB_QUERY, m_iChannelNO, &tQuery, sizeof(FaceLibQuery), &tResult, sizeof(FaceLibQueryResult));
		if (RET_SUCCESS != iRet)
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_FaceConfig failed, ret(%d), pageNo(%d).", iRet, iPageNo);
			break;
		}

		for (int iIdx = 0; iIdx < FACE_MAX_PAGE_COUNT && iIdx < tResult[0].iPageCount; ++iIdx)
		{
			if (tResult[iIdx].tFaceLib.iSize > 0)
			{
				m_cboLibKey.SetItemData(m_cboLibKey.AddString(tResult[iIdx].tFaceLib.cName), tResult[iIdx].tFaceLib.iLibKey);
			}			
		}

		iPageNo++;
		int iPageCount = tResult[0].iTotal / FACE_MAX_PAGE_COUNT;
		if (tResult[0].iTotal % FACE_MAX_PAGE_COUNT > 0)
		{
			iPageCount = iPageCount + 1;
		}

		if (iPageNo >= iPageCount)
		{
			break;
		}
	}
	m_cboLibKey.SetCurSel(0);
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicQuery()
{
	memset(&m_tQueryInfo, 0, sizeof(m_tQueryInfo));
	m_iCurPage = 0;
	m_iTolalPage = 0;
	m_stcPageNo.SetWindowText("");

	int iLibKeySel = m_cboLibKey.GetCurSel();
	if (iLibKeySel < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "Face database is illegal.");
		return;
	}

	FaceQuery tQuery = {0};
	tQuery.iSize = sizeof(tQuery);
	tQuery.iChanNo = m_iChannelNO;
	tQuery.iLibKey = m_cboLibKey.GetItemData(iLibKeySel);
	m_edtName.GetWindowText(tQuery.cName, sizeof(tQuery.cName));
	tQuery.iSex = m_cboSex.GetItemData(m_cboSex.GetCurSel());
	tQuery.iNation = m_cboNation.GetCurSel();
	m_dtBirthBeg.GetWindowText(tQuery.cBirthStart, sizeof(tQuery.cBirthStart));
	m_dtBirthEnd.GetWindowText(tQuery.cBirthEnd, sizeof(tQuery.cBirthEnd));
	tQuery.iPlace = MAKELONG(m_cboCity.GetItemData(m_cboCity.GetCurSel()), m_cboProvience.GetItemData(m_cboProvience.GetCurSel()));
	tQuery.iCertType = m_cboCardType.GetCurSel();
	tQuery.iModeling = m_cboModeState.GetCurSel();
	m_edtCarNum.GetWindowText(tQuery.cCertNum, sizeof(tQuery.cCertNum));
	tQuery.iPageCount = FACE_MAX_PAGE_COUNT;
	m_tQueryInfo = tQuery;
	ShowPage(m_iCurPage);
}

void CLS_DlgCfgFacePicMng::ShowPage(int _iPageNo)
{
	if (NULL == NetClient_FaceConfig)
	{
		return;
	}

	if ((m_iTolalPage > 0 && _iPageNo >= m_iTolalPage) || _iPageNo < 0)
	{
		return;
	}

	if (m_tQueryInfo.iSize <= 0)
	{
		return;
	}
	
	m_lstFacePic.DeleteAllItems();
	memset(&m_tQueryResult, 0, sizeof(m_tQueryResult));
	m_tQueryInfo.iPageNo = _iPageNo;
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_QUERY, m_iChannelNO, &m_tQueryInfo, sizeof(m_tQueryInfo), &m_tQueryResult,sizeof(FaceQueryResult));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "ShowPage(%d) NetClient_FaceConfig failed.", _iPageNo);
		return;
	}

	int iTotalPage = m_tQueryResult[0].iTotal/FACE_MAX_PAGE_COUNT;
	if (m_tQueryResult[0].iTotal%FACE_MAX_PAGE_COUNT > 0 && m_tQueryResult[0].iTotal > 0)
	{
		iTotalPage ++;
	}

	if (0 == m_iTolalPage)
	{
		m_iTolalPage = iTotalPage;
		m_cboPageNo.ResetContent();
		for (int i = 0; i < m_iTolalPage; ++i)
		{
			m_cboPageNo.InsertString(i, IntToString(i+1));
		}
	}

	m_iCurPage = _iPageNo;
	m_cboPageNo.SetCurSel(m_iCurPage);
	if (m_tQueryResult[0].iTotal > 0)
	{
		_iPageNo ++;
	}
	m_stcPageNo.SetWindowText(IntToString(_iPageNo)+"/"+IntToString(m_iTolalPage));

	for (int i = 0; i < m_tQueryResult[0].iPageCount; ++i)
	{
		UI_UpdateListItem(m_tQueryResult[i].tFace);
	}
}

void CLS_DlgCfgFacePicMng::UI_UpdateListItem(FaceInfo& _tInfo, int _iLibIndex /*= -1*/)
{
	int iIndex = _iLibIndex;
	if (-1 == _iLibIndex)
	{
		iIndex = m_lstFacePic.GetItemCount();
		m_lstFacePic.InsertItem(iIndex,_T(""));
	}
	m_lstFacePic.SetItemData(iIndex, _tInfo.iFaceKey);

	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_INDEX, IntToCString(iIndex + 1));
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_NAME, _tInfo.cName);
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_SEX, GetTextEx(CONST_INT_SEX[_tInfo.iSex]));
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_NATION, GetTextEx(CONST_INT_NATION[_tInfo.iNation]));
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_BIRTH, _tInfo.cBirthTime);
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_PLACE, "未知");
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_CARDTYPE, GetTextEx(CONST_INT_CARD[_tInfo.iCertType]));
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_CARDNO, _tInfo.cCertNum);
	m_lstFacePic.SetItemText(iIndex, ITEM_PIC_MODESTATE, GetTextEx(CONST_INT_MODE[_tInfo.iModeling + 1]));
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPageBeg()
{
	ShowPage(0);
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPagePre()
{
	ShowPage(m_iCurPage - 1);
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPageNxt()
{
	ShowPage(m_iCurPage + 1);
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPageEnd()
{
	ShowPage(m_iTolalPage - 1);
}

void CLS_DlgCfgFacePicMng::OnCbnSelchangeCboFacePicPageNo()
{
	ShowPage(m_cboPageNo.GetCurSel());
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicPath()
{
	CFileDialog clsFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, _T("图片(*.jpg;*.jpeg;*.png)|*.jpg;*.jpeg;*.png||"));
	if (IDOK == clsFileDlg.DoModal())
	{
		m_edtPicPath.SetWindowText(clsFileDlg.GetPathName());
	}
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicAdd()
{
	if (NULL == NetClient_FaceConfig)
	{
		return;
	}

	int iLibKeySel = m_cboLibKey.GetCurSel();
	if (iLibKeySel < 0)
	{
		return;
	}

	FaceEdit tInfo = {0};
	tInfo.iSize = sizeof(tInfo);
	tInfo.iChanNo = m_iChannelNO;
	tInfo.tFace.iLibKey = m_cboLibKey.GetItemData(iLibKeySel);
	m_edtName.GetWindowText(tInfo.tFace.cName, sizeof(tInfo.tFace.cName));
	tInfo.tFace.iSex = m_cboSex.GetItemData(m_cboSex.GetCurSel());
	tInfo.tFace.iNation = m_cboNation.GetCurSel();
	m_dtBirthEnd.GetWindowText(tInfo.tFace.cBirthTime, sizeof(tInfo.tFace.cBirthTime));
	tInfo.tFace.iPlace = MAKELONG(m_cboCity.GetItemData(m_cboCity.GetCurSel()), m_cboProvience.GetItemData(m_cboProvience.GetCurSel()));
	tInfo.tFace.iCertType = m_cboCardType.GetCurSel();
	tInfo.tFace.iModeling = TRUE;
	m_edtCarNum.GetWindowText(tInfo.tFace.cCertNum, sizeof(tInfo.tFace.cCertNum));
	m_edtPicPath.GetWindowText(tInfo.cFacePic, sizeof(tInfo.cFacePic));

	if (strlen(tInfo.tFace.cName) || strlen(tInfo.cFacePic))
	{
		AddLog(LOG_TYPE_FAIL, "", "failed, name(%s), path(%s).", tInfo.tFace.cName, tInfo.cFacePic);
		return;
	}

	FaceReply tReply= {0};
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_EDIT, m_iChannelNO, &tInfo, sizeof(FaceEdit), &tReply, sizeof(FaceReply));
	if (RET_SUCCESS != iRet || RET_SUCCESS != tReply.iResult)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_FaceConfig add failed, ret(%d), reply(%d).", iRet, tReply.iResult);
	}
	else
	{
		ShowPage(m_iCurPage);
	}
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicMdy()
{
	POSITION pPos = m_lstFacePic.GetFirstSelectedItemPosition();
	if (NULL == pPos || NULL == NetClient_FaceConfig)
	{
		return;
	}
	int iPos = m_lstFacePic.GetNextSelectedItem(pPos);
	if (iPos < 0 || iPos >= m_tQueryResult[0].iPageCount)
	{
		return;
	}

	FaceEdit tInfo = {0};
	tInfo.tFace = m_tQueryResult[iPos].tFace;
	m_edtName.GetWindowText(tInfo.tFace.cName, sizeof(tInfo.tFace.cName));
	tInfo.tFace.iSex = m_cboSex.GetCurSel();
	tInfo.tFace.iNation = m_cboNation.GetCurSel();
	m_dtBirthEnd.GetWindowText(tInfo.tFace.cBirthTime, sizeof(tInfo.tFace.cBirthTime));
	tInfo.tFace.iPlace = MAKELONG(m_cboCity.GetItemData(m_cboCity.GetCurSel()), m_cboProvience.GetItemData(m_cboProvience.GetCurSel()));
	tInfo.tFace.iCertType = m_cboCardType.GetCurSel();
	m_edtCarNum.GetWindowText(tInfo.tFace.cCertNum, sizeof(tInfo.tFace.cCertNum));

	if (strlen(tInfo.tFace.cName) <= 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "failed, name is empty.");
		return;
	}

	FaceReply tReply= {0};
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_EDIT, m_iChannelNO, &tInfo, sizeof(FaceEdit), &tReply, sizeof(FaceReply));
	if (RET_SUCCESS != iRet || RET_SUCCESS != tReply.iResult)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_FaceConfig add failed, ret(%d), reply(%d).", iRet, tReply.iResult);
	}
	else
	{
		ShowPage(m_iCurPage);
	}
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicDel()
{
	POSITION pPos = m_lstFacePic.GetFirstSelectedItemPosition();
	if (NULL == pPos || NULL == NetClient_FaceConfig)
	{
		return;
	}
	int iPos = m_lstFacePic.GetNextSelectedItem(pPos);
	if (iPos < 0 || iPos >= m_tQueryResult[0].iPageCount)
	{
		return;
	}

	FaceDelete tDelete = {0};
	tDelete.iSize = sizeof(tDelete);
	tDelete.iChanNo = m_iChannelNO;
	tDelete.iLibKey = m_tQueryResult[iPos].tFace.iLibKey;
	tDelete.iFaceKey = m_tQueryResult[iPos].tFace.iFaceKey;	
	FaceReply tReply= {0};
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_DELETE, m_iChannelNO, &tDelete, sizeof(tDelete), &tReply, sizeof(FaceReply));
	if (RET_SUCCESS != iRet || RET_SUCCESS != tReply.iResult)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_FaceConfig delete failed, ret(%d), reply(%d).", iRet, tReply.iResult);
	}
	else
	{
		ShowPage(m_iCurPage);
	}
}

void CLS_DlgCfgFacePicMng::OnNMClickLstFacePicInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	FaceQueryResult tInfo = {0};
	int iIndex = pNMItemActivate->iItem;
	if (iIndex >= 0 && iIndex < FACE_MAX_PAGE_COUNT)
	{
		tInfo = m_tQueryResult[iIndex];
	}

	m_edtName.SetWindowText(tInfo.tFace.cName);
	m_cboSex.SetCurSel(tInfo.tFace.iSex);
	m_cboNation.SetCurSel(tInfo.tFace.iNation);
	m_cboCardType.SetCurSel(tInfo.tFace.iCertType);
	m_edtCarNum.SetWindowText(tInfo.tFace.cCertNum);

	COleDateTime tmBirthday = COleDateTime::GetCurrentTime();
	if (strlen(tInfo.tFace.cBirthTime) > 0)
	{
		tmBirthday.ParseDateTime(tInfo.tFace.cBirthTime,LOCALE_NOUSEROVERRIDE);
	}	
	m_dtBirthEnd.SetTime(tmBirthday);

	//todo 省市
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicMode()
{
	if (m_iTolalPage <= 0) {
		return;
	}

	//首先暂停智能分析算法，否则建模会失败
	SetVcaStatue(VCA_SUSPEND_STATUS_PAUSE);
	m_stcProcess.SetWindowText("");

	FaceModeling tInfo = {0};
	tInfo.iSize = sizeof(tInfo);
	tInfo.iChanNo = m_iChannelNO;
	tInfo.iType = m_cboModeType.GetCurSel();
	if (MODING_TYPE_SINGLE == tInfo.iType) {	//单张图片建模
		//获取选中的行号
		POSITION pPos = m_lstFacePic.GetFirstSelectedItemPosition();
		if (NULL == pPos) {
			return;
		}
		int iPos = m_lstFacePic.GetNextSelectedItem(pPos);
		if (iPos < 0 || iPos > FACE_MAX_PAGE_COUNT) {
			return;
		}
		tInfo.iLibKey = m_tQueryResult[iPos].tFace.iLibKey;
		//人脸key最多可以有20个
		tInfo.iFaceNum = 1;
		tInfo.iFaceKey[0] = m_tQueryResult[iPos].tFace.iFaceKey;
	} else {	//批量建模
		tInfo.iLibKey = m_tQueryResult[0].tFace.iLibKey;
	}
	
	FaceReply tResult = {0};
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_MODEL, m_iChannelNO, &tInfo, sizeof(tInfo), &tResult, sizeof(FaceReply));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_FaceConfig, set mode(%d) failed, ret(%d).", tInfo.iType, iRet);
	}
	m_tModeInfo = tInfo;
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicModeStop()
{
	FaceModeling tInfo = m_tModeInfo;
	memset(&m_tModeInfo, 0, sizeof(m_tModeInfo));

	if (NULL == NetClient_FaceConfig) {
		return;
	}
	//没有建模，不用停止
	if (tInfo.iSize <= 0) {
		return;
	}
	tInfo.iType = MODING_TYPE_CANCEL;

	FaceReply tResult = {0};
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_MODEL, m_iChannelNO, &tInfo, sizeof(tInfo), &tResult, sizeof(FaceReply));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_FaceConfig, stop mode failed, ret(%d).", iRet);
	}

	//恢复智能分析算法
	SetVcaStatue(VCA_SUSPEND_STATUS_RESUME);
}

bool CLS_DlgCfgFacePicMng::SetVcaStatue(int _iStatus)
{
	bool bPause = true;
	int iTrackStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iTrackStatus, sizeof(int));
	if (RET_SUCCESS != iRet)
	{
		bPause = false;
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig, set VCA state(%d) failed, ret(%d).", _iStatus, iRet);	
	}
	return bPause;
}

void CLS_DlgCfgFacePicMng::OnBnClickedBtnFacePicLibQuery()
{
	UI_Updata();
}
