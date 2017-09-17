#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/Object.h"
#include "Window.h"
#include "Game/Game/Include/SafeGet.h"
namespace SpaceGameEngine
{
	class MeshComponent :public Component
	{
	public:
		static const int ModelFileMode = 1;				//Model文件模式

		static ComponentManager::NewComponent<MeshComponent> NewComponent;		//创建组件
		MeshComponent();
		void Release();
		~MeshComponent();

		void InitFromMemory(int VertexSize, int IndexSize, DefaultVertex* pVertices, WORD* pIndices);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）

		void InitFromFile(const std::string& filename, int mode = 1);			//从文件读取Mesh
		void Start();
		void Run(float DeltaTime);												//渲染网格
	protected:
		void InitVertexBuffer();
		void InitIndexBuffer();

		Vector<DefaultVertex> m_Vertices;
		Vector<unsigned int> m_Indices;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
	};
}