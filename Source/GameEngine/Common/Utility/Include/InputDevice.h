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
		const DIMOUSESTATE& GetMouseState();									//��ȡ�������
		/*
		��ȡ���X���λ��
		����0Ϊ��
		С��0Ϊ��
		*/
		LONG GetMouseAnxisXMovement();
		/*
		��ȡ���Y���λ��
		����0Ϊ��
		С��0Ϊ��
		*/
		LONG GetMouseAnxisYMovement();
		bool IfLeftButtonPressDown();
		bool IfMiddleButtonPressDown();
		bool IfRightButtonPressDown();
	private:
		InputDevice m_InputDevice;
		DIMOUSESTATE m_Content;										//�������
	};

}