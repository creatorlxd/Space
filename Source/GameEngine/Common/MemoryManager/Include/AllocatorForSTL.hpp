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
		void destroy(pointer p)
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
		AllocatorForSTL(const AllocatorForSTL<U>& alloc)
		{

		}
		AllocatorForSTL(const AllocatorForSTL& alloc)
		{

		}
	};

	template<typename T>
	using Vector = std::vector<T, AllocatorForSTL<T> >;

	template<typename T,typename U>
	using Map = std::map<T,U, std::less<T>,AllocatorForSTL<std::pair<const T,U> > >;

	template<typename T,typename U>
	using HashMap = std::unordered_map < T, U, std::hash<T>, std::equal_to<T>, AllocatorForSTL<std::pair<const T, U>>>;

	template<typename T>
	using Deque = std::deque<T, AllocatorForSTL<T> >;

	template<typename T>
	using Queue = std::queue<T, Deque<T> >;
	
	template<typename T>
	using Stack = std::stack<T, Deque<T> >;

	template<typename T>
	using ForwardList = std::forward_list<T, AllocatorForSTL<T> >;

	template<typename T, typename _Pr = std::less<T> >
	using Set = std::set<T, _Pr, AllocatorForSTL<T> >;
}