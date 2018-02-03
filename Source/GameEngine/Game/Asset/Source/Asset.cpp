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
#include "../Include/Asset.h"

SpaceGameEngine::Asset::Asset()
{
	m_TypeName = "NullAsset";
	m_FileName = "Null";
}

SpaceGameEngine::Asset::~Asset()
{

}

void SpaceGameEngine::Asset::InitFromFile(const std::string & filename)
{
	m_FileName = filename;
}

SpaceGameEngine::AssetManager::~AssetManager()
{
	Release();
}

void SpaceGameEngine::AssetManager::Release()
{
	for (const auto& i : m_Content)
	{
		MemoryManager::Delete(i.second);
	}
}

bool SpaceGameEngine::AssetManager::AddAsset(Asset * pa)
{
	if (pa == nullptr)
	{
		ThrowError("the pointer can not be nullptr");
		return false;
	}
	auto iter = m_Content.find(pa->m_FileName);
	if (iter != m_Content.end())
	{
		ThrowError("have already have this asset");
		return false;
	}
	m_Content.insert(std::make_pair(pa->m_FileName, pa));
	return true;
}

const SpaceGameEngine::Asset * SpaceGameEngine::AssetManager::GetAsset(const std::string & name)
{
	auto iter = m_Content.find(name);
	if (iter != m_Content.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

SpaceGameEngine::AssetManager & SpaceGameEngine::GetAssetManager()
{
	static AssetManager g_AssetManager;
	return g_AssetManager;
}
