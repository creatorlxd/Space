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
#include "stdafx.h"
#include "../Include/GlobalOctree.h"

SpaceGameEngine::GlobalOctreeNode::GlobalOctreeNode()
{
	m_IfLeafNode = true;
	m_Deepth = 1;
}

SpaceGameEngine::GlobalOctreeNode::GlobalOctreeNode(const AxisAlignedBoundingBox & space, int deepth)
{
	Init(space, deepth);
}

void SpaceGameEngine::GlobalOctreeNode::Init(const AxisAlignedBoundingBox & space,int deepth)
{
	m_Space = space;
	m_Deepth = deepth;
}

void SpaceGameEngine::GlobalOctreeNode::InsertObject(const GlobalOctreeData & data)
{
	if (!IfInclude(m_Space, data.first))
		return;
	if (m_Deepth == GlobalOctreeMaxDeepth)
	{
		m_Content.push_front(data);
		return;
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
		space[0]=AxisAlignedBoundingBox(
			XMFLOAT3(m_Space.m_MinPosition.x,center.y,m_Space.m_MinPosition.z),
			XMFLOAT3(center.x,m_Space.m_MaxPosition.y,center.z)
		);
		space[4]=AxisAlignedBoundingBox(
			XMFLOAT3(m_Space.m_MinPosition.x,center.y,center.z),
			XMFLOAT3(center.x,m_Space.m_MaxPosition.y,m_Space.m_MaxPosition.z)
		);
		space[1] = AxisAlignedBoundingBox(
			XMFLOAT3(center.x,center.y,m_Space.m_MinPosition.z),
			XMFLOAT3(m_Space.m_MaxPosition.x,m_Space.m_MaxPosition.y,center.z)
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
			XMFLOAT3(center.x,m_Space.m_MinPosition.y,m_Space.m_MinPosition.z),
			XMFLOAT3(m_Space.m_MaxPosition.x,center.y,center.z)
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
				m_ChildrenNode[i] = MemoryManager::New<GlobalOctreeNode>();
				m_ChildrenNode[i]->Init(space[i], m_Deepth + 1);
			}
			m_ChildrenNode[index]->InsertObject(data);
		}
		else
		{
			m_Content.push_front(data);
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if(IfInclude(m_ChildrenNode[i]->m_Space,data.first))
			{
				m_ChildrenNode[i]->InsertObject(data);
				return;
			}
		}
		m_Content.push_front(data);
	}
}

void SpaceGameEngine::GlobalOctreeNode::Release()
{
	if (m_IfLeafNode)
		return;
	else
	{
		for (int i = 0; i < 8; i++)
		{
			m_ChildrenNode[i]->Release();
			MemoryManager::Delete(m_ChildrenNode[i]);
		}
	}
}
