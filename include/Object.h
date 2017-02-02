#pragma once
#include "stdafx.h"
#include "Space.h"
#include "LightRender.h"
#include "Texture.h"
#include "Physics.h"
#include "Graphics.h"

class object    //DX3D�������
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[]);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,const std::string& filename, LPCTSTR photoname);								//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename,LPCTSTR photoname,const std::string& TextureFile);	//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, const std::string& lightfilename, LPCTSTR photoname);					//���ļ��ж�ȡ���ݣ�������Դ�����г�ʼ��
	~object();																//�ͷŶ��㻺�����������
	object();																//��ʼ��
	object(int &i);															//��ʼ����˳����ʼ��m_Light
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//д�붥�㻺������
	void WriteInIndexBuffer(WORD Indices[]);							//д��������������
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//ͼ�εĻ���
	//---------------------------------------------------------------------------------------------------------------
	//��X-File��֧��
	void InitFromXFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR filename);					//��X-File�ж�ȡģ��:��Ҫ�ã����ȶ���δ��ɣ�
	//---------------------------------------------------------------------------------------------------------------
	Light m_Light;																			//��Դ
	void InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,const std::string& filename);		//���ļ��г�ʼ�����Դ
	void InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);//���ļ��г�ʼ�������Դ
	void InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);		//���ļ��г�ʼ���۹��
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);										//���ƹ�Դ����������Դ
	void LightBeginPrint();																	//������Դ
	void LightEndPrint();																	//�رչ�Դ
	//---------------------------------------------------------------------------------------------------------------
	void GetTime();														//��ȡ�����ʱ����
	//---------------------------------------------------------------------------------------------------------------
	void SetXYZ(float x, float y, float z);								//��ʱ������������������ĺ���
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysicsFromFile(const std::string& filename);						//���ļ��г�ʼ��������Ϣ
	void SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);						//ͨ�����������������������任����ֻ����ƽ�ƺ���ת��
	void GetG();														//��������������������ӵ��ܺ�����
	void RunMovingEngine();											//���й����ƶ�����������
	void RunRotationEngine();											//���й�����ת����������
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//���㻺��
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//��������
	int m_VertexSize;							//������
	int m_IndexSize;							//������
	VOID* mpVertices;							//ָ�򶥵㻺���ڲ����������ָ��
	WORD* mpIndices;							//ָ�����������ڲ����������ָ��
	int m_PrimitiveCount;						//ͼԪ������
	//----------------------------------------------------------------------------------------------------------------
	//X-File
	bool m_IfXFile;								//�Ƿ�ʹ��X-File
	LPD3DXBUFFER m_pAdjBuffer;					//���ڱ������������ڽ���Ϣ��Ҳ���ǰ���ÿ���������Χ�Ķ������Ϣ�Ļ��������ڴ��ַ
	LPD3DXBUFFER m_pMtrlBuffer;					//���ڱ�������������Ӽ��Ĳ��ʺ�����ָ�����ڴ洢ģ�Ͳ��ʺ������ļ����Ļ������ĵ�ַ�������ʵ���Ŀ����֮����߸�����pNumMaterials����
	DWORD m_NumMaterials;						//��������ʵ�����
	LPD3DXMESH m_pMesh;							//����
	D3DMATERIAL9* m_pMaterials;					//����Ĳ���
	LPDIRECT3DTEXTURE9* m_pTextures;			//���������
	//----------------------------------------------------------------------------------------------------------------
	bool m_IfLight;								//�Ƿ��й�Դ
	float m_lx, m_ly, m_lz;						//��Դ��������������������ĵ��������
	//----------------------------------------------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;				//����
	//----------------------------------------------------------------------------------------------------------------
	float m_TimeNow;							//���ڵ�ʱ��
	float m_TimeChange;						//ʱ����ʱ��仯��
	//----------------------------------------------------------------------------------------------------------------
	bool m_IfPhysics;							//�Ƿ�����������
	D3DVECTOR m_Position;						//�������ĵ�����
	float m_m;									//���������
	D3DVECTOR m_F;								//�������ܵ��ܵĺ���
	D3DVECTOR m_a;								//������ܵļ��ٶ�
	D3DVECTOR m_v;								//������ܵ��ٶ�
	D3DVECTOR m_I;								//�����ת������
	float m_rxv, m_ryv, m_rzv;					//�����XYZ�����ϵ���ת�ĽǶ�
	float m_rxa, m_rya, m_rza;					//�����XYZ�����ϵ���ת�ĽǶȵ�ÿ��ı仯��
};
class Object									//�������
{
public:
	Object(bool ifphysics=true);
	Object(int &i,bool ifphysics = true);
	GraphicsComponent* GetGraphicsComponent();	//��ȡͼ�������ָ��
	PhysicsComponent* GetPhysicsComponent();	//��ȡ���������ָ��
	bool IfPhysics();							//�Ƿ�������
	//--------------------------------------------------------------
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname, const std::string& materialname = "NULL");								//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname, const std::string& TextureFile, const std::string& materialname = "NULL");	//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, const std::string& lightfilename, LPCTSTR photoname, const std::string& materialname = "NULL");					//���ļ��ж�ȡ���ݣ�������Դ�����г�ʼ��
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//ͼ�εĻ���
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);										//���ƹ�Դ����������Դ
	void LightBeginPrint();																	//������Դ
	void LightEndPrint();																	//�رչ�Դ
	void ChangeTexture(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname);										//��������
	void ChangeTextureEx(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, const std::string& TextureFile);	//��������EX
	//--------------------------------------------------------------
	void InitPhysicsFromFile(const std::string& filename);						//���ļ��г�ʼ��������Ϣ
	void GetG();														//��������������������ӵ��ܺ�����
	void RunMovingEngine();											//���й����ƶ�����������
	void RunRotationEngine();											//���й�����ת����������
private:
	GraphicsComponent m_Graphics;				//ͼ��
	bool m_IfPhysics;							//�Ƿ�������
	PhysicsComponent m_Physics;					//����
};
class ObjectManager								//������������
{
public:
	bool AddObject(Object* obj);				//��Ӷ���
	bool RemoveObject(Object* obj);			//�Ƴ�����
	virtual bool RunManager(LPDIRECT3DDEVICE9 g_pd3dDevice);	//���й�����
private:
	GraphicsManager m_GraphicsManager;			//ͼ��
	PhysicsManager m_PhysicsManager;			//����
	std::vector<Object*> m_Content;				//Object����
};