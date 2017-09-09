#include "stdafx.h"
#include "MemoryManager.h"

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

	SpaceGameEngine::MemoryManager g_MemoryManager;
}

SpaceGameEngine::MemoryManager::MemoryManager()
{
	Init();
}

SpaceGameEngine::MemoryManager::~MemoryManager()
{
	Release();
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
			if (i >= g_BlockSizes[j]) j += 1;
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

void SpaceGameEngine::MemoryManager::Release()
{
	delete[] m_pAllocators;
	delete[] m_pBlockSizeContent;
}

SpaceGameEngine::Allocator* SpaceGameEngine::MemoryManager::FindAllocator(size_t size)
{
	if (size <= g_MaxBlockSize)
		return &m_pAllocators[m_pBlockSizeContent[size]];
	else
		return nullptr;
}

void* SpaceGameEngine::MemoryManager::Allocate(size_t size)
{
	Allocator* pAlloc = FindAllocator(size);
	if (pAlloc)
		return pAlloc->Allocate();
	else
		return malloc(size);
}

void SpaceGameEngine::MemoryManager::Free(void* p, size_t size)
{
	Allocator* pAlloc = FindAllocator(size);
	if (pAlloc)
		pAlloc->Free(p);
	else
		free(p);
}