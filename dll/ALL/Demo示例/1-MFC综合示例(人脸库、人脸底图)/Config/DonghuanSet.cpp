// DonghuanSet.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DonghuanSet.h"
#include <algorithm>
#include "PEDevComEdit.h"
#include "PEDevSimuEdit.h"
#include "PEDevSwitchEdit.h"


// CDonghuanSet dialog

IMPLEMENT_DYNAMIC(CLS_DonghuanSet, CDialog)

CLS_DonghuanSet::CLS_DonghuanSet(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DonghuanSet::IDD, pParent)
{

}

CLS_DonghuanSet::~CLS_DonghuanSet()
{
}

void CLS_DonghuanSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DONGHUAN_LIST, m_lstPowerDevInfo);
	DDX_Control(pDX, IDC_EDIT_INTERVAL_TIME, m_edtIntervelTime);
	DDX_Control(pDX, IDC_EDT_ALARM_RECEIVE_IP, m_edtIP);
	DDX_Control(pDX, IDC_EDT_ALARM_RECEIVE_PORT, m_edtPort);
}

BEGIN_MESSAGE_MAP(CLS_DonghuanSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DONGHUAN_ADD, &CLS_DonghuanSet::OnBnClickedButtonDonghuanAdd)
	ON_BN_CLICKED(IDC_BUTTON_INTERVAL_TIME_SET, &CLS_DonghuanSet::OnBnClickedButtonIntervalTimeSet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DONGHUAN_LIST, &CLS_DonghuanSet::OnNMClickListDonghuanList)
	ON_BN_CLICKED(IDC_BTN_ALARM_RECEIVE_SAVE, &CLS_DonghuanSet::OnBnClickedBtnAlarmReceiveSave)
END_MESSAGE_MAP()


// CDonghuanSet message handlers

BOOL CLS_DonghuanSet::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	//初始化列表信息
	m_lstPowerDevInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
 	m_lstPowerDevInfo.InsertColumn(0, GetTextEx(IDS_POWER_DEV_LST_NO), 0, 60);
 	m_lstPowerDevInfo.InsertColumn(1, GetTextEx(IDS_POWER_DEV_LST_NAME), 0, 100);
 	m_lstPowerDevInfo.InsertColumn(2, GetTextEx(IDS_POWER_DEV_LST_INTERFACE), 0, 100);
 	m_lstPowerDevInfo.InsertColumn(3, GetTextEx(IDS_POWER_DEV_LST_TYPE), 0, 100);
 	m_lstPowerDevInfo.InsertColumn(4, GetTextEx(IDS_POWER_DEV_LST_ALARMTEM), 0, 100);
 	m_lstPowerDevInfo.InsertColumn(5, GetTextEx(IDS_POWER_DEV_LST_OPER), 0, 100);
	m_lstPowerDevInfo.InsertColumn(6, TEXT(""), 0, 50);
	
	m_edtIP.LimitText(LEN_32-1);
	m_edtPort.LimitText(LEN_8);
	m_edtPort.EnableWindow(FALSE);

	UI_UpdateSDKInfo();
	UI_UpdateDialogText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DonghuanSet::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
	UI_UpdateSDKInfo();

}

void CLS_DonghuanSet::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_DonghuanSet::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case 0:
		UI_UpdateSDKInfo();
		break;
	default:
		break;
	}
}

void CLS_DonghuanSet::UI_UpdateDialogText()
{
	m_lstPowerDevInfo.DeleteAllItems();
	int nColumnCount = m_lstPowerDevInfo.GetHeaderCtrl()->GetItemCount();
	for (int i=0; i < nColumnCount; i++)
	{
		m_lstPowerDevInfo.DeleteColumn(0);
	}

	m_lstPowerDevInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lstPowerDevInfo.InsertColumn(0, GetTextEx(IDS_POWER_DEV_LST_NO), 0, 60);
	m_lstPowerDevInfo.InsertColumn(1, GetTextEx(IDS_POWER_DEV_LST_NAME), 0, 100);
	m_lstPowerDevInfo.InsertColumn(2, GetTextEx(IDS_POWER_DEV_LST_INTERFACE), 0, 100);
	m_lstPowerDevInfo.InsertColumn(3, GetTextEx(IDS_POWER_DEV_LST_TYPE), 0, 100);
	m_lstPowerDevInfo.InsertColumn(4, GetTextEx(IDS_POWER_DEV_LST_ALARMTEM), 0, 100);
	m_lstPowerDevInfo.InsertColumn(5, GetTextEx(IDS_POWER_DEV_LST_OPER), 0, 100);
	m_lstPowerDevInfo.InsertColumn(6, TEXT(""), 0, 50);

	SetDlgItemTextEx(IDC_STATIC_PE_INTERVAL, IDS_PE_INTERVAL);//脱机存储间隔
	SetDlgItemTextEx(IDC_BUTTON_INTERVAL_TIME_SET, IDS_ITS_LIGHTSET);//设置
    SetDlgItemTextEx(IDC_STATIC_INTERVAL_TIME, IDS_PE_INTERVAL_TIME);//脱机存储间隔(分钟)
	SetDlgItemTextEx(IDC_STC_ALARM_RECEIVE, IDS_ALARM_RECEIVE_SERVER);//报警接收服务器
	SetDlgItemTextEx(IDC_STC_ALARM_RECEIVE_IP, IDS_CONFIG_LAN_IP);//IP
	SetDlgItemTextEx(IDC_STC_ALARM_RECEIVE_PORT, IDS_CONFIG_IP_REGISTER_REGPORT1);//端口号
	SetDlgItemTextEx(IDC_BTN_ALARM_RECEIVE_SAVE, IDS_LOG_SAVE);//保存
	SetDlgItemTextEx(IDC_BUTTON_DONGHUAN_ADD, IDS_CONFIG_LINK_ADD);
	SetDlgItemTextEx(IDC_STATIC_INTERVAL, IDS_PE_INTERVAL);	
}

