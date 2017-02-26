#include "stdafx.h"
#include "InputDevice.h"

InputInterface::InputInterface()
{
	m_pDirectInput = NULL;
}

InputInterface::~InputInterface()
{
	if (m_pDirectInput != NULL)
		SAFE_RELEASE(m_pDirectInput);
}

bool InputInterface::Init(HINSTANCE hInstance)
{
	if (FAILED(DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (void**)&m_pDirectInput, NULL)))
		return false;
	else
		return true;
}

LPDIRECTINPUT8 InputInterface::GetInterface()
{
	return m_pDirectInput;
}

InputDevice::InputDevice()
{
	m_InputDevice = NULL;
}

InputDevice::~InputDevice()
{
	if (m_InputDevice != NULL)
	{
		SAFE_RELEASE(m_InputDevice);
		m_InputDevice->Unacquire();
	}
}

bool InputDevice::Init(HWND hwnd, InputInterface inputinterface, REFGUID rguid, LPCDIDATAFORMAT lpdf)
{
	if (FAILED(inputinterface.GetInterface()->CreateDevice(rguid, (LPDIRECTINPUTDEVICE8W*)(&m_InputDevice), NULL)))
		return false;
	m_InputDevice->SetDataFormat(lpdf);
	m_InputDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	return true;
}

bool InputDevice::DeviceRead(void * pBuffer, long lSize)
{
	HRESULT hr;
	LPDIRECTINPUTDEVICE8A InputDevice =(LPDIRECTINPUTDEVICE8A)m_InputDevice;
	while (true)
	{
		InputDevice->Poll();
		InputDevice->Acquire();          // 获取设备的控制权  
		if (SUCCEEDED(hr = InputDevice->GetDeviceState(lSize, pBuffer))) break;
		if (hr != DIERR_INPUTLOST || hr != DIERR_NOTACQUIRED) return false;
		if (FAILED(InputDevice->Acquire())) return false;
	}
	return true;
}

KeyboardDevice::KeyboardDevice()
{
	ZeroMemory(m_Content, sizeof(m_Content));
}

KeyboardDevice::~KeyboardDevice()
{
}

bool KeyboardDevice::Init(HWND hwnd, InputInterface inputinterface)
{
	if (m_InputDevice.Init(hwnd, inputinterface, GUID_SysKeyboard, &c_dfDIKeyboard))
		return true;
	else
		return false;
}

bool KeyboardDevice::DeviceRead()
{
	if (m_InputDevice.DeviceRead((void*)(m_Content), sizeof(m_Content)))
		return true;
	else
		return false;
}

bool KeyboardDevice::IfPressDown(int b)
{
	return (m_Content[b] & 0x80);
}

MouseDevice::MouseDevice()
{
	m_Content = { 0 };
	ZeroMemory(&m_Content, sizeof(m_Content));
}

MouseDevice::~MouseDevice()
{
}

bool MouseDevice::Init(HWND hwnd, InputInterface inputinterface)
{
	if (m_InputDevice.Init(hwnd, inputinterface, GUID_SysMouse, &c_dfDIMouse))
		return true;
	else
		return false;
}

bool MouseDevice::DeviceRead()
{
	if (m_InputDevice.DeviceRead((void*)(&m_Content), sizeof(m_Content)))
		return true;
	else
		return false;
}

DIMOUSESTATE MouseDevice::GetMouseState()
{
	return m_Content;
}
