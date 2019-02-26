
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VcaQueryFile.h"

typedef enum{
	ITEM_INDEX = 0,						//序号
	ITEM_VCA_TYPE,						//智能分析类型
	ITEM_CHAN_NO,						//通道号
	ITEM_FILE_TYPE,						//文件类型
	ITEM_FILE1_ATTR,					//文件1属性
	ITEM_FILE2_ATTR,					//文件2属性
	ITEM_BEG_TIME,						//开始时间
	ITEM_END_TIME,						//结束时间
	ITEM_EX_ATTR1,						//扩展属性1
	ITEM_EX_ATTR2,						//扩展属性2
	ITEM_EX_ATTR3,						//扩展属性3
	ITEM_EX_ATTR4,						//扩展属性4
}ITEM_VCAFILE;

IMPLEMENT_DYNAMIC(CLS_DlgCfgVcaQueryFile, CDialog)

CLS_DlgCfgVcaQueryFile::CLS_DlgCfgVcaQueryFile(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgCfgVcaQueryFile::IDD, pParent)
{
	m_iCurPageNo = 0;
	m_iTotalPage = 0;
	m_iCurChanPageNo = 0;
	m_iTotalChanPage = 0;
	memset(&m_tQueryChan, 0, sizeof(m_tQueryChan));
	memset(&m_tQueryInfo, 0, sizeof(m_tQueryInfo));
}

CLS_DlgCfgVcaQueryFile::~CLS_DlgCfgVcaQueryFile()
{
}

void CLS_DlgCfgVcaQueryFile::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_ALL, m_chkVcaTypeAll);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_TRIP, m_chkVcaTypeTrip);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_DB_TRIP, m_chkVcaTypeDbTrip);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_BDY, m_chkVcaTypeBoundary);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_LOITER, m_chkVcaTypeLoiter);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_PARK, m_chkVcaTypePark);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_RUN, m_chkVcaTypeRun);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_STOEN, m_chkVcaTypeStolen);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_LEFT, m_chkVcaTypeLeft);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_FACE, m_chkVcaTypeFace);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_ALERT, m_chkVcaTypeAlert);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_LPR, m_chkVcaTypeLPR);
	DDX_Control(pDX, IDC_CHK_VCA_TYPE_SAFEHAT, m_chkVcaTypeHelmet);
	DDX_Control(pDX, IDC_DT_VCA_START, m_dtBeg);
	DDX_Control(pDX, IDC_DT_VCA_END, m_dtEnd);
	DDX_Control(pDX, IDC_CBO_VCA_FILE_TYPE, m_cboFileType);
	DDX_Control(pDX, IDC_LST_VCA_FILE_INFO, m_lstVcaFile);
	DDX_Control(pDX, IDC_STC_VCA_PAGE_INFO, m_stcPageInfo);
	DDX_Control(pDX, IDC_CHK_VCA_CHAN_ALL, m_chkChanAll);
	for (int i = 0; i < LEN_32; ++i)
	{
		DDX_Control(pDX, IDC_STC_CHAN_1 + i, m_stcChanNo[i]);
		DDX_Control(pDX, IDC_CHK_CHAN_1 + i, m_chkChanNo[i]);
	}
	DDX_Control(pDX, IDC_CBO_VCA_CHAN_PAGE, m_cboChanPageNo);
}


