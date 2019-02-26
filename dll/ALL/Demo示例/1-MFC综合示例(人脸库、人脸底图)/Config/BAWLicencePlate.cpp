#include "stdafx.h"
#include "NetClientDemo.h"
#include "BAWLicencePlate.h"


// CLS_BAWLicencePlate dialog
#define BLACKENABLE 1 //黑牌车使能
#define LISENCE_PARAM_OK	100 //导入进度条进度100,导入成功
#define LISENCE_PARAM_ERROR -1 //导入失败
#define CURRENTSHOWCOUNT 25//当前显示条数
#define DEFAULT_PAGEID 1 //默认页编号

IMPLEMENT_DYNAMIC(CLS_BAWLicencePlate, CDialog)

CLS_BAWLicencePlate::CLS_BAWLicencePlate(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_BAWLicencePlate::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_BAWLicencePlate::~CLS_BAWLicencePlate()
{
	
}

void CLS_BAWLicencePlate::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_DNVR_BAWLICENCEPLATE_QUERYLIST, m_lstQueryList);
	DDX_Control(pDX, IDC_CHK_DNVR_BAWLICENCEPLATE_BLACKENABLE, m_chkBalckEnable);
	DDX_Control(pDX, IDC_EDT_NDVR_BAWLICENCEPLATE_PATH, m_edtFilePath);
}

BEGIN_MESSAGE_MAP(CLS_BAWLicencePlate, CDialog)
	ON_BN_CLICKED(IDC_BTN_DNVR_BAWLICENCEPLATE_QUERY, &CLS_BAWLicencePlate::OnBnClickedBtnDnvrBawlicenceplateQuery)
	ON_BN_CLICKED(IDC_BTN_NDVR_BAWLICENCEPALTE_SET, &CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicencepalteSet)
	ON_BN_CLICKED(IDC_BTN_NDVR_BAWLICENCEPLATE_BROWSER, &CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicenceplateBrowser)
	ON_BN_CLICKED(IDC_BTN_NDVR_BAWLICENCEPLATE_INPUT, &CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicenceplateInput)
	ON_BN_CLICKED(IDC_BTN_NDVR_BAWLICENCEPLATE_OUTPUT, &CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicenceplateOutput)
END_MESSAGE_MAP()

// CLS_BAWLicencePlate message handlers

BOOL CLS_BAWLicencePlate::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	// TODO:  Add extra initialization here
	UI_UpdateDialogText();
	UpdateListInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_BAWLicencePlate::UI_UpdateDialogText()
{
	m_lstQueryList.DeleteColumn(0);
	m_lstQueryList.InsertColumn(0, GetTextEx(IDS_CONFIG_DNVR_BAWLICENCEPLATE_LICENCEPLATE), 0, 500);
	SetDlgItemTextEx(IDC_GBO_DNVR_BANDW_LICENCEPLATE_ENABLE, IDS_CONFIG_DNVR_BAWLICENCEPLATE_ENABLE);
	SetDlgItemTextEx(IDC_CHK_DNVR_BAWLICENCEPLATE_BLACKENABLE, IDS_CONFIG_DNVR_BAWLICENCEPLATE_BLACKENABLE);
	SetDlgItemTextEx(IDC_BTN_NDVR_BAWLICENCEPALTE_SET, IDS_CONFIG_DNVR_BAWLICENCEPLATE_ENABLE_SET);
	SetDlgItemTextEx(IDC_GBO_NEVR_BAWLICENCEPLATE_QUERY, IDS_CONFIG_DNVR_BAWLICENCEPLATE_GBOQUERY);
	SetDlgItemTextEx(IDC_STC_NDVR_BAWLICENCEPLATE_PAGETOTAL, IDS_CONFIG_DNVR_BAWLICENCEPLATE_STCPAGETOTAL);
	SetDlgItemTextEx(IDC_STC_DNVR_BAWLICENCEPLATE_PAGESIZE, IDS_CONFIG_DNVR_BAWLICENCEPLATE_STCPAGESIZE);
	SetDlgItemTextEx(IDC_STC_DNVR_BAWLICENCEPLATE_PAGEID, IDS_CONFIG_DNVR_BAWLICENCEPLATE_STCPAGEID);
	SetDlgItemTextEx(IDC_BTN_DNVR_BAWLICENCEPLATE_QUERY, IDS_CONFIG_DNVR_BAWLICENCEPLATE_BTNQUERY);
	SetDlgItemTextEx(IDC_GBO_NDVR_BAWLICENCEPLATE_IOPUTFILE, IDS_CONFIG_DNVR_BAWLICENCEPLATE_GBOIOPUT);
	SetDlgItemTextEx(IDC_STC_NDVR_BAWLICENCEPLATE_FILEPATH, IDS_CONFIG_DNVR_BAWLICENCEPLATE_STCFILEPATH);
	SetDlgItemTextEx(IDC_BTN_NDVR_BAWLICENCEPLATE_BROWSER, IDS_CONFIG_DNVR_BAWLICENCEPLATE_BTNBROWER);
	SetDlgItemTextEx(IDC_BTN_NDVR_BAWLICENCEPLATE_INPUT, IDS_CONFIG_DNVR_BAWLICENCEPLATE_BTNINPUT);
	SetDlgItemTextEx(IDC_BTN_NDVR_BAWLICENCEPLATE_OUTPUT, IDS_CONFIG_DNVR_BAWLICENCEPLATE_BTNOUTPUT);	
}

