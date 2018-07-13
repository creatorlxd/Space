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
#pragma once
#include "../RenderInterface.h"
#include <d3d11.h>
#include <dxgi.h>
#include "dxerr/dxerr.h"
#include "Def.h"
#include "Math/Common/ConstantValue.hpp"

namespace SpaceGameEngine
{
	class DX11RenderInterface :public RenderInterface
	{
	public:
		DX11RenderInterface();
		virtual ~DX11RenderInterface();

		virtual void Init()override;
		virtual void BeginRender(const RenderTarget& rendertarget)override;
		virtual void EndRender(const RenderTarget& rendertarget)override;
		
		//RenderTarget
		virtual void InitRenderTarget(RenderTarget & rendertarget, HWND hwnd)override;
		virtual void ReleaseRenderTarget(RenderTarget & rendertarget)override;
		virtual void ResizeRenderTarget(RenderTarget & rendertarget, const ViewPort& viewport)override;
	private:
		static D3D11_VIEWPORT GetDX11ViewPort(const ViewPort& viewport);
	private:
		ID3D11Device * m_pDevice;
		ID3D11DeviceContext* m_pImmediateDeviceContext;
		UINT m_4xMsaaQuality;
	};
}