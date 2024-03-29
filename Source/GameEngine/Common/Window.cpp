﻿/*
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
	m_IconFileName = "";
	m_WindowWidth = 0;
	m_WindowHeight = 0;
	m_WindowTitle = "";
	m_WindowPosition = m_DefaultWindowPosition;		//default value
	m_IfShowCursor = true;
	m_FPSLimit = 360;		//default value
	auto pConfigTable = GetDefaultConfigFile().QueryConfigTable("Window");
	if (pConfigTable)
	{
		auto pbuffer = pConfigTable->QueryConfigValue("IconFileName");
		if (pbuffer)
			m_IconFileName = pbuffer->AsString();
		
		pbuffer = pConfigTable->QueryConfigValue("WindowWidth");
		if (pbuffer)
			m_WindowWidth = pbuffer->AsInt();
		
		pbuffer = pConfigTable->QueryConfigValue("WindowHeight");
		if (pbuffer)
			m_WindowHeight = pbuffer->AsInt();
		
		pbuffer = pConfigTable->QueryConfigValue("WindowTitle");
		if (pbuffer)
			m_WindowTitle = pbuffer->AsString();

		pbuffer = pConfigTable->QueryConfigValue("WindowPositionX");
		if (pbuffer)
			m_WindowPosition.first = pbuffer->AsInt();

		pbuffer = pConfigTable->QueryConfigValue("WindowPositionY");
		if (pbuffer)
			m_WindowPosition.second = pbuffer->AsInt();

		pbuffer = pConfigTable->QueryConfigValue("IfShowCursor");
		if (pbuffer)
			m_IfShowCursor = pbuffer->AsBool();

		pbuffer = pConfigTable->QueryConfigValue("FPSLimit");
		if (pbuffer)
			m_FPSLimit = pbuffer->AsInt();
	}

	ShowCursor(m_IfShowCursor);

	m_IfHaveBegun = false;
}

SpaceGameEngine::Window::~Window()
{
	SUBJECT_NOTIFY(Window, m_RespondRelease, *this);
}

HWND SpaceGameEngine::Window::GetHwnd()
{
	return m_Hwnd;
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
	GetClientRect(m_Hwnd, &r);
	m_WindowWidth = abs(r.right - r.left);
	m_WindowHeight = abs(r.bottom - r.top);
}

std::pair<int, int> SpaceGameEngine::Window::GetWindowPosition()
{
	if (m_IfHaveBegun)
	{
		RECT r;
		GetClientRect(m_Hwnd, &r);
		m_WindowPosition = std::pair<int, int>(r.left, r.top);
	}
	return m_WindowPosition;
}

void SpaceGameEngine::Window::SetWindowPosition(int x, int y)
{
	if (m_IfHaveBegun)
	{
		RECT r;
		GetWindowRect(m_Hwnd, &r);
		SetWindowPos(m_Hwnd, HWND_TOPMOST, r.left + x - m_WindowPosition.first, r.top + y - m_WindowPosition.second, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
	}
	m_WindowPosition = std::make_pair(x, y);
}

void SpaceGameEngine::Window::SetWindowSize(int x, int y)
{
	if (m_IfHaveBegun)
	{
		RECT r;
		SetRect(&r, 0, 0, x, y);
		AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(m_Hwnd, HWND_TOPMOST, 0, 0, r.right - r.left, r.bottom - r.top, SWP_SHOWWINDOW | SWP_NOMOVE);
	}
	m_WindowWidth = x;
	m_WindowHeight = y;
	if (m_IfHaveBegun)
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

bool SpaceGameEngine::Window::IfHaveBegun()
{
	return m_IfHaveBegun;
}

SpaceGameEngine::Timer & SpaceGameEngine::Window::GetTimer()
{
	return m_Timer;
}

void SpaceGameEngine::Window::StartRun(HINSTANCE hInstance)
{
	m_Timer.Init();

	//init window
	WNDCLASSEX WndClass = { 0 };
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WindowProcess;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = (HICON)LoadImage(NULL, StringToWString(m_IconFileName).c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = L"SpaceGameEngineWindow";
	if (!RegisterClassEx(&WndClass))
	{
		THROW_ERROR("can not register window");
		return;
	}
	RECT r;
	SetRect(&r, m_WindowPosition.first, m_WindowPosition.second, m_WindowPosition.first + m_WindowWidth, m_WindowPosition.second + m_WindowHeight);
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
	m_Hwnd = CreateWindow(WndClass.lpszClassName, StringToWString(m_WindowTitle).c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL);
	MoveWindow(m_Hwnd, r.left, r.top, r.right - r.left, r.bottom - r.top, true);
	ShowWindow(m_Hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_Hwnd);

	SUBJECT_NOTIFY(Window, m_RespondInit, *this);
	m_IfHaveBegun = true;
	SUBJECT_NOTIFY(Window, m_RespondStart, *this);

	MSG msg = { 0 };
	double time_limit = 1.0 / (double)m_FPSLimit;
	TimePoint time_pre = std::chrono::steady_clock::now();
	TimePoint time_now;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			time_now = std::chrono::steady_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(time_now - time_pre);

			if (time_span.count() >= time_limit)
			{
				m_Timer.Tick();
				SUBJECT_NOTIFY(Window, m_RespondRun, *this);
				time_pre = time_now;
			}
			else
			{
				Sleep(1000 * (time_limit - time_span.count()));
			}
		}
	}
	UnregisterClass(WndClass.lpszClassName, hInstance);
}

void SpaceGameEngine::Window::Resize()
{
	SUBJECT_NOTIFY(Window, m_RespondResize, *this);
}

LRESULT SpaceGameEngine::Window::WindowProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ASSERT(Window::GetCurrentObject(), "Must have a current window object");
	switch (message)
	{
	case WM_PAINT:
		ValidateRect(Window::GetCurrentObject()->m_Hwnd, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		Window::GetCurrentObject()->m_WindowWidth = LOWORD(lParam);
		Window::GetCurrentObject()->m_WindowHeight = HIWORD(lParam);
		if (LOWORD(lParam) != 0 && HIWORD(lParam) != 0)
			Window::GetCurrentObject()->Resize();
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
	return NULL;
}
