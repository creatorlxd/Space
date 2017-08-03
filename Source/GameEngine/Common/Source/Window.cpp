#include"stdafx.h"
#include"Window.h"
using namespace SpaceGameEngine;

Window* SpaceGameEngine::Window::sm_pThis = nullptr;

void SpaceGameEngine::DefaultWindowLoop()
{
	//do nothing
}

void SpaceGameEngine::DefaultInitAction()
{
	//do nothing
}

LRESULT CALLBACK SpaceGameEngine::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(SpaceEngineWindow==nullptr)
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程
	switch (message)						//switch语句开始
	{
	case WM_PAINT:						// 若是客户区重绘消息
		SpaceEngineWindow->m_pWindowLoop();                 //调用Direct3D渲染函数
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

	case WM_SIZE:
		SpaceEngineWindow->SetWindowWidth(LOWORD(lParam));
		SpaceEngineWindow->SetWindowHeight(HIWORD(lParam));
		SpaceEngineWindow->Resize();
		break;
	default:										//若上述case条件都不符合，则执行该default语句
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程
	}

	return 0;
}

SpaceGameEngine::Window::Window()
{
	m_Hwnd = NULL;
	m_pD3DDevice = nullptr;
	m_pD3DDeviceContext = nullptr;
	m_IfUse4xMsaa = true;
	m_4xMsaaQuality = 0;
	m_pSwapChain = nullptr;
	m_pDepthStencilBuffer = nullptr;
	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;
	m_pWindowLoop = DefaultWindowLoop;
	m_pInitAction = DefaultInitAction;
	m_IfShowCursor = true;
	m_WindowPosition = m_StartWindowPosition;
	m_pInputLayout = nullptr;
	m_pVertexShaderCode = nullptr;
	SetAsMainWindow();
}

SpaceGameEngine::Window::~Window()
{
	Release();
}

void SpaceGameEngine::Window::SetWindow(LPCTSTR title, DWORD width, DWORD height)
{
	m_WindowTitle = title;
	m_WindowWidth = width;
	m_WindowHeight = height;
}

HRESULT SpaceGameEngine::Window::InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(), void(*InitAction)())
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
	m_Hwnd = CreateWindow(L"SpaceEngineWindow", m_WindowTitle,				//喜闻乐见的创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_WindowWidth,
		m_WindowHeight, NULL, NULL, hInstance, NULL);

	//Direct3D资源的初始化，成功或者失败都用messagebox予以显示
	if (E_FAIL == Direct3DInit(m_Hwnd))
	{
		MessageBox(m_Hwnd, L"Direct3D初始化失败~！", L"消息窗口", 0); //使用MessageBox函数，创建一个消息窗口 
	}

	//【4】窗口创建四步曲之四：窗口的移动、显示与更新
	MoveWindow(m_Hwnd, m_WindowPosition.first, m_WindowPosition.second, m_WindowWidth, m_WindowHeight, true);		//调整窗口显示时的位置，使窗口左上角位于（250,80）处
	ShowWindow(m_Hwnd, nShowCmd);    //调用ShowWindow函数来显示窗口
	UpdateWindow(m_Hwnd);						//对窗口进行更新，就像我们买了新房子要装修一样

	EnvironmentInit(m_Hwnd);

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
			m_pWindowLoop();   //进行渲染
		}
	}
	//【6】窗口类的注销
	UnregisterClass(L"SpaceEngineWindow", wndClass.hInstance);  //程序准备结束，注销窗口类
	return 0;
}

void SpaceGameEngine::Window::Release()
{
	if (SpaceEngineWindow == this)
		sm_pThis = nullptr;
	SafeRelease(m_pD3DDevice);
	SafeRelease(m_pD3DDeviceContext);
	SafeRelease(m_pSwapChain);
	SafeRelease(m_pDepthStencilBuffer);
	SafeRelease(m_pRenderTargetView);
	SafeRelease(m_pDepthStencilView);
	SafeRelease(m_pInputLayout);
	SafeRelease(m_pVertexShaderCode);
	if (!m_IfShowCursor)
	{
		ChangeIfShowCursor(true);
	}
}

HRESULT SpaceGameEngine::Window::Direct3DInit(HWND hwnd)
{
	UINT CreateDeviceFlags = 0;

#if  defined(DEBUG)||defined(_DEBUG)
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT  hr = D3D11CreateDevice(
		0,                     //  默认显示适配器
		D3D_DRIVER_TYPE_HARDWARE,
		0,                     //  不使用软件设备
		CreateDeviceFlags,
		0, 0,               //  默认的特征等级数组
		D3D11_SDK_VERSION,
		&m_pD3DDevice,
		&featureLevel,
		&m_pD3DDeviceContext);
	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return  false;
	}
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D FeatureLevel 11 unsupported.", 0, 0);
		return  false;
	}
	HR(m_pD3DDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	assert(m_4xMsaaQuality > 0);

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = m_WindowWidth;    // 使用窗口客户区宽度
	sd.BufferDesc.Height = m_WindowHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	// 是否使用4X MSAA?
	if (m_IfUse4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		// m4xMsaaQuality是通过CheckMultisampleQualityLevels()方法获得的
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	// NoMSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = m_Hwnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGIDevice* dxgiDevice = 0;
	HR(m_pD3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_pD3DDevice, &sd, &m_pSwapChain));

	SafeRelease(dxgiDevice);
	SafeRelease(dxgiAdapter);
	SafeRelease(dxgiFactory);

	Resize();
	return true;
}

