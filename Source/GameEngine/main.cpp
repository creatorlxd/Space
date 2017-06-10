#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"
#include "Space.h"
#include "Window.h"
#include "Memory.hpp"
#include "Camera.h"
#include "Graphics/Mesh/Include/Mesh.h"
#include "Game/Game/Include/Game.h"

//-----------------------------------�����ļ��������֡�---------------------------------------
//	���������������������Ŀ��ļ�
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")  //����PlaySound����������ļ�
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

Game g_Game;
Scene g_Scene;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_Game.Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	//write your init code here
	g_Game.m_Window.SetWindow();
	g_Game.SetScene(&g_Scene);
	//-------------------------
	g_Game.StartRunGame();
	return 0;
}