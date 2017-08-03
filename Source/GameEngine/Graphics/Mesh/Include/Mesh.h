#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"
#include "Window.h"
namespace SpaceGameEngine
{
	class MeshComponent :public Component
	{
	public:
		static const int ModelFileMode = 1;				//Model文件模式
		static const int XMeshFileMode = 2;				//XMesh文件模式

		static ComponentManager::NewComponent<MeshComponent> NewComponent;		//创建组件
		MeshComponent();
		void Release();
		~MeshComponent();

		void WriteInVertexBuffer(DefaultVertex* pVertices);					//写入顶点缓存内容
		void WriteInIndexBuffer(WORD* pIndices);							//写入索引缓存内容
		void Init(int VertexSize, int IndexSize, DefaultVertex* pVertices, WORD* pIndices);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）

		void InitFromFile(const std::string& filename, int mode = 0);			//从文件读取Mesh
		void Run(float DeltaTime);												//渲染网格
	protected:
		int m_Mode;

		ID3D11DeviceContext* m_pD3DDeviceContext;
	};
}