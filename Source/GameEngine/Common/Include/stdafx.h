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
#include "ThirdParty/FX11/inc/d3dx11effect.h"

//-----------------------------------【库文件包含部分】---------------------------------------
//	描述：包含程序所依赖的库文件
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //调用PlaySound函数所需库文件
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

using std::unique_ptr;
using namespace DirectX;