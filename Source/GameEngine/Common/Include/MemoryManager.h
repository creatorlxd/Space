#pragma once
#include "stdafx.h"
#include "Allocator.h"

namespace SpaceGameEngine
{
	class MemoryManager
	{
	public:
		template<typename T, typename... Arguments>
		static T* New(Arguments... parameters)
		{
			return new (Allocate(sizeof(T))) T(parameters...);
		}

		template<typename T>
		static void Delete(T *p)
		{
			reinterpret_cast<T*>(p)->~T();
			Free(p, sizeof(T));
		}

	public:
		MemoryManager();
		~MemoryManager();

		static void Init();
		static void Release();

		static void* Allocate(size_t size);
		static void Free(void* p, size_t size);

	private:
		static size_t* m_pBlockSizeContent;	//the information of the size of block to find the Allcotor
		static Allocator* m_pAllocators;

	private:
		static Allocator* FindAllocator(size_t size);
	};

	extern MemoryManager g_MemoryManager;
}