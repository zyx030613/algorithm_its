// PEDevComEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "PEDevComEdit.h"
#include <algorithm>


// CLS_PEDevComEdit dialog

IMPLEMENT_DYNAMIC(CLS_PEDevComEdit, CDialog)

CLS_PEDevComEdit::CLS_PEDevComEdit(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_PEDevComEdit::IDD, pParent)
{
	m_iDlgStyle = 0;
	m_clsPowerEnPage = NULL;
	m_iLogonID = -1;
}

CLS_PEDevComEdit::~CLS_PEDevComEdit()
{
	m_iDlgStyle = 0;
	m_clsPowerEnPage = NULL;
	m_iLogonID = -1;
}

void CLS_PEDevComEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_cboDevNo);
	DDX_Control(pDX, IIDC_EDIT_NAME, m_edtDevName);
	DDX_Control(pDX, IDC_COMBO_DEVTYPE, m_cboDevType);
	DDX_Control(pDX, IDC_COMBO_SCHDULE, m_cboDevSchedule);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtDevName);
	DDX_Control(pDX, IDC_EDIT_DEVADDRESS, m_edtDevAddr);
	DDX_Control(pDX, IDC_EDIT_CLEARALARM_TIME, m_edtDisAlarmIntervelTime);
	DDX_Control(pDX, IDC_EDIT_ALARMUP_TEMP, m_edtTemAlarmUpLevel);
	DDX_Control(pDX, IDC_EDIT_ALARMDOWN_TEMP, m_edtTemAlarmDownLevel);
	DDX_Control(pDX, IDC_EDIT_CLEARUP_TEMP, m_edtTemDisAlarmUpLevel);
	DDX_Control(pDX, IDC_EDIT_CLEARDOWN_TEMP, m_edtTemDisAlarmDownLevel);
	DDX_Control(pDX, IDC_EDIT_ALARMUP_HUM, m_edtHulAlarmUpLevel);
	DDX_Control(pDX, IDC_EDIT_ALARMDOWN_HUM, m_edtHulAlarmDownLevel);
	DDX_Control(pDX, IDC_EDIT_CLEARUP_HUM, m_edtHulDisAlarmUpLevel);
	DDX_Control(pDX, IDC_EDIT_CLEARDOWN_HUM, m_edtHulDisAlarmDownLevel);
}


BEGIN_MESSAGE_MAP(CLS_PEDevComEdit, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLS_PEDevComEdit::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLS_PEDevComEdit message handlers

BOOL CLS_PEDevComEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	UI_UpdateDialogText();
	m_edtDevName.SetLimitText(32);
	m_edtDevAddr.SetLimitText(3);
	m_edtDisAlarmIntervelTime.SetLimitText(6);
	m_edtTemAlarmUpLevel.SetLimitText(5);
	m_edtTemAlarmDownLevel.SetLimitText(5);
	m_edtTemDisAlarmUpLevel.SetLimitText(5);
	m_edtTemDisAlarmDownLevel.SetLimitText(5);
	m_edtHulAlarmUpLevel.SetLimitText(5);
	m_edtHulAlarmDownLevel.SetLimitText(5);
	m_edtHulDisAlarmUpLevel.SetLimitText(5);
	m_edtHulDisAlarmDownLevel.SetLimitText(5);
	m_edtTemAlarmUpLevel.SetWindowText("0.00");
	m_edtTemAlarmDownLevel.SetWindowText("0.00");
	m_edtTemDisAlarmUpLevel.SetWindowText("0.00");
	m_edtTemDisAlarmDownLevel.SetWindowText("0.00");
	m_edtHulAlarmUpLevel.SetWindowText("0.00");
	m_edtHulAlarmDownLevel.SetWindowText("0.00");
	m_edtHulDisAlarmUpLevel.SetWindowText("0.00");
	m_edtHulDisAlarmDownLevel.SetWindowText("0.00");

	m_edtDevAddr.SetWindowText("1");
	m_edtDisAlarmIntervelTime.SetWindowText("5");

	InitComInfo();
	if (m_iDlgStyle == enu_Add)
	{
		m_cboDevNo.SetCurSel(0);
		m_cboDevType.SetCurSel(0);
		m_cboDevSchedule.SetCurSel(0);
	}
	else
	{
		InitDlgItemInfo();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_PEDevComEdit::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

void CLS_PEDevComEdit::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_PEDevComEdit::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case 0:
		break;
	default:
		break;
	}
}

