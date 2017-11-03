/*
Copyright 2017 creatorlxd

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
