#include "StdAfx.h"
#include "BasePage.h"

//0：单绊线 1：双绊线 2：周界检测 3：徘徊 4：停车 5：奔跑 6：区域内人员密度 7：被盗物 8：遗弃物 9：人脸识别
//10:视频诊断 11:智能跟踪 12：流量统计 13：人群聚集  14：离岗检测 15：水位监测 16：音频诊断 17：人脸遮挡(马赛克)
//18:河道漂浮物 19：盗采盗卸 20：违章停车 21：打架 22：警戒 23：车牌识别(仅NVR使用，交通前端使用的是交通协议)
//24-热度图 25-积水监测 26-翻窗检测 27-ST人脸识别 28-车位看守 30-安全帽检测算法  31-鱼球联动跟踪 32 闸门检测
//下标索引跟VCA事件ID绑定
int g_iEventIDS[VCA_EVENT_MAX] = {
	IDS_VCA_ALARM_EVENT_TRIPWIRE,		//0-单绊线
	IDS_VCA_ALARM_EVENT_DBTRIPWIRE,		//1-双绊线
	IDS_VCA_ALARM_EVENT_PERIMETER,		//2-周界检测		
	IDS_VCA_ALARM_EVENT_LOITER,			//3-徘徊		
	IDS_VCA_ALARM_EVENT_PARKING,		//4-停车	
	IDS_VCA_ALARM_EVENT_RUN,			//5-奔跑		
	IDS_VCA_ALARM_EVENT_HIGH_DENSITY,	//6-区域内人员密度	
	IDS_VCA_ALARM_EVENT_OBJSTOLEN,		//7-被盗物	
	IDS_VCA_ALARM_EVENT_ABANDUM,		//8-遗弃物	
	IDS_VCA_ALARM_EVENT_FACEREC,		//9-人脸识别
	IDS_VCA_ALARM_EVENT_VIDEODETECT,	//10-视频诊断	
	IDS_VCA_ALARM_EVENT_TRACK,			//11-智能跟踪
	IDS_VCA_EVENT_FLUX,					//12-流量统计
	IDS_VCA_EVENT_CROWD_NEW,			//13-人群聚集
	IDS_VCA_EVENT_LEAVE_DETECT,			//14-离岗检测
	IDS_CFG_FUNC_WATER_LEVEL,			//15-水位监测
	IDS_VCA_EVENT_AUDIO_DIAGNOSE_NEW,	//16-音频诊断
	IDS_CFG_FUNC_FACE_COVER,			//17-人脸遮挡
	IDS_VCA_EVENT_RIVER,				//18-河道漂浮物
	IDS_VCA_EVENT_DREDGE,				//19-盗采盗卸
	IDS_CONFIG_ITS_ILLEGALPARK,			//20-违章停车
	IDS_VCA_EVENT_FIGHT,				//21-打架
	IDS_PROTECT,						//22-警戒
	IDS_VCA_IDS_LISENCE,				//23-车牌识别
	IDS_CFG_FEC_HEAT_MAP,				//24-热度图
	IDS_CFG_SEEPER,						//25-积水监测
	IDS_WINDOW_DETECTION,				//26-翻窗检测
	IDS_VCA_EVENT_FACEREC,				//27-ST人脸识别
	IDS_CONFIG_ITS_ILLEGALPARK,			//28-车位看守
	IDS_UNKNOW_CONNECT,					//29-未知
	IDS_CFG_HELMET,						//30-安全帽检测
	IDS_CFG_LINKDOMETRACK,				//31-鱼球联动跟踪 
	IDS_VCA_SLUICEGATE,					//32-闸门检测
};

CLS_BasePage::CLS_BasePage(UINT nIDTemplate,CWnd* pParentWnd)
: CLS_BaseWindow(nIDTemplate, pParentWnd)
{
	m_iLogonID = -1;
	m_iChannelNO = 0;
	m_iStreamNO = 0;
}

CLS_BasePage::~CLS_BasePage()
{

}

void CLS_BasePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannelNO = _iChannelNo;
	m_iStreamNO = _iStreamNo;
}

CString CLS_BasePage::GetHDTemplateName(char* pTemplateName)
{
	CString cstrTamplateName;
	cstrTamplateName.Format("%s",pTemplateName);
	if (cstrTamplateName == "outdoor" && !GetTextEx(IDS_HD_MODE_OUTDOOR).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_OUTDOOR);
	}
	else if(cstrTamplateName == "indoor" && !GetTextEx(IDS_HD_MODE_INDOOR).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_INDOOR);
	}
	else if(cstrTamplateName == "motion" && !GetTextEx(IDS_HD_MODE_MOTION).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_MOTION);
	}
	else if(cstrTamplateName == "wdr" && !GetTextEx(IDS_HD_MODE_WDR).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_WDR);
	}
	else if(cstrTamplateName == "dark" && !GetTextEx(IDS_HD_MODE_DARK).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_DARK);
	}
	else if(cstrTamplateName == "bright" && !GetTextEx(IDS_HD_MODE_BRIGHT).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_BRIGHT);
	}
	else if(cstrTamplateName == "colorful" && !GetTextEx(IDS_HD_MODE_COLORFUL).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_COLORFUL);
	}
	else if(cstrTamplateName == "customized" && !GetTextEx(IDS_HD_MODE_CUSTOMIZED).IsEmpty())
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_CUSTOMIZED);
	}

	return cstrTamplateName;
}

void CLS_BasePage::GetNvsFileTime(CDateTimeCtrl* _pDt, OUT NVS_FILE_TIME &_tTime)
{
	if (NULL == _pDt)
	{
		return;
	}

	CTime ctTm;
	_pDt->GetTime(ctTm);
	_tTime.iYear = ctTm.GetYear();
	_tTime.iMonth = ctTm.GetMonth();
	_tTime.iDay = ctTm.GetDay();
	_tTime.iHour = ctTm.GetHour();
	_tTime.iMinute = ctTm.GetMinute();
	_tTime.iSecond = ctTm.GetSecond();
}

CString CLS_BasePage::GetWidgetText(int nId)
{
	CString cstrTxt;
	CWnd* pWnd = GetDlgItem(nId);
	if (NULL != pWnd)
	{
		pWnd->GetWindowText(cstrTxt);
	}
	return cstrTxt;
}