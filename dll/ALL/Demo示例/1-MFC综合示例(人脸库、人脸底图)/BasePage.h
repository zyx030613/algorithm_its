#ifndef _BASE_PAGE_H
#define _BASE_PAGE_H

#include "BaseWindow.h"

#define TEMP_TEMPLATE_INDEX		255
const int CONST_LENGTH_TWO = 2;
const int CONST_LENGTH_THREE = 3;
const int CONST_MIN_SLIDER = 0;												//����ؼ���Сֵ
const int CONST_MAX_SLIDER = 255;											//����ؼ����ֵ
const int CONST_MAX_100 = 100;

#define MAX_DEV_STATE_COUNT	6		//�豸״̬��������
typedef enum 
{
	n_Device_Type_RedLight = 0,				//���״̬
	n_Device_Type_Senser_IsOnline,			//������״̬
	n_Device_Type_Senser_Loop_IsOnline,		//��Ȧ״̬
	n_Device_Type_Cam_Temp,					//����¶�
	n_Device_Type_Singnal_IsOnline,			//����źż����״̬
	n_Device_Type_Illumination,				//ͼ�����ȣ���ǰ���գ�
}n_DEVICE_TYPE;

class CLS_BasePage :
	public CLS_BaseWindow
{
public:
	CLS_BasePage(UINT nIDTemplate,CWnd* pParentWnd = NULL);//��Ҫ��� 
	~CLS_BasePage();
	static CString GetHDTemplateName(char* pTemplateName);//���豸��������ģ������ת������ʾ�������ϵ�����
	
	int		m_iLogonID;
	int		m_iChannelNO;
	int		m_iStreamNO;

	void GetNvsFileTime(CDateTimeCtrl* _pDt, OUT NVS_FILE_TIME &_tTime);
	CString GetWidgetText(int nId);
	virtual void OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo );

};

#endif
