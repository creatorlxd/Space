#pragma once
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"
#include "Game/Object/Include/ObjectManager.h"
#include "Game/Message/Include/Message.h"
#include "Game/Scene/Include/Scene.h"
#include "Game/Game/Include/Game.h"

ComponentManager* GetComponentManager();
ObjectManager* GetObjectManager();
MessageManager* GetMessageManager();
Scene* GetScene();
Game* GetGame();