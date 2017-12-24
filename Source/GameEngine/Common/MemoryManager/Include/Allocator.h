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

namespace SpaceGameEngine
{
#ifndef ALIGN
#define ALIGN(x, a)         (((x) + ((a) - 1)) & ~((a) - 1))
#endif

	struct BlockHeader
	{
		BlockHeader* m_pNext = nullptr;
	};

	struct PageHeader
	{
		PageHeader* m_pNext = nullptr;
		BlockHeader* Blocks()
		{
			return reinterpret_cast<BlockHeader*>(this + 1);
		}
	};

	class Allocator
	{
	public:
		const static uint8_t PATTERN_ALIGH = 0xfc;
		const static uint8_t PATTERN_ALLOC = 0xfd;
		const static uint8_t PATTERN_FREE = 0xfe;

		Allocator();
		Allocator(size_t data_size, size_t page_size, size_t alignment);
		~Allocator();

		void Reset(size_t data_size, size_t page_size, size_t aligement);

		void* Allocate();
		void Free(void* p);
		void FreeAll();
	private:
#if defined(DEBUG) | defined(_DEBUG)
		void FillFreePage(PageHeader* pPage);
		void FillFreeBlock(BlockHeader* pBlock);
		void FillAllocatedBlock(BlockHeader* pBlock);
#endif
		BlockHeader* NextBlock(BlockHeader* pBlock);

		BlockHeader* m_pFreeBlockList;
		PageHeader* m_pPageList;

		//以下皆为内存大小
		size_t m_DataSize;		//memory size of data
		size_t m_PageSize;		//^^^^^^^^^^^^^^^^^^^
		size_t m_AlignmentSize;	//BlockSize+AlignmentSize=alignment=2^n
		size_t m_BlockSize;
		uint32_t m_BlocksPerPage;

		//以下皆为数量
		uint32_t m_Pages;
		uint32_t m_Blocks;
		uint32_t m_FreeBlocks;

		Allocator(const Allocator& clone);
		Allocator& operator = (const Allocator& rhs);
	};
}