BEGIN_MESSAGE_MAP(CLS_DlgCfgVcaQueryFile, CLS_BasePage)
	ON_BN_CLICKED(IDC_CHK_VCA_TYPE_ALL, &CLS_DlgCfgVcaQueryFile::OnBnClickedChkVcaTypeAll)
	ON_BN_CLICKED(IDC_BTN_VCA_QUERY, &CLS_DlgCfgVcaQueryFile::OnBnClickedBtnQuery)
	ON_BN_CLICKED(IDC_BTN_VCA_PAGE_FIRST, &CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPageFirst)
	ON_BN_CLICKED(IDC_BTN_VCA_PAGE_PRE, &CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPagePre)
	ON_BN_CLICKED(IDC_BTN_VCA_PAGE_NEXT, &CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPageNext)
	ON_BN_CLICKED(IDC_BTN_VCA_PAGE_LAST, &CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPageLast)
	ON_BN_CLICKED(IDC_BTN_VCA_CHAN_PAGE_PRE, &CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPreChanPage)
	ON_BN_CLICKED(IDC_BTN_VCA_CHAN_PAGE_NEXT, &CLS_DlgCfgVcaQueryFile::OnBnClickedBtnNextChanPage)
	ON_CBN_SELCHANGE(IDC_CBO_VCA_CHAN_PAGE, &CLS_DlgCfgVcaQueryFile::OnCbnSelchangeCboChanPage)
	ON_BN_CLICKED(IDC_CHK_VCA_CHAN_ALL, &CLS_DlgCfgVcaQueryFile::OnBnClickedChekChanAll)
END_MESSAGE_MAP()


BOOL CLS_DlgCfgVcaQueryFile::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_dtBeg.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_dtEnd.SetFormat("yyyy-MM-dd HH:mm:ss");

	InitUI();

	return TRUE; 
}

void CLS_DlgCfgVcaQueryFile::InitUI()
{
	m_cboFileType.SetItemData(m_cboFileType.AddString("全部"), 0);
	m_cboFileType.SetItemData(m_cboFileType.AddString("录像"), 1);
	m_cboFileType.SetItemData(m_cboFileType.AddString("图片"), 2);
	m_cboFileType.SetCurSel(2);
	
	//初始化列表
	m_lstVcaFile.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_lstVcaFile.InsertColumn(ITEM_INDEX, "序号", LVCFMT_LEFT, 40, -1);
	m_lstVcaFile.InsertColumn(ITEM_VCA_TYPE, "智能分析类型", LVCFMT_LEFT, 40, -1);
	m_lstVcaFile.InsertColumn(ITEM_CHAN_NO, "通道号", LVCFMT_LEFT, 40, -1);	
	m_lstVcaFile.InsertColumn(ITEM_FILE_TYPE, "文件类型", LVCFMT_LEFT, 40, -1);	
	m_lstVcaFile.InsertColumn(ITEM_FILE1_ATTR, "文件1属性", LVCFMT_LEFT, 90, -1);
	m_lstVcaFile.InsertColumn(ITEM_FILE2_ATTR, "文件2属性", LVCFMT_LEFT, 90, -1);
	m_lstVcaFile.InsertColumn(ITEM_BEG_TIME, "开始时间", LVCFMT_LEFT, 70, -1);
	m_lstVcaFile.InsertColumn(ITEM_END_TIME, "结束时间", LVCFMT_LEFT, 70, -1);
	m_lstVcaFile.InsertColumn(ITEM_EX_ATTR1, "扩展属性1", LVCFMT_LEFT, 80, -1);	
	m_lstVcaFile.InsertColumn(ITEM_EX_ATTR2, "扩展属性2", LVCFMT_LEFT, 80, -1);
	m_lstVcaFile.InsertColumn(ITEM_EX_ATTR3, "扩展属性3", LVCFMT_LEFT, 80, -1);
	m_lstVcaFile.InsertColumn(ITEM_EX_ATTR4, "扩展属性4", LVCFMT_LEFT, 80, -1);	
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedChkVcaTypeAll()
{
	BOOL blCheck = !m_chkVcaTypeAll.GetCheck();

	m_chkVcaTypeTrip.EnableWindow(blCheck);
	m_chkVcaTypeDbTrip.EnableWindow(blCheck);
	m_chkVcaTypeBoundary.EnableWindow(blCheck);
	m_chkVcaTypeLoiter.EnableWindow(blCheck);
	m_chkVcaTypePark.EnableWindow(blCheck);
	m_chkVcaTypeRun.EnableWindow(blCheck);
	m_chkVcaTypeStolen.EnableWindow(blCheck);
	m_chkVcaTypeLeft.EnableWindow(blCheck);
	m_chkVcaTypeFace.EnableWindow(blCheck);
	m_chkVcaTypeAlert.EnableWindow(blCheck);
	m_chkVcaTypeLPR.EnableWindow(blCheck);
	m_chkVcaTypeHelmet.EnableWindow(blCheck);
}

void CLS_DlgCfgVcaQueryFile::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	int iCurLogonId = m_iLogonID;
	CLS_BasePage::OnChannelChanged(_iLogonID, _iChannelNo, _iStreamNo);
	if (iCurLogonId != _iLogonID)
	{
		int iChannelNum = 0;
		NetClient_GetChannelNum(_iLogonID, &iChannelNum);
		m_cboChanPageNo.ResetContent();
		m_iTotalChanPage = iChannelNum/LEN_32;
		if (0 != (iChannelNum%LEN_32) && iChannelNum > 0)
		{
			m_iTotalChanPage ++;
		}

		for (int i = 0; i < m_iTotalChanPage; ++i)
		{
			m_cboChanPageNo.InsertString(i, IntToCString(i+1));
		}
		m_cboChanPageNo.SetCurSel(0);
		m_iCurChanPageNo = -1;
		OnCbnSelchangeCboChanPage();
	}	
}

