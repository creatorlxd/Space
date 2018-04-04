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
#include "Space.h"
#include "Math/Triangle/Include/Triangle.h"

namespace SpaceGameEngine
{
	const int ObjectOctreeMaxDeepth = 8;

	struct IndexTriangle
	{
		int m_Content[3];
		IndexTriangle();
		IndexTriangle(int i1, int i2, int i3);
	};

	bool operator == (const IndexTriangle& it1, const IndexTriangle& it2);

	struct ObjectOctreeNode
	{
		ObjectOctreeNode(Vector<DefaultVertex>* data) :
			m_pVertexData(data), m_IfLeafNode(true), m_Deepth(1)
		{};
		ObjectOctreeNode(Vector<DefaultVertex>* data, const AxisAlignedBoundingBox& space, int deepth = 1) :
			m_pVertexData(data), m_IfLeafNode(true), m_Space(space), m_Deepth(deepth)
		{};
		~ObjectOctreeNode();

		void Init(const AxisAlignedBoundingBox& space, int deepth = 1);
		void InsertTriangle(const IndexTriangle& data);
		bool DeleteTriangle(const IndexTriangle& data);
		void Run(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale,Vector<unsigned int>& indices,unsigned int& index);
		void Release();
		void GetIndices(Vector<unsigned int>& indices, unsigned int& index);

		Vector<DefaultVertex>* m_pVertexData;
		ForwardList<IndexTriangle> m_Content;
		AxisAlignedBoundingBox m_Space;
		ObjectOctreeNode* m_ChildrenNode[8];
		bool m_IfLeafNode;
		int m_Deepth;
	};
	
	/*
	warning : do not use nullptr to initliazation
	*/
	class ObjectOctree
	{
	public:
		ObjectOctree(Vector<DefaultVertex>* data) :m_RootNode(data)
		{}
		void ResetVertexData(Vector<DefaultVertex>* data);
		void BuildTree(const Vector<unsigned int>& indices);
		~ObjectOctree();
		Vector<unsigned int> Run(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);
		void CleanUp();
	private:
		size_t m_MaxIndicesSize;
		ObjectOctreeNode m_RootNode;
	};
}