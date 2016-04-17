#include<d3d9.h>
#include "tools.h"


object::object(LPDIRECT3DDEVICE9 g_pd3dDevice, int VertexSize, int IndexSize)
{
	g_pVertexbuffer = NULL;
	g_pIndexBuffer = NULL;
	g_VertexSize = VertexSize;
	g_IndexSize = IndexSize;
	g_pd3dDevice->CreateVertexBuffer(g_VertexSize*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVertexbuffer, NULL);
	g_pd3dDevice->CreateIndexBuffer(g_IndexSize*sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIndexBuffer, NULL);
}

object::~object()
{
	SAFE_RELEASE(g_pVertexbuffer);
	SAFE_RELEASE(g_pIndexBuffer);
}
