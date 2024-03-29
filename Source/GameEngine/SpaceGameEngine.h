﻿/*
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

//Common
#include "Common/Def.h"
#include "Common/MemoryManager/AllocatorForSTL.hpp"
#include "Common/Timer.h"
#include "Common/Error.h"
#include "Common/GlobalVariable.h"
#include "Common/File.h"
#include "Common/ConfigFile.h"
#include "Common/GUIDFactory.h"
#include "Common/CurrentObject.hpp"
#include "Common/Window.h"
#include "Common/MetaData/MetaData.h"
#include "Common/MetaData/Serialize.h"
#include "Common/MetaData/TextFileSerializeInterface.h"
#include "Common/MetaData/BinaryFileSerializeInterface.h"
#include "Common/UnitTestFramework.hpp"
#include "Common/Observer.hpp"

//Math
#include "Math/Common/ConstantValue.hpp"
#include "Math/Common/Vector2D.h"
#include "Math/Common/Vector3D.h"
#include "Math/Common/Vector4D.h"
#include "Math/Common/Matrix3D.h"
#include "Math/Common/Matrix4D.h"
#include "Math/BoundingBox/AxisAlignedBoundingBox.h"
#include "Math/Common/Triangle.h"

//Render
#include "Render/RenderInterface/RenderInterface.h"
#include "Render/RenderInterface/DX11/DX11RenderInterface.h"