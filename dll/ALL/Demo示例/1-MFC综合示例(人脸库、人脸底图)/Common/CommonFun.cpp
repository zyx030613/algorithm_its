#include "stdafx.h"
#include "CommonFun.h"
#include <stdio.h>

static char s_cChineseCharMin = (char)0xA1;
static char s_cChineseCharMax = (char)0xF7;

CString g_strLocalSaveDirectory;

//  有效IP地址返回>0, 其中:
//  多播地址:2
//  子网掩码:3
//  普通IP:1
int IsValidIP(const char* _cIP)
{
	if (!_cIP)
		return 0;

    int i, i1, i2, i3, i4=0;
	char ct = '\0';
    unsigned long uIP=0;
    if(sscanf_s(_cIP, "%03d.%03d.%03d.%d%c", &i1, &i2, &i3, &i4, &ct) != 4)
        return 0;
    if( ((0 <= i1) && (i1 <= 255)) &&
        ((0 <= i2) && (i2 <= 255)) &&
        ((0 <= i3) && (i3 <= 255)) &&
        ((0 <= i4) && (i4 <= 255)) )
    {
        if((224 <= i1) && (i1 <= 239))
            return 2;   //Multicast

        uIP = (i1<<24) | (i2<<16) | (i3<<8) | (i4);
        i=0;
        while(((uIP & 0x01)==0) && i<32)
        {
            uIP = uIP>>1;
            i++;
        }
        while(((uIP & 0x01)==1) && i<32)
        {
            uIP = uIP>>1;
            i++;
        }
        if(i==32)
            return 3;     //Mask
        else
            return 1;     //valid ip
    }
    return 0;
}

int IsValidIP(const char* _cIP,const char* _cMask,const char* _cGateway)
{
	unsigned long ulIP = inet_addr(_cIP);
	unsigned long ulMask = inet_addr(_cMask);
	unsigned long ulGateway = inet_addr(_cGateway);
	
	if (ulIP != 0 || ulGateway != 0)
	{
		if (INADDR_NONE == ulIP || INADDR_NONE == ulMask || INADDR_NONE == ulGateway
			||( 0 == (ulIP & 0xFF) || 0 == (ulGateway & 0xFF)))
		{
			return -1;
		}
	}

	if ((ulIP & ulMask) == (ulGateway & ulMask))
	{
		return 0;
	}
	return -1;
}

PDEVICE_INFO FindDevice( char* _pcIP, int _iPort,char* _pcProxy,char* _pcID,int* _piLogonID)
{
	return CLS_DeviceManager::Instance()->FindDevice(_pcIP,_iPort,_pcProxy,_pcID,_piLogonID);
}

PDEVICE_INFO FindDevice( int _iLogonID )
{
	return CLS_DeviceManager::Instance()->FindDevice(_iLogonID);
}

PDEVICE_INFO AddDevice( int _iLogonID )
{
	return CLS_DeviceManager::Instance()->AddDevice(_iLogonID);
}

PDEVICE_INFO RemoveDevice( int _iLogonID )
{
	return CLS_DeviceManager::Instance()->RemoveDevice(_iLogonID);
}

PDEVICE_INFO RemoveDevice( char* _pcIP,int _iPort,char* _pcProxy,char* _pcID,int* _piLogonID /*= NULL*/ )
{
	return CLS_DeviceManager::Instance()->RemoveDevice(_pcIP,_iPort,_pcProxy,_pcID,_piLogonID);
}

PCHANNEL_INFO FindChannel( int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID)
{
	return CLS_DeviceManager::Instance()->FindChannel(_iLogonID,_iChannelNo,_iStreamNo,_puConnID);
}

PCHANNEL_INFO FindChannel( unsigned int _uConnID )
{
	return CLS_DeviceManager::Instance()->FindChannel(_uConnID);
}

PCHANNEL_INFO AddChannel( unsigned int _uConnID )
{
	return CLS_DeviceManager::Instance()->AddChannel(_uConnID);
}

PCHANNEL_INFO RemoveChannel( unsigned int _uConnID )
{
	return CLS_DeviceManager::Instance()->RemoveChannel(_uConnID);
}

PCHANNEL_INFO RemoveChannel( int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID /*= NULL*/ )
{
	return CLS_DeviceManager::Instance()->RemoveChannel(_iLogonID,_iChannelNo,_iStreamNo,_puConnID);
}
void SetLogCtrl( CListCtrl* _plvLog )
{
	CLS_LogManager::Instance()->SetListCtrl(_plvLog);
}

