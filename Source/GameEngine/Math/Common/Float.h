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
	GLOBAL_CONST float FloatEpsilon = 0.000001f;
	bool FloatEqual(float f1, float f2);

	bool FloatLess(float f1, float f2);

	bool FloatMore(float f1, float f2);

	bool FloatLessOrEqual(float f1, float f2);

	bool FloatMoreOrEqual(float f1, float f2);

	float FloatMin(float f1, float f2);

	float FloatMax(float f1, float f2);
}