void CLS_DonghuanSet::UI_UpdateSDKInfo()
{
	//更新界面数据信息
	if (NetClient_GetAlarmPortNum)
	{
		int iAlarmInPortNum = 0;
		int iAlarmOutPortNum = 0;
		int iRet = NetClient_GetAlarmPortNum(m_iLogonID,&iAlarmInPortNum,&iAlarmOutPortNum);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "UpdateUI-TDGetAlarmPortNum(loginID %d,alarmInNUm %d,alarmOutNum %d)",m_iLogonID, iAlarmInPortNum, iAlarmOutPortNum);
			return;
		}
		m_vecExtDevNo.clear();
		m_lstPowerDevInfo.DeleteAllItems();

		for (int i=0; i<iAlarmInPortNum; i++)
		{
			UpdateListInfo(i);
		}

		//更新脱机存储间隔时间
		UpdateStoreIntervalTime();

		UpdateAlarmReciveServer();
	}
}

void CLS_DonghuanSet::UpdateListInfo(int _iAlarmINo)
{
	if (NetClient_GetAlarmConfig)
	{
		AlarmInConfig pAlarmInfo = {-1};
		pAlarmInfo.iSize = sizeof(AlarmInConfig);
		pAlarmInfo.iInterfaceNo = _iAlarmINo;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,_iAlarmINo,-1,CMD_ALARM_IN_CONFIG,&pAlarmInfo);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","UpdateListInfo-TDGetAlarmConfig(loginID %d,_iAlarmINo %d)",m_iLogonID, _iAlarmINo);
			return;
		}

		//获取设备使能
		int iEnable = -1;
		iRet = NetClient_GetAlarmConfig(m_iLogonID,_iAlarmINo,-1,CMD_DH_DEVICE_ENABLE,&iEnable);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "UpdateListInfo-TDGetAlarmConfig(iEnable %d)",iEnable);
			return;
		}

		int iType = pAlarmInfo.iInterfaceType;

		switch (iType)
		{
		case ALARM_INTERFACE_TYPE_SWITCH:
			{
				//更新模拟量设备列表节点，不存在添加
				UpdateItemInfo(_iAlarmINo, &pAlarmInfo, iEnable);
				break;
			}
		case ALARM_INTERFACE_TYPE_ANALOG:
			{
				//更新串口设备列表信息
				UpdateItemInfo(_iAlarmINo, &pAlarmInfo, iEnable);
				break;
			}
		case ALARM_INTERFACE_TYPE_COM:
			{
				if (iEnable)
				{
					//更新串口设备列表节点，不存在添加
					UpdateItemInfo(_iAlarmINo, &pAlarmInfo, iEnable);

					vector<int>::iterator iterInfo = find(m_vecExtDevNo.begin(),m_vecExtDevNo.end(),_iAlarmINo);
					if (iterInfo == m_vecExtDevNo.end())
					{
						m_vecExtDevNo.push_back(_iAlarmINo);
					}
				}
				else
				{
					//删除串口设备列表节点
					DeleteComItem(_iAlarmINo, &pAlarmInfo);

					vector<int>::iterator iterInfo = find(m_vecExtDevNo.begin(),m_vecExtDevNo.end(),_iAlarmINo);
					if (iterInfo != m_vecExtDevNo.end())
					{
						m_vecExtDevNo.erase(iterInfo);
					}
				}

				break;
			}
		default:
			break;
		}
	}
}

