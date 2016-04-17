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
	object(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�
	~object();																//�ͷŶ��㻺�����������
private:
	LPDIRECT3DVERTEXBUFFER9 g_pVertexbuffer;	//���㻺��
	LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		//��������
	int g_VertexSize;							//������
	int g_IndexSize;							//������
};