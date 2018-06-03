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
#include "Matrix3D.h"
#include <cstring>

SpaceGameEngine::Matrix3D::Matrix3D()
	:XMFLOAT3X3(0, 0, 0, 0, 0, 0, 0, 0, 0)
{
}

SpaceGameEngine::Matrix3D::Matrix3D(float __11, float __12, float __13, float __21, float __22, float __23, float __31, float __32, float __33)
	:XMFLOAT3X3(__11, __12, __13,
				__21, __22, __23,
				__31, __32, __33)
{
}

SpaceGameEngine::Matrix3D::Matrix3D(const XMFLOAT3X3 & c)
	:XMFLOAT3X3(c)
{
}

SpaceGameEngine::Matrix3D::Matrix3D(const Matrix3D & m)
{
	memcpy(this->m, m.m, sizeof(float) * 9);
}

SpaceGameEngine::Matrix3D::Matrix3D(CXMMATRIX m)
{
	XMStoreFloat3x3(this, m);
}

bool SpaceGameEngine::Matrix3D::operator=(const XMFLOAT3X3 & c)
{
	XMFLOAT3X3::operator=(c);
	return true;
}

bool SpaceGameEngine::Matrix3D::operator=(const Matrix3D & m)
{
	memcpy(this->m, m.m, sizeof(float) * 9);
	return true;
}

bool SpaceGameEngine::Matrix3D::operator=(CXMMATRIX m)
{
	XMStoreFloat3x3(this, m);
	return true;
}

SpaceGameEngine::Matrix3D::operator XMMATRIX()
{
	return XMLoadFloat3x3(this);
}
