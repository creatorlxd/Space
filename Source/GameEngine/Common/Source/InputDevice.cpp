#include "stdafx.h"
#include "InputDevice.h"

InputInterface::~InputInterface()
{
	SafeRelease(m_pDirectInput);
}

bool InputInterface::Init(HINSTANCE hInstance)
{
	HRESULT r = DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	return SUCCEEDED(r);
}


LPDIRECTINPUT8 InputInterface::GetInterface()
{
	return m_pDirectInput;
}

InputDevice::~InputDevice()
{
	if (m_InputDevice) {
		m_InputDevice->Unacquire();
		SafeRelease(m_InputDevice);
	}
}

bool InputDevice::Init(HWND hwnd, InputInterface& inputinterface, REFGUID rguid, LPCDIDATAFORMAT lpdf)
{
	HRESULT r = inputinterface.GetInterface()->CreateDevice(rguid, (LPDIRECTINPUTDEVICE8W*)(&m_InputDevice), NULL);
	if (SUCCEEDED(r)) {
		m_InputDevice->SetDataFormat(lpdf);
		m_InputDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		return true;
	}
	else {
		return false;
	}
}

bool InputDevice::DeviceRead(void * pBuffer, long lSize)
{
	
	LPDIRECTINPUTDEVICE8A InputDevice = (LPDIRECTINPUTDEVICE8A)m_InputDevice;
	InputDevice->Poll();
	InputDevice->Acquire();          // 获取设备的控制权  
	HRESULT r = InputDevice->GetDeviceState(lSize, pBuffer);
	return SUCCEEDED(r);
}

KeyboardDevice::KeyboardDevice()
{
	ZeroMemory(m_Content, sizeof(m_Content));
}

KeyboardDevice::~KeyboardDevice()
{
}

bool KeyboardDevice::Init(HWND hwnd, InputInterface& inputinterface)
{
	return m_InputDevice.Init(hwnd, inputinterface, GUID_SysKeyboard, &c_dfDIKeyboard);
}

bool KeyboardDevice::DeviceRead()
{
	return m_InputDevice.DeviceRead((void*)(m_Content), sizeof(m_Content));
}

bool KeyboardDevice::IfPressDown(int b)
{
	return static_cast<bool>(m_Content[b] & 0x80);
}

MouseDevice::MouseDevice()
{
	m_Content = { 0 };
	ZeroMemory(&m_Content, sizeof(m_Content));
}

MouseDevice::~MouseDevice()
{
}

bool MouseDevice::Init(HWND hwnd, InputInterface& inputinterface)
{
	return m_InputDevice.Init(hwnd, inputinterface, GUID_SysMouse, &c_dfDIMouse);
}

bool MouseDevice::DeviceRead()
{
	return m_InputDevice.DeviceRead((void*)(&m_Content), sizeof(m_Content));
}

DIMOUSESTATE MouseDevice::GetMouseState()
{
	return m_Content;
}
