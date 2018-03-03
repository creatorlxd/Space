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
#include"stdafx.h"
#include "../Include/Mesh.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(MeshComponent);

SpaceGameEngine::MeshComponent::MeshComponent()
{
	m_TypeName = "MeshComponent";
}

void SpaceGameEngine::MeshComponent::CleanUp()
{
	if (m_Mode&ModelFileMode)
	{
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				SafeRelease(m_pFatherObject->GetRenderObject()->m_pVertexBuffer);
				SafeRelease(m_pFatherObject->GetRenderObject()->m_pIndexBuffer);
				m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset = MeshForModelFileAsset();
				m_pFatherObject->GetRenderObject()->m_IfHaveMesh = false;

				m_pFatherObject->GetRenderObject()->m_pGlobalOctree->DeleteObject(m_pFatherObject);
			}
		}
	}
}

SpaceGameEngine::MeshComponent::~MeshComponent()
{
	
}

void SpaceGameEngine::MeshComponent::InitFromFile(const std::string & filename, int mode)
{
	m_Mode = mode;

	if (m_Mode&ModelFileMode)
	{
		const MeshForModelFileAsset* ma = ReadAssetFromFile<MeshForModelFileAsset>(filename);
		m_Content = *ma;
	}
}

void SpaceGameEngine::MeshComponent::InitFromMemory(int VertexSize, int IndexSize, DefaultVertex * pVertices, unsigned int* pIndices)
{
	m_Content.m_Vertices.clear();
	m_Content.m_Indices.clear();
	m_Content.m_Vertices.resize(VertexSize);
	m_Content.m_Indices.resize(IndexSize);
	for (int i = 0; i < VertexSize; i++)
	{
		m_Content.m_Vertices[i] = pVertices[i];
	}
	for (int i = 0; i < IndexSize; i++)
	{
		m_Content.m_Indices[i] = pIndices[i];
	}
}

void SpaceGameEngine::MeshComponent::Start()
{
	if (m_Mode&ModelFileMode)
	{
		if (m_pFatherObject->GetRenderObject())
		{
			m_pFatherObject->GetRenderObject()->m_Type = RenderObjectType::Model;
			m_pFatherObject->GetRenderObject()->m_Mode = m_Mode;
			if (m_pFatherObject->GetRenderObject()->m_IfHaveMesh == false)
			{
				m_pFatherObject->GetRenderObject()->SetMesh(m_Content);
				m_pFatherObject->GetRenderObject()->m_IfHaveMesh = true;
			}
			if ((m_Mode&RenderObject::DynamicMode) == 0)
			{
				Vector<XMFLOAT3> points;
				for (const auto& i : m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset.m_Vertices)
				{
					points.push_back(i.m_Position);
				}
				m_pFatherObject->GetRenderObject()->m_BaseSpace = GetAxisAlignedBoundingBox(points);
				m_pFatherObject->GetRenderObject()->m_Space = TransformByWorldMatrix(m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Position, m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation, m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Scale, m_pFatherObject->GetRenderObject()->m_BaseSpace);
				m_pFatherObject->GetRenderObject()->m_pGlobalOctree = &Scene::GetMainScene()->m_GlobalOctree;
				m_pFatherObject->GetRenderObject()->m_pGlobalOctreeNode = m_pFatherObject->GetRenderObject()->m_pGlobalOctree->AddObject(GlobalOctreeData(m_pFatherObject->GetRenderObject()->m_Space, m_pFatherObject));
			}
		}
		else
			ThrowError("物体对象不能没有RenderObject");
	}
}

void SpaceGameEngine::MeshComponent::Run(float DeltaTime)
{
	if (m_pFatherObject->GetRenderObject())
	{
		if ((m_Mode&RenderObject::DynamicMode) == 0)
		{
			if (m_pFatherObject->GetComponentByMessage(Event::PositionChange) ||
				m_pFatherObject->GetComponentByMessage(Event::RotationChange) ||
				m_pFatherObject->GetComponentByMessage(Event::ScaleChange))
			{
				bool if_recompute = true;

				if (m_pFatherObject->GetComponentByMessage(Event::RotationChange) &&
					(m_pFatherObject->GetComponentByMessage(Event::PositionChange) == nullptr) &&
					(m_pFatherObject->GetComponentByMessage(Event::ScaleChange) == nullptr))
				{
					static XMFLOAT3 rotation = m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation;
					if (rotation != m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation)
					{
						auto ro_now = m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation;
						if ((rotation.x == ro_now.x && (m_Mode&RenderObject::XAxisAlignedMode)) ||
							(rotation.y == ro_now.y && (m_Mode&RenderObject::YAxisAlignedMode)) ||
							(rotation.z == ro_now.z && (m_Mode&RenderObject::ZAxisAlignedMode)))
						{
							rotation = ro_now;
							if_recompute = false;
						}
					}
				}

				if (if_recompute)
				{
					m_pFatherObject->GetRenderObject()->m_Space = TransformByWorldMatrix(m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Position, m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Rotation, m_pFatherObject->GetRenderObject()->m_TransformAsset.m_Scale, m_pFatherObject->GetRenderObject()->m_BaseSpace);
					if (m_pFatherObject->GetRenderObject()->m_pGlobalOctreeNode)
					{
						m_pFatherObject->GetRenderObject()->m_pGlobalOctreeNode->DeleteObjectData(m_pFatherObject);
						m_pFatherObject->GetRenderObject()->m_pGlobalOctreeNode = m_pFatherObject->GetRenderObject()->m_pGlobalOctree->AddObject(GlobalOctreeData(m_pFatherObject->GetRenderObject()->m_Space, m_pFatherObject));
					}
					else
						m_pFatherObject->GetRenderObject()->m_pGlobalOctreeNode = m_pFatherObject->GetRenderObject()->m_pGlobalOctree->UpdateObject(GlobalOctreeData(m_pFatherObject->GetRenderObject()->m_Space, m_pFatherObject));
				}
			}
		}
	}
}

void SpaceGameEngine::MeshComponent::Copy(Component * pc)
{
	if (pc)
	{
		if (pc->GetTypeName() == m_TypeName)
		{
			m_Mode = pc->GetMode();
			m_pAsset = pc->GetAsset();
			auto src = dynamic_cast<MeshComponent*>(pc);
			if (m_Mode&ModelFileMode)
			{
				m_Content = src->m_Content;
				if (m_pFatherObject->GetRenderObject() && pc->GetFatherObject()->GetRenderObject())
				{
					m_pFatherObject->GetRenderObject()->SetMesh(m_Content);
					m_pFatherObject->GetRenderObject()->m_IfHaveMesh = true;
				}
			}
		}
		else
		{
			ThrowError("dst's type must equal to src's type");
			return;
		}
	}
	else
		ThrowError("component can not be nullptr");
}

void SpaceGameEngine::MeshComponent::SetMesh(const MeshForModelFileAsset & mmfa)
{
	if (m_Mode&ModelFileMode)
	{
		m_Content = mmfa;
		if (m_pFatherObject)
		{
			if (m_pFatherObject->GetRenderObject())
			{
				if (m_pFatherObject->GetRenderObject()->m_IfHaveMesh)
					m_pFatherObject->GetRenderObject()->SetMesh(m_Content);
			}
		}
	}
}

MeshForModelFileAsset SpaceGameEngine::MeshComponent::GetMesh()
{
	return m_Content;
}
