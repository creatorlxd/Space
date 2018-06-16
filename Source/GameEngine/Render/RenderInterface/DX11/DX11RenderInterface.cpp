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
#include "DX11RenderInterface.h"

SpaceGameEngine::DX11RenderInterface::DX11RenderInterface()
	:m_pDevice(nullptr), m_pImmdiateDeviceContext(nullptr)
{
}

SpaceGameEngine::DX11RenderInterface::~DX11RenderInterface()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pImmdiateDeviceContext);
}

void SpaceGameEngine::DX11RenderInterface::Init()
{
	UINT CreateDeviceFlags = 0;

#if  defined(DEBUG)||defined(_DEBUG)
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, CreateDeviceFlags, 0, 0, D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pImmdiateDeviceContext);
	if (FAILED(hr))
	{
		THROWERROR("can not create D3D11Device");
	}
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		THROWERROR("D3D11 featurelevel 11 unsupported");
	}
	HR(m_pDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	assert(m_4xMsaaQuality > 0);

	m_IfInitialized = true;
	DATA_NOTIFY(RenderInterface, m_OnStartAction);
}

void SpaceGameEngine::DX11RenderInterface::BeginRender(const RenderTarget & rendertarget)
{
	assert(m_IfInitialized);
	assert(rendertarget.m_IfInitialized);
	//TODO
}

void SpaceGameEngine::DX11RenderInterface::EndRender(const RenderTarget & rendertarget)
{
	assert(m_IfInitialized);
	assert(rendertarget.m_IfInitialized);
	//TODO
}

void SpaceGameEngine::DX11RenderInterface::InitRenderTarget(RenderTarget & rendertarget, HWND hwnd)
{
	assert(m_IfInitialized);
	assert(hwnd);
	//TODO
}

void SpaceGameEngine::DX11RenderInterface::ReleaseRenderTarget(RenderTarget & rendertarget)
{
	assert(m_IfInitialized);
	assert(rendertarget.m_IfInitialized);
	//TODO
}

void SpaceGameEngine::DX11RenderInterface::ResizeRenderTarget(RenderTarget & rendertarget, const ViewPort & viewport)
{
	if (rendertarget.m_IfInitialized)
	{
		assert(m_IfInitialized);
		//TODO
	}
	else
	{
		rendertarget.m_ViewPort = viewport;
	}
}
