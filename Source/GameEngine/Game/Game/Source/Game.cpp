#include "stdafx.h"
#include "../Include/Game.h" 
using namespace SpaceGameEngine;

Game* SpaceGameEngine::Game::sm_pThis = nullptr;
HINSTANCE SpaceGameEngine::Game::sm_hInstance=NULL;
HINSTANCE SpaceGameEngine::Game::sm_hPrevInstance = NULL;
LPSTR SpaceGameEngine::Game::sm_lpCmdLine = NULL;
int SpaceGameEngine::Game::sm_nShowCmd=0;

SpaceGameEngine::Game::Game()
{
	sm_pThis = this;
	m_pScene = nullptr;
	m_IfReadKeyboard = true;
	m_IfReadMouse = true;
}

SpaceGameEngine::Game::~Game()
{
	Release();
}

Game * SpaceGameEngine::Game::GetMainGame()
{
	return sm_pThis;
}

void SpaceGameEngine::Game::SetAsMainGame()
{
	sm_pThis = this;
}

void SpaceGameEngine::Game::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
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

void SpaceGameEngine::Game::Start()
{
	if (!sm_pThis)
	{
		ThrowError(L"需要先定义一个Game");
		return;
	}
	if (sm_pThis->m_pScene)
	{
		sm_pThis->m_pScene->Start();
	}
}

void SpaceGameEngine::Game::Run()
{
	if (!sm_pThis)
	{
		ThrowError(L"需要先定义一个Game");
		return;
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

void SpaceGameEngine::Game::Release()
{
	if (sm_pThis == this)
		sm_pThis = nullptr;
}

void SpaceGameEngine::Game::SetScene(Scene * ps)
{
	if (!ps)
	{
		ThrowError(L"场景指针不能为空");
		return;
	}
	if (m_pScene == nullptr)
	{
		m_pScene = ps;
		ps->SetAsMainScene();
	}
	else
	{
		ThrowError(L"只能在设置第一个场景时使用SetScene");
	}
}

void SpaceGameEngine::Game::ChangeScene(Scene * ps)
{
	if (!ps)
	{
		ThrowError(L"场景指针不能为空");
		return;
	}
	if (m_pScene == nullptr)
	{
		ThrowError(L"第一次设置场景需使用SetScene");
		return;
	}
	m_pScene = ps;
	ps->SetAsMainScene();
	ps->Start();
}

bool SpaceGameEngine::Game::IfReadKeyboard()
{
	return m_IfReadKeyboard;
}

bool SpaceGameEngine::Game::IfReadMouse()
{
	return m_IfReadMouse;
}

void SpaceGameEngine::Game::ChangeIfReadKeyboard(bool b)
{
	m_IfReadKeyboard = b;
}

void SpaceGameEngine::Game::ChangeIfReadMouse(bool b)
{
	m_IfReadMouse = b;
}

void SpaceGameEngine::Game::ReadInputDevice()
{
	if (m_IfReadKeyboard)
		m_KeyboardDevice.DeviceRead();
	if (m_IfReadMouse)
		m_MouseDevice.DeviceRead();
}

void SpaceGameEngine::Game::StartRunGame()
{
	m_Window.InitWindow(sm_hInstance, sm_hPrevInstance, sm_lpCmdLine, sm_nShowCmd, Run, Start);
}

void SpaceGameEngine::Game::ExitGame()
{
	PostQuitMessage(0);
}
