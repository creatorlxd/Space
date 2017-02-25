#pragma once
#include "stdafx.h"
#include "Space.h"

class InputInterface		//D3DInput�ӿ�
{
public:
	InputInterface();
	~InputInterface();
	bool Init(HINSTANCE hInstance);	//��ʼ��
	LPDIRECTINPUT8 GetInterface();	//��ȡ�ӿ�
private:
	LPDIRECTINPUT8 m_pDirectInput;	//D3DInput�ӿ�
};

class InputDevice		//�����豸
{
public:
	InputDevice();
	~InputDevice();
	bool Init(HWND hwnd,InputInterface inputinterface,REFGUID rguid,LPCDIDATAFORMAT lpdf);	//��ʼ��
	bool DeviceRead(void* pBuffer, long lSize);					//��ȡ�豸����
private:
	LPDIRECTINPUTDEVICE m_InputDevice;	//�����豸
};