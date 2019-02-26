// NetAdminWindow.cpp : implementation file
//

#include "stdafx.h"
#include "NetAdminPage.h"
#include "NetClientTypes.h"
#include "../LogonView.h"
#include "ProductModel.h"

#define MSG_ADMIN		(WM_USER + 1101)

HWND CLS_NetAdminPage::s_hWnd = NULL;
// CLS_NetAdminPage dialog

IMPLEMENT_DYNAMIC(CLS_NetAdminPage, CDialog)

CLS_NetAdminPage::CLS_NetAdminPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_NetAdminPage::IDD, pParent)
{
	memset(&m_tSortData,0,sizeof(SORT_DATA));
}

CLS_NetAdminPage::~CLS_NetAdminPage()
{

}

void CLS_NetAdminPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVER, m_lvServer);
	DDX_Control(pDX, IDC_COMBO_INTERFACE, m_cboInterface);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_cboDeviceType);
}


BEGIN_MESSAGE_MAP(CLS_NetAdminPage, CLS_BasePage)
	ON_WM_DESTROY()
	ON_MESSAGE(MSG_ADMIN,&CLS_NetAdminPage::OnSeachMsg)
	ON_CBN_SELCHANGE(IDC_COMBO_INTERFACE, &CLS_NetAdminPage::OnCbnSelchangeComboInterface)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CLS_NetAdminPage::OnBnClickedBtnRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_TYPE, &CLS_NetAdminPage::OnCbnSelchangeComboDeviceType)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SERVER, &CLS_NetAdminPage::OnNMDblclkListServer)
END_MESSAGE_MAP()


// CLS_NetAdminPage message handlers

BOOL CLS_NetAdminPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_lvServer.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_tSortData.m_plvCtrl = &m_lvServer;
	m_tSortData.m_iSubItem = -1;

	UI_UpdateDialog();

	m_cboInterface.SetCurSel(0);
	m_cboDeviceType.SetCurSel(0);

	m_lvServer.SetSortType(1,SORT_TYPE_IP);
	m_lvServer.SetSortType(2,SORT_TYPE_IP);
	m_lvServer.SetSortType(3,SORT_TYPE_IP);
	m_lvServer.SetSortType(4,SORT_TYPE_IP);
	m_lvServer.SetSortType(5,SORT_TYPE_INT);
	m_lvServer.SetSortType(6,SORT_TYPE_INT);
	m_lvServer.SetSortType(7,SORT_TYPE_INT);
	m_lvServer.SetSortType(9,SORT_TYPE_INT);

	if (DLL_LOAD_SUCCESS == CLS_NetAdmin_Interface::LoadDLL())
	{
		s_hWnd = this->GetSafeHwnd();
		NetAdmin_Startup();
		NetAdmin_SetNotify(&CLS_NetAdminPage::SeachNotify);
		InitProductModel();
		InitDeviceType();

		int iInterface = 0;
		char* pcIP = NULL;
		while((pcIP = NetAdmin_GetNetInterface(iInterface++)))
		{
			m_cboInterface.AddString(pcIP);
		}

		int iType = 0;
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));
		m_cboDeviceType.AddString(GetDeviceType(iType++));

		this->EnableWindow(TRUE);

		Refresh();
	}
	else
	{
		MessageBox(_T("error in load NetAdmin.dll"),_T(""),MB_TOPMOST|MB_OK);
		this->EnableWindow(FALSE);
	}

	return TRUE; 
}

void CLS_NetAdminPage::OnDestroy()
{
	CLS_BasePage::OnDestroy();

	if (NetAdmin_Closeup)
	{
		NetAdmin_Closeup();
	}

	CLS_NetAdmin_Interface::FreeDLL();
}

