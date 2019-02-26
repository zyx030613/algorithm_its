// PEDevSimuEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "PEDevSimuEdit.h"


// CLS_PEDevSimuEdit dialog

IMPLEMENT_DYNAMIC(CLS_PEDevSimuEdit, CDialog)

CLS_PEDevSimuEdit::CLS_PEDevSimuEdit(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_PEDevSimuEdit::IDD, pParent)
{

}

CLS_PEDevSimuEdit::~CLS_PEDevSimuEdit()
{
}

void CLS_PEDevSimuEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_cboSimuNo);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_cboUnit);
	DDX_Control(pDX, IDC_COMBO_SCHDULE, m_cboSimuSchedule);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtName);
	DDX_Control(pDX, IDC_EDIT_CLEARALARM_TIME, m_edtDisAlarmDelayTime);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_edtCollectIntervel);
	DDX_Control(pDX, IDC_EDIT_UPLIMIT, m_edtRangeUpLevel);
	DDX_Control(pDX, IDC_EDIT_UPVALUE, m_edtRangeUpValue);
	DDX_Control(pDX, IDC_EDIT_DOWNVALUE, m_edtRangeDownValue);
	DDX_Control(pDX, IDC_EDIT_DOWMLIMIT, m_edtRangeDownLevel);
	DDX_Control(pDX, IDC_EDIT_ALARMUP_HUM2, m_edtAlarmUpLevel);
	DDX_Control(pDX, IDC_EDIT_ALARMDOWN_HUM2, m_edtAlarmDownLevel);
	DDX_Control(pDX, IDC_EDIT_CLEARUP_HUM2, m_edtDisAlarmUpLevel);
	DDX_Control(pDX, IDC_EDIT_CLEARDOWN_HUM2, m_edtDisAlarmDownLevel);
}


BEGIN_MESSAGE_MAP(CLS_PEDevSimuEdit, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLS_PEDevSimuEdit::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CLS_PEDevSimuEdit message handlers

BOOL CLS_PEDevSimuEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cboUnit.InsertString(0, "V");
	m_cboUnit.InsertString(1, "A");
	m_cboUnit.InsertString(2, "°C");
	m_cboUnit.InsertString(3, "%RH");

	m_edtName.SetLimitText(32);
	m_edtDisAlarmDelayTime.SetLimitText(6);
	m_edtCollectIntervel.SetLimitText(6);
	m_edtRangeUpLevel.SetLimitText(4);
	m_edtRangeUpValue.SetLimitText(4);
	m_edtRangeDownLevel.SetLimitText(4);
	m_edtRangeDownValue.SetLimitText(4);
	m_edtAlarmUpLevel.SetLimitText(4);
	m_edtAlarmDownLevel.SetLimitText(4);
	m_edtDisAlarmUpLevel.SetLimitText(4);
	m_edtDisAlarmDownLevel.SetLimitText(4);

	m_edtDisAlarmDelayTime.SetWindowText("5");

	//编号
	CString strIndex;
	for (int i=16; i<MAX_SIMU_NUM + 16; i++)
	{
		strIndex.Format("%d", i+1);
		m_cboSimuNo.InsertString(i, strIndex);
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
				m_cboSimuSchedule.AddString(strSchedule.c_str());
				m_cboSimuSchedule.SetItemData(m_cboSimuSchedule.GetCount() - 1,srcAlarmInSchedule.iScheduleNo);
			}
		}
	}

	if (m_iDlgStyle == enu_Add)
	{
		m_cboUnit.SetCurSel(0);
		ChangeUnitofText(0);

		m_cboSimuNo.SetCurSel(0);
		m_cboSimuSchedule.SetCurSel(0);
	}
	else
	{
		InitDlgItemInfo();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void  CLS_PEDevSimuEdit::ChangeUnitofText(int _iUnitType, CString _strUnit)
{
	CString strUnit;
	if (_iUnitType < 0)
	{
		strUnit = _strUnit;
	}
	else if (_iUnitType >= m_cboUnit.GetCount())
	{
		return;
	}
	else
	{
		switch(_iUnitType)
		{
		case 0: strUnit = "(V)";
			break;
		case 1: strUnit = "(A)";
			break;
		case 2: strUnit = "(°C)";
			break;
		case 3: strUnit = "(%RH)";
			break;
		default:
			break;
		}
	}

	SetDlgItemText(IDC_STATIC_UPLIMIT,GetText(IDS_PE_UPLIMIT) + strUnit);
	SetDlgItemText(IDC_STATIC_DOWMLIMIT,GetText(IDS_PE_DOWMLIMIT) + strUnit);
	SetDlgItemText(IDC_STAT_UPVALUE,GetText(IDS_PE_DOWNVALUE) + strUnit);
	SetDlgItemText(IDC_STATIC_DOWNVALUE,GetText(IDS_PE_DOWNVALUE) + strUnit);
	SetDlgItemText(IDC_STATIC_ALARMUP_HUM,GetText(IDS_PE_ALARMUP_TEMP) + strUnit);
	SetDlgItemText(IDC_STATIC_ALARMDOWN_HUM,GetText(IDS_PE_ALARMDOWN_TEMP) + strUnit);
	SetDlgItemText(IDC_STATIC_CLEARUP_HUM,GetText(IDS_PE_CLEARUP_TEMP) + strUnit);
	SetDlgItemText(IDC_STATIC_CLEARDOWN_HUM,GetText(IDS_PE_CLEARDOWN_TEMP) + strUnit);
}

void CLS_PEDevSimuEdit::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

void CLS_PEDevSimuEdit::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_PEDevSimuEdit::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case 0:
		break;
	default:
		break;
	}
}

