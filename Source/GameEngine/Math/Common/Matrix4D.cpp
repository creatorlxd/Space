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
#include "Matrix4D.h"
#include <cstring>

SpaceGameEngine::Matrix4D::Matrix4D()
	:XMFLOAT4X4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
}

SpaceGameEngine::Matrix4D::Matrix4D(float __11, float __12, float __13, float __14, float __21, float __22, float __23, float __24, float __31, float __32, float __33, float __34, float __41, float __42, float __43, float __44)
	:XMFLOAT4X4(__11,__12,__13,__14,
				__21,__22,__23,__24,
				__31,__32,__33,__34,
				__41,__42,__43,__44)
{
}

SpaceGameEngine::Matrix4D::Matrix4D(const XMFLOAT4X4 & c)
	:XMFLOAT4X4(c)
{
}

SpaceGameEngine::Matrix4D::Matrix4D(const Matrix4D & m)
{
	memcpy(this->m, m.m, sizeof(float) * 16);
}

SpaceGameEngine::Matrix4D::Matrix4D(CXMMATRIX m)
{
	XMStoreFloat4x4(this, m);
}

bool SpaceGameEngine::Matrix4D::operator=(const XMFLOAT4X4 & c)
{
	XMFLOAT4X4::operator=(c);
	return true;
}

bool SpaceGameEngine::Matrix4D::operator=(const Matrix4D & m)
{
	memcpy(this->m, m.m, sizeof(float) * 16);
	return true;
}

bool SpaceGameEngine::Matrix4D::operator=(CXMMATRIX m)
{
	XMStoreFloat4x4(this, m);
	return true;
}

SpaceGameEngine::Matrix4D::operator XMMATRIX() const
{
	return XMLoadFloat4x4(this);
}
