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
#include <DirectXMath.h>
#include "Float.h"

using namespace DirectX;

namespace SpaceGameEngine
{
	struct Vector3D :public XMFLOAT3
	{
		Vector3D();
		Vector3D(float _x, float _y, float _z);
		Vector3D(const XMFLOAT3& c);
		Vector3D(const Vector3D& v);
		Vector3D(FXMVECTOR v);

		bool operator = (const XMFLOAT3& c);
		bool operator = (const Vector3D& v);
		bool operator = (FXMVECTOR v);

		operator XMVECTOR();
	};

	bool operator == (const Vector3D& v1, const Vector3D& v2);
	bool operator != (const Vector3D& v1, const Vector3D& v2);
}