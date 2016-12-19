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

extern Window SpaceEngineWindow;

void Run(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	SpaceEngineWindow.SetWindow(L"SpaceEngineWindow", 800, 600);
	SpaceEngineWindow.InitWindow(hInstance,hPrevInstance,lpCmdLine,nShowCmd,Run);

	return 0;
}
void Run(HWND hwnd)
{
	SpaceEngineWindow.BeginPrint();

	SpaceEngineWindow.EndPrint();
}