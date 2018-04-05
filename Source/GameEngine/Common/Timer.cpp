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
#include "Timer.h"

SpaceGameEngine::TimePoint SpaceGameEngine::Timer::GetNowTimePoint()
{
	return std::chrono::steady_clock::now();
}

SpaceGameEngine::Timer::Timer()
{
	m_IfStop = false;
}

float SpaceGameEngine::Timer::GetTotalTime()
{
	return SecondsType((m_IfStop ? (m_StopTimePoint - m_PausedTime) : (m_CurrentTimePoint - m_PausedTime)) - m_InitTimePoint).count();
}

float SpaceGameEngine::Timer::GetDeltaTime()
{
	return m_DeltaTime.count();
}

float SpaceGameEngine::Timer::GetPausedTime()
{
	return m_PausedTime.count();
}

void SpaceGameEngine::Timer::Init()
{
	m_CurrentTimePoint = GetNowTimePoint();
	m_InitTimePoint = m_CurrentTimePoint;
	m_PreviousTimePoint = m_CurrentTimePoint;
	m_StartTimePoint = TimePoint();
	m_StopTimePoint = TimePoint();

	m_DeltaTime = SecondsType(0.0f);
	m_PausedTime = SecondsType(0.0f);

	m_IfStop = false;
}

void SpaceGameEngine::Timer::Start()
{
	m_StartTimePoint = GetNowTimePoint();

	if (m_IfStop)
	{
		m_PausedTime += (m_StartTimePoint - m_StopTimePoint);
		m_PreviousTimePoint = m_StartTimePoint;
		m_IfStop = false;
	}
}

void SpaceGameEngine::Timer::Stop()
{
	if (!m_IfStop)
	{
		m_StopTimePoint = GetNowTimePoint();
		m_IfStop = true;
	}
}

void SpaceGameEngine::Timer::Tick()
{
	if (m_IfStop)
	{
		m_DeltaTime = SecondsType(0);
		return;
	}
	m_CurrentTimePoint = GetNowTimePoint();
	m_DeltaTime = m_CurrentTimePoint - m_PreviousTimePoint;
	m_PreviousTimePoint = m_CurrentTimePoint;
}
