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
#include "Game/Component/Include/ComponentManager.h"
#include "Physics/Transform/Include/Transform.h"

namespace SpaceGameEngine
{
	/*
	链接组件，用于对象间的链接
	*/
	class ConnectComponent :public Component
	{
	public:
		static ComponentManager::NewComponent<ConnectComponent> NewComponent;

		ConnectComponent();
		
		void Run(float DeltaTime);

		void SetTransform(TransformComponent* father,TransformComponent* child);
	private:
		TransformComponent * m_pFatherTransform;
		TransformComponent * m_pChildTransform;
		bool m_IfInit;
	};

	void ConnectObject(Object* father, Object* child);
	void DisconObject(Object* child);
}