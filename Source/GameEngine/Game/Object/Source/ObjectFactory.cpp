#include "stdafx.h"
#include "../Include/ObjectFactory.h"
using namespace SpaceGameEngine;

Object * SpaceGameEngine::NewObjectByName(const std::string & name)
{
	Object* po = ObjectManager::NewObject();
	if (name != "")
	{
		RegisterObject(name, po);
	}
	return po;
}
