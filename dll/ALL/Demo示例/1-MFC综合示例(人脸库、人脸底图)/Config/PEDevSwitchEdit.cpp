// PEDevSwitchEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "PEDevSwitchEdit.h"
#include "DonghuanSet.h"
#include <shlwapi.h>


// CLS_PEDevSwitchEdit dialog

IMPLEMENT_DYNAMIC(CLS_PEDevSwitchEdit, CDialog)

CLS_PEDevSwitchEdit::CLS_PEDevSwitchEdit(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_PEDevSwitchEdit::IDD, pParent)
{
	m_clsPowerEnPage = NULL;
}

CLS_PEDevSwitchEdit::~CLS_PEDevSwitchEdit()
{
	m_clsPowerEnPage = NULL;
}

void CLS_PEDevSwitchEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODESET, m_cboModeSet);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_cboIndex);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtName);
	DDX_Control(pDX, IDC_EDIT_CLEARALARM_TIME, m_edtDisAlarmDelayTime);
	DDX_Control(pDX, IDC_COMBO_SCHDULE2, m_cboAlarmSchedule);
}


BEGIN_MESSAGE_MAP(CLS_PEDevSwitchEdit, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLS_PEDevSwitchEdit::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CLS_PEDevSwitchEdit message handlers

BOOL CLS_PEDevSwitchEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtName.SetLimitText(32);
	m_edtDisAlarmDelayTime.SetLimitText(6);

	CString strIndex;
	for (int i=0; i<MAX_SWITCH_NUM; i++)
	{
		strIndex.Format("%d", i+1);
		m_cboIndex.InsertString(i, strIndex);
	}

	m_cboModeSet.InsertString(0, "Off");
	m_cboModeSet.InsertString(1, "On");

	//布防模板
	if (NetClient_GetAlarmConfig)
	{
		for (int i=0; i<SCHEDULE_NUM; i++)
		{
			AlarmInSchedule srcAlarmInSchedule = {-1};
			srcAlarmInSchedule.iSize = sizeof(AlarmInSchedule);
			int iRet = NetClient_GetAlarmConfig(m_iLogonID,i,-1,CMD_ALARM_IN_SCHEDULE,&srcAlarmInSchedule);
			if (iRet < 0)
			{
				continue;
			}

			if (srcAlarmInSchedule.iEnable == 1)
			{
				string strSchedule = srcAlarmInSchedule.cName;
				m_cboAlarmSchedule.AddString(strSchedule.c_str());
				m_cboAlarmSchedule.SetItemData(m_cboAlarmSchedule.GetCount() - 1, srcAlarmInSchedule.iScheduleNo);
			}
		}
	}

	InitDlgItemInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_PEDevSwitchEdit::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo =  _iChannelNo;
	}

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO = _iStreamNo;
	}
}

void CLS_PEDevSwitchEdit::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_PEDevSwitchEdit::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case 0:
		break;
	default:
		break;
	}
}

void CLS_PEDevSwitchEdit::UI_UpdateDialogText()
{
	SetDlgItemText(IDC_STATIC_INDEX,GetText(IDS_PE_INDEX));
	SetDlgItemText(IDC_STATIC_NAME,GetText(IDS_PE_NAME));
	SetDlgItemText(IDC_STATIC_SCHEDULE,GetText(IDS_PE_SCHEDULE));
	SetDlgItemText(IDC_STATIC_MODESET,GetText(IDS_ALARM_MODE_SET));
	SetDlgItemText(IDC_STATIC_CLEARALARM_TIME,GetText(IDS_PE_CLEARALARM_TIME));
	SetDlgItemText(IDC_BUTTON_SAVE,GetText(IDS_PE_SAVE));
}

void CLS_PEDevSwitchEdit::InitParentInfo(void* _pInfo)
{
	if (_pInfo == NULL)
	{
		return;
	}

	m_clsPowerEnPage = (CLS_DonghuanSet*)_pInfo;
}

void CLS_PEDevSwitchEdit::InitParamInfo(int _iSwitchNo, int _iLogonID)
{
	m_iSwitchNo = _iSwitchNo;
	m_iLogonID = _iLogonID;
}

