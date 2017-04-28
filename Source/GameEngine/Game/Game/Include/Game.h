#pragma once 
#include "stdafx.h"
#include "Window.h"
class Game				//顶层游戏类
{
public:
	Game();
	~Game();
	Game* const GetMainGame();	//获取当前的游戏类指针
public:
	Window m_Window;			//窗口
protected:
	static Game* sm_pThis;		//当前的游戏指针
};