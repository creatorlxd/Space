#pragma once
#include"Space.h"
#include"stdafx.h"
#include"Texture.h"
#include"ClassDef.h"
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
	LPDIRECT3DDEVICE9 GetD3DDevice();				//��ȡD3D�ӿ�
	DWORD GetWindowWidth();							//��ȡ���ڿ��
	DWORD GetWindowHeight();						//��ȡ���ڸ߶�

	static Window* GetMainWindow();					//��ȡ������ָ��
	void SetAsMainWindow();							//����Ϊ������
protected:
	static Window* sm_pThis;

	HWND m_Hwnd;									//���ھ��
	LPDIRECT3DDEVICE9 m_pd3dDevice;					//D3D9�ӿ�
	DWORD m_WindowWidth;								//���ڿ��
	DWORD m_WindowHeight;								//���ڸ߶�
	LPCTSTR m_WindowTitle;							//���ڱ���

	virtual HRESULT	Direct3DInit(HWND hwnd);		 //����������н���Direct3D�ĳ�ʼ��
	virtual HRESULT EnvironmentInit(HWND hwnd); 		//����������н��л�����ʼ��

	void (*m_pWindowLoop)();						//��Ϸѭ�����ݺ���ָ��
	void (*m_pInitAction)();					//��Ϸ��ʼ������
};
#define SpaceEngineWindow Window::GetMainWindow()