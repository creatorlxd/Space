#pragma once
#include"Space.h"
#include"stdafx.h"
#include"Texture.h"
void DefaultWindowLoop(HWND hwnd);				//Ĭ�ϵ���Ϸѭ������ָ��
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows����ѭ��
class Window						//���ڿ��
{
public:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window();
	~Window();
	void SetWindow(LPCWSTR title=L"SpaceEngineWindow", int width=800, int height=600);			//���ô�����Ϣ
	virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(HWND hwnd) = DefaultWindowLoop);	//��ʼ��������SetWindow
	virtual HRESULT	Direct3D_Init(HWND hwnd);		 //����������н���Direct3D�ĳ�ʼ��
	virtual HRESULT Objects_Init(HWND hwnd); 		//����������н���Ҫ���Ƶ��������Դ��ʼ��
	void BeginPrint();								//��ʼD3D����
	void EndPrint();								//����D3D����
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;					//D3D9�ӿ�
	int m_WindowWidth;								//���ڿ��
	int m_WindowHeight;								//���ڸ߶�
	LPCWSTR m_WindowTitle;							//���ڱ���
	void (*m_pWindowLoop)(HWND hwnd);						//��Ϸѭ�����ݺ���ָ��
};