void CLS_PEDevSimuEdit::UI_UpdateDialogText()
{
	SetDlgItemText(IDC_STATIC_SIMU_BASIC_INFO,GetText(IDS_PE_BASIC_INFO));
	SetDlgItemText(IDC_STATIC_INDEX,GetText(IDS_PE_INDEX));
	SetDlgItemText(IDC_STATIC_NAME,GetText(IDS_PE_NAME));
	SetDlgItemText(IDC_STATIC_SCHEDULE,GetText(IDS_PE_SCHEDULE));
	SetDlgItemText(IDC_STATIC_UNIT,GetText(IDS_PE_UNIT));
	SetDlgItemText(IDC_STATIC_CLEARALARM_TIME,GetText(IDS_PE_CLEARALARM_TIME));
	SetDlgItemText(IDC_STATIC_INTERVAL,GetText(IDC_STATIC_PE_INTERVAL_TIME));
	SetDlgItemText(IDC_STATIC_ALARM_LIMIT,GetText(IDS_ALARM_LIMIT_SET));
	SetDlgItemText(IDC_BUTTON_SAVE,GetText(IDS_PE_SAVE));
	SetDlgItemText(IDC_STATIC_UPLIMIT,GetText(IDS_PE_UPLIMIT));
	SetDlgItemText(IDC_STATIC_DOWMLIMIT,GetText(IDS_PE_DOWMLIMIT));
	SetDlgItemText(IDC_STAT_UPVALUE,GetText(IDS_PE_UPDOWNVALUE));
	SetDlgItemText(IDC_STATIC_DOWNVALUE,GetText(IDS_PE_UPDOWNVALUE));
	SetDlgItemText(IDC_STATIC_ALARMUP_HUM,GetText(IDS_PE_ALARMUP_TEMP));
	SetDlgItemText(IDC_STATIC_ALARMDOWN_HUM,GetText(IDS_PE_ALARMDOWN_TEMP));
	SetDlgItemText(IDC_STATIC_CLEARUP_HUM,GetText(IDS_PE_CLEARUP_TEMP));
	SetDlgItemText(IDC_STATIC_CLEARDOWN_HUM,GetText(IDS_PE_CLEARDOWN_TEMP));
}

void CLS_PEDevSimuEdit::InitParentInfo(void* _pInfo)
{
	if (_pInfo == NULL)
	{
		return;
	}

	m_clsPowerEnPage = (CLS_DonghuanSet*)_pInfo;
}

void CLS_PEDevSimuEdit::InitParamInfo(int _iSimuNo, int _iLogonID)
{
	m_iSimuNo = _iSimuNo;
	m_iLogonID = _iLogonID;
}