void CLS_BAWLicencePlate::UpdateListInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[BAWLicencePlate::UpdateListInfo]Invalid logon id(%d)", m_iLogonID);
		return;
	}
	m_lstQueryList.DeleteAllItems();
	PlateListQueryGet tPlateListQueryGet = {0};
	tPlateListQueryGet.iSize = sizeof(PlateListQueryGet);
	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_PLATE_LIST_QUERY, m_iChannelNo, &tPlateListQueryGet, sizeof(tPlateListQueryGet));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[BAWLicencePlate::UpdateListInfo][PLATE_LIST_QUERY] Set fail,error = %d", GetLastError());
	}
	else
	{
		for(int i = 0; i < tPlateListQueryGet.iShow; i++)
		{
			if(NULL != tPlateListQueryGet.cPlate[i])
			{
				m_lstQueryList.InsertItem(i, tPlateListQueryGet.cPlate[i]);
			}		
		}
		SetDlgItemInt(IDC_EDT_NDVR_BAWLICENCEPLATE_PAGETOTAL, tPlateListQueryGet.iTotal);
		SetDlgItemInt(IDC_EDT_NDVR_BAWLICENCEPLATE_PAGESIZE, tPlateListQueryGet.iShow);	
		SetDlgItemInt(IDC_EDT_DNVR_BAWLICENCEPLATE_PAGEID, tPlateListQueryGet.iPageNo);
	}
}

void CLS_BAWLicencePlate::UpdateListType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[BAWLicencePlate::UpdateListType]Invalid logon id(%d)", m_iLogonID);
		return;
	}
	PlateListType tPlateListType = {0};
	tPlateListType.iSize = sizeof(PlateListType);
	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_LINK_HTTP_INFO, m_iChannelNo, &tPlateListType, sizeof(PlateListType), &iReturnByte);
	if (RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[BAWLicencePlate::UpdateListType][PLATE_LIST_TYPE] Set fail,error = %d", GetLastError());
	}
	else
	{
		if(BLACKENABLE == tPlateListType.iListType)
		{
			m_chkBalckEnable.SetCheck(BLACKENABLE);
		}
		else
		{
			m_chkBalckEnable.SetCheck(tPlateListType.iListType);
		}
	}
}

void CLS_BAWLicencePlate::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	UpdateListType();
	UpdateListInfo();
}

void CLS_BAWLicencePlate::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialogText();
}

