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
#include "../Include/LightManager.h"

SpaceGameEngine::LightEx::LightEx()
{
	m_IfOn = true;
	m_Mode = LightMode::Normal;
}

SpaceGameEngine::LightManager* SpaceGameEngine::LightManager::sm_pThis = nullptr;

SpaceGameEngine::LightManager::LightManager()
{
	sm_pThis = this;
}

SpaceGameEngine::LightManager::~LightManager()
{
	Release();
}

void SpaceGameEngine::LightManager::Release()
{
	m_Content.clear();
	m_FreeIndexList = Queue<unsigned int>();
	m_LightingOctree.Release();
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void SpaceGameEngine::LightManager::StartRun()
{
	m_LightingOctree.BuildTree();
}

void SpaceGameEngine::LightManager::AddLight(LightEx * plight)
{
	//TODO:
}

void SpaceGameEngine::LightManager::DeleteLight(LightEx * plight)
{
	//TODO:
}

void SpaceGameEngine::LightManager::AddLighting(Lighting * plg)
{
	size_t index = -1;
	if (m_FreeIndexList.empty())
	{
		m_Content.push_back(plg);
		index = m_Content.size() - 1;
	}
	else
	{
		m_Content[m_FreeIndexList.front()] = plg;
		index = m_FreeIndexList.front();
		m_FreeIndexList.pop();
	}
	m_LightingOctree.InsertData(std::make_pair(plg->m_Position, index));
}

void SpaceGameEngine::LightManager::DeleteLighting(Lighting * plg)
{
	auto iter = std::find(m_Content.begin(), m_Content.end(), plg);
	if (iter != m_Content.end())
	{
		m_FreeIndexList.push(iter - m_Content.begin());
		*iter = nullptr;
		m_LightingOctree.DeleteData(iter - m_Content.begin());
	}
	else
	{
		ThrowError("do not have this Lighting");
	}
}

void SpaceGameEngine::LightManager::SetAsMainManager()
{
	sm_pThis = this;
}

SpaceGameEngine::LightManager * SpaceGameEngine::LightManager::GetMainManager()
{
	return sm_pThis;
}
