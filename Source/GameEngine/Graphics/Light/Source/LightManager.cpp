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
	m_DirectionLights.clear();
	m_DynamicLights.clear();
	m_FreeIndexList = Queue<unsigned int>();
	m_LightOctree.Release();
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void SpaceGameEngine::LightManager::InsertLight(LightEx * plight)
{
	if (plight->m_Mode == LightEx::LightMode::Normal&&
		plight->m_Content.m_Type != LightType::DirectionLight&&
		plight->m_Content.m_Type != LightType::UnkownLight)
	{
		if (m_FreeIndexList.empty())
		{
			m_Content.push_back(plight);
			m_LightOctree.InsertData(std::make_pair(plight->m_Content.m_Position, m_Content.size() - 1));
		}
		else
		{
			m_Content[m_FreeIndexList.front()] = plight;
			m_LightOctree.InsertData(std::make_pair(plight->m_Content.m_Position, m_FreeIndexList.front()));
			m_FreeIndexList.pop();
		}
	}
	else
	{
		if (plight->m_Content.m_Type != LightType::UnkownLight)
		{
			if (plight->m_Mode == LightEx::LightMode::Dynamic)
				m_DynamicLights.push_back(plight);
			else
				m_DirectionLights.push_back(plight);
		}
	}
}

void SpaceGameEngine::LightManager::DeleteLight(LightEx * plight)
{
	if (plight->m_Mode == LightEx::LightMode::Normal&&
		plight->m_Content.m_Type != LightType::DirectionLight&&
		plight->m_Content.m_Type != LightType::UnkownLight)
	{
		auto iter = std::find(m_Content.begin(), m_Content.end(), plight);
		if (iter == m_Content.end())
		{
			ThrowError("do not have this light");
		}
		m_FreeIndexList.push(iter - m_Content.begin());
		m_LightOctree.DeleteData(iter - m_Content.begin());
	}
	else
	{
		if (plight->m_Content.m_Type != LightType::UnkownLight)
		{
			if (plight->m_Mode == LightEx::LightMode::Dynamic)
				m_DynamicLights.erase(std::find(m_DynamicLights.begin(), m_DynamicLights.end(), plight));
			else
				m_DirectionLights.erase(std::find(m_DirectionLights.begin(), m_DirectionLights.end(), plight));
		}
	}
}

SpaceGameEngine::Vector<SpaceGameEngine::Light> SpaceGameEngine::LightManager::GetLight(TransformComponent * transform)
{
	if (m_LightOctree.IfInit() == false)
		m_LightOctree.BuildTree();

	return Vector<Light>();		//TODO:
}

void SpaceGameEngine::LightManager::SetAsMainManager()
{
	sm_pThis = this;
}

SpaceGameEngine::LightManager * SpaceGameEngine::LightManager::GetMainManager()
{
	return sm_pThis;
}
