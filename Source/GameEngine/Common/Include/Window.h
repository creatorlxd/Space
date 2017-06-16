#pragma once
#include"Space.h"
#include"stdafx.h"
#include"Texture.h"
#include"ClassDef.h"
#include"InputDevice.h"
void DefaultWindowLoop();				//默认的游戏循环函数指针
void DefaultInitAction();					//默认的初始化函数
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows窗口循环
class Window						//窗口框架
{
public:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window();
	~Window();
	void SetWindow(LPCTSTR title=L"SpaceEngineWindow", DWORD width=800, DWORD height=600);			//设置窗口信息
	virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)() = DefaultWindowLoop,void (*InitAction)() = DefaultInitAction);	//初始化，需先SetWindow
	virtual void Release();							//释放窗口
	void BeginPrint();								//开始D3D绘制
	void EndPrint();								//结束D3D绘制
	HWND GetHwnd();									//获取窗口句柄
	LPDIRECT3DDEVICE9 GetD3DDevice();				//获取D3D接口
	void SetWindowWidth(DWORD width);				//设置窗口宽度
	void SetWindowHeight(DWORD height);				//设置窗口高度
	DWORD GetWindowWidth();							//获取窗口宽度
	DWORD GetWindowHeight();						//获取窗口高度
	void Resize();									//改变了窗口大小之后的事
	void ChangeIfShowCursor(bool b);				//改变是否显示鼠标
	void SetCursorPosition(int x, int y);			//设置鼠标位置
	void UpdateWindowSize();						//重新获取窗口大小
	std::pair<int, int> GetWindowPosition();		//获取窗口位置

	static Window* GetMainWindow();					//获取主窗口指针
	void SetAsMainWindow();							//设置为主窗口
protected:
	static Window* sm_pThis;

	HWND m_Hwnd;									//窗口句柄
	LPDIRECT3DDEVICE9 m_pd3dDevice;					//D3D9接口
	DWORD m_WindowWidth;								//窗口宽度
	DWORD m_WindowHeight;								//窗口高度
	LPCTSTR m_WindowTitle;							//窗口标题

	virtual HRESULT	Direct3DInit(HWND hwnd);		 //在这个函数中进行Direct3D的初始化
	virtual HRESULT EnvironmentInit(HWND hwnd); 		//在这个函数中进行环境初始化

	void (*m_pWindowLoop)();						//游戏循环内容函数指针
	void (*m_pInitAction)();					//游戏初始化函数

	bool m_IfShowCursor;						//是否显示鼠标
};
#define SpaceEngineWindow Window::GetMainWindow()