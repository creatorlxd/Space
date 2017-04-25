#pragma once
#include"Space.h"
#include"stdafx.h"
#include"Texture.h"
#include"ClassDef.h"
#include"InputDevice.h"
void DefaultWindowLoop(HWND hwnd);				//默认的游戏循环函数指针
void DefaultInitAction(Window* window);					//默认的初始化函数
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows窗口循环
class Window						//窗口框架
{
public:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window();
	~Window();
	void SetWindow(LPCTSTR title=L"SpaceEngineWindow", DWORD width=800, DWORD height=600);			//设置窗口信息
	virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(HWND hwnd) = DefaultWindowLoop,void (*InitAction)(Window* window) = DefaultInitAction);	//初始化，需先SetWindow
	virtual void Release();							//释放窗口
	void BeginPrint();								//开始D3D绘制
	void EndPrint();								//结束D3D绘制
	LPDIRECT3DDEVICE9 GetD3DDevice();				//获取D3D接口
	DWORD GetWindowWidth();							//获取窗口宽度
	DWORD GetWindowHeight();							//获取窗口高度

	unique_ptr<MouseDevice> m_pMouseDevice;					//鼠标设备
	unique_ptr<KeyboardDevice> m_pKeyboardDevice;				//键盘设备
	bool ReadInputDevice();								//鼠标和键盘的设备的读取
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;					//D3D9接口
	DWORD m_WindowWidth;								//窗口宽度
	DWORD m_WindowHeight;								//窗口高度
	LPCTSTR m_WindowTitle;							//窗口标题

	virtual HRESULT	Direct3DInit(HWND hwnd);		 //在这个函数中进行Direct3D的初始化
	virtual HRESULT EnvironmentInit(HWND hwnd); 		//在这个函数中进行环境初始化

	void (*m_pWindowLoop)(HWND hwnd);						//游戏循环内容函数指针
	void (*m_pInitAction)(Window* window);					//游戏初始化函数
	unique_ptr<InputInterface> m_pInputInterface;				//输入设备接口
};
void SetMainWindow(Window* window);					//设置主窗口
extern Window* SpaceEngineWindow;