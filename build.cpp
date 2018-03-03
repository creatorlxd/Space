#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <io.h>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

string path_format(const string &str)
{
	if (str.empty())
		return str;
	string re = str;
	if (re[re.size() - 1] == '\\')
		return re;
	else
	{
		re += "\\";
		return re;
	}
}

void search_copy(string path, string add, vector<string> filetype, string target)
{
	string str_buff = add;
	str_buff = path_format(str_buff);

	queue<string> paths;
	paths.push(str_buff);

	while (!paths.empty())
	{
		string path_buff = path_format(path) + path_format(paths.front()) + "*.*";
		string path_record = path_format(paths.front());
		paths.pop();

		_finddata_t buff;
		intptr_t handle;
		handle = _findfirst(path_buff.c_str(), &buff);
		if (handle == -1)
		{
			cout << path << endl;
			cout << "do not have correct file" << endl;
			return;
		}
		do
		{
			if (string(buff.name) != "." && string(buff.name) != "..")
			{

				if (buff.attrib & _A_SUBDIR && string(buff.name) != "." && string(buff.name) != "..")
				{
					paths.push(path_format(path_record) + string(buff.name));
					continue;
				}

				string filename(buff.name);
				int index = filename.find_last_of('.');
				for (const string& i : filetype)
				{
					if (index != -1 && (filename.size() - index - 1) == i.size())
					{
						if (filename.substr(index + 1, i.size()) == i)
						{
							system(string("xcopy /Y " + path_format(path) + path_format(path_record) + filename + " " + path_format(target) + path_format(path_record)).c_str());
							break;
						}
					}
				}
			}
		} while (_findnext(handle, &buff) == 0);

		_findclose(handle);
	}
}

int main(int argc, char const *argv[])
{
	string src, des, x86_debug_lib, x64_debug_lib,x86_release_lib,x64_release_lib;

	if (argc > 1)
		src = argv[1];
	else
		src = ".";

	if (argc > 2)
		des = argv[2];
	else
		des = ".//Build";

	if (argc > 3)
		x86_debug_lib = argv[3];
	else
		x86_debug_lib = src;
	
	if (argc > 4)
		x64_debug_lib = argv[4];
	else
		x64_debug_lib = src;

	if (argc > 5)
		x86_release_lib = argv[5];
	else
		x86_release_lib = src;

	if (argc > 6)
		x64_release_lib = argv[6];
	else
		x64_release_lib = src;
	//------------
	search_copy(src, "Source\\GameEngine", {"h","hpp","inl","hlsl","fx","lib"}, path_format(des) + "include");
	search_copy(x86_debug_lib, "", {"lib"}, path_format(des) + "lib\\x86\\debug");
	search_copy(x64_debug_lib, "", {"lib"}, path_format(des) + "lib\\x64\\debug");
	search_copy(x86_release_lib, "", {"lib"}, path_format(des) + "lib\\x86\\release");
	search_copy(x64_release_lib, "", {"lib"}, path_format(des) + "lib\\x64\\release");
	return 0;
}
