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
#include "stdafx.h"
#include "../Include/StringConverter.h"

std::wstring SpaceGameEngine::StringToWString(const std::string& str)
{
	/*std::wstring wstr;
	size_t size;
	wstr.resize(str.length());
	mbstowcs_s(&size, &wstr[0], wstr.size() + 1, str.c_str(), str.size());
	return wstr;*/

	std::wstring wstr;
	size_t size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wstr.resize(size);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], size);
	wstr.erase(wstr.end() - 1);
	return wstr;
}

std::string SpaceGameEngine::WStringToString(const std::wstring & wstr)
{
	/*std::string str;
	size_t size;
	str.resize(wstr.length());
	wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
	return str;*/

	std::string str;
	size_t size = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	str.resize(size);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], size, NULL, NULL);
	str.erase(str.end() - 1);
	return str;
}

SpaceGameEngine::TString SpaceGameEngine::StringToTString(const std::string& str)
{
#ifdef _UNICODE
	return StringToWString(str);
#else
	return str;
#endif
}

SpaceGameEngine::TString SpaceGameEngine::WStringToTString(const std::wstring& wstr)
{
#ifdef _UNICODE
	return wstr;
#else
	return WStringToString(wstr);
#endif
}

std::string SpaceGameEngine::TStringToString(const SpaceGameEngine::TString & tstr)
{
#ifdef _UNICODE
	return WStringToString(tstr);
#else
	return tstr;
#endif
}

std::wstring SpaceGameEngine::TStringToWString(const SpaceGameEngine::TString & tstr)
{
#ifdef _UNICODE
	return tstr;
#else
	return StringToWString(tstr);
#endif
}