void CLS_PEDevComEdit::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_COM_BASIC_INFO, IDS_PE_BASIC_INFO);
	SetDlgItemTextEx(IDC_STATIC_INDEX, IDS_PE_INDEX);
	SetDlgItemTextEx(IDC_STATIC_NAME, IDS_PE_NAME);
	SetDlgItemTextEx(IDC_STATIC_DEVTYPE, IDS_PE_DEVTYPE);
	SetDlgItemTextEx(IDC_STATIC_DEV_ADDRESS, IDS_PE_DEV_ADDRESS);
	SetDlgItemTextEx(IDC_STATIC_SCHEDULE, IDS_PE_SCHEDULE);
	SetDlgItemTextEx(IDC_STATIC_CLEARALARM_TIME, IDS_PE_CLEARALARM_TIME);
	SetDlgItemTextEx(IDC_STATIC_TEMPERATURE, IDS_PE_TEMP_LIMIT);

	SetDlgItemText(IDC_STATIC_ALARMUP_TEMP,GetTextEx(IDS_PE_ALARMUP_TEMP)+"(°C)");
	SetDlgItemText(IDC_STATIC_ALARMDOWN_TEMP,GetTextEx(IDS_PE_ALARMDOWN_TEMP)+"(°C)");
	SetDlgItemText(IDC_STATIC_CLEARUP_TEMP,GetTextEx(IDS_PE_CLEARUP_TEMP)+"(°C)");
	SetDlgItemText(IDC_STATIC_CLEARDOWN_TEMP,GetTextEx(IDS_PE_CLEARDOWN_TEMP)+"(°C)");
	SetDlgItemText(IDC_STATIC_HUM_VALUE,GetTextEx(IDS_PE_HUM_LIMIT));
	SetDlgItemText(IDC_STATIC_ALARMUP_HUM,GetTextEx(IDS_PE_ALARMUP_TEMP)+"(°C)");
	SetDlgItemText(IDC_STATIC_ALARMDOWN_HUM,GetTextEx(IDS_PE_ALARMDOWN_TEMP)+"(°C)");
	SetDlgItemText(IDC_STATIC_CLEARUP_HUM,GetTextEx(IDS_PE_CLEARUP_TEMP)+"(°C)");
	SetDlgItemText(IDC_STATIC_CLEARDOWN_HUM,GetTextEx(IDS_PE_CLEARDOWN_TEMP)+"(°C)");
	SetDlgItemText(IDC_BUTTON_SAVE,GetTextEx(IDS_PE_SAVE));
}

void CLS_PEDevComEdit::InitDlgStyle(int _iDlgStyle)
{
	m_iDlgStyle = _iDlgStyle;
}

void CLS_PEDevComEdit::InitComNoInfo()
{
	m_cboDevNo.EnableWindow(TRUE);

	if (m_clsPowerEnPage != NULL)
	{
		for (int i=COM_START_NUM; i< PROTOCOL_COUNT+COM_START_NUM; i++)
		{
			vector<int>::iterator iterInfo = find(m_clsPowerEnPage->m_vecExtDevNo.begin(),m_clsPowerEnPage->m_vecExtDevNo.end(),i);
			if (iterInfo != m_clsPowerEnPage->m_vecExtDevNo.end())
			{
				continue;
			}

			CString cstrNo = "";
			cstrNo.Format("%d",i + 1);
			m_cboDevNo.AddString(cstrNo);
		}
	}	
}

