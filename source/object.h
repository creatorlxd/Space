#pragma once
//
//
//
//
//
#include<d3d9.h>
#include"space.h"





class object    //DX3D�������
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[]);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�
	~object();																//�ͷŶ��㻺�����������
	object();																//��ʼ��
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//д�붥�㻺������
	void WriteInIndexBuffer(WORD Indices[]);							//д��������������
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//ͼ�εĻ���
	//---------------------------------------------------------------------------------------------------------------
	void GetTime();
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysics();													//��ʼ��������Ϣ
	void GetG();														//��������������������ӵ��ܺ�����
	void RunMovingGraphics();											//���й����ƶ�����������
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//���㻺��
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//��������
	int m_VertexSize;							//������
	int m_IndexSize;							//������
	VOID* mpVertices;							//ָ�򶥵㻺���ڲ����������ָ��
	WORD* mpIndices;							//ָ�����������ڲ����������ָ��
	int m_PrimitiveCount;						//ͼԪ������
	//----------------------------------------------------------------------------------------------------------------
	time_t m_TimeNow;							//���ڵ�ʱ��
	time_t m_TimeChange;						//ʱ����ʱ��仯��
	//----------------------------------------------------------------------------------------------------------------
	D3DVECTOR m_Position;						//�������ĵ�����
	float m_m;									//���������
	D3DVECTOR m_F;								//�������ܵ��ܵĺ���
	D3DVECTOR m_a;								//������ܵļ��ٶ�
	D3DVECTOR m_v;								//������ܵ��ٶ�
};