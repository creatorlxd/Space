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
#include "../Include/TimeTool.h"

float SpaceGameEngine::GetDeltaTime()
{
	static float TimeNow = 0.00f;
	static float TimeBuffer = 0.00f;
	static float DeltaTime = 0.00f;
	if (TimeNow == 0.00f)
	{
		TimeNow = timeGetTime()*0.001f;
		return SpaceGameEngine::GetDeltaTime();
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		DeltaTime = TimeBuffer - TimeNow;
		TimeNow = timeGetTime()*0.001f;
		return DeltaTime;
	}
}

void SpaceGameEngine::Period::Begin()
{
	m_BeginTime = std::chrono::steady_clock::now();
}

void SpaceGameEngine::Period::End()
{
	m_EndTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(m_EndTime - m_BeginTime);
	m_Content = time_span.count();
	m_IfEnd = true;
}

double SpaceGameEngine::Period::GetContent()
{
	if (!m_IfEnd)
	{
		ThrowError("can not get content before invoke End()");
	}
	return m_Content;
}