int SetLogFileName( char* _pcFileName,int _iLen )
{
	if (_iLen <= 0)
	{
		_iLen = (int)strlen(_pcFileName);
	}
	return CLS_LogManager::Instance()->SetFileName(_pcFileName,_iLen);
}

int SetLogCaps( unsigned int _uRemove,unsigned int _uAdd )
{
	return CLS_LogManager::Instance()->SetLogCaps(_uRemove,_uAdd);
}

unsigned int GetLogCaps()
{
	return CLS_LogManager::Instance()->GetLogCaps();
}

void AddLog( int _iLogType,const char* _pcDevFmt,const char* _pcLogFmt, ... )
{
	int iLastError = GetLastError();
	if (NULL == _pcDevFmt)
	{
		_pcDevFmt = "";
	}
	if (NULL == _pcLogFmt)
	{
		_pcLogFmt = "";
	}

	char cDevInfo[2048] = {0};
	char cFormat[1024] = {0};
	char cSplit[5] = {28,29,30,31};
	
	sprintf_s(cFormat,sizeof(cFormat),"%s%s%s",_pcDevFmt,cSplit,_pcLogFmt);
	va_list vlLog;
	va_start(vlLog, _pcLogFmt);
	vsprintf_s(cDevInfo, cFormat, vlLog);
	va_end(vlLog);	
	char* pcLogInfo = strstr(cDevInfo,cSplit);
	if (pcLogInfo)
	{
		memset(pcLogInfo,0,strlen(cSplit));
		pcLogInfo += strlen(cSplit);
	}
	else
	{
		pcLogInfo = "";
	}

	CLS_LogManager::Instance()->AddLog(_iLogType,cDevInfo,pcLogInfo,iLastError);
}

void OutPutLogMsg(const char* _pcLogFmt, ...)
{
	if (NULL == _pcLogFmt)
	{
		_pcLogFmt = "";
	}
	char cLogBuf[MAX_LOG_MSG_LEN] = {0};
	va_list vlsLog;
	va_start( vlsLog, _pcLogFmt );
	_vsnprintf(cLogBuf, MAX_LOG_MSG_LEN, _pcLogFmt, vlsLog);
	va_end(vlsLog);

	//C语言中数组不容许整体复制
	char* pcLogInfo = strcat(cLogBuf, "\n");
	::OutputDebugString(pcLogInfo);
}

void DestroyManager()
{
	CLS_DeviceManager::Destroy();
	CLS_LanguageManager::Destroy();
	CLS_LogManager::Destroy();
	CLS_MessageManager::Destroy();
}


int InsertItem( CTabCtrl& _TabCtrl,int _iItem,LPCTSTR _strItem )
{
	int iCount = _TabCtrl.GetItemCount();
	if (_iItem >= 0 && _iItem < iCount)
	{
		TCITEM tcItem = {0};
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = (LPSTR)_strItem;
		_TabCtrl.SetItem(_iItem,&tcItem);
	}
	else
	{
		_TabCtrl.InsertItem(_iItem,_strItem);
	}

	return 0;
}

int InsertItem( CTabCtrl& _TabCtrl,int _iItem,unsigned int _uIDResource )
{
	return InsertItem(_TabCtrl,_iItem,GetTextEx(_uIDResource));
}


HTREEITEM InsertItem( CTreeCtrl& _TreeCtrl,LPCTSTR _strItem,DWORD_PTR _dwData,HTREEITEM _hParent /*= TVI_ROOT*/ )
{
	DWORD_PTR dwData = 0;
	HTREEITEM hItem = _TreeCtrl.GetChildItem(_hParent);
	while(hItem)
	{
		dwData = _TreeCtrl.GetItemData(hItem);
		if (dwData == _dwData)
		{
			_TreeCtrl.SetItemText(hItem,_strItem);
			return hItem;
		}
		hItem = _TreeCtrl.GetNextSiblingItem(hItem);
	}

	hItem = _TreeCtrl.InsertItem(_strItem,_hParent);
	_TreeCtrl.SetItemData(hItem,_dwData);
	return hItem;
}

HTREEITEM InsertItem( CTreeCtrl& _TreeCtrl,unsigned int _uIDResource,DWORD_PTR _dwData,HTREEITEM _hParent /*= TVI_ROOT*/ )
{
	return InsertItem(_TreeCtrl,GetTextEx(_uIDResource),_dwData,_hParent);
}