int CLS_DlgCfgVcaQueryFile::GetVcaTypeList(int* _piList, int _iMaxCount)
{
	int iCount = 0;
	
	if (m_chkVcaTypeAll.GetCheck())
	{
		iCount = 1;
		_piList[0] = 0x7FFFFFFF;
	}
	else
	{
		if (m_chkVcaTypeTrip.GetCheck()){
			_piList[iCount++] = VCA_EVENT_TRIPWIRE;
		}
		if (m_chkVcaTypeDbTrip.GetCheck()){
			_piList[iCount++] = VCA_EVENT_DBTRIPWIRE;
		}
		if (m_chkVcaTypeBoundary.GetCheck()){
			_piList[iCount++] = VCA_EVENT_PERIMETER;
		}
		if (m_chkVcaTypeLoiter.GetCheck()){
			_piList[iCount++] = VCA_EVENT_LOITER;
		}
		if (m_chkVcaTypePark.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_PARKING;
		}
		if (m_chkVcaTypeRun.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_RUN;
		}
		if (m_chkVcaTypeStolen.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_ABANDUM;
		}
		if (m_chkVcaTypeLeft.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_OBJSTOLEN;
		}	
		if (m_chkVcaTypeFace.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_FACEREC;
		}
		if (m_chkVcaTypeAlert.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_PROTECT;
		}
		if (m_chkVcaTypeLPR.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_PLATE_RECOGNISE;
		}
		if (m_chkVcaTypeHelmet.GetCheck()) {
			_piList[iCount++] = VCA_EVENT_HELMET;
		}
	}
	return iCount;
}