void CLS_PEDevComEdit::InitComInfo()
{
	//编号
	InitComNoInfo();

	//设备类型
	int iIndex = -1;
	CString cstrComName = "";
	CString cstrComTypeName = "";
	for (int i=1; i<COM_NUM+1; i++)
	{
		//类型名称前半部分
		string strFirstName = "";
		if (m_clsPowerEnPage != NULL)
		{
			m_clsPowerEnPage->GetComTypeFirstName(i, strFirstName);
		}
		if (strFirstName == "")
		{
			strFirstName = "COM";
		}

		//串口信息
		ComDevice srcComInfo = {-1};
		srcComInfo.iSize = sizeof(ComDevice);
		srcComInfo.iComNo = i;
		int iByteReturn = 0;
		int iRet = NetClient_GetDevConfig(m_iLogonID,NET_CLIENT_COM_DEVICE,-1,&srcComInfo,sizeof(ComDevice),&iByteReturn);
		if (iRet < 0)
		{
			cstrComName.Format("%s %d",strFirstName.c_str(), i);
			iIndex = m_cboDevType.AddString(cstrComName);		
			m_cboDevType.SetItemData(iIndex, n_ComDev_Tem);
			AddLog(LOG_TYPE_FAIL, "", "GetComInfo-TDGetAlarmConfig(loginID %d,DeviceType %d)",m_iLogonID, srcComInfo.iDeviceType);
			continue;
		}
		cstrComName.Format("%s %d",strFirstName.c_str(), i);

		switch(srcComInfo.iDeviceType)
		{
		case 0:
			break;
		case 1:
			cstrComTypeName.LoadString(IDS_POWER_DEV_HUMITURE);
			break;
		case 2:
			break;
		default:
			break;
		}
		if (cstrComTypeName != "")
		{
			cstrComName = cstrComName + "-" + cstrComTypeName;
		}

		iIndex = m_cboDevType.AddString(cstrComName);		
		m_cboDevType.SetItemData(iIndex,srcComInfo.iDeviceType);
	}

	//布防模板
	if (NetClient_GetAlarmConfig)
	{
		for (int i=0; i<SCHEDULE_NUM; i++)
		{
			AlarmInSchedule srcAlarmInSchedule = {-1};
			srcAlarmInSchedule.iSize = sizeof(AlarmInSchedule);
			srcAlarmInSchedule.iScheduleNo = i;
			int iRet = NetClient_GetAlarmConfig(m_iLogonID,i,-1,CMD_ALARM_IN_SCHEDULE,&srcAlarmInSchedule);
			if (iRet < 0)
			{
				continue;
			}

			if (srcAlarmInSchedule.iEnable == 1)
			{
				string strSchedule = srcAlarmInSchedule.cName;
				m_cboDevSchedule.AddString(strSchedule.c_str());
				m_cboDevSchedule.SetItemData(m_cboDevSchedule.GetCount() - 1,srcAlarmInSchedule.iScheduleNo);
			}
		}
	}
}

void CLS_PEDevComEdit::InitParentInfo(void* _pInfo)
{
	if (_pInfo == NULL)
	{
		return;
	}

	m_clsPowerEnPage = (CLS_DonghuanSet*)_pInfo;
}

void CLS_PEDevComEdit::InitParamInfo(int _iComNo, int _iLogonID)
{
	m_iComNo = _iComNo;
	m_iLogonID = _iLogonID;
}

void CLS_PEDevComEdit::InitDlgItemInfo()
{
	m_cboDevNo.EnableWindow(FALSE);

	//编号
	CString cstrComNo = "";
	int iIndex = -1;
	int iValue = -1;
	float fValue = 0.00;
	cstrComNo.Format("%d",m_iComNo);

	iIndex = m_cboDevNo.AddString(cstrComNo);
	m_cboDevNo.SetCurSel(iIndex);

	if (NetClient_GetAlarmConfig)
	{
		AlarmInConfig srcAlarmInConfig = {-1};
		srcAlarmInConfig.iSize = sizeof(AlarmInConfig);
		srcAlarmInConfig.iInterfaceNo = m_iComNo;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iComNo-1, -1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","InitDlgItemInfo-TDGetAlarmConfig(loginID %d,_iComNo %d)",m_iLogonID, m_iComNo);
			return;
		}

		
		StrctCom strctSimuInfo;
		m_clsPowerEnPage->StringToStruct(srcAlarmInConfig.cParam, &strctSimuInfo);

		//名称
		string strName = srcAlarmInConfig.cName;
		m_edtDevName.SetWindowText(srcAlarmInConfig.cName);

		//设备类型
		m_cboDevType.SetCurSel(srcAlarmInConfig.iInterfaceNo);
// 		string strComTypeName = "";
// 		if (m_clsPowerEnPage != NULL)
// 		{
// 			m_clsPowerEnPage->GetComInfo(m_iComNo,strComTypeName);
// 		}
// 		iIndex = m_cboDevType.FindString(-1,strComTypeName.c_str());
// 		m_cboDevType.SetCurSel(iIndex);

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
		iIndex = m_cboDevSchedule.FindString(-1,strSchedule.c_str());
		m_cboDevSchedule.SetCurSel(iIndex);

		//消警延时
		CString cstrDelayTime = "";
		cstrDelayTime.Format("%d",srcAlarmInConfig.iDelay);
		m_edtDisAlarmIntervelTime.SetWindowText(cstrDelayTime);

		//解析地址、报警消警上下限等
		//设备地址
		CString cstrTemp = "";
		cstrTemp.Format("%d",strctSimuInfo.m_iAddr);
		m_edtDevAddr.SetWindowText(cstrTemp);

		//温度报警上限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtTemAlarmUpLevel.SetWindowText(cstrTemp);

		//温度报警下限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtTemAlarmDownLevel.SetWindowText(cstrTemp);

		//温度消警上限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtTemDisAlarmUpLevel.SetWindowText(cstrTemp);

		//温度消警下限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtTemDisAlarmDownLevel.SetWindowText(cstrTemp);

		//湿度报警上限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtHulAlarmUpLevel.SetWindowText(cstrTemp);

		//湿度报警下限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtHulAlarmDownLevel.SetWindowText(cstrTemp);

		//湿度消警上限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtHulDisAlarmUpLevel.SetWindowText(cstrTemp);

		//湿度消警下限
		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtHulDisAlarmDownLevel.SetWindowText(cstrTemp);
	}
}

