#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"
#include "Window.h"
namespace SpaceGameEngine
{
	class MeshComponent :public Component
	{
	public:
		static const int ModelFileMode = 1;				//Model�ļ�ģʽ
		static const int XMeshFileMode = 2;				//XMesh�ļ�ģʽ

		static ComponentManager::NewComponent<MeshComponent> NewComponent;		//�������
		MeshComponent();
		void Release();
		~MeshComponent();

		void WriteInVertexBuffer(DefaultVertex* pVertices);					//д�붥�㻺������
		void WriteInIndexBuffer(WORD* pIndices);							//д��������������
		void Init(int VertexSize, int IndexSize, DefaultVertex* pVertices, WORD* pIndices);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�

		void InitFromFile(const std::string& filename, int mode = 0);			//���ļ���ȡMesh
		void Run(float DeltaTime);												//��Ⱦ����
	protected:
		int m_Mode;

		ID3D11DeviceContext* m_pD3DDeviceContext;
	};
}