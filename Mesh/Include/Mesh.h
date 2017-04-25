#pragma once 
#include "stdafx.h"
#include "../../Component/Include/ComponentManager.h"
#include "Window.h"

class MeshComponent :public Component 
{
public:
	static ComponentManager::NewComponent<MeshComponent> NewComponent;		//�������
	MeshComponent();
	~MeshComponent();
protected:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//���㻺��
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//��������
	int m_VertexSize;							//������
	int m_IndexSize;							//������
	VOID* mpVertices;							//ָ�򶥵㻺���ڲ����������ָ��
	WORD* mpIndices;							//ָ�����������ڲ����������ָ��
	int m_PrimitiveCount;						//ͼԪ������
	//----------------------------------------------------------------------------------------------------------------
	//X-File
	LPD3DXBUFFER m_pAdjBuffer;					//���ڱ������������ڽ���Ϣ��Ҳ���ǰ���ÿ���������Χ�Ķ������Ϣ�Ļ��������ڴ��ַ
	LPD3DXBUFFER m_pMtrlBuffer;					//���ڱ�������������Ӽ��Ĳ��ʺ�����ָ�����ڴ洢ģ�Ͳ��ʺ������ļ����Ļ������ĵ�ַ�������ʵ���Ŀ����֮����߸�����pNumMaterials����
	DWORD m_NumMaterials;						//��������ʵ�����
	LPD3DXMESH m_pMesh;							//����
	D3DMATERIAL9* m_pMaterials;					//����Ĳ���
	LPDIRECT3DTEXTURE9* m_pTextures;			//���������
};