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
#include "StringConverter.h"

namespace SpaceGameEngine
{
	//TODO:报错后的处理
	void ThrowError(const TString& errormessage, const TString& filename, const TString& funcname, int line);		//报错
#ifndef _UNICODE
	void ThrowError(const WString& errormessage, const WString& filename, const WString& funcname, int line);
#else
	void ThrowError(const String& errormessage, const String& filename, const String& funcname, int line);
#endif

#define THROWERROR(str)\
SpaceGameEngine::ThrowError((str),__FILE__,__FUNCTION__,__LINE__)
#define THROWERRORW(wstr)\
SpaceGameEngine::ThrowError((wstr),__FILEW__,__FUNCTIONW__,__LINE__)
}