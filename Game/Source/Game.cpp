#include "stdafx.h"
#include "../Include/Game.h" 

Game* Game::sm_pThis = nullptr;

Game::Game()
{
	sm_pThis = this;
	m_pThis = this;
}

Game::~Game()
{
	sm_pThis = nullptr;
}

Game * const Game::GetMainGame()
{
	return sm_pThis;
}
