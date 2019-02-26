#include "StdAfx.h"
#include "BasePage.h"

//0�������� 1��˫���� 2���ܽ��� 3���ǻ� 4��ͣ�� 5������ 6����������Ա�ܶ� 7�������� 8�������� 9������ʶ��
//10:��Ƶ��� 11:���ܸ��� 12������ͳ�� 13����Ⱥ�ۼ�  14����ڼ�� 15��ˮλ��� 16����Ƶ��� 17�������ڵ�(������)
//18:�ӵ�Ư���� 19�����ɵ�ж 20��Υ��ͣ�� 21����� 22������ 23������ʶ��(��NVRʹ�ã���ͨǰ��ʹ�õ��ǽ�ͨЭ��)
//24-�ȶ�ͼ 25-��ˮ��� 26-������� 27-ST����ʶ�� 28-��λ���� 30-��ȫñ����㷨  31-������������ 32 բ�ż��
//�±�������VCA�¼�ID��
int g_iEventIDS[VCA_EVENT_MAX] = {
	IDS_VCA_ALARM_EVENT_TRIPWIRE,		//0-������
	IDS_VCA_ALARM_EVENT_DBTRIPWIRE,		//1-˫����
	IDS_VCA_ALARM_EVENT_PERIMETER,		//2-�ܽ���		
	IDS_VCA_ALARM_EVENT_LOITER,			//3-�ǻ�		
	IDS_VCA_ALARM_EVENT_PARKING,		//4-ͣ��	
	IDS_VCA_ALARM_EVENT_RUN,			//5-����		
	IDS_VCA_ALARM_EVENT_HIGH_DENSITY,	//6-��������Ա�ܶ�	
	IDS_VCA_ALARM_EVENT_OBJSTOLEN,		//7-������	
	IDS_VCA_ALARM_EVENT_ABANDUM,		//8-������	
	IDS_VCA_ALARM_EVENT_FACEREC,		//9-����ʶ��
	IDS_VCA_ALARM_EVENT_VIDEODETECT,	//10-��Ƶ���	
	IDS_VCA_ALARM_EVENT_TRACK,			//11-���ܸ���
	IDS_VCA_EVENT_FLUX,					//12-����ͳ��
	IDS_VCA_EVENT_CROWD_NEW,			//13-��Ⱥ�ۼ�
	IDS_VCA_EVENT_LEAVE_DETECT,			//14-��ڼ��
	IDS_CFG_FUNC_WATER_LEVEL,			//15-ˮλ���
	IDS_VCA_EVENT_AUDIO_DIAGNOSE_NEW,	//16-��Ƶ���
	IDS_CFG_FUNC_FACE_COVER,			//17-�����ڵ�
	IDS_VCA_EVENT_RIVER,				//18-�ӵ�Ư����
	IDS_VCA_EVENT_DREDGE,				//19-���ɵ�ж
	IDS_CONFIG_ITS_ILLEGALPARK,			//20-Υ��ͣ��
	IDS_VCA_EVENT_FIGHT,				//21-���
	IDS_PROTECT,						//22-����
	IDS_VCA_IDS_LISENCE,				//23-����ʶ��
	IDS_CFG_FEC_HEAT_MAP,				//24-�ȶ�ͼ
	IDS_CFG_SEEPER,						//25-��ˮ���
	IDS_WINDOW_DETECTION,				//26-�������
	IDS_VCA_EVENT_FACEREC,				//27-ST����ʶ��
	IDS_CONFIG_ITS_ILLEGALPARK,			//28-��λ����
	IDS_UNKNOW_CONNECT,					//29-δ֪
	IDS_CFG_HELMET,						//30-��ȫñ���
	IDS_CFG_LINKDOMETRACK,				//31-������������ 
	IDS_VCA_SLUICEGATE,					//32-բ�ż��
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