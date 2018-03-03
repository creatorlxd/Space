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
#include "Texture.h"
#include "Game/Asset/Include/TextureAsset.h"
#include "Game/Game/Include/Game.h"

namespace SpaceGameEngine
{
	class TextureComponent:public Component		//纹理组件，目前还不支持多纹理
	{
	public:
		static const int SingleMode = 1;
		static const int MultipleMode = 2;

		TextureComponent();
		~TextureComponent();
		void CleanUp();
		static ComponentFactory<TextureComponent> NewComponent;

		void InitFromFile(const std::string& filename, int mode = 0);
		void Start();
		void Run(float DeltaTime);
		void Copy(Component* pc);

		void SetTexture(TextureAsset& ta);
		void SetTransformMatrix(const XMMATRIX& mat);
		void AddTexture(const std::string& filename, XMMATRIX mat);
		TextureAsset GetTexture();
	private:
		XMMATRIX m_TextureTransformMatrix;
		
		std::string m_FileName;					//用于延迟初始化
		TextureAsset m_Content;
	};
}