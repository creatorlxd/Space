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
#include "../../BoundingBox/Include/BoundingBox.h"

namespace SpaceGameEngine
{
	template<typename T, unsigned int MaxDeepth = 8>
	struct OctreeNode
	{
		typedef typename std::pair<XMFLOAT3, T> DataType;
		static const int OctreeMaxDeepth = MaxDeepth;

		OctreeNode()
		{
			m_IfLeafNode = true;
			m_Deepth = 1;
			m_pFather = nullptr;
		}
		~OctreeNode()
		{
			Release();
		}
		OctreeNode(const AxisAlignedBoundingBox& space, int deepth = 1)
		{
			m_IfLeafNode = true;
			m_Deepth = 1;
			m_pFather = nullptr;
			Init(space, deepth);
		}
		void Init(const AxisAlignedBoundingBox& space, int deepth = 1)
		{
			m_Space = space;
			m_Deepth = deepth;
		}
		OctreeNode<T,OctreeMaxDeepth>* InsertData(const DataType& data)
		{
			if (!IfInclude(m_Space, data.first))
				return nullptr;
			if (m_Deepth == OctreeMaxDeepth)
			{
				m_Content.push_front(data);
				return this;
			}
			if (m_IfLeafNode)
			{
				/*
				front
				0 1
				2 3

				behind
				4 5
				6 7
				*/
				XMFLOAT3 center((m_Space.m_MinPosition.x + m_Space.m_MaxPosition.x) / 2.0f,
					(m_Space.m_MinPosition.y + m_Space.m_MaxPosition.y) / 2.0f,
					(m_Space.m_MinPosition.z + m_Space.m_MaxPosition.z) / 2.0f);
				AxisAlignedBoundingBox space[8];
				space[0] = AxisAlignedBoundingBox(
					XMFLOAT3(m_Space.m_MinPosition.x, center.y, m_Space.m_MinPosition.z),
					XMFLOAT3(center.x, m_Space.m_MaxPosition.y, center.z)
				);
				space[4] = AxisAlignedBoundingBox(
					XMFLOAT3(m_Space.m_MinPosition.x, center.y, center.z),
					XMFLOAT3(center.x, m_Space.m_MaxPosition.y, m_Space.m_MaxPosition.z)
				);
				space[1] = AxisAlignedBoundingBox(
					XMFLOAT3(center.x, center.y, m_Space.m_MinPosition.z),
					XMFLOAT3(m_Space.m_MaxPosition.x, m_Space.m_MaxPosition.y, center.z)
				);
				space[5] = AxisAlignedBoundingBox(
					center,
					m_Space.m_MaxPosition
				);
				space[2] = AxisAlignedBoundingBox(
					m_Space.m_MinPosition,
					center
				);
				space[6] = AxisAlignedBoundingBox(
					XMFLOAT3(m_Space.m_MinPosition.x, m_Space.m_MinPosition.y, center.z),
					XMFLOAT3(center.x, center.y, m_Space.m_MaxPosition.z)
				);
				space[3] = AxisAlignedBoundingBox(
					XMFLOAT3(center.x, m_Space.m_MinPosition.y, m_Space.m_MinPosition.z),
					XMFLOAT3(m_Space.m_MaxPosition.x, center.y, center.z)
				);
				space[7] = AxisAlignedBoundingBox(
					XMFLOAT3(center.x, m_Space.m_MinPosition.y, center.z),
					XMFLOAT3(m_Space.m_MaxPosition.x, center.y, m_Space.m_MaxPosition.z)
				);
				bool if_child = false;
				int index = -1;
				for (int i = 0; i < 8; i++)
				{
					if (IfInclude(space[i], data.first))
					{
						if_child = true;
						index = i;
						break;
					}
				}
				if (if_child)
				{
					m_IfLeafNode = false;
					for (int i = 0; i < 8; i++)
					{
						m_ChildrenNode[i] = MemoryManager::New<OctreeNode<T, OctreeMaxDeepth>>();
						m_ChildrenNode[i]->Init(space[i], m_Deepth + 1);
						m_ChildrenNode[i]->m_pFather = this;
					}
					return m_ChildrenNode[index]->InsertData(data);
				}
				else
				{
					m_Content.push_front(data);
					return this;
				}
			}
			else
			{
				for (int i = 0; i < 8; i++)
				{
					if (IfInclude(m_ChildrenNode[i]->m_Space, data.first))
					{
						return m_ChildrenNode[i]->InsertData(data);
					}
				}
				m_Content.push_front(data);
				return this;
			}
		}
		OctreeNode<T, OctreeMaxDeepth>* UpdateData(const DataType& data)
		{
			Queue<OctreeNode<T, OctreeMaxDeepth>*> que;
			que.push(this);
			bool if_find = false;
			while (!que.empty())
			{
				OctreeNode<T, OctreeMaxDeepth>* node = que.front();
				que.pop();
				auto iter = node->m_Content.before_begin();
				for (auto i = node->m_Content.begin(); i != node->m_Content.end(); i++)
				{
					if (i->second == data.second)
					{
						if_find = true;
						node->m_Content.erase_after(iter);
						break;
					}
					iter++;
				}
				if (if_find)
				{
					break;
				}
				else
				{
					if (m_IfLeafNode == false)
					{
						for (int i = 0; i < 8; i++)
						{
							que.push(node->m_ChildrenNode[i]);
						}
					}
				}
			}
			if (!if_find)
				ThrowError("can not find the data in octree");
			return InsertData(data);
		}
		void Release()
		{
			if (m_IfLeafNode)
			{
				m_pFather = nullptr;
				m_Content.clear();
				return;
			}
			else
			{
				for (int i = 0; i < 8; i++)
				{
					m_ChildrenNode[i]->Release();
					MemoryManager::Delete(m_ChildrenNode[i]);
				}
				m_pFather = nullptr;
				m_Content.clear();
				m_IfLeafNode = true;
			}
		}
		bool DeleteData(const T& content)
		{
			auto iter = m_Content.before_begin();
			for (auto i = m_Content.begin(); i != m_Content.end(); i++, iter++)
			{
				if (i->second == pointer)
				{
					m_Content.erase_after(iter);
					return true;
				}
			}
			if (!m_IfLeafNode)
			{
				for (int i = 0; i < 8; i++)
				{
					if (m_ChildrenNode[i]->DeleteData(pointer))
						return true;
				}
			}
			return false;
		}
		OctreeNode<T, MaxDeepth>* FindOctreeNode(const XMFLOAT3& position)
		{
			if (!IfInclude(m_Space, position))
				return nullptr;
			if (m_Deepth == OctreeMaxDeepth)
			{
				return this;
			}
			if (m_IfLeafNode)
			{
				/*
				front
				0 1
				2 3

				behind
				4 5
				6 7
				*/
				XMFLOAT3 center((m_Space.m_MinPosition.x + m_Space.m_MaxPosition.x) / 2.0f,
					(m_Space.m_MinPosition.y + m_Space.m_MaxPosition.y) / 2.0f,
					(m_Space.m_MinPosition.z + m_Space.m_MaxPosition.z) / 2.0f);
				AxisAlignedBoundingBox space[8];
				space[0] = AxisAlignedBoundingBox(
					XMFLOAT3(m_Space.m_MinPosition.x, center.y, m_Space.m_MinPosition.z),
					XMFLOAT3(center.x, m_Space.m_MaxPosition.y, center.z)
				);
				space[4] = AxisAlignedBoundingBox(
					XMFLOAT3(m_Space.m_MinPosition.x, center.y, center.z),
					XMFLOAT3(center.x, m_Space.m_MaxPosition.y, m_Space.m_MaxPosition.z)
				);
				space[1] = AxisAlignedBoundingBox(
					XMFLOAT3(center.x, center.y, m_Space.m_MinPosition.z),
					XMFLOAT3(m_Space.m_MaxPosition.x, m_Space.m_MaxPosition.y, center.z)
				);
				space[5] = AxisAlignedBoundingBox(
					center,
					m_Space.m_MaxPosition
				);
				space[2] = AxisAlignedBoundingBox(
					m_Space.m_MinPosition,
					center
				);
				space[6] = AxisAlignedBoundingBox(
					XMFLOAT3(m_Space.m_MinPosition.x, m_Space.m_MinPosition.y, center.z),
					XMFLOAT3(center.x, center.y, m_Space.m_MaxPosition.z)
				);
				space[3] = AxisAlignedBoundingBox(
					XMFLOAT3(center.x, m_Space.m_MinPosition.y, m_Space.m_MinPosition.z),
					XMFLOAT3(m_Space.m_MaxPosition.x, center.y, center.z)
				);
				space[7] = AxisAlignedBoundingBox(
					XMFLOAT3(center.x, m_Space.m_MinPosition.y, center.z),
					XMFLOAT3(m_Space.m_MaxPosition.x, center.y, m_Space.m_MaxPosition.z)
				);
				bool if_child = false;
				int index = -1;
				for (int i = 0; i < 8; i++)
				{
					if (IfInclude(space[i], position))
					{
						if_child = true;
						index = i;
						break;
					}
				}
				if (if_child)
				{
					m_IfLeafNode = false;
					for (int i = 0; i < 8; i++)
					{
						m_ChildrenNode[i] = MemoryManager::New<OctreeNode<T, OctreeMaxDeepth>>();
						m_ChildrenNode[i]->Init(space[i], m_Deepth + 1);
						m_ChildrenNode[i]->m_pFather = this;
					}
					return m_ChildrenNode[index]->FindOctreeNode(position);
				}
				else
				{
					return this;
				}
			}
			else
			{
				for (int i = 0; i < 8; i++)
				{
					if (IfInclude(m_ChildrenNode[i]->m_Space, position))
					{
						return m_ChildrenNode[i]->FindOctreeNode(position);
					}
				}
				return this;
			}
		}

