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

	void DefaultWindowLoop();				//Ĭ�ϵ���Ϸѭ������ָ��
	void DefaultInitAction();					//Ĭ�ϵĳ�ʼ������
	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows����ѭ��
	class Window						//���ڿ��
	{
	public:
		friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		Window();
		~Window();
		void SetWindow(LPCTSTR title = L"SpaceEngineWindow", DWORD width = 800, DWORD height = 600);			//���ô�����Ϣ
		virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)() = DefaultWindowLoop, void(*InitAction)() = DefaultInitAction);	//��ʼ��������SetWindow
		void BeginPrint();								//��ʼD3D����
		void EndPrint();								//����D3D����
		HWND GetHwnd();									//��ȡ���ھ��
		ID3D11Device* GetD3DDevice();				//��ȡD3D
		ID3D11DeviceContext* GetD3DDeviceContext();
		void SetWindowWidth(DWORD width);				//���ô��ڿ��
		void SetWindowHeight(DWORD height);				//���ô��ڸ߶�
		DWORD GetWindowWidth();							//��ȡ���ڿ��
		DWORD GetWindowHeight();						//��ȡ���ڸ߶�
		void Resize();									//�ı��˴��ڴ�С֮�����
		void ChangeIfShowCursor(bool b);				//�ı��Ƿ���ʾ���
		void SetCursorPosition(int x, int y);			//�������λ��
		std::pair<int, int> GetCursorPosition();		//��ȡ���λ��
		void UpdateWindowSize();						//���»�ȡ���ڴ�С
		std::pair<int, int> GetWindowPosition();		//��ȡ����λ��

		void SetWindowPosition(int x, int y);			//���ô���λ��
		void SetWindowSize(int x, int y);				//���ô��ڴ�С

		static Window* GetMainWindow();					//��ȡ������ָ��
		void SetAsMainWindow();							//����Ϊ������

		void ChangeIfUse4xMsaa(bool b);					//�����Ƿ�ʹ��4X MASS���ز���

		void InitDefaultEffectShaderFromFile(const std::string& filename,DefaultEffectShader& shader);
		DefaultEffectShader& GetEffectShader();
		Vector<DefaultEffectShader*>& GetDefaultEffectShader();

		void SetDefaultState();							//����Ĭ��״̬

		void BeginRun();								//��Ϸ��ʼ
		bool IfBegin();								//��ȡ��Ϸ�Ƿ�ʼ��

		RenderQuality GetRenderQuality();
		void SetRenderQuality(const RenderQuality& rq);
	private:
		Vector<std::pair<DefaultEffectShader*, std::string>> m_InitializationDefaultEffectShaderList;
	protected:
		virtual void Release();							//�ͷŴ���
		bool m_IfReleased;

		static Window* sm_pThis;

		ID3D11Device* m_pD3DDevice;
		ID3D11DeviceContext* m_pD3DDeviceContext;
		UINT m_4xMsaaQuality;
		bool m_IfUse4xMsaa;							//�Ƿ�ʹ��4X MASS���ز���

		IDXGISwapChain* m_pSwapChain;
		ID3D11Texture2D* m_pDepthStencilBuffer;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;
		D3D11_VIEWPORT m_ScreenViewport;

		ID3D11InputLayout* m_pInputLayout;
		ID3D11RasterizerState* m_pRasterizerState;
		
		DefaultEffectShader m_EffectShader;
		Vector<DefaultEffectShader*> m_DefaultEffectShader;

		HWND m_Hwnd;									//���ھ��
		DWORD m_WindowWidth;								//���ڿ��
		DWORD m_WindowHeight;								//���ڸ߶�
		LPCTSTR m_WindowTitle;							//���ڱ���
		std::pair<int, int> m_WindowPosition;			//����λ��
		const std::pair<int, int> m_StartWindowPosition = { 250 ,80 };

		virtual HRESULT	Direct3DInit(HWND hwnd);		 //����������н���Direct3D�ĳ�ʼ��
		virtual HRESULT EnvironmentInit(HWND hwnd); 		//����������н��л�����ʼ��

		void(*m_pWindowLoop)();						//��Ϸѭ�����ݺ���ָ��
		void(*m_pInitAction)();					//��Ϸ��ʼ������

		bool m_IfShowCursor;						//�Ƿ���ʾ���

		bool m_IfBegin;							//��Ϸ�Ƿ��ѿ�ʼ

		RenderQuality m_RenderQuality;

		unsigned int m_FPSLimit;
	};

	Window* GetWindow();
#define SpaceEngineWindow SpaceGameEngine::GetWindow()

}