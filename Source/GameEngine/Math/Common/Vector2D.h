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
#include "Def.h"

namespace SpaceGameEngine
{
	struct Vector2D :public XMFLOAT2
	{
		Vector2D(float x, float y);
		Vector2D(const XMFLOAT2& c);
		Vector2D(const Vector2D& v);
		Vector2D(FXMVECTOR v);

		bool operator = (const XMFLOAT2& c);
		bool operator = (const Vector2D& v);
		bool operator = (FXMVECTOR v);

		operator XMVECTOR();
	};
}