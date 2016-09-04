#include"Texture.h"

void SetTextureFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname,LPDIRECT3DTEXTURE9 & g_pTexture)
{
	D3DXCreateTextureFromFile(g_pd3dDevice, photoname, &g_pTexture);
}

void SetTextureFromFileEx(LPDIRECT3DDEVICE9 g_pd3dDevice, LPCTSTR photoname, std::string filename, LPDIRECT3DTEXTURE9 & g_pTexture)
{
	std::fstream file(filename, std::ios::in);
	int r, g, b;
	file >> r >> g >> b;
	D3DXCreateTextureFromFileEx(g_pd3dDevice, photoname, 0, 0, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,D3DCOLOR_XRGB(r,g,b), NULL, NULL, &g_pTexture);
	file.close();
}

void TexturePrintInit(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
}

void TexturePrintInitEx(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}
