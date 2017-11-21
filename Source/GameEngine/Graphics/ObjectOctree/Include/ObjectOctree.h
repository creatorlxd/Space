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
#include "Space.h"
#include "Math/Triangle/Include/Triangle.h"

namespace SpaceGameEngine
{
	const int ObjectOctreeMaxDeepth = 8;

	struct IndexTriangle
	{
		int m_Content[3];
		IndexTriangle();
	};

	bool operator == (const IndexTriangle& it1, const IndexTriangle& it2);

	struct ObjectOctreeNode
	{
		ObjectOctreeNode(const Vector<DefaultVertex>& data) :
			m_VertexData(data), m_IfLeafNode(true), m_Deepth(1)
		{};
		ObjectOctreeNode(const Vector<DefaultVertex>& data, const AxisAlignedBoundingBox& space, int deepth = 1) :
			m_VertexData(data), m_IfLeafNode(true), m_Space(space), m_Deepth(deepth)
		{};
		~ObjectOctreeNode();

		void Init(const AxisAlignedBoundingBox& space, int deepth = 1);
		void InsertTriangle(const IndexTriangle& data);
		bool DeleteTriangle(const IndexTriangle& data);
		Vector<unsigned int> Run(XMFLOAT3 position,XMFLOAT3 rotation,XMFLOAT3 scale);
		void Release();
		Vector<unsigned int> GetIndices();

		const Vector<DefaultVertex>& m_VertexData;
		ForwardList<IndexTriangle> m_Content;
		AxisAlignedBoundingBox m_Space;
		ObjectOctreeNode* m_ChildrenNode[8];
		bool m_IfLeafNode;
		int m_Deepth;
	};
}