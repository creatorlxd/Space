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
#include "Game/Object/Include/Object.h"
#include "Window.h"
#include "Game/Game/Include/SafeGet.h"
#include "Game/Scene/Include/Scene.h"
#include "Graphics/ObjectOctree/Include/ObjectOctree.h"

namespace SpaceGameEngine
{
	class MeshComponent :public Component
	{
	public:
		static const int ModelFileMode = 1;				//Model文件模式
		static const int DynamicMode = 2;				//Dynamic mode do not use global octree

		static ComponentManager::NewComponent<MeshComponent> NewComponent;		//创建组件
		MeshComponent();
		void Release();
		~MeshComponent();

		void InitFromMemory(int VertexSize, int IndexSize, DefaultVertex* pVertices, unsigned int* pIndices);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）

		void InitFromFile(const std::string& filename, int mode = 1);			//从文件读取Mesh
		void Start();
		void Run(float DeltaTime);												//渲染网格
	protected:
		void InitVertexBuffer();
		void InitIndexBuffer();

		Vector<DefaultVertex> m_Vertices;
		Vector<unsigned int> m_Indices;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		TransformComponent* m_pTransform;
		AxisAlignedBoundingBox m_Space;

		ObjectOctree m_ObjectOctree;
	};
}