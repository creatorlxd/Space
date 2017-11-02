#include "stdafx.h"
#include "../Include/StringConverter.h"

std::wstring SpaceGameEngine::StringToWString(const std::string str)
{
	std::wstring wstr;
	size_t size;
	wstr.resize(str.length());
	mbstowcs_s(&size, &wstr[0], wstr.size() + 1, str.c_str(), str.size());
	return wstr;
}

std::string SpaceGameEngine::WStringToString(const std::wstring & wstr)
{
	std::string str;
	size_t size;
	str.resize(wstr.length());
	wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
	return str;
}

SpaceGameEngine::TString SpaceGameEngine::StringToTString(const std::string str)
{
#ifdef _UNICODE
	return StringToWString(str);
#else
	return str;
#endif
}

SpaceGameEngine::TString SpaceGameEngine::WStringToTString(const std::wstring wstr)
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
