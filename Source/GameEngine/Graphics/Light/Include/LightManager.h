/*
Copyright 2017 creatorlxd

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
#include "stdafx.h"
#include "Space.h"
#include "Light.h"
#include "Math/Octree/Include/Octree.h"

namespace SpaceGameEngine
{
	struct LightEx			//基本的光源单位
	{
		enum class LightMode
		{
			Normal=0,
			Dynamic=1		//often on/off or move
		};

		LightEx();
		LightMode m_Mode;
		bool m_IfOn;		//光源的开启状态
		Light m_Content;
	};

	struct Lighting			//受到光照的信息
	{
		XMFLOAT3 m_Position;
		Vector<std::pair<float,LightEx*>> m_Content;	//<distance pointer>
	};

	class LightManager
	{
	public:
		LightManager();
		~LightManager();
		void Release();

		void StartRun();

		void AddLight(LightEx* plight);
		void DeleteLight(LightEx* plight);
		void AddLighting(Lighting* plg);
		void DeleteLighting(Lighting* plg);

		void SetAsMainManager();
		static LightManager* GetMainManager();
	private:
		Vector<Lighting*> m_Content;		//不负责释放
		Queue<unsigned int> m_FreeIndexList;
		Octree<XMFLOAT3,unsigned int> m_LightingOctree;

		static LightManager* sm_pThis;
	};
}