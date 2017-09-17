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

		pointer address(reference x);
		const_pointer address(const_reference x);
		point allocate(size_t size, AllocatorForSTL<void>::const_pointer pHint = 0);
		void deallocate(pointer p, size_type size);
		void construct(pointer p, const_reference ref);
		void destory(pointer p);
	};
	template<typename T>
	inline pointer AllocatorForSTL<T>::address(reference x)
	{
		return pointer(&x);
	}
	template<typename T>
	inline const_pointer AllocatorForSTL<T>::address(const_reference x)
	{
		return const_pointer(&x);
	}
	template<typename T>
	inline point AllocatorForSTL<T>::allocate(size_t size, AllocatorForSTL<void>::const_pointer pHint)
	{
		return point(MemoryManager::Allocate(size));
	}
	template<typename T>
	inline void AllocatorForSTL<T>::deallocate(pointer p, size_type size)
	{
		MemoryManager::Free(p, size*sizeof(T));
	}
	template<typename T>
	inline void AllocatorForSTL<T>::construct(pointer p, const_reference ref)
	{
		new (p) T(ref);
	}
	template<typename T>
	inline void AllocatorForSTL<T>::destory(pointer p)
	{
		p->~T();
	}
}