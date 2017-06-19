#pragma once 
#include "stdafx.h"
#include "Window.h"
#include "InputDevice.h"
#include "Game/Scene/Include/Scene.h"

class Game				//������Ϸ��
{
public:
	Game();
	~Game();
	static Game* GetMainGame();	//��ȡ��ǰ����Ϸ��ָ��
	void SetAsMainGame();	//����Ϊ��Ҫ����Ϸ

	void Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);			//��ʼ��
	static void Start();			//��ʼ
	static void Run();				//ÿ֡������
	void Release();			//�ͷ�

	void SetScene(Scene* ps);		//��һ�����ó���
	void ChangeScene(Scene* ps);	//�ı䳡��

	bool IfReadKeyboard();
	bool IfReadMouse();
	void ChangeIfReadKeyboard(bool b);
	void ChangeIfReadMouse(bool b);

	void ReadInputDevice();			//��ȡ�����豸

	void StartRunGame();			//��ʼ������Ϸ

	static void ExitGame();			//�˳���Ϸ
public:
	Window m_Window;			//����
	KeyboardDevice m_KeyboardDevice;	//�����豸
	MouseDevice m_MouseDevice;			//����豸
private:
	static Game* sm_pThis;		//��ǰ����Ϸָ��
	Scene* m_pScene;			//��ǰ�ĳ���
	InputInterface m_InputInterface;	//����ӿ�
	bool m_IfReadKeyboard;		//�Ƿ��ȡ����
	bool m_IfReadMouse;			//�Ƿ��ȡ���

	static HINSTANCE sm_hInstance;
	static HINSTANCE sm_hPrevInstance;
	static LPSTR sm_lpCmdLine;
	static int sm_nShowCmd;
};