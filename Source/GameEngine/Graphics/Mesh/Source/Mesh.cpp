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

SpaceGameEngine::MeshComponent::MeshComponent()
{
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_TypeName = "MeshComponent";
}

void SpaceGameEngine::MeshComponent::Release()
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
	m_Vertices.clear();
	m_Indices.clear();
}

SpaceGameEngine::MeshComponent::~MeshComponent()
{
	Release();
}

void SpaceGameEngine::MeshComponent::InitFromMemory(int VertexSize, int IndexSize, DefaultVertex * pVertices, WORD * pIndices)
{
	m_Vertices.clear();
	m_Indices.clear();
	for (int i = 0; i < VertexSize; i++)
	{
		m_Vertices.push_back(pVertices[i]);
	}
	for (int i = 0; i < IndexSize; i++)
	{
		m_Indices.push_back(pIndices[i]);
	}
}

void SpaceGameEngine::MeshComponent::InitFromFile(const std::string & filename, int mode)
{
	m_Mode = mode;
	switch (m_Mode)
	{
	case ModelFileMode:
	{
		int v_s, i_s;
		File file(filename, FileMode::Read);

		file >> v_s >> i_s;

		m_Vertices.clear();
		m_Indices.clear();

		DefaultVertex vbuff;
		unsigned int ibuff;

		for (int i = 0; i < v_s; i++)
		{
			file >> vbuff.m_Position.x >> vbuff.m_Position.y >> vbuff.m_Position.z;
			file >> vbuff.m_Normal.x >> vbuff.m_Normal.y >> vbuff.m_Normal.z;
			file >> vbuff.m_TextureCoord.x >> vbuff.m_TextureCoord.y;
			m_Vertices.push_back(vbuff);
		}

		for (int i = 0; i < i_s; i++)
		{
			file >> ibuff;
			m_Indices.push_back(ibuff);
		}

		file.Close();
		break;
	}
	default:
	{
		break;
	}
	}
}

void SpaceGameEngine::MeshComponent::Start()
{
	InitVertexBuffer();
	InitIndexBuffer();
	
	if ((m_Mode&MeshComponent::DynamicMode) == 0)
	{
		if (m_pFatherObject == nullptr)
		{
			ThrowError("the father object of mesh component can not be nullptr");
		}
		Vector<XMFLOAT3> points;
		for (const auto& i : m_Vertices)
		{
			points.push_back(i.m_Position);
		}
		m_Space = GetAxisAlignedBoundingBox(points);
		Scene::GetMainScene()->m_GlobalOctree.AddObject(std::make_pair(m_Space, m_pFatherObject));
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
			Vector<XMFLOAT3> points;
			TransformComponent* transform = dynamic_cast<TransformComponent*>(m_pFatherObject->GetComponent("TransformComponent"));
			for (const auto& i : m_Vertices)
			{
				points.push_back(TransformByWorldMatrix(transform->GetPosition(), transform->GetRotation(), transform->GetScale(), i.m_Position));
			}
			m_Space = GetAxisAlignedBoundingBox(points);
			Scene::GetMainScene()->m_GlobalOctree.UpdateObject(std::make_pair(m_Space, m_pFatherObject));
		}
	}
	if (m_pFatherObject->IfRender() == false)
	{
		return;
	}
	unsigned int v_strides = sizeof(DefaultVertex);
	unsigned int v_offset = 0;
	GetGame()->m_Window.GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer,&v_strides, &v_offset);
	GetGame()->m_Window.GetD3DDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	D3DX11_TECHNIQUE_DESC techDesc;
	SpaceEngineWindow->GetEffectShader().m_pTechnique->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		SpaceEngineWindow->GetEffectShader().m_pTechnique->GetPassByIndex(p)->Apply(0, SpaceEngineWindow->GetD3DDeviceContext());

		SpaceEngineWindow->GetD3DDeviceContext()->DrawIndexed(m_Indices.size(), 0, 0);
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
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth = sizeof(unsigned int)*m_Indices.size();
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initdata;
	initdata.pSysMem = m_Indices.data();
	
	HR(GetGame()->m_Window.GetD3DDevice()->CreateBuffer(&desc, &initdata, &m_pIndexBuffer));
}
