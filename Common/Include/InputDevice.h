#pragma once
#include "stdafx.h"
#include "Space.h"

class InputInterface		//D3DInput�ӿ�
{
public:
	InputInterface()
		: m_pDirectInput(nullptr) {}
	~InputInterface();
	InputInterface(const InputInterface&) = delete;
	bool Init(HINSTANCE hInstance);	//��ʼ��
	LPDIRECTINPUT8 GetInterface();	//��ȡ�ӿ�
private:
	LPDIRECTINPUT8 m_pDirectInput;	//D3DInput�ӿ�
};

class InputDevice		//�����豸
{
public:
	InputDevice()
		: m_InputDevice(nullptr) {}
	~InputDevice();
	bool Init(HWND hwnd, InputInterface& inputinterface, REFGUID rguid, LPCDIDATAFORMAT lpdf);	//��ʼ��
	bool DeviceRead(void* pBuffer, long lSize);					//��ȡ�豸����
private:
	LPDIRECTINPUTDEVICE m_InputDevice;	//�����豸
};

class KeyboardDevice	//�����豸
{
public:
	KeyboardDevice();
	~KeyboardDevice();
	bool Init(HWND hwnd, InputInterface& inputinterface);			//��ʼ��
	bool DeviceRead();											//��ȡ�豸
	bool IfPressDown(int b);									//�ж��Ƿ���ĳ����
private:
	InputDevice m_InputDevice;
	char m_Content[256];										//��������
};

class MouseDevice		//����豸
{
public:
	MouseDevice();
	~MouseDevice();
	bool Init(HWND hwnd, InputInterface& inputinterface);			//��ʼ��
	bool DeviceRead();												//��ȡ�豸
	DIMOUSESTATE GetMouseState();									//��ȡ�������
private:
	InputDevice m_InputDevice;
	DIMOUSESTATE m_Content;										//�������
};