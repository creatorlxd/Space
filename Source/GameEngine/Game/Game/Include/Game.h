#pragma once 
#include "stdafx.h"
#include "Window.h"
class Game				//������Ϸ��
{
public:
	Game();
	~Game();
	Game* const GetMainGame();	//��ȡ��ǰ����Ϸ��ָ��
public:
	Window m_Window;			//����
protected:
	static Game* sm_pThis;		//��ǰ����Ϸָ��
};