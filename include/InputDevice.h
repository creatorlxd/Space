#pragma once
#include "stdafx.h"
#include "Space.h"

class InputInterface		//D3DInput接口
{
public:
	InputInterface();
	~InputInterface();
	bool Init(HINSTANCE hInstance);	//初始化
	LPDIRECTINPUT8 GetInterface();	//获取接口
private:
	LPDIRECTINPUT8 m_pDirectInput;	//D3DInput接口
};

class InputDevice		//输入设备
{
public:
	InputDevice();
	~InputDevice();
	bool Init(HWND hwnd,InputInterface inputinterface,REFGUID rguid,LPCDIDATAFORMAT lpdf);	//初始化
	bool DeviceRead(void* pBuffer, long lSize);					//读取设备内容
private:
	LPDIRECTINPUTDEVICE m_InputDevice;	//输入设备
};