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
#include "Common/Error.h"
#include "Common/Connection.hpp"
#include "RenderTarget.h"

namespace SpaceGameEngine
{
	class RenderInterface :public Data<RenderInterface>
	{
	public:
		RenderInterface();
		virtual void Init() = 0;
		virtual void BeginRender(const RenderTarget& rendertarget) = 0;
		virtual void EndRender(const RenderTarget& rendertarget) = 0;
		virtual ~RenderInterface();

		//RenderTarget
		/*
		初始化RenderTarget,但是RenderInterface必须已经初始化。
		*/
		virtual void InitRenderTarget(RenderTarget & rendertarget, HWND hwnd) = 0;
		/*
		释放一个已被初始化的RenderTarget,但是RenderInterface必须已经初始化。
		*/
		virtual void ReleaseRenderTarget(RenderTarget & rendertarget) = 0;
		virtual void ResizeRenderTarget(RenderTarget & rendertarget, const ViewPort& viewport) = 0;
	protected:
		bool m_IfUse4xMsaa;
		bool m_IfInitialized;
	};

	CONNECTION_BEGIN(RenderInterface)
		OnNotifyAction<void()> m_OnStartAction;
		OnNotifyAction<void()> m_OnReleaseAction;
	CONNECTION_END;
}