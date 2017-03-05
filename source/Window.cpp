#include"stdafx.h"
#include"Window.h"

void DefaultWindowLoop(HWND hwnd)
{
	//do nothing
}

void DefaultInitAction(Window* window)
{
	//do nothing
}


Window* SpaceEngineWindow=NULL;								//唯一指针



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(SpaceEngineWindow==NULL)
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程
	switch (message)						//switch语句开始
	{
	case WM_PAINT:						// 若是客户区重绘消息
		SpaceEngineWindow->m_pWindowLoop(hwnd);                 //调用Direct3D渲染函数
		ValidateRect(hwnd, NULL);		// 更新客户区的显示
		break;									//跳出该switch语句

	case WM_KEYDOWN:					// 若是键盘按下消息
		if (wParam == VK_ESCAPE)    // 如果被按下的键是ESC
			DestroyWindow(hwnd);		// 销毁窗口, 并发送一条WM_DESTROY消息
		break;									//跳出该switch语句

	case WM_DESTROY:					//若是窗口销毁消息
		SpaceEngineWindow->Release();
			PostQuitMessage(0);			//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;									//跳出该switch语句

	default:										//若上述case条件都不符合，则执行该default语句
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程
	}

	return 0;
}

Window::Window() :
	m_pMouseDevice(new MouseDevice()),
	m_pKeyboardDevice(new KeyboardDevice()),
	m_pInputInterface(new InputInterface())
{
	m_pd3dDevice = NULL;
	m_pWindowLoop = DefaultWindowLoop;
	m_pInitAction = DefaultInitAction;
	SpaceEngineWindow = this;
}

Window::~Window()
{
	if (SpaceEngineWindow == this)
		SpaceEngineWindow = NULL;
	if (m_pd3dDevice)
		SafeRelease(m_pd3dDevice);
}

void Window::SetWindow(LPCTSTR title, int width, int height)
{
	m_WindowTitle = title;
	m_WindowWidth = width;
	m_WindowHeight = height;
}

HRESULT Window::InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(HWND hwnd), void(*InitAction)(Window* window))
{
	m_pWindowLoop = WindowLoop;
	m_pInitAction = InitAction;
	//【1】窗口创建四步曲之一：开始设计一个完整的窗口类
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;							//窗口的附加内存，依然取0就行了
	wndClass.hInstance = hInstance;						//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  //为hbrBackground成员指定一个白色画刷句柄	
	wndClass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = L"SpaceEngineWindow";		//用一个以空终止的字符串，指定窗口类的名字。

														//【2】窗口创建四步曲之二：注册窗口类
	if (!RegisterClassEx(&wndClass))				//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;

	//【3】窗口创建四步曲之三：正式创建窗口
	HWND hwnd = CreateWindow(L"SpaceEngineWindow", m_WindowTitle,				//喜闻乐见的创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_WindowWidth,
		m_WindowHeight, NULL, NULL, hInstance, NULL);

	//Direct3D资源的初始化，成功或者失败都用messagebox予以显示
	if (E_FAIL == Direct3D_Init(hwnd))
	{
		MessageBox(hwnd, L"Direct3D初始化失败~！", L"消息窗口", 0); //使用MessageBox函数，创建一个消息窗口 
	}
	m_pInputInterface->Init(hInstance);
	Objects_Init(hwnd);

	//【4】窗口创建四步曲之四：窗口的移动、显示与更新
	MoveWindow(hwnd, 250, 80, m_WindowWidth, m_WindowHeight, true);		//调整窗口显示时的位置，使窗口左上角位于（250,80）处
	ShowWindow(hwnd, nShowCmd);    //调用ShowWindow函数来显示窗口
	UpdateWindow(hwnd);						//对窗口进行更新，就像我们买了新房子要装修一样



											//【5】消息循环过程
	MSG msg = { 0 };  //初始化msg
	while (msg.message != WM_QUIT)			//使用while循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);		//该函数分发一个消息给窗口程序。
		}
		else
		{
			m_pWindowLoop(hwnd);   //进行渲染
		}
	}
	//【6】窗口类的注销
	UnregisterClass(L"SpaceEngineWindow", wndClass.hInstance);  //程序准备结束，注销窗口类
	return 0;
}

void Window::Release()
{
	if (SpaceEngineWindow == this)
		SpaceEngineWindow = NULL;
	if (m_pd3dDevice != NULL)
		SafeRelease(m_pd3dDevice);
	m_pd3dDevice = NULL;
}

HRESULT Window::Direct3D_Init(HWND hwnd)
{
	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之一，创接口】：创建Direct3D接口对象, 以便用该Direct3D对象创建Direct3D设备对象
	//--------------------------------------------------------------------------------------
	LPDIRECT3D9  pD3D = NULL; //Direct3D接口对象的创建
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION))) //初始化Direct3D接口对象，并进行DirectX版本协商
		return E_FAIL;

	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之二,取信息】：获取硬件设备信息
	//--------------------------------------------------------------------------------------
	D3DCAPS9 caps; int vp = 0;
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //支持硬件顶点运算，我们就采用硬件顶点运算，妥妥的
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //不支持硬件顶点运算，无奈只好采用软件顶点运算

	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之三，填内容】：填充D3DPRESENT_PARAMETERS结构体
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
	// 【Direct3D初始化四步曲之四，创设备】：创建Direct3D设备接口
	//--------------------------------------------------------------------------------------
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, vp, &d3dpp, &m_pd3dDevice)))
		return E_FAIL;

	SafeRelease(pD3D); //LPDIRECT3D9接口对象的使命完成，我们将其释放掉
	return S_OK;
}

HRESULT Window::Objects_Init(HWND hwnd)
{
	m_pMouseDevice->Init(hwnd, *m_pInputInterface);
	m_pKeyboardDevice->Init(hwnd, *m_pInputInterface);
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);   //开启背面消隐
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);
	TexturePrintInitEx(m_pd3dDevice);
	m_pd3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	OpenDepthBuffer(m_pd3dDevice);
	SetDepthBuffer(m_pd3dDevice);
	m_pInitAction(this);
	return S_OK;
}

void Window::BeginPrint()
{
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);//一：清屏操作

	m_pd3dDevice->BeginScene();			//开始绘制
}

void Window::EndPrint()
{
	m_pd3dDevice->EndScene();	//结束绘制

	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);	//翻转显示
}

LPDIRECT3DDEVICE9 Window::GetD3DDevice()
{
	return m_pd3dDevice;
}

int Window::GetWindowWidth()
{
	return m_WindowWidth;
}

int Window::GetWindowHeight()
{
	return m_WindowHeight;
}

void SetMainWindow(Window* window)
{
	SpaceEngineWindow = window;
}