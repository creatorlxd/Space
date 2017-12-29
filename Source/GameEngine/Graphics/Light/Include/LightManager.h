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
#include "Physics/Transform/Include/Transform.h"

namespace SpaceGameEngine
{
	struct LightEx			//�����Ĺ�Դ��λ
	{
		enum class LightMode
		{
			Normal=0,
			Dynamic=1		//often on/off or move
		};

		LightEx();
		LightMode m_Mode;
		bool m_IfOn;		//��Դ�Ŀ���״̬
		Light m_Content;
	};

	class LightManager
	{
	public:
		static const unsigned int MaxLightSize = 8;						//һ��������ദ��Ĺ�Դ��

		LightManager();
		~LightManager();
		void Release();

		void InsertLight(LightEx* plight);
		void UpdateLight(LightEx* plight);
		void DeleteLight(LightEx* plight);

		Vector<Light> GetLight(TransformComponent* transform);			//transform��camera��transform

		void SetAsMainManager();
		static LightManager* GetMainManager();
	private:
		Vector<LightEx*> m_Content;		//�������ͷ�
		Vector<LightEx*> m_DirectionLights;
		Vector<LightEx*> m_DynamicLights;
		Queue<unsigned int> m_FreeIndexList;
		Octree<XMFLOAT3,unsigned int> m_LightOctree;

		static LightManager* sm_pThis;
	};
}