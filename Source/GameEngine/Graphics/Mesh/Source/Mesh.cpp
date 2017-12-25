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
#include"stdafx.h"
#include "../Include/Mesh.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(MeshComponent);

SpaceGameEngine::MeshComponent::MeshComponent() :m_ObjectOctree(&m_Vertices)
{
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_TypeName = "MeshComponent";
	m_pTransform = nullptr;
	m_pGlobalOctreeNode = nullptr;
}

void SpaceGameEngine::MeshComponent::Release()
{
	if (m_pTransform)
	{
		Scene::GetMainScene()->m_GlobalOctree.DeleteObject(m_pFatherObject);
	}
	if ((m_Mode&MeshComponent::WholeMode) == 0)
		m_ObjectOctree.Release();
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
	m_Vertices.clear();
	m_Indices.clear();
	m_pTransform = nullptr;
	m_pGlobalOctreeNode = nullptr;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
}

SpaceGameEngine::MeshComponent::~MeshComponent()
{
	Release();
}

void SpaceGameEngine::MeshComponent::InitFromMemory(int VertexSize, int IndexSize, DefaultVertex * pVertices, unsigned int* pIndices)
{
	m_Vertices.clear();
	m_Indices.clear();
	m_Vertices.resize(VertexSize);
	m_Indices.resize(IndexSize);
	for (int i = 0; i < VertexSize; i++)
	{
		m_Vertices[i] = pVertices[i];
	}
	for (int i = 0; i < IndexSize; i++)
	{
		m_Indices[i] = pIndices[i];
	}
}

void SpaceGameEngine::MeshComponent::InitFromFile(const std::string & filename, int mode)
{
	m_Mode = mode;

	if (m_Mode&ModelFileMode)
	{
		const MeshForModelFileAsset* ma = ReadAssetFromFile<MeshForModelFileAsset>(filename);
		m_Vertices = ma->m_Vertices;
		m_Indices = ma->m_Indices;
	}
}

void SpaceGameEngine::MeshComponent::Start()
{
	InitVertexBuffer();
	InitIndexBuffer();
	if (m_pFatherObject == nullptr)
	{
		ThrowError("the father object of mesh component can not be nullptr");
	}
	m_pTransform = m_pFatherObject->GetComponent<TransformComponent>();
	if (m_pTransform == nullptr)
	{
		ThrowError("the mesh need transform");
	}
	if ((m_Mode&MeshComponent::WholeMode) == 0)
		m_ObjectOctree.BuildTree(m_Indices);
	if ((m_Mode&MeshComponent::DynamicMode) == 0)
	{
		Vector<XMFLOAT3> points;
		for (const auto& i : m_Vertices)
		{
			points.push_back(i.m_Position);
		}
		m_BaseSpace = GetAxisAlignedBoundingBox(points);
		m_Space = TransformByWorldMatrix(m_pTransform->GetPosition(), m_pTransform->GetRotation(), m_pTransform->GetScale(), m_BaseSpace);
		m_pGlobalOctreeNode=Scene::GetMainScene()->m_GlobalOctree.AddObject(GlobalOctreeData(m_Space, m_pFatherObject));
	}
}

void SpaceGameEngine::MeshComponent::Run(float DeltaTime)
{
	if ((m_Mode&MeshComponent::DynamicMode) == 0)
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
				static XMFLOAT3 rotation = m_pTransform->GetRotation();
				if (rotation != m_pTransform->GetRotation())
				{
					auto ro_now = m_pTransform->GetRotation();
					if ((rotation.x == ro_now.x && (m_Mode&MeshComponent::XAxisAlignedMode)) ||
						(rotation.y == ro_now.y && (m_Mode&MeshComponent::YAxisAlignedMode)) ||
						(rotation.z == ro_now.z && (m_Mode&MeshComponent::ZAxisAlignedMode)))
					{
						rotation = ro_now;
						if_recompute = false;
					}
				}
			}

			if (if_recompute)
			{
				m_Space = TransformByWorldMatrix(m_pTransform->GetPosition(), m_pTransform->GetRotation(), m_pTransform->GetScale(), m_BaseSpace);
				if (m_pGlobalOctreeNode)
				{
					m_pGlobalOctreeNode->DeleteObjectData(m_pFatherObject);
					m_pGlobalOctreeNode = Scene::GetMainScene()->m_GlobalOctree.AddObject(GlobalOctreeData(m_Space, m_pFatherObject));
				}
				else
					m_pGlobalOctreeNode = Scene::GetMainScene()->m_GlobalOctree.UpdateObject(GlobalOctreeData(m_Space, m_pFatherObject));
			}
		}
	}
	if (m_pFatherObject->IfRender() == false)
	{
		return;
	}
	if ((m_Mode&MeshComponent::WholeMode) == 0)
	{
		auto indices_buffer = m_ObjectOctree.Run(m_pTransform->GetPosition(), m_pTransform->GetRotation(), m_pTransform->GetScale());
		D3D11_MAPPED_SUBRESOURCE mappeddata;
		HR(SpaceEngineWindow->GetD3DDeviceContext()->Map(m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappeddata));
		unsigned int* pi = reinterpret_cast<unsigned int*>(mappeddata.pData);
		for (unsigned int i = 0; i < indices_buffer.size(); i++)
			pi[i] = indices_buffer[i];
		SpaceEngineWindow->GetD3DDeviceContext()->Unmap(m_pIndexBuffer, 0);
		unsigned int v_strides = sizeof(DefaultVertex);
		unsigned int v_offset = 0;
		GetGame()->m_Window.GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &v_strides, &v_offset);
		GetGame()->m_Window.GetD3DDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		D3DX11_TECHNIQUE_DESC techDesc;
		SpaceEngineWindow->GetEffectShader().m_pTechnique->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			SpaceEngineWindow->GetEffectShader().m_pTechnique->GetPassByIndex(p)->Apply(0, SpaceEngineWindow->GetD3DDeviceContext());

			SpaceEngineWindow->GetD3DDeviceContext()->DrawIndexed(indices_buffer.size(), 0, 0);
		}
	}
	else
	{
		unsigned int v_strides = sizeof(DefaultVertex);
		unsigned int v_offset = 0;
		GetGame()->m_Window.GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &v_strides, &v_offset);
		GetGame()->m_Window.GetD3DDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		D3DX11_TECHNIQUE_DESC techDesc;
		SpaceEngineWindow->GetEffectShader().m_pTechnique->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			SpaceEngineWindow->GetEffectShader().m_pTechnique->GetPassByIndex(p)->Apply(0, SpaceEngineWindow->GetD3DDeviceContext());

			SpaceEngineWindow->GetD3DDeviceContext()->DrawIndexed(m_Indices.size(), 0, 0);
		}
	}
}

void SpaceGameEngine::MeshComponent::InitVertexBuffer()
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth = sizeof(DefaultVertex)*m_Vertices.size();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initdata;
	initdata.pSysMem = m_Vertices.data();

	HR(GetGame()->m_Window.GetD3DDevice()->CreateBuffer(&desc, &initdata, &m_pVertexBuffer));
}

void SpaceGameEngine::MeshComponent::InitIndexBuffer()
{
	D3D11_BUFFER_DESC desc;
	if ((m_Mode&MeshComponent::WholeMode) == 0)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(unsigned int)*m_Indices.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
	}
	else
	{
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(unsigned int)*m_Indices.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
	}

	D3D11_SUBRESOURCE_DATA initdata;
	initdata.pSysMem = m_Indices.data();

	HR(GetGame()->m_Window.GetD3DDevice()->CreateBuffer(&desc, &initdata, &m_pIndexBuffer));
}
