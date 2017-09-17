#pragma once
#include "stdafx.h"
#include "MemoryManager.h"

namespace SpaceGameEngine
{
	template<typename T>
	class AllocatorForSTL
	{
	public :
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef value_type const* const_pointer;
		typedef value_type const& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<typename _other>
		struct rebind
		{
			typedef AllocatorForSTL<T> other;
		};

		pointer address(reference x)
		{
			return pointer(&x);
		}
		const_pointer address(const_reference x)
		{
			return const_pointer(&x);
		}
		pointer allocate(size_type size, AllocatorForSTL<void>::const_pointer pHint = 0)
		{
			return pointer(MemoryManager::Allocate(size));
		}
		void deallocate(pointer p, size_type size)
		{
			MemoryManager::Free(p, size * sizeof(T));
		}
		void construct(pointer p, const_reference ref)
		{
			new (p) T(ref);
		}
		void destory(pointer p)
		{
			p->~T();
		}
	};
}