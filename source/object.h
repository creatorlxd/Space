#pragma once
#include<d3d9.h>

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }   //����һ����ȫ�ͷź꣬���ں���COM�ӿ�ָ����ͷ�




//-----------------------------------��FVF�����ʽ��---------------------------------------------

struct CUSTOMVERTEX //����ṹ��
{
	float x, y, z;	//��ά����
	DWORD color;	//������ɫ
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)	//FVF�����ʽ

//----------------------------------------------------------------------------------------------

class object    //DX3D�������
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[],int PrimitiveCount);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�
	~object();																//�ͷŶ��㻺�����������
	object();																//��ʼ��
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//д�붥�㻺������
	void WriteInIndexBuffer(WORD Indices[]);							//д��������������
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//ͼ�εĻ���
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//���㻺��
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//��������
	int m_VertexSize;							//������
	int m_IndexSize;							//������
	VOID* mVertices;							//ָ�򶥵㻺���ڲ����������ָ��
	WORD* mIndices;								//ָ�����������ڲ����������ָ��
	int m_PrimitiveCount;						//ͼԪ������
};