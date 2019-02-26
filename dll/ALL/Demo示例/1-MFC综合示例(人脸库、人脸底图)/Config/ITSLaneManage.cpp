// ITSLaneManage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ITSLaneManage.h"

#define MSG_TYPE_ADD_CROSS		1
#define MSG_TYPE_DELETE_CROSS	2
#define MSG_TYPE_MODIFY_CROSS	3
#define MSG_TYPE_ADD_LANE		4
#define MSG_TYPE_DELETE_LANE	5
#define MSG_TYPE_MODIFY_LANE	6

// CLS_ITSLaneManage dialog

IMPLEMENT_DYNAMIC(CLS_ITSLaneManage, CDialog)

CLS_ITSLaneManage::CLS_ITSLaneManage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSLaneManage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	memset(m_tItsCross, 0, MAX_ITS_CROSS_COUNT * sizeof(ITSCrossInfo));
	memset(m_tItsLane, 0, MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT * sizeof(ITSLaneInfo));
}

CLS_ITSLaneManage::~CLS_ITSLaneManage()
{
}

void CLS_ITSLaneManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ITS_CROSS, m_cboItsCross);
	DDX_Control(pDX, IDC_EDIT_ITS_CROSS_NUMBER, m_edtItsCrossNumber);
	DDX_Control(pDX, IDC_EDIT_ITS_CROSS_NAME, m_edtItsCrossName);
	DDX_Control(pDX, IDC_COMBO_ITS_LANE, m_cboItsLane);
	DDX_Control(pDX, IDC_EDIT_ITS_LANE_NUMBER, m_edtItsLaneNumber);
	DDX_Control(pDX, IDC_EDIT_ITS_LANE_NAME, m_edtItsLaneName);
	DDX_Control(pDX, IDC_COMBO_ITS_LANE_CROSS, m_cboItsCrossByLane);
	DDX_Control(pDX, IDC_COMBO_ITS_TRAVEL_DIRECTION, m_cboItsTravelDirection);
	DDX_Control(pDX, IDC_COMBO_ITS_LANE_TYPE, m_cboItsLaneType);
	DDX_Control(pDX, IDC_EDIT_ITS_CAMERA_NUMBER, m_edtItsCameraNumber);
	DDX_Control(pDX, IDC_EDIT_ITS_CHECK_REGION, m_edtItsCheckRegion);
}


BEGIN_MESSAGE_MAP(CLS_ITSLaneManage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ITS_ADD_CROSS, &CLS_ITSLaneManage::OnBnClickedButtonItsAddCross)
	ON_BN_CLICKED(IDC_BUTTON_ITS_DELETE_CROSS, &CLS_ITSLaneManage::OnBnClickedButtonItsDeleteCross)
	ON_BN_CLICKED(IDC_BUTTON_ITS_MODIFY_CROSS, &CLS_ITSLaneManage::OnBnClickedButtonItsModifyCross)
	ON_BN_CLICKED(IDC_BUTTON_ITS_ADD_LANE, &CLS_ITSLaneManage::OnBnClickedButtonItsAddLane)
	ON_BN_CLICKED(IDC_BUTTON_ITS_DELETE_LANE, &CLS_ITSLaneManage::OnBnClickedButtonItsDeleteLane)
	ON_BN_CLICKED(IDC_BUTTON_ITS_MODIFY_LANE, &CLS_ITSLaneManage::OnBnClickedButtonItsModifyLane)
	ON_CBN_SELCHANGE(IDC_COMBO_ITS_CROSS, &CLS_ITSLaneManage::OnCbnSelchangeComboItsCross)
	ON_CBN_SELCHANGE(IDC_COMBO_ITS_LANE, &CLS_ITSLaneManage::OnCbnSelchangeComboItsLane)
END_MESSAGE_MAP()


// CLS_ITSLaneManage message handlers

BOOL CLS_ITSLaneManage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtItsCrossNumber.SetLimitText(LEN_64);
	m_edtItsCrossName.SetLimitText(LEN_64);
	m_edtItsLaneNumber.SetLimitText(LEN_32);
	m_edtItsLaneName.SetLimitText(LEN_64);
	m_edtItsCameraNumber.SetLimitText(LEN_64);
	m_edtItsCheckRegion.SetLimitText(LEN_64);

	UI_UpdateDialogText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_ITSLaneManage::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;

	UI_UpdateCrossInfo();
	UI_UpdateLaneInfo();
}

void CLS_ITSLaneManage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialogText();
}

