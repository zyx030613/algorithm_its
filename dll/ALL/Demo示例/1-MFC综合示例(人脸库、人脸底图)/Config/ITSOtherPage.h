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
	unsigned char	m_ui8PkgHead[PACKET_HEAD_LEN]; //包头 //{16,14,12,10,8,6,4,2,1,3,5,7,9,11,13,15}
	uint	m_ui32DataType;						//数据类型，
	int   	m_iChannelID;						//车道号 //填充0

	char  	m_cPlate[32];						//车牌
	//前16char拷贝，后16char 为0，第一张抓拍图片全部为0。
	int   	m_iPlateColor;			            //车牌颜色，第一张抓拍图片该参数置0
	int   	m_iPlateType;			            //车辆类型, 第一张抓拍图片该参数置0
	int	  	m_iCarColor;			            //车身颜色, 第一张抓拍图片该参数置0
	//相机输出的是32种颜色，但是终端按照国标转成10种颜色
	RECT	m_stPlateRange;			            //车牌范围, 第一张抓拍图片该参数置0
	int   	m_iCharConfid[12];	                //各字符置信度,最大为12个字符 前8个拷贝 后4个为0,每个的值的范围0-1024, , 第一张抓拍图片该参数置0
	int   	m_iCharNum;					        //字符数目 填充8  --,第一张抓拍图片该参数置0
	int   	m_iPlateConfid;				        //整车牌置信度, 第一张抓拍图片该参数置0
	int   	m_iRecoNum;					        //识别图片序号  //违停共3张图片，识别为第二张，固定填充为2，用于后端二次识别使用
	float 	m_fSpeed;							//车辆速度 //填充0
	int 	m_iVehicleDirection;				//车辆方向 //填充0
	int		m_iAlarmType;						//报警类型
	char  	m_cCameraIP[16];					//相机IP  //格式例如：127.0.0.1
	int   	m_iCaptureInfoNum;					//记录包含的图片数量 //固定为1，注意此处的修改，从3改为1
	int     m_iRedBeginTime;					//红灯开始时间，单位秒 //填充为0
	int     m_iRedEndTime;						//红灯结束时间，单位秒 //填充为0
	char  	m_stCaptureTime[MAX_PICTURE_NUM][8];//每张图片的抓拍时间:年-月-日-星期-时-分-秒-毫秒
	//注意，根据目前实际应用，只有一张图片，此处清stCaptureTime[1][8]和stCaptureTime[2][8]为全0，只复制抓拍时间到stCaptureTime[0][8]
	int	  	m_iCaptureLen[MAX_PICTURE_NUM];	    //每张图片的长度
	//注意，同上，填充当前图片长度到m_iCaptureLen[0]，其他填充为0
	//违停字段（本项目专属字段）：
	int 		m_iPreset;					    //预置位编号
	int 		m_iArea;					    //区域编号
	char 		fileName[32];				    //录像文件名
	long		m_iCarSerialNum;			    //违停车辆编号，同一设备该编号唯一
	int			m_iPictureNum;				    //在3张抓拍中的图片编号，1、2或3
	unsigned char	m_ui8PkgTail[PACKET_HEAD_LEN];		//包尾{15,13,11,9,7,5,3,1,2,4,6,8,10,12,14,16};
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