void CLS_DonghuanSet::UpdateItemInfo(int _iChlNo, AlarmInConfig* _pAlarmInfo, int _iEnable)
{
	//更新，没找到就添加
	bool blFind = false;
	CString cstrNo = "";
	string strDevName = "";
	string strSchedule = "";
	string strEnable = "";
	string strComName = "";
	CString cstrOperInfo = "";

	int iSize = m_lstPowerDevInfo.GetItemCount();
	for (int i=0; i<iSize; i++)
	{
		cstrNo = m_lstPowerDevInfo.GetItemText(i,0);
		if (_iChlNo + 1 == atoi(cstrNo))
		{
			//在列表中找到该条目进行更新
			blFind = true;
			CString cstrDevName = _pAlarmInfo->cName;
			if (strcmp(_pAlarmInfo->cName, "") == 0)
			{
				if (_pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_SWITCH)
				{
					cstrDevName.LoadString(IDS_POWER_DEV_SWITCH);
				}
				else if (_pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_ANALOG)
				{
					cstrDevName.LoadString(IDS_POWER_DEV_ANALOG);
				}
			}
			m_lstPowerDevInfo.SetItemText(i,1,cstrDevName);//设备名称
			GetDevUpdateInfo(_pAlarmInfo, _iEnable, strDevName, strSchedule, strEnable);
			m_lstPowerDevInfo.SetItemText(i,2,strDevName.c_str());//接口名称
			if (_pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_SWITCH)
			{
				m_lstPowerDevInfo.SetItemText(iSize,3,"--");		//设备类型
				cstrOperInfo.LoadString(IDS_POWER_DEV_LST_EDIT);	//编辑
			}
			else if( _pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_ANALOG)
			{
				m_lstPowerDevInfo.SetItemText(iSize,3,"--");//设备类型
				if (_iEnable == 1)
				{
					cstrOperInfo.LoadString(IDS_POWER_DEV_LST_FORBID);	//禁用
				}
				else
				{
					cstrOperInfo.LoadString(IDS_POWER_DEV_LST_ENABLE);	//启用
				}
			}
			else
			{
				GetComTypeLastName(_pAlarmInfo->iInterfaceNo,strComName);
				if (strComName != "")
				{
					strComName = strDevName + "-" + strComName;
				}
				else
				{
					strComName = strDevName;
				}
				m_lstPowerDevInfo.SetItemText(i,3,strComName.c_str());//设备类型

				cstrOperInfo.LoadString(IDS_POWER_DEV_LST_DELETE);
			}	
			m_lstPowerDevInfo.SetItemText(i,4,strSchedule.c_str());	//布防模板	
			m_lstPowerDevInfo.SetItemText(i,5,GetText(IDS_POWER_DEV_LST_EDIT));
			m_lstPowerDevInfo.SetItemText(i,6,cstrOperInfo);		//操作	
			break;
		}
	}

	if (!blFind)
	{
		cstrNo.Format("%d",_iChlNo + 1);
		m_lstPowerDevInfo.InsertItem(iSize,cstrNo);//通道
		CString cstrDevName = _pAlarmInfo->cName;
		if (strcmp(_pAlarmInfo->cName, "") == 0)
		{
			if (_pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_SWITCH)
			{
				cstrDevName.LoadString(IDS_POWER_DEV_SWITCH);
			}
			else if (_pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_ANALOG)
			{
				cstrDevName.LoadString(IDS_POWER_DEV_ANALOG);
			}
		}
		m_lstPowerDevInfo.SetItemText(iSize,1,cstrDevName);//设备名称
		GetDevUpdateInfo(_pAlarmInfo, _iEnable, strDevName, strSchedule, strEnable);
		m_lstPowerDevInfo.SetItemText(iSize,2,strDevName.c_str());//接口名称
		if (_pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_SWITCH)
		{
			m_lstPowerDevInfo.SetItemText(iSize,3,"--");		//设备类型
			cstrOperInfo.LoadString(IDS_POWER_DEV_LST_EDIT);	//编辑

		}
		else if( _pAlarmInfo->iInterfaceType == ALARM_INTERFACE_TYPE_ANALOG)
		{
			m_lstPowerDevInfo.SetItemText(iSize,3,"--");//设备类型
			if (_iEnable == 1)
			{
				cstrOperInfo.LoadString(IDS_POWER_DEV_LST_FORBID);	//禁用
			}
			else
			{
				cstrOperInfo.LoadString(IDS_POWER_DEV_LST_ENABLE);	//启用
			}
			
			m_lstPowerDevInfo.SetItemText(iSize,6,cstrOperInfo);		//操作	
		}
		else
		{
			GetComTypeLastName(_pAlarmInfo->iInterfaceNo,strComName);
			if (strComName != "")
			{
				strComName = strDevName + "-" + strComName;
			}
			else
			{
				strComName = strDevName;
			}
			m_lstPowerDevInfo.SetItemText(iSize,3,strComName.c_str());	//设备类型

			cstrOperInfo.LoadString(IDS_POWER_DEV_LST_DELETE);
		}
		m_lstPowerDevInfo.SetItemText(iSize,4,strSchedule.c_str());		//布防模板
		m_lstPowerDevInfo.SetItemText(iSize,5,GetText(IDS_POWER_DEV_LST_EDIT));
	}
}

