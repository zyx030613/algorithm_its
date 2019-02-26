#ifndef _BASE_PAGE_H
#define _BASE_PAGE_H

#include "BaseWindow.h"

#define TEMP_TEMPLATE_INDEX		255
const int CONST_LENGTH_TWO = 2;
const int CONST_LENGTH_THREE = 3;
const int CONST_MIN_SLIDER = 0;												//滑块控件最小值
const int CONST_MAX_SLIDER = 255;											//滑块控件最大值
const int CONST_MAX_100 = 100;

#define MAX_DEV_STATE_COUNT	6		//设备状态类型总数
typedef enum 
{
	n_Device_Type_RedLight = 0,				//红灯状态
	n_Device_Type_Senser_IsOnline,			//车检器状态
	n_Device_Type_Senser_Loop_IsOnline,		//线圈状态
	n_Device_Type_Cam_Temp,					//相机温度
	n_Device_Type_Singnal_IsOnline,			//红灯信号检测器状态
	n_Device_Type_Illumination,				//图像亮度（当前光照）
}n_DEVICE_TYPE;

class CLS_BasePage :
	public CLS_BaseWindow
{
public:
	CLS_BasePage(UINT nIDTemplate,CWnd* pParentWnd = NULL);//需要这个 
	~CLS_BasePage();
	static CString GetHDTemplateName(char* pTemplateName);//将设备传回来的模板名称转换到显示到界面上的内容
	
	int		m_iLogonID;
	int		m_iChannelNO;
	int		m_iStreamNO;

	void GetNvsFileTime(CDateTimeCtrl* _pDt, OUT NVS_FILE_TIME &_tTime);
	CString GetWidgetText(int nId);
	virtual void OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo );

};

#endif
