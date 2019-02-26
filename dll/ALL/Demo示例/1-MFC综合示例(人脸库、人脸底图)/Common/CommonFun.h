#ifndef __COMMONFUN_H__
#define __COMMONFUN_H__

#include "LanguageManager.h"
#include "DeviceManager.h"
#include "LogManager.h"
#include "MessageManager.h"

enum DlgType
{
	n_Dlg_ADD,
	n_Dlg_Edit,
};

#define MAX_LIST_COLUMN_NAME_LEN 128

#define DLL_LOAD_SUCCESS         0
#define DLL_NOT_FOUND           -1
#define DLL_RELOAD              -2
#define DLL_FUN_EXPORT_FAILED   -3
#define TYPEDEF_FUNCTION(funcName)  typedef int (__stdcall* pf##funcName)
#define DECLARE_FUNCTION(funcName)	extern pf##funcName funcName
#define TYPEDEF_FUNCTION2(funcName)  typedef int (__cdecl* pf##funcName)
#define IMPLEMENT_FUNCTION(funcName)  pf##funcName funcName = NULL
//#define EXPORT_FUNCTION(hDll, funcName)	if(NULL == (funcName = (pf##funcName)::GetProcAddress(hDll, #funcName))) {return DLL_FUN_EXPORT_FAILED;}
#define EXPORT_FUNCTION(hDll, funcName)	funcName = (pf##funcName)::GetProcAddress(hDll, #funcName);
#define  TYPEDEF_FUNCTION_RET(retType, funcName) typedef retType (__stdcall* pf##funcName)
#define DH_PARAM_SEPARATOR ','

#define MAX_LOG_MSG_LEN		4096
//IP校验
int				IsValidIP(const char* _cIP);
int				IsValidIP(const char* _cIP,const char* _cMask,const char* _cGateway);

//语言管理
#define SetCurrentLanguage(_iLanguage)\
	CLS_LanguageManager::Instance()->SetLanguage(_iLanguage)

#define SetDlgItemTextEx(_iIDDlgItem,_uIDResource)\
	CLS_LanguageManager::Instance()->SetText(m_hWnd,_iIDDlgItem,_uIDResource)

#define SetWindowTextEx(_uIDResource)\
	CLS_LanguageManager::Instance()->SetText(this,_uIDResource)

#define GetTextEx(_uIDResource)\
	CLS_LanguageManager::Instance()->GetText(_uIDResource)

//设备管理
PDEVICE_INFO FindDevice(char* _pcIP, int _iPort, char* _pcProxy,char* _pcID,int* _piLogonID = NULL);
PDEVICE_INFO FindDevice(int _iLogonID);
PDEVICE_INFO AddDevice(int _iLogonID);
PDEVICE_INFO RemoveDevice(int _iLogonID);
PDEVICE_INFO RemoveDevice(char* _pcIP,int _iPort,char* _pcProxy,char* _pcID,int* _piLogonID = NULL);
PCHANNEL_INFO FindChannel(int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID = NULL);
PCHANNEL_INFO FindChannel(unsigned int _uConnID);
PCHANNEL_INFO AddChannel(unsigned int _uConnID);
PCHANNEL_INFO RemoveChannel(unsigned int _uConnID);
PCHANNEL_INFO RemoveChannel(int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID = NULL);

//日志管理
void SetLogCtrl(CListCtrl* _plvLog);
int SetLogFileName(char* _pcFileName,int _iLen = 0);
int SetLogCaps(unsigned int _uRemove,unsigned int _uAdd);
unsigned int GetLogCaps();
void AddLog(int _iLogType,const char* _pcDevFmt,const char* _pcLogFmt, ...);

void OutPutLogMsg(const char* _pcLogFmt, ...);

void DestroyManager();

int InsertItem(CTabCtrl& _TabCtrl,int _iItem,LPCTSTR _strItem);
int InsertItem(CTabCtrl& _TabCtrl,int _iItem,unsigned int _uIDResource);
int InsertColumn(CListCtrl& _ListCtrl,int _iColumn,LPCTSTR _strColumn, 
				 int _iFormat = LVCFMT_LEFT,int _iWidth = -1,int _iSubItem = -1);
int InsertColumn(CListCtrl& _ListCtrl,int _iColumn,unsigned int _uIDResource, 
				 int _iFormat = LVCFMT_LEFT,int _iWidth = -1,int _iSubItem = -1);
int InsertString(CComboBox& _ComboBox,int _iIndex,LPCTSTR _strItem);
int InsertString(CComboBox& _ComboBox,int _iIndex,unsigned int _uIDResource);
HTREEITEM InsertItem(CTreeCtrl& _TreeCtrl,LPCTSTR _strItem,DWORD_PTR _dwData,HTREEITEM _hParent = TVI_ROOT);
HTREEITEM InsertItem(CTreeCtrl& _TreeCtrl,unsigned int _uIDResource,DWORD_PTR _dwData,HTREEITEM _hParent = TVI_ROOT);

//设备验证
bool IsDVR(const int _iProductModel);

CString IntToString(int _iData);

string IntToStr( int _iValue );

int SetLocalSaveDirectory(CString _strPath);
CString GetLocalSaveDirectory();

CString Bytes2HexString(unsigned char* _pcSrc,int _iSrcLen );


bool Inner_SafeCloseFile(FILE** _ppFile);

CString IntToCString(int _iPara, CString *_pCstr = NULL);

bool IfPointInPolygon(POINT _ptCur, POINT *_ptPolygon, int _iPtSum = 4);
bool IfHaveInterSection(POINT _ptLine1Start, POINT _ptLine1End, POINT _ptLine2Start, POINT _ptLine2End);
bool IfPolygonIntersect(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2);
bool IfPolygonInPolygon(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2);

//消息管理
void* MallocMsgMemory(int _iSize);
void FreeMsgMemory(void* _pMemory);
//
int SplitStringToArray(const string &_strStingSource, const string &_strSplitChar,
					   string *_strArray, int _iArraySize, const int _numberOfElements = 10240); 
CString GetText(UINT _uiID);
CString ExtractFilePath();

//根据ComboBox ItemData获取下标ys
int GetCboSel(CComboBox* _pComboBox, int _iItemData);

int FillStringBufferGb2312(char* _pcStringBuffer, int _iStringLen, char* _pcSrc, int _iSrcLen);

void SetListCtrlColumn(CListCtrl& _lstListCtrl, int _iIndex, CString _cstrColumnName);

#endif //__COMMONFUN_H__
