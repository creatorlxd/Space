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
#include "stdafx.h"
#include "../Include/ComponentInformationManager.h"

namespace SpaceGameEngine
{
	ComponentInformationManager g_ComponentInformationManager;
}

SpaceGameEngine::ComponentInformation::ComponentInformation()
{
	ZeroMemory(this, sizeof(ComponentInformation));
}

SpaceGameEngine::ComponentInformation::ComponentInformation(const std::string & name, size_t size)
{
	m_Name = name;
	m_MemorySize = size;
}

SpaceGameEngine::ComponentInformation::ComponentInformation(const std::string & name, size_t size, std::function<Component*(void)> func)
{
	m_Name = name;
	m_MemorySize = size;
	m_FactoryFunction = func;
}

bool SpaceGameEngine::ComponentInformationManager::AddInformation(const ComponentInformation & info)
{
	auto iter = m_Content.find(info.m_Name);
	if (iter != m_Content.end())
	{
		ThrowError("this component class information already be recorded");
		return false;
	}
	else
	{
		m_Content.insert(std::make_pair(info.m_Name, info));
		return true;
	}
}

const SpaceGameEngine::ComponentInformation & SpaceGameEngine::ComponentInformationManager::GetInformation(const std::string & name)
{
	auto iter = m_Content.find(name);
	if (iter == m_Content.end())
	{
		ThrowError("do not have the information of this component class");
	}
	else
		return iter->second;
}
