#pragma once
//
//
//
//
//
#include<d3d9.h>
#include"space.h"
#include<string>
#include<fstream>
#include"LightRender.h"
#include"Texture.h"


class object    //DX3D�������
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[]);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,std::string filename, LPCTSTR photoname);								//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename,LPCTSTR photoname,std::string TextureFile);	//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename, std::string lightfilename, LPCTSTR photoname);					//���ļ��ж�ȡ���ݣ�������Դ�����г�ʼ��
	~object();																//�ͷŶ��㻺�����������
	object();																//��ʼ��
	object(int &i);															//��ʼ����˳����ʼ��m_Light
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//д�붥�㻺������
	void WriteInIndexBuffer(WORD Indices[]);							//д��������������
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//ͼ�εĻ���
	//---------------------------------------------------------------------------------------------------------------
	Light m_Light;
	void InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,std::string filename);
	void InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename);
	void InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename);
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);
	//---------------------------------------------------------------------------------------------------------------
	void GetTime();
	//---------------------------------------------------------------------------------------------------------------
	void SetXYZ(float x, float y, float z);								//��ʱ������������������ĺ���
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysicsFromFile(std::string filename);													//��ʼ��������Ϣ
	void SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);													//ͨ�����������������������任����ֻ����ƽ�ƺ���ת��
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
	float m_lx, m_ly, m_lz;						//��Դ��������������������ĵ��������
	//----------------------------------------------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;				//����
	//----------------------------------------------------------------------------------------------------------------
	time_t m_TimeNow;							//���ڵ�ʱ��
	time_t m_TimeChange;						//ʱ����ʱ��仯��
	//----------------------------------------------------------------------------------------------------------------
	D3DVECTOR m_Position;						//�������ĵ�����
	float m_m;									//���������
	D3DVECTOR m_F;								//�������ܵ��ܵĺ���
	D3DVECTOR m_a;								//������ܵļ��ٶ�
	D3DVECTOR m_v;								//������ܵ��ٶ�
	float m_rxv, m_ryv, m_rzv;					//�����XYZ�����ϵ���ת�ĽǶ�
	float m_rxa, m_rya, m_rza;					//�����XYZ�����ϵ���ת�ĽǶȵ�ÿ��ı仯��
};