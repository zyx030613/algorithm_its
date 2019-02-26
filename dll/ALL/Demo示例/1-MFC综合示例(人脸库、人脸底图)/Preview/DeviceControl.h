#ifndef DEVCONTROL_H
#define DEVCONTROL_H

#include <windows.h>
#include <stdio.h>

//Ctrl param
struct CONTROL_PARAM
{
	int   m_iAddress;   //device address
	int   m_iPreset;	  //preset pos
	POINT m_ptMove;      //move pos
	BYTE  m_btBuf[256];//Ctrl-Code(OUT)
	int   m_iCount;     //Ctrl-Code count(OUT)
};

typedef int (__stdcall *pfGetControlCode)(int _iAction, CONTROL_PARAM *_pParam);
class CLS_DeviceControl
{
private:
	pfGetControlCode m_pfGetControlCode;       //dll function pointer
	HINSTANCE       m_hInst;                 //handle of dll
	char			m_cDeviceType[MAX_PATH];

private:
/*
	Init dll
	*/
	int Initialize(char* _pcDevictType);

public:
	CLS_DeviceControl();	                
	~CLS_DeviceControl();
	/*
	Get Ctrl-Code
	return£º1£­success 2£­failed
	*/
	int GetCtrlCode(char* _pcDevictType,int _iActionCode,CONTROL_PARAM* _cParam);

};

#endif