int InsertColumn( CListCtrl& _ListCtrl,int _iColumn,LPCTSTR _strColumn, int _iFormat /*= LVCFMT_LEFT*/,int _iWidth /*= -1*/,int _iSubItem /*= -1*/ )
{
	CHeaderCtrl* pHeader = _ListCtrl.GetHeaderCtrl();
	if (pHeader)
	{
		int iCount = pHeader->GetItemCount();
		if (_iColumn >= 0 && _iColumn < iCount)
		{
			HDITEM hdItem = {0};
			hdItem.mask = HDI_TEXT;
			hdItem.pszText = (LPSTR)_strColumn;
			pHeader->SetItem(_iColumn,&hdItem);
			return 0;
		}
	}

	_ListCtrl.InsertColumn(_iColumn,_strColumn,_iFormat,_iWidth,_iSubItem);
	return 0;
}

int InsertColumn( CListCtrl& _ListCtrl,int _iColumn,unsigned int _uIDResource, int _iFormat /*= LVCFMT_LEFT*/,int _iWidth /*= -1*/,int _iSubItem /*= -1*/ )
{
	return InsertColumn(_ListCtrl,_iColumn,GetTextEx(_uIDResource),_iFormat,_iWidth,_iSubItem);
}

int InsertString( CComboBox& _ComboBox,int _iIndex,LPCTSTR _strItem )
{
	int iItem = _ComboBox.GetCurSel();
	_ComboBox.DeleteString(_iIndex);
	_ComboBox.InsertString(_iIndex,_strItem);
	_ComboBox.SetCurSel(iItem);

	return 0;
}

int InsertString( CComboBox& _ComboBox,int _iIndex,unsigned int _uIDResource )
{
	return InsertString(_ComboBox,_iIndex,GetTextEx(_uIDResource));
}

bool IsDVR(const int _iProductModel)
{
	return ((_iProductModel & 0x100) == 0x100);
}

CString IntToString( int _iData )
{
	CString strData;
	strData.Format(_T("%d"),_iData);
	return strData;
}

string IntToStr( int _iValue )
{
	char pcValue[32] = {0};
	sprintf_s(pcValue,"%d",_iValue);
	string strTemp = pcValue;
	return strTemp;
}

int SetLocalSaveDirectory( CString _strPath )
{
	CreateDirectory(_strPath,NULL);
	g_strLocalSaveDirectory = _strPath;
	return 0;
}

CString GetLocalSaveDirectory()
{
	return g_strLocalSaveDirectory;
}

CString Bytes2HexString( unsigned char* _pcSrc,int _iSrcLen )
{
	CString strHex;
	for (int i = 0; i < _iSrcLen; ++i)
	{
		strHex.AppendFormat(_T("%02X "),_pcSrc[i]);
	}
	return strHex.Trim();
}

bool Inner_SafeCloseFile(FILE** _ppFile)
{
	if (_ppFile == NULL || *_ppFile == NULL)
		return true;

	fclose(*_ppFile);
	*_ppFile = NULL;
	return true;
}

//只能用在别的函数复制此返回值的情况时
//如intsert***(0, IntToCString(**))，不能如此用CString str = IntToCString(**)
CString IntToCString(int _iPara, CString *_pCstr/* = NULL*/)
{
	if (_pCstr == NULL)
	{
		CString strPara;
		strPara.Format(_T("%d"), _iPara);
		return strPara;
	}
	else
	{
		_pCstr->Format(_T("%d"), _iPara);
		return *_pCstr;
	}
}

//算法2 点是否在多边形内部  这里默认是四边形 _iPtSum默认为4
//_ptCur 当前点，_ptPolygon 多边形点坐标， 多边形点数
// 判断方法 从当前点与（0，0）点做一条连线，然后与多边形每条边判断是否有交点，统计一共多少个交点，偶数在外部，奇数在内部
bool IfPointInPolygon(POINT _ptCur, POINT *_ptPolygon, int _iPtSum)
{
	if(_iPtSum < 1)
		return false;
	POINT pt = {0};
	int iPtSum = 0;
	for(int i = 0; i< _iPtSum - 1; i++)   //判断当前点与（0，0）这点的连线与四边形的四条边共有多少条连线
	{
		if(IfHaveInterSection(_ptCur, pt, _ptPolygon[i], _ptPolygon[i+1]))
			iPtSum++;
	}
	//判断当前点与（0，0）这点的连线与四边形的最后一条边是否有交点
	if(IfHaveInterSection(_ptCur, pt, *_ptPolygon, *(_ptPolygon+ _iPtSum - 1)))
		iPtSum++;

	if(iPtSum%2)
	{
		//trace("在内部\n");
		return true;
	}
	else
	{
		//trace("在外部\n");
		return false;
	}
}

