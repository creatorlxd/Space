#include "stdafx.h"
#include "Object.h"
#include "Space.h"
#include "Window.h"
#include "Memory.hpp"
#include "Camera.h"
#include "Graphics/Mesh/Include/Mesh.h"

//-----------------------------------【库文件包含部分】---------------------------------------
//	描述：包含程序所依赖的库文件
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //调用PlaySound函数所需库文件
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
void Run(HWND hwnd);
void Init(Window* window);
Window g_Window;
Camera g_Camera(*(g_Window.m_pKeyboardDevice),*(g_Window.m_pMouseDevice));
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//test
	ComponentManager m;
	Component* t=MeshComponent::NewComponent();
	//----
	g_Window.SetWindow();
	g_Window.InitWindow(hInstance, hPrevInstance,lpCmdLine,nShowCmd,Run,Init);
	return 0;
}
void Init(Window* window)
{
	//do somethine to init
	g_Camera.SetProjectionMatrix(D3DX_PI / 4, static_cast<float>(window->GetWindowWidth()), static_cast<float>(window->GetWindowHeight()));
}
void Run(HWND hwnd)
{
	SetMainWindow(&g_Window);
	g_Window.BeginPrint();
	g_Window.ReadInputDevice();
	g_Camera.Run(g_Window.GetD3DDevice());

	g_Window.EndPrint();
	if (g_Window.m_pKeyboardDevice->IfPressDown(DIK_ESCAPE))
	{
		g_Window.Release();
		PostQuitMessage(0);
	}
}