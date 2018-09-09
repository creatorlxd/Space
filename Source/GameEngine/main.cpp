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

using namespace SpaceGameEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Window* pWindow = MemoryManager::New<Window>();
	RenderInterface* pRenderInterface = MemoryManager::New<DX11RenderInterface>();
	//test
	RenderTarget render_target(ViewPort(0, 0, pWindow->GetWindowWidth(), pWindow->GetWindowHeight()));
	Observer<Window> WindowConnection(pWindow);
	Observer<RenderInterface> RenderInterfaceConnection(pRenderInterface);
	WindowConnection.m_RespondStart = [&]() {
		pRenderInterface->Init();
	};
	WindowConnection.m_RespondRun = [&]() {
		pRenderInterface->BeginRender(render_target);
		pRenderInterface->EndRender(render_target);
	};
	WindowConnection.m_RespondResize = [&]() {
		if (render_target.m_IfInitialized)
		{
			pRenderInterface->ResizeRenderTarget(render_target, ViewPort(0, 0, pWindow->GetWindowWidth(), pWindow->GetWindowHeight()));
			pRenderInterface->BeginRender(render_target);
			pRenderInterface->EndRender(render_target);
		}
	};
	WindowConnection.m_RespondRelease = [&]() {

	};
	RenderInterfaceConnection.m_RespondStart = [&]() {
		pRenderInterface->InitRenderTarget(render_target, pWindow->GetHwnd());
	};
	RenderInterfaceConnection.m_RespondRelease = [&]() {
		pRenderInterface->ReleaseRenderTarget(render_target);
	};
	//----
	pWindow->StartRun(hInstance);
	MemoryManager::Delete(pWindow);
	MemoryManager::Delete(pRenderInterface);
	return 0;
}
