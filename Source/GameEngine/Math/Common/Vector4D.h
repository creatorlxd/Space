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
	struct Vector4D :public XMFLOAT4
	{
		Vector4D();
		Vector4D(float _x, float _y, float _z, float _w);
		Vector4D(const XMFLOAT4& c);
		Vector4D(const Vector4D& v);
		Vector4D(FXMVECTOR v);

		Vector4D& operator = (const XMFLOAT4& c);
		Vector4D& operator = (const Vector4D& v);
		Vector4D& operator = (FXMVECTOR v);

		operator XMVECTOR() const;
	};

	bool operator == (const Vector4D& v1, const Vector4D& v2);
	bool operator != (const Vector4D& v1, const Vector4D& v2);
}