int CLS_DlgCfgVcaQueryFile::GetChanList(QueryChanNo* _pList, int _iMaxCount)
{
	int iCount = 0;
	if (m_chkChanAll.GetCheck())
	{
		iCount = 1;
		_pList->iChanNo = 0x7FFFFFFF;
	}
	else
	{
		for (int i = 0; i < LEN_32; ++i)
		{
			if (m_chkChanNo[i].GetCheck())
			{
				iCount++;
				_pList->iChanNo = i + m_iCurChanPageNo*LEN_32;
			}
		}
	}
	return iCount;
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedBtnQuery()
{
	if (NULL == NetClient_Query_V5)
	{
		return;
	}

	memset(&m_tQueryChan, 0, sizeof(m_tQueryChan));
	memset(&m_tQueryInfo, 0, sizeof(m_tQueryInfo));

	NetFileQueryVca &tQuery = m_tQueryInfo;
	tQuery.iSize = sizeof(tQuery);
	
	//通道列表
	tQuery.iChanCount = GetChanList(&m_tQueryChan[0], MAX_QUERY_LIST_COUNT);
	tQuery.iChanSize = sizeof(QueryChanNo);
	tQuery.pChanList = &m_tQueryChan[0];

	//智能分析列表,最多32个
	tQuery.iVcaCount = GetVcaTypeList(tQuery.iVcaList, MAX_QUERY_LIST_COUNT);

	//开始结束时间
	GetNvsFileTime(&m_dtBeg, tQuery.tBegTime);
	GetNvsFileTime(&m_dtEnd, tQuery.tEndTime);

	//页码信息
	tQuery.iPageCount = MAX_QUERY_PAGE_COUNT;
	tQuery.iPageNo = 0;

	//文件类型
	tQuery.iFileType = m_cboFileType.GetCurSel();

	ShowPage(0, &tQuery, TRUE);
}

CString GetFileTypeStr(int _iType)
{
	CString cstr;
	if (1 == _iType) {
		cstr = "录像";
	} else if (2 == _iType) {
		cstr = "图片";
	} else {
		cstr = IntToCString(_iType);
	}
	return cstr;
}

CString GetVcaTypeStr(int _iType)
{
	CString cstr;
	if (VCA_EVENT_TRIPWIRE == _iType) {
		cstr = "单伴线";
	} else if (VCA_EVENT_DBTRIPWIRE == _iType) {
		cstr = "双伴线";
	} else if (VCA_EVENT_PERIMETER == _iType) {
		cstr = "周界检测";
	} else if (VCA_EVENT_LOITER == _iType) {
		cstr = "徘徊";
	} else if (VCA_EVENT_PARKING == _iType) {
		cstr = "停车";
	} else if (VCA_EVENT_RUN == _iType) {
		cstr = "奔跑";
	} else if (VCA_EVENT_ABANDUM == _iType) {
		cstr = "被盗物";
	} else if (VCA_EVENT_OBJSTOLEN == _iType) {
		cstr = "遗弃物";
	} else if (VCA_EVENT_FACEREC == _iType) {
		cstr = "人脸识别 ";
	} else if (VCA_EVENT_PROTECT == _iType) {
		cstr = "警戒";
	} else if (VCA_EVENT_PLATE_RECOGNISE == _iType) {
		cstr = "车牌识别";
	} else if (VCA_EVENT_HELMET == _iType) {
		cstr = "安全帽检测";
	} else {
		cstr = IntToCString(_iType);
	}
	return cstr;
}

CString GetPicTypeStr(int _iType)
{
	CString cstr;
	if (1 == _iType) {
		cstr = "小图";
	} else if (2 == _iType) {
		cstr = "大图";
	} else if (0 == _iType) {
		cstr = "无";
	} else {
		cstr = IntToCString(_iType);
	}
	return cstr;
}

CString GetFileAttr(VcaFileAttr& _tInfo)
{
	CString cstr;
	cstr.Format("文件序号:%d；文件名称:%s；文件大小:%d；文件属性:%s", _tInfo.iFileIndex, _tInfo.cFileName,
		_tInfo.iFileSize, GetPicTypeStr(_tInfo.iFileType));
	return cstr;
}

CString GetTimeStr(NVS_FILE_TIME& _tInfo)
{
	CString cstr;
	cstr.Format("%04d-%02d-%02d %02d:%02d:%02d", _tInfo.iYear, _tInfo.iMonth, _tInfo.iDay,
		_tInfo.iHour, _tInfo.iMinute, _tInfo.iSecond);
	return cstr;
}

CString GetFieldAttr(int _iVcaType, int _iIndex, CString _cSrc)
{
	CString cstr;
	int iValue = atoi(_cSrc);

	if (VCA_EVENT_FACEREC == _iVcaType) {
		if (1 == _iIndex) {
			cstr = "年龄:" + _cSrc;
		} else if (2 == _iIndex) {
			if (1 == iValue) {
				cstr = "男";
			} else if (2 == iValue) {
				cstr = "女";
			} else if (3 == iValue) {
				cstr = "未知";
			} else {
				cstr = _cSrc;
			}
		} else if (3 == _iIndex) {
			if (1 == iValue) {
				cstr = "汉族";
			} else if (2 == iValue) {
				cstr = "少数民族";
			} else {
				cstr = _cSrc;
			}
		} 
	} else if (VCA_EVENT_PROTECT == _iVcaType) {
		if (1 == _iIndex) {
			if (1 == iValue) {
				cstr = "人";
			} else if (2 == iValue) {
				cstr = "车";
			} else if (3 == iValue) {
				cstr = "其他";
			} else {
				cstr = _cSrc;
			}
		}else if (2 == _iIndex) {
			if (1 == iValue) {
				cstr = "周界-入侵";
			} else if (2 == iValue) {
				cstr = "周界-离开";
			} else if (3 == iValue) {
				cstr = "绊线";
			} else if (0x7FFFFFFF == iValue) {
				cstr = "全部";
			}else {
				cstr = _cSrc;
			}
		}		
	} else if (VCA_EVENT_PLATE_RECOGNISE == _iVcaType) {
		cstr = _cSrc;
	} else if (VCA_EVENT_HELMET == _iVcaType) {
		if (1 == iValue) {
			cstr = "红色";
		} else if (2 == iValue) {
			cstr = "黄色";
		} else if (3 == iValue) {
			cstr = "蓝色";
		} else if (4 == iValue) {
			cstr = "白色";
		} else if (5 == iValue) {
			cstr = "其他";
		} else {
			cstr = _cSrc;
		}
	} else {
		cstr = _cSrc;
	}
	return cstr;
}

void CLS_DlgCfgVcaQueryFile::ShowPage(int _iPageNo, NetFileQueryVca* _pInfo, BOOL _blFirst)
{
	m_lstVcaFile.DeleteAllItems();

	if (NULL == _pInfo || _iPageNo < 0)
	{
		return;
	}

	if (!_blFirst && m_iTotalPage <= 0)
	{
		MessageBox("请先查询!", GetTextEx(IDS_LOG_OPERATION_MSG), MB_OK);
		return;
	}

	if (!_blFirst && _iPageNo >= m_iTotalPage)
	{
		return;
	}

	m_iCurPageNo = _iPageNo;
	_pInfo->iPageNo = _iPageNo;

	NetFileQueryVcaResult tResult[MAX_QUERY_PAGE_COUNT] = {0};
	int iRet = NetClient_Query_V5(m_iLogonID, CMD_NETFILE_QUERY_VCA, m_iChannelNO, _pInfo, sizeof(NetFileQueryVca), &tResult, sizeof(NetFileQueryVcaResult));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","ShowPage(%d) failed.", _iPageNo);
		return;
	}

	//列表中更新数据
	int iCount = tResult[0].iCurPageCount;
	for (int i = 0; i < iCount && i < MAX_QUERY_PAGE_COUNT; ++i)
	{
		int iItem = m_lstVcaFile.GetItemCount();
		m_lstVcaFile.InsertItem(iItem, "");

		NetFileQueryVcaResult tInfo = tResult[i];
		m_lstVcaFile.SetItemText(iItem, ITEM_INDEX, IntToCString(i + 1));
		m_lstVcaFile.SetItemText(iItem, ITEM_CHAN_NO, IntToCString(tInfo.iChanNo));
		m_lstVcaFile.SetItemText(iItem, ITEM_VCA_TYPE, GetVcaTypeStr(tInfo.iVcaType));
		m_lstVcaFile.SetItemText(iItem, ITEM_FILE_TYPE, GetFileTypeStr(tInfo.iFileType));		
		if (tInfo.iFileAttrCount > 0) {
			m_lstVcaFile.SetItemText(iItem, ITEM_FILE1_ATTR, GetFileAttr(tInfo.tFileAttr[0]));
		}
		if (tInfo.iFileAttrCount > 1) {
			m_lstVcaFile.SetItemText(iItem, ITEM_FILE2_ATTR, GetFileAttr(tInfo.tFileAttr[1]));
		}
		m_lstVcaFile.SetItemText(iItem, ITEM_BEG_TIME, GetTimeStr(tInfo.tBegTime));
		m_lstVcaFile.SetItemText(iItem, ITEM_END_TIME, GetTimeStr(tInfo.tEndTime));

		if (tInfo.iExAttrCount > 0){
			m_lstVcaFile.SetItemText(iItem, ITEM_EX_ATTR1, GetFieldAttr(tInfo.iVcaType, 1, tInfo.cExAttr[0]));
		}
		if (tInfo.iExAttrCount > 1) {
			m_lstVcaFile.SetItemText(iItem, ITEM_EX_ATTR2, GetFieldAttr(tInfo.iVcaType, 2, tInfo.cExAttr[1]));
		}
		if (tInfo.iExAttrCount > 2) {
			m_lstVcaFile.SetItemText(iItem, ITEM_EX_ATTR3, GetFieldAttr(tInfo.iVcaType, 3, tInfo.cExAttr[2]));
		}
		if (tInfo.iExAttrCount > 3) {
			m_lstVcaFile.SetItemText(iItem, ITEM_EX_ATTR4, GetFieldAttr(tInfo.iVcaType, 4, tInfo.cExAttr[3]));
		}	
	}	
	CString cstrPage;
	m_iTotalPage = tResult[0].iTotal/MAX_QUERY_PAGE_COUNT;
	if (0 != tResult[0].iTotal%MAX_QUERY_PAGE_COUNT)
	{
		m_iTotalPage++;
	}
	cstrPage.Format("%d/%d", (_iPageNo + 1), m_iTotalPage);
	m_stcPageInfo.SetWindowText(cstrPage);
}


void CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPageFirst()
{
	ShowPage(0, &m_tQueryInfo);
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPagePre()
{
	ShowPage(m_iCurPageNo - 1, &m_tQueryInfo);
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPageNext()
{
	ShowPage(m_iCurPageNo + 1, &m_tQueryInfo);
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPageLast()
{
	ShowPage(m_iTotalPage - 1, &m_tQueryInfo);
}

void CLS_DlgCfgVcaQueryFile::OnCbnSelchangeCboChanPage()
{
	ShowChanPage(m_cboChanPageNo.GetCurSel());
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedBtnPreChanPage()
{
	ShowChanPage(m_iCurChanPageNo - 1);
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedBtnNextChanPage()
{
	ShowChanPage(m_iCurChanPageNo + 1);
}

void CLS_DlgCfgVcaQueryFile::ShowChanPage(int _iPageNo)
{
	if (_iPageNo < 0 || _iPageNo >= m_iTotalChanPage || m_iCurChanPageNo == _iPageNo)
	{
		return;
	}

	int iChannelNum = 0;
	NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	if (iChannelNum <= 0)
	{
		return;
	}

	m_iCurChanPageNo = _iPageNo;
	m_cboChanPageNo.SetCurSel(_iPageNo);

	for (int i = 0; i < LEN_32; ++i)
	{
		int iChanNo = i + _iPageNo*LEN_32;
		m_stcChanNo[i].SetWindowText(IntToCString(iChanNo + 1));
		m_chkChanNo[i].SetCheck(FALSE);
		m_chkChanNo[i].EnableWindow(iChanNo < iChannelNum ? TRUE : FALSE);
	}
}

void CLS_DlgCfgVcaQueryFile::OnBnClickedChekChanAll()
{
	int iChannelNum = 0;
	NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	if (iChannelNum <= 0)
	{
		return;
	}

	int iEnable = m_chkChanAll.GetCheck();
	for (int i = 0; i < LEN_32; ++i)
	{
		int iChanNo = i + m_iCurChanPageNo*LEN_32;
		if (iChanNo >= iChannelNum)
		{
			m_chkChanNo[i].EnableWindow(FALSE);
		}
		else
		{
			m_chkChanNo[i].EnableWindow(!iEnable);
		}	
	}
}
