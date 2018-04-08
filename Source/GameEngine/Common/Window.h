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
#include "ConfigFile.h"
#include "CurrentObject.hpp"

namespace SpaceGameEngine
{
	class Window :public CurrentObject<Window>
	{
	public:
		Window();
		~Window();

		void Resize();

		DWORD GetWindowWidth();							//获取窗口宽度
		DWORD GetWindowHeight();						//获取窗口高度
		void ChangeIfShowCursor(bool b);				//改变是否显示鼠标
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
	private:
		HWND m_Hwnd;									//窗口句柄
		DWORD m_WindowWidth;								//窗口宽度
		DWORD m_WindowHeight;								//窗口高度
		String m_WindowTitle;							//窗口标题
		std::pair<int, int> m_WindowPosition;			//窗口位置
		inline static const std::pair<int, int> m_DefaultWindowPosition = { 250 ,80 };
		bool m_IfShowCursor;						//是否显示鼠标
		bool m_IfBegin;							//游戏是否已开始
		unsigned int m_FPSLimit;

		std::function<void()> m_InitAction;
		std::function<void()> m_RunAction;
		std::function<void()> m_ResizeAction;
		std::function<void()> m_ReleaseAction;
	};
}