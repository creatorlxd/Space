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
#include "StringConverter.h"

SpaceGameEngine::WString SpaceGameEngine::StringToWString(const String& str)
{
	/*WString wstr;
	size_t size;
	wstr.resize(str.length());
	mbstowcs_s(&size, &wstr[0], wstr.size() + 1, str.c_str(), str.size());
	return wstr;*/

	WString wstr;
	size_t size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wstr.resize(size);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], size);
	wstr.erase(wstr.end() - 1);
	return wstr;
}

SpaceGameEngine::String SpaceGameEngine::WStringToString(const WString & wstr)
{
	/*String str;
	size_t size;
	str.resize(wstr.length());
	wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
	return str;*/

	String str;
	size_t size = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	str.resize(size);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], size, NULL, NULL);
	str.erase(str.end() - 1);
	return str;
}

SpaceGameEngine::TString SpaceGameEngine::StringToTString(const String& str)
{
#ifdef _UNICODE
	return StringToWString(str);
#else
	return str;
#endif
}

SpaceGameEngine::TString SpaceGameEngine::WStringToTString(const WString& wstr)
{
#ifdef _UNICODE
	return wstr;
#else
	return WStringToString(wstr);
#endif
}

SpaceGameEngine::String SpaceGameEngine::TStringToString(const SpaceGameEngine::TString & tstr)
{
#ifdef _UNICODE
	return WStringToString(tstr);
#else
	return tstr;
#endif
}

SpaceGameEngine::WString SpaceGameEngine::TStringToWString(const SpaceGameEngine::TString & tstr)
{
#ifdef _UNICODE
	return tstr;
#else
	return StringToWString(tstr);
#endif
}

std::string SpaceGameEngine::StringToStdString(const String & str)
{
	return std::string(str.c_str());
}

std::wstring SpaceGameEngine::WStringToStdWString(const WString & wstr)
{
	return std::wstring(wstr.c_str());
}

SpaceGameEngine::String SpaceGameEngine::StdStringToString(const std::string & str)
{
	return String(str.c_str());
}

SpaceGameEngine::WString SpaceGameEngine::StdWStringToWString(const std::wstring & str)
{
	return WString(str.c_str());
}
