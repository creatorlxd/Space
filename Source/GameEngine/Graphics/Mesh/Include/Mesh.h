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
#include "Game/Object/Include/Object.h"
#include "Common/Utility/Include/Window.h"
#include "Game/Game/Include/SafeGet.h"
#include "Game/Scene/Include/Scene.h"
#include "Graphics/ObjectOctree/Include/ObjectOctree.h"
#include "Game/Asset/Include/MeshAsset.h"

namespace SpaceGameEngine
{
	class MeshComponent :public Component
	{
	public:
		static const int ModelFileMode = 1;				//Model文件模式
		static const int DynamicMode = 2;				//Dynamic mode do not use global octree
		static const int WholeMode = 4;					//Whole mode do not use object octree
		static const int XAxisAlignedMode = 8;
		static const int YAxisAlignedMode = 16;
		static const int ZAxisAlignedMode = 32;

		static ComponentFactory<MeshComponent> NewComponent;		//创建组件
		MeshComponent();
		void CleanUp();
		~MeshComponent();

		void InitFromFile(const std::string& filename, int mode = 1);			//从文件读取Mesh
		void InitFromMemory(int VertexSize, int IndexSize, DefaultVertex* pVertices, unsigned int* pIndices);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）
		void Start();
		void Run(float DeltaTime);												//渲染网格
		void Copy(Component* pc);

		void SetMesh(const MeshForModelFileAsset& mmfa);
		MeshForModelFileAsset GetMesh();
	private:
		MeshForModelFileAsset m_Content;
	};
}