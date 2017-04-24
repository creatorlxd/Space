#pragma once 
#include "stdafx.h"
#include "Window.h"
class Game
{
public:
	Game();
	~Game();
	Game* const GetMainGame();
public:
	Window m_Window;
protected:
	Game* m_pThis;
	static Game* sm_pThis;
};