void CLS_PEDevComEdit::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	if (m_clsPowerEnPage == NULL)
	{
		return;
	}

	//保存串口数据
	AlarmInConfig pAlarmInInfo = {-1};
	pAlarmInInfo.iSize = sizeof(AlarmInConfig);
	int iValue = -1;

	//编号
	CString cstrNo = "";
	m_cboDevNo.GetWindowText(cstrNo);
	m_iComNo = atoi(cstrNo) - 1;

	//名称
	CString cstrName = "";
	m_edtDevName.GetWindowText(cstrName);
	memcpy(pAlarmInInfo.cName,cstrName,MAX_NAME_LEN + 1);
	if (cstrName == _T("") || cstrName.FindOneOf(" ") >= 0)
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE1),"",MB_OK|MB_TOPMOST);
		m_edtDevName.SetFocus();
		return;
	}

	//设备类型
	CString cstrDevType = "";
	m_cboDevType.GetWindowText(cstrDevType);
	pAlarmInInfo.iInterfaceType = ALARM_INTERFACE_TYPE_COM;
	pAlarmInInfo.iInterfaceNo = m_cboDevType.GetCurSel();
	cstrDevType.ReleaseBuffer();
	//设备地址
	CString cstrDevAddr = "";
	m_edtDevAddr.GetWindowText(cstrDevAddr);
	if (cstrDevAddr == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE2),"",MB_OK|MB_TOPMOST);
		m_edtDevAddr.SetFocus();
		return;
	}

	//布防模板
	int iScheduleNo = -1;
	iScheduleNo = (int)m_cboDevSchedule.GetItemData(m_cboDevSchedule.GetCurSel());
	pAlarmInInfo.iScheduleNo = iScheduleNo;

	//消警延时
	CString cstrDelayTime = "";
	m_edtDisAlarmIntervelTime.GetWindowText(cstrDelayTime);
	pAlarmInInfo.iDelay = atoi(cstrDelayTime);
	if (cstrDelayTime == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE3),"",MB_OK|MB_TOPMOST);
		m_edtDisAlarmIntervelTime.SetFocus();
		return;
	}

	pAlarmInInfo.iInterfaceType = ALARM_INTERFACE_TYPE_COM;

	//温度报警上限
	CString cstrAlarmUpLevel = "";
	m_edtTemAlarmUpLevel.GetWindowText(cstrAlarmUpLevel);
	if (cstrAlarmUpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE4),"",MB_OK|MB_TOPMOST);
		m_edtTemAlarmUpLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrAlarmUpLevel) * 100) + 10000;
	cstrAlarmUpLevel.Format("%d",iValue);

	//温度报警下限
	CString cstrAlarmDownLevel = "";
	m_edtTemAlarmDownLevel.GetWindowText(cstrAlarmDownLevel);
	if (cstrAlarmDownLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE5),"",MB_OK|MB_TOPMOST);
		m_edtTemAlarmDownLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrAlarmDownLevel) * 100) + 10000;
	cstrAlarmDownLevel.Format("%d",iValue);

	//温度消警上限
	CString cstrDisAlarmUpLevel = "";
	m_edtTemDisAlarmUpLevel.GetWindowText(cstrDisAlarmUpLevel);
	if (cstrDisAlarmUpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE6),"",MB_OK|MB_TOPMOST);
		m_edtTemDisAlarmUpLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrDisAlarmUpLevel) * 100) + 10000;
	cstrDisAlarmUpLevel.Format("%d",iValue);

	//温度消警下限
	CString cstrDisAlarmDownLevel = "";
	m_edtTemDisAlarmDownLevel.GetWindowText(cstrDisAlarmDownLevel);
	if (cstrDisAlarmDownLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE7),"",MB_OK|MB_TOPMOST);
		m_edtTemDisAlarmDownLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrDisAlarmDownLevel) * 100) + 10000;
	cstrDisAlarmDownLevel.Format("%d",iValue);

	//湿度报警上限
	CString cstrHulAlarmUpLevel = "";
	m_edtHulAlarmUpLevel.GetWindowText(cstrHulAlarmUpLevel);
	if (cstrHulAlarmUpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE8),"",MB_OK|MB_TOPMOST);
		m_edtHulAlarmUpLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrHulAlarmUpLevel) * 100) + 10000;
	cstrHulAlarmUpLevel.Format("%d",iValue);

	//湿度报警下限
	CString cstrHulAlarmDownLevel = "";
	m_edtHulAlarmDownLevel.GetWindowText(cstrHulAlarmDownLevel);
	if (cstrHulAlarmDownLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE9),"",MB_OK|MB_TOPMOST);
		m_edtHulAlarmDownLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrHulAlarmDownLevel) * 100) + 10000;
	cstrHulAlarmDownLevel.Format("%d",iValue);

	//湿度消警上限
	CString cstrHulDisAlarmUpLevel = "";
	m_edtHulDisAlarmUpLevel.GetWindowText(cstrHulDisAlarmUpLevel);
	if (cstrHulDisAlarmUpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE10),"",MB_OK|MB_TOPMOST);
		m_edtHulDisAlarmUpLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrHulDisAlarmUpLevel) * 100) + 10000;
	cstrHulDisAlarmUpLevel.Format("%d",iValue);

	//湿度消警下限
	CString cstrHulDisAlarmDownpLevel = "";
	m_edtHulDisAlarmDownLevel.GetWindowText(cstrHulDisAlarmDownpLevel);
	if (cstrHulDisAlarmDownpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE11),"",MB_OK|MB_TOPMOST);
		m_edtHulDisAlarmDownLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrHulDisAlarmDownpLevel) * 100) + 10000;
	cstrHulDisAlarmDownpLevel.Format("%d",iValue);

	CString cstrAlarmInfo = "";
	CString cstrStep = "";
	cstrAlarmInfo.Format("addr=%s,temalarmup=%s,temalarmlow=%s,temelimup=%s,temelimlow=%s,humalarmup=%s,humalarmlow=%s,humelimup=%s,humelimlow=%s"
		,cstrDevAddr,cstrAlarmUpLevel,cstrAlarmDownLevel,cstrDisAlarmUpLevel,cstrDisAlarmDownLevel
		,cstrHulAlarmUpLevel,cstrHulAlarmDownLevel,cstrHulDisAlarmUpLevel,cstrHulDisAlarmDownpLevel);
	strcpy(pAlarmInInfo.cParam,cstrAlarmInfo);

	pAlarmInInfo.iInterfaceType = ALARM_INTERFACE_TYPE_COM;

	//保存
	if (NetClient_SetAlarmConfig)
	{
		//使能
		int iEnable = 1;
		int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iComNo, -1, CMD_DH_DEVICE_ENABLE, &iEnable);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","OnBnClickedButtonSave-TDSetAlarmConfig[CMD_DH_DEVICE_ENABLE]");
			return;
		}

		iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iComNo,-1,CMD_ALARM_IN_CONFIG,&pAlarmInInfo);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","OnBnClickedButtonSave-TDSetAlarmConfig(loginID %d,iInterfaceNo %d,SetInfo %s)",m_iLogonID, pAlarmInInfo.iInterfaceNo,pAlarmInInfo.cParam);
			return;
		}

		//更新列表
		if (m_clsPowerEnPage != NULL)
		{
			m_clsPowerEnPage->UpdateListInfo(pAlarmInInfo.iInterfaceNo);
			vector<int>::iterator iterInfo = find(m_clsPowerEnPage->m_vecExtDevNo.begin(),m_clsPowerEnPage->m_vecExtDevNo.end(),m_iComNo);
			if (iterInfo != m_clsPowerEnPage->m_vecExtDevNo.end())
			{
				m_clsPowerEnPage->m_vecExtDevNo.erase(iterInfo);
			}
		}
	}
	EndDialog(IDOK);
}

void CLS_PEDevComEdit::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CLS_PEDevComEdit::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}