void CLS_PEDevSimuEdit::InitDlgItemInfo()
{
	//编号
	int iIndex = -1;
	int iValue = -1;
	float fValue = 0.00;
	CString cstrSimuNo = "";
	cstrSimuNo.Format("%d",m_iSimuNo);
	iIndex = m_cboSimuNo.AddString(cstrSimuNo);
	m_cboSimuNo.SetCurSel(iIndex);

	if (NetClient_GetAlarmConfig)
	{
		AlarmInConfig srcAlarmInConfig = {-1};
		srcAlarmInConfig.iSize = sizeof(AlarmInConfig);
		srcAlarmInConfig.iInterfaceNo = m_iSimuNo - 1;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iSimuNo - 1,-1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","InitDlgItemInfo-TDGetAlarmConfig(loginID %d,m_iSimuNo %d)",m_iLogonID, m_iSimuNo);
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
		iIndex = m_cboSimuSchedule.FindString(-1,strSchedule.c_str());
		m_cboSimuSchedule.SetCurSel(iIndex);

		//消警延时
		CString cstrDelayTime = "";
		cstrDelayTime.Format("%d",srcAlarmInConfig.iDelay);
		m_edtDisAlarmDelayTime.SetWindowText(cstrDelayTime);

		//解析结果
		CString cstrTemp = "";
		//if (!AfxExtractSubString(cstrTemp, srcAlarmInConfig.cParam, 0, _T(':')))
		//{
		//	AddLog(LOG_TYPE_FAIL, "","Error extracting unit\r\n");
		//	return;
		//}

		StrctSimu strctSimuInfo;
		m_clsPowerEnPage->StringToStruct(srcAlarmInConfig.cParam, &strctSimuInfo);


		//单位
		cstrTemp = strctSimuInfo.m_cSimuUnit;
		iIndex = m_cboUnit.FindString(-1,cstrTemp);
		if (iIndex == -1)
		{
			m_cboUnit.AddString(cstrTemp);
			m_cboUnit.SetCurSel(m_cboUnit.GetCount() - 1);
		}
		else
		{
			m_cboUnit.SetCurSel(iIndex);
		}


		//采集间隔
		cstrTemp.Format("%d",strctSimuInfo.m_iCollectTime);
		m_edtCollectIntervel.SetWindowText(cstrTemp);

		//量程上限
		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtRangeUpLevel.SetWindowText(cstrTemp);

		//对应值
		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtRangeUpValue.SetWindowText(cstrTemp);

		//量程下限

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtRangeDownLevel.SetWindowText(cstrTemp);

		//对应值

		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtRangeDownValue.SetWindowText(cstrTemp);

		//报警上限
		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtAlarmUpLevel.SetWindowText(cstrTemp);

		//报警下限
		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtAlarmDownLevel.SetWindowText(cstrTemp);

		//消警上限
		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtDisAlarmUpLevel.SetWindowText(cstrTemp);

		//消警下限
		fValue = (float)(atof(cstrTemp) - 10000) / 100;
		cstrTemp.Format("%0.2f",fValue);
		m_edtDisAlarmDownLevel.SetWindowText(cstrTemp);
	}
}

