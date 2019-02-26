// ls_ItsStateQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsStateQuery.h"

#define  ABS_SECOND_START_YEAR		1900
#define  ABS_SECOND_START_MONTH		1
#define  LOOP_STATUS_EMPTY			0				//线圈触发状态-空
#define  LOOP_STATUS_ENTER			1				//线圈触发状态-进入
#define  LOOP_STATUS_LEAVE			2				//线圈触发转台-离开


void SecondsToNvsFileTime( NVS_FILE_TIME* _fileTime,long _tTime )
{
	time_t ltime = (time_t)_tTime;
	struct tm pTime = {0};
	gmtime_s(&pTime, &ltime);
	_fileTime->iYear = pTime.tm_year + ABS_SECOND_START_YEAR;
	_fileTime->iMonth = pTime.tm_mon + ABS_SECOND_START_MONTH;
	_fileTime->iDay = pTime.tm_mday;
	_fileTime->iHour = pTime.tm_hour;
	_fileTime->iMinute = pTime.tm_min;
	_fileTime->iSecond = pTime.tm_sec;
}

IMPLEMENT_DYNAMIC(Cls_ItsStateQuery, CDialog)

Cls_ItsStateQuery::Cls_ItsStateQuery(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsStateQuery::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

Cls_ItsStateQuery::~Cls_ItsStateQuery()
{
}

void Cls_ItsStateQuery::OnChannelChanged( int _iLogonID,int _iChannelNo, int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
}

void Cls_ItsStateQuery::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}
void Cls_ItsStateQuery::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_GP_STATIS, IDS_ITS_STATE_QUERY);
	SetDlgItemTextEx(IDC_GP_CAMERA_STATIS, IDS_ITS_CAMERA_STATUS);
	SetDlgItemTextEx(IDC_STC_LABLE_CAMERA_TEM, IDS_ITS_CAMERA_TEMPERTURE);
	SetDlgItemTextEx(IDC_GP_TEST_STATIS, IDS_ITS_SIGNAL_STATUS);
	SetDlgItemTextEx(IDC_STC_LABLE_SIGNAL_STATIS, IDS_ITS_SIGNAL_STATUS);
	SetDlgItemTextEx(IDC_GP_CAR_TEST_STATIS, IDS_ITS_QUERY_STATUS);
	SetDlgItemTextEx(IDC_STC_CAR_STATIS, IDS_ITS_QUERY_STATUS);
	SetDlgItemTextEx(IDC_STC_ROLL_STATIS, IDS_ITS_LOOP_STATUS);
	SetDlgItemTextEx(IDC_BTN_UPDATE_CAMTEM, IDS_CFG_LOG_NVS_REFRESH);
	SetDlgItemTextEx(IDC_BTN_UPDATE_CAR_STATIS, IDS_CFG_LOG_NVS_REFRESH);
	SetDlgItemTextEx(IDC_BTN_UPDATE_ROLL, IDS_CFG_LOG_NVS_REFRESH);
	SetDlgItemTextEx(IDC_BTN_UPDATE_SIGSTA, IDS_CFG_LOG_NVS_REFRESH);
	SetDlgItemTextEx(IDC_GPO_PIC_QUITY, IDS_CONFIG_FTP_QVALUE);
	SetDlgItemTextEx(IDC_STC_PIC_QUITY, IDS_CONFIG_ECOP_BRIGHTEN);
	SetDlgItemTextEx(IDC_BTN_PIC_QUITY, IDS_CFG_LOG_NVS_REFRESH);
	SetDlgItemTextEx(IDC_GPO_RED_LIGHT, IDS_RED_LIGHT_SYNC);
	SetDlgItemTextEx(IDC_STC_RED_LIGHT, IDS_RED_LIGHT_SYNC);
	SetDlgItemTextEx(IDC_BTN_RED_LIGHT, IDS_CFG_LOG_NVS_REFRESH);

	SetDlgItemTextEx(IDC_GPO_SHOW_LOOP_MSG, IDS_ITS_LOOP_STATE_UPLOAD);
	SetDlgItemTextEx(IDC_STC_SHOW_LOOP_MSG, IDS_LOOP_NO);
	SetDlgItemTextEx(IDC_BTN_SHOW_LOOP_MSG, IDS_CFG_LOG_NVS_REFRESH);

}

