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
#include "Math/BoundingBox/Include/BoundingBox.h"

namespace SpaceGameEngine
{
	const int GlobalOctreeMaxDeepth = 8;

	using GlobalOctreeData = std::pair<AxisAlignedBoundingBox, Object*>;	//first:aabb;second:component*

	struct GlobalOctreeNode
	{
		GlobalOctreeNode();
		~GlobalOctreeNode();
		GlobalOctreeNode(const AxisAlignedBoundingBox& space, int deepth = 1);
		void Init(const AxisAlignedBoundingBox& space, int deepth = 1);
		void InsertObject(const GlobalOctreeData& data);
		void Run();
		void SetObjectRenderState(bool state);
		void UpdateObjectData(const GlobalOctreeData& data);
		void UpdateObjectRenderState(const GlobalOctreeData& data);
		void Release();
		bool DeleteObjectData(GlobalOctreeData::second_type pointer);

		ForwardList<GlobalOctreeData> m_Content;
		AxisAlignedBoundingBox m_Space;
		GlobalOctreeNode* m_ChildrenNode[8];
		bool m_IfLeafNode;
		int m_Deepth;
	};

	class GlobalOctree
	{
	public:
		~GlobalOctree();
		void AddObject(const GlobalOctreeData& data);
		bool DeleteObject(GlobalOctreeData::second_type pointer);
		void BuildTree();
		void BuildTreeWithSpaceLimit(const AxisAlignedBoundingBox& space);
		void Run();
		void Release();
		void UpdateObject(const GlobalOctreeData& data);
	private:
		GlobalOctreeNode m_RootNode;
		Vector<GlobalOctreeData> m_IntializaionData;
		bool m_IfInit = false;
	};
}