void CLS_ITSLaneManage::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_ITS_CROSS, IDS_ITS_STAR_NVR_CROSS);
	SetDlgItemTextEx(IDC_STATIC_ITS_CROSS_NUMBER, IDS_CONFIG_ITS_OSD_ROADNO);
	SetDlgItemTextEx(IDC_STATIC_ITS_CROSS_NAME, IDS_ITS_OROADNAME);
	SetDlgItemTextEx(IDC_BUTTON_ITS_ADD_CROSS, IDS_ADD);
	SetDlgItemTextEx(IDC_BUTTON_ITS_DELETE_CROSS, IDS_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_ITS_MODIFY_CROSS, IDS_MODIFY);
	SetDlgItemTextEx(IDC_STATIC_ITS_LANE, IDS_ITS_STAR_NVR_LANE);
	SetDlgItemTextEx(IDC_STATIC_ITS_LANE_NUMBER, IDS_CONFIG_ITS_ROADWAY_ROADWAYNO);
	SetDlgItemTextEx(IDC_STATIC_ITS_LANE_NAME, IDS_CONFIG_ITS_ROADWAY_ROADWAYNAME);
	SetDlgItemTextEx(IDC_STATIC_ITS_LANE_CROSS, IDS_ROAD_ID);
	SetDlgItemTextEx(IDC_STATIC_ITS_TRAVEL_DIRECTION, IDS_ITS_STAR_NVR_TRAVEL_DIRECTION);
	SetDlgItemTextEx(IDC_STATIC_ITS_LANE_TYPE, IDS_ITS_TYPE);
	SetDlgItemTextEx(IDC_STATIC_ITS_CAMERA_NUMBER, IDS_ITS_STAR_NVR_CAMERA_NUMBER);
	SetDlgItemTextEx(IDC_STATIC_ITS_CHECK_REGION, IDS_ITS_STAR_NVR_CHECK_REGION);
	SetDlgItemTextEx(IDC_BUTTON_ITS_ADD_LANE, IDS_ADD);
	SetDlgItemTextEx(IDC_BUTTON_ITS_DELETE_LANE, IDS_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_ITS_MODIFY_LANE, IDS_MODIFY);

	InsertString(m_cboItsTravelDirection, 0, IDS_ITS_STAR_NVR_EAST_TO_WEST);
	InsertString(m_cboItsTravelDirection, 1, IDS_ITS_STAR_NVR_WEST_TO_EAST);
	InsertString(m_cboItsTravelDirection, 2, IDS_ITS_STAR_NVR_SOUTH_TO_NORTH);
	InsertString(m_cboItsTravelDirection, 3, IDS_ITS_STAR_NVR_NORTH_TO_SOUTH);
	InsertString(m_cboItsTravelDirection, 4, IDS_ITS_STAR_NVR_COME_IN);
	InsertString(m_cboItsTravelDirection, 5, IDS_ITS_STAR_NVR_GO_AWAY);

	InsertString(m_cboItsLaneType, 0, IDS_ITS_NORMALROADWAY);
	InsertString(m_cboItsLaneType, 1, IDS_ITS_NOT_CAR_ROADWAY);
	InsertString(m_cboItsLaneType, 2, IDS_ITS_BUS_ROADWAY);
	InsertString(m_cboItsLaneType, 3, IDS_ITS_SMALLCAR_ROADWAY);
	InsertString(m_cboItsLaneType, 4, IDS_ITS_ROADWAY_EMERGENCY2);
	InsertString(m_cboItsLaneType, 5, IDS_ITS_ROADWAY_SINGAL);
}

void CLS_ITSLaneManage::OnMainNotify(int _iLogonID, int _iWparam, void* _iLParam, void* _iUser)
{
	
}

