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
#include "ConfigFile.h"
#include "GlobalVariable.h"

namespace SpaceGameEngine
{
	/*!
	@brief 获取引擎的相对路径
	@note 该值由项目下的"systemconfig.configfile"中配置的相对路径"Engine::RootDirectory"决定
	*/
	const String& GetEngineRootDirectory();
}