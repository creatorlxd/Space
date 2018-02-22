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
#include "../Include/MemoryManager.h"

namespace SpaceGameEngine
{
	size_t* MemoryManager::m_pBlockSizeContent = nullptr;
	Allocator* MemoryManager::m_pAllocators = nullptr;

	static const uint32_t g_BlockSizes[] = {
		// 4-increments
		4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
		52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,

		// 32-increments
		128, 160, 192, 224, 256, 288, 320, 352, 384,
		416, 448, 480, 512, 544, 576, 608, 640,

		// 64-increments
		704, 768, 832, 896, 960, 1024
	};
	static const uint32_t g_PageSize = 8192;
	static const uint32_t g_Alignment = 4;
	static const uint32_t g_NumBlockSizes = sizeof(g_BlockSizes) / sizeof(g_BlockSizes[0]);
	static const uint32_t g_MaxBlockSize = g_BlockSizes[g_NumBlockSizes - 1];
}

SpaceGameEngine::MemoryManager::MemoryManager()
{
	Init();
}

SpaceGameEngine::MemoryManager::~MemoryManager()
{
	delete[] m_pAllocators;
	delete[] m_pBlockSizeContent;
}

void SpaceGameEngine::MemoryManager::Init()
{
	static bool ifinitialized = false;
	if (!ifinitialized)
	{
		m_pBlockSizeContent = new size_t[g_MaxBlockSize + 1];

		size_t j = 0;
		for (size_t i = 0; i <= g_MaxBlockSize; i++)
		{
			if (i > g_BlockSizes[j]) j += 1;
			m_pBlockSizeContent[i] = j;
		}

		m_pAllocators = new Allocator[g_NumBlockSizes];
		for (size_t i = 0; i<g_NumBlockSizes; i++)
		{
			m_pAllocators[i].Reset(g_BlockSizes[i], g_PageSize, g_Alignment);
		}

		ifinitialized = true;
	}
}

void SpaceGameEngine::MemoryManager::Clear()
{
	GetMemoryManager();
	delete[] m_pAllocators;
	delete[] m_pBlockSizeContent;
}

SpaceGameEngine::Allocator* SpaceGameEngine::MemoryManager::FindAllocator(size_t size)
{
	if (size <= g_MaxBlockSize)
		return m_pAllocators+m_pBlockSizeContent[size];
	else
		return nullptr;
}

void* SpaceGameEngine::MemoryManager::Allocate(size_t size)
{
	GetMemoryManager();
	Allocator* pAlloc = FindAllocator(size);
	if (pAlloc)
		return pAlloc->Allocate();
	else
		return malloc(size);
}

void SpaceGameEngine::MemoryManager::Free(void* p, size_t size)
{
	GetMemoryManager();
	Allocator* pAlloc = FindAllocator(size);
	if (pAlloc)
		pAlloc->Free(p);
	else
		free(p);
}

SpaceGameEngine::MemoryManager & SpaceGameEngine::GetMemoryManager()
{
	static MemoryManager g_MemoryManager;
	return g_MemoryManager;
}