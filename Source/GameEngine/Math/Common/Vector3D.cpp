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
#include "Vector3D.h"

SpaceGameEngine::Vector3D::Vector3D()
	:XMFLOAT3(0, 0, 0)
{
}

SpaceGameEngine::Vector3D::Vector3D(float _x, float _y, float _z)
	:XMFLOAT3(_x, _y, _z)
{
}

SpaceGameEngine::Vector3D::Vector3D(const XMFLOAT3 & c)
	: XMFLOAT3(c)
{
}

SpaceGameEngine::Vector3D::Vector3D(const Vector3D & v)
	: XMFLOAT3(v.x, v.y, v.z)
{
}

SpaceGameEngine::Vector3D::Vector3D(FXMVECTOR v)
{
	XMStoreFloat3(this, v);
}

bool SpaceGameEngine::Vector3D::operator=(const XMFLOAT3 & c)
{
	x = c.x;
	y = c.y;
	z = c.z;
	return true;
}

bool SpaceGameEngine::Vector3D::operator=(const Vector3D & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return true;
}

bool SpaceGameEngine::Vector3D::operator=(FXMVECTOR v)
{
	XMStoreFloat3(this, v);
	return true;
}

SpaceGameEngine::Vector3D::operator XMVECTOR()
{
	return XMLoadFloat3(this);
}

bool SpaceGameEngine::operator==(const Vector3D & v1, const Vector3D & v2)
{
	if (!FloatEqual(v1.x, v2.x))
		return false;
	if (!FloatEqual(v1.y, v2.y))
		return false;
	if (!FloatEqual(v1.z, v2.z))
		return false;
	return true;
}
