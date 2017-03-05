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
	void SetWindow(LPCTSTR title=L"SpaceEngineWindow", int width=800, int height=600);			//设置窗口信息
	virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(HWND hwnd) = DefaultWindowLoop,void (*InitAction)(Window* window) = DefaultInitAction);	//初始化，需先SetWindow
	virtual void Release();							//释放窗口
	void BeginPrint();								//开始D3D绘制
	void EndPrint();								//结束D3D绘制
	LPDIRECT3DDEVICE9 GetD3DDevice();				//获取D3D接口
	int GetWindowWidth();							//获取窗口宽度
	int GetWindowHeight();							//获取窗口高度

	MouseDevice* m_pMouseDevice;						//鼠标设备
	KeyboardDevice* m_pKeyboardDevice;				//键盘设备
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;					//D3D9接口
	int m_WindowWidth;								//窗口宽度
	int m_WindowHeight;								//窗口高度
	LPCTSTR m_WindowTitle;							//窗口标题

	virtual HRESULT	Direct3D_Init(HWND hwnd);		 //在这个函数中进行Direct3D的初始化
	virtual HRESULT Objects_Init(HWND hwnd); 		//在这个函数中进行要绘制的物体的资源初始化

	void (*m_pWindowLoop)(HWND hwnd);						//游戏循环内容函数指针
	void (*m_pInitAction)(Window* window);					//游戏初始化函数
	InputInterface* m_pInputInterface;				//输入设备接口
};
void SetMainWindow(Window* window);					//设置主窗口