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
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[]);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�
	~object();																//�ͷŶ��㻺�����������
	object();																//��ʼ��
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//д�붥�㻺������
	void WriteInIndexBuffer(WORD Indices[]);							//д��������������

private:
	LPDIRECT3DVERTEXBUFFER9 g_pVertexbuffer;	//���㻺��
	LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		//��������
	int g_VertexSize;							//������
	int g_IndexSize;							//������
	VOID* pVertices;							//ָ�򶥵㻺���ڲ����������ָ�룬��ֵ��Ϊ0����ֻ����ʱ�ġ�
	WORD* pIndices;								//ָ�����������ڲ����������ָ�룬��ֵ��Ϊ0����ֻ����ʱ�ġ�
};