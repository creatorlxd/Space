#include "stdafx.h"
#include "Object.h"
#include "Space.h"
#include "Window.h"
#include "Memory.hpp"

//-----------------------------------�����ļ��������֡�---------------------------------------
//	���������������������Ŀ��ļ�
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //����PlaySound����������ļ�
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
void Run(HWND hwnd);
void Init(Window* window);
Window g_window;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_window.SetWindow();
	g_window.InitWindow(hInstance, hPrevInstance,lpCmdLine,nShowCmd,Run,Init);
	return 0;
}
void Init(Window* window)
{
	//do somethine to init
}
void Run(HWND hwnd)
{
	SetMainWindow(&g_window);
	g_window.BeginPrint();

	g_window.EndPrint();
}