void CLS_DonghuanSet::DeleteComItem(int _iChlNo, AlarmInConfig* _pAlarmInfo)
{
	CString cstrNo = "";

	int iSize = m_lstPowerDevInfo.GetItemCount();
	for (int i=0; i<iSize; i++)
	{
		cstrNo = m_lstPowerDevInfo.GetItemText(i,0);
		if (_iChlNo + 1 == atoi(cstrNo))
		{
			//在列表中找到该条目进行删除
			m_lstPowerDevInfo.DeleteItem(i);

			//从容器中删除条目编号
			vector<int>::iterator iterInfo = find(m_vecExtDevNo.begin(),m_vecExtDevNo.end(),_iChlNo);
			if (iterInfo != m_vecExtDevNo.end())
			{
				m_vecExtDevNo.erase(iterInfo);
			}
			break;
		}
	}
}

void CLS_DonghuanSet::UpdateStoreIntervalTime()
{
	if (NetClient_GetAlarmConfig)
	{
		tLogInterval srcAlarmInTimeIntervel = {-1};
		srcAlarmInTimeIntervel.iSize = sizeof(tLogInterval);
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,-1,-1,CMD_ALARM_IN_OFFLINE_TIME_INTERVEL,&srcAlarmInTimeIntervel);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","UpdateStoreIntervalTime-TDGetAlarmConfig(loginID %d,Interveltime %d)",m_iLogonID, srcAlarmInTimeIntervel.iDelayTime);
			return;
		}

		CString cstrValue = "";
		cstrValue.Format("%d",srcAlarmInTimeIntervel.iDelayTime);
		m_edtIntervelTime.SetWindowText(cstrValue);
	}
}

void CLS_DonghuanSet::UpdateAlarmReciveServer()
{
	AddAlarmHost srcAddAlarmHost = {0};
	srcAddAlarmHost.iSize = sizeof(AddAlarmHost);
	srcAddAlarmHost.iHostIndex = HOSTINDEX;
	int iRet = NetClient_GetAlarmConfig(m_iLogonID, -1, -1, CMD_DH_ADD_ALARM_HOST, &srcAddAlarmHost);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "","[CLS_DonghuanSet::UpdateAlarmReciveServer] TDGetAlarmConfig failed! logonID(%d)"
			,m_iLogonID);
		return;
	}

	//IP地址
	m_edtIP.SetWindowText(srcAddAlarmHost.cIP);

	//端口
	SetDlgItemInt(IDC_EDT_ALARM_RECEIVE_PORT, srcAddAlarmHost.iPort);
}

void CLS_DonghuanSet::GetDevUpdateInfo(AlarmInConfig* _pAlarmInfo, int _iEnable
				, string& _strDevName, string& _strScheduleName, string& _strEnable)
{
	//设备名称
	CString cstrName = "";
	switch(_pAlarmInfo->iInterfaceType)
	{
	case ALARM_INTERFACE_TYPE_SWITCH:
		cstrName.LoadString(IDS_POWER_DEV_SWITCH);
		break;
	case ALARM_INTERFACE_TYPE_ANALOG:
		cstrName.LoadString(IDS_POWER_DEV_ANALOG);
		break;
	case ALARM_INTERFACE_TYPE_COM:
		cstrName.LoadString(IDS_POWER_DEV_HUMITURE);
		break;
	default:
		break;
	}

	char chTemp[30] = {0};
	strcpy(chTemp, cstrName.GetBuffer());
	if (cstrName != "")
	{
		cstrName.Format("%s%d", chTemp, _pAlarmInfo->iInterfaceNo);
	}

	_strDevName = cstrName.GetBuffer();
	cstrName.ReleaseBuffer();

	//模板名称
	CString cstrSchedule = "--";
	if (NetClient_GetAlarmConfig)
	{
		AlarmInSchedule srcAlarmInSchedule = {-1};
		srcAlarmInSchedule.iSize = sizeof(AlarmInSchedule);
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,_pAlarmInfo->iScheduleNo,-1,CMD_ALARM_IN_SCHEDULE,&srcAlarmInSchedule);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","GetDevUpdateInfo-TDGetAlarmConfig(loginID %d,iScheduleNo %d)",m_iLogonID, _pAlarmInfo->iScheduleNo);
			return;
		}

		cstrSchedule = srcAlarmInSchedule.cName;

		_strScheduleName = cstrSchedule.GetBuffer();
		cstrSchedule.ReleaseBuffer();
	}

	//是否使能
	CString cstrEnable = "";
	if (_iEnable == 0)
	{
		cstrEnable.LoadString(IDS_POWER_DEV_ABLE);
	}
	else
	{
		cstrEnable.LoadString(IDS_POWER_DEV_ENABLE);
	}

	_strEnable = cstrEnable.GetBuffer();
	cstrEnable.ReleaseBuffer();
}

void CLS_DonghuanSet::GetComInfo(int _iComNo, string& _strComName)
{
	CString cstrComName = "";
	CString cstrComTypeName = "";
	ComDevice srcComInfo = {-1};
	srcComInfo.iSize = sizeof(ComDevice);
	srcComInfo.iComNo = _iComNo;
	int iByteReturn = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID,NET_CLIENT_COM_DEVICE,-1,&srcComInfo,sizeof(ComDevice),&iByteReturn);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "","GetComInfo-TDGetAlarmConfig(loginID %d,DeviceType %d)",m_iLogonID, srcComInfo.iDeviceType);
		return;
	}
	cstrComName.Format("%d",_iComNo);

	switch(srcComInfo.iDeviceType)
	{
	case 0:
		cstrComTypeName.LoadString(IDS_POWER_DEV_HUMITURE);
		break;
	case 1:
	case 2:
		break;
	default:
		break;
	}

	cstrComName = cstrComName + cstrComTypeName;
	_strComName = cstrComName.GetBuffer();
	cstrComName.ReleaseBuffer();
}

