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

SpaceGameEngine::RenderSystem::RenderSystem()
{

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
}

SpaceGameEngine::RenderObject * SpaceGameEngine::RenderSystem::NewRenderObject()
{
	RenderObject* re = new RenderObject();

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
			delete *iter;
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
	for (auto i : m_Content)
	{
		if (i != nullptr)
			i->Init();
	}
}

void SpaceGameEngine::RenderSystem::Render()
{
	for (auto i : m_Content)
	{
		if (i != nullptr)
			i->Render();
	}
}
