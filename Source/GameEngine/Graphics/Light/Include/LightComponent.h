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
#include "LightManager.h"
#include "Game/Scene/Include/Scene.h"
#include "Game/Asset/Include/LightAsset.h"
#include "Physics/Transform/Include/Transform.h"
#include "Math/Common/Include/XMathExtension.h"

namespace SpaceGameEngine
{
	class LightComponent :public Component
	{
	public:
		REGISTER_COMPONENT(LightComponent);

		static const int StaticMode = 1;
		static const int DynamicMode = 2;

		LightComponent();
		~LightComponent();

		void InitFromFile(const String& filename, int mode = 0);
		void Start();
		void Run(float DeltaTime);
		void CleanUp();
		void Copy(Component* pc);

		bool IfOn();
		void ChangeIfOn(bool b);
	private:
		LightEx m_Content;
		TransformComponent* m_pTransform;
	};
}