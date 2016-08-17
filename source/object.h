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


class object    //DX3D物体对象
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[]);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）
	void InitFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,std::string filename, LPCTSTR photoname);								//从文件中读取数据，进行初始化
	void InitFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename,LPCTSTR photoname,std::string TextureFile);	//从文件中读取数据，进行初始化
	void InitWithLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename, std::string lightfilename, LPCTSTR photoname);					//从文件中读取数据，包括光源，进行初始化
	~object();																//释放顶点缓存和索引缓存
	object();																//初始化
	object(int &i);															//初始化，顺带初始化m_Light
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//写入顶点缓存内容
	void WriteInIndexBuffer(WORD Indices[]);							//写入索引缓存内容
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//图形的绘制
	//---------------------------------------------------------------------------------------------------------------
	Light m_Light;
	void InitPointLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice,std::string filename);
	void InitDirectionalLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename);
	void InitSpotLightFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filename);
	void LightPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);
	//---------------------------------------------------------------------------------------------------------------
	void GetTime();
	//---------------------------------------------------------------------------------------------------------------
	void SetXYZ(float x, float y, float z);								//临时的设置物体质心坐标的函数
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysicsFromFile(std::string filename);													//初始化物理信息
	void SetMatrix(LPDIRECT3DDEVICE9 g_pd3dDevice);													//通过物理量来设置物体的世界变换矩阵，只包含平移和旋转。
	void GetG();														//获得物体的重力，并将其加到总合力中
	void RunMovingGraphics();											//运行关于移动的物理引擎
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//顶点缓存
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//索引缓存
	int m_VertexSize;							//顶点数
	int m_IndexSize;							//索引数
	VOID* mpVertices;							//指向顶点缓存内部数据数组的指针
	WORD* mpIndices;							//指向索引缓存内部数据数组的指针
	int m_PrimitiveCount;						//图元的数量
	//----------------------------------------------------------------------------------------------------------------
	float m_lx, m_ly, m_lz;						//光源在物体中相对于物体质心的相对坐标
	//----------------------------------------------------------------------------------------------------------------
	LPDIRECT3DTEXTURE9 m_pTexture;				//纹理
	//----------------------------------------------------------------------------------------------------------------
	time_t m_TimeNow;							//现在的时间
	time_t m_TimeChange;						//时间差，即时间变化量
	//----------------------------------------------------------------------------------------------------------------
	D3DVECTOR m_Position;						//物体质心的坐标
	float m_m;									//物体的质量
	D3DVECTOR m_F;								//物体所受的总的合力
	D3DVECTOR m_a;								//物体的总的加速度
	D3DVECTOR m_v;								//物体的总的速度
	float m_rxv, m_ryv, m_rzv;					//物体的XYZ三轴上的旋转的角度
	float m_rxa, m_rya, m_rza;					//物体的XYZ三轴上的旋转的角度的每秒的变化量
};