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
#include "../Include/ObjectOctree.h"

SpaceGameEngine::IndexTriangle::IndexTriangle()
{
	m_Content[0] = -1;
	m_Content[1] = -1;
	m_Content[2] = -1;
}

SpaceGameEngine::IndexTriangle::IndexTriangle(int i1, int i2, int i3)
{
	m_Content[0] = i1;
	m_Content[1] = i2;
	m_Content[2] = i3;
}

bool SpaceGameEngine::operator==(const IndexTriangle & it1, const IndexTriangle & it2)
{
	return (memcmp(it1.m_Content, it2.m_Content, sizeof(int) * 3) == 0);
}

SpaceGameEngine::ObjectOctreeNode::~ObjectOctreeNode()
{
	Release();
}

void SpaceGameEngine::ObjectOctreeNode::Init(const AxisAlignedBoundingBox & space, int deepth)
{
	m_Space = space;
	m_Deepth = deepth;
}

void SpaceGameEngine::ObjectOctreeNode::InsertTriangle(const IndexTriangle & data)
{
	Triangle triangle(m_VertexData[data.m_Content[0]].m_Position, m_VertexData[data.m_Content[1]].m_Position, m_VertexData[data.m_Content[2]].m_Position);
	if (!IfInclude(m_Space, triangle))
		return;
	if (m_Deepth == ObjectOctreeMaxDeepth)
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
			if (IfInclude(space[i], triangle))
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
				m_ChildrenNode[i] = MemoryManager::New<ObjectOctreeNode>(m_VertexData);
				m_ChildrenNode[i]->Init(space[i], m_Deepth + 1);
			}
			m_ChildrenNode[index]->InsertTriangle(data);
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
			if (IfInclude(m_ChildrenNode[i]->m_Space, triangle))
			{
				m_ChildrenNode[i]->InsertTriangle(data);
				return;
			}
		}
		m_Content.push_front(data);
	}
}

bool SpaceGameEngine::ObjectOctreeNode::DeleteTriangle(const IndexTriangle & data)
{
	auto iter = m_Content.before_begin();
	for (auto i = m_Content.begin(); i != m_Content.end(); i++, iter++)
	{
		if (*i == data)
		{
			m_Content.erase_after(iter);
			return true;
		}
	}
	if (!m_IfLeafNode)
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_ChildrenNode[i]->DeleteTriangle(data))
				return true;
		}
	}
	return false;
}

SpaceGameEngine::Vector<unsigned int> SpaceGameEngine::ObjectOctreeNode::Run(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
	XMMATRIX worldmatrix = GetWorldMatrix(position, rotation, scale);
	Vector<unsigned int> re;
	for (const auto& i : m_Content)
	{
		re.insert(re.end(), i.m_Content, i.m_Content + 3);
	}
	if (!m_IfLeafNode)
	{
		for (int i = 0; i < 8; i++)
		{
			int buff = IfIntersectWithFrustum(m_ChildrenNode[i]->m_Space);
			if (buff == 8)
			{
				auto buffer = m_ChildrenNode[i]->GetIndices();
				re.insert(re.end(), buffer.begin(), buffer.end());
			}
			else if (buff >= 0)
			{
				auto buffer=m_ChildrenNode[i]->Run(position,rotation,scale);
				re.insert(re.end(), buffer.begin(), buffer.end());
			}
			else
			{
				//do nothing
			}
		}
	}
	return re;
}

void SpaceGameEngine::ObjectOctreeNode::Release()
{
	if (m_IfLeafNode)
	{
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
		m_Content.clear();
		m_IfLeafNode = true;
	}
}

SpaceGameEngine::Vector<unsigned int> SpaceGameEngine::ObjectOctreeNode::GetIndices()
{
	Vector<unsigned int> re;
	for (const auto& i : m_Content)
	{
		re.insert(re.end(), i.m_Content, i.m_Content + 3);
	}
	if(!m_IfLeafNode)
	{
		for (int i = 0; i < 8; i++)
		{
			auto buffer = m_ChildrenNode[i]->GetIndices();
			re.insert(re.end(), buffer.begin(), buffer.end());
		}
	}
	return re;
}

void SpaceGameEngine::ObjectOctree::BuildTree(const Vector<unsigned int> indices)
{
	Vector<XMFLOAT3> points;
	points.resize(m_RootNode.m_VertexData.size());
	for (int i=0;i<m_RootNode.m_VertexData.size();i++)
	{
		points[i] = m_RootNode.m_VertexData[i].m_Position;
	}
	auto space = GetAxisAlignedBoundingBox(points);
	m_RootNode.Init(space);
	for (int i = 0; i < indices.size(); i+=3)
	{
		m_RootNode.InsertTriangle(IndexTriangle(indices[i], indices[i + 1], indices[i + 2]));
	}
}

SpaceGameEngine::ObjectOctree::~ObjectOctree()
{
	Release();
}

void SpaceGameEngine::ObjectOctree::Release()
{
	m_RootNode.Release();
}

SpaceGameEngine::Vector<unsigned int> SpaceGameEngine::ObjectOctree::Run(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
	return m_RootNode.Run(position,rotation,scale);
}
