#include "stdafx.h"
#include "SpaceGameEngine.h"

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
