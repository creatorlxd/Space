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
				m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset = MeshForModelFileAsset();
				SafeRelease(m_pFatherObject->GetRenderObject()->m_pVertexBuffer);
				SafeRelease(m_pFatherObject->GetRenderObject()->m_pIndexBuffer);
				m_pFatherObject->GetRenderObject()->m_IfHaveMesh = false;
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
	}
}

void SpaceGameEngine::MeshComponent::InitFromMemory(int VertexSize, int IndexSize, DefaultVertex * pVertices, unsigned int* pIndices)
{
	m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset.m_Vertices.clear();
	m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset.m_Indices.clear();
	m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset.m_Vertices.resize(VertexSize);
	m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset.m_Indices.resize(IndexSize);
	for (int i = 0; i < VertexSize; i++)
	{
		m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset.m_Vertices[i] = pVertices[i];
	}
	for (int i = 0; i < IndexSize; i++)
	{
		m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset.m_Indices[i] = pIndices[i];
	}
}

void SpaceGameEngine::MeshComponent::Start()
{
	m_pFatherObject->GetRenderObject()->m_Mode = m_Mode;
	if (m_Mode&ModelFileMode)
	{
		if (m_pFatherObject->GetRenderObject())
		{
			if (m_pFatherObject->GetRenderObject()->m_IfHaveMesh == false)
			{
				m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset = *(dynamic_cast<MeshForModelFileAsset*>(const_cast<Asset*>(m_pAsset)));
				m_pFatherObject->GetRenderObject()->m_IfHaveMesh = true;
			}
		}
		else
			ThrowError("物体对象不能没有RenderObject");
	}
}

void SpaceGameEngine::MeshComponent::Run(float DeltaTime)
{
	
}

void SpaceGameEngine::MeshComponent::Copy(Component * pc)
{
	if (pc)
	{
		if (pc->GetTypeName() == m_TypeName)
		{
			m_Mode = pc->GetMode();
			m_pAsset = pc->GetAsset();
			if (m_Mode&ModelFileMode)
			{
				if (m_pFatherObject->GetRenderObject() && pc->GetFatherObject()->GetRenderObject())
				{
					SafeRelease(m_pFatherObject->GetRenderObject()->m_pVertexBuffer);
					SafeRelease(m_pFatherObject->GetRenderObject()->m_pIndexBuffer);
					m_pFatherObject->GetRenderObject()->m_MeshForModelFileAsset = pc->GetFatherObject()->GetRenderObject()->m_MeshForModelFileAsset;
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
