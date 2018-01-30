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

bool SpaceGameEngine::operator == (const XMFLOAT4 & v1, const XMFLOAT4 & v2)
{
	return (v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z&&v1.w == v2.w);
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

XMFLOAT3 SpaceGameEngine::Add(const XMFLOAT3 & v1, const XMFLOAT3 & v2)
{
	XMVECTOR ve1, ve2;
	ve1 = XMLoadFloat3(&v1);
	ve2 = XMLoadFloat3(&v2);
	ve2 = ve1 + ve2;
	XMFLOAT3 re;
	XMStoreFloat3(&re, ve2);
	return re;
}

XMFLOAT3 SpaceGameEngine::Substract(const XMFLOAT3 & v1, const XMFLOAT3 & v2)
{
	XMVECTOR ve1, ve2;
	ve1 = XMLoadFloat3(&v1);
	ve2 = XMLoadFloat3(&v2);
	ve2 = ve1 - ve2;
	XMFLOAT3 re;
	XMStoreFloat3(&re, ve2);
	return re;
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

XMFLOAT3 SpaceGameEngine::GetDirectionByRotation(XMFLOAT3 rotation)
{
	XMFLOAT3 re;
	XMFLOAT3 unit_vector{ 0.0f,0.0f,1.0f };
	XMMATRIX rotationmat = XMMatrixRotationX(rotation.x)*XMMatrixRotationY(rotation.y)*XMMatrixRotationZ(rotation.z);
	XMVECTOR direction = XMLoadFloat3(&unit_vector);
	direction = XMVector3Transform(direction, rotationmat);
	direction = XMVector3Normalize(direction);
	XMStoreFloat3(&re, direction);
	return re;
}

XMMATRIX SpaceGameEngine::InverseTransposeMatrix(CXMMATRIX M)
{
	XMMATRIX A = M;
	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	XMVECTOR det = XMMatrixDeterminant(A);
	return XMMatrixTranspose(XMMatrixInverse(&det, A));
}