void CLS_ITSLaneManage::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	int* piResult = (int*)_pPara; 
	switch(_iParaType)
	{
	case PARA_ITS_ADDCROSS:
		{

			ShowMsgToUser(MSG_TYPE_ADD_CROSS, *piResult);
			UI_UpdateCrossInfo(MSG_TYPE_ADD_CROSS);
		}
		break;
	case PARA_ITS_DELETECROSS:
		{
			ShowMsgToUser(MSG_TYPE_DELETE_CROSS, *piResult);
			UI_UpdateCrossInfo(MSG_TYPE_DELETE_CROSS);
		}
		break;
	case PARA_ITS_MODIFYCROSS:
		{
			ShowMsgToUser(MSG_TYPE_MODIFY_CROSS, *piResult);
			UI_UpdateCrossInfo(MSG_TYPE_MODIFY_CROSS);
		}
		break;
	case PARA_ITS_ADDLANE:
		{
			ShowMsgToUser(MSG_TYPE_ADD_LANE, *piResult);
			UI_UpdateLaneInfo(MSG_TYPE_ADD_LANE);
		}
		break;
	case PARA_ITS_DELETELANE:
		{
			ShowMsgToUser(MSG_TYPE_DELETE_LANE, *piResult);
			UI_UpdateLaneInfo(MSG_TYPE_DELETE_LANE);
		}
		break;
	case PARA_ITS_MODIFYLANE:
		{
			ShowMsgToUser(MSG_TYPE_MODIFY_LANE, *piResult);
			UI_UpdateLaneInfo(MSG_TYPE_MODIFY_LANE);
		}
		break;
	default:
		break;
	}
}

void CLS_ITSLaneManage::ShowMsgToUser(int _iMsgType, int _iResult)
{
	switch (_iMsgType)
	{
	case MSG_TYPE_ADD_CROSS:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Add cross success!", "", MB_OK|MB_TOPMOST);
			else
				MessageBox("Add cross faied!", "", MB_OK|MB_TOPMOST);
		}
		break;
	case MSG_TYPE_DELETE_CROSS:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Delete cross success!", "", MB_OK|MB_TOPMOST);
			else
				MessageBox("Delete cross faied!", "", MB_OK|MB_TOPMOST);
		}
		break;
	case MSG_TYPE_MODIFY_CROSS:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Modify cross success!", "", MB_OK|MB_TOPMOST);
			else
				MessageBox("Modify cross faied!", "", MB_OK|MB_TOPMOST);
		}
		break;
	case MSG_TYPE_ADD_LANE:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Add Lane success!", "", MB_OK|MB_TOPMOST);
			else
				MessageBox("Add Lane faied!", "", MB_OK|MB_TOPMOST);
		}
		break;
	case MSG_TYPE_DELETE_LANE:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Delete lane success!", "", MB_OK|MB_TOPMOST);
			else
				MessageBox("Delete lane faied!", "", MB_OK|MB_TOPMOST);
		}
		break;
	case MSG_TYPE_MODIFY_LANE:
		{
			if (RET_SUCCESS == _iResult)
				MessageBox("Modify lane success!", "", MB_OK|MB_TOPMOST);
			else
				MessageBox("Modify lane faied!", "", MB_OK|MB_TOPMOST);
		}
		break;
	default:
		break;
	}
}

void CLS_ITSLaneManage::UI_UpdateCrossInfo(int _iMsgType)
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
		m_cboItsCross.ResetContent();
		m_cboItsCrossByLane.ResetContent();
		for (int i = 0; i < iCrossCount; ++i)
		{
			m_cboItsCross.AddString(m_tItsCross[i].cCrossNumber);
			m_cboItsCrossByLane.AddString(m_tItsCross[i].cCrossNumber);
		}

		if (MSG_TYPE_MODIFY_CROSS != _iMsgType)
		{
			m_cboItsCross.SetCurSel(0);
			m_edtItsCrossNumber.SetWindowText(m_tItsCross[0].cCrossNumber);
			m_edtItsCrossName.SetWindowText(m_tItsCross[0].cCrossName);
		}
		
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO] (%d, %d)", m_iLogonID, m_iChannelNo);
	}

END:
	return;
}

int CLS_ITSLaneManage::GetIndexByNumber(CComboBox &_cboComboBox, CString _cstrNumber)
{
	int iCount = _cboComboBox.GetCount();
	int iIndex = 0;
	for (; iIndex < iCount; ++iIndex)
	{
		CString cstrTmp;
		_cboComboBox.GetLBText(iIndex, cstrTmp);
		if (_cstrNumber = cstrTmp)
		{
			break;
		}
	}

	return iIndex;
}

