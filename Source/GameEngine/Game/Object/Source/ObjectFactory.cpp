#include "stdafx.h"
#include "../Include/ObjectFactory.h"

Object * NewObjectByName(const std::string & name)
{
	Object* po = ObjectManager::NewObject();
	if (name != "")
	{
		RegisterObject(name, po);
	}
	return po;
}
