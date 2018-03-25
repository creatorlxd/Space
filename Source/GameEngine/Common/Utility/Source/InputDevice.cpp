/*
Copyright 2018 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "stdafx.h"
#include "../Include/InputDevice.h"

using namespace SpaceGameEngine;

SpaceGameEngine::InputInterface::~InputInterface()
{
	SafeRelease(m_pDirectInput);
}

bool SpaceGameEngine::InputInterface::Init(HINSTANCE hInstance)
{
	HRESULT r = DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	return SUCCEEDED(r);
}


LPDIRECTINPUT8 SpaceGameEngine::InputInterface::GetInterface()
{
	return m_pDirectInput;
}

SpaceGameEngine::InputDevice::~InputDevice()
{
	if (m_InputDevice) {
		m_InputDevice->Unacquire();
		SafeRelease(m_InputDevice);
	}
}

bool SpaceGameEngine::InputDevice::Init(HWND hwnd, InputInterface& inputinterface, REFGUID rguid, LPCDIDATAFORMAT lpdf)
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

bool SpaceGameEngine::InputDevice::DeviceRead(void * pBuffer, long lSize)
{
	
	LPDIRECTINPUTDEVICE8A InputDevice = (LPDIRECTINPUTDEVICE8A)m_InputDevice;
	InputDevice->Poll();
	InputDevice->Acquire();          // ��ȡ�豸�Ŀ���Ȩ  
	HRESULT r = InputDevice->GetDeviceState(lSize, pBuffer);
	return SUCCEEDED(r);
}

SpaceGameEngine::KeyboardDevice::KeyboardDevice()
{
	memset(m_Content, false, sizeof(m_Content));
}

SpaceGameEngine::KeyboardDevice::~KeyboardDevice()
{
}

bool SpaceGameEngine::KeyboardDevice::Init(HWND hwnd, InputInterface& inputinterface)
{
	return m_InputDevice.Init(hwnd, inputinterface, GUID_SysKeyboard, &c_dfDIKeyboard);
}

bool SpaceGameEngine::KeyboardDevice::DeviceRead()
{
	memcpy(m_LastContent, m_Content, sizeof(m_Content));
	return m_InputDevice.DeviceRead((void*)(m_Content), sizeof(m_Content));
}

bool SpaceGameEngine::KeyboardDevice::IfPress(int b)
{
	return static_cast<bool>(m_Content[b] & 0x80);
}

bool SpaceGameEngine::KeyboardDevice::IfPressDown(int b)
{
	return (!IfLastPress(b)&&IfPress(b));
}

bool SpaceGameEngine::KeyboardDevice::IfPressUp(int b)
{
	return (IfLastPress(b) && !IfPress(b));
}

bool SpaceGameEngine::KeyboardDevice::IfLastPress(int b)
{
	return static_cast<bool>(m_LastContent[b] & 0x80);
}

SpaceGameEngine::MouseDevice::MouseDevice()
{
	m_Content = { 0 };
	ZeroMemory(&m_Content, sizeof(m_Content));
	memset(m_Content.rgbButtons, false, sizeof(m_Content.rgbButtons));
}

SpaceGameEngine::MouseDevice::~MouseDevice()
{
}

bool SpaceGameEngine::MouseDevice::Init(HWND hwnd, InputInterface& inputinterface)
{
	return m_InputDevice.Init(hwnd, inputinterface, GUID_SysMouse, &c_dfDIMouse);
}

bool SpaceGameEngine::MouseDevice::DeviceRead()
{
	memcpy(m_LastState, m_Content.rgbButtons, sizeof(m_Content.rgbButtons));
	return m_InputDevice.DeviceRead((void*)(&m_Content), sizeof(m_Content));
}

const DIMOUSESTATE& SpaceGameEngine::MouseDevice::GetMouseState()
{
	return m_Content;
}

LONG SpaceGameEngine::MouseDevice::GetMouseAnxisXMovement()
{
	return GetMouseState().lX;
}

LONG SpaceGameEngine::MouseDevice::GetMouseAnxisYMovement()
{
	return GetMouseState().lY;
}

bool SpaceGameEngine::MouseDevice::IfLeftButtonPress()
{
	return GetMouseState().rgbButtons[0] & 0x80;
}

bool SpaceGameEngine::MouseDevice::IfMiddleButtonPress()
{
	return GetMouseState().rgbButtons[2] & 0x80;
}

bool SpaceGameEngine::MouseDevice::IfRightButtonPress()
{
	return GetMouseState().rgbButtons[1] & 0x80;
}

bool SpaceGameEngine::MouseDevice::IfLeftButtonPressDown()
{
	return (!IfLastLeftButtonPress() && IfLeftButtonPress());
}

bool SpaceGameEngine::MouseDevice::IfMiddleButtonPressDown()
{
	return (!IfLastMiddleButtonPress() && IfMiddleButtonPress());
}

bool SpaceGameEngine::MouseDevice::IfRightButtonPressDown()
{
	return (!IfLastRightButtonPress() && IfRightButtonPress());
}

bool SpaceGameEngine::MouseDevice::IfLeftButtonPressUp()
{
	return (IfLastLeftButtonPress() && !IfLeftButtonPress());
}

bool SpaceGameEngine::MouseDevice::IfMiddleButtonPressUp()
{
	return (IfLastMiddleButtonPress() && !IfMiddleButtonPress());
}

bool SpaceGameEngine::MouseDevice::IfRightButtonPressUp()
{
	return (IfLastRightButtonPress() && !IfRightButtonPress());
}

bool SpaceGameEngine::MouseDevice::IfLastLeftButtonPress()
{
	return m_LastState[0] & 0x80;
}

bool SpaceGameEngine::MouseDevice::IfLastMiddleButtonPress()
{
	return m_LastState[2] & 0x80;
}

bool SpaceGameEngine::MouseDevice::IfLastRightButtonPress()
{
	return m_LastState[1] & 0x80;
}
