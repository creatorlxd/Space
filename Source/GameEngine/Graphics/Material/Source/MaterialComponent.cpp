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

SpaceGameEngine::MaterialComponent::MaterialComponent()
{
	m_TypeName = "MaterialComponent";
}

SpaceGameEngine::MaterialComponent::~MaterialComponent()
{
	
}

void SpaceGameEngine::MaterialComponent::InitFromFile(const String & filename, int mode)
{
	m_Mode = mode;
	if (m_Mode == SingleMode)
	{
		const MaterialAsset* ma = ReadAssetFromFile<MaterialAsset>(filename);
		m_Content = ma->m_Content;
	}
}

void SpaceGameEngine::MaterialComponent::Start()
{
	if (m_Mode == SingleMode)
	{
		if (m_pFatherObject->GetRenderObject())
		{
			if (m_pFatherObject->GetRenderObject()->m_IfHaveMaterial == false)
			{
				if (m_pFatherObject->GetRenderObject()->m_MaterialAsset.empty())
					m_pFatherObject->GetRenderObject()->m_MaterialAsset.emplace_back();
				(m_pFatherObject->GetRenderObject()->m_MaterialAsset.end() - 1)->m_Content = m_Content;
				m_pFatherObject->GetRenderObject()->m_IfHaveMaterial = true;
			}
		}
		else
			ThrowError("物体对象不能没有RenderObject");
	}
}

void SpaceGameEngine::MaterialComponent::Run(float DeltaTime)
{
	
}

void SpaceGameEngine::MaterialComponent::CleanUp()
{
	if (m_Mode == SingleMode)
	{
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				if(m_pFatherObject->GetRenderObject()->m_IfHaveMaterial)
					*m_pFatherObject->GetRenderObject()->m_MaterialAsset.rbegin() = MaterialAsset();
				m_pFatherObject->GetRenderObject()->m_IfHaveMaterial = false;
			}
		}
	}
}

void SpaceGameEngine::MaterialComponent::Copy(Component * pc)
{
	if (pc)
	{
		if (pc->GetTypeName() == m_TypeName)
		{
			m_Mode = pc->GetMode();
			m_pAsset = pc->GetAsset();
			auto src = dynamic_cast<MaterialComponent*>(pc);
			m_Content = src->m_Content;
			if (m_Mode == SingleMode)
			{
				if (m_pFatherObject->GetRenderObject() && pc->GetFatherObject()->GetRenderObject())
				{
					if (m_pFatherObject->GetRenderObject()->m_MaterialAsset.empty())
						m_pFatherObject->GetRenderObject()->m_MaterialAsset.emplace_back();
					(*m_pFatherObject->GetRenderObject()->m_MaterialAsset.rbegin()).m_Content = m_Content;
					m_pFatherObject->GetRenderObject()->m_IfHaveMaterial = true;
				}
			}
		}
		else
		{
			ThrowError("dst's type must equal to src's type");
			return;
		}
	}
	else
		ThrowError("component can not be nullptr");
}

void SpaceGameEngine::MaterialComponent::SetMaterial(const Material & ma)
{
	if (m_Mode == SingleMode)
	{
		m_Content = ma;
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				if (m_pFatherObject->GetRenderObject()->m_IfHaveMaterial)
					(*m_pFatherObject->GetRenderObject()->m_MaterialAsset.rbegin()).m_Content = m_Content;
			}
		}
	}
}

Material SpaceGameEngine::MaterialComponent::GetMaterial()
{
	return m_Content;
}
