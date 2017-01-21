#pragma once
#include"stdafx.h"
#include"Space.h"
#include"LightRender.h"
#include"Texture.h"
#include"Physics.h"
#include"ClassDef.h"
class GraphicsComponent													//图形组件
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice, int VertexSize, int IndexSize, CUSTOMVERTEX Vertices[], WORD Indices[]);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname,const std::string& materialname="NULL");								//从文件中读取数据，进行初始化
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, LPCTSTR photoname, const std::string& TextureFile, const std::string& materialname = "NULL");	//从文件中读取数据，进行初始化
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename, const std::string& lightfilename, LPCTSTR photoname, const std::string& materialname = "NULL");					//从文件中读取数据，包括光源，进行初始化
	~GraphicsComponent();																//释放顶点缓存和索引缓存
	GraphicsComponent();																//初始化
	GraphicsComponent(int &i);															//初始化，顺带初始化m_Light
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//写入顶点缓存内容
	void WriteInIndexBuffer(WORD Indices[]);							//写入索引缓存内容
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//图形的绘制
	//---------------------------------------------------------------------------------------------------------------
	//对X-File的支持
	void InitFromXFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR filename);					//从X-File中读取模型:不要用，不稳定。未完成！
	//---------------------------------------------------------------------------------------------------------------
	Light m_Light;																			//光源
	void InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);		//从文件中初始化点光源
	void InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);//从文件中初始化方向光源
	void InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const std::string& filename);		//从文件中初始化聚光灯
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice,PhysicsComponent& physics);										//绘制光源，即开启光源
	void LightBeginPrint();																	//开启光源
	void LightEndPrint();																	//关闭光源
	//----------------------------------------------------------------------------------------------------------------
	D3DMATERIAL9 m_Material;																//材质
	//----------------------------------------------------------------------------------------------------------------
	void ChangeTexture(LPDIRECT3DDEVICE9 g_pd3dDevice,LPCTSTR photoname);										//更换纹理
	void ChangeTexture(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, const std::string& TextureFile);		//更换纹理EX
	//----------------------------------------------------------------------------------------------------------------
	void SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice,PhysicsComponent& physics);						//通过物理量来设置物体的世界变换矩阵，只包含平移和旋转。
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
};
class GraphicsManager							//图形管理器
{
public:
	bool AddGraphicsComponent(GraphicsComponent* graphicscomponent);	//加入图形组件
	bool RemoveGraphicsComponent(GraphicsComponent* graphicscomponent);	//删除图形组件
	virtual bool RunManager(LPDIRECT3DDEVICE9 g_pd3dDevice);			//运行管理器
private:
	std::vector<GraphicsComponent*> m_Content;		//图形内容
};