void Cls_ItsStateQuery::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GP_STATIS, m_gpStatis);
	DDX_Control(pDX, IDC_GP_CAMERA_STATIS, m_gpCameraStatis);
	DDX_Control(pDX, IDC_GP_TEST_STATIS, m_gpSignalStatis);
	DDX_Control(pDX, IDC_GP_CAR_TEST_STATIS, m_gpCarStatis);
	DDX_Control(pDX, IDC_STC_LABLE_CAMERA_TEM, m_stcCameraTem);
	DDX_Control(pDX, IDC_STC_VALUE, m_stcTemValue);
	DDX_Control(pDX, IDC_STC_LABLE_SIGNAL_STATIS, m_stcSignalStatis);
	DDX_Control(pDX, IDC_STC_SIGNAL_VALUE, m_stcSignalValue);
	DDX_Control(pDX, IDC_BTN_UPDATE_SIGSTA, m_btnUpdateSigSta);
	DDX_Control(pDX, IDC_BTN_UPDATE_CAMTEM, m_btnUpdateCamTem);
	DDX_Control(pDX, IDC_STC_CAR_STATIS, m_stcCarStatis);
	DDX_Control(pDX, IDC_STC_CAR_STATIS_VALUE, m_stcCarStaValue);
	DDX_Control(pDX, IDC_STC_ROLL_STATIS, m_stcRollStatis);
	DDX_Control(pDX, IDC_EDT_ROLL_VALUE, m_edtRollValue);
	DDX_Control(pDX, IDC_BTN_UPDATE_CAR_STATIS, m_btnUpdateCarSta);
	DDX_Control(pDX, IDC_BTN_UPDATE_ROLL, m_btnUpdateRoll);
	DDX_Control(pDX, IDC_LIST_RED_LIGHT, m_listRedLightSync);
	DDX_Control(pDX, IDC_LIST_SHOW_LOOP_MSG, m_listLoopTriggerMsg);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG1, m_chkLoopSerialNum[0]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG2, m_chkLoopSerialNum[1]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG3, m_chkLoopSerialNum[2]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG4, m_chkLoopSerialNum[3]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG5, m_chkLoopSerialNum[4]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG6, m_chkLoopSerialNum[5]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG7, m_chkLoopSerialNum[6]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG8, m_chkLoopSerialNum[7]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG9, m_chkLoopSerialNum[8]);
	DDX_Control(pDX, IDC_CHK_LOOP_MSG10, m_chkLoopSerialNum[9]);

}


BEGIN_MESSAGE_MAP(Cls_ItsStateQuery, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON1, &Cls_ItsStateQuery::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_UPDATE_CAMTEM, &Cls_ItsStateQuery::OnBnClickedBtnUpdateCamtem)
	ON_BN_CLICKED(IDC_BTN_UPDATE_SIGSTA, &Cls_ItsStateQuery::OnBnClickedBtnUpdateSigsta)
	ON_BN_CLICKED(IDC_BTN_UPDATE_CAR_STATIS, &Cls_ItsStateQuery::OnBnClickedBtnUpdateCarStatis)
	ON_BN_CLICKED(IDC_BTN_UPDATE_ROLL, &Cls_ItsStateQuery::OnBnClickedBtnUpdateRoll)
	ON_BN_CLICKED(IDC_BTN_PIC_QUITY, &Cls_ItsStateQuery::OnBnClickedBtnPicQuity)
	ON_BN_CLICKED(IDC_BTN_RED_LIGHT, &Cls_ItsStateQuery::OnBnClickedBtnRedLight)
	ON_BN_CLICKED(IDC_BTN_SHOW_LOOP_MSG, &Cls_ItsStateQuery::OnBnClickedBtnShowLoopMsg)
END_MESSAGE_MAP()


// Cls_ItsStateQuery 消息处理程序

BOOL Cls_ItsStateQuery::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Cls_ItsStateQuery::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Cls_ItsStateQuery::OnBnClickedBtnUpdateCamtem()
{
	int iRet = NetClient_QueryDevStatus(m_iLogonID, ITS_TEMPRETURE);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_QueryDevStatus[TEMPRETURE](%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_QueryDevStatus[TEMPRETURE] (%d),error(%d)",m_iLogonID, GetLastError());
	}
}

void Cls_ItsStateQuery::OnBnClickedBtnUpdateSigsta()
{
	int iRet = NetClient_QueryDevStatus(m_iLogonID, ITS_SIGNAL_CHECK);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[SIGNAL](%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[SIGNAL] (%d),error(%d)",m_iLogonID, GetLastError());
	}
}

