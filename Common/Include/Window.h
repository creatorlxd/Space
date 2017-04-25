#pragma once
#include"Space.h"
#include"stdafx.h"
#include"Texture.h"
#include"ClassDef.h"
#include"InputDevice.h"
void DefaultWindowLoop(HWND hwnd);				//Ĭ�ϵ���Ϸѭ������ָ��
void DefaultInitAction(Window* window);					//Ĭ�ϵĳ�ʼ������
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	//Windows����ѭ��
class Window						//���ڿ��
{
public:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window();
	~Window();
	void SetWindow(LPCTSTR title=L"SpaceEngineWindow", DWORD width=800, DWORD height=600);			//���ô�����Ϣ
	virtual HRESULT InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, void(*WindowLoop)(HWND hwnd) = DefaultWindowLoop,void (*InitAction)(Window* window) = DefaultInitAction);	//��ʼ��������SetWindow
	virtual void Release();							//�ͷŴ���
	void BeginPrint();								//��ʼD3D����
	void EndPrint();								//����D3D����
	LPDIRECT3DDEVICE9 GetD3DDevice();				//��ȡD3D�ӿ�
	DWORD GetWindowWidth();							//��ȡ���ڿ��
	DWORD GetWindowHeight();							//��ȡ���ڸ߶�

	unique_ptr<MouseDevice> m_pMouseDevice;					//����豸
	unique_ptr<KeyboardDevice> m_pKeyboardDevice;				//�����豸
	bool ReadInputDevice();								//���ͼ��̵��豸�Ķ�ȡ
protected:
	LPDIRECT3DDEVICE9 m_pd3dDevice;					//D3D9�ӿ�
	DWORD m_WindowWidth;								//���ڿ��
	DWORD m_WindowHeight;								//���ڸ߶�
	LPCTSTR m_WindowTitle;							//���ڱ���

	virtual HRESULT	Direct3DInit(HWND hwnd);		 //����������н���Direct3D�ĳ�ʼ��
	virtual HRESULT EnvironmentInit(HWND hwnd); 		//����������н��л�����ʼ��

	void (*m_pWindowLoop)(HWND hwnd);						//��Ϸѭ�����ݺ���ָ��
	void (*m_pInitAction)(Window* window);					//��Ϸ��ʼ������
	unique_ptr<InputInterface> m_pInputInterface;				//�����豸�ӿ�
};
void SetMainWindow(Window* window);					//����������
extern Window* SpaceEngineWindow;