void CLS_PEDevSwitchEdit::InitDlgItemInfo()
{
	//编号
	int iIndex = -1;
	CString cstrSwitchNo = "";
	cstrSwitchNo.Format("%d",m_iSwitchNo);
	iIndex = m_cboIndex.AddString(cstrSwitchNo);
	m_cboIndex.SetCurSel(iIndex);

	if (NetClient_GetAlarmConfig)
	{
		AlarmInConfig srcAlarmInConfig = {-1};
		srcAlarmInConfig.iSize = sizeof(AlarmInConfig);
		srcAlarmInConfig.iInterfaceNo = m_iSwitchNo;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iSwitchNo - 1,-1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","InitDlgItemInfo-TDGetAlarmConfig(loginID %d,m_iSwitchNo %d)",m_iLogonID, m_iSwitchNo);
			return;
		}

		//名称
		string strName = srcAlarmInConfig.cName;
		m_edtName.SetWindowText(strName.c_str());

		//布防模板
		AlarmInSchedule srcAlarmInSchedule = {-1};
		srcAlarmInSchedule.iSize = sizeof(AlarmInSchedule);
		srcAlarmInSchedule.iScheduleNo = srcAlarmInConfig.iScheduleNo;
		iRet = NetClient_GetAlarmConfig(m_iLogonID,srcAlarmInConfig.iScheduleNo,-1,CMD_ALARM_IN_SCHEDULE,&srcAlarmInSchedule);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","InitDlgItemInfo-TDGetAlarmConfig(loginID %d,iScheduleNo %d)",m_iLogonID, srcAlarmInConfig.iScheduleNo);
			return;
		}

		string strSchedule = srcAlarmInSchedule.cName;
		iIndex = m_cboAlarmSchedule.FindString(-1,strSchedule.c_str());
		m_cboAlarmSchedule.SetCurSel(iIndex);

		//消警延时
		CString cstrDelayTime = "";
		cstrDelayTime.Format("%d",srcAlarmInConfig.iDelay);
		m_edtDisAlarmDelayTime.SetWindowText(cstrDelayTime);

		string strAlarmInfo = srcAlarmInConfig.cParam;

		//模式设置
		if (StrToInt(strAlarmInfo.c_str()) == 0)
		{
			//闭路报警
			m_cboModeSet.SetCurSel(1);
		}
		else
		{
			//开路报警
			m_cboModeSet.SetCurSel(0);
		}
	}
}

void CLS_PEDevSwitchEdit::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	if (m_clsPowerEnPage == NULL)
	{
		AddLog(LOG_TYPE_FAIL, "","OnBnClickedButtonSave-m_clsPowerEnPage is null");
		return;
	}

	//保存数据
	AlarmInConfig pAlarmInInfo = {-1};
	pAlarmInInfo.iSize = sizeof(AlarmInConfig);

	//编号
	CString cstrNo = "";
	m_cboIndex.GetWindowText(cstrNo);
	pAlarmInInfo.iInterfaceNo = atoi(cstrNo);

	//名称
	CString cstrName = "";
	m_edtName.GetWindowText(cstrName);
	memcpy(pAlarmInInfo.cName,cstrName,MAX_NAME_LEN + 1);
	if (cstrName == _T("") || cstrName.FindOneOf(" ") >= 0)
	{
		MessageBox("名称不允许为空或包含空格！", "", MB_OK|MB_TOPMOST);
		m_edtName.SetFocus();
		return;
	}

	//布防模板
	CString cstrSchedule = "";
	int iScheduleNo = -1;
	iScheduleNo = (int)m_cboAlarmSchedule.GetItemData(m_cboAlarmSchedule.GetCurSel());
	pAlarmInInfo.iScheduleNo = iScheduleNo;
	m_cboAlarmSchedule.GetWindowText(cstrSchedule);

	//消警延时
	CString cstrDelayTime = "";
	m_edtDisAlarmDelayTime.GetWindowText(cstrDelayTime);
	if (cstrDelayTime == _T(""))
	{
		MessageBox("消警延时时间不允许为空！", "", MB_OK|MB_TOPMOST);
		m_edtDisAlarmDelayTime.SetFocus();
		return;
	}
	pAlarmInInfo.iDelay = atoi(cstrDelayTime);

	//模式设置
	int iSelMode = -1;
	CString cstrAlarmInfo = "";
	if (m_cboModeSet.GetCurSel() == 0)
	{
		iSelMode = 1;
	}
	else
	{
		iSelMode = 0;
	}
	cstrAlarmInfo.Format("%d",iSelMode);
	strcpy(pAlarmInInfo.cParam,cstrAlarmInfo);


	if (m_clsPowerEnPage != NULL)
	{
		StrctSwicth strctSwitchInfo;
		strctSwitchInfo.m_iMode = iSelMode;
		m_clsPowerEnPage->StructToString(&strctSwitchInfo, cstrAlarmInfo);
		strcpy(pAlarmInInfo.cParam,cstrAlarmInfo);
	}

	pAlarmInInfo.iInterfaceType = ALARM_INTERFACE_TYPE_SWITCH;

	//保存
	if (NetClient_SetAlarmConfig)
	{
		//使能
		int iEnable = 1;
		int iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iSwitchNo-1, -1,CMD_DH_DEVICE_ENABLE,&iEnable);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","OnBnClickedButtonSave-TDSetAlarmConfig(loginID %d,iInterfaceNo %d,SetInfo %s)",m_iLogonID, pAlarmInInfo.iInterfaceNo,pAlarmInInfo.cParam);
			return;
		}

		//参数设置
		pAlarmInInfo.iSize = sizeof(AlarmInConfig);
		iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iSwitchNo-1, -1,CMD_ALARM_IN_CONFIG,&pAlarmInInfo);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","OnBnClickedButtonSave-TDSetAlarmConfig(loginID %d,iInterfaceNo %d,SetInfo %s)",m_iLogonID, pAlarmInInfo.iInterfaceNo,pAlarmInInfo.cParam);
			return;
		}

		//更新列表
		if (m_clsPowerEnPage != NULL)
		{
			m_clsPowerEnPage->UpdateListInfo(pAlarmInInfo.iInterfaceNo);
		}
	}
	EndDialog(IDCLOSE);
}

void CLS_PEDevSwitchEdit::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}
