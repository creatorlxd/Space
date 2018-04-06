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
#include "GUIDFactory.h"

unsigned int SpaceGameEngine::HashString(const String & str)
{
	std::hash<String> sh;
	return static_cast<unsigned int>(sh(str));
}

bool SpaceGameEngine::GUIDFactory::IfGUIDHasBeenUsed(GUIDType c)
{
	auto iter = m_Content.find(c);
	if (iter == m_Content.end())
		return false;
	else
		return true;
}

SpaceGameEngine::GUIDType SpaceGameEngine::GUIDFactory::GetGUIDByString(const String & str)
{
	GUIDType c = HashString(str);
	while (IfGUIDHasBeenUsed(c))
	{
		c += 1;
	}
	m_Content.insert(std::make_pair(c, str));
	return c;
}

SpaceGameEngine::String SpaceGameEngine::GUIDFactory::GetStringByGUID(GUIDType c)
{
	auto iter = m_Content.find(c);
	if (iter != m_Content.end())
		return iter->second;
	else
		return "";
}