void CLS_ITSLaneManage::UI_UpdateLaneInfo(int _iMsgType)
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
		m_cboItsLane.ResetContent();
		CString cLaneID;
		for (int i = 0; i < iLaneCount; ++i)
		{
			cLaneID.Format("%d", m_tItsLane[i].iLaneID);
			m_cboItsLane.InsertString(i, cLaneID);
			m_cboItsLane.SetItemData(i, m_tItsLane[i].iLaneID);
		}

		if (MSG_TYPE_MODIFY_LANE != _iMsgType)
		{
			m_cboItsLane.SetCurSel(0);
			SetDlgItemInt(IDC_EDIT_ITS_LANE_NUMBER, m_tItsLane[0].iLaneID);
			m_edtItsLaneName.SetWindowText(m_tItsLane[0].cLaneName);
			int iIndex = GetIndexByNumber(m_cboItsCrossByLane, m_tItsLane[0].cCrossNumber);
			m_cboItsCrossByLane.SetCurSel(iIndex);
			m_cboItsTravelDirection.SetCurSel(m_tItsLane[0].iDirection);
			m_cboItsLaneType.SetCurSel(m_tItsLane[0].iType);
			SetDlgItemInt(IDC_EDIT_ITS_CHECK_REGION, m_tItsLane[0].iRegionID);
		}
		
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO] (%d, %d)", m_iLogonID, m_iChannelNo);
	}

END:
	return;
}

void CLS_ITSLaneManage::OnBnClickedButtonItsAddCross()
{
	CString cstrCrossNumber;
	CString cstrCrossName;
	m_edtItsCrossNumber.GetWindowText(cstrCrossNumber);
	m_edtItsCrossName.GetWindowText(cstrCrossName);

	bool blExit = false;
	ITSCrossInfo tItsCrossInfo = {0};
	int iCount = m_cboItsCross.GetCount();
	for (int i = 0; i < iCount; ++i)
	{
		CString cstrTmpCrossNumber;
		m_cboItsCross.GetLBText(i, cstrTmpCrossNumber);
		if (cstrCrossNumber == cstrTmpCrossNumber)
		{
			blExit = true;
			break;
		}
	}

	if (blExit)
	{
		MessageBox("This cross already exit!", "", MB_OK|MB_TOPMOST);
		goto END;
	}

	tItsCrossInfo.iSize = sizeof(ITSCrossInfo);
	tItsCrossInfo.iOpt = ITS_CROSS_OPT_ADD;
	strncpy(tItsCrossInfo.cCrossNumber, cstrCrossNumber, cstrCrossNumber.GetLength());
	strncpy(tItsCrossInfo.cCrossName, cstrCrossName, cstrCrossName.GetLength());
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CROSSINFO, m_iChannelNo, &tItsCrossInfo, sizeof(ITSCrossInfo));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO][ITS_CROSS_OPT_ADD] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO][ITS_CROSS_OPT_ADD] (%d, %d)", m_iLogonID, m_iChannelNo);
	}

END:
	return;
}

