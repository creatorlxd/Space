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
#include "Game/Component/Include/Component.h"
#include "Math/BoundingBox/Include/BoundingBox.h"

namespace SpaceGameEngine
{
	const int GlobalOctreeMaxDeepth = 8;

	using GlobalOctreeData = std::pair<AxisAlignedBoundingBox, Component*>;	//first:aabb;second:component*

	struct GlobalOctreeNode
	{
		GlobalOctreeNode();
		GlobalOctreeNode(const AxisAlignedBoundingBox& space, int deepth = 1);
		void Init(const AxisAlignedBoundingBox& space, int deepth = 1);
		void InsertObject(const GlobalOctreeData& data);
		void Release();

		ForwardList<GlobalOctreeData> m_Content;
		AxisAlignedBoundingBox m_Space;
		GlobalOctreeNode* m_ChildrenNode[8];
		bool m_IfLeafNode;
		int m_Deepth;
	};

	class GlobalOctree
	{
	public:
	private:
		GlobalOctreeNode m_RootNode;
	};
}