void CLS_DonghuanSet::OnBnClickedButtonDonghuanAdd()
{
	// TODO: Add your control notification handler code here
	//添加串口
	CLS_PEDevComEdit clsDlgComEdit;
	clsDlgComEdit.InitParentInfo(this);
	clsDlgComEdit.InitParamInfo(-1, m_iLogonID);
	clsDlgComEdit.InitDlgStyle(enu_Add);
	if (clsDlgComEdit.DoModal() == IDOK)
	{
	}
}

void CLS_DonghuanSet::OnBnClickedButtonIntervalTimeSet()
{
	// TODO: Add your control notification handler code here
	//设置脱机存储间隔
	if (NetClient_SetAlarmConfig)
	{
		tLogInterval srcAlarmInTimeIntervel = {-1};
		srcAlarmInTimeIntervel.iSize = sizeof(tLogInterval);
		CString cstrTime = "";
		m_edtIntervelTime.GetWindowText(cstrTime);
		srcAlarmInTimeIntervel.iDelayTime = atoi(cstrTime);
		int iRet = NetClient_SetAlarmConfig(m_iLogonID,-1,-1,CMD_ALARM_IN_OFFLINE_TIME_INTERVEL,&srcAlarmInTimeIntervel);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","OnBnClickedButtonSave-TDSetAlarmConfig(loginID %d,iIntervelTime %d)",m_iLogonID, srcAlarmInTimeIntervel.iDelayTime);
			return;
		}
	}
}

