#pragma once 
#include "stdafx.h"
#include "../../Component/Include/ComponentManager.h"
#include "Window.h"

class MeshComponent :public Component 
{
public:
	const int ModelFileMode = 1;				//Model文件模式
	const int XMeshFileMode = 2;				//XMesh文件模式

	static ComponentManager::NewComponent<MeshComponent> NewComponent;		//创建组件
	MeshComponent();
	void Release();
	~MeshComponent();
protected:
	int m_Mode;

	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//顶点缓存
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//索引缓存
	int m_VertexSize;							//顶点数
	int m_IndexSize;							//索引数
	VOID* m_pVertices;							//指向顶点缓存内部数据数组的指针
	WORD* m_pIndices;							//指向索引缓存内部数据数组的指针
	int m_PrimitiveCount;						//图元的数量
	//----------------------------------------------------------------------------------------------------------------
	//X-File
	LPD3DXBUFFER m_pAdjBuffer;					//用于保存加载网格的邻接信息，也就是包含每个多边形周围的多边形信息的缓冲区的内存地址
	LPD3DXBUFFER m_pMtrlBuffer;					//用于保存网格的所有子集的材质和纹理，指向用于存储模型材质和纹理文件名的缓冲区的地址，而材质的数目存在之后第七个参数pNumMaterials中了
	DWORD m_NumMaterials;						//网格里材质的数量
	LPD3DXMESH m_pMesh;							//网格
	D3DMATERIAL9* m_pMaterials;					//网格的材质
	LPDIRECT3DTEXTURE9* m_pTextures;			//网格的纹理
};