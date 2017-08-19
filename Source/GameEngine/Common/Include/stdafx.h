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

//-----------------------------------�����ļ��������֡�---------------------------------------
//	���������������������Ŀ��ļ�
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //����PlaySound����������ļ�
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"legacy_stdio_definitions.lib")
#pragma comment(lib,"D3DCompiler.lib")

using std::unique_ptr;
using namespace DirectX;