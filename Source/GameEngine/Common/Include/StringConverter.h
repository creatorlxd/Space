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

	std::wstring StringToWString(const std::string str);
	std::string WStringToString(const std::wstring& wstr);

	TString StringToTString(const std::string str);
	TString WStringToTString(const std::wstring wstr);
	std::string TStringToString(const TString& tstr);
	std::wstring TStringToWString(const TString& tstr);
}