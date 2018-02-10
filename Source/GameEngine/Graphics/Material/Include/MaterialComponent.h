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
#include "stdafx.h"
#include "Game/Component/Include/ComponentFactory.h"
#include "Game/Asset/Include/MaterialAsset.h"
#include "Game/Game/Include/Game.h"

namespace SpaceGameEngine
{
	class MaterialComponent :public Component
	{
	public:
		MaterialComponent();
		~MaterialComponent();

		static const int SingleMode = 1;

		static ComponentFactory<MaterialComponent> NewComponent;

		void InitFromFile(const std::string& filename, int mode = 0);
		void Start();
		void Run(float DeltaTime);
		void CleanUp();
		void Copy(Component* pc);

		void SetMaterial(const Material& ma);
		Material GetMaterial();
	private:
		Material m_Content;
	};
}