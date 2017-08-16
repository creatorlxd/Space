#include"stdafx.h"
#include "../Include/Mesh.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(MeshComponent);

SpaceGameEngine::MeshComponent::MeshComponent()
{
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
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
	switch (mode)
	{
	case ModelFileMode:
	{
		int v_s, i_s;
		std::fstream file(filename, std::ios::in);

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

		file.close();

		InitVertexBuffer();
		InitIndexBuffer();
		break;
	}
	default:
	{
		break;
	}
	}
}

void SpaceGameEngine::MeshComponent::Run(float DeltaTime)
{
	unsigned int v_strides = sizeof(DefaultVertex);
	GetGame()->m_Window.GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer,&v_strides, 0);
	GetGame()->m_Window.GetD3DDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	GetGame()->m_Window.GetD3DDeviceContext()->DrawIndexed(m_Indices.size(), 0, 0);
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
