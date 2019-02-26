#ifndef _ITS_SETVCA_PAGE_H
#define _ITS_SETVCA_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "../Preview/DeviceControl.h"
#include "../Preview/ActionControl.h"

typedef struct tagPolygon
{
	int iPointCount;
	int iIndex;
	POINT m_ptSet[VCA_MAX_POLYGON_POINT_NUM];
} POLYGON;
// CLS_ITSSetVCAPage dialog

//bool IfHaveInterSection(POINT _ptLine1Start, POINT _ptLine1End, POINT _ptLine2Start, POINT _ptLine2End);
//bool IfPointInPolygon(POINT _ptCur, POINT *_ptPolygon, int _iPtSum = 4);
//bool IfPolygonIntersect(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2);
//bool IfPolygonInPolygon(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2);

class CLS_ITSSetVCAPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSSetVCAPage)

public:
	CLS_ITSSetVCAPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSSetVCAPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_SETVCA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnCancel();

public:
	void StartPlay();
	void StopPlay();

public:	// 以下函数是2011-11月，交通球项目需要添加
	void ShowVCADialog(void);
	void ShowITSDialog(void);
	int GotoPreset(int _iPreset, int _iDevAddress, int _iComNo);
	//实现视频中画四边形，矩形不交叉控制
	int AddOrDelPolygon(bool _bFlag = true); //添加或删除前一个图形，供后面修改。true：增加  false:删除 只能删除一次。
	//所以每次画完图形后，AddOrDelPolygon（true）,来新加一个图形，防止后面的操作修改了刚画好的图形
	int DrawITSQuadRangle(POINT *_ptPolygon, int _ptSum);//修改上一次画的图形，是它成为四边形  wxl 2011-11-22
	int DrawRect(POINT *_ptRect); //重画上一次画的图形，是它成为矩形  wxl 2011-11-22  注意：是重画，不是添加，所以调用前，先随意添加个图形
	void ChangePoint(void);   //wxl 2011-11-22
	/*wxl 判断当前点 在哪个区域，0表示不在任何四边形内部，10表示在四边形1内部其他区域，
	20表示在四边形2内部其他区域。。。
	11表示在四边形1的第一个矩形内部，12表示在四边形1的第二个矩形内部。。。
	21表示在四边形2的第一个矩形内部，22表示在四边形2的第二个矩形内部。。。
	*/
	int WhichAreaOfCurPt(void);
	bool IfRectValidAndDraw(POINT *_ptRect);
	bool IfPolygonValidAndDraw(POINT *_ptPolygon, int _iPoly);
	//设置或者获取界面上文本框显示的坐标
	void SetCoorEditShow(POINT *_ptPoint, int _iN0, int flag);
	void GetCoorEditShow(POINT *_ptPoint, int _iN0, int flag);
	//返回值用来判断是否画出视频窗口范围
	BOOL PolygonOnViedo(POINT *_ptArr, int _iPointCnt);
	BOOL IsInsideVideoStatic(POINT _pt);
	//	_iEnableArrow含义:按bit控制显示方式, 0x01: 箭头, 0x02: Add方式，保留其它多边形, 0x04: 只修改上一次画的多边形

public:
	HWND m_hResetPlayerWnd;
	HWND m_hPlayWnd;
	CStatic *m_pstxtPlayWnd;
	POINT m_ptSet[VCA_MAX_POLYGON_POINT_NUM];
	int m_iPointCount;				
	int m_iCurPolyIndex;
	int m_iPolyCount;
	POINT m_ptCur;
	POLYGON m_MainPolygon;
	POLYGON m_SubPolygon[3];
	POINT m_ptAngle[2];
	int m_iAngle;
	double m_dArrowLen;					//  角度线的长度
	bool m_bMouseDown;
	bool m_bSetAngle;
	int m_iModifyPointIndex;            //  修改点的下标，需要与所有的点比较来决定
	unsigned long m_ulConnID;
	unsigned int m_uiConnID;
	int m_iWidth;
	int m_iHeight;  
	//wxl 2011-11-22 交通球项目
	int m_iCurDrawGrh;       //画图形  0表示不画，1表示画四边形，2表示画矩形
	CString m_strIP;
	unsigned short m_usRangeTimeStartH[MAX_PRESET_COUNT][MAX_AREA_COUNT];
	unsigned short m_usRangeTimeStartM[MAX_PRESET_COUNT][MAX_AREA_COUNT];
	unsigned short m_usRangeTimeEndH[MAX_PRESET_COUNT][MAX_AREA_COUNT];
	unsigned short m_usRangeTimeEndM[MAX_PRESET_COUNT][MAX_AREA_COUNT];

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateDeviceType();
	BOOL UI_UpdateGraph();

private:
	CComboBox m_cboPreset;
	CComboBox m_cboArea;
	CEdit m_edtTime;
	CComboBox m_cboTimeRange;
	CDateTimeCtrl m_dtcFrom;
	CDateTimeCtrl m_dtcTo;
	CEdit m_edtPointx[4];
	CEdit m_edtPointy[4];
	CEdit m_edtParkTime;
	CEdit m_edtSensitivity;
	CButton m_btnReset;
	CButton m_btnSet;
	CEdit m_edtRectPointx[4][2];
	CEdit m_edtRectPointy[4][2];
	CComboBox m_cboParamArea;
	CButton m_btnParamReset;
	CButton m_btnParamSet;
	CButton m_btnExactFix;
	CStatic m_StxtPlayWnd;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	CLS_DeviceControl m_tDevCtrl;
	char m_cDeviceType[64];
public:
	afx_msg void OnCbnSelchangeComboPreset();
	afx_msg void OnCbnSelchangeComboArea();
	afx_msg void OnCbnSelchangeComboTimerange();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnCbnSelchangeComboParamArea();
	afx_msg void OnBnClickedButtonParamReset();
	afx_msg void OnBnClickedButtonParamSet();
	afx_msg void OnBnClickedButtonParamExactfix();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
};
#endif