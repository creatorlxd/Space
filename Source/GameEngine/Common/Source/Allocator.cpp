#include "stdafx.h"
#include "Allocator.h"

SpaceGameEngine::Allocator::Allocator()
{
	m_pFreeBlockList = nullptr;
	m_pPageList = nullptr;
	m_DataSize = 0;
	m_PageSize = 0;
	m_AlignmentSize = 0;
	m_BlockSize = 0;
	m_BlocksPerPage = 0;
}

SpaceGameEngine::Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment) :m_pFreeBlockList(nullptr), m_pPageList(nullptr)
{
	Allocator();
	Reset(data_size, page_size, alignment);
}

SpaceGameEngine::Allocator::~Allocator()
{
	FreeAll();
}

void SpaceGameEngine::Allocator::Reset(size_t data_size, size_t page_size, size_t alignment)
{
	FreeAll();

	m_DataSize = data_size;
	m_PageSize = page_size;

	size_t minmal_size = max(m_DataSize, sizeof(BlockHeader));

#if defined(_DEBUG) | defined (DEBUG)
	assert(alignment > 0 && ((alignment & (alignment - 1))) == 0);
#endif

	m_BlockSize = ALIGN(minmal_size, alignment);
	m_AlignmentSize = m_BlockSize - minmal_size;
	m_BlocksPerPage = (m_PageSize - sizeof(PageHeader)) / m_BlockSize;
}

void* SpaceGameEngine::Allocator::Allocate()
{
	if (!m_pFreeBlockList)
	{
		PageHeader* pNewPage = reinterpret_cast<PageHeader*>(new uint8_t[m_PageSize]());
		m_Pages += 1;
		m_Blocks += m_BlocksPerPage;
		m_FreeBlocks += m_BlocksPerPage;

#if defined(_DEBUG)
		FillFreePage(pNewPage);
#endif

		if (m_pPageList)
		{
			pNewPage->m_pNext = m_pPageList;
		}

		m_pPageList = pNewPage;

		BlockHeader* pBlock = pNewPage->Blocks();

		//link blocks in page
		for (uint32_t i = 0; i<m_BlocksPerPage; i++)
		{
			pBlock->m_pNext = NextBlock(pBlock);
			pBlock = NextBlock(pBlock);
		}
		pBlock->m_pNext = nullptr;

		m_pFreeBlockList = pNewPage->Blocks();
	}

	BlockHeader* freeBlock = m_pFreeBlockList;
	m_pFreeBlockList = m_pFreeBlockList->m_pNext;
	m_FreeBlocks -= 1;

#if defined(_DEBUG) | defined(DEBUG)
	FillAllocatedBlock(freeBlock);
#endif

	return reinterpret_cast<void*>(freeBlock);
}

void SpaceGameEngine::Allocator::Free(void* p)
{
	BlockHeader* block = reinterpret_cast<BlockHeader*>(p);

#if defined(_DEBUG) | defined(DEBUG)
	FillFreeBlock(block);
#endif

	block->m_pNext = m_pFreeBlockList;
	m_pFreeBlockList = block;
	m_FreeBlocks += 1;
}

void SpaceGameEngine::Allocator::FreeAll()
{
	PageHeader* pPage = m_pPageList;
	while (pPage)
	{
		PageHeader* _p = pPage;
		pPage = pPage->m_pNext;

		delete[] reinterpret_cast<uint8_t*>(_p);
	}

	m_pPageList = nullptr;
	m_pFreeBlockList = nullptr;

	m_Blocks = 0;
	m_FreeBlocks = 0;
	m_Pages = 0;
}
#if defined(DEBUG) | defined(_DEBUG)
void SpaceGameEngine::Allocator::FillFreePage(PageHeader *pPage)
{
	pPage->m_pNext = nullptr;

	BlockHeader *pBlock = pPage->Blocks();
	for (uint32_t i = 0; i < m_BlocksPerPage; i++)
	{
		FillFreeBlock(pBlock);
		pBlock = NextBlock(pBlock);
	}
}

void SpaceGameEngine::Allocator::FillFreeBlock(BlockHeader *pBlock)
{
	memset(pBlock, PATTERN_FREE, m_BlockSize - m_AlignmentSize);

	memset(reinterpret_cast<uint8_t*>(pBlock) + m_BlockSize - m_AlignmentSize, PATTERN_ALIGH, m_AlignmentSize);
}

void SpaceGameEngine::Allocator::FillAllocatedBlock(BlockHeader *pBlock)
{
	std::memset(pBlock, PATTERN_ALLOC, m_BlockSize - m_AlignmentSize);

	std::memset(reinterpret_cast<uint8_t*>(pBlock) + m_BlockSize - m_AlignmentSize, PATTERN_ALIGH, m_AlignmentSize);
}
#endif

SpaceGameEngine::BlockHeader* SpaceGameEngine::Allocator::NextBlock(BlockHeader* pBlock)
{
	return reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(pBlock) + m_BlockSize);
}

SpaceGameEngine::Allocator & SpaceGameEngine::Allocator::operator=(const Allocator & rhs)
{
	FreeAll();
	memcpy(this, &rhs, sizeof(Allocator));
	return *this;
}