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

#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"legacy_stdio_definitions.lib")
#pragma comment(lib,"D3DCompiler.lib")

#ifdef _WIN64
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "FX11/Bin/x64/Effects11d.lib")
#else
#pragma comment(lib, "FX11/Bin/x64/Effects11.lib")
#endif
#else
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "FX11/Bin/x86/Effects11d.lib")
#else
#pragma comment(lib, "FX11/Bin/x86/Effects11.lib")
#endif
#endif

#ifdef _WIN64
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "tinyxml2/lib/x64/Debug/tinyxml2.lib")
#else
#pragma comment(lib, "tinyxml2/lib/x64/Release/tinyxml2.lib")
#endif
#else
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "tinyxml2/lib/x86/Debug/tinyxml2.lib")
#else
#pragma comment(lib, "tinyxml2/lib/x86/Release/tinyxml2.lib")
#endif
#endif

#ifdef _WIN64
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "DirectXTex/lib/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/lib/x64/Release/DirectXTex.lib")
#endif
#else
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "DirectXTex/lib/x86/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/lib/x86/Release/DirectXTex.lib")
#endif
#endif