/*
Copyright 2018 creatorlxd

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

GlobalVariable<Game> g_Game;
GlobalVariable<Scene> g_Scene;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_Game.Get().Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	//write your init code here
	g_Game.Get().m_Window.SetWindow();
	g_Game.Get().SetScene(&g_Scene.Get());
	//-------------------------
	g_Game.Get().StartRunGame();
	return 0;
}
