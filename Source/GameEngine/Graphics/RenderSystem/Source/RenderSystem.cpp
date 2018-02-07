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
#include "../Include/RenderSystem.h"

SpaceGameEngine::RenderSystem* SpaceGameEngine::RenderSystem::sm_pThis = nullptr;

SpaceGameEngine::RenderSystem::RenderSystem()
{
	sm_pThis = this;
	m_pGlobalOctree = nullptr;
}

SpaceGameEngine::RenderSystem::~RenderSystem()
{
	if (m_FreeIndexList.size() == m_Content.size())
	{

	}
	else
	{
		for (auto i : m_Content)
		{
			if (i)
				MemoryManager::Delete(i);
		}
	}
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void SpaceGameEngine::RenderSystem::Clear()
{
	if (m_FreeIndexList.size() == m_Content.size())
	{

	}
	else
	{
		for (auto i : m_Content)
		{
			if (i)
				MemoryManager::Delete(i);
		}
	}
	m_FreeIndexList = Queue<size_t>();
	m_pGlobalOctree = nullptr;
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

SpaceGameEngine::RenderObject * SpaceGameEngine::RenderSystem::NewRenderObject()
{
	RenderObject* re = MemoryManager::New<RenderObject>();

	if (m_FreeIndexList.empty())
	{
		m_Content.push_back(re);
	}
	else
	{
		size_t index = m_FreeIndexList.front();
		m_FreeIndexList.pop();
		m_Content[index] = re;
	}
	return re;
}

void SpaceGameEngine::RenderSystem::DeleteRenderObject(RenderObject * pro)
{
	if (pro != nullptr)
	{
		auto iter = std::find(m_Content.begin(), m_Content.end(), pro);
		if (iter != m_Content.end())
		{
			m_FreeIndexList.push(iter - m_Content.begin());
			(*iter)->Clear();
			MemoryManager::Delete(*iter);
			*iter = nullptr;
		}
		else
			ThrowError("do not have this RenderObject");
	}
	else
		ThrowError("can not delete nullptr");
}

void SpaceGameEngine::RenderSystem::Init()
{
	if (m_pGlobalOctree == nullptr)
		ThrowError("使用RenderSystem时，需先设置GlobalOctree");
	for (auto i : m_Content)
	{
		if (i != nullptr)
		{
			i->m_pGlobalOctree = m_pGlobalOctree;
			i->Init();
		}
	}
}

void SpaceGameEngine::RenderSystem::Render()
{
	for (auto i : m_Content)
	{
		if (i != nullptr&&i->m_IfRender)
			i->Render();
	}
}

SpaceGameEngine::RenderSystem * SpaceGameEngine::RenderSystem::GetMainRenderSystem()
{
	return sm_pThis;
}

void SpaceGameEngine::RenderSystem::SetAsMainRenderSystem()
{
	sm_pThis = this;
}
