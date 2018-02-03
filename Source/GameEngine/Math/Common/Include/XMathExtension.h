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
#pragma once
#include "stdafx.h"
#include "MathDefinition.h"

namespace SpaceGameEngine
{
	const float FloatEpsilon = 0.000001f;
	bool FloatEqual(float f1, float f2);

	bool FloatLess(float f1, float f2);

	bool FloatMore(float f1, float f2);

	bool FloatLessOrEqual(float f1, float f2);

	bool FloatMoreOrEqual(float f1, float f2);

	bool operator < (const XMFLOAT3& v1, const XMFLOAT3& v2);

	bool operator > (const XMFLOAT3& v1, const XMFLOAT3& v2);

	bool operator == (const XMFLOAT3& v1, const XMFLOAT3& v2);

	bool operator == (const XMFLOAT4& v1, const XMFLOAT4& v2);

	bool operator != (const XMFLOAT3& v1, const XMFLOAT3& v2);

	bool operator == (const XMFLOAT4X4& m1, const XMFLOAT4X4& m2);

	bool operator != (const XMFLOAT4X4& m1, const XMFLOAT4X4& m2);

	XMFLOAT3 Add(const XMFLOAT3& v1, const XMFLOAT3& v2);

	XMFLOAT3 Substract(const XMFLOAT3& v1, const XMFLOAT3& v2);

	XMFLOAT3 TransformByWorldMatrix(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale, XMFLOAT3 data);

	XMMATRIX GetWorldMatrix(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);

	XMFLOAT3 RotationVector(XMFLOAT3 rotation, XMFLOAT3 v);

	XMFLOAT3 GetDirectionByRotation(XMFLOAT3 rotation);

	XMMATRIX InverseTransposeMatrix(CXMMATRIX M);
}