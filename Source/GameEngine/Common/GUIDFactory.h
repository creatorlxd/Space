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
#pragma once
#include "MemoryManager/AllocatorForSTL.hpp"
#include "Error.h"

namespace SpaceGameEngine
{
	unsigned int HashString(const String& str);

	typedef unsigned int GUIDType;

	class GUIDFactory
	{
	public:
		bool IfGUIDHasBeenUsed(GUIDType c);
		/*
		相同的String返回相同的GUID
		*/
		GUIDType GetGUIDByString(const String& str);
		String GetStringByGUID(GUIDType c);
	private:
		Map<GUIDType, String> m_GUIDMap;
		Map<String, GUIDType> m_StringMap;
	};
}