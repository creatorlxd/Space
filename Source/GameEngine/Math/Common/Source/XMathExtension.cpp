/*
Copyright 2017 creatorlxd

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
#include "../Include/XMathExtension.h"

bool SpaceGameEngine::operator < (const XMFLOAT3& v1, const XMFLOAT3& v2)
{
	if (v1.x < v2.x&&v1.y < v2.y&&v1.z < v2.z)
		return true;
	else
		return (v1.x < v2.x||v1.y < v2.y||v1.z < v2.z);
}

bool SpaceGameEngine::operator > (const XMFLOAT3 & v1, const XMFLOAT3 & v2)
{
	if (v1.x > v2.x&&v1.y > v2.y&&v1.z > v2.z)
		return true;
	else
		return (v1.x > v2.x || v1.y > v2.y || v1.z > v2.z);
}

bool SpaceGameEngine::operator == (const XMFLOAT3 & v1, const XMFLOAT3 & v2)
{
	return (v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z);
}

bool SpaceGameEngine::operator != (const XMFLOAT3 & v1, const XMFLOAT3 & v2)
{
	return !(v1 == v2);
}

bool SpaceGameEngine::operator < (const XMFLOAT2 & v1, const XMFLOAT2 & v2)
{
	return (v1.x < v2.x&&v1.y < v2.y);
}

bool SpaceGameEngine::operator == (const XMFLOAT4X4 & m1, const XMFLOAT4X4 & m2)
{
	return memcmp(&m1, &m2, sizeof(XMFLOAT4X4)) == 0;
}

bool SpaceGameEngine::operator != (const XMFLOAT4X4 & m1, const XMFLOAT4X4 & m2)
{
	return !(m1 == m2);
}

XMFLOAT3 SpaceGameEngine::TransformByWorldMatrix(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale, XMFLOAT3 data)
{
	static XMMATRIX mrebuff, mbuff;
	static XMFLOAT3 pos, rot, sca;
	if (pos != position || rot != rotation || sca != scale)
	{
		pos = position;
		rot = rotation;
		sca = scale;
		mbuff = XMMatrixScaling(scale.x, scale.y, scale.z);
		mrebuff = mbuff;
		mbuff = XMMatrixRotationX(rotation.x);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixRotationY(rotation.y);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixRotationZ(rotation.z);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixTranslation(position.x, position.y, position.z);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
	}
	XMFLOAT4 vbuff(data.x, data.y, data.z, 1.0f);
	XMVECTOR vvec = XMLoadFloat4(&vbuff);
	vvec=XMVector4Transform(vvec, mrebuff);
	XMStoreFloat4(&vbuff, vvec);
	return XMFLOAT3(vbuff.x, vbuff.y, vbuff.z);
}

XMMATRIX SpaceGameEngine::GetWorldMatrix(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
	static XMMATRIX mrebuff, mbuff;
	static XMFLOAT3 pos, rot, sca;
	if (pos != position || rot != rotation || sca != scale)
	{
		pos = position;
		rot = rotation;
		sca = scale;
		mbuff = XMMatrixScaling(scale.x, scale.y, scale.z);
		mrebuff = mbuff;
		mbuff = XMMatrixRotationX(rotation.x);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixRotationY(rotation.y);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixRotationZ(rotation.z);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
		mbuff = XMMatrixTranslation(position.x, position.y, position.z);
		mrebuff = XMMatrixMultiply(mrebuff, mbuff);
	}
	return mrebuff;
}
