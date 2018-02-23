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
#pragma once
#include "stdafx.h"
#include "Allocator.h"

namespace SpaceGameEngine
{
	const uint32_t g_BlockSizes[] = {
		// 4-increments
		4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
		52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,

		// 32-increments
		128, 160, 192, 224, 256, 288, 320, 352, 384,
		416, 448, 480, 512, 544, 576, 608, 640,

		// 64-increments
		704, 768, 832, 896, 960, 1024
	};
	const uint32_t g_PageSize = 8192;
	const uint32_t g_Alignment = 4;
	const uint32_t g_NumBlockSizes = sizeof(g_BlockSizes) / sizeof(g_BlockSizes[0]);
	const uint32_t g_MaxBlockSize = 1024;			//g_BlockSizes[g_NumBlockSizes - 1]

	class MemoryManager
	{
	public:
		template<typename T, typename... Arguments>
		static T* New(Arguments... parameters)
		{
			return new (Allocate(sizeof(T))) T(parameters...);
		}

		template<typename T>
		static T* NewArray(size_t size)
		{
			return new (Allocate(sizeof(T)*size)) T[size];
		}

		template<typename T>
		static void Delete(T *p)
		{
			reinterpret_cast<T*>(p)->~T();
			Free(p, sizeof(T));
		}

	public:
		friend MemoryManager& GetMemoryManager();
		
		~MemoryManager();

		static void* Allocate(size_t size);
		static void Free(void* p, size_t size);

	private:
		MemoryManager();
		size_t* m_pBlockSizeContent;	//the information of the size of block to find the Allcotor
		Allocator* m_pAllocators;

	private:
		Allocator* FindAllocator(size_t size);
	};
}