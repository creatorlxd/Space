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
#include "../Include/LightComponent.h"

using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(LightComponent);

SpaceGameEngine::LightComponent::LightComponent()
{
	m_TypeName = "LightComponent";
	m_pTransform = nullptr;
}

SpaceGameEngine::LightComponent::~LightComponent()
{
	Release();
}

void SpaceGameEngine::LightComponent::InitFromFile(const std::string & filename, int mode)
{
	m_Mode = mode;
	auto lightasset = ReadAssetFromFile<LightAsset>(filename);
	m_Content.m_Content = lightasset->m_Content;
	if (mode == StaticMode)
		m_Content.m_Mode = LightEx::LightMode::Normal;
	else if (mode == DynamicMode)
		m_Content.m_Mode = LightEx::LightMode::Dynamic;
}

void SpaceGameEngine::LightComponent::Start()
{
	Scene::GetMainScene()->m_LightManager.InsertLight(&m_Content);
}

void SpaceGameEngine::LightComponent::Run(float DeltaTime)
{
	if (m_Mode == StaticMode)
	{
		if (m_pFatherObject->GetComponentByMessage(Event::PositionChange) ||
			m_pFatherObject->GetComponentByMessage(Event::RotationChange))
		{
			m_Content.m_Content.m_Position = m_pTransform->GetPosition();
			m_Content.m_Content.m_Direction = GetDirectionByRotation(m_pTransform->GetRotation());
			Scene::GetMainScene()->m_LightManager.UpdateLight(&m_Content);
		}
	}
}

void SpaceGameEngine::LightComponent::Release()
{
	if (m_Mode != 0)
	{
		Scene::GetMainScene()->m_LightManager.DeleteLight(&m_Content);
		m_Mode = 0;
	}
	m_pTransform = nullptr;
}

bool SpaceGameEngine::LightComponent::IfOn()
{
	return m_Content.m_IfOn;
}

void SpaceGameEngine::LightComponent::ChangeIfOn(bool b)
{
	m_Content.m_IfOn = b;
}
