#include "object.h"


void object::init(LPDIRECT3DDEVICE9 g_pd3dDevice, int VertexSize, int IndexSize, CUSTOMVERTEX Vertices[], WORD Indices[])
{
	
	m_VertexSize = VertexSize;
	m_IndexSize = IndexSize;
	m_PrimitiveCount = m_IndexSize/3;
	g_pd3dDevice->CreateVertexBuffer(m_VertexSize*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);
	g_pd3dDevice->CreateIndexBuffer(m_IndexSize*sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);
	WriteInVertexBuffer(Vertices);
	WriteInIndexBuffer(Indices);
}

void object::InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,std::string filename)
{
	std::fstream file;
	file.open(filename, std::ios::in);
	int VertexSize, IndexSize;
	file >> VertexSize;
	file >> IndexSize;
	CUSTOMVERTEX* Vertices = new CUSTOMVERTEX[VertexSize];
	WORD* Indices = new WORD[IndexSize];
	for (int i = 0;i < VertexSize;i++)
	{
		file >> Vertices[i].x >> Vertices[i].y >> Vertices[i].z >>Vertices[i].nx>> Vertices[i].ny>> Vertices[i] .nz>> Vertices[i].u >> Vertices[i].v;
	}
	for (int j = 0;j < IndexSize;j++)
	{
		file >> Indices[j];
	}
	init(g_pd3dDevice, VertexSize, IndexSize, Vertices, Indices);
	file.close();
}

object::~object()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

object::object()
{
	m_VertexSize = 0;
	m_IndexSize = 0;
	m_PrimitiveCount = 0;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	mpVertices = NULL;
	mpIndices = NULL;
	m_TimeNow = 0;
	m_TimeChange = 0;
	m_a = { 0,0,0 };
	m_F = { 0,0,0 };
	m_m = 0;
}

void object::WriteInVertexBuffer(CUSTOMVERTEX Vertices[])
{
	m_pVertexBuffer->Lock(0, 0, (void**)&mpVertices, 0);
	memcpy(mpVertices, Vertices, m_VertexSize*sizeof(CUSTOMVERTEX));
	m_pVertexBuffer->Unlock();
}

void object::WriteInIndexBuffer(WORD Indices[])
{
	m_pIndexBuffer->Lock(0, 0, (void**)&mpIndices, 0);
	memcpy(mpIndices, Indices, m_IndexSize*sizeof(WORD));
	m_pIndexBuffer->Unlock();
}

void object::ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->SetIndices(m_pIndexBuffer);
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_VertexSize, 0,(UINT)m_PrimitiveCount);
}

void object::GetTime()
{
	time_t TimeBuffer=0;
	if (m_TimeNow != 0)
	{
		m_TimeNow = time(NULL);
	}
	else
	{
		TimeBuffer = time(NULL);
		m_TimeChange = TimeBuffer - m_TimeNow;
		m_TimeNow = time(NULL);
	}
}

void object::InitPhysics()
{
}

void object::GetG()
{
}

void object::RunMovingGraphics()
{
}