		ForwardList<DataType> m_Content;
		AxisAlignedBoundingBox m_Space;
		OctreeNode<T, OctreeMaxDeepth>* m_ChildrenNode[8];
		bool m_IfLeafNode;
		int m_Deepth;
		OctreeNode<T, OctreeMaxDeepth>* m_pFather;
	};

	template<typename T, unsigned int MaxDeepth = 8>
	class Octree
	{
	public:
		typedef typename OctreeNode<T, MaxDeepth>::DataType DataType;

		~Octree()
		{
			Release();
		}
		OctreeNode<T, MaxDeepth>* AddData(const DataType& data)
		{
			if (!m_IfInit)
			{
				m_IntializaionData.push_back(data);
				return nullptr;
			}
			else
			{
				return m_RootNode.InsertData(data);
			}
		}
		bool DeleteData(typename DataType::second_type data)
		{
			if (!m_IfInit)
			{
				for (auto i = m_IntializaionData.begin(); i != m_IntializaionData.end(); i++)
				{
					if (i->second == data)
					{
						m_IntializaionData.erase(i);
						return true;
					}
				}
				return false;
			}
			else
			{
				return m_RootNode.DeleteData(data);
			}
		}
		void BuildTree()
		{
			m_IfInit = true;
			Vector<AxisAlignedBoundingBox> aabb;
			for (const auto& i : m_IntializaionData)
			{
				aabb.push_back(i.first);
			}
			AxisAlignedBoundingBox max_space = GetAxisAlignedBoundingBox(aabb);
			m_RootNode.Init(max_space);
			for (const auto& i : m_IntializaionData)
			{
				m_RootNode.InsertData(i);
			}
			m_IntializaionData.clear();
		}
		void BuildTreeWithSpaceLimit(const AxisAlignedBoundingBox& space)
		{
			m_IfInit = true;
			m_RootNode.Init(space);
			for (const auto& i : m_IntializaionData)
			{
				m_RootNode.InsertData(i);
			}
			m_IntializaionData.clear();
		}
		void Release()
		{
			m_RootNode.Release();
		}
		OctreeNode<T, MaxDeepth>* UpdateData(const DataType& data)
		{
			return m_RootNode.UpdateData(data);
		}
		OctreeNode<T, MaxDeepth>* FindOctreeNode(const XMFLOAT3& position)
		{
			return m_RootNode.FindOctreeNode(position);
		}
	private:
		OctreeNode<T, MaxDeepth> m_RootNode;
		Vector<DataType> m_IntializaionData;
		bool m_IfInit = false;
	};
}