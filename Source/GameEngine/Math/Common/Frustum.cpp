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
#include "Frustum.h"

SpaceGameEngine::Frustum SpaceGameEngine::GetFrustumFromMatrix(const Matrix4D & matrix)
{
	Frustum re;
	re.m_LeftPlane = Plane(Vector3D(matrix._14 + matrix._11, matrix._24 + matrix._21, matrix._34 + matrix._31), matrix._44 + matrix._41);
	re.m_RightPlane = Plane(Vector3D(matrix._14 - matrix._11, matrix._24 - matrix._21, matrix._34 - matrix._31), matrix._44 - matrix._41);
	re.m_BottomPlane = Plane(Vector3D(matrix._14 + matrix._12, matrix._24 + matrix._22, matrix._34 + matrix._32), matrix._44 + matrix._42);
	re.m_TopPlane = Plane(Vector3D(matrix._14 - matrix._12, matrix._24 - matrix._22, matrix._34 - matrix._32), matrix._44 - matrix._42);
	re.m_NearPlane = Plane(Vector3D(matrix._13, matrix._23, matrix._33), matrix._43);
	re.m_FarPlane = Plane(Vector3D(matrix._14 - matrix._13, matrix._24 - matrix._23, matrix._34 - matrix._33), matrix._44 - matrix._43);
	return re;
}