void __stdcall CLS_NetAdminPage::SeachNotify(PTDEVICE _pDevice)
{
	__try
	{
		if (_pDevice)
		{
			LRESULT lRet = SendMessageTimeout(s_hWnd,MSG_ADMIN,(WPARAM)_pDevice,0,SMTO_NORMAL,500,NULL);
// 			if (0 == lRet)
// 			{
// 				AddLog(LOG_TYPE_MSG,"","SeachNotify(%s,%d,%#08x)",_pDevice->m_cIP,_pDevice->m_iDeviceType,GetLastError());
// 			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//AddLog(LOG_TYPE_MSG,"","SeachNotify exception");
	}
}

LRESULT CLS_NetAdminPage::OnSeachMsg( WPARAM wParam, LPARAM lParam )
{
	__try
	{
		PTDEVICE pDevice = (PTDEVICE)wParam;
		AddServer(pDevice);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		AddLog(LOG_TYPE_MSG,"","AddServer exception");
	}
	return 0;
}

void CLS_NetAdminPage::AddServer( PTDEVICE _pDevice )
{
	int iDeviceType = m_cboDeviceType.GetCurSel() - 1;
	if (iDeviceType >= 0 && iDeviceType != _pDevice->m_iDeviceType)
	{
		return;
	}

	int iItem = -1;
	LVFINDINFO info;
	CString strDeviceType = GetDeviceType(_pDevice->m_iDeviceType);
	info.flags = LVFI_STRING;
	info.psz = _pDevice->m_cMAC;
	while ((iItem = m_lvServer.FindItem(&info,iItem)) != -1)
	{
		CString strIP = m_lvServer.GetItemText(iItem,1);
		CString strDevType = m_lvServer.GetItemText(iItem,8);
		if (0 == strDeviceType.CompareNoCase(strDevType) && 0 == strIP.CompareNoCase(_pDevice->m_cIP))
		{
			return;
		}
	}
	
	iItem = m_lvServer.GetItemCount();
	m_lvServer.InsertItem(iItem,_pDevice->m_cMAC);
	m_lvServer.SetItemText(iItem,1,_pDevice->m_cIP);
	m_lvServer.SetItemText(iItem,2,_pDevice->m_cMask);
	m_lvServer.SetItemText(iItem,3,_pDevice->m_Gateway);
	m_lvServer.SetItemText(iItem,4,_pDevice->m_cDNS);
	m_lvServer.SetItemText(iItem,5,IntToString(_pDevice->m_iChanNum));
	m_lvServer.SetItemText(iItem,6,IntToString(_pDevice->m_iServerPort));
	m_lvServer.SetItemText(iItem,7,IntToString(_pDevice->m_iClientPort));
	m_lvServer.SetItemText(iItem,8,strDeviceType);
	m_lvServer.SetItemText(iItem,9,IntToString(_pDevice->m_iHttpPort));
	m_lvServer.SetItemText(iItem,10,GetProductModel(_pDevice->m_iProductModel&0xffff));
	m_lvServer.SetItemText(iItem,11,_pDevice->m_cFactoryID);
	m_lvServer.SetItemText(iItem,12,_pDevice->m_cKernelVersion);
	m_lvServer.SetItemText(iItem,13,_pDevice->m_cOCXVersion);
}

void CLS_NetAdminPage::Refresh()
{
	m_lvServer.DeleteAllItems();
	NetAdmin_SeekServers();
}

void CLS_NetAdminPage::OnCbnSelchangeComboInterface()
{
	 NetAdmin_SetNetInterface(m_cboInterface.GetCurSel() - 1);
	 Refresh();
}

void CLS_NetAdminPage::OnBnClickedBtnRefresh()
{
	Refresh();
}

void CLS_NetAdminPage::Make_M7_PM(int _iPM, char* _pcID, char* _pcID1)
{
	CString strPM;
	strPM.Format("%s/%s", _pcID, _pcID1);
	m_mapProductModel.insert(pair<int, char*>(_iPM, (LPSTR)(LPCTSTR)strPM));
}

void CLS_NetAdminPage::InitProductModel()
{
#define INSERT_PRODUCTMODEL(id)				m_mapProductModel.insert(pair<int,char*>(id, #id));
#define INSERT_PRODUCTMODEL_M7(id, idEx)     Make_M7_PM(id, #id, #idEx)

	INSERT_PRODUCTMODEL(TC_NVSS);
	INSERT_PRODUCTMODEL(TC_NS621S);
	INSERT_PRODUCTMODEL(TC_NS621S_USB);
	INSERT_PRODUCTMODEL(TC_NS224S);
	INSERT_PRODUCTMODEL(TC_NC621S);
	INSERT_PRODUCTMODEL(TC_NC8000S);
	INSERT_PRODUCTMODEL(TC_NC8001S);
	INSERT_PRODUCTMODEL(TC_NC8100S);
	INSERT_PRODUCTMODEL(TC_NC8101S);
	INSERT_PRODUCTMODEL(TC_NC8200S);
	INSERT_PRODUCTMODEL(TC_NC8700S2);
	INSERT_PRODUCTMODEL(TC_NC8250);
	INSERT_PRODUCTMODEL(TC_NC9010S2_MP);
	INSERT_PRODUCTMODEL(TC_NC9000S2_2MP);
	INSERT_PRODUCTMODEL(TC_NC9010N1_2MP);
	INSERT_PRODUCTMODEL(TC_NC9000S3_3MP);
	INSERT_PRODUCTMODEL(TC_NH9106N1_2MPIR);
	//INSERT_PRODUCTMODEL(TC_NS921_N1_2MP);
	INSERT_PRODUCTMODEL(TC_CC9118_MP_E);
	INSERT_PRODUCTMODEL(TC_NC9100S3_3MP_IR30);
	INSERT_PRODUCTMODEL(TC_NT9054S2_MPIR);
	INSERT_PRODUCTMODEL(TC_NS621S2);
	INSERT_PRODUCTMODEL(TC_NS324S2);
	INSERT_PRODUCTMODEL(TC_NS628S2);
	INSERT_PRODUCTMODEL(TC_NC9010I_2MP);
	INSERT_PRODUCTMODEL(TC_NC9000I_5MP);
	INSERT_PRODUCTMODEL(TC_2816AN_SH);
	INSERT_PRODUCTMODEL(TC_2808AN_S_3511);
	INSERT_PRODUCTMODEL(TC_2816AN_SD);
	INSERT_PRODUCTMODEL(TC_2816AN_SD_E);
	INSERT_PRODUCTMODEL(TC_2808AN_S_3515);
	INSERT_PRODUCTMODEL(TC_2804AN_MX);
	INSERT_PRODUCTMODEL(TC_2816AN_S);
	INSERT_PRODUCTMODEL(TC_H802BHX_T);
	INSERT_PRODUCTMODEL(TC_2832AN_SS)
	INSERT_PRODUCTMODEL(TC_1002S2_3C);
	INSERT_PRODUCTMODEL(TC_2802AN_SDI);
	INSERT_PRODUCTMODEL(TC_H908NC_H_V50);
	INSERT_PRODUCTMODEL(TC_ND921S2_MP);
	INSERT_PRODUCTMODEL(TC_ND921S2_2MP);
	INSERT_PRODUCTMODEL(TC_2800AN_SF_L_H, TC_2800AN_SF_L);
	INSERT_PRODUCTMODEL(TC_2800AN_SF_H, TC_2800AN_SF);
	INSERT_PRODUCTMODEL(TC_2804AN_SA);
	INSERT_PRODUCTMODEL(TC_2800AN_SF_L, TC_2800AN_SF_L_H);
	INSERT_PRODUCTMODEL(TC_2800AN_SF, TC_2800AN_SF_H);

	INSERT_PRODUCTMODEL(TC_2804AN_SDI);

	INSERT_PRODUCTMODEL(TC_FS0013ERS_HD);         // 修改高清播放器
	INSERT_PRODUCTMODEL(TC_NC9100S3E_MP_IR30);    //
	INSERT_PRODUCTMODEL(TC_NC9000S3_2MP_E);       // 200W摄像机 朱建立项目
	INSERT_PRODUCTMODEL(TC_NC9200S3_MP_E_IR15);   // 之前复用三百万productmodel 0x0059,徐蒙蒙项目
	INSERT_PRODUCTMODEL(TC_NC9100S1_MP_IR);       // 0xC0046,刘子龙项目
	INSERT_PRODUCTMODEL(TC_NS921S3_HD_V1);        // 0xC0056,马尊峰项目 之前TC_NS921_N1_2MP设备撤销，变为此款
	INSERT_PRODUCTMODEL(TC_NC9000S3_MP_E);        // 齐学庆项目
	INSERT_PRODUCTMODEL(TC_2804AN_SQ);
	INSERT_PRODUCTMODEL(TC_2808AN_SF_L);

	INSERT_PRODUCTMODEL(TC_ND921S2_SDI)
	INSERT_PRODUCTMODEL(TC_21X_R2);
	INSERT_PRODUCTMODEL(TC_21X_R3);
	INSERT_PRODUCTMODEL(TC_21X_R5);

	//  跟踪球
	INSERT_PRODUCTMODEL(TC_NH9206S3_2MP_IVS);
	INSERT_PRODUCTMODEL(TC_NC9000S3E_MP);
	INSERT_PRODUCTMODEL(TC_NC9200S3E_MP_IR);

	//add by bo 20140725
	INSERT_PRODUCTMODEL(TC_2804AN_SR_L);
	INSERT_PRODUCTMODEL(TC_H804I_HD_BP);
	INSERT_PRODUCTMODEL(TC_H904B_HD_V6_X);
	INSERT_PRODUCTMODEL(TC_H908NC_HD);
	INSERT_PRODUCTMODEL(TC_NC9100S3E_2MP_IR30);
	INSERT_PRODUCTMODEL(TC_NC9000S3E_2MP);
	INSERT_PRODUCTMODEL(TC_NC9200S3E_2MP_IR);
	INSERT_PRODUCTMODEL(TC_NC921S3E_MP_HD_C);
	INSERT_PRODUCTMODEL(TC_NH9406S3E_MPIR);
	INSERT_PRODUCTMODEL(TC_NH9406S3E_2MPIR);
	INSERT_PRODUCTMODEL(TC_NC9320S3E_2MP_E);
	INSERT_PRODUCTMODEL(TC_NC9320S3E_MP_E);								
	INSERT_PRODUCTMODEL(TC_218_T5);
	INSERT_PRODUCTMODEL(TC_218_T3H);
	INSERT_PRODUCTMODEL(TC_217_T5);
	INSERT_PRODUCTMODEL(TC_217_T3H);
	INSERT_PRODUCTMODEL(TC_NH9X06S6_XMPIR_A);
	INSERT_PRODUCTMODEL(TC_NH9X06S6_XMPIR_T);														
	INSERT_PRODUCTMODEL(TC_H804BE_HD);				
	INSERT_PRODUCTMODEL(TC_H804N_HD);						
	INSERT_PRODUCTMODEL(TC_2800AN_SF_L_H);		
	INSERT_PRODUCTMODEL(TC_2800AN_SF_H);				
	INSERT_PRODUCTMODEL(TC_2800AN_SF_L);			
	INSERT_PRODUCTMODEL(TC_2800AN_SF);		
	INSERT_PRODUCTMODEL(TC_H804BE_P);	
	INSERT_PRODUCTMODEL(TC_2800AN_R16_S2);
	INSERT_PRODUCTMODEL(TC_2804AN_M);
	INSERT_PRODUCTMODEL(TC_2800AN_R4_S1);
	INSERT_PRODUCTMODEL(TC_2800AN_R4_S2);
	INSERT_PRODUCTMODEL(TC_2800AN_R8_S2);
	INSERT_PRODUCTMODEL(TC_H804N_HD_P);
	INSERT_PRODUCTMODEL(TC_2800AN_R16_S2_V2_0);
	INSERT_PRODUCTMODEL(TC_2800AN_R16_S4);
	INSERT_PRODUCTMODEL(TC_2800AN_R32_S4);
	INSERT_PRODUCTMODEL(TC_2816AN_SR_V2_0);
	INSERT_PRODUCTMODEL(TC_2832AN_SR_V2_0);							
	INSERT_PRODUCTMODEL(TC_2864AN_SR);
	INSERT_PRODUCTMODEL(TC_7816W);

	//add by bo 20150713
	INSERT_PRODUCTMODEL(TC_NH9206N1_MPIR_IVS);
	INSERT_PRODUCTMODEL(TC_NS324S2);
	INSERT_PRODUCTMODEL(TC_NC9000S3E_5MP_UE);
	INSERT_PRODUCTMODEL(TC_NC9001S3E_3MP_E);
	INSERT_PRODUCTMODEL(TC_NC9201S3E_3MP_EI_IR);
	INSERT_PRODUCTMODEL(TC_NH9806S6_3MPIR_I);
	INSERT_PRODUCTMODEL(TC_CC9033_3MP);
	INSERT_PRODUCTMODEL(TC_NC9401S3E_4MP_I5_E);
	INSERT_PRODUCTMODEL(TC_NC9401S3E_4MP_I_E);
	INSERT_PRODUCTMODEL(TC_NC9001S3E_2MP_ES);
	INSERT_PRODUCTMODEL(TC_NH9904S6_2MP);
	INSERT_PRODUCTMODEL(TC_NH9806S6_2MPIR_S_A);
	INSERT_PRODUCTMODEL(TC_NC9320S3E_2MP_D);
	INSERT_PRODUCTMODEL(TC_217_T2);
	INSERT_PRODUCTMODEL(TC_217_T3);
	INSERT_PRODUCTMODEL(TC_237_5MPH);
	INSERT_PRODUCTMODEL(TC_238_5MPH);
	INSERT_PRODUCTMODEL(TC_227_2MP_S_Z);
	INSERT_PRODUCTMODEL(TC_217_1MP_S);
	INSERT_PRODUCTMODEL(TC_T800GE);
	INSERT_PRODUCTMODEL(TC_H904BIX_HD_I);
	INSERT_PRODUCTMODEL(TC_T238_5MP_S_Z);
	INSERT_PRODUCTMODEL(TC_T238_6MP);
	INSERT_PRODUCTMODEL(TC_T237_6MP);
	INSERT_PRODUCTMODEL(TC_T238_6MP_B);
	INSERT_PRODUCTMODEL(TC_NR2160M7_E16);
	INSERT_PRODUCTMODEL(TC_NR2080M7_E16);
	INSERT_PRODUCTMODEL(TC_NR2080M7_E8);
	INSERT_PRODUCTMODEL(TC_NR2040M7_E8);
	INSERT_PRODUCTMODEL(TC_NR2020M7_E8);
	INSERT_PRODUCTMODEL(TC_NR2080M7_S8);
	INSERT_PRODUCTMODEL(TC_NR2040M7_S8);
	INSERT_PRODUCTMODEL(TC_NR2020M7_S8);
	INSERT_PRODUCTMODEL(TC_NR2040M7_S4);
	INSERT_PRODUCTMODEL(TC_NR2020M7_S4);	
	INSERT_PRODUCTMODEL(TC_NR2020M7_S2);

	//Add 2015 12 31
	INSERT_PRODUCTMODEL(TC_NC9400S3E_MP_C_IR30);
	INSERT_PRODUCTMODEL(TC_NC9200S3E_2MP_E_I3);
	INSERT_PRODUCTMODEL(TC_T237_2MP_S);
	INSERT_PRODUCTMODEL(TC_NC9201S3E_4MP_EI_IR30);
	INSERT_PRODUCTMODEL(TC_NC9201S3E_4MP_EI_IR30_M);
	INSERT_PRODUCTMODEL(TC_NC9101S3E_2MP_EI_IRW30_S);
	INSERT_PRODUCTMODEL(TC_NC9201S3E_2MP_EI_IR30);
	INSERT_PRODUCTMODEL(TC_NC9011S3E_3MP);
	INSERT_PRODUCTMODEL(TC_NC9501S3E_2MP_I3S);
	INSERT_PRODUCTMODEL(TC_NC9201S3E_2MP_I3S);
	INSERT_PRODUCTMODEL(TC_NH9806S6_2MPIR_S_T);
	INSERT_PRODUCTMODEL(TC_2800AN_R4_S1_V2_0);
	INSERT_PRODUCTMODEL(TC_T237_7MP);
	INSERT_PRODUCTMODEL(TC_T238_7MP);
	INSERT_PRODUCTMODEL(TC_T237_2MP_S);
	INSERT_PRODUCTMODEL(TC_NH9406S6_MPIR_S);
	INSERT_PRODUCTMODEL(TC_NH9606S6_2MPIR_S);
	INSERT_PRODUCTMODEL(TC_T1);
	INSERT_PRODUCTMODEL(TC_NC9101S3E_2MP_ES);
	INSERT_PRODUCTMODEL(T227_2MP_S_Z_V2);
	INSERT_PRODUCTMODEL(TC_H804N_HD_4SATA);
	INSERT_PRODUCTMODEL(TC_2800AN_P4_S1);
	INSERT_PRODUCTMODEL(TC_2800AN_P4_S2);
	INSERT_PRODUCTMODEL(TC_2800AN_P16_S4);
	INSERT_PRODUCTMODEL(TC_2816AN_SR_DZ15543);
	INSERT_PRODUCTMODEL(TC_NR2020M7_S1);
	INSERT_PRODUCTMODEL(TC_NR2010M7_S1);
	INSERT_PRODUCTMODEL(TC_H802_XK);
	INSERT_PRODUCTMODEL(TC_H904BIX_N);
}

CString CLS_NetAdminPage::GetProductModel(int _iModel)
{
	CString strModel;
	map<int,char*>::iterator it = m_mapProductModel.find(_iModel);
	if (it == m_mapProductModel.end())
	{
		if (0xFFFF != _iModel)
		{
			strModel.Format(_T("undefined-%#x"),_iModel);
		}
	}
	else
	{
		strModel.Format(_T("%s"),it->second);
	}

	return strModel;
}

void CLS_NetAdminPage::InitDeviceType()
{
#define INSERT_DEVICETYPE(id)\
	m_mapProductModel.insert(pair<int,char*>(TYPE_##id, #id));

	INSERT_DEVICETYPE(NVS_T);
	INSERT_DEVICETYPE(KEYBOARD);
	INSERT_DEVICETYPE(CTL_ALLOTER);
	INSERT_DEVICETYPE(ALARMHOST);	
	INSERT_DEVICETYPE(NVS_S);
	INSERT_DEVICETYPE(MATRIX);
	INSERT_DEVICETYPE(NET_PU);
	INSERT_DEVICETYPE(NET_GURAD);
	INSERT_DEVICETYPE(PC_DVR);
	INSERT_DEVICETYPE(S_DECODER);
	INSERT_DEVICETYPE(NVS_TPLUS);
	INSERT_DEVICETYPE(WIH_S);
	INSERT_DEVICETYPE(EMBED_DVR);	
	INSERT_DEVICETYPE(SMS_200);
	INSERT_DEVICETYPE(ALARM_HOST42);
	INSERT_DEVICETYPE(TC_T820GE);
	INSERT_DEVICETYPE(TC_T860GE);
	INSERT_DEVICETYPE(TC_T890GE);
	INSERT_DEVICETYPE(TC_HDC);
	INSERT_DEVICETYPE(ONVIF); 
}

CString CLS_NetAdminPage::GetDeviceType( int _iType )
{
	CString strModel;
	map<int,char*>::iterator it = m_mapProductModel.find(_iType);
	if (it == m_mapProductModel.end())
	{
		strModel.Format(_T("undefined-%#x"),_iType);
	}
	else
	{
		strModel.Format(_T("%s"),it->second);
	}

	return strModel;
}

void CLS_NetAdminPage::OnCbnSelchangeComboDeviceType()
{
	Refresh();
}

void CLS_NetAdminPage::OnNMDblclkListServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	DEVICE_INFO tDevInit = {0};
	m_lvServer.GetItemText(pNMItemActivate->iItem,1,tDevInit.cIP,sizeof(tDevInit.cIP));
	//m_lvServer.GetItemText(pNMItemActivate->iItem,11,tDevInit.cID,sizeof(tDevInit.cID));
	CString strPort = m_lvServer.GetItemText(pNMItemActivate->iItem,6);
	tDevInit.iPort = atoi((LPSTR)(LPCTSTR)strPort);
//#ifdef _DEBUG
	strcpy_s(tDevInit.cUserName,sizeof(tDevInit.cUserName),"Admin");
	strcpy_s(tDevInit.cPassword,sizeof(tDevInit.cPassword),"1111");
//#endif

	CLS_LogonView logon(&tDevInit);
	if(IDOK != logon.DoModal())
	{
		return;
	}

	int iOldLogonID = -1;
	PDEVICE_INFO pDevLogon = logon.GetDeviceInfo();
	PDEVICE_INFO pDevFind = FindDevice(pDevLogon->cIP,pDevLogon->iPort,pDevLogon->cProxy,pDevLogon->cID,&iOldLogonID);
	if (pDevFind)
	{
		if(LOGON_SUCCESS == NetClient_GetLogonStatus(iOldLogonID))
		{
			AddLog(LOG_TYPE_MSG,"","FindDevice(%s,%d,%s,%s) device already exist!"
				,pDevFind->cIP,pDevLogon->iPort,pDevFind->cProxy,pDevFind->cID);
			return;
		}
	}

	int iLogonID = NetClient_LogonEx(pDevLogon->cProxy,pDevLogon->cIP,pDevLogon->cUserName,pDevLogon->cPassword,pDevLogon->cID,pDevLogon->iPort,"UTF-8");
	if (iLogonID >= 0)
	{
		AddLog(LOG_TYPE_SUCC,pDevLogon->cIP,"(%d)NetClient_LogonEx",iLogonID);
		if (pDevFind)
		{
			return;
		}
		PDEVICE_INFO pDevNew = AddDevice(iLogonID);
		if (pDevNew)
		{
			memcpy_s(pDevNew,sizeof(DEVICE_INFO),pDevLogon,sizeof(DEVICE_INFO));
			pDevNew->hItem = NULL;
			pDevNew->uiInterTalkID  = -1;
		}
		else
		{
			AddLog(LOG_TYPE_MSG,"","AddDevice(%d) Can not add device",iLogonID);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,pDevLogon->cIP,"NetClient_LogonEx(%s,%s,,,%s,,)",pDevLogon->cProxy,pDevLogon->cIP,pDevLogon->cID);
	}

	*pResult = 0;
}

void CLS_NetAdminPage::UI_UpdateDialog()
{
	InsertColumn(m_lvServer,0,IDS_MNG_ADMIN_MAC,LVCFMT_LEFT,120);
	InsertColumn(m_lvServer,1,IDS_MNG_ADMIN_IP,LVCFMT_LEFT,90);
	InsertColumn(m_lvServer,2,IDS_MNG_ADMIN_MASK,LVCFMT_LEFT,90);
	InsertColumn(m_lvServer,3,IDS_MNG_ADMIN_GATEWAY,LVCFMT_LEFT,90);
	InsertColumn(m_lvServer,4,IDS_MNG_ADMIN_DNS,LVCFMT_LEFT,90);
	InsertColumn(m_lvServer,5,IDS_MNG_ADMIN_CHANNEL_NUM,LVCFMT_LEFT,80);
	InsertColumn(m_lvServer,6,IDS_MNG_ADMIN_SERVER_PORT,LVCFMT_LEFT,80);
	InsertColumn(m_lvServer,7,IDS_MNG_ADMIN_CLIENT_PORT,LVCFMT_LEFT,80);
	InsertColumn(m_lvServer,8,IDS_MNG_ADMIN_DEVICE_TYPE,LVCFMT_LEFT,80);
	InsertColumn(m_lvServer,9,IDS_MNG_ADMIN_HTTP_PORT,LVCFMT_LEFT,80);
	InsertColumn(m_lvServer,10,IDS_MNG_ADMIN_PRODUCT_MODEL,LVCFMT_LEFT,120);
	InsertColumn(m_lvServer,11,IDS_MNG_ADMIN_FACTORY_ID,LVCFMT_LEFT,160);
	InsertColumn(m_lvServer,12,IDS_MNG_ADMIN_KERNEL_VERSION,LVCFMT_LEFT,160);
	InsertColumn(m_lvServer,13,IDS_MNG_ADMIN_OCX_VERSION,LVCFMT_LEFT,90);

	InsertString(m_cboInterface,0,IDS_MNG_ADMIN_AUTO);
	InsertString(m_cboDeviceType,0,IDS_MNG_ADMIN_ALL);

	SetDlgItemTextEx(IDC_STATIC_INTERFACE,IDS_MNG_ADMIN_INTERFACE);
	SetDlgItemTextEx(IDC_STATIC_DEVICE_TYPE,IDS_MNG_ADMIN_DEVICE_TYPE);
	SetDlgItemTextEx(IDC_BTN_REFRESH,IDS_MNG_ADMIN_REFRESH);
}

void CLS_NetAdminPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}