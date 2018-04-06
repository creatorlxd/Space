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
#include "MemoryManager/AllocatorForSTL.hpp"

namespace SpaceGameEngine
{
#ifdef _UNICODE
#define tcin std::wcin
#define tfstream std::wfstream
	using TString = WString;
#else
#define tcin std::cin
#define tfstream std::fstream
	using TString = String;
#endif

	WString StringToWString(const String& str);
	String WStringToString(const WString& wstr);

	TString StringToTString(const String& str);
	TString WStringToTString(const WString& wstr);
	String TStringToString(const TString& tstr);
	WString TStringToWString(const TString& tstr);

	std::string StringToStdString(const String& str);
	std::wstring WStringToStdWString(const WString& wstr);
	String StdStringToString(const std::string& str);
	WString StdWStringToWString(const std::wstring& str);
}