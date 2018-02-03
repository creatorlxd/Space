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
	Release();
}

void SpaceGameEngine::TextureComponent::Release()
{
	m_FileName = "";
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
	if (m_Mode&SingleMode)
	{
		auto ptex = ReadAssetFromFile<TextureAsset>(m_FileName);
		m_Content.push_back(const_cast<TextureForShader*>(&(ptex->m_Content)));
	}
}

void SpaceGameEngine::TextureComponent::Run(float DeltaTime)
{
	if (m_Mode&SingleMode)
	{
		Game::GetMainGame()->m_Window.GetEffectShader().m_pTextureTransformMatrix->SetMatrix(reinterpret_cast<float*>(&m_TextureTransformMatrix));
		Game::GetMainGame()->m_Window.GetEffectShader().m_pTexture->SetResource(m_Content[0]->m_pContent);
	}
}

void SpaceGameEngine::TextureComponent::SetTransformMatrix(const XMMATRIX & mat)
{
	m_TextureTransformMatrix = mat;
}