void Cls_ItsStateQuery::OnBnClickedBtnUpdateCarStatis()
{
	int iRet = NetClient_QueryDevStatus(m_iLogonID, ITS_CAR_CHECK);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_QueryDevStatus[QUERY](%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_QueryDevStatus[QUERY] (%d),error(%d)",m_iLogonID, GetLastError());
	}
}

void Cls_ItsStateQuery::OnBnClickedBtnUpdateRoll()
{
	int iRet = NetClient_QueryDevStatus(m_iLogonID, ITS_LOOP);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_QueryDevStatus[LOOP](%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_QueryDevStatus[LOOP] (%d),error(%d)",m_iLogonID, GetLastError());
	}
}

void Cls_ItsStateQuery::SetState(int _ID, int iState)
{
	if (ITS_ONLINE == iState)
	{
		SetDlgItemText(_ID, GetTextEx(IDS_ITS_ONLINE));
	}
	else if (ITS_OFFLINE == iState)
	{
		SetDlgItemText(_ID, GetTextEx(IDS_ITS_OFFLINE));
	}
	else
	{
		SetDlgItemText(_ID, GetTextEx(IDS_ITS_ERR));
	}
}

void Cls_ItsStateQuery::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (_ulLogonID != m_iLogonID)
	{
		return;
	}
	int iMsgType = _iWparam;
	switch (iMsgType)
	{
	case WCM_ITS_LOOPTRIGSTATE:
		{
			int iLoopId = (int)_iLParam;
			UI_UpdateLoopTriggerMsg(iLoopId);
		}
		break;
	default:
		break;
	}
}

void Cls_ItsStateQuery::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_DEVSTATUS:
		{
			//STR_DevStatus tStatis = {0};
			//NetClient_GetDevStatus(m_iLogonID, &tStatis, sizeof(STR_DevStatus));
			STR_Para* ptStrPara = (STR_Para*)_pPara; 
			int iType = (int)ptStrPara->m_iPara[0];
			int iStatus[MAX_DEVSTATUS_NUM] = {-1};
			iStatus[0] = (int)ptStrPara->m_iPara[1];
			switch (iType)
			{
				case ITS_CAR_CHECK :
					{
						SetState(IDC_STC_CAR_CHECK, iStatus[0]);
					}
					break;
				case ITS_LOOP:
					{
						const int CONST_iRow = 2;
						const int CONST_iColumn = 8;
						int iValue = iStatus[0];
						int iLoonNum = 0;
						CString cstrTest;
						for(int i=0; i<CONST_iRow; i++)
						{
							for(int j=0; j<CONST_iColumn; j++)
							{
								if (1 == j%2) //奇数
								{
									iLoonNum += 1;
									int iState = iValue & 0x0000000f;

									CString cstrLoop;
									if (0 > iState || 2 < iState)
									{
										cstrLoop.Format("Loop%d:%s", iLoonNum, GetTextEx(IDS_ITS_OFFLINE));
										SetDlgItemText(IDC_EDT_LOOP_VALUE, cstrLoop);
									}
									else
									{
										if (ITS_ONLINE == iState)
										{
											cstrLoop.Format("Loop%d:%s", iLoonNum, GetTextEx(IDS_ITS_ONLINE));
										}
										else if (ITS_OFFLINE == iState)
										{
											cstrLoop.Format("Loop%d:%s", iLoonNum, GetTextEx(IDS_ITS_OFFLINE));
										}
										else
										{
											cstrLoop.Format("Loop%d:%s", iLoonNum, GetTextEx(IDS_ITS_ERR));
										}
									}
									cstrTest += cstrLoop;
									iValue = (iValue & 0xfffffff0) >> 4;
								}
							}
						}
						SetDlgItemText(IDC_EDT_LOOP_VALUE, cstrTest);
					}
					break;
				case ITS_TEMPRETURE :
					{
						float fTemp = 0.0;
						fTemp = (float)(iStatus[0] - 1000)/10;
						CString cstrTemp;
						cstrTemp.Format("%.1f℃", fTemp);
						SetDlgItemText(IDC_STC_CAMTEM, cstrTemp);
					}
					break;
				case ITS_SIGNAL_CHECK :
					{
						SetState(IDC_STC_SIGNAL_CHECK, iStatus[0]);
					}
					break;
				case ITS_DEVICE_TYPE_IMAGE_LIGHTNESS :
					{
						SetDlgItemInt(IDC_EDT_PIC_QUITY, iStatus[0]);
					}
					break;
				case ITS_DEVICE_TYPE_RED_SYN :
					{
						m_listRedLightSync.ResetContent();
						for(int i = 1; i < ITS_RED_LIGHT_NUM_MAX; i++)
						{
							CString cstrRedLightStat = (ITS_SYNC_TRUE == iStatus[i]) ? GetTextEx(IDS_SYNC) :  GetTextEx(IDS_SYNC_UN);
							CString cstrRedLightMsg;
							cstrRedLightMsg.Format("RedLight%d:", i);
							cstrRedLightMsg += cstrRedLightStat;
							m_listRedLightSync.AddString(cstrRedLightMsg);
						}
					}
					break;
				default:
					{
						AddLog(LOG_TYPE_FAIL,"","PARA_DEVSTATUS Not Exist");
					}
					break;
			}
		}
		break;
	default:
		break;
	}
}