void CLS_ITSLaneManage::OnBnClickedButtonItsDeleteCross()
{
	CString cstrCrossNumber;
	CString cstrCrossName;
	m_cboItsCross.GetWindowText(cstrCrossNumber);
	m_edtItsCrossName.GetWindowText(cstrCrossName);

	ITSCrossInfo tItsCrossInfo = {0};
	tItsCrossInfo.iSize = sizeof(ITSCrossInfo);
	tItsCrossInfo.iOpt = ITS_CROSS_OPT_DELETE;
	int iIndex = GetCrossIndexByCrossNumber(cstrCrossNumber);
	if (iIndex >= 0 && iIndex < MAX_ITS_CROSS_COUNT)
	{
		tItsCrossInfo.iOrderId = m_tItsCross[iIndex].iOrderId;
	}
	strncpy(tItsCrossInfo.cCrossNumber, cstrCrossNumber, cstrCrossNumber.GetLength());
	strncpy(tItsCrossInfo.cCrossName, cstrCrossName, cstrCrossName.GetLength());
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CROSSINFO, m_iChannelNo, &tItsCrossInfo, sizeof(ITSCrossInfo));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO][ITS_CROSS_OPT_DELETE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO][ITS_CROSS_OPT_DELETE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSLaneManage::OnBnClickedButtonItsModifyCross()
{
	CString cstrCrossNumber;
	CString cstrCrossName;
	m_edtItsCrossNumber.GetWindowText(cstrCrossNumber);
	m_edtItsCrossName.GetWindowText(cstrCrossName);

	ITSCrossInfo tItsCrossInfo = {0};
	tItsCrossInfo.iSize = sizeof(ITSCrossInfo);
	tItsCrossInfo.iOpt = ITS_CROSS_OPT_MODIFY;
	int iIndex = GetCrossIndexByCrossNumber(cstrCrossNumber);
	if (iIndex >= 0 && iIndex < MAX_ITS_CROSS_COUNT)
	{
		tItsCrossInfo.iOrderId = m_tItsCross[iIndex].iOrderId;
	}
	strncpy(tItsCrossInfo.cCrossNumber, cstrCrossNumber, cstrCrossNumber.GetLength());
	strncpy(tItsCrossInfo.cCrossName, cstrCrossName, cstrCrossName.GetLength());
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_CROSSINFO, m_iChannelNo, &tItsCrossInfo, sizeof(ITSCrossInfo));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO][ITS_CROSS_OPT_MODIFY] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_CROSSINFO][ITS_CROSS_OPT_MODIFY] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSLaneManage::OnBnClickedButtonItsAddLane()
{
	int iLaneID = GetDlgItemInt(IDC_EDIT_ITS_LANE_NUMBER);
	CString cstrLaneName;
	m_edtItsLaneName.GetWindowText(cstrLaneName);
	CString cstrCrossNumber;
	m_cboItsCrossByLane.GetWindowText(cstrCrossNumber);
	int iDirection = m_cboItsTravelDirection.GetCurSel();
	int iLaneType = m_cboItsLaneType.GetCurSel();
	CString cstrCameraNumber;
	m_edtItsCameraNumber.GetWindowText(cstrCameraNumber);
	int iRegionID = GetDlgItemInt(IDC_EDIT_ITS_CHECK_REGION);

	ITSLaneInfo tITSLaneInfo = {0};
	bool blExit = false;
	int iCount = m_cboItsLane.GetCount();
	for (int i = 0; i < iCount; ++i)
	{
		int iTmpLaneID = (int)m_cboItsLane.GetItemData(i);
		if (iLaneID == iTmpLaneID)
		{
			blExit = true;
			break;
		}
	}

	if (blExit)
	{
		MessageBox("This lane already exit!", "", MB_OK|MB_TOPMOST);
		goto END;
	}

	tITSLaneInfo.iSize = sizeof(ITSLaneInfo);
	tITSLaneInfo.iOpt = ITS_LANE_OPT_ADD;
	strncpy(tITSLaneInfo.cCrossNumber, cstrCrossNumber, cstrCrossNumber.GetLength());
	tITSLaneInfo.iLaneID = iLaneID;
	strncpy(tITSLaneInfo.cLaneName, cstrLaneName, cstrLaneName.GetLength());
	tITSLaneInfo.iDirection = iDirection;
	tITSLaneInfo.iType = iLaneType;
	tITSLaneInfo.iRegionID = iRegionID;
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_LANEINFO, m_iChannelNo, &tITSLaneInfo, sizeof(ITSLaneInfo));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO][ITS_LANE_OPT_ADD] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO][ITS_LANE_OPT_ADD] (%d, %d)", m_iLogonID, m_iChannelNo);
	}

END:
	return;
}

