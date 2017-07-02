#pragma once
#include"Space.h"
#include"stdafx.h"
#include"InputDevice.h"
void DefaultWindowLoop();				//Ĭ�ϵ���Ϸѭ������ָ��
void DefaultInitAction();					//Ĭ�ϵĳ�ʼ������
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows����ѭ��
class Window						//���ڿ��
{
public:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window();
	~Window();
	void SetWindow(LPCTSTR title=L"SpaceEngineWindow", DWORD width=800, DWORD height=600);			//���ô�����Ϣ
	virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)() = DefaultWindowLoop,void (*InitAction)() = DefaultInitAction);	//��ʼ��������SetWindow
	virtual void Release();							//�ͷŴ���
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
	void UpdateWindowSize();						//���»�ȡ���ڴ�С
	std::pair<int, int> GetWindowPosition();		//��ȡ����λ��

	static Window* GetMainWindow();					//��ȡ������ָ��
	void SetAsMainWindow();							//����Ϊ������

	void ChangeIfUse4xMsaa(bool b);					//�����Ƿ�ʹ��4X MASS���ز���
	void SetViewPort();								//�����ӿ�
protected:
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

	HWND m_Hwnd;									//���ھ��
	DWORD m_WindowWidth;								//���ڿ��
	DWORD m_WindowHeight;								//���ڸ߶�
	LPCTSTR m_WindowTitle;							//���ڱ���

	virtual HRESULT	Direct3DInit(HWND hwnd);		 //����������н���Direct3D�ĳ�ʼ��
	virtual HRESULT EnvironmentInit(HWND hwnd); 		//����������н��л�����ʼ��

	void (*m_pWindowLoop)();						//��Ϸѭ�����ݺ���ָ��
	void (*m_pInitAction)();					//��Ϸ��ʼ������

	bool m_IfShowCursor;						//�Ƿ���ʾ���
};
#define SpaceEngineWindow Window::GetMainWindow()