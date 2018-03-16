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
#include "../Include/TextureComponent.h"

using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(TextureComponent);

SpaceGameEngine::TextureComponent::TextureComponent()
{
	m_TypeName = STRING(TextureComponent);
	m_FileName = "";

	m_TextureTransformMatrix = XMMatrixIdentity();
}

SpaceGameEngine::TextureComponent::~TextureComponent()
{
	
}

void SpaceGameEngine::TextureComponent::CleanUp()
{
	if (m_Mode == SingleMode)
	{
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				if (m_pFatherObject->GetRenderObject()->m_IfHaveTexture)
				{
					m_pFatherObject->GetRenderObject()->m_TextureAsset.rbegin()->first.m_Content.Release();
					m_pFatherObject->GetRenderObject()->m_TextureAsset.rbegin()->first.m_FileName = "";
				}
				m_pFatherObject->GetRenderObject()->m_IfHaveTexture = false;
			}
		}
	}
}

void SpaceGameEngine::TextureComponent::InitFromFile(const std::string & filename, int mode)
{
	m_Mode = mode;
	if (m_Mode&SingleMode)
	{
		m_FileName = filename;
	}
}

void SpaceGameEngine::TextureComponent::Start()
{
	if (m_Mode == SingleMode)
	{
		if (m_pFatherObject->GetRenderObject())
		{
			if (m_pFatherObject->GetRenderObject()->m_IfHaveTexture == false)
			{
				auto ptex = ReadAssetFromFile<TextureAsset>(m_FileName);
				m_Content = *ptex;
				if (m_pFatherObject->GetRenderObject()->m_TextureAsset.empty())
					m_pFatherObject->GetRenderObject()->m_TextureAsset.emplace_back();
				(m_pFatherObject->GetRenderObject()->m_TextureAsset.end() - 1)->first = m_Content;
				(m_pFatherObject->GetRenderObject()->m_TextureAsset.end() - 1)->second = m_TextureTransformMatrix;
				m_pFatherObject->GetRenderObject()->m_IfHaveTexture = true;
			}
		}
		else
			ThrowError("物体对象不能没有RenderObject");
	}
}

void SpaceGameEngine::TextureComponent::Run(float DeltaTime)
{
	if (m_Mode == SingleMode)
	{
		
	}
}

void SpaceGameEngine::TextureComponent::Copy(Component * pc)
{
	if (pc)
	{
		if (pc->GetTypeName() == m_TypeName)
		{
			m_Mode = pc->GetMode();
			m_pAsset = pc->GetAsset();
			auto src = dynamic_cast<TextureComponent*>(pc);
			m_Content = src->m_Content;
			m_TextureTransformMatrix = src->m_TextureTransformMatrix;
			if (m_Mode == SingleMode)
			{
				if (m_pFatherObject->GetRenderObject() && pc->GetFatherObject()->GetRenderObject())
				{
					if (SpaceEngineWindow->IfBegin())
					{
						if (m_pFatherObject->GetRenderObject()->m_TextureAsset.empty())
							m_pFatherObject->GetRenderObject()->m_TextureAsset.emplace_back();
						(*m_pFatherObject->GetRenderObject()->m_TextureAsset.rbegin()).first = m_Content;
						(*m_pFatherObject->GetRenderObject()->m_TextureAsset.rbegin()).second = m_TextureTransformMatrix;
						m_pFatherObject->GetRenderObject()->m_IfHaveTexture = true;
					}
					else
					{
						m_FileName = src->m_FileName;
					}
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

void SpaceGameEngine::TextureComponent::SetTexture(TextureAsset & ta)
{
	if (m_Mode == SingleMode)
	{
		m_Content = ta;
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				if (m_pFatherObject->GetRenderObject()->m_IfHaveTexture)
					(*m_pFatherObject->GetRenderObject()->m_TextureAsset.rbegin()).first = m_Content;
			}
		}
	}
}

void SpaceGameEngine::TextureComponent::SetTransformMatrix(const XMMATRIX & mat)
{
	if (m_Mode == SingleMode)
	{
		m_TextureTransformMatrix = mat;
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				if (m_pFatherObject->GetRenderObject()->m_IfHaveTexture)
					(m_pFatherObject->GetRenderObject()->m_TextureAsset.rbegin())->second = m_TextureTransformMatrix;
			}
		}
	}
}

void SpaceGameEngine::TextureComponent::AddTexture(const std::string& filename, XMMATRIX mat)
{
	if (m_Mode != SingleMode)
	{
		auto ta = GetAssetByFileName<TextureAsset>(filename);
		if (m_pFatherObject->GetRenderObject())
		{
			m_pFatherObject->GetRenderObject()->m_TextureAsset.emplace_back();
			(m_pFatherObject->GetRenderObject()->m_TextureAsset.end() - 1)->first = *ta;
			(m_pFatherObject->GetRenderObject()->m_TextureAsset.end() - 1)->second = mat;
		}
	}
}

TextureAsset SpaceGameEngine::TextureComponent::GetTexture()
{
	return m_Content;
}
