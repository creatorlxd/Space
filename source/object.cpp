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

void object::InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename, LPCTSTR photoname)
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
	SetTextureFromFile(g_pd3dDevice, photoname, m_pTexture);
	file.close();
}

void object::InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename, LPCTSTR photoname, std::string TextureFile)
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
		file >> Vertices[i].x >> Vertices[i].y >> Vertices[i].z >> Vertices[i].nx >> Vertices[i].ny >> Vertices[i].nz >> Vertices[i].u >> Vertices[i].v;
	}
	for (int j = 0;j < IndexSize;j++)
	{
		file >> Indices[j];
	}
	init(g_pd3dDevice, VertexSize, IndexSize, Vertices, Indices);
	SetTextureFromFileEx(g_pd3dDevice, photoname, TextureFile, m_pTexture);
	file.close();
}

void object::InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename,std::string lightfilename, LPCTSTR photoname)
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
		file >> Vertices[i].x >> Vertices[i].y >> Vertices[i].z >> Vertices[i].nx >> Vertices[i].ny >> Vertices[i].nz >> Vertices[i].u >> Vertices[i].v;
	}
	for (int j = 0;j < IndexSize;j++)
	{
		file >> Indices[j];
	}
	init(g_pd3dDevice, VertexSize, IndexSize, Vertices, Indices);
	SetTextureFromFile(g_pd3dDevice, photoname, m_pTexture);
	std::fstream lightfile;
	lightfile.open(lightfilename, std::ios::in);
	std::string true_lightfilename;
	int light_flag = 0;
	lightfile >> true_lightfilename;
	lightfile >> light_flag;
	lightfile >> m_lx >> m_ly >> m_lz;
	switch (light_flag)
	{
	case 0: {
		InitPointLightFromFile(g_pd3dDevice, true_lightfilename);
		break;
	}
	case 1: {
		InitDirectionalLightFromFile(g_pd3dDevice, true_lightfilename);
		break;
	}
	case 2: {
		InitSpotLightFromFile(g_pd3dDevice, true_lightfilename);
		break;
	}
	default: {
		InitPointLightFromFile(g_pd3dDevice, true_lightfilename);
		break;
	}
	}
	lightfile.close();

	file.close();
}

object::~object()
{
	SAFE_RELEASE(m_pVertexBuffer)
	SAFE_RELEASE(m_pIndexBuffer)
	SAFE_RELEASE(m_pAdjBuffer)
	SAFE_RELEASE(m_pMtrlBuffer)
	if (m_pMaterials != NULL)
	{
		delete[] m_pMaterials;
	}
	if (m_pTextures != NULL)
	{
		delete[] m_pTextures;
	}
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
	m_rxa = 0;
	m_rxv = 0;
	m_rya = 0;
	m_ryv = 0;
	m_rza = 0;
	m_rzv = 0;
	m_pTexture = NULL;
	m_IfXFile = false;
	m_pAdjBuffer = NULL;
	m_pMtrlBuffer = NULL;
	m_NumMaterials = 0;
	m_pMesh = NULL;
	m_pMaterials = NULL;
	m_pTextures = NULL;
}

object::object(int & i)
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
	m_rxa = 0;
	m_rxv = 0;
	m_rya = 0;
	m_ryv = 0;
	m_rza = 0;
	m_rzv = 0;
	m_Light.SetLightNumber(i);
	m_pTexture = NULL;
	m_IfXFile = false;
	m_pAdjBuffer = NULL;
	m_pMtrlBuffer = NULL;
	m_NumMaterials = 0;
	m_pMesh = NULL;
	m_pMaterials = NULL;
	m_pTextures = NULL;
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
	if (m_IfXFile == false)
	{
		g_pd3dDevice->SetTexture(0, m_pTexture);
		g_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->SetIndices(m_pIndexBuffer);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_VertexSize, 0, (UINT)m_PrimitiveCount);
	}
	else
	{
		for (DWORD i = 0; i < m_NumMaterials; i++)
		{
			g_pd3dDevice->SetMaterial(&m_pMaterials[i]);
			g_pd3dDevice->SetTexture(0, m_pTextures[i]);
			m_pMesh->DrawSubset(i);
		}
	}
}

void object::InitFromXFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR filename)
{
	m_IfXFile = true;
	D3DXLoadMeshFromX(filename, D3DXMESH_MANAGED, g_pd3dDevice, &m_pAdjBuffer, &m_pMtrlBuffer, NULL, &m_NumMaterials, &m_pMesh);
	D3DXMATERIAL *pMtrls = (D3DXMATERIAL*)m_pMtrlBuffer->GetBufferPointer();	//创建一个D3DXMATERIAL结构体用于读取材质和纹理信息
	m_pMaterials = new D3DMATERIAL9[m_NumMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	for (DWORD i = 0;i < m_NumMaterials;i++)
	{
		//获取材质
		m_pMaterials[i] = pMtrls[i].MatD3D;

		//创建一下纹理对象  
		m_pTextures[i] = NULL;
		D3DXCreateTextureFromFileA(g_pd3dDevice, pMtrls[i].pTextureFilename, &m_pTextures[i]);
	}
}

void object::InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename)
{
	m_Light.SetPointLightsFromFile(filename);
	m_Light.RegisterLight(g_pd3dDevice);
}

void object::InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename)
{
	m_Light.SetDirectionalLightsFromFile(filename);
	m_Light.RegisterLight(g_pd3dDevice);
}

void object::InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename)
{
	m_Light.SetSpotLightsFromFile(filename);
	m_Light.RegisterLight(g_pd3dDevice);
}

void object::LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	m_Light.SetLightPosition(m_lx + m_Position.x, m_ly + m_Position.y, m_lz + m_Position.z);
	D3DXVECTOR3 buf;
	buf = m_Light.m_LightContent.Direction;
	D3DXMATRIX matrx, matry, matrz;
	D3DXMatrixRotationX(&matrx, m_rxv);
	D3DXMatrixRotationY(&matry, m_ryv);
	D3DXMatrixRotationZ(&matrz, m_rzv);
	D3DXVec3TransformCoord(&buf, &buf, &matrx);
	D3DXVec3TransformCoord(&buf, &buf, &matry);
	D3DXVec3TransformCoord(&buf, &buf, &matrz);
	m_Light.SetLightDirection(buf.x, buf.y, buf.z);
	m_Light.BeginLightPrint(g_pd3dDevice);
}

void object::GetTime()
{
	float TimeBuffer=0;
	if (m_TimeNow == 0)
	{
		m_TimeNow = timeGetTime()*0.001f;
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		m_TimeChange = TimeBuffer - m_TimeNow;
		m_TimeNow = timeGetTime()*0.001f;
	}
}

void object::SetXYZ(float x, float y, float z)
{
	m_Position = D3DXVECTOR3(x, y, z);
}

void object::InitPhysicsFromFile(std::string filename)
{
}

void object::SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matBuf;
	D3DXMatrixTranslation(&matWorld, m_Position.x, m_Position.y, m_Position.z);
	if (m_rxv != 0)
	{
		D3DXMatrixRotationX(&matBuf, m_rxv);
		matWorld = matBuf*matWorld;
	}
	if (m_ryv != 0)
	{
		D3DXMatrixRotationY(&matBuf, m_ryv);
		matWorld = matBuf*matWorld;
	}
	if (m_rzv != 0)
	{
		D3DXMatrixRotationZ(&matBuf, m_rzv);
		matWorld = matBuf*matWorld;
	}
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

void object::GetG()
{
}

void object::RunMovingGraphics()
{
}
