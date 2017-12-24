/*
Copyright 2017 creatorlxd

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
#include "stdafx.h"
#include "../Error/Include/Error.h"

namespace SpaceGameEngine
{
	float GetDeltaTime();		//获取时间间隔

	struct Period				//时间段
	{
		std::chrono::steady_clock::time_point m_BeginTime;
		std::chrono::steady_clock::time_point m_EndTime;
		bool m_IfEnd = false;
		double m_Content = 0.00f;

		void Begin();
		void End();

		double GetContent();
	};
}