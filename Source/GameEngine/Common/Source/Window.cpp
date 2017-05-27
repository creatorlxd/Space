#include"stdafx.h"
#include"Window.h"

Window* Window::sm_pThis = nullptr;

void DefaultWindowLoop()
{
	//do nothing
}

void DefaultInitAction()
{
	//do nothing
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(SpaceEngineWindow==nullptr)
		return DefWindowProc(hwnd, message, wParam, lParam);		//����ȱʡ�Ĵ��ڹ���
	switch (message)						//switch��俪ʼ
	{
	case WM_PAINT:						// ���ǿͻ����ػ���Ϣ
		SpaceEngineWindow->m_pWindowLoop();                 //����Direct3D��Ⱦ����
		ValidateRect(hwnd, NULL);		// ���¿ͻ�������ʾ
		break;									//������switch���

	case WM_KEYDOWN:					// ���Ǽ��̰�����Ϣ
		if (wParam == VK_ESCAPE)    // ��������µļ���ESC
			DestroyWindow(hwnd);		// ���ٴ���, ������һ��WM_DESTROY��Ϣ
		break;									//������switch���

	case WM_DESTROY:					//���Ǵ���������Ϣ
		SpaceEngineWindow->Release();
			PostQuitMessage(0);			//��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;									//������switch���

	default:										//������case�����������ϣ���ִ�и�default���
		return DefWindowProc(hwnd, message, wParam, lParam);		//����ȱʡ�Ĵ��ڹ���
	}

	return 0;
}

Window::Window()
{
	m_Hwnd = NULL;
	m_pd3dDevice = NULL;
	m_pWindowLoop = DefaultWindowLoop;
	m_pInitAction = DefaultInitAction;
	SetAsMainWindow();
}

Window::~Window()
{
	if (SpaceEngineWindow == this)
		sm_pThis = nullptr;
	if (m_pd3dDevice)
		SafeRelease(m_pd3dDevice);
	m_pd3dDevice = NULL;
}

void Window::SetWindow(LPCTSTR title, DWORD width, DWORD height)
{
	m_WindowTitle = title;
	m_WindowWidth = width;
	m_WindowHeight = height;
}

HRESULT Window::InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(), void(*InitAction)())
{
	m_pWindowLoop = WindowLoop;
	m_pInitAction = InitAction;
	//��1�����ڴ����Ĳ���֮һ����ʼ���һ�������Ĵ�����
	WNDCLASSEX wndClass = { 0 };							//��WINDCLASSEX������һ��������
	wndClass.cbSize = sizeof(WNDCLASSEX);			//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;					//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra = 0;								//������ĸ����ڴ棬ȡ0�Ϳ�����
	wndClass.cbWndExtra = 0;							//���ڵĸ����ڴ棬��Ȼȡ0������
	wndClass.hInstance = hInstance;						//ָ���������ڹ��̵ĳ����ʵ�������
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //���ؼ����Զ���icoͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //ָ��������Ĺ������
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  //ΪhbrBackground��Աָ��һ����ɫ��ˢ���	
	wndClass.lpszMenuName = NULL;						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndClass.lpszClassName = L"SpaceEngineWindow";		//��һ���Կ���ֹ���ַ�����ָ������������֡�

														//��2�����ڴ����Ĳ���֮����ע�ᴰ����
	if (!RegisterClassEx(&wndClass))				//����괰�ں���Ҫ�Դ��������ע�ᣬ�������ܴ��������͵Ĵ���
		return -1;

	//��3�����ڴ����Ĳ���֮������ʽ��������
	m_Hwnd = CreateWindow(L"SpaceEngineWindow", m_WindowTitle,				//ϲ���ּ��Ĵ������ں���CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_WindowWidth,
		m_WindowHeight, NULL, NULL, hInstance, NULL);

	//Direct3D��Դ�ĳ�ʼ�����ɹ�����ʧ�ܶ���messagebox������ʾ
	if (E_FAIL == Direct3DInit(m_Hwnd))
	{
		MessageBox(m_Hwnd, L"Direct3D��ʼ��ʧ��~��", L"��Ϣ����", 0); //ʹ��MessageBox����������һ����Ϣ���� 
	}
	EnvironmentInit(m_Hwnd);

	//��4�����ڴ����Ĳ���֮�ģ����ڵ��ƶ�����ʾ�����
	MoveWindow(m_Hwnd, 250, 80, m_WindowWidth, m_WindowHeight, true);		//����������ʾʱ��λ�ã�ʹ�������Ͻ�λ�ڣ�250,80����
	ShowWindow(m_Hwnd, nShowCmd);    //����ShowWindow��������ʾ����
	UpdateWindow(m_Hwnd);						//�Դ��ڽ��и��£��������������·���Ҫװ��һ��



											//��5����Ϣѭ������
	MSG msg = { 0 };  //��ʼ��msg
	while (msg.message != WM_QUIT)			//ʹ��whileѭ��
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			TranslateMessage(&msg);		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);		//�ú����ַ�һ����Ϣ�����ڳ���
		}
		else
		{
			m_pWindowLoop();   //������Ⱦ
		}
	}
	//��6���������ע��
	UnregisterClass(L"SpaceEngineWindow", wndClass.hInstance);  //����׼��������ע��������
	return 0;
}

void Window::Release()
{
	if (SpaceEngineWindow == this)
		sm_pThis = nullptr;
	if (m_pd3dDevice != NULL)
		SafeRelease(m_pd3dDevice);
	m_pd3dDevice = NULL;
}

HRESULT Window::Direct3DInit(HWND hwnd)
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
	d3dpp.BackBufferWidth = m_WindowWidth;
	d3dpp.BackBufferHeight = m_WindowHeight;
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
		hwnd, vp, &d3dpp, &m_pd3dDevice)))
		return E_FAIL;

	SafeRelease(pD3D); //LPDIRECT3D9�ӿڶ����ʹ����ɣ����ǽ����ͷŵ�
	return S_OK;
}

HRESULT Window::EnvironmentInit(HWND hwnd)
{
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);   //������������
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);
	TexturePrintInitEx(m_pd3dDevice);
	m_pd3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	OpenDepthBuffer(m_pd3dDevice);
	SetDepthBuffer(m_pd3dDevice);
	SetViewPort(m_pd3dDevice, m_WindowWidth, m_WindowHeight);
	m_pInitAction();
	return S_OK;
}

void Window::BeginPrint()
{
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);//һ����������

	m_pd3dDevice->BeginScene();			//��ʼ����
}

void Window::EndPrint()
{
	m_pd3dDevice->EndScene();	//��������

	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);	//��ת��ʾ
}

HWND Window::GetHwnd()
{
	return m_Hwnd;
}

LPDIRECT3DDEVICE9 Window::GetD3DDevice()
{
	return m_pd3dDevice;
}

DWORD Window::GetWindowWidth()
{
	return m_WindowWidth;
}

DWORD Window::GetWindowHeight()
{
	return m_WindowHeight;
}

Window * Window::GetMainWindow()
{
	return sm_pThis;
}

void Window::SetAsMainWindow()
{
	sm_pThis = this;
}
