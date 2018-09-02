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
#include "Plane.h"

SpaceGameEngine::Plane::Plane()
	:m_Direction(0, 0, 0), m_Distance(0)
{
}

SpaceGameEngine::Plane::Plane(Vector3D dir, float d)
	:m_Direction(dir), m_Distance(d)
{
}

SpaceGameEngine::Plane::Plane(Vector4D c)
	: m_Direction(c.x, c.y, c.z), m_Distance(c.w)
{
}

SpaceGameEngine::Plane::Plane(Vector3D v1, Vector3D v2, Vector3D v3)
{
	m_Direction = XMVector3Cross((v2 - v1), (v3 - v2));
	m_Distance = -1.00f*Vector4D(XMVector3Dot(m_Direction, v1)).x;
}

bool SpaceGameEngine::IfBehindPlane(const Plane & plane, const Vector3D & position)
{
	XMVECTOR vbuff = XMVector3Dot(plane.m_Direction, position);
	float dt = XMVectorGetX(vbuff);
	if (FloatLess(dt + plane.m_Distance, 0.00f))
		return true;
	else
		return false;
}

bool SpaceGameEngine::IfBeFrontOfPlane(const Plane & plane, const Vector3D & position)
{
	XMVECTOR vbuff = XMVector3Dot(plane.m_Direction, position);
	float dt = XMVectorGetX(vbuff);
	if (FloatMore(dt + plane.m_Distance, 0.00f))
		return true;
	else
		return false;
}

SpaceGameEngine::Plane SpaceGameEngine::NormalizePlane(const Plane & plane)
{
	Vector4D buff = XMVectorDivide(Vector4D(plane.m_Direction.x, plane.m_Direction.y, plane.m_Direction.z, plane.m_Distance), XMVector3Length(plane.m_Direction));
	return Plane(buff);
}