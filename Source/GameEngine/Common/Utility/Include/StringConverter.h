/*
Copyright 2017 creatorlxd

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

namespace SpaceGameEngine
{
#ifdef _UNICODE
#define tcin std::wcin
#define tfstream std::wfstream
using TString = std::wstring;
#else
#define tcin std::cin
#define tfstream std::fstream
using TString = std::string;
#endif

	std::wstring StringToWString(const std::string& str);
	std::string WStringToString(const std::wstring& wstr);

	TString StringToTString(const std::string& str);
	TString WStringToTString(const std::wstring& wstr);
	std::string TStringToString(const TString& tstr);
	std::wstring TStringToWString(const TString& tstr);
}