void CLS_ITSLaneManage::OnBnClickedButtonItsDeleteLane()
{
	int iLaneID = (int)m_cboItsLane.GetItemData(m_cboItsLane.GetCurSel());

	CString cstrLaneName;
	m_edtItsLaneName.GetWindowText(cstrLaneName);
	CString cstrCrossNumber;
	m_cboItsCrossByLane.GetWindowText(cstrCrossNumber);
	int iDirection = m_cboItsTravelDirection.GetCurSel();
	int iLaneType = m_cboItsLaneType.GetCurSel();
	CString cstrCameraNumber;
	m_edtItsCameraNumber.GetWindowText(cstrCameraNumber);
	int iRegionID = m_edtItsCheckRegion.GetDlgItemInt(IDC_EDIT_ITS_CHECK_REGION);

	ITSLaneInfo tITSLaneInfo = {0};
	tITSLaneInfo.iSize = sizeof(ITSLaneInfo);
	tITSLaneInfo.iOpt = ITS_LANE_OPT_DELETE;
	int iIndex = GetLaneIndexByLaneID(iLaneID);
	if (iIndex >= 0 && iIndex < MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT)
	{
		tITSLaneInfo.iOrderId = m_tItsLane[iIndex].iOrderId;
	}
	strncpy(tITSLaneInfo.cCrossNumber, cstrCrossNumber, cstrCrossNumber.GetLength());
	tITSLaneInfo.iLaneID = iLaneID;
	strncpy(tITSLaneInfo.cLaneName, cstrLaneName, cstrLaneName.GetLength());
	tITSLaneInfo.iDirection = iDirection;
	tITSLaneInfo.iType = iLaneType;
	tITSLaneInfo.iRegionID = iRegionID;
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_LANEINFO, m_iChannelNo, &tITSLaneInfo, sizeof(ITSLaneInfo));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO][ITS_LANE_OPT_DELETE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO][ITS_LANE_OPT_DELETE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSLaneManage::OnBnClickedButtonItsModifyLane()
{
	int iLaneID = (int)m_cboItsLane.GetItemData(m_cboItsLane.GetCurSel());

	CString cstrLaneName;
	m_edtItsLaneName.GetWindowText(cstrLaneName);
	CString cstrCrossNumber;
	m_cboItsCrossByLane.GetWindowText(cstrCrossNumber);
	int iDirection = m_cboItsTravelDirection.GetCurSel();
	int iLaneType = m_cboItsLaneType.GetCurSel();
	CString cstrCameraNumber;
	m_edtItsCameraNumber.GetWindowText(cstrCameraNumber);
	int iRegionID = m_edtItsCheckRegion.GetDlgItemInt(IDC_EDIT_ITS_CHECK_REGION);

	ITSLaneInfo tITSLaneInfo = {0};
	tITSLaneInfo.iSize = sizeof(ITSLaneInfo);
	tITSLaneInfo.iOpt = ITS_LANE_OPT_MODIFY;
	int iIndex = GetLaneIndexByLaneID(iLaneID);
	if (iIndex >= 0 && iIndex < MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT)
	{
		tITSLaneInfo.iOrderId = m_tItsLane[iIndex].iOrderId;
	}
	strncpy(tITSLaneInfo.cCrossNumber, cstrCrossNumber, cstrCrossNumber.GetLength());
	tITSLaneInfo.iLaneID = iLaneID;
	strncpy(tITSLaneInfo.cLaneName, cstrLaneName, cstrLaneName.GetLength());
	tITSLaneInfo.iDirection = iDirection;
	tITSLaneInfo.iType = iLaneType;
	tITSLaneInfo.iRegionID = iRegionID;
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_LANEINFO, m_iChannelNo, &tITSLaneInfo, sizeof(ITSLaneInfo));
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO][ITS_LANE_OPT_MODIFY] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LANEINFO][ITS_LANE_OPT_MODIFY] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_ITSLaneManage::OnCbnSelchangeComboItsCross()
{
	int iIndex = m_cboItsCross.GetCurSel();
	if (iIndex >= 0 && iIndex < MAX_ITS_CROSS_COUNT)
	{
		m_edtItsCrossNumber.SetWindowText(m_tItsCross[iIndex].cCrossNumber);
		m_edtItsCrossName.SetWindowText(m_tItsCross[iIndex].cCrossName);
	}
}

void CLS_ITSLaneManage::OnCbnSelchangeComboItsLane()
{
	int iIndex = m_cboItsLane.GetCurSel();
	int iLaneID = (int)m_cboItsLane.GetItemData(iIndex);
	int i = 0;
	for (; i < MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT; ++i)
	{
		if (iLaneID == m_tItsLane[i].iLaneID)
		{
			break;
		}
	}

	SetDlgItemInt(IDC_EDIT_ITS_LANE_NUMBER, m_tItsLane[i].iLaneID);
	m_edtItsLaneName.SetWindowText(m_tItsLane[i].cLaneName);
	int j = GetIndexByNumber(m_cboItsCrossByLane, m_tItsLane[i].cCrossNumber);
	m_cboItsCrossByLane.SetCurSel(j);
	m_cboItsTravelDirection.SetCurSel(m_tItsLane[i].iDirection);
	m_cboItsLaneType.SetCurSel(m_tItsLane[i].iType);
	SetDlgItemInt(IDC_EDIT_ITS_CHECK_REGION, m_tItsLane[i].iRegionID);
}

int CLS_ITSLaneManage::GetCrossIndexByCrossNumber(CString _cstrCrossNumber)
{
	int iIndex = 0;
	for (; iIndex < MAX_ITS_CROSS_COUNT; ++iIndex)
	{
		if (_cstrCrossNumber == m_tItsCross[iIndex].cCrossNumber)
		{
			break;
		}
	}

	return iIndex;
}

int CLS_ITSLaneManage::GetLaneIndexByLaneID(int _iLaneID)
{
	int iIndex = 0;
	for (; iIndex < MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT; ++iIndex)
	{
		if (_iLaneID == m_tItsLane[iIndex].iLaneID)
		{
			break;
		}
	}

	return iIndex;
}
