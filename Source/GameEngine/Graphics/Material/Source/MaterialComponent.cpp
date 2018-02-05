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
#include "../Include/MaterialComponent.h"

using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(MaterialComponent);

SpaceGameEngine::MaterialComponent::MaterialComponent()
{
	m_TypeName = "MaterialComponent";
}

SpaceGameEngine::MaterialComponent::~MaterialComponent()
{

}

void SpaceGameEngine::MaterialComponent::InitFromFile(const std::string & filename, int mode)
{
	m_Mode = mode;
	if (m_Mode == SingleMode)
	{
		const MaterialAsset* ma = ReadAssetFromFile<MaterialAsset>(filename);
		m_Content.clear();
		m_Content.push_back(ma->m_Content);
	}
}

void SpaceGameEngine::MaterialComponent::Run(float DeltaTime)
{
	if (m_Mode == SingleMode)
	{
		Game::GetMainGame()->m_Window.GetEffectShader().m_pMaterial->SetRawValue(&m_Content[0], 0, sizeof(m_Content[0]));
	}
}

void SpaceGameEngine::MaterialComponent::Clear()
{
	m_Content.clear();
}

void SpaceGameEngine::MaterialComponent::AddMaterial(const Material & m)
{
	m_Content.push_back(m);
}
