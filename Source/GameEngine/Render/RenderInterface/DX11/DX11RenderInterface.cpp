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
	:m_pDevice(nullptr), m_pImmediateDeviceContext(nullptr)
{
}

SpaceGameEngine::DX11RenderInterface::~DX11RenderInterface()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pImmediateDeviceContext);
}

void SpaceGameEngine::DX11RenderInterface::Init()
{
	UINT CreateDeviceFlags = 0;

#if  defined(DEBUG)||defined(_DEBUG)
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, CreateDeviceFlags, 0, 0, D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pImmediateDeviceContext);
	if (FAILED(hr))
	{
		THROW_ERROR("can not create D3D11Device");
	}
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		THROW_ERROR("D3D11 featurelevel 11 unsupported");
	}
	HR(m_pDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	ASSERT(m_4xMsaaQuality > 0, "Msaa Quality must more than zero");

	m_IfInitialized = true;
	DATA_NOTIFY(RenderInterface, m_OnStartAction);
}

void SpaceGameEngine::DX11RenderInterface::BeginRender(const RenderTarget & rendertarget)
{
	ASSERT(m_IfInitialized, "RenderInterface must has been initialized");
	ASSERT(rendertarget.m_IfInitialized, "RenderTarget must has been initialized");
	m_pImmediateDeviceContext->ClearRenderTargetView((ID3D11RenderTargetView*)rendertarget.m_pRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	m_pImmediateDeviceContext->ClearDepthStencilView((ID3D11DepthStencilView*)rendertarget.m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateDeviceContext->OMSetRenderTargets(1, (ID3D11RenderTargetView**)&rendertarget.m_pRenderTargetView, (ID3D11DepthStencilView*)rendertarget.m_pDepthStencilView);
	D3D11_VIEWPORT dx11viewport = GetDX11ViewPort(rendertarget.m_ViewPort);
	m_pImmediateDeviceContext->RSSetViewports(1, &dx11viewport);
}

void SpaceGameEngine::DX11RenderInterface::EndRender(const RenderTarget & rendertarget)
{
	ASSERT(m_IfInitialized, "RenderInterface must has been initialized");
	ASSERT(rendertarget.m_IfInitialized, "RenderTarget must has been initialized");
	HR(((IDXGISwapChain*)rendertarget.m_pSwapChain)->Present(0, 0));
}

void SpaceGameEngine::DX11RenderInterface::InitRenderTarget(RenderTarget & rendertarget, HWND hwnd)
{
	ASSERT(m_IfInitialized, "RenderInterface must has been initialized");
	ASSERT(!rendertarget.m_IfInitialized, "Can not initialize the RenderTarget which has been initialized");
	ASSERT(hwnd, "HWND can not be NULL");
	//swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = rendertarget.m_ViewPort.m_Width;    // 使用窗口客户区宽度
	sd.BufferDesc.Height = rendertarget.m_ViewPort.m_Height;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	if (m_IfUse4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	IDXGIDevice* dxgiDevice = 0;
	HR(m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));
	HR(dxgiFactory->CreateSwapChain(m_pDevice, &sd, (IDXGISwapChain**)&rendertarget.m_pSwapChain));
	SafeRelease(dxgiDevice);
	SafeRelease(dxgiAdapter);
	SafeRelease(dxgiFactory);
	//render target view
	ID3D11Texture2D* backBuffer;
	HR(((IDXGISwapChain*)rendertarget.m_pSwapChain)->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_pDevice->CreateRenderTargetView(backBuffer, 0, (ID3D11RenderTargetView**)&rendertarget.m_pRenderTargetView));
	SafeRelease(backBuffer);
	//depth&stencil buffer&view
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = rendertarget.m_ViewPort.m_Width;
	depthStencilDesc.Height = rendertarget.m_ViewPort.m_Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	if (m_IfUse4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	HR(m_pDevice->CreateTexture2D(&depthStencilDesc, 0, (ID3D11Texture2D**)&rendertarget.m_pDepthStencilBuffer));
	HR(m_pDevice->CreateDepthStencilView((ID3D11Texture2D*)rendertarget.m_pDepthStencilBuffer, 0, (ID3D11DepthStencilView**)&rendertarget.m_pDepthStencilView));
	//set rendertarget's if_initialized
	rendertarget.m_IfInitialized = true;
}

void SpaceGameEngine::DX11RenderInterface::ReleaseRenderTarget(RenderTarget & rendertarget)
{
	ASSERT(m_IfInitialized, "RenderInterface must has been initialized");
	ASSERT(rendertarget.m_IfInitialized, "RenderTarget must has been initialized");
	SafeRelease((IDXGISwapChain*&)rendertarget.m_pSwapChain);
	SafeRelease((ID3D11RenderTargetView*&)rendertarget.m_pRenderTargetView);
	SafeRelease((ID3D11DepthStencilView*&)rendertarget.m_pDepthStencilView);
	SafeRelease((ID3D11Texture2D*&)rendertarget.m_pDepthStencilBuffer);
}

void SpaceGameEngine::DX11RenderInterface::ResizeRenderTarget(RenderTarget & rendertarget, const ViewPort & viewport)
{
	if (rendertarget.m_IfInitialized)
	{
		ASSERT(m_IfInitialized, "RenderInterface must has been initialized");
		//set the viewport
		rendertarget.m_ViewPort = viewport;
		//release old rendertargetview;depth&stencilview/buffer
		SafeRelease((ID3D11RenderTargetView*&)rendertarget.m_pRenderTargetView);
		SafeRelease((ID3D11DepthStencilView*&)rendertarget.m_pDepthStencilView);
		SafeRelease((ID3D11Texture2D*&)rendertarget.m_pDepthStencilBuffer);
		//resize swap chain
		HR(((IDXGISwapChain*)rendertarget.m_pSwapChain)->ResizeBuffers(1, rendertarget.m_ViewPort.m_Width, rendertarget.m_ViewPort.m_Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
		//re create rendertargetview
		ID3D11Texture2D* backBuffer;
		HR(((IDXGISwapChain*)rendertarget.m_pSwapChain)->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
		HR(m_pDevice->CreateRenderTargetView(backBuffer, 0, (ID3D11RenderTargetView**)&rendertarget.m_pRenderTargetView));
		SafeRelease(backBuffer);
		//recreate depth/stencil view&buffer
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = rendertarget.m_ViewPort.m_Width;
		depthStencilDesc.Height = rendertarget.m_ViewPort.m_Height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (m_IfUse4xMsaa)
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		HR(m_pDevice->CreateTexture2D(&depthStencilDesc, 0, (ID3D11Texture2D**)&rendertarget.m_pDepthStencilBuffer));
		HR(m_pDevice->CreateDepthStencilView((ID3D11Texture2D*)rendertarget.m_pDepthStencilBuffer, 0, (ID3D11DepthStencilView**)&rendertarget.m_pDepthStencilView));
	}
	else
	{
		rendertarget.m_ViewPort = viewport;
	}
}

D3D11_VIEWPORT SpaceGameEngine::DX11RenderInterface::GetDX11ViewPort(const ViewPort & viewport)
{
	D3D11_VIEWPORT re;
	re.TopLeftX = static_cast<float>(viewport.m_PositionX);
	re.TopLeftY = static_cast<float>(viewport.m_PositionY);
	re.Width = static_cast<float>(viewport.m_Width);
	re.Height = static_cast<float>(viewport.m_Height);
	re.MinDepth = 0.0f;
	re.MaxDepth = 1.0f;
	return re;
}
