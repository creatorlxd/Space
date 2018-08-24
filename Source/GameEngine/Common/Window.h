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
#include <Windows.h>
#include "ConfigFile.h"
#include "CurrentObject.hpp"
#include "Timer.h"
#include "Connection.hpp"

namespace SpaceGameEngine
{
	/*
	窗口类
	注：该窗口类的一切关于size和position的操作都是针对客户区的。
	*/
	class Window :public CurrentObject<Window>, public Data<Window>
	{
	public:
		Window();
		virtual ~Window();

		HWND GetHwnd();
		DWORD GetWindowWidth();							//获取窗口宽度
		DWORD GetWindowHeight();						//获取窗口高度
		void ChangeIfShowCursor(bool b);				//改变是否显示鼠标
		bool GetIfShowCursor();
		/*
		设置鼠标位置
		接受相对位置
		*/
		void SetCursorPosition(int x, int y);
		/*
		获取鼠标位置
		返回相对位置
		*/
		std::pair<int, int> GetCursorPosition();
		void UpdateWindowSize();						//重新获取窗口大小(StartRun后)
		std::pair<int, int> GetWindowPosition();		//获取窗口位置

		void SetWindowPosition(int x, int y);			//设置窗口位置
		void SetWindowSize(int x, int y);				//设置窗口大小
		void SetWindowTitle(const String& title);
		String GetWindowTitle();
		void SetFPSLimit(unsigned int limit);
		unsigned int GetFPSLimit();

		bool IfBegin();
		Timer& GetTimer();

		void StartRun(HINSTANCE hInstance);
		void Resize();
	private:
		static LRESULT CALLBACK WindowProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		HWND m_Hwnd;									//窗口句柄
		String m_IconFileName;
		DWORD m_WindowWidth;								//窗口客户区宽度
		DWORD m_WindowHeight;								//窗口客户区高度
		String m_WindowTitle;							//窗口标题
		std::pair<int, int> m_WindowPosition;			//窗口客户区位置
		inline static const std::pair<int, int> m_DefaultWindowPosition = { 250 ,80 };
		bool m_IfShowCursor;						//是否显示鼠标
		bool m_IfHaveBegun;							//游戏是否已开始
		unsigned int m_FPSLimit;

		Timer m_Timer;
	};

	CONNECTION_BEGIN(Window)
		OnNotifyAction<void()> m_OnInitAction;
		OnNotifyAction<void()> m_OnStartAction;
		OnNotifyAction<void()> m_OnRunAction;
		OnNotifyAction<void()> m_OnResizeAction;
		OnNotifyAction<void()> m_OnReleaseAction;
	CONNECTION_END;
}