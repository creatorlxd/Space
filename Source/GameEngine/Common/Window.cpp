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
	m_WindowWidth = 0;
	m_WindowHeight = 0;
	m_WindowTitle = "";
	m_WindowPosition = m_DefaultWindowPosition;		//default value
	m_IfShowCursor = true;
	m_IfBegin = false;
	m_FPSLimit = 360;		//default value

	m_InitAction = [&]()->void {};
	m_RunAction = [&]()->void {};
	m_ResizeAction = [&]()->void {};
	m_ReleaseAction = [&]()->void {};
}

SpaceGameEngine::Window::~Window()
{
	m_ReleaseAction();
}