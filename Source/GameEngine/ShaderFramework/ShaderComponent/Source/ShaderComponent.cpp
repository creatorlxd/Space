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
#include "..\Include\ShaderComponent.h"

SpaceGameEngine::ShaderComponent::ShaderComponent()
{
	m_TypeName = STRING(ShaderComponent);
}

void SpaceGameEngine::ShaderComponent::InitFromFile(const String & filename, int mode)
{
	ReadAssetFromFile<DefaultEffectShaderAsset>(filename);
}

void SpaceGameEngine::ShaderComponent::Start()
{
	if (!m_pAsset->m_FileName.empty())
	{
		m_pFatherObject->GetRenderObject()->m_Shader.push_back(&dynamic_cast<DefaultEffectShaderAsset*>(const_cast<Asset*>(m_pAsset))->m_Content);
	}
}

void SpaceGameEngine::ShaderComponent::Copy(Component * pc)
{
	if (pc)
	{
		if (pc->GetTypeName() == m_TypeName)
		{
			m_pAsset = pc->GetAsset();
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