void CLS_DonghuanSet::OnNMClickListDonghuanList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int nItem = pNMListView->iItem;		//行号
	int nSub = 	pNMListView->iSubItem;	//列号
	int iCount = m_lstPowerDevInfo.GetItemCount();
	if(nItem  == -1)	//该行没数据则返回
	{
		return;
	}
	int iTmpNo = atoi(m_lstPowerDevInfo.GetItemText(nItem,0));
	char cDevName[3] = {0};
	//编辑
	if (5 == nSub)
	{
		m_lstPowerDevInfo.GetItemText(nItem,2,(LPTSTR)cDevName,3);//接口名称
		if (strcmp(cDevName,"模") == 0)
		{
			CLS_PEDevSimuEdit myPeDevSimuEdit;
			myPeDevSimuEdit.InitParamInfo(iTmpNo, m_iLogonID);
			myPeDevSimuEdit.InitParentInfo(this);
			if(IDOK == myPeDevSimuEdit.DoModal())
			{
				UI_UpdateSDKInfo();
			}
		}
		else if(strcmp(cDevName,"开") == 0)
		{
			CLS_PEDevSwitchEdit myPEDevSwitchEdit;
			myPEDevSwitchEdit.InitParamInfo(iTmpNo, m_iLogonID);
			myPEDevSwitchEdit.InitParentInfo(this);
			if(IDOK == myPEDevSwitchEdit.DoModal())
			{
				UI_UpdateSDKInfo();
			}
		}
		else
		{
			CLS_PEDevComEdit myPEDevComEdit;
			myPEDevComEdit.InitParamInfo(iTmpNo, m_iLogonID);
			myPEDevComEdit.InitParentInfo(this);
			myPEDevComEdit.InitDlgStyle(enu_Edit);
			if(IDOK == myPEDevComEdit.DoModal())
			{
				UI_UpdateSDKInfo();
			}
		}

	}
	//启用禁用
 	if (6 == nSub)
 	{
		int iRet = -1;

		AlarmInConfig srcAlarmInConfig = {-1};
		srcAlarmInConfig.iSize = sizeof(AlarmInConfig);
		iRet = NetClient_GetAlarmConfig(m_iLogonID,iTmpNo - 1,-1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
		if (iRet < 0)
		{
			return;
		}

		//使能
		int iEnable = -1;
		iRet = NetClient_GetAlarmConfig(m_iLogonID,iTmpNo - 1,-1,CMD_DH_DEVICE_ENABLE,&iEnable);
		if (iRet < 0)
		{
			return;
		}
		if (iEnable == 1)
		{
			iEnable = 0;
		}
		else
		{
			iEnable = 1;
		}

		//设置使能
		iRet = NetClient_SetAlarmConfig(m_iLogonID,iTmpNo - 1,-1,CMD_DH_DEVICE_ENABLE,&iEnable);
		if (iRet < 0)
		{
			return;
		}

		//设备参数
		srcAlarmInConfig.iSize = sizeof(AlarmInConfig);
		iRet = NetClient_SetAlarmConfig(m_iLogonID,iTmpNo - 1,-1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
		if (iRet < 0)
		{
			return;
		}
// 		AlarmInSchedule tmp = {0};
// 		tmp.iSize = sizeof(tmp);
// 		tmp.iScheduleNo = iTmpNo;
// 		tmp.iEnable = 0;
// 		int iRet = NetClient_SetAlarmConfig(m_iLogonID,-1 ,-1, CMD_ALARM_IN_SCHEDULE, &tmp);
// 		if (iRet < 0)
// 		{
// 			AddLog(LOG_TYPE_FAIL,"","[CLS_DefenceTemplatePage::UpdateSchedule] NetClient_GetAlarmConfig failed! logonID(%d),error(%d)"
// 				,m_iLogonID,GetLastError());
// 			return ;
// 		}
// 		UpdateUI();
 	}
	*pResult = 0;
}

void CLS_DonghuanSet::OperateInfo(int _iPos)
{
	if (m_iSelectIndex == -1)
	{
		return;
	}

	int iItemNo = -1;
	int iRet = -1;
	CString cstrNo = "";
	CString cstrEnable = "";
	cstrNo = m_lstPowerDevInfo.GetItemText(m_iSelectIndex,0);
	iItemNo = atoi(cstrNo);

	AlarmInConfig srcAlarmInConfig = {-1};
	srcAlarmInConfig.iSize = sizeof(AlarmInConfig);
	srcAlarmInConfig.iInterfaceNo = iItemNo;

	iRet = NetClient_GetAlarmConfig(m_iLogonID,iItemNo,-1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "","OperateInfo-TDGetAlarmConfig(Get ItemInfo error. loginID %d,iItemNo %d)",m_iLogonID, iItemNo);
	}

	//使能
	int iEnable = -1;
	iRet = NetClient_GetAlarmConfig(m_iLogonID,iItemNo,-1,CMD_DH_DEVICE_ENABLE,&iEnable);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "OperateInfo-TDGetAlarmConfig(Get EnableInfo error. iEnable %d)",iEnable);
	}

	if (iItemNo < 16)//开关量
	{
		if (_iPos == 0)
		{
			//编辑
			CLS_PEDevSwitchEdit clsSwitchEdit;
			clsSwitchEdit.InitParentInfo(this);
			clsSwitchEdit.InitParamInfo(iItemNo, m_iLogonID);
			//clsSwitchEdit.InitDlgStyle(enu_Edit);
			clsSwitchEdit.DoModal();
		}
		else if (_iPos == 1)
		{
			//启用禁用
			goto END;
		}
	}
	else if (iItemNo >= 16 && iItemNo < 32) //模拟量
	{
		if (_iPos == 0)
		{
			//编辑
			CLS_PEDevSimuEdit clsSimuEdit;
			clsSimuEdit.InitParentInfo(this);
			clsSimuEdit.InitParamInfo(iItemNo, m_iLogonID);
			//clsSimuEdit.InitDlgStyle(enu_Edit);
			clsSimuEdit.DoModal();
		}
		else if (_iPos == 1)
		{
			//启用禁用
			goto END;
		}
	}
	else if (iItemNo > 32)//温湿度
	{
		if (_iPos == 0)
		{
			//编辑
			CLS_PEDevComEdit clsComEdit;
			clsComEdit.InitParentInfo(this);
			clsComEdit.InitParamInfo(iItemNo, m_iLogonID);
			clsComEdit.InitDlgStyle(enu_Edit);
			clsComEdit.DoModal();
		}
		else if (_iPos == 1)
		{
			//删除
			iRet = NetClient_SetAlarmConfig(m_iLogonID,iItemNo,-1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
			if (iRet < 0)
			{
				AddLog(LOG_TYPE_FAIL, "","OperateInfo-TDSetAlarmConfig(Delete Item error. loginID %d,iItemNo %d)",m_iLogonID, srcAlarmInConfig.iInterfaceNo);
				return;
			}

			m_lstPowerDevInfo.DeleteItem(m_iSelectIndex);
		}
	}
	return;

END:
	if (iEnable == 1)
	{
		iEnable = 0;
		cstrEnable.LoadString(IDS_POWER_DEV_LST_ENABLE);	//启用
	}
	else
	{
		iEnable = 1;
		cstrEnable.LoadString(IDS_POWER_DEV_LST_FORBID);	//禁用
	}
	m_lstPowerDevInfo.SetItemText(m_iSelectIndex,5,cstrEnable);
	iRet = NetClient_SetAlarmConfig(m_iLogonID, iItemNo,-1,CMD_ALARM_IN_CONFIG,&srcAlarmInConfig);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "","OperateInfo-TDSetAlarmConfig(Enable Item error. loginID %d,iItemNo %d)",m_iLogonID, srcAlarmInConfig.iInterfaceNo);
		return;
	}
}

