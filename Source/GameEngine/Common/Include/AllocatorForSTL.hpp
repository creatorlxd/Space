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
		typedef T *pointer;
		typedef T &reference;
		typedef const T *const_pointer;
		typedef const T &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<typename _other>
		struct rebind
		{
			typedef AllocatorForSTL<_other> other;
		};

		pointer address(reference x)
		{
			return pointer(&x);
		}
		const_pointer address(const_reference x)
		{
			return const_pointer(&x);
		}
		pointer allocate(size_type size)
		{
			return reinterpret_cast<pointer>(MemoryManager::Allocate(size*sizeof(T)));
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
		size_type max_size() const
		{
			return size_type(UINT_MAX / sizeof(T));
		}
		bool operator==(const AllocatorForSTL &rhs)
		{
			return true;
		}
		bool operator!=(const AllocatorForSTL &rhs)
		{
			return !operator==(rhs);
		}
		AllocatorForSTL()
		{

		}
		template<typename U>
		AllocatorForSTL(AllocatorForSTL<U>& alloc)
		{

		}
		AllocatorForSTL(AllocatorForSTL& alloc)
		{

		}
	};

	template<typename T>
	using Vector = std::vector<T, AllocatorForSTL<T> >;

	template<typename T,typename U>
	using Map = std::map<T,U, std::less<T>,AllocatorForSTL<std::pair<const T,U> > >;

}