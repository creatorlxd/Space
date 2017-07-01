#include"stdafx.h"
#include "../Include/Mesh.h" 

REGISTERCOMPONENTCLASS(MeshComponent);

MeshComponent::MeshComponent()
{
	m_Mode = 0;
	m_TypeName = "MeshComponent";
	if (SpaceEngineWindow != nullptr)
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

void MeshComponent::WriteInVertexBuffer(CUSTOMVERTEX* pVertices)
{
	m_pVertexBuffer->Lock(0, 0, (void**)&m_pVertices, 0);
	memcpy(m_pVertices, pVertices, m_VertexSize * sizeof(CUSTOMVERTEX));
	m_pVertexBuffer->Unlock();
}

void MeshComponent::WriteInIndexBuffer(WORD* pIndices)
{
	m_pIndexBuffer->Lock(0, 0, (void**)&m_pIndices, 0);
	memcpy(m_pIndices, pIndices, m_IndexSize * sizeof(WORD));
	m_pIndexBuffer->Unlock();
}

void MeshComponent::Init(int VertexSize, int IndexSize, CUSTOMVERTEX * pVertices, WORD * pIndices)
{
	m_VertexSize = VertexSize;
	m_IndexSize = IndexSize;
	m_PrimitiveCount = m_IndexSize / 3;
	m_pD3DDevice->CreateVertexBuffer(m_VertexSize * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);
	m_pD3DDevice->CreateIndexBuffer(m_IndexSize * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);
	WriteInVertexBuffer(pVertices);
	WriteInIndexBuffer(pIndices);
}

void MeshComponent::InitFromFile(const std::string & filename, int mode)
{
	switch (mode)
	{
	case ModelFileMode:
	{
		m_Mode = ModelFileMode;
		std::fstream file;
		file.open(filename, std::ios::in);
		int VertexSize = 0, IndexSize = 0;
		file >> VertexSize;
		file >> IndexSize;
		CUSTOMVERTEX* Vertices = new CUSTOMVERTEX[VertexSize];
		WORD* Indices = new WORD[IndexSize];
		for (int i = 0; i < VertexSize; i++)
		{
			file >> Vertices[i].x >> Vertices[i].y >> Vertices[i].z >> Vertices[i].nx >> Vertices[i].ny >> Vertices[i].nz >> Vertices[i].u >> Vertices[i].v;
		}
		for (int j = 0; j < IndexSize; j++)
		{
			file >> Indices[j];
		}
		Init(VertexSize, IndexSize, Vertices, Indices);
		delete[] Vertices;
		delete[] Indices;
		file.close();
		break;
	}
	case XMeshFileMode:
	{
		m_Mode = XMeshFileMode;
		auto tfilename = StringToTString(filename);

		D3DXLoadMeshFromX(tfilename.c_str(), D3DXMESH_MANAGED, m_pD3DDevice, &m_pAdjBuffer, &m_pMtrlBuffer, NULL, &m_NumMaterials, &m_pMesh);
		D3DXMATERIAL *pMtrls = (D3DXMATERIAL*)m_pMtrlBuffer->GetBufferPointer();	//创建一个D3DXMATERIAL结构体用于读取材质和纹理信息
		m_pMaterials = new D3DMATERIAL9[m_NumMaterials];
		m_pTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
		for (DWORD i = 0; i < m_NumMaterials; i++)
		{
			//获取材质
			m_pMaterials[i] = pMtrls[i].MatD3D;

			//创建一下纹理对象  
			m_pTextures[i] = NULL;
			D3DXCreateTextureFromFileA(m_pD3DDevice, pMtrls[i].pTextureFilename, &m_pTextures[i]);
		}

		break;
	}
	default:
	{
		ThrowError(tstring(L"需要设定Mesh的模型类型!!!"));
		break;
	}
	}
}

void MeshComponent::Run(float DeltaTime)
{
	switch (m_Mode)
	{
	case ModelFileMode:
	{
		m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		m_pD3DDevice->SetIndices(m_pIndexBuffer);
		m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_VertexSize, 0, (UINT)m_PrimitiveCount);
		break;
	}
	case XMeshFileMode:
	{
		for (DWORD i = 0; i < m_NumMaterials; i++)
		{
			m_pD3DDevice->SetMaterial(&m_pMaterials[i]);
			m_pD3DDevice->SetTexture(0, m_pTextures[i]);
			m_pMesh->DrawSubset(i);
		}
		break;
	}
	default:
	{
		ThrowError(tstring(L"需要设定Mesh的模型类型!!!"));
		break;
	}
	}
}
