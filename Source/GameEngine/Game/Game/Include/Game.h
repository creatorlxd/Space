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
#include "Common/Utility/Include/Window.h"
#include "Common/Utility/Include/InputDevice.h"
#include "Game/Scene/Include/Scene.h"
#include "Game/Component/Include/Component.h"

namespace SpaceGameEngine
{
	class Game				//������Ϸ��
	{
	public:
		Game();
		~Game();
		static Game* GetMainGame();	//��ȡ��ǰ����Ϸ��ָ��
		void SetAsMainGame();	//����Ϊ��Ҫ����Ϸ

		void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);			//��ʼ��
		static void Start();			//��ʼ
		static void Run();				//ÿ֡������

		void SetScene(Scene* ps);		//��һ�����ó���
		void ChangeScene(Scene* ps);	//�ı䳡��

		bool IfReadKeyboard();
		bool IfReadMouse();
		void ChangeIfReadKeyboard(bool b);
		void ChangeIfReadMouse(bool b);

		void ReadInputDevice();			//��ȡ�����豸

		void StartRunGame();			//��ʼ������Ϸ

		static void ExitGame();			//�˳���Ϸ
	public:
		Window m_Window;			//����
		KeyboardDevice m_KeyboardDevice;	//�����豸
		MouseDevice m_MouseDevice;			//����豸
	private:
		static Game* sm_pThis;		//��ǰ����Ϸָ��
		Scene* m_pScene;			//��ǰ�ĳ���
		InputInterface m_InputInterface;	//����ӿ�
		bool m_IfReadKeyboard;		//�Ƿ��ȡ����
		bool m_IfReadMouse;			//�Ƿ��ȡ���

		static HINSTANCE sm_hInstance;
		static HINSTANCE sm_hPrevInstance;
		static LPSTR sm_lpCmdLine;
		static int sm_nShowCmd;
	};
}