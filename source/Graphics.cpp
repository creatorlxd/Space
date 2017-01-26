#include"stdafx.h"
#include"Graphics.h"

void GraphicsComponent::Init(LPDIRECT3DDEVICE9 g_pd3dDevice, int VertexSize, int IndexSize, CUSTOMVERTEX Vertices[], WORD Indices[])
{
	m_VertexSize = VertexSize;
	m_IndexSize = IndexSize;
	m_PrimitiveCount = m_IndexSize / 3;
	g_pd3dDevice->CreateVertexBuffer(m_VertexSize*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);
	g_pd3dDevice->CreateIndexBuffer(m_IndexSize*sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);
	WriteInVertexBuffer(Vertices);
	WriteInIndexBuffer(Indices);
}

void GraphicsComponent::InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string & filename, LPCTSTR photoname, const std::string& materialname)
{
	if(materialname!="NULL")
		InitMaterialFromFile(m_Material, materialname);
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
	Init(g_pd3dDevice, VertexSize, IndexSize, Vertices, Indices);
	SetTextureFromFile(g_pd3dDevice, photoname, m_pTexture);
	file.close();
}

void GraphicsComponent::InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string & filename, LPCTSTR photoname, const std::string & TextureFile, const std::string& materialname)
{
	if (materialname != "NULL")
		InitMaterialFromFile(m_Material, materialname);
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
	Init(g_pd3dDevice, VertexSize, IndexSize, Vertices, Indices);
	SetTextureFromFileEx(g_pd3dDevice, photoname, TextureFile, m_pTexture);
	file.close();
}

void GraphicsComponent::InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string & filename, const std::string & lightfilename, LPCTSTR photoname, const std::string& materialname)
{
	if (materialname != "NULL")
		InitMaterialFromFile(m_Material, materialname);
	m_IfLight = true;
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
	Init(g_pd3dDevice, VertexSize, IndexSize, Vertices, Indices);
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

GraphicsComponent::~GraphicsComponent()
{
	SAFE_RELEASE(m_pVertexBuffer)
	SAFE_RELEASE(m_pIndexBuffer)
	SAFE_RELEASE(m_pAdjBuffer)
	SAFE_RELEASE(m_pMtrlBuffer)
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture)
	if (m_pMaterials != NULL)
	{
		delete[] m_pMaterials;
	}
	if (m_pTextures != NULL)
	{
		for (DWORD i = 0;i < m_NumMaterials;i++)
		{
			SAFE_RELEASE(m_pTextures[i])
		}
		delete[] m_pTextures;
	}
}

GraphicsComponent::GraphicsComponent()
{
	m_VertexSize = 0;
	m_IndexSize = 0;
	m_PrimitiveCount = 0;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	mpVertices = NULL;
	mpIndices = NULL;
	m_Light.SetLightNumber(-1);
	m_pTexture = NULL;
	m_IfXFile = false;
	m_pAdjBuffer = NULL;
	m_pMtrlBuffer = NULL;
	m_NumMaterials = 0;
	m_pMesh = NULL;
	m_pMaterials = NULL;
	m_pTextures = NULL;
	m_IfLight = false;

	m_Material.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Emissive = D3DXCOLOR(0.00f, 0.0f, 0.0f, 1.0f);
	m_Material.Power = 1.0f;

}

GraphicsComponent::GraphicsComponent(int& i)
{
	m_VertexSize = 0;
	m_IndexSize = 0;
	m_PrimitiveCount = 0;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	mpVertices = NULL;
	mpIndices = NULL;
	m_Light.SetLightNumber(i);
	m_pTexture = NULL;
	m_IfXFile = false;
	m_pAdjBuffer = NULL;
	m_pMtrlBuffer = NULL;
	m_NumMaterials = 0;
	m_pMesh = NULL;
	m_pMaterials = NULL;
	m_pTextures = NULL;
	m_IfLight = false;

	m_Material.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Emissive = D3DXCOLOR(0.00f, 0.0f, 0.0f, 1.0f);
	m_Material.Power = 1.0f;

}

void GraphicsComponent::WriteInVertexBuffer(CUSTOMVERTEX Vertices[])
{
	m_pVertexBuffer->Lock(0, 0, (void**)&mpVertices, 0);
	memcpy(mpVertices, Vertices, m_VertexSize*sizeof(CUSTOMVERTEX));
	m_pVertexBuffer->Unlock();
}

