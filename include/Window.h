#pragma once
#include"Space.h"
#include"stdafx.h"
#include"Texture.h"
void DefaultWindowLoop(HWND hwnd);				//默认的游戏循环函数指针
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows窗口循环
class Window						//窗口框架
{
public:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window();
	~Window();
	void SetWindow(LPCWSTR title=L"SpaceEngineWindow", int width=800, int height=600);			//设置窗口信息
	virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(HWND hwnd) = DefaultWindowLoop);	//初始化，需先SetWindow
	virtual HRESULT	Direct3D_Init(HWND hwnd);		 //在这个函数中进行Direct3D的初始化
	virtual HRESULT Objects_Init(HWND hwnd); 		//在这个函数中进行要绘制的物体的资源初始化
	void BeginPrint();								//开始D3D绘制
	void EndPrint();								//结束D3D绘制
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;					//D3D9接口
	int m_WindowWidth;								//窗口宽度
	int m_WindowHeight;								//窗口高度
	LPCWSTR m_WindowTitle;							//窗口标题
	void (*m_pWindowLoop)(HWND hwnd);						//游戏循环内容函数指针
};