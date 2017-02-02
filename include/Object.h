#pragma once
#include "stdafx.h"
#include "Space.h"
#include "LightRender.h"
#include "Texture.h"
#include "Physics.h"
#include "Graphics.h"

class object    //DX3D物体对象
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[]);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,const std::string& filename, LPCTSTR photoname);								//从文件中读取数据，进行初始化
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename,LPCTSTR photoname,const std::string& TextureFile);	//从文件中读取数据，进行初始化
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, const std::string& lightfilename, LPCTSTR photoname);					//从文件中读取数据，包括光源，进行初始化
	~object();																//释放顶点缓存和索引缓存
	object();																//初始化
	object(int &i);															//初始化，顺带初始化m_Light
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//写入顶点缓存内容
	void WriteInIndexBuffer(WORD Indices[]);							//写入索引缓存内容
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//图形的绘制
	//---------------------------------------------------------------------------------------------------------------
	//对X-File的支持
	void InitFromXFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR filename);					//从X-File中读取模型:不要用，不稳定。未完成！
	//---------------------------------------------------------------------------------------------------------------
	Light m_Light;																			//光源
	void InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,const std::string& filename);		//从文件中初始化点光源
	void InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);//从文件中初始化方向光源
	void InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);		//从文件中初始化聚光灯
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);										//绘制光源，即开启光源
	void LightBeginPrint();																	//开启光源
	void LightEndPrint();																	//关闭光源
	//---------------------------------------------------------------------------------------------------------------
	void GetTime();														//获取或更新时间间隔
	//---------------------------------------------------------------------------------------------------------------
	void SetXYZ(float x, float y, float z);								//临时的设置物体质心坐标的函数
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysicsFromFile(const std::string& filename);						//从文件中初始化物理信息
	void SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);						//通过物理量来设置物体的世界变换矩阵，只包含平移和旋转。
	void GetG();														//获得物体的重力，并将其加到总合力中
	void RunMovingEngine();											//运行关于移动的物理引擎
	void RunRotationEngine();											//运行关于旋转的物理引擎
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//顶点缓存
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//索引缓存
	int m_VertexSize;							//顶点数
	int m_IndexSize;							//索引数
	VOID* mpVertices;							//指向顶点缓存内部数据数组的指针
	WORD* mpIndices;							//指向索引缓存内部数据数组的指针
	int m_PrimitiveCount;						//图元的数量
	//----------------------------------------------------------------------------------------------------------------
	//X-File
	bool m_IfXFile;								//是否使用X-File
	LPD3DXBUFFER m_pAdjBuffer;					//用于保存加载网格的邻接信息，也就是包含每个多边形周围的多边形信息的缓冲区的内存地址
	LPD3DXBUFFER m_pMtrlBuffer;					//用于保存网格的所有子集的材质和纹理，指向用于存储模型材质和纹理文件名的缓冲区的地址，而材质的数目存在之后第七个参数pNumMaterials中了
	DWORD m_NumMaterials;						//网格里材质的数量
	LPD3DXMESH m_pMesh;							//网格
	D3DMATERIAL9* m_pMaterials;					//网格的材质
	LPDIRECT3DTEXTURE9* m_pTextures;			//网格的纹理
	//----------------------------------------------------------------------------------------------------------------
	bool m_IfLight;								//是否有光源
	float m_lx, m_ly, m_lz;						//光源在物体中相对于物体质心的相对坐标
	//----------------------------------------------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;				//纹理
	//----------------------------------------------------------------------------------------------------------------
	float m_TimeNow;							//现在的时间
	float m_TimeChange;						//时间差，即时间变化量
	//----------------------------------------------------------------------------------------------------------------
	bool m_IfPhysics;							//是否开启物理引擎
	D3DVECTOR m_Position;						//物体质心的坐标
	float m_m;									//物体的质量
	D3DVECTOR m_F;								//物体所受的总的合力
	D3DVECTOR m_a;								//物体的总的加速度
	D3DVECTOR m_v;								//物体的总的速度
	D3DVECTOR m_I;								//物体的转动惯量
	float m_rxv, m_ryv, m_rzv;					//物体的XYZ三轴上的旋转的角度
	float m_rxa, m_rya, m_rza;					//物体的XYZ三轴上的旋转的角度的每秒的变化量
};
class Object									//物体对象
{
public:
	Object(bool ifphysics=true);
	Object(int &i,bool ifphysics = true);
	GraphicsComponent* GetGraphicsComponent();	//获取图形组件的指针
	PhysicsComponent* GetPhysicsComponent();	//获取物理组件的指针
	bool IfPhysics();							//是否有物理
	//--------------------------------------------------------------
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname, const std::string& materialname = "NULL");								//从文件中读取数据，进行初始化
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname, const std::string& TextureFile, const std::string& materialname = "NULL");	//从文件中读取数据，进行初始化
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, const std::string& lightfilename, LPCTSTR photoname, const std::string& materialname = "NULL");					//从文件中读取数据，包括光源，进行初始化
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//图形的绘制
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);										//绘制光源，即开启光源
	void LightBeginPrint();																	//开启光源
	void LightEndPrint();																	//关闭光源
	void ChangeTexture(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname);										//更换纹理
	void ChangeTextureEx(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, const std::string& TextureFile);	//更换纹理EX
	//--------------------------------------------------------------
	void InitPhysicsFromFile(const std::string& filename);						//从文件中初始化物理信息
	void GetG();														//获得物体的重力，并将其加到总合力中
	void RunMovingEngine();											//运行关于移动的物理引擎
	void RunRotationEngine();											//运行关于旋转的物理引擎
private:
	GraphicsComponent m_Graphics;				//图形
	bool m_IfPhysics;							//是否有物理
	PhysicsComponent m_Physics;					//物理
};
class ObjectManager								//物体对象管理器
{
public:
	bool AddObject(Object* obj);				//添加对象
	bool RemoveObject(Object* obj);			//移除对象
	virtual bool RunManager(LPDIRECT3DDEVICE9 g_pd3dDevice);	//运行管理器
private:
	GraphicsManager m_GraphicsManager;			//图形
	PhysicsManager m_PhysicsManager;			//物理
	std::vector<Object*> m_Content;				//Object内容
};