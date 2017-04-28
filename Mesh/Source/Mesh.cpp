#include"stdafx.h"
#include "../Include/Mesh.h" 

ComponentManager::NewComponent<MeshComponent> MeshComponent::NewComponent;

MeshComponent::MeshComponent()
{
	m_Mode = 0;
	m_TypeName = "MeshComponent";
	if (SpaceEngineWindow != NULL)
	{
		m_pD3DDevice = SpaceEngineWindow->GetD3DDevice();
	}
	else
	{
		m_pD3DDevice = nullptr;
	}

	m_VertexSize = 0;
	m_IndexSize = 0;
	m_PrimitiveCount = 0;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_pVertices = NULL;
	m_pIndices = NULL;
	m_pAdjBuffer = NULL;
	m_pMtrlBuffer = NULL;
	m_NumMaterials = 0;
	m_pMesh = NULL;
	m_pMaterials = NULL;
	m_pTextures = NULL;
}

void MeshComponent::Release()
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
	SafeRelease(m_pAdjBuffer);
	SafeRelease(m_pMtrlBuffer);
	SafeRelease(m_pMesh);
	if (m_pMaterials != NULL)
	{
		delete[] m_pMaterials;
	}
	if (m_pTextures != NULL)
	{
		for (DWORD i = 0; i < m_NumMaterials; i++)
		{
			SafeRelease(m_pTextures[i]);
		}
		delete[] m_pTextures;
	}
}

MeshComponent::~MeshComponent()
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
	SafeRelease(m_pAdjBuffer);
	SafeRelease(m_pMtrlBuffer);
	SafeRelease(m_pMesh);
	if (m_pMaterials != NULL)
	{
		delete[] m_pMaterials;
	}
	if (m_pTextures != NULL)
	{
		for (DWORD i = 0; i < m_NumMaterials; i++)
		{
			SafeRelease(m_pTextures[i]);
		}
		delete[] m_pTextures;
	}
}
