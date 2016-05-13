#pragma once
#include<d3d9.h>

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }   //定义一个安全释放宏，便于后面COM接口指针的释放




//-----------------------------------【FVF顶点格式】---------------------------------------------

struct CUSTOMVERTEX //顶点结构体
{
	float x, y, z;	//三维坐标
	DWORD color;	//顶点颜色
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)	//FVF灵活顶点格式

//----------------------------------------------------------------------------------------------

class object    //DX3D物体对象
{
public:
	void init(LPDIRECT3DDEVICE9 g_pd3dDevice,int VertexSize,int IndexSize,CUSTOMVERTEX Vertices[],WORD Indices[],int PrimitiveCount);	//创建顶点缓存和索引缓存,VertexSize为顶点数,IndexSize为索引数（索引的多少）
	~object();																//释放顶点缓存和索引缓存
	object();																//初始化
	void WriteInVertexBuffer(CUSTOMVERTEX Vertices[]);					//写入顶点缓存内容
	void WriteInIndexBuffer(WORD Indices[]);							//写入索引缓存内容
	void ObjectPrint(LPDIRECT3DDEVICE9 g_pd3dDevice);					//图形的绘制
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;	//顶点缓存
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;		//索引缓存
	int m_VertexSize;							//顶点数
	int m_IndexSize;							//索引数
	VOID* mVertices;							//指向顶点缓存内部数据数组的指针
	WORD* mIndices;								//指向索引缓存内部数据数组的指针
	int m_PrimitiveCount;						//图元的数量
};