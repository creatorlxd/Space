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
#include "../Include/SceneData.h"

using namespace SpaceGameEngine;

XMFLOAT4X4 SpaceGameEngine::SceneData::m_ViewMatrix;
XMFLOAT4X4 SpaceGameEngine::SceneData::m_ProjectionMatrix;

bool SpaceGameEngine::IfIntersectWithFrustum(const XMFLOAT3 & position)
{
	XMFLOAT4 vec(position.x, position.y, position.z, 1.0f);
	XMMATRIX mbuff = XMLoadFloat4x4(&SceneData::m_ViewMatrix);
	mbuff = mbuff*XMLoadFloat4x4(&SceneData::m_ProjectionMatrix);
	XMVECTOR vbuff = XMLoadFloat4(&vec);
	vbuff = XMVector4Transform(vbuff, mbuff);
	XMFLOAT4 pos_after;
	XMStoreFloat4(&pos_after, vbuff);
	vbuff = vbuff / pos_after.w;
	XMStoreFloat4(&pos_after, vbuff);
	if ((pos_after.x >= -1.0f&&pos_after.x <= 1.0f) &&
		(pos_after.y >= -1.0f&&pos_after.y <= 1.0f) &&
		(pos_after.z >= 0.0f&&pos_after.z <= 1.0f))
		return true;
	else
		return false;
}

XMFLOAT3 SpaceGameEngine::TransformByViewProjectionMatrix(const XMFLOAT3 & position)
{
	XMFLOAT4 vec(position.x, position.y, position.z, 1.0f);
	XMMATRIX mbuff = XMLoadFloat4x4(&SceneData::m_ViewMatrix);
	mbuff = mbuff*XMLoadFloat4x4(&SceneData::m_ProjectionMatrix);
	XMVECTOR vbuff = XMLoadFloat4(&vec);
	vbuff = XMVector4Transform(vbuff, mbuff);
	XMFLOAT4 pos_after;
	vbuff = vbuff / XMVectorGetW(vbuff);
	XMStoreFloat4(&pos_after, vbuff);
	return XMFLOAT3(pos_after.x, pos_after.y, pos_after.z);
}