void CLS_BAWLicencePlate::OnMainNotify(int _iLogonID,int _iWParam, void* _iLParam, void* _iUser)
{
	if (_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_BAWLicencePlate::OnMainNotify]Invalid logon id(%d)", _iLogonID);
		return;
	}

	int iMessage = _iWParam & 0xFFFF;
	switch (iMessage)
	{
	case WCM_PLATE_LIST_QUERY:
		{
			AddLog(LOG_TYPE_SUCC, "", "[CLS_BAWLicencePlate::BawlicenceplateQuery][PLATE_LIST_QUERY] Query success!");
			UpdateListInfo();	
		}
		break;
	default:
		break;
	}
}

void CLS_BAWLicencePlate::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	if (_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_BAWLicencePlate::OnParamChangeNotify]Invalid logon id(%d)", _iLogonID);
		return;
	}

	if (_iChannelNo == m_iChannelNo)//只刷新参数改变的通道
	{
		switch(_iParaType)
		{
		case  PARA_PLATE_LIST_TYPE:
			{
				AddLog(LOG_TYPE_SUCC, "", "[CLS_BAWLicencePlate::ParamChangeNotify][PLATE_LIST_TYPE] Set enable success!");
				UpdateListType();
			}
			break;
		default:
			break;
		}
	}
}

void CLS_BAWLicencePlate::OnBnClickedBtnDnvrBawlicenceplateQuery()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_BAWLicencePlate:::BawlicenceplateQuery]Invalid logon id(%d)", m_iLogonID);
		return;
	}

	int iPageIDTemp = GetDlgItemInt(IDC_EDT_DNVR_BAWLICENCEPLATE_PAGEID);
	PlateListQuerySet tPlateListQuerySet = {0};
	tPlateListQuerySet.iSessionId = 0;
	tPlateListQuerySet.iPageSize = 25;
	tPlateListQuerySet.iSize = sizeof(PlateListQuerySet);
	if(0 == iPageIDTemp)
	{
		tPlateListQuerySet.iPageNo = DEFAULT_PAGEID;
	}
	tPlateListQuerySet.iPageNo = iPageIDTemp;

	int iRet = NetClient_SendCommand(m_iLogonID,  COMMAND_ID_PLATE_LIST_QUERY, m_iChannelNo, &tPlateListQuerySet, sizeof(PlateListQuerySet));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicenceplateQuery][PLATE_LIST_QUERY] Set fail,error = %d", GetLastError());
	}
}

void CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicencepalteSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_BAWLicencePlate:::BawlicencepalteSet]Invalid logon id(%d)", m_iLogonID);
		return;
	}

	PlateListType tPlateListType = {0};
	tPlateListType.iSize = sizeof(PlateListType);
	int iCheckStatus = m_chkBalckEnable.GetCheck();
	tPlateListType.iListType = iCheckStatus;

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_PLATE_LIST_TYPE, m_iChannelNo, &tPlateListType, sizeof(PlateListType));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicencepalteSet][PLATE_LIST_TYPE] Set fail,error = %d", GetLastError());
	}
}

void CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicenceplateBrowser()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "All files(*.*)|*.*|box files(*.box)|*.box||");
	if (IDOK == fileDlg.DoModal())
	{
		m_cstrFilePath = fileDlg.GetPathName();
		m_edtFilePath.SetWindowText(m_cstrFilePath);
	}
}

void CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicenceplateInput()
{
	// TODO: Add your control notification handler code here
	CString strPathName;
	m_edtFilePath.GetWindowText(strPathName);
	if (strPathName.GetLength() >= 128)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicenceplateInput]Illegal system path!");
		return;
	}
	if (strPathName == "")
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicenceplateInput]Illegal system path!");
		return;
	}
	
	FileTransport stFileTransport = {0};
	stFileTransport.iOptType = TRANSPORT_TYPE_IMPORT;
	strcpy_s(stFileTransport.cLocalFilePath, strPathName);
	stFileTransport.iFileType = 1;
	stFileTransport.iSize = sizeof(FileTransport);
	stFileTransport.pvUserData = this;
	stFileTransport.cbNotify = (TRANSPORT_NOTIFY)LicencePlateInputProgress;
	int iRet = NetClient_SendCommand(m_iLogonID,  COMMAND_ID_FILE_TRANSPORT, m_iChannelNo, &stFileTransport, sizeof(FileTransport));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicenceplateInput][FILE_TRANSPORT] Input fail,error = %d", GetLastError());
	}
}

