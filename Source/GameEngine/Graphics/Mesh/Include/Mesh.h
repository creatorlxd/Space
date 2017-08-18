#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"
#include "Window.h"
#include "Game/Game/Include/SafeGet.h"
namespace SpaceGameEngine
{
	class MeshComponent :public Component
	{
	public:
		static const int ModelFileMode = 1;				//Model�ļ�ģʽ

		static ComponentManager::NewComponent<MeshComponent> NewComponent;		//�������
		MeshComponent();
		void Release();
		~MeshComponent();

		void InitFromMemory(int VertexSize, int IndexSize, DefaultVertex* pVertices, WORD* pIndices);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�

		void InitFromFile(const std::string& filename, int mode = 1);			//���ļ���ȡMesh
		void Run(float DeltaTime);												//��Ⱦ����
	protected:
		void InitVertexBuffer();
		void InitIndexBuffer();

		std::vector<DefaultVertex> m_Vertices;
		std::vector<unsigned int> m_Indices;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
	};
}