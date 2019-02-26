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

public:	// ���º�����2011-11�£���ͨ����Ŀ��Ҫ���
	void ShowVCADialog(void);
	void ShowITSDialog(void);
	int GotoPreset(int _iPreset, int _iDevAddress, int _iComNo);
	//ʵ����Ƶ�л��ı��Σ����β��������
	int AddOrDelPolygon(bool _bFlag = true); //��ӻ�ɾ��ǰһ��ͼ�Σ��������޸ġ�true������  false:ɾ�� ֻ��ɾ��һ�Ρ�
	//����ÿ�λ���ͼ�κ�AddOrDelPolygon��true��,���¼�һ��ͼ�Σ���ֹ����Ĳ����޸��˸ջ��õ�ͼ��
	int DrawITSQuadRangle(POINT *_ptPolygon, int _ptSum);//�޸���һ�λ���ͼ�Σ�������Ϊ�ı���  wxl 2011-11-22
	int DrawRect(POINT *_ptRect); //�ػ���һ�λ���ͼ�Σ�������Ϊ����  wxl 2011-11-22  ע�⣺���ػ���������ӣ����Ե���ǰ����������Ӹ�ͼ��
	void ChangePoint(void);   //wxl 2011-11-22
	/*wxl �жϵ�ǰ�� ���ĸ�����0��ʾ�����κ��ı����ڲ���10��ʾ���ı���1�ڲ���������
	20��ʾ���ı���2�ڲ��������򡣡���
	11��ʾ���ı���1�ĵ�һ�������ڲ���12��ʾ���ı���1�ĵڶ��������ڲ�������
	21��ʾ���ı���2�ĵ�һ�������ڲ���22��ʾ���ı���2�ĵڶ��������ڲ�������
	*/
	int WhichAreaOfCurPt(void);
	bool IfRectValidAndDraw(POINT *_ptRect);
	bool IfPolygonValidAndDraw(POINT *_ptPolygon, int _iPoly);
	//���û��߻�ȡ�������ı�����ʾ������
	void SetCoorEditShow(POINT *_ptPoint, int _iN0, int flag);
	void GetCoorEditShow(POINT *_ptPoint, int _iN0, int flag);
	//����ֵ�����ж��Ƿ񻭳���Ƶ���ڷ�Χ
	BOOL PolygonOnViedo(POINT *_ptArr, int _iPointCnt);
	BOOL IsInsideVideoStatic(POINT _pt);
	//	_iEnableArrow����:��bit������ʾ��ʽ, 0x01: ��ͷ, 0x02: Add��ʽ���������������, 0x04: ֻ�޸���һ�λ��Ķ����

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
	double m_dArrowLen;					//  �Ƕ��ߵĳ���
	bool m_bMouseDown;
	bool m_bSetAngle;
	int m_iModifyPointIndex;            //  �޸ĵ���±꣬��Ҫ�����еĵ�Ƚ�������
	unsigned long m_ulConnID;
	unsigned int m_uiConnID;
	int m_iWidth;
	int m_iHeight;  
	//wxl 2011-11-22 ��ͨ����Ŀ
	int m_iCurDrawGrh;       //��ͼ��  0��ʾ������1��ʾ���ı��Σ�2��ʾ������
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