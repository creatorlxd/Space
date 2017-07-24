#include "stdafx.h"
#include "Space.h"
using namespace SpaceGameEngine;

tstring SpaceGameEngine::StringToTString(const std::string & str)
{
	tstring tstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), tstr.begin());
	return tstr;
}

std::string SpaceGameEngine::TStringToString(const tstring & tstr)
{
	std::string str;
	for (auto i : tstr)
	{
		str += i;
	}
	return str;
}

float SpaceGameEngine::GetDeltaTime()
{
	static float TimeNow=0.00f;
	static float TimeBuffer = 0.00f;
	static float DeltaTime = 0.00f;
	if (TimeNow == 0.00f)
	{
		TimeNow = timeGetTime()*0.001f;
		return SpaceGameEngine::GetDeltaTime();
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		DeltaTime = TimeBuffer - TimeNow;
		TimeNow = timeGetTime()*0.001f;
		return DeltaTime;
	}
}

void SpaceGameEngine::ThrowError(const tstring & errormessege)
{
	MessageBox(NULL, errormessege.c_str(), L"Space Game Engine", NULL);
}

std::vector<std::pair<std::string, std::string> > SpaceGameEngine::ReadAssetListFromFile(const std::string & filename)
{
	std::vector<std::pair<std::string, std::string> > re;
	std::fstream file(filename, std::ios::in);
	std::string componentname, assetname;

	while (file >> componentname >> assetname)
	{
		re.push_back(make_pair(componentname, assetname));
	}
	file.close();

	return re;
}
