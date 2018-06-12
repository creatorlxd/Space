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
#include "Vector4D.h"

SpaceGameEngine::Vector4D::Vector4D()
	:XMFLOAT4(0, 0, 0, 0)
{
}

SpaceGameEngine::Vector4D::Vector4D(float _x, float _y, float _z, float _w)
	:XMFLOAT4(_x, _y, _z, _w)
{
}

SpaceGameEngine::Vector4D::Vector4D(const XMFLOAT4 & c)
	: XMFLOAT4(c)
{
}

SpaceGameEngine::Vector4D::Vector4D(const Vector4D & v)
	: XMFLOAT4(v.x, v.y, v.z, v.w)
{
}

SpaceGameEngine::Vector4D::Vector4D(FXMVECTOR v)
{
	XMStoreFloat4(this, v);
}

bool SpaceGameEngine::Vector4D::operator=(const XMFLOAT4 & c)
{
	x = c.x;
	y = c.y;
	z = c.z;
	w = c.w;
	return true;
}

bool SpaceGameEngine::Vector4D::operator=(const Vector4D & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return true;
}

bool SpaceGameEngine::Vector4D::operator=(FXMVECTOR v)
{
	XMStoreFloat4(this, v);
	return true;
}

SpaceGameEngine::Vector4D::operator XMVECTOR() const
{
	return XMLoadFloat4(this);
}

bool SpaceGameEngine::operator==(const Vector4D & v1, const Vector4D & v2)
{
	if (!FloatEqual(v1.x, v2.x))
		return false;
	if (!FloatEqual(v1.y, v2.y))
		return false;
	if (!FloatEqual(v1.z, v2.z))
		return false;
	if (!FloatEqual(v1.w, v2.w))
		return false;
	return true;
}

bool SpaceGameEngine::operator!=(const Vector4D & v1, const Vector4D & v2)
{
	return !(v1 == v2);
}
