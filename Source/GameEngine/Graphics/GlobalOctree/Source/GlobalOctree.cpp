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
#include "stdafx.h"
#include "../Include/GlobalOctree.h"

SpaceGameEngine::GlobalOctreeNode::GlobalOctreeNode()
{
	m_IfLeafNode = true;
	m_Deepth = 1;
	m_pFather = nullptr;
}

SpaceGameEngine::GlobalOctreeNode::~GlobalOctreeNode()
{
	
}

SpaceGameEngine::GlobalOctreeNode::GlobalOctreeNode(const AxisAlignedBoundingBox & space, int deepth)
{
	m_IfLeafNode = true;
	Init(space, deepth);
	m_pFather = nullptr;
}

void SpaceGameEngine::GlobalOctreeNode::Init(const AxisAlignedBoundingBox & space,int deepth)
{
	m_Space = space;
	m_Deepth = deepth;
}

SpaceGameEngine::GlobalOctreeNode* SpaceGameEngine::GlobalOctreeNode::InsertObject(const GlobalOctreeData & data)
{
	if (!IfIntersect(m_Space, data.first))
		return nullptr;
	if (m_Deepth == GlobalOctreeMaxDeepth)
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
				m_ChildrenNode[i]->m_pFather = this;
			}
			return m_ChildrenNode[index]->InsertObject(data);
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
			if(IfInclude(m_ChildrenNode[i]->m_Space,data.first))
			{
				return m_ChildrenNode[i]->InsertObject(data);
			}
		}
		m_Content.push_front(data);
		return this;
	}
}

void SpaceGameEngine::GlobalOctreeNode::Run()
{
	for (const auto& i : m_Content)
	{
		if (IfIntersectWithFrustum(i.first) >= 0)
			i.second->ChangeIfRender(true);
		else
			i.second->ChangeIfRender(false);
	}
	if (!m_IfLeafNode)
	{
		for (int i = 0; i < 8; i++)
		{
			int buff = IfIntersectWithFrustum(m_ChildrenNode[i]->m_Space);
			if (buff==8)
			{
				m_ChildrenNode[i]->SetObjectRenderState(true);
			}
			else if (buff >= 0)
			{
				m_ChildrenNode[i]->Run();
			}
			else
			{
				m_ChildrenNode[i]->SetObjectRenderState(false);
			}
		}
	}
}

void SpaceGameEngine::GlobalOctreeNode::SetObjectRenderState(bool state)
{
	for (const auto& i : m_Content)
	{
		i.second->ChangeIfRender(state);
	}
	if (!m_IfLeafNode)
	{
		for (int i = 0; i < 8; i++)
		{
			m_ChildrenNode[i]->SetObjectRenderState(state);
		}
	}
}

SpaceGameEngine::GlobalOctreeNode* SpaceGameEngine::GlobalOctreeNode::UpdateObjectData(const GlobalOctreeData & data)
{
	Queue<GlobalOctreeNode*> que;
	que.push(this);
	bool if_find = false;
	while (!que.empty())
	{
		GlobalOctreeNode* node = que.front();
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
		ThrowError("can not find the object in global octree");
	return InsertObject(data);
}

void SpaceGameEngine::GlobalOctreeNode::UpdateObjectRenderState(const GlobalOctreeData & data)
{
	if (IfIntersectWithFrustum(data.first))
		data.second->ChangeIfRender(true);
	else
		data.second->ChangeIfRender(false);
}

void SpaceGameEngine::GlobalOctreeNode::Release()
{
	if (m_IfLeafNode)
	{
		
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			m_ChildrenNode[i]->Release();
			MemoryManager::Delete(m_ChildrenNode[i]);
			m_ChildrenNode[i] = nullptr;
		}
		m_IfLeafNode = true;
	}
	m_pFather = nullptr;
	m_Content.clear();
	m_Space = AxisAlignedBoundingBox();
	m_Deepth = 1;
}

bool SpaceGameEngine::GlobalOctreeNode::DeleteObjectData(GlobalOctreeData::second_type pointer)
{
	auto iter = m_Content.before_begin();
	for (auto i = m_Content.begin(); i != m_Content.end(); i++,iter++)
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
			if (m_ChildrenNode[i]->DeleteObjectData(pointer))
				return true;
		}
	}
	return false;
}

SpaceGameEngine::GlobalOctree::~GlobalOctree()
{
	if (m_IfInit)
	{
		m_RootNode.Release();
	}
}

SpaceGameEngine::GlobalOctreeNode* SpaceGameEngine::GlobalOctree::AddObject(const GlobalOctreeData & data)
{
	if (!m_IfInit)
	{
		m_IntializaionData.push_back(data);
		return nullptr;
	}
	else
	{
		return m_RootNode.InsertObject(data);
	}
}

bool SpaceGameEngine::GlobalOctree::DeleteObject(GlobalOctreeData::second_type pointer)
{
	if (!m_IfInit)
	{
		for (auto i = m_IntializaionData.begin(); i != m_IntializaionData.end(); i++)
		{
			if (i->second == pointer)
			{
				m_IntializaionData.erase(i);
				return true;
			}
		}
		return false;
	}
	else
	{
		return m_RootNode.DeleteObjectData(pointer);
	}
}

void SpaceGameEngine::GlobalOctree::BuildTree()
{
	if (!m_IfInit)
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
			m_RootNode.InsertObject(i);
		}
		m_IntializaionData.clear();
	}
}

void SpaceGameEngine::GlobalOctree::BuildTreeWithSpaceLimit(const AxisAlignedBoundingBox & space)
{
	if (!m_IfInit)
	{
		m_IfInit = true;
		m_RootNode.Init(space);
		for (const auto& i : m_IntializaionData)
		{
			m_RootNode.InsertObject(i);
		}
		m_IntializaionData.clear();
	}
}

void SpaceGameEngine::GlobalOctree::Run()
{
	m_RootNode.Run();
}

SpaceGameEngine::GlobalOctreeNode* SpaceGameEngine::GlobalOctree::UpdateObject(const GlobalOctreeData & data)
{
	GlobalOctreeNode* re=m_RootNode.UpdateObjectData(data);
	m_RootNode.UpdateObjectRenderState(data);
	return re;
}