void CLS_PEDevSimuEdit::OnBnClickedButtonSave()
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
	int iValue = -1;

	//编号
	CString cstrNo = "";
	m_cboSimuNo.GetWindowText(cstrNo);
	pAlarmInInfo.iInterfaceNo = atoi(cstrNo);

	//名称
	CString cstrName = "";
	m_edtName.GetWindowText(cstrName);
	memcpy(pAlarmInInfo.cName,cstrName,MAX_NAME_LEN + 1);
	if (cstrName == _T("") || cstrName.FindOneOf(" ") >= 0)
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE1), "", MB_OK|MB_TOPMOST);
		m_edtName.SetFocus();
		return;
	}

	//布防模板
	CString cstrSchedule = "";
	int iScheduleNo = -1;
	iScheduleNo = (int)m_cboSimuSchedule.GetItemData(m_cboSimuSchedule.GetCurSel());
	pAlarmInInfo.iScheduleNo = iScheduleNo;
	m_cboSimuSchedule.GetWindowText(cstrSchedule);

	//单位
	CString cstrUnit = "";
	m_cboUnit.GetWindowText(cstrUnit);

	//消警延时
	CString cstrDelayTime = "";
	m_edtDisAlarmDelayTime.GetWindowText(cstrDelayTime);
	if (cstrDelayTime == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE3), "", MB_OK|MB_TOPMOST);
		m_edtDisAlarmDelayTime.SetFocus();
		return;
	}
	pAlarmInInfo.iDelay = atoi(cstrDelayTime);

	//采集间隔
	CString	cstrCollectTime = "";
	m_edtCollectIntervel.GetWindowText(cstrCollectTime);
	if (cstrDelayTime == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_MESSAGE12), "", MB_OK|MB_TOPMOST);
		m_edtCollectIntervel.SetFocus();
		return;
	}

	//量程上限
	CString cstrRangeUpLevel = "";
	m_edtRangeUpLevel.GetWindowText(cstrRangeUpLevel);
	if (cstrRangeUpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE1), "", MB_OK|MB_TOPMOST);
		m_edtRangeUpLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrRangeUpLevel) * 100) + 10000;
	cstrRangeUpLevel.Format("%d",iValue);

	//量程上限测量值
	CString cstrRangeUpValue = "";
	m_edtRangeUpValue.GetWindowText(cstrRangeUpValue);
	if (cstrRangeUpValue == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE2), "", MB_OK|MB_TOPMOST);
		m_edtRangeUpValue.SetFocus();
		return;
	}
	iValue = (atoi(cstrRangeUpValue) * 100) + 10000;
	cstrRangeUpValue.Format("%d",iValue);

	//量程下限
	CString cstrRangeDownLevel = "";
	m_edtRangeDownLevel.GetWindowText(cstrRangeDownLevel);
	if (cstrRangeDownLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE3), "", MB_OK|MB_TOPMOST);
		m_edtRangeDownLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrRangeDownLevel) * 100) + 10000;
	cstrRangeDownLevel.Format("%d",iValue);

	//量程下限测量值
	CString cstrRangeDownValue = "";
	m_edtRangeDownValue.GetWindowText(cstrRangeDownValue);
	if (cstrRangeDownValue == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE4), "", MB_OK|MB_TOPMOST);
		m_edtRangeDownValue.SetFocus();
		return;
	}
	iValue = (atoi(cstrRangeDownValue) * 100) + 10000;
	cstrRangeDownValue.Format("%d",iValue);


	//报警上限
	CString cstrAlarmUpLevel = "";
	m_edtAlarmUpLevel.GetWindowText(cstrAlarmUpLevel);
	if (cstrAlarmUpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE5), "", MB_OK|MB_TOPMOST);
		m_edtAlarmUpLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrAlarmUpLevel) * 100) + 10000;
	cstrAlarmUpLevel.Format("%d",iValue);

	//报警下限
	CString cstrAlarmDownLevel = "";
	m_edtAlarmDownLevel.GetWindowText(cstrAlarmDownLevel);
	if (cstrAlarmDownLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE6), "", MB_OK|MB_TOPMOST);
		m_edtAlarmDownLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrAlarmDownLevel) * 100) + 10000;
	cstrAlarmDownLevel.Format("%d",iValue);

	//消警上限
	CString cstrDisAlarmUpLevel = "";
	m_edtDisAlarmUpLevel.GetWindowText(cstrDisAlarmUpLevel);
	if (cstrDisAlarmUpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE7), "", MB_OK|MB_TOPMOST);
		m_edtDisAlarmUpLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrDisAlarmUpLevel) * 100) + 10000;
	cstrDisAlarmUpLevel.Format("%d",iValue);

	//消警下限
	CString cstrDisAlarmDownpLevel = "";
	m_edtDisAlarmDownLevel.GetWindowText(cstrDisAlarmDownpLevel);
	if (cstrDisAlarmDownpLevel == _T(""))
	{
		MessageBox(GetText(IDS_POWER_DEV_SIMUU_MESSAGE8), "", MB_OK|MB_TOPMOST);
		m_edtDisAlarmDownLevel.SetFocus();
		return;
	}
	iValue = (atoi(cstrDisAlarmDownpLevel) * 100) + 10000;
	cstrDisAlarmDownpLevel.Format("%d",iValue);

	CString cstrAlarmInfo = "";
	CString cstrStep = "";
	cstrAlarmInfo.Format("unit=%s,interval=%s,disuplimit=%s,disupvalue=%s,dislowlimit=%s,dislowvalue=%s,alarmup=%s,alarmlow=%s,elimup=%s,elimlow=%s",
		cstrUnit, cstrCollectTime,cstrRangeUpLevel,cstrRangeUpValue,cstrRangeDownLevel,
		cstrRangeDownValue,cstrAlarmUpLevel,cstrAlarmDownLevel,cstrDisAlarmUpLevel,cstrDisAlarmDownpLevel);
	strcpy(pAlarmInInfo.cParam,cstrAlarmInfo);

	pAlarmInInfo.iInterfaceType = ALARM_INTERFACE_TYPE_ANALOG;
	//保存
	if (NetClient_SetAlarmConfig)
	{
		int iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iSimuNo - 1, -1, CMD_ALARM_IN_CONFIG, &pAlarmInInfo);
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
	EndDialog(IDOK);
}

void CLS_PEDevSimuEdit::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}
