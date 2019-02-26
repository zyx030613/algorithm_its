
#include "stdafx.h"
#include "NetClientDemo.h"
#include "../Include/NVSSDK_INTERFACE.h"
#include "LinkBSF.h"
#include "../Common/CommonFun.h"
#include <Shlwapi.h>
// CLS_LinkBSF 对话框

IMPLEMENT_DYNAMIC(CLS_LinkBSF, CDialog)

CLS_LinkBSF::CLS_LinkBSF(int _iLogonID, CWnd* pParent /*=NULL*/)
	: CDialog(CLS_LinkBSF::IDD, pParent)
{
	m_iLogonID = _iLogonID;
}

CLS_LinkBSF::~CLS_LinkBSF()
{
}

void CLS_LinkBSF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_LINK_DEV, m_lstLinkDevice);
	DDX_Control(pDX, IDC_CBO_ALARM_CLEAR, m_cboAlarmClear);
}


BEGIN_MESSAGE_MAP(CLS_LinkBSF, CDialog)
END_MESSAGE_MAP()


// CLS_LinkBSF 消息处理程序

BOOL CLS_LinkBSF::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_LINK_DEV, IDS_CONFIG_LINK_DEVICE);
	SetDlgItemTextEx(IDC_STC_ALARM_CLEAR, IDS_CONFIG_LINK_ALARM_CLEAR);

	InitDlgData();

	UpdateLinkDeviceList();
	return TRUE;
}

void CLS_LinkBSF::InitDlgData()
{
	//联动设备表格
	int iColumn = 0;
	DWORD dwStyle = m_lstLinkDevice.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT| LVS_EX_CHECKBOXES; 
	m_lstLinkDevice.SetExtendedStyle(dwStyle);
	m_lstLinkDevice.InsertColumn(iColumn++, GetTextEx(IDS_CONFIG_LINK_DEV_NUM), LVCFMT_LEFT, 52);
	m_lstLinkDevice.InsertColumn(iColumn++, GetTextEx(IDS_CONFIG_LINK_DEV_NAME), LVCFMT_LEFT, 150);
	//消警时操作
	m_cboAlarmClear.InsertString(0,GetTextEx(IDS_ALARM_SCHEDULE_STATUS_ENABLE));
	m_cboAlarmClear.InsertString(1,GetTextEx(IDS_ALARM_SCHEDULE_STATUS_DISABLE));
	m_cboAlarmClear.InsertString(2,GetTextEx(IDS_CONFIG_DH_MANUAL_RECOVER));
	m_cboAlarmClear.SetCurSel(0);
}

void CLS_LinkBSF::SetDlgInfo(char* _cParam,int _iSize)
{
	//联动设备
	int iCount = 5;
	for (int iItem = 0; iItem < iCount; iItem++)
	{
		int iRow = 0;
		m_lstLinkDevice.SetItemText(iItem, iRow++, "编号数");
		m_lstLinkDevice.SetItemText(iItem, iRow++, "联动设备名称");
		m_lstLinkDevice.SetCheck(iItem,1);
	}	
	//消警时操作
	m_cboAlarmClear.SetCurSel(0);
}

void CLS_LinkBSF::GetDlgInfo(char* _cParam,int _iSize)
{
	//联动设备
	int iCount = 5;
	for (int iItem = 0; iItem < iCount; iItem++)
	{
		int iSel = m_lstLinkDevice.GetCheck(iItem);
	}	
	//消警时操作
	int iOpreat = m_cboAlarmClear.GetCurSel();
}

void CLS_LinkBSF::UpdateLinkDeviceList()
{
	if (m_iLogonID == -1)
	{
		return;
	}

	int iAlarmInPortNum;
	int iAlarmOutPortNum;
	int iRet = NVSSDK_INTERFACE::NetClient_GetAlarmPortNum(m_iLogonID, &iAlarmInPortNum, &iAlarmOutPortNum);
	if (iRet < 0)
	{
		return;
	} 

	m_lstLinkDevice.DeleteAllItems();

	for (int i = 0; i < iAlarmInPortNum; i++)
	{
		int iEnable = 0;
		int iRetGet = NVSSDK_INTERFACE::NetClient_GetAlarmConfig(m_iLogonID, i, -1, CMD_DH_DEVICE_ENABLE, &iEnable);
		if (iRetGet < 0 || iEnable != 1)
		{
			continue;
		}

		AlarmInConfig alarminConfig;
		alarminConfig.iSize = sizeof(AlarmInConfig);
		iRetGet = NVSSDK_INTERFACE::NetClient_GetAlarmConfig(m_iLogonID, i, -1, CMD_ALARM_IN_CONFIG, &alarminConfig);
		if (iRetGet < 0)
		{
			continue;
		}

		int iItemIndex = m_lstLinkDevice.InsertItem(m_lstLinkDevice.GetItemCount(), (IntToStr(i+1)).c_str());
		m_lstLinkDevice.SetItemText(iItemIndex, 1, alarminConfig.cName);
	}
}


