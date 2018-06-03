/*
Copyright 2018 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "stdafx.h"
#include "Vector2D.h"

SpaceGameEngine::Vector2D::Vector2D()
	:XMFLOAT2(0, 0)
{
}

SpaceGameEngine::Vector2D::Vector2D(float _x, float _y)
	:XMFLOAT2(_x, _y)
{
}

SpaceGameEngine::Vector2D::Vector2D(const XMFLOAT2 & c)
	: XMFLOAT2(c)
{
}

SpaceGameEngine::Vector2D::Vector2D(const Vector2D & v)
	: XMFLOAT2(v.x, v.y)
{
}

SpaceGameEngine::Vector2D::Vector2D(FXMVECTOR v)
{
	XMStoreFloat2(this, v);
}

bool SpaceGameEngine::Vector2D::operator=(const XMFLOAT2 & c)
{
	x = c.x;
	y = c.y;
	return true;
}

bool SpaceGameEngine::Vector2D::operator=(const Vector2D & v)
{
	x = v.x;
	y = v.y;
	return true;
}

bool SpaceGameEngine::Vector2D::operator=(FXMVECTOR v)
{
	XMStoreFloat2(this, v);
	return true;
}

SpaceGameEngine::Vector2D::operator XMVECTOR()
{
	return XMLoadFloat2(this);
}

bool SpaceGameEngine::operator==(const Vector2D & v1, const Vector2D & v2)
{
	if (!FloatEqual(v1.x, v2.x))
		return false;
	if (!FloatEqual(v1.y, v2.y))
		return false;
	return true;
}
