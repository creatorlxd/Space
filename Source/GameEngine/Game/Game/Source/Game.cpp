#include "stdafx.h"
#include "../Include/Game.h" 

Game* Game::sm_pThis = nullptr;
HINSTANCE Game::sm_hInstance=NULL;
HINSTANCE Game::sm_hPrevInstance = NULL;
LPSTR Game::sm_lpCmdLine = NULL;
int Game::sm_nShowCmd=0;

Game::Game()
{
	sm_pThis = this;
	m_pScene = nullptr;
	m_IfReadKeyboard = true;
	m_IfReadMouse = true;
}

Game::~Game()
{
	Release();
}

Game * Game::GetMainGame()
{
	return sm_pThis;
}

void Game::SetAsMainGame()
{
	sm_pThis = this;
}

void Game::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	m_InputInterface.Init(hInstance);

	sm_hInstance = hInstance;
	sm_hPrevInstance = hPrevInstance;
	sm_lpCmdLine = lpCmdLine;
	sm_nShowCmd = nShowCmd;

	auto window = Window::GetMainWindow();
	if (window)
	{
		m_KeyboardDevice.Init(window->GetHwnd(), m_InputInterface);
		m_MouseDevice.Init(window->GetHwnd(), m_InputInterface);
	}
}

void Game::Start()
{
	if (!sm_pThis)
	{
		ThrowError(L"需要先定义一个Game");
	}
	if (sm_pThis->m_pScene)
	{
		sm_pThis->m_pScene->Start();
	}
}

void Game::Run()
{
	if (!sm_pThis)
	{
		ThrowError(L"需要先定义一个Game");
	}
	auto deltatime = GetDeltaTime();
	sm_pThis->ReadInputDevice();
	if (sm_pThis->m_pScene)
	{
		sm_pThis->m_Window.BeginPrint();
		sm_pThis->m_pScene->Run(deltatime);
		sm_pThis->m_Window.EndPrint();
	}
}

void Game::Release()
{
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void Game::SetScene(Scene * ps)
{
	if(m_pScene==nullptr)
		m_pScene = ps;
	else
	{
		ThrowError(L"只能在设置第一个场景时使用SetScene");
	}
}

void Game::ChangeScene(Scene * ps)
{
	m_pScene = ps;
	ps->Start();
}

bool Game::IfReadKeyboard()
{
	return m_IfReadKeyboard;
}

bool Game::IfReadMouse()
{
	return m_IfReadMouse;
}

void Game::ChangeIfReadKeyboard(bool b)
{
	m_IfReadKeyboard = b;
}

void Game::ChangeIfReadMouse(bool b)
{
	m_IfReadMouse = b;
}

void Game::ReadInputDevice()
{
	if (m_IfReadKeyboard)
		m_KeyboardDevice.DeviceRead();
	if (m_IfReadMouse)
		m_MouseDevice.DeviceRead();
}

void Game::StartRunGame()
{
	m_Window.InitWindow(sm_hInstance, sm_hPrevInstance, sm_lpCmdLine, sm_nShowCmd, Run, Start);
}