BOOL CLS_LinkBSF::GetData(AlarmInLink* _pAlarmInLink)
{
	if (_pAlarmInLink == NULL)
	{
		return FALSE;
	}

	//CLS_DlgLinkBase::GetData(_pAlarmInLink);

	//_pAlarmInLink->iDisappearType = m_cboAlarmClear.GetItemData(m_cboAlarmClear.GetCurSel());

// 	CString cstrRecoveryParam = "";
// 	m_cboAlarmClear.GetWindowText(cstrRecoveryParam);
// 	if (cstrRecoveryParam != "")
// 	{
// 		_pAlarmInLink->iDisappearTime = StrToInt(cstrRecoveryParam);
// 	}
// 	else
// 	{
// 		_pAlarmInLink->iDisappearTime = -1;
// 	}
// 
// 	if (_pAlarmInLink->iDisappearType == n_RecoverType_Delay || _pAlarmInLink->iDisappearType == n_RecoverType_DisAlarm_Delay)
// 	{
// 		if (_pAlarmInLink->iDisappearTime == -1)
// 		{
// 			return FALSE;
// 		} 
// 		else if (!CheckValue(_pAlarmInLink->iDisappearTime, 0, MAX_LINKTIME_LIMIT, IDS_LINK_LINK_TIME))
// 		{
// 			return FALSE;
// 		}
// 	}
// 
// 	if (_pAlarmInLink->iDisappearType == n_RecoverType_None || _pAlarmInLink->iDisappearType == n_RecoverType_DisAlarm)
// 	{
// 		_pAlarmInLink->iDisappearTime = DISAPPEARTIME_NO;
// 	}

	int iCheck32 = 0;
	for (int i = 0; i < LINK_DEVICE_STEP; i++)
	{
		if (DeviceGetCheck(i))
		{
			iCheck32 = iCheck32|(1<<i);
		}
	}

	int iCheck64 = 0;
	for (int i = LINK_DEVICE_STEP; i < LINK_DEVICE_STEP*2; i++)
	{
		if (DeviceGetCheck(i))
		{
			iCheck64 = iCheck64|(1<<i);
		}
	}

	int iCheck96 = 0;
	for (int i = LINK_DEVICE_STEP*2; i < LINK_DEVICE_STEP*3; i++)
	{
		if (DeviceGetCheck(i))
		{
			iCheck96 = iCheck96|(1<<i);
		}
	}

	int iCheck128 = 0;
	for (int i = LINK_DEVICE_STEP*3; i < LINK_DEVICE_STEP*4; i++)
	{
		if (DeviceGetCheck(i))
		{
			iCheck128 = iCheck128|(1<<i);
		}
	}

	if (iCheck32 == 0 && iCheck64 == 0 && iCheck96 == 0 && iCheck128 == 0)
	{
		return FALSE;
	}

	CString cstrParam = (IntToStr(iCheck32)).c_str();	
	cstrParam = cstrParam + PARAM_STEP_ADD + (IntToStr(iCheck64)).c_str();
	cstrParam = cstrParam + PARAM_STEP_ADD + (IntToStr(iCheck96)).c_str();
	cstrParam = cstrParam + PARAM_STEP_ADD + (IntToStr(iCheck128)).c_str();

	CString strData;
	strData.AppendFormat(_T(",dev=%s"),cstrParam);

	CString cstrDev = strData;

	strcpy_s(_pAlarmInLink->cParam, (LPSTR)(LPCTSTR)cstrDev);

	return TRUE;
}

void CLS_LinkBSF::DeviceSetCheck(int _iNo, BOOL _blCheck)
{
	int iCount = m_lstLinkDevice.GetItemCount();

	for(int i = 0; i < iCount; i++)
	{
		int iNo = StrToInt(m_lstLinkDevice.GetItemText(i, 0)) - 1;
		if (_iNo == iNo)
		{
			m_lstLinkDevice.SetCheck(i, _blCheck);
			break;
		}
	}	
}

BOOL CLS_LinkBSF::DeviceGetCheck(int _iNo)
{
	int iCount = m_lstLinkDevice.GetItemCount();

	for(int i = 0; i < iCount; i++)
	{
		int iNo = StrToInt(m_lstLinkDevice.GetItemText(i, 0)) - 1;
		if (_iNo == iNo)
		{
			return m_lstLinkDevice.GetCheck(i);
		}
	}

	return FALSE;
}

void CLS_LinkBSF::CheckDevice(int _iDevice, int _iShift)
{
	for (int i = 0; i < LINK_DEVICE_STEP; i++)
	{
		if ((_iDevice&(1<<i)) == 0)
		{
			DeviceSetCheck(i + _iShift, FALSE);
		}
		else
		{
			DeviceSetCheck(i + _iShift, TRUE);
		}
	}
}