//算法1 判断两条线是否有交点函数
bool IfHaveInterSection(POINT _ptLine1Start, POINT _ptLine1End, POINT _ptLine2Start, POINT _ptLine2End)     //wxl 2011-11-22
{
	double iL1SX = _ptLine1Start.x;
	double iL1SY = _ptLine1Start.y;

	double iL2SX = _ptLine2Start.x;
	double iL2SY = _ptLine2Start.y;

	double iL1EX = _ptLine1End.x;
	double iL1EY = _ptLine1End.y;

	double iL2EX = _ptLine2End.x;
	double iL2EY = _ptLine2End.y;
	double fDiv = 0.0;
	double fInterSX = 0.0;           //假如有焦点 焦点x坐标
	double fInterSY = 0.0;           //假如有焦点 焦点y坐标

	fDiv = (iL1SX -iL1EX)*(iL2SY -iL2EY) -(iL2SX -iL2EX)*(iL1SY - iL1EY);
	if(fDiv == 0)
	{
		return false;
	}
	else
	{
		fInterSX = ((iL2SX-iL2EX)*(iL1SX*iL1EY -iL1EX*iL1SY)-(iL1SX-iL1EX)*(iL2SX*iL2EY - iL2EX*iL2SY))/fDiv;
		fInterSY = ((iL2EX*iL2SY -iL2SX*iL2EY)*(iL1SY-iL1EY)-(iL2SY-iL2EY)*(iL1EX*iL1SY-iL1SX*iL1EY))/fDiv;

		if (fInterSX < max(min(iL1SX,iL1EX),min(iL2SX,iL2EX)) || fInterSX > min(max(iL1SX,iL1EX),max(iL2SX,iL2EX)))
		{
			return false;
		}
		else if (fInterSY < max(min(iL1SY,iL1EY),min(iL2SY,iL2EY)) || fInterSY > min(max(iL1SY,iL1EY),max(iL2SY,iL2EY)))
		{
			return false;
		}
		else
		{
			return true;      //有交点
		}
	}
}

//算法 判断两个多边形是否相交，这个算法主要是判断两个四边形
bool IfPolygonIntersect(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2)
{
	POINT ptPolygon1[5] = {0};
	memcpy(ptPolygon1, _ptPolygon1, _iPoly1 * sizeof(POINT));
	ptPolygon1[_iPoly1] =  _ptPolygon1[0];

	POINT ptPolygon2[5] = {0};
	memcpy(ptPolygon2, _ptPolygon2, _iPoly2 * sizeof(POINT));
	ptPolygon2[_iPoly2] =  _ptPolygon2[0];

	for(int i = 0; i < _iPoly1; i++)
	{
		for(int j = 0; j < _iPoly2; j++)
		{
			if(IfHaveInterSection(*(ptPolygon1+i), *(ptPolygon1+i+1), *(ptPolygon2+j), *(ptPolygon2+j+1)))
				return true;
		}
	}
	return false;
}

//算法 两个不相交的多边形，判断是否包含
bool IfPolygonInPolygon(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2)
{
	if(IfPointInPolygon(_ptPolygon1[0], _ptPolygon2, _iPoly2))
	{
		return true;
	}
	if(IfPointInPolygon(_ptPolygon2[0], _ptPolygon1, _iPoly2))
	{
		return true;
	}
	return false;
}

void* MallocMsgMemory(int _iSize)
{
	return CLS_MessageManager::Instance()->MallocMemory(_iSize);
}

void FreeMsgMemory( void* _pMemory )
{
	CLS_MessageManager::Instance()->FreeMemory(_pMemory);
}

int SplitStringToArray(const string &_strStingSource, const string &_strSplitChar,
    string *_strArray,  int _iArraySize, const int _numberOfElements)