void CLS_DonghuanSet::GetComTypeLastName(int _iComNo, string& _strLastComName)
{
	CString cstrComName = "";
	CString cstrComTypeName = "";
	ComDevice srcComInfo = {-1};
	srcComInfo.iSize = sizeof(ComDevice);
	srcComInfo.iComNo = _iComNo + 1;
	int iByteReturn = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID,NET_CLIENT_COM_DEVICE,-1,&srcComInfo,sizeof(ComDevice),&iByteReturn);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "","GetComTypeLastName-TDGetAlarmConfig(loginID %d,DeviceType %d)",m_iLogonID, srcComInfo.iDeviceType);
		return;
	}

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

	cstrComName = cstrComTypeName;
	_strLastComName = cstrComName.GetBuffer();
	cstrComName.ReleaseBuffer();
}

void CLS_DonghuanSet::GetComTypeFirstName(int _iComNo, string& _strFirstName)
{
	if (NetClient_GetComFormat_V2)
	{
		COMFORMAT srcComFormat = {0};
		srcComFormat.iSize = sizeof(COMFORMAT);
		srcComFormat.iComNo = _iComNo;
		int iRet = NetClient_GetComFormat_V2(m_iLogonID,&srcComFormat);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "","GetComTypeFirstName-TDGetComFormat_V2(loginID %d,iComNo %d)",m_iLogonID, srcComFormat.iComNo);
			return;
		}

		CString cstrFirstName = "";
		switch(srcComFormat.iComType)
		{
		case enu_485:
			_strFirstName = "485";
			break;
		case enu_232:
			_strFirstName = "232";
			break;
		case enu_422:
			_strFirstName = "422";
			break;
		default:
			break;
		}
	}
}



BOOL CLS_DonghuanSet::StringToStruct( CString _cstrSrc,StrctSwicth* _strctDest )
{
	if (NULL == _strctDest)
	{
		return FALSE;
	}

	int iIndex = _cstrSrc.Find('=');
	if (iIndex < 0)
	{
		return FALSE;
	}

	CString strKey = _cstrSrc.Left(iIndex);
	CString strValue = _cstrSrc.Right(_cstrSrc.GetLength()-iIndex-1);

	_strctDest->m_iMode = atoi((LPSTR)(LPCTSTR)strValue);

	return TRUE;
}

BOOL CLS_DonghuanSet::StringToStruct( CString _cstrSrc,StrctSimu* _strctDest )
{
	if (NULL == _strctDest)
	{
		return FALSE;
	}

	static int s_iParamNum = 0;
	while(1)
	{
		int iIndex = _cstrSrc.Find(',');
		if (iIndex < 0)
		{
			s_iParamNum = 0;
			break;
		}

		s_iParamNum++;
		CString cstrParam = _cstrSrc.Left(iIndex);

		int iParamIndex = cstrParam.Find('=');
		if (iParamIndex < 0)
		{
			return FALSE;
		}
		CString strKey = cstrParam.Left(iParamIndex);
		CString strValue = cstrParam.Right(cstrParam.GetLength()-iParamIndex-1);

		switch (s_iParamNum)
		{
		case 1:
			strcpy(_strctDest->m_cSimuUnit,strValue.GetBuffer());
			break;
		case 2:
			_strctDest->m_iCollectTime = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 3:
			_strctDest->m_dbRangeUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 4:
			_strctDest->m_dbRangeUpValue = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 5:
			_strctDest->m_dbRangeDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 6:
			_strctDest->m_dbRangeDownValue = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 7:
			_strctDest->m_dbAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;		
		case 8:
			_strctDest->m_dbAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 9:
			_strctDest->m_dbDisAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 10:
			_strctDest->m_dbDisAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		default:
			break;
		}

		_cstrSrc = _cstrSrc.Right(_cstrSrc.GetLength()-iIndex-1);
	}

	return TRUE;
}

BOOL CLS_DonghuanSet::StringToStruct( CString _cstrSrc,StrctCom* _strctDest )
{
	if (NULL == _strctDest)
	{
		return FALSE;
	}

	static int s_iParamNum = 0;
	while(1)
	{
		int iIndex = _cstrSrc.Find(',');
		if (iIndex < 0)
		{
			s_iParamNum = 0;
			break;
		}

		s_iParamNum++;
		CString cstrParam = _cstrSrc.Left(iIndex);

		int iParamIndex = cstrParam.Find('=');
		if (iParamIndex < 0)
		{
			return FALSE;
		}
		CString strKey = cstrParam.Left(iParamIndex);
		CString strValue = cstrParam.Right(cstrParam.GetLength()-iParamIndex-1);

		switch (s_iParamNum)
		{
		case 1:
			_strctDest->m_iAddr = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 2:
			_strctDest->m_strctTem.m_dbTemAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 3:
			_strctDest->m_strctTem.m_dbTemAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 4:
			_strctDest->m_strctTem.m_dbTemDisAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 5:
			_strctDest->m_strctTem.m_dbTemDisAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 6:
			_strctDest->m_strctTem.m_dbHulAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 7:
			_strctDest->m_strctTem.m_dbHulAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;		
		case 8:
			_strctDest->m_strctTem.m_dbHulDisAlarmUpLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		case 9:
			_strctDest->m_strctTem.m_dbHulDisAlarmDownLevel = atoi((LPSTR)(LPCTSTR)strValue);
			break;
		default:
			break;
		}
		_cstrSrc = _cstrSrc.Right(_cstrSrc.GetLength()-iIndex-1);
	}

	return TRUE;
}