bool CLS_LinkBSF::CheckValue( int _iNum, int _iStart, int _iEnd, CString _strMsg/* = _T("")*/)
{
	if(_iNum < _iStart || _iNum > _iEnd)
	{
		CString strMsg;
		if (_strMsg == _T(""))
		{
		}
		else
		{
			strMsg = _strMsg;
		}
		return false;
	}
	return true;
}

bool CLS_LinkBSF::CheckValue( int _iNum, int _iStart, int _iEnd, int _iTitle )
{
	if(_iNum < _iStart || _iNum > _iEnd)
	{
		CString strMsg;
		if (_iTitle > 0)
		{
		}
		else
		{
		}
		return false;
	}
	return true;
}

bool CLS_LinkBSF::CheckValue( double _dbNum, double _dbStart, double _dbEnd, int _iTitle)
{
	if(_dbNum < _dbStart || _dbNum > _dbEnd)
	{
		CString strMsg;
		if (_iTitle > 0)
		{
		}
		else
		{
		}
		return false;
	}
	return true;
}

void CLS_LinkBSF::SetData(AlarmInLink* _pAlarmInLink)
{
	if (_pAlarmInLink == NULL)
	{
		return;
	}

//	CLS_DlgLinkBase::SetData(_pAlarmInLink);

	for (int i = 0; i < m_cboAlarmClear.GetCount(); i++)
	{
		if (m_cboAlarmClear.GetItemData(i) == _pAlarmInLink->iDisappearType)
		{
			m_cboAlarmClear.SetCurSel(i); //恢复类型
		}
	}

	//OnCbnSelchangeCboLinkarmingRecoverType();

	if (_pAlarmInLink->iDisappearType == n_RecoverType_Delay || _pAlarmInLink->iDisappearType == n_RecoverType_DisAlarm_Delay)
	{
		//m_edtLInkArmingTime.SetWindowText((IntToStr(_pAlarmInLink->iDisappearTime)).c_str());
	}

	LPCTSTR lpszSource = _pAlarmInLink->cParam;
	CString strData = _pAlarmInLink->cParam;



	int iParamIndex = strData.Find('=');
	if (iParamIndex < 0)
	{
		return;
	}
	CString strKey = strData.Left(iParamIndex);
	CString strValue = strData.Right(strData.GetLength()-iParamIndex-1);

	CString cstrSource = strValue;

	//联动设备1-32
	CString cstrDevice; 
	if (AfxExtractSubString(cstrDevice, cstrSource, 0, PARAM_STEP))
	{
		int iDevice = StrToInt(cstrDevice);
		CheckDevice(iDevice);
	}

	//联动设备33-64 
	if (AfxExtractSubString(cstrDevice, cstrSource, 1, PARAM_STEP))
	{
		int iDevice = StrToInt(cstrDevice);
		CheckDevice(iDevice, LINK_DEVICE_STEP);
	}

	//联动设备65-96 
	if (AfxExtractSubString(cstrDevice, cstrSource, 2, PARAM_STEP))
	{
		int iDevice = StrToInt(cstrDevice);
		CheckDevice(iDevice, LINK_DEVICE_STEP*2);
	}

	//联动设备97-128 
	if (AfxExtractSubString(cstrDevice, cstrSource, 3, PARAM_STEP))
	{
		int iDevice = StrToInt(cstrDevice);
		CheckDevice(iDevice, LINK_DEVICE_STEP*3);
	}

	for (int i = 0; i < m_lstLinkDevice.GetItemCount(); i++)
	{		
		if (!m_lstLinkDevice.GetCheck(i))
		{
			m_blFullSet = false;
			break;
		}
	}

	if (m_blFullSet)
	{
		//m_chkSelectAllDevice.SetCheck(1);
	}
}


void CLS_LinkBSF::SetAlarmTypeFlag(bool _bAlarmTypeFlag)
{
	m_cboAlarmClear.ResetContent();
	int iItemComb = m_cboAlarmClear.AddString(GetText(IDS_RECOVER_TYPE_NONE));//不恢复
	m_cboAlarmClear.SetItemData(iItemComb, DH_ALARM_DISAPPEAR_TYPE_NOT);
	iItemComb = m_cboAlarmClear.AddString(GetText(IDS_RECOVER_TYPE_DELAY));//延时恢复
	m_cboAlarmClear.SetItemData(iItemComb, DH_ALARM_DISAPPEAR_TYPE_DELAY);
	if (!_bAlarmTypeFlag)
	{
		iItemComb = m_cboAlarmClear.AddString(GetText(IDS_RECOVER_TYPE_DISALARM));//消警恢复
		m_cboAlarmClear.SetItemData(iItemComb, DH_ALARM_DISAPPEAR_TYPE_DIS_RECOVERY);
		iItemComb = m_cboAlarmClear.AddString(GetText(IDS_RECOVER_TYPE_DISALARM_DELAY));//消警延时恢复
		m_cboAlarmClear.SetItemData(iItemComb, DH_ALARM_DISAPPEAR_TYPE_DIS_DELAY);	
	}
	m_cboAlarmClear.SetCurSel(0);
}
