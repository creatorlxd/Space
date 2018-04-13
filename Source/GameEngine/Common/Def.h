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
// Windows
#include <Windows.h>
// DirectX
#include <dinput.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <dxerr/dxerr.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
// Standard Library
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <memory>
#include <xutility>
#include <cstring>
#include <type_traits>
#include <map>
#include <algorithm>
#include <new>
#include <codecvt>
#include <queue>
#include <stack>
#include <functional>
#include <cstdint>
#include <cstddef>
#include <direct.h>
#include <io.h>
#include <forward_list>
#include <set>
#include <chrono>
#include <unordered_map>
#include <tchar.h>

#include "ThirdParty/FX11/inc/d3dx11effect.h"
#include "ThirdParty/tinyxml2/include/tinyxml2.h"
#include "ThirdParty/DirectXTex/include/DirectXTex.h"

using std::unique_ptr;
using namespace DirectX;

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
}
