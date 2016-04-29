#include<d3d9.h>
#include "tools.h"


void object::init(LPDIRECT3DDEVICE9 g_pd3dDevice, int VertexSize, int IndexSize, CUSTOMVERTEX Vertices[], WORD Indices[])
{
	
	g_VertexSize = VertexSize;
	g_IndexSize = IndexSize;
	g_pd3dDevice->CreateVertexBuffer(g_VertexSize*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVertexbuffer, NULL);
	g_pd3dDevice->CreateIndexBuffer(g_IndexSize*sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIndexBuffer, NULL);
	WriteInVertexBuffer(Vertices);
	WriteInIndexBuffer(Indices);
}

object::~object()
{
	SAFE_RELEASE(g_pVertexbuffer);
	SAFE_RELEASE(g_pIndexBuffer);
}

object::object()
{
	g_VertexSize = 0;
	g_IndexSize = 0;
	g_pVertexbuffer = NULL;
	g_pIndexBuffer = NULL;
	pVertices = NULL;
	pIndices = NULL;
}

void object::WriteInVertexBuffer(CUSTOMVERTEX Vertices[])
{
	g_pVertexbuffer->Lock(0, sizeof(Vertices), (void**)&pVertices, 0);
	memcpy(pVertices, Vertices, sizeof(Vertices));
	g_pIndexBuffer->Unlock();
}

void object::WriteInIndexBuffer(WORD Indices[])
{
	g_pIndexBuffer->Lock(0, sizeof(Indices), (void**)&pIndices, 0);
	memcpy(pIndices, Indices, sizeof(Indices));
	g_pIndexBuffer->Unlock();
}