void CLS_BAWLicencePlate::OnBnClickedBtnNdvrBawlicenceplateOutput()
{
	// TODO: Add your control notification handler code here
	m_cstrOutPutPath = GetSystemOutputPath();
	if (m_cstrOutPutPath.GetLength() >= 128)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicenceplateOutput]Illegal system path!");
		return;
	}
	if (m_cstrOutPutPath == "")
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicenceplateOutput]Illegal system path!");
		return;
	}
	
	FileTransport stFileTransport = {0};
	stFileTransport.iOptType = TRANSPORT_TYPE_EXPORT;
	strcpy_s(stFileTransport.cLocalFilePath, m_cstrOutPutPath);
	stFileTransport.iSize = sizeof(FileTransport);
	stFileTransport.pvUserData = this;
	stFileTransport.iFileType = 1;
	stFileTransport.cbNotify = (TRANSPORT_NOTIFY)LicencePlateOutputProgress;
	int iRet = NetClient_SendCommand(m_iLogonID,  COMMAND_ID_FILE_TRANSPORT, m_iChannelNo, &stFileTransport, sizeof(FileTransport));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::BawlicenceplateOutput][FILE_TRANSPORT] Input fail,error = %d", GetLastError());
	}
}

CString CLS_BAWLicencePlate::GetSystemOutputPath()
{
	CString sFolder = "";   
	COleDateTime m_Date = COleDateTime::GetCurrentTime ();
	CString strFileName;
	strFileName = m_Date.Format("%Y%m%d%H%M%S");                               //导出数据的文件名称
	CFileDialog fileDlg(FALSE, "xls", strFileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("xls files(*.xls)|*.xls||"));
	if (IDOK == fileDlg.DoModal())
	{
		if (fileDlg.GetFileExt() != _T("xls"))
		{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_BAWLicencePlate::OutputPath]Illegal file name!");
		}
		else
		{
			sFolder = fileDlg.GetPathName();
		}
	}
	return sFolder;
}

void CLS_BAWLicencePlate::LicencePlateInputProgress(int _iLogonID, int _iServerState, void* _iUserData)
{
	if(NULL == _iUserData)
	{
		return;
	}

	CLS_BAWLicencePlate* clsLicencePlate = (CLS_BAWLicencePlate*)_iUserData;

	if (LISENCE_PARAM_OK == _iServerState)
	{		
		clsLicencePlate->MessageBox(GetTextEx(IDS_CONFIG_DNVR_BAWLICENCEPLATE_INPUTSUCCESS));
	}
	else if(-1 == _iServerState)
	{
		clsLicencePlate->MessageBox(GetTextEx(IDS_CONFIG_DNVR_BAWLICENCEPLATE_INPUTFAIL));
	}
}

void CLS_BAWLicencePlate::LicencePlateOutputProgress(int _iLogonID, int _iServerState, void* _iUserData)
{
	if(NULL == _iUserData)
	{
		return;
	}

	CLS_BAWLicencePlate* clsLicencePlate = (CLS_BAWLicencePlate*)_iUserData;
	if (LISENCE_PARAM_OK == _iServerState)
	{		
		clsLicencePlate->MessageBox(GetTextEx(IDS_CONFIG_DNVR_BAWLICENCEPLATE_OUTPUTSUCCESS));
	}
	else if(-1 == _iServerState)
	{
		clsLicencePlate->MessageBox(GetTextEx(IDS_CONFIG_DNVR_BAWLICENCEPLATE_OUTPUTFAIL));
	}
}
