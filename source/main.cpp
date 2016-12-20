#include "stdafx.h"
#include "object.h"
#include "Space.h"
#include "Window.h"

//-----------------------------------【库文件包含部分】---------------------------------------
//	描述：包含程序所依赖的库文件
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //调用PlaySound函数所需库文件
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
void Run(HWND hwnd);
Window g_window;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_window.SetWindow();
	g_window.InitWindow(hInstance, hPrevInstance,lpCmdLine,nShowCmd,Run);
	return 0;
}
void Run(HWND hwnd)
{
	SetMainWindow(&g_window);
	g_window.BeginPrint();

	g_window.EndPrint();
}