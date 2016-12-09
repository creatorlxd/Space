#include "stdafx.h"
#include "space.h"


//-----------------------------------��Direct3D_Init( )������--------------------------------------
//	������Direct3D��ʼ������������Direct3D�ĳ�ʼ��
//------------------------------------------------------------------------------------------------
HRESULT Direct3D_Init(HWND hwnd, LPDIRECT3DDEVICE9       g_pd3dDevice,int WINDOW_HEIGHT,int WINDOW_WIDTH)
{
	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮һ�����ӿڡ�������Direct3D�ӿڶ���, �Ա��ø�Direct3D���󴴽�Direct3D�豸����
	//--------------------------------------------------------------------------------------
	LPDIRECT3D9  pD3D = NULL; //Direct3D�ӿڶ���Ĵ���
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION))) //��ʼ��Direct3D�ӿڶ��󣬲�����DirectX�汾Э��
		return E_FAIL;

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮��,ȡ��Ϣ������ȡӲ���豸��Ϣ
	//--------------------------------------------------------------------------------------
	D3DCAPS9 caps; int vp = 0;
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //֧��Ӳ���������㣬���ǾͲ���Ӳ���������㣬���׵�
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //��֧��Ӳ���������㣬����ֻ�ò��������������

//--------------------------------------------------------------------------------------
// ��Direct3D��ʼ���Ĳ���֮���������ݡ������D3DPRESENT_PARAMETERS�ṹ��
//--------------------------------------------------------------------------------------
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮�ģ����豸��������Direct3D�豸�ӿ�
	//--------------------------------------------------------------------------------------
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, vp, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;

	SAFE_RELEASE(pD3D) //LPDIRECT3D9�ӿڶ����ʹ����ɣ����ǽ����ͷŵ�


		
	return S_OK;
}
void InitMaterialFromFile(D3DMATERIAL9 &Material, std::string filename)
{
	std::fstream file;
	file.open(filename, std::ios::in);
	float r, g, b, a;				//������0.0~~1.0֮��
	file >> r >> g >> b >> a;
	Material.Ambient = D3DXCOLOR(r, g, b, a);		//���价�������ɫֵ
	file >> r >> g >> b >> a;
	Material.Diffuse = D3DXCOLOR(r, g, b, a);		//���������ɫֵ
	file >> r >> g >> b >> a;
	Material.Specular = D3DXCOLOR(r, g, b, a);		//���淴�����ɫֵ
	file >> r >> g >> b >> a;
	Material.Emissive = D3DXCOLOR(r, g, b, a);		//�Է������ɫֵ

	float Power;
	file >> Power;
	Material.Power = Power;

	file.close();
}

void OpenAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

void CloseAlpha(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void OpenDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, true);
}

void SetDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void CloseDepthBuffer(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
}
