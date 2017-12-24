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