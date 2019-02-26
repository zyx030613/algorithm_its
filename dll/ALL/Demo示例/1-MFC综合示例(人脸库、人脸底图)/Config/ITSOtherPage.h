#ifndef _ITS_OTHER_PAGE_H
#define _ITS_OTHER_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

static void __stdcall cbkRecvDataEx(unsigned long _ulID,unsigned char* _ucData,int _iLen, int _iFlag, void* _lpUserData);

#define  MAX_PICTURE_NUM 3
#define  PIC_CRC_NUM 3
#define  PACKET_HEAD_LEN 16
typedef  unsigned int uint;
typedef struct
{
	unsigned char	m_ui8PkgHead[PACKET_HEAD_LEN]; //��ͷ //{16,14,12,10,8,6,4,2,1,3,5,7,9,11,13,15}
	uint	m_ui32DataType;						//�������ͣ�
	int   	m_iChannelID;						//������ //���0

	char  	m_cPlate[32];						//����
	//ǰ16char��������16char Ϊ0����һ��ץ��ͼƬȫ��Ϊ0��
	int   	m_iPlateColor;			            //������ɫ����һ��ץ��ͼƬ�ò�����0
	int   	m_iPlateType;			            //��������, ��һ��ץ��ͼƬ�ò�����0
	int	  	m_iCarColor;			            //������ɫ, ��һ��ץ��ͼƬ�ò�����0
	//����������32����ɫ�������ն˰��չ���ת��10����ɫ
	RECT	m_stPlateRange;			            //���Ʒ�Χ, ��һ��ץ��ͼƬ�ò�����0
	int   	m_iCharConfid[12];	                //���ַ����Ŷ�,���Ϊ12���ַ� ǰ8������ ��4��Ϊ0,ÿ����ֵ�ķ�Χ0-1024, , ��һ��ץ��ͼƬ�ò�����0
	int   	m_iCharNum;					        //�ַ���Ŀ ���8  --,��һ��ץ��ͼƬ�ò�����0
	int   	m_iPlateConfid;				        //���������Ŷ�, ��һ��ץ��ͼƬ�ò�����0
	int   	m_iRecoNum;					        //ʶ��ͼƬ���  //Υͣ��3��ͼƬ��ʶ��Ϊ�ڶ��ţ��̶����Ϊ2�����ں�˶���ʶ��ʹ��
	float 	m_fSpeed;							//�����ٶ� //���0
	int 	m_iVehicleDirection;				//�������� //���0
	int		m_iAlarmType;						//��������
	char  	m_cCameraIP[16];					//���IP  //��ʽ���磺127.0.0.1
	int   	m_iCaptureInfoNum;					//��¼������ͼƬ���� //�̶�Ϊ1��ע��˴����޸ģ���3��Ϊ1
	int     m_iRedBeginTime;					//��ƿ�ʼʱ�䣬��λ�� //���Ϊ0
	int     m_iRedEndTime;						//��ƽ���ʱ�䣬��λ�� //���Ϊ0
	char  	m_stCaptureTime[MAX_PICTURE_NUM][8];//ÿ��ͼƬ��ץ��ʱ��:��-��-��-����-ʱ-��-��-����
	//ע�⣬����Ŀǰʵ��Ӧ�ã�ֻ��һ��ͼƬ���˴���stCaptureTime[1][8]��stCaptureTime[2][8]Ϊȫ0��ֻ����ץ��ʱ�䵽stCaptureTime[0][8]
	int	  	m_iCaptureLen[MAX_PICTURE_NUM];	    //ÿ��ͼƬ�ĳ���
	//ע�⣬ͬ�ϣ���䵱ǰͼƬ���ȵ�m_iCaptureLen[0]���������Ϊ0
	//Υͣ�ֶΣ�����Ŀר���ֶΣ���
	int 		m_iPreset;					    //Ԥ��λ���
	int 		m_iArea;					    //������
	char 		fileName[32];				    //¼���ļ���
	long		m_iCarSerialNum;			    //Υͣ������ţ�ͬһ�豸�ñ��Ψһ
	int			m_iPictureNum;				    //��3��ץ���е�ͼƬ��ţ�1��2��3
	unsigned char	m_ui8PkgTail[PACKET_HEAD_LEN];		//��β{15,13,11,9,7,5,3,1,2,4,6,8,10,12,14,16};
}STRCT_Record;

// CLS_ITSOtherPage dialog

class CLS_ITSOtherPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSOtherPage)

public:
	CLS_ITSOtherPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSOtherPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_OTHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateOther();
	void UpdateEnable();
	void UI_UpdateWorkmode();
	void UI_UpdateLinkCamera();

private:
	CEdit m_edtDeviceCode;
	CEdit m_edtRoadName;
	CButton m_btnCamLocation;
	CEdit m_edtWokeMode;
	CEdit m_edtInterval;
	CButton m_btnWokeMode;
	CComboBox m_cboPicChan;
	CComboBox m_cboCapChan;
	CComboBox m_cboNetMode;
	CButton m_chkConnPic;	
	CButton m_btnConnect;
	CButton m_btnDisconnect;
	CComboBox m_cboEnableMode;
	CComboBox m_cboEnable;
	CComboBox m_cboDevSta;
	CComboBox m_cboLineNo;
	CButton m_chkLinkEnable;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonCamlocation();
	afx_msg void OnBnClickedButtonWorkmode();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonItsEnableSet();
	afx_msg void OnCbnSelchangeComboItsEnableMode();

	afx_msg void OnBnClickedButtonItsJpegsizeSet();
	afx_msg void OnBnClickedButtonItsJpegqualitySet();
	afx_msg void OnCbnSelchangeComboItsDevsta();
	afx_msg void OnBnClickedBtnLinkSet();
	afx_msg void OnCbnSelchangeCboLineNo();
};

#endif