void Cls_ItsStateQuery::OnBnClickedBtnPicQuity()
{
	int iRet = NetClient_QueryDevStatus(m_iLogonID, ITS_DEVICE_TYPE_IMAGE_LIGHTNESS);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_QueryDevStatus[IMAGE](%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_QueryDevStatus[IMAGE] (%d),error(%d)",m_iLogonID, GetLastError());
	}
}

void Cls_ItsStateQuery::OnBnClickedBtnRedLight()
{
	int iRet = NetClient_QueryDevStatus(m_iLogonID, ITS_DEVICE_TYPE_RED_SYN);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_QueryDevStatus[RedLight](%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_QueryDevStatus[RedLight] (%d),error(%d)",m_iLogonID, GetLastError());
	}
}

void Cls_ItsStateQuery::OnBnClickedBtnShowLoopMsg()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	if (m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid ChannelNo(%d)", m_iChannelNo);
		return;
	}

	m_listLoopTriggerMsg.ResetContent();

	for (int iLoopIndex = 0; iLoopIndex < MAX_ITS_LOOP_NUM; iLoopIndex++)
	{
		if (!m_chkLoopSerialNum[iLoopIndex].GetCheck())
		{
			continue;
		}

		UI_UpdateLoopTriggerMsg(iLoopIndex);
	}
}

void Cls_ItsStateQuery::UI_UpdateLoopTriggerMsg(int iLoopId)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	if (m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid ChannelNo(%d)", m_iChannelNo);
		return;
	}

	int iCmd = ITS_EXTRAINFO_CMD_LOOPTRIGSTATE;
	ItsLoopTrigState tItsLoopTrigState = {0};
	tItsLoopTrigState.iSize = sizeof(ItsLoopTrigState);
	tItsLoopTrigState.iLoopID = iLoopId;

	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, iCmd, m_iChannelNo, (void*)&tItsLoopTrigState, sizeof(ItsLoopTrigState));

	if (0 > iRet || 0 == tItsLoopTrigState.iSize)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[LoopTrigger](%d,%d)", m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[LoopTrigger](%d,%d)", m_iLogonID, m_iChannelNo);
		//线圈状态
		CString cstrLoopState;
		switch (tItsLoopTrigState.iTrigState)
		{
		case LOOP_STATUS_EMPTY:
			cstrLoopState = GetTextEx(IDS_CFG_COM_PARITY_NONE);
			break;
		case LOOP_STATUS_ENTER:
			cstrLoopState = GetTextEx(IDS_VCA_ENTER);
			break;
		case LOOP_STATUS_LEAVE:
			cstrLoopState = GetTextEx(IDS_VCA_LEAVE);
			break;
		default:
			cstrLoopState = GetTextEx(IDS_ITS_ERR);
			break;
		}
		//显示线圈触发时间
		CString cstrTime;
		NVS_FILE_TIME tTime = {0}; 
		SecondsToNvsFileTime(&tTime, tItsLoopTrigState.iTrigTime);
		cstrTime.Format("%04d-%02d-%02d-%02d-%02d-%02d", tTime.iYear, tTime.iMonth, tTime.iDay, tTime.iHour, tTime.iMinute, tTime.iSecond);

		CString cstrLoopTriggerMsg;
		cstrLoopTriggerMsg.Format("-Loop(%d)-", iLoopId + 1);
		cstrLoopTriggerMsg = cstrTime + cstrLoopTriggerMsg + cstrLoopState;
		m_listLoopTriggerMsg.InsertString(0, cstrLoopTriggerMsg);
	}
}
