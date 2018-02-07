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
	}
}

void SpaceGameEngine::MaterialComponent::Start()
{
	if (m_Mode == SingleMode)
	{
		if (m_pFatherObject->GetRenderObject())
		{
			m_pFatherObject->GetRenderObject()->m_MaterialAsset.emplace_back();
			(m_pFatherObject->GetRenderObject()->m_MaterialAsset.end() - 1)->m_Content = (dynamic_cast<MaterialAsset*>(const_cast<Asset*>(m_pAsset)))->m_Content;
		}
		else
			ThrowError("物体对象不能没有RenderObject");
	}
}

void SpaceGameEngine::MaterialComponent::Run(float DeltaTime)
{
	
}

void SpaceGameEngine::MaterialComponent::Clear()
{
	if (m_Mode == SingleMode)
	{
		if (m_pFatherObject->GetRenderObject())
		{
			*m_pFatherObject->GetRenderObject()->m_MaterialAsset.rbegin() = MaterialAsset();
		}
	}
	Component::Clear();
}