void GraphicsComponent::WriteInIndexBuffer(WORD Indices[])
{
	m_pIndexBuffer->Lock(0, 0, (void**)&mpIndices, 0);
	memcpy(mpIndices, Indices, m_IndexSize*sizeof(WORD));
	m_pIndexBuffer->Unlock();
}

void GraphicsComponent::ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	if (m_IfXFile == false)
	{
		g_pd3dDevice->SetMaterial(&m_Material);
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

void GraphicsComponent::InitFromXFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR filename)	//不要用，不稳定。未完成！
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

void GraphicsComponent::InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string & filename)
{
	m_Light.SetPointLightFromFile(filename);
	m_Light.RegisterLight(g_pd3dDevice);
}

void GraphicsComponent::InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string & filename)
{
	m_Light.SetDirectionalLightFromFile(filename);
	m_Light.RegisterLight(g_pd3dDevice);
}

void GraphicsComponent::InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string & filename)
{
	m_Light.SetSpotLightFromFile(filename);
	m_Light.RegisterLight(g_pd3dDevice);
}

void GraphicsComponent::LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice, PhysicsComponent& physics)
{
	m_Light.SetLightPosition(m_lx + physics.m_Position.x, m_ly + physics.m_Position.y, m_lz + physics.m_Position.z);
	D3DXVECTOR3 buf;
	buf = m_Light.m_LightContent.Direction;
	D3DXMATRIX matrx, matry, matrz;
	D3DXMatrixRotationX(&matrx, physics.m_rxv);
	D3DXMatrixRotationY(&matry, physics.m_ryv);
	D3DXMatrixRotationZ(&matrz, physics.m_rzv);
	D3DXVec3TransformCoord(&buf, &buf, &matrx);
	D3DXVec3TransformCoord(&buf, &buf, &matry);
	D3DXVec3TransformCoord(&buf, &buf, &matrz);
	m_Light.SetLightDirection(buf.x, buf.y, buf.z);
	if (m_IfLight == true)
	{
		m_Light.BeginLightPrint(g_pd3dDevice);
	}
	else
	{
		m_Light.EndLightPrint(g_pd3dDevice);
	}
}

void GraphicsComponent::LightBeginPrint()
{
	m_IfLight = true;
}

void GraphicsComponent::LightEndPrint()
{
	m_IfLight = false;
}

void GraphicsComponent::ChangeTexture(LPDIRECT3DDEVICE9 g_pd3dDevice,LPCTSTR photoname)
{
	if (m_pTexture != NULL)
	{
		SAFE_RELEASE(m_pTexture)
	}
	SetTextureFromFile(g_pd3dDevice, photoname, m_pTexture);
}

void GraphicsComponent::ChangeTextureEx(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, const std::string & TextureFile)
{
	if (m_pTexture != NULL)
	{
		SAFE_RELEASE(m_pTexture)
	}
	SetTextureFromFileEx(g_pd3dDevice, photoname, TextureFile, m_pTexture);
}

void GraphicsComponent::SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice, PhysicsComponent& physics)
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matBuf;
	D3DXMatrixTranslation(&matWorld, physics.m_Position.x, physics.m_Position.y, physics.m_Position.z);
	if (physics.m_rxv != 0)
	{
		D3DXMatrixRotationX(&matBuf, physics.m_rxv);
		matWorld = matBuf*matWorld;
	}
	if (physics.m_ryv != 0)
	{
		D3DXMatrixRotationY(&matBuf, physics.m_ryv);
		matWorld = matBuf*matWorld;
	}
	if (physics.m_rzv != 0)
	{
		D3DXMatrixRotationZ(&matBuf, physics.m_rzv);
		matWorld = matBuf*matWorld;
	}
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

bool GraphicsManager::AddGraphicsComponent(GraphicsComponent * graphicscomponent)
{
	m_Content.push_back(graphicscomponent);
	return true;
}

bool GraphicsManager::RemoveGraphicsComponent(GraphicsComponent * graphicscomponent)
{
	std::vector<GraphicsComponent*>::iterator result = m_Content.end();
	for (std::vector<GraphicsComponent*>::iterator i = m_Content.begin();i != m_Content.end();i += 1)
	{
		if (*i == graphicscomponent)
		{
			result = i;
			break;
		}
	}
	if (result != m_Content.end())
	{
		m_Content.erase(result);
		return true;
	}
	else
		return false;
}

bool GraphicsManager::RunManager(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	for (size_t i = 0;i < m_Content.size();i++)
	{
		m_Content[i]->ObjectPrint(g_pd3dDevice);
	}
	return true;
}
