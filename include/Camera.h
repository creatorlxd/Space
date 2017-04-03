#pragma once
#include "stdafx.h"
#include "Space.h"
#include "InputDevice.h"

class Camera
{
public:
	Camera(KeyboardDevice& keyboard,MouseDevice& mouse):m_KeyBoardDevice(keyboard),m_MouseDevice(mouse){}
	~Camera();

private:
	KeyboardDevice& m_KeyBoardDevice;
	MouseDevice& m_MouseDevice;
};