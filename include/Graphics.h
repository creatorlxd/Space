#pragma once
#include"stdafx.h"
#include"Space.h"
#include"LightRender.h"
#include"Texture.h"
#include"Physics.h"
#include"ClassDef.h"
class GraphicsComponent													//ͼ�����
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice, int VertexSize, int IndexSize, CUSTOMVERTEX Vertices[], WORD Indices[]);	//�������㻺�����������,VertexSizeΪ������,IndexSizeΪ�������������Ķ��٣�
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname,const std::string& materialname="NULL");								//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname, const std::string& TextureFile, const std::string& materialname = "NULL");	//���ļ��ж�ȡ���ݣ����г�ʼ��
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, const std::string& lightfilename, LPCTSTR photoname, const std::string& materialname = "NULL");					//���ļ��ж�ȡ���ݣ�������Դ�����г�ʼ��
	~GraphicsComponent();																//�ͷŶ��㻺�����������
	GraphicsComponent();																//��ʼ��
	GraphicsComponent(int &i);															//��ʼ����˳����ʼ��m_Light
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//д�붥�㻺������
	void WriteInIndexBuffer(WORD Indices[]);							//д��������������
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//ͼ�εĻ���
	//---------------------------------------------------------------------------------------------------------------
	//��X-File��֧��
	void InitFromXFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR filename);					//��X-File�ж�ȡģ��:��Ҫ�ã����ȶ���δ��ɣ�
	//---------------------------------------------------------------------------------------------------------------
	Light m_Light;																			//��Դ
	void InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);		//���ļ��г�ʼ�����Դ
	void InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);//���ļ��г�ʼ�������Դ
	void InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);		//���ļ��г�ʼ���۹��
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice,PhysicsComponent& physics);										//���ƹ�Դ����������Դ
	void LightBeginPrint();																	//������Դ
	void LightEndPrint();																	//�رչ�Դ
	//----------------------------------------------------------------------------------------------------------------
	D3DMATERIAL9 m_Material;																//����
	//----------------------------------------------------------------------------------------------------------------
	void ChangeTexture(LPDIRECT3DDEVICE9 g_pd3dDevice,LPCTSTR photoname);										//��������
	void ChangeTexture(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, const std::string& TextureFile);		//��������EX
	//----------------------------------------------------------------------------------------------------------------
	void SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice,PhysicsComponent& physics);						//ͨ�����������������������任����ֻ����ƽ�ƺ���ת��
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
};
class GraphicsManager							//ͼ�ι�����
{
public:
	bool AddGraphicsComponent(GraphicsComponent* graphicscomponent);	//����ͼ�����
	bool RemoveGraphicsComponent(GraphicsComponent* graphicscomponent);	//ɾ��ͼ�����
	virtual bool RunManager(LPDIRECT3DDEVICE9 g_pd3dDevice);			//���й�����
private:
	std::vector<GraphicsComponent*> m_Content;		//ͼ������
};