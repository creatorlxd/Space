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
#include "Game/Scene/Include/Scene.h"
namespace SpaceGameEngine
{
	class InformationComponent :public Component			//Object信息组件
	{
	public:
		static ComponentManager::NewComponent<InformationComponent> NewComponent;

		InformationComponent();
		~InformationComponent();

		void Run(float DeltaTime);
	};

	bool RegisterObject(const std::string& name, Object* po);	//注册Object

#define REGISTEROBJECT(o) RegisterObject(#o,o);
}