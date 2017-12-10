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
#pragma once
#include "stdafx.h"
#include "Space.h"
#include "File.h"

namespace SpaceGameEngine
{
	struct Asset
	{
		virtual ~Asset();
		std::string m_FileName, m_TypeName;
		virtual void InitFromFile(const std::string& filename);
	};

	class AssetManager
	{
	public:
		~AssetManager();
		void Release();
		template<typename T>
		const Asset* NewAsset(const std::string& filename);
		bool AddAsset(Asset* pa);
		const Asset* GetAsset(const std::string& name);
	private:
		Map<std::string, Asset*> m_Content;
	};

	AssetManager& GetAssetManager();

	template<typename T>
	inline const Asset * AssetManager::NewAsset(const std::string & filename)
	{
		T* re = MemoryManager::New<T>();
		re->InitFromFile(filename);
		GetAssetManager().AddAsset((Asset*)re);
		return re;
	}

	template<typename T>
	const T* GetAsset(const std::string& filename)
	{
		auto rebuff = GetAssetManager().GetAsset(filename);
		if (rebuff)
		{
			return reinterpret_cast<const T*>(rebuff);
		}
		else
		{
			return GetAssetManager().NewAsset<T>(filename);
		}
	}
}