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

SpaceGameEngine::MemoryManager::MemoryManager()
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
}

SpaceGameEngine::MemoryManager::~MemoryManager()
{
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
	Allocator* pAlloc = GetMemoryManager().FindAllocator(size);
	if (pAlloc)
		return pAlloc->Allocate();
	else
		return malloc(size);
}

void SpaceGameEngine::MemoryManager::Free(void* p, size_t size)
{
	Allocator* pAlloc = GetMemoryManager().FindAllocator(size);
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