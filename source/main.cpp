#include "stdafx.h"
#include "object.h"
#include "Space.h"
#include "Window.h"

//-----------------------------------�����ļ��������֡�---------------------------------------
//	���������������������Ŀ��ļ�
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //����PlaySound����������ļ�
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