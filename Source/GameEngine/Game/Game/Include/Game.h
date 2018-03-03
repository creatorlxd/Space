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
	class Game				//顶层游戏类
	{
	public:
		Game();
		~Game();
		static Game* GetMainGame();	//获取当前的游戏类指针
		void SetAsMainGame();	//设置为主要的游戏

		void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);			//初始化
		static void Start();			//开始
		static void Run();				//每帧的运行

		void SetScene(Scene* ps);		//第一次设置场景
		void ChangeScene(Scene* ps);	//改变场景

		bool IfReadKeyboard();
		bool IfReadMouse();
		void ChangeIfReadKeyboard(bool b);
		void ChangeIfReadMouse(bool b);

		void ReadInputDevice();			//读取输入设备

		void StartRunGame();			//开始运行游戏

		static void ExitGame();			//退出游戏
	public:
		Window m_Window;			//窗口
		KeyboardDevice m_KeyboardDevice;	//键盘设备
		MouseDevice m_MouseDevice;			//鼠标设备
	private:
		static Game* sm_pThis;		//当前的游戏指针
		Scene* m_pScene;			//当前的场景
		InputInterface m_InputInterface;	//输入接口
		bool m_IfReadKeyboard;		//是否读取键盘
		bool m_IfReadMouse;			//是否读取鼠标

		static HINSTANCE sm_hInstance;
		static HINSTANCE sm_hPrevInstance;
		static LPSTR sm_lpCmdLine;
		static int sm_nShowCmd;
	};
}