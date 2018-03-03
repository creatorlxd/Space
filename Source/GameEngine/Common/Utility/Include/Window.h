/*
Copyright 2018 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once
#include"Space.h"
#include"InputDevice.h"
#include "ShaderFarmework/VertexShader/Include/VertexShader.h"
#include "ShaderFarmework/PixelShader/Include/PixelShader.h"
#include "ShaderFarmework/EffectShader/Include/EffectShader.h"
#include "ConfigFile.h"

namespace SpaceGameEngine
{
	enum class RenderQuality :unsigned char
	{
		LowQuality=1,
		MediumQuality=2,
		HighQuality=3
	};

	void DefaultWindowLoop();				//默认的游戏循环函数指针
	void DefaultInitAction();					//默认的初始化函数
	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows窗口循环
	class Window						//窗口框架
	{
	public:
		friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		Window();
		~Window();
		void SetWindow(LPCTSTR title = L"SpaceEngineWindow", DWORD width = 800, DWORD height = 600);			//设置窗口信息
		virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)() = DefaultWindowLoop, void(*InitAction)() = DefaultInitAction);	//初始化，需先SetWindow
		void BeginPrint();								//开始D3D绘制
		void EndPrint();								//结束D3D绘制
		HWND GetHwnd();									//获取窗口句柄
		ID3D11Device* GetD3DDevice();				//获取D3D
		ID3D11DeviceContext* GetD3DDeviceContext();
		void SetWindowWidth(DWORD width);				//设置窗口宽度
		void SetWindowHeight(DWORD height);				//设置窗口高度
		DWORD GetWindowWidth();							//获取窗口宽度
		DWORD GetWindowHeight();						//获取窗口高度
		void Resize();									//改变了窗口大小之后的事
		void ChangeIfShowCursor(bool b);				//改变是否显示鼠标
		void SetCursorPosition(int x, int y);			//设置鼠标位置
		std::pair<int, int> GetCursorPosition();		//获取鼠标位置
		void UpdateWindowSize();						//重新获取窗口大小
		std::pair<int, int> GetWindowPosition();		//获取窗口位置

		void SetWindowPosition(int x, int y);			//设置窗口位置
		void SetWindowSize(int x, int y);				//设置窗口大小

		static Window* GetMainWindow();					//获取主窗口指针
		void SetAsMainWindow();							//设置为主窗口

		void ChangeIfUse4xMsaa(bool b);					//设置是否使用4X MASS多重采样

		void InitDefaultEffectShaderFromFile(const std::string& filename,DefaultEffectShader& shader);
		DefaultEffectShader& GetEffectShader();
		Vector<DefaultEffectShader*>& GetDefaultEffectShader();

		void SetDefaultState();							//设置默认状态

		void BeginRun();								//游戏开始
		bool IfBegin();								//获取游戏是否开始了

		RenderQuality GetRenderQuality();
		void SetRenderQuality(const RenderQuality& rq);
	private:
		Vector<std::pair<DefaultEffectShader*, std::string>> m_InitializationDefaultEffectShaderList;
	protected:
		virtual void Release();							//释放窗口
		bool m_IfReleased;

		static Window* sm_pThis;

		ID3D11Device* m_pD3DDevice;
		ID3D11DeviceContext* m_pD3DDeviceContext;
		UINT m_4xMsaaQuality;
		bool m_IfUse4xMsaa;							//是否使用4X MASS多重采样

		IDXGISwapChain* m_pSwapChain;
		ID3D11Texture2D* m_pDepthStencilBuffer;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;
		D3D11_VIEWPORT m_ScreenViewport;

		ID3D11InputLayout* m_pInputLayout;
		ID3D11RasterizerState* m_pRasterizerState;
		
		DefaultEffectShader m_EffectShader;
		Vector<DefaultEffectShader*> m_DefaultEffectShader;

		HWND m_Hwnd;									//窗口句柄
		DWORD m_WindowWidth;								//窗口宽度
		DWORD m_WindowHeight;								//窗口高度
		LPCTSTR m_WindowTitle;							//窗口标题
		std::pair<int, int> m_WindowPosition;			//窗口位置
		const std::pair<int, int> m_StartWindowPosition = { 250 ,80 };

		virtual HRESULT	Direct3DInit(HWND hwnd);		 //在这个函数中进行Direct3D的初始化
		virtual HRESULT EnvironmentInit(HWND hwnd); 		//在这个函数中进行环境初始化

		void(*m_pWindowLoop)();						//游戏循环内容函数指针
		void(*m_pInitAction)();					//游戏初始化函数

		bool m_IfShowCursor;						//是否显示鼠标

		bool m_IfBegin;							//游戏是否已开始

		RenderQuality m_RenderQuality;

		unsigned int m_FPSLimit;
	};

	Window* GetWindow();
#define SpaceEngineWindow SpaceGameEngine::GetWindow()

}