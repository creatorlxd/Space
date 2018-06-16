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
#include "RenderTarget.h"

SpaceGameEngine::RenderTarget::RenderTarget()
	:m_pSwapChain(nullptr), m_pRenderTargetView(nullptr), m_pDepthStencilBuffer(nullptr), m_pDepthStencilView(nullptr), m_IfInitialized(false)
{
}

SpaceGameEngine::RenderTarget::RenderTarget(const ViewPort & vp)
	: m_pSwapChain(nullptr), m_pRenderTargetView(nullptr), m_pDepthStencilBuffer(nullptr), m_pDepthStencilView(nullptr), m_ViewPort(vp), m_IfInitialized(false)
{
}