HRESULT SpaceGameEngine::Window::EnvironmentInit(HWND hwnd)
{
	m_pInitAction();
	CompileShaderFromFile(L"./Source/GameEngine/Shader/Common/DefaultVS.hlsl", "", "main", "vs_5_0", NULL, &m_pVertexShaderCode);
	SetDefaultInputLayout(m_pD3DDevice, m_pVertexShaderCode, &m_pInputLayout);
	return S_OK;
}

void SpaceGameEngine::Window::BeginPrint()
{
	assert(m_pD3DDeviceContext);
	assert(m_pSwapChain);

	m_pD3DDeviceContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	m_pD3DDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void SpaceGameEngine::Window::EndPrint()
{
	HR(m_pSwapChain->Present(0, 0));
}

HWND SpaceGameEngine::Window::GetHwnd()
{
	return m_Hwnd;
}

ID3D11Device* SpaceGameEngine::Window::GetD3DDevice()
{
	return m_pD3DDevice;
}

ID3D11DeviceContext * SpaceGameEngine::Window::GetD3DDeviceContext()
{
	return m_pD3DDeviceContext;
}

void SpaceGameEngine::Window::SetWindowWidth(DWORD width)
{
	m_WindowWidth = width;
}

void SpaceGameEngine::Window::SetWindowHeight(DWORD height)
{
	m_WindowHeight = height;
}

DWORD SpaceGameEngine::Window::GetWindowWidth()
{
	return m_WindowWidth;
}

DWORD SpaceGameEngine::Window::GetWindowHeight()
{
	return m_WindowHeight;
}

void SpaceGameEngine::Window::Resize()
{
	assert(m_pD3DDeviceContext);
	assert(m_pD3DDevice);
	assert(m_pSwapChain);

	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.

	SafeRelease(m_pRenderTargetView);
	SafeRelease(m_pDepthStencilView);
	SafeRelease(m_pDepthStencilBuffer);


	// Resize the swap chain and recreate the render target view.

	HR(m_pSwapChain->ResizeBuffers(1, m_WindowWidth, m_WindowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_pD3DDevice->CreateRenderTargetView(backBuffer, 0, &m_pRenderTargetView));
	SafeRelease(backBuffer);

	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_WindowWidth;
	depthStencilDesc.Height = m_WindowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Use 4X MSAA? --must match swap chain MSAA values.
	if (m_IfUse4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(m_pD3DDevice->CreateTexture2D(&depthStencilDesc, 0, &m_pDepthStencilBuffer));
	HR(m_pD3DDevice->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView));


	// Bind the render target view and depth/stencil view to the pipeline.

	m_pD3DDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_ScreenViewport.TopLeftX = 0;
	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width = static_cast<float>(m_WindowWidth);
	m_ScreenViewport.Height = static_cast<float>(m_WindowHeight);
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;

	m_pD3DDeviceContext->RSSetViewports(1, &m_ScreenViewport);
}

void SpaceGameEngine::Window::ChangeIfShowCursor(bool b)
{
	if (m_IfShowCursor == b)
	{
		return;
	}
	else
	{
		m_IfShowCursor = b;
		ShowCursor(b);
	}
}

void SpaceGameEngine::Window::SetCursorPosition(int x, int y)
{
	auto pos = GetWindowPosition();
	SetCursorPos(pos.first + x, pos.second + y);
}

void SpaceGameEngine::Window::UpdateWindowSize()
{
	RECT r;
	GetWindowRect(m_Hwnd, &r);
	m_WindowWidth = abs(r.right - r.left);
	m_WindowHeight = abs(r.bottom - r.top);
}

std::pair<int, int> SpaceGameEngine::Window::GetWindowPosition()
{
	RECT r;
	GetWindowRect(m_Hwnd, &r);
	return std::pair<int, int>(r.left,r.top);
}

void SpaceGameEngine::Window::SetWindowPosition(int x, int y)
{
	SetWindowPos(m_Hwnd, HWND_TOPMOST, x, y, m_WindowWidth, m_WindowHeight, SWP_SHOWWINDOW);
	m_WindowPosition = std::make_pair(x, y);
}

void SpaceGameEngine::Window::SetWindowSize(int x, int y)
{
	SetWindowPos(m_Hwnd, HWND_TOPMOST, m_WindowPosition.first, m_WindowPosition.second, x, y, SWP_SHOWWINDOW);
	m_WindowWidth = x;
	m_WindowHeight = y;
}

Window * SpaceGameEngine::Window::GetMainWindow()
{
	return sm_pThis;
}

void SpaceGameEngine::Window::SetAsMainWindow()
{
	sm_pThis = this;
}

void SpaceGameEngine::Window::ChangeIfUse4xMsaa(bool b)
{
	m_IfUse4xMsaa = b;
}

void SpaceGameEngine::Window::SetVertexShaderCode(ID3DBlob * pshader)
{
	SafeRelease(m_pVertexShaderCode);
	m_pVertexShaderCode = pshader;
}