/*  参数：_astrStingSource:源字符串；
          _astrSplitChar：字符串分隔符 ，可以是"/"、"@"等；
          _astrArray：    返回值，字符串数组，储存拆分出的字符串的值。
    功能：将用特殊符号隔开的字符串拆分成数组
*/
{
    int iTempCount=0;
    int iTempPos=0;  //遍历整个字符串的指针    //modify by lpy;
    int iTempPos1=0; //记录一个子字符串的首地址
    int iTempPos2=0; //记录一个子字符串的尾地址

	int iTempStrLen = (int)_strStingSource.length();
    
    if (iTempStrLen > _numberOfElements) //wxl 2011-12-21 防止内存越界
    {
        iTempStrLen = _numberOfElements;
    }
    while (iTempPos<=iTempStrLen && (iTempCount < _iArraySize -1))
    {
		string strTemp = _strStingSource.substr(iTempPos,1) ; 
        if (strTemp.compare(_strSplitChar) == 0)
        {
            if (iTempPos1==0)
            {
                iTempPos1=iTempPos+1;
                if(iTempPos != 0)
                {
                    _strArray[iTempCount]=_strStingSource.substr(0, iTempPos);
                    iTempCount++;
                }
            }
            else if (iTempPos2==0)
            {
                iTempPos2=iTempPos+1;
                _strArray[iTempCount]=_strStingSource.substr(iTempPos1,iTempPos2-iTempPos1-1);
                iTempCount++;
                iTempPos1=iTempPos2;
                iTempPos2=0;
            }
        }
        iTempPos++;
    }
		_strArray[iTempCount]=_strStingSource.substr(iTempPos1,iTempPos-iTempPos1);
    return iTempCount+1;
}

CString GetText(UINT _uiID)
{
	CString strBuffer;
	strBuffer.LoadString(_uiID);
	return strBuffer;
}

CString ExtractFilePath()
{
	char fileNewPath[MAX_PATH+1]= {0};
	char *p = NULL;
	GetModuleFileName(NULL, fileNewPath, sizeof(fileNewPath)); //获取程序当前执行文件名
	p=strrchr(fileNewPath, '\\');   
	*(p + 1)='\0';
	return CString(fileNewPath);
}

int GetCboSel(CComboBox* _pComboBox, int _iItemData)
{
	int iResult = -1;
	if (NULL == _pComboBox)
	{
		return iResult;
	}

	int iMaxIndex = _pComboBox->GetCount();
	for (int iTempIndex = 0; iTempIndex < iMaxIndex; iTempIndex++)
	{
		if (_iItemData == _pComboBox->GetItemData(iTempIndex))
		{
			iResult = iTempIndex;
			break;
		}
	}

	return iResult;
}

int FillStringBufferGb2312(char* _pcStringBuffer, int _iStringLen, char* _pcSrc, int _iSrcLen)
{
	if (NULL == _pcStringBuffer || NULL == _pcSrc)
	{
		return -1;
	}

	int iCopyLen = 0;
	while (iCopyLen <= _iSrcLen)
	{
		int iCharLen = 1;
		if (_pcSrc[iCopyLen] >= s_cChineseCharMin && _pcSrc[iCopyLen] <= s_cChineseCharMax)
		{
			iCharLen = 2;
		}

		if (iCopyLen + iCharLen >= _iStringLen)
		{
			_pcStringBuffer[iCopyLen] = '\0';
			break;
		}

		if (iCopyLen + iCharLen > _iSrcLen)
		{
			_pcStringBuffer[iCopyLen] = '\0';
			break;
		}

		memcpy(_pcStringBuffer + iCopyLen, _pcSrc+iCopyLen, iCharLen);
		iCopyLen += iCharLen;
	}
	return  iCopyLen;
}

void SetListCtrlColumn(CListCtrl& _lstListCtrl, int _iIndex, CString _cstrColumnName)
{
	CHeaderCtrl *pHead = _lstListCtrl.GetHeaderCtrl();    
	if(NULL == pHead || NULL == pHead->GetSafeHwnd())    
	{    
		return;
	}  

	TCHAR szBuf[MAX_LIST_COLUMN_NAME_LEN + 1] = {0};    
	HDITEM hdItem ={0};    
	hdItem.mask = HDI_TEXT; //取字符掩码     
	hdItem.pszText = szBuf; //字符缓冲区     
	hdItem.cchTextMax = MAX_LIST_COLUMN_NAME_LEN; //缓冲区大小     
	hdItem.pszText = _cstrColumnName.GetBuffer(0); //设置新字符     
	pHead->SetItem(_iIndex, &hdItem); //设置题头   
}
