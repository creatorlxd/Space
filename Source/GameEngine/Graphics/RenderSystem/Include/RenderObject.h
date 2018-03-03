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
#include "Game/Asset/Include/TransformAsset.h"
#include "Game/Asset/Include/MaterialAsset.h"
#include "Game/Asset/Include/TextureAsset.h"
#include "Game/Asset/Include/LightAsset.h"
#include "Game/Asset/Include/MeshAsset.h"
#include "ShaderFarmework/EffectShader/Include/EffectShader.h"
#include "Game/Object/Include/Object.h"
#include "Math/Common/Include/XMathExtension.h"
#include "Game/Scene/Include/SceneData.h"
#include "Graphics/GlobalOctree/Include/GlobalOctree.h"
#include "Graphics/ObjectOctree/Include/ObjectOctree.h"

namespace SpaceGameEngine
{
	enum class RenderObjectType :uint32_t
	{
		Unkown = 0,
		Model = 1
	};

	class RenderObject
	{
	public:
		RenderObject();
		~RenderObject();

		void Init();
		void Render();
		void SetMesh(const MeshForModelFileAsset& mmfa);
	private:
		void InitVertexBuffer();
		void InitIndexBuffer();
	public:
		static const int ModelFileMode = 1;				//Model文件模式
		static const int DynamicMode = 2;				//Dynamic mode do not use global octree
		static const int WholeMode = 4;					//Whole mode do not use object octree
		static const int XAxisAlignedMode = 8;
		static const int YAxisAlignedMode = 16;
		static const int ZAxisAlignedMode = 32;
	public:
		bool m_IfHaveTransform;
		bool m_IfHaveMaterial;
		bool m_IfHaveTexture;
		bool m_IfHaveMesh;

		GlobalOctree * m_pGlobalOctree;

		Vector<DefaultEffectShader*> m_Shader;
		Object* m_pObject;

		TransformAsset m_TransformAsset;
		Vector<MaterialAsset> m_MaterialAsset;
		Vector<std::pair<TextureAsset,XMMATRIX>> m_TextureAsset;
		MeshForModelFileAsset m_MeshForModelFileAsset;

		int m_Mode;
		RenderObjectType m_Type;
		bool m_IfRender;
		bool m_IfInit;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		AxisAlignedBoundingBox m_Space;
		AxisAlignedBoundingBox m_BaseSpace;

		GlobalOctreeNode* m_pGlobalOctreeNode;

		ObjectOctree m_ObjectOctree;
	};
}