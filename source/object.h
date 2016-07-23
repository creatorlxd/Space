#pragma once
//
//
//
//
//
#include<d3d9.h>
#include"space.h"





class object    //DX3D物体对象
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[]);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）
	~object();																//释放顶点缓存和索引缓存
	object();																//初始化
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//写入顶点缓存内容
	void WriteInIndexBuffer(WORD Indices[]);							//写入索引缓存内容
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//图形的绘制
	//---------------------------------------------------------------------------------------------------------------
	void GetTime();
	//---------------------------------------------------------------------------------------------------------------
	void InitPhysics();													//初始化物理信息
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
	time_t m_TimeNow;							//现在的时间
	time_t m_TimeChange;						//时间差，即时间变化量
	//----------------------------------------------------------------------------------------------------------------
	D3DVECTOR m_Position;						//物体质心的坐标
	float m_m;									//物体的质量
	D3DVECTOR m_F;								//物体所受的总的合力
	D3DVECTOR m_a;								//物体的总的加速度
	D3DVECTOR m_v;								//物体的总的速度
};