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
#include "Error.h"

void SpaceGameEngine::ThrowError(const TString & errormessage, const TString& filename, const TString& funcname, int line)
{
#ifdef _UNICODE
	auto line_str = StdWStringToWString(std::to_wstring(line));
#else
	auto line_str = StdStringToString(std::to_string(line));
#endif
	MessageBox(NULL, (_T("在") + filename + _T(":") + funcname + _T(":") + line_str + _T("中\n\t") + errormessage).c_str(), _T("Space Game Engine Error"), NULL);
#if defined(_DEBUG)|defined(DEBUG)	
	DebugBreak();
#endif
}
#ifndef _UNICODE
void SpaceGameEngine::ThrowError(const WString& errormessage, const WString& filename, const WString& funcname, int line)
{
	ThrowError(WStringToTString(errormessage), WStringToTString(filename), WStringToTString(funcname), line);
}
#else
void SpaceGameEngine::ThrowError(const String& errormessage, const String& filename, const String& funcname, int line)
{
	ThrowError(StringToTString(errormessage), StringToTString(filename), StringToTString(funcname), line);
}
#endif