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
#include "Def.h"

namespace SpaceGameEngine
{
	using SecondsType = std::chrono::duration<float, std::ratio<1>>;
	using TimePoint = std::chrono::steady_clock::time_point;

	class Timer
	{
	public:
		static TimePoint GetNowTimePoint();
		
		Timer();

		/*
		Get Total Time since the Timer Init except the time when Timer stop
		*/
		float GetTotalTime();
		float GetDeltaTime();
		float GetPausedTime();

		/*
		Init Timer also	can Reset the Timer
		*/
		void Init();
		void Start();
		void Stop();
		/*
		must call Tick() every frame
		*/
		void Tick();
	private:
		TimePoint m_CurrentTimePoint;
		TimePoint m_PreviousTimePoint;

		SecondsType	m_DeltaTime;
		SecondsType m_PausedTime;

		TimePoint m_InitTimePoint;
		TimePoint m_StartTimePoint;
		TimePoint m_StopTimePoint;

		bool m_IfStop;
	};
}