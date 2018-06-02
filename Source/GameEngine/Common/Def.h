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
// Standard Library
#include <utility>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>

namespace SpaceGameEngine
{
#define GLOBALCONST extern const __declspec(selectany)

#define STRING(str) #str

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILEW__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

	template <typename _T> void SafeRelease(_T& p) { if (p) { p->Release(); p = nullptr; } }

	template<bool b,typename T,typename U>
	struct TypeIf
	{

	};

	template<typename T,typename U>
	struct TypeIf<true, T, U>
	{
		using Result = T;
	};

	template<typename T, typename U>
	struct TypeIf<false, T, U>
	{
		using Result = U;
	};

	/*
	删除类型的修饰符
	不适用于函数类型
	*/
	template<typename T,bool ifsame=std::is_pointer<typename std::decay<T>::type>::value>
	struct Decay {};

	/*
	删除类型的修饰符
	不适用于函数类型
	*/
	template<typename T>
	struct Decay<T,true>
	{
		using Result = typename Decay<typename std::remove_pointer<typename std::decay<T>::type>::type>::Result;
	};

	/*
	删除类型的修饰符
	不适用于函数类型
	*/
	template<typename T>
	struct Decay<T, false>
	{
		using Result = typename std::decay<T>::type;
	};
}
