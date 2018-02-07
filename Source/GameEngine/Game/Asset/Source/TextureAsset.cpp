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
#include "../Include/TextureAsset.h"

SpaceGameEngine::TextureAsset::TextureAsset()
{
	m_TypeName = "TextureAsset";
}

SpaceGameEngine::TextureAsset::TextureAsset(const TextureAsset & ta)
{
	if (ta.m_FileName != "Null")
	{
		m_Content.Clear();
		InitFromFile(ta.m_FileName);
	}
}

void SpaceGameEngine::TextureAsset::InitFromFile(const std::string & filename)
{
	m_FileName = filename;

	CreateDDSTextureFromFile(SpaceEngineWindow->GetD3DDevice(), StringToWString(filename).c_str(), nullptr, &m_Content.m_pContent);
}

SpaceGameEngine::TextureAsset & SpaceGameEngine::TextureAsset::operator=(const TextureAsset & t)
{
	if (t.m_FileName != "Null")
	{
		m_Content.Clear();
		InitFromFile(t.m_FileName);
	}
	return *this;
}
