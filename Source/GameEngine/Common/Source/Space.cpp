#include "stdafx.h"
#include "Space.h"

tstring StringToTString(const std::string & str)
{
	tstring tstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), tstr.begin());
	return tstr;
}

std::string TStringToString(const tstring & tstr)
{
	std::string str;
	for (auto i : tstr)
	{
		str += i;
	}
	return str;
}

float GetDeltaTime()
{
	static float TimeNow=0.00f;
	static float TimeBuffer = 0.00f;
	static float DeltaTime = 0.00f;
	if (TimeNow == 0.00f)
	{
		TimeNow = timeGetTime()*0.001f;
		return GetDeltaTime();
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		DeltaTime = TimeBuffer - TimeNow;
		TimeNow = timeGetTime()*0.001f;
		return DeltaTime;
	}
}

void ThrowError(const tstring & errormessege)
{
	MessageBox(NULL, errormessege.c_str(), L"Space Game Engine", NULL);
}

std::vector<std::pair<std::string, std::string> > ReadAssetListFromFile(const std::string & filename)
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
