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
#pragma once
#include "Space.h"
#include <Windows.h>
#include <dinput.h>

namespace SpaceGameEngine
{
#define KEY(str) DIK_##str

	class InputInterface		//D3DInput接口
	{
	public:
		InputInterface()
			: m_pDirectInput(nullptr) {}
		~InputInterface();
		InputInterface(const InputInterface&) = delete;
		bool Init(HINSTANCE hInstance);	//初始化
		LPDIRECTINPUT8 GetInterface();	//获取接口
	private:
		LPDIRECTINPUT8 m_pDirectInput;	//D3DInput接口
	};

	class InputDevice		//输入设备
	{
	public:
		InputDevice()
			: m_InputDevice(nullptr) {}
		~InputDevice();
		bool Init(HWND hwnd, InputInterface& inputinterface, REFGUID rguid, LPCDIDATAFORMAT lpdf);	//初始化
		bool DeviceRead(void* pBuffer, long lSize);					//读取设备内容
	private:
		LPDIRECTINPUTDEVICE m_InputDevice;	//输入设备
	};

	class KeyboardDevice	//键盘设备
	{
	public:
		KeyboardDevice();
		~KeyboardDevice();
		bool Init(HWND hwnd, InputInterface& inputinterface);			//初始化
		bool DeviceRead();											//读取设备
		bool IfPressDown(int b);									//判断是否按下某个键
	private:
		InputDevice m_InputDevice;
		char m_Content[256];										//键盘内容
	};

	class MouseDevice		//鼠标设备
	{
	public:
		MouseDevice();
		~MouseDevice();
		bool Init(HWND hwnd, InputInterface& inputinterface);			//初始化
		bool DeviceRead();												//读取设备
		const DIMOUSESTATE& GetMouseState();									//获取鼠标内容
		/*
		获取鼠标X轴的位移
		大于0为右
		小于0为左
		*/
		LONG GetMouseAnxisXMovement();
		/*
		获取鼠标Y轴的位移
		大于0为下
		小于0为上
		*/
		LONG GetMouseAnxisYMovement();
		bool IfLeftButtonPressDown();
		bool IfMiddleButtonPressDown();
		bool IfRightButtonPressDown();
	private:
		InputDevice m_InputDevice;
		DIMOUSESTATE m_Content;										//鼠标内容
	};

}