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
#include "../Include/ComponentManager.h"
using namespace SpaceGameEngine;

ComponentManager* SpaceGameEngine::ComponentManager::sm_pThis = nullptr;
namespace SpaceGameEngine 
{
	ComponentFactoryManager g_ComponentFactoryManager;
}

SpaceGameEngine::ComponentManager::ComponentManager()
{
	sm_pThis = this;
}

SpaceGameEngine::ComponentManager::~ComponentManager()
{
	for (auto i : m_Content)
	{
		MemoryManager::Delete(i);
	}
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

ComponentManager * SpaceGameEngine::ComponentManager::GetMainManager()
{
	return sm_pThis;
}

void SpaceGameEngine::ComponentManager::SetAsMainManager()
{
	sm_pThis = this;
}

bool SpaceGameEngine::ComponentManager::DeleteComponent(Component * pc)
{
	for (unsigned int i = 0; i < m_Content.size(); i++)
	{
		if (m_Content[i] == pc)
		{
			MemoryManager::Delete(pc);
			m_FreeIndexList.push(i);
			m_Content[i] = nullptr;
			return true;
		}
	}
	return false;
}

void SpaceGameEngine::ComponentManager::Release()
{
	for (auto i : m_Content)
	{
		MemoryManager::Delete(i);
	}
	m_Content.clear();
	m_FreeIndexList = Queue<unsigned int>();
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void SpaceGameEngine::ComponentManager::DestoryComponent(Component * pc)
{
	pc->Release();
	if (sm_pThis)
		sm_pThis->DeleteComponent(pc);
	else
		ThrowError("当前未设定组件管理器");
}

Component * SpaceGameEngine::ComponentManager::NewComponentByName(const std::string & name)
{
	std::function<Component*(void)> f = g_ComponentFactoryManager.FindComponentFactory(name);
	return f();
}
