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
#include "Window.h"

SpaceGameEngine::Window::Window() :CurrentObject<Window>(this)
{
	m_Hwnd = NULL;
	m_WindowWidth = 0;
	m_WindowHeight = 0;
	m_WindowTitle = "";
	m_WindowPosition = m_DefaultWindowPosition;		//default value
	m_IfShowCursor = true;
	m_FPSLimit = 360;		//default value
	if (GetDefaultConfigFile().IfHaveConfigTable("Window"))
	{
		auto WindowConfig = GetDefaultConfigFile().GetConfigTable("Window");
		if (WindowConfig.IfHaveConfigValue("WindowWidth"))
			m_WindowWidth = WindowConfig.GetConfigValue("WindowWidth").AsInt();
		if (WindowConfig.IfHaveConfigValue("WindowHeight"))
			m_WindowHeight = WindowConfig.GetConfigValue("WindowHeight").AsInt();
		if (WindowConfig.IfHaveConfigValue("WindowTitle"))
			m_WindowTitle = WindowConfig.GetConfigValue("WindowTitle").AsString();
		if (WindowConfig.IfHaveConfigValue("WindowPositionX"))
			m_WindowPosition.first = WindowConfig.GetConfigValue("WindowPositionX").AsInt();
		if (WindowConfig.IfHaveConfigValue("WindowPositionY"))
			m_WindowPosition.second = WindowConfig.GetConfigValue("WindowPositionY").AsInt();
		if (WindowConfig.IfHaveConfigValue("IfShowCursor"))
			m_IfShowCursor = WindowConfig.GetConfigValue("IfShowCursor").AsBool();
		if (WindowConfig.IfHaveConfigValue("FPSLimit"))
			m_FPSLimit = WindowConfig.GetConfigValue("FPSLimit").AsInt();
	}

	ShowCursor(m_IfShowCursor);

	m_IfBegin = false;

	m_InitAction = [&]()->void {};
	m_RunAction = [&]()->void {};
	m_ResizeAction = [&]()->void {};
	m_ReleaseAction = [&]()->void {};
}

SpaceGameEngine::Window::~Window()
{
	m_ReleaseAction();
}

DWORD SpaceGameEngine::Window::GetWindowWidth()
{
	return m_WindowWidth;
}

DWORD SpaceGameEngine::Window::GetWindowHeight()
{
	return m_WindowHeight;
}

void SpaceGameEngine::Window::ChangeIfShowCursor(bool b)
{
	if (m_IfShowCursor == b)
	{
		return;
	}
	else
	{
		m_IfShowCursor = b;
		ShowCursor(b);
	}
}

bool SpaceGameEngine::Window::GetIfShowCursor()
{
	return m_IfShowCursor;
}

void SpaceGameEngine::Window::SetCursorPosition(int x, int y)
{
	auto pos = GetWindowPosition();
	SetCursorPos(pos.first + x, pos.second + y);
}

std::pair<int, int> SpaceGameEngine::Window::GetCursorPosition()
{
	POINT p;
	GetCursorPos(&p);
	GetWindowPosition();
	return std::pair<int, int>(p.x - m_WindowPosition.first, p.y - m_WindowPosition.second);
}

void SpaceGameEngine::Window::UpdateWindowSize()
{
	RECT r;
	GetWindowRect(m_Hwnd, &r);
	m_WindowWidth = abs(r.right - r.left);
	m_WindowHeight = abs(r.bottom - r.top);
}

std::pair<int, int> SpaceGameEngine::Window::GetWindowPosition()
{
	if (m_IfBegin)
	{
		RECT r;
		GetWindowRect(m_Hwnd, &r);
		m_WindowPosition = std::pair<int, int>(r.left, r.top);
	}
	return m_WindowPosition;
}

void SpaceGameEngine::Window::SetWindowPosition(int x, int y)
{
	if (m_IfBegin)
		SetWindowPos(m_Hwnd, HWND_TOPMOST, x, y, m_WindowWidth, m_WindowHeight, SWP_SHOWWINDOW);
	m_WindowPosition = std::make_pair(x, y);
}

void SpaceGameEngine::Window::SetWindowSize(int x, int y)
{
	if (m_IfBegin)
	{
		SetWindowPos(m_Hwnd, HWND_TOPMOST, m_WindowPosition.first, m_WindowPosition.second, x, y, SWP_SHOWWINDOW);
	}
	m_WindowWidth = x;
	m_WindowHeight = y;
	if (m_IfBegin)
	{
		Resize();
	}
}

void SpaceGameEngine::Window::SetWindowTitle(const String & title)
{
	m_WindowTitle = title;
}

SpaceGameEngine::String SpaceGameEngine::Window::GetWindowTitle()
{
	return m_WindowTitle;
}

void SpaceGameEngine::Window::SetFPSLimit(unsigned int limit)
{
	m_FPSLimit = limit;
}

unsigned int SpaceGameEngine::Window::GetFPSLimit()
{
	return m_FPSLimit;
}

bool SpaceGameEngine::Window::GetIfBegin()
{
	return m_IfBegin;
}

void SpaceGameEngine::Window::SetInitAction(const std::function<void()>& func)
{
	m_InitAction = func;
}

void SpaceGameEngine::Window::SetRunAction(const std::function<void()>& func)
{
	m_RunAction = func;
}

void SpaceGameEngine::Window::SetResizeAction(const std::function<void()>& func)
{
	m_ResizeAction = func;
}

void SpaceGameEngine::Window::SetReleaseAction(const std::function<void()>& func)
{
	m_ReleaseAction = func;
}

void SpaceGameEngine::Window::StartRun(HINSTANCE hInstance)
{
	m_InitAction();
}

void SpaceGameEngine::Window::Resize()
{
	m_ResizeAction();
}
