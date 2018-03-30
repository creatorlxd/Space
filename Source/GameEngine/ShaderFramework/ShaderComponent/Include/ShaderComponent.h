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
#include "Game/Component/Include/ComponentFactory.h"
#include "Game/Object/Include/Object.h"
#include "Game/Asset/Include/ShaderAsset.h"
#include "Graphics/RenderSystem/Include/RenderObject.h"

namespace SpaceGameEngine
{
	/*
	仅能使用DefaultEffectShader。
	如果需要读取自定义的Shader格式，需要继承自DefaultEffectShader并重写部分代码，并写一个相关的Asset和一个Component。
	所以，这个Component和DefaultShaderAsset就相当于两个模板可以用来借鉴。
	*/
	class ShaderComponent :public Component
	{
	public:
		REGISTER_COMPONENT(ShaderComponent);

		ShaderComponent();

		void InitFromFile(const String& filename, int mode = 0);
		void Start();

		void Copy(Component* pc);
	};
}