void CLS_DonghuanSet::OnBnClickedBtnAlarmReceiveSave()
{
	// TODO: Add your control notification handler code here
	AddAlarmHost srcAddAlarmHost = {0};
	srcAddAlarmHost.iSize = sizeof(AddAlarmHost);
	srcAddAlarmHost.iHostIndex = HOSTINDEX;
	srcAddAlarmHost.iEnable = 1;   //使能
	CString cstrIPAddr;
	m_edtIP.GetWindowText(cstrIPAddr);
	memcpy(srcAddAlarmHost.cIP, cstrIPAddr, cstrIPAddr.GetLength()+1);
	srcAddAlarmHost.iPort = GetDlgItemInt(IDC_EDT_ALARM_RECEIVE_PORT);
	int iRet = NetClient_SetAlarmConfig(m_iLogonID, -1, -1, CMD_DH_ADD_ALARM_HOST, &srcAddAlarmHost);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "","[CLS_DonghuanSet::OnBnClickedBtnAlarmReceiveSave] TDSetAlarmConfig failed! logonID(%d)"
			,m_iLogonID);
		return;
	}
}

BOOL CLS_DonghuanSet::StructToString( StrctSwicth* _strctSrc, CString& _cstrDest )
{
	if (NULL == _strctSrc)
	{
		return FALSE;
	}

	_cstrDest.Format("mode=%d",_strctSrc->m_iMode);

	return TRUE;
}

BOOL CLS_DonghuanSet::StructToString( StrctSimu* _strctSrc, CString& _cstrDest )
{
	if (NULL == _strctSrc)
	{
		return FALSE;
	}

	_cstrDest.Format("unit=%s,interval=%s,disuplimit=%s,disupvalue=%s,dislowlimit=%s,dislowvalue=%s,alarmup=%s,alarmlow=%s,elimup=%s,elimlow=%s,",
		_strctSrc->m_cSimuUnit,
		_strctSrc->m_iCollectTime,
		_strctSrc->m_dbRangeUpLevel,
		_strctSrc->m_dbRangeUpValue,
		_strctSrc->m_dbRangeDownLevel,
		_strctSrc->m_dbRangeDownValue,
		_strctSrc->m_dbAlarmUpLevel,
		_strctSrc->m_dbAlarmDownLevel,
		_strctSrc->m_dbDisAlarmUpLevel,
		_strctSrc->m_dbDisAlarmDownLevel
		);
// 	CString cstrData = "";
// 	CLS_TString tData;
// 	tData.Append(_T("unit"),_strctSrc->m_cSimuUnit);
// 	tData.Append(_T("interval"),_strctSrc->m_iCollectTime);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbRangeUpLevel);
// 	tData.Append(_T("disuplimit"),cstrData);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbRangeUpValue);
// 	tData.Append(_T("disupvalue"),cstrData);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbRangeDownLevel);
// 	tData.Append(_T("dislowlimit"),cstrData);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbRangeDownValue);
// 	tData.Append(_T("dislowvalue"),cstrData);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbAlarmUpLevel);
// 	tData.Append(_T("alarmup"),cstrData);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbAlarmDownLevel);
// 	tData.Append(_T("alarmlow"),cstrData);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbDisAlarmUpLevel);
// 	tData.Append(_T("elimup"),cstrData);
// 	cstrData.Format("%0.2f",_strctSrc->m_dbDisAlarmDownLevel);
// 	tData.Append(_T("elimlow"),cstrData);
// 	tData.Combine(_cstrDest);

	return TRUE;
}

BOOL CLS_DonghuanSet::StructToString( StrctCom* _strctSrc, CString& _cstrDest )
{
	if (NULL == _strctSrc)
	{
		return FALSE;
	}
	_cstrDest.Format("addr=%s,temalarmup=%s,temalarmlow=%s,temelimup=%s,temelimlow=%s,humalarmup=%s,humalarmlow=%s,humelimup=%s,humelimlow=%s",
		_strctSrc->m_iAddr,
		_strctSrc->m_strctTem.m_dbTemAlarmUpLevel,
		_strctSrc->m_strctTem.m_dbTemAlarmDownLevel,
		_strctSrc->m_strctTem.m_dbTemDisAlarmUpLevel,
		_strctSrc->m_strctTem.m_dbTemDisAlarmDownLevel,
		_strctSrc->m_strctTem.m_dbHulAlarmUpLevel,
		_strctSrc->m_strctTem.m_dbHulAlarmDownLevel,
		_strctSrc->m_strctTem.m_dbHulDisAlarmUpLevel,
		_strctSrc->m_strctTem.m_dbHulDisAlarmDownLevel
		);
	return TRUE;
}
