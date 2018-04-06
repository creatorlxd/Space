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
#include "File.h"
#include "Error.h"

SpaceGameEngine::File::File()
{
	m_pFile = nullptr;
	m_FileMode = FileMode::None;
	m_IfFileReadOver = false;
}

SpaceGameEngine::File::~File()
{
	if (m_FileMode != FileMode::None)
		Close();
}

SpaceGameEngine::File::File(const String & filename, unsigned char mode)
{
	m_pFile = nullptr;
	m_FileMode = FileMode::None;
	m_IfFileReadOver = false;
	Open(filename, mode);
}

void SpaceGameEngine::File::Open(const String & filename, unsigned char mode)
{
	m_FileName = filename;
	m_FileMode = mode;
	String opt;
	if ((mode&FileMode::Append) != 0 && (mode&FileMode::Write) != 0)
	{
		opt = "a";
		if (mode&FileMode::Binary)
		{
			opt += "b";
		}
		if (mode&FileMode::Read)
		{
			opt += "+";
		}
		CheckAndCreateDirectory(filename);
		if (fopen_s(&m_pFile, filename.c_str(), opt.c_str()) != 0)
			THROWERROR("can not open file:" + filename);
	}
	else
	{
		if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) == 0)
		{
			opt = "r";
		}
		if ((mode&FileMode::Read) == 0 && (mode&FileMode::Write) != 0)
		{
			opt = "w";
		}
		if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) != 0)
		{
			opt = "r";
		}
		if ((mode&FileMode::Binary) != 0)
		{
			opt += "b";
		}
		if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) != 0)
		{
			opt += "+";
		}
		CheckAndCreateDirectory(filename);
		if (fopen_s(&m_pFile, filename.c_str(), opt.c_str()) != 0)
			THROWERROR("can not open file:" + filename);
	}
}

void SpaceGameEngine::File::Close()
{
	if (m_FileMode == FileMode::None)
		THROWERROR("can not Close a File without Open or has been closed");

	fclose(m_pFile);
	m_FileMode = FileMode::None;
	m_FileName.clear();
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetBeginPosition()
{
	FilePosition buff, re;
	fgetpos(m_pFile, &buff);
	fseek(m_pFile, 0, SEEK_SET);
	fgetpos(m_pFile, &re);
	fsetpos(m_pFile, &buff);
	return re;
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetEndPosition()
{
	FilePosition buff, re;
	fgetpos(m_pFile, &buff);
	fseek(m_pFile, 0L, SEEK_END);
	fgetpos(m_pFile, &re);
	fsetpos(m_pFile, &buff);
	return re;
}

SpaceGameEngine::FilePosition SpaceGameEngine::File::GetCurrentPosition()
{
	FilePosition re;
	fgetpos(m_pFile, &re);
	return re;
}

void SpaceGameEngine::File::SetFilePosition(FilePosition pos)
{
	fsetpos(m_pFile, &pos);
}

void SpaceGameEngine::File::Read(void * adr, size_t size)
{
	if (fread_s(adr, size, size, 1, m_pFile) == 0)
		m_IfFileReadOver = true;
	else
		m_IfFileReadOver = false;
}

void SpaceGameEngine::File::Write(const void * adr, size_t size)
{
	fwrite(adr, size, 1, m_pFile);
}

bool SpaceGameEngine::File::IfFileReadOver()
{
	return m_IfFileReadOver;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(wchar_t * cwstr)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		WString wstr;
		*this >> wstr;
		memcpy(cwstr, wstr.c_str(), sizeof(wchar_t)*wstr.size());
	}
	return *this;
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(WString & wstr)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		wstr.clear();
		wchar_t c = L' ';
		while (c == L' ' || c == L'\r' || c == L'\n')
		{
			c = fgetwc(m_pFile);
		}
		while (c != L' '&&c != EOF && c != L'\r'&&c != L'\n')
		{
			wstr += c;
			c = fgetwc(m_pFile);
		}
		if (wstr.empty())
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(wchar_t & wc)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, " \r\n\t%C", &wc, (unsigned int)sizeof(wchar_t)) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}
SpaceGameEngine::File & SpaceGameEngine::File::operator>>(char * cstr)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		String str;
		*this >> str;
		memcpy(cstr, str.c_str(), sizeof(char)*str.size());
	}
	return *this;
}

SpaceGameEngine::File& SpaceGameEngine::File::operator>>(String & str)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		str.clear();
		char c = ' ';
		while (c == ' ' || c == '\r' || c == '\n')
		{
			c = fgetc(m_pFile);
		}
		while (c != ' '&&c != EOF && c != '\r'&&c != '\n')
		{
			str += c;
			c = fgetc(m_pFile);
		}
		if (str.empty())
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(int & i)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%d", &i) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned int & ui)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%ud", &ui) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(short & s)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%hd", &s) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned short & us)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%hud", &us) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long & l)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%ld", &l) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned long & ul)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%uld", &ul) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long long & ll)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%I64d", &ll) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%I64ud", &ull) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(char & c)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, " \r\n\t%c", &c, (unsigned int)sizeof(char)) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(unsigned char & uc)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%hhu", &uc) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(float & f)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%f", &f) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(double & d)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%lf", &d) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator>>(long double & ld)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		if (fscanf_s(m_pFile, "%Lf", &ld) == EOF)
			m_IfFileReadOver = true;
		else
			m_IfFileReadOver = false;
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const wchar_t * wcstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		fprintf_s(m_pFile, "%S", wcstr);
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const WString & wstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		fprintf_s(m_pFile, "%S", wstr.c_str());
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const wchar_t & wc)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		fprintf_s(m_pFile, "%C", wc);
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const SpaceGameEngine::PrintMode & pm)
{
	if ((m_FileMode&FileMode::Write) != 0)
	{
		switch (pm)
		{
		case PrintMode::EndLine:
		{
			fprintf_s(m_pFile, "\n");
			fflush(m_pFile);
		}
		default:
			break;
		}
	}
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const char * cstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%s", cstr);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const String & str)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%s", str.c_str());
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const int & i)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%d", i);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned int & ui)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%ud", ui);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const short & s)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%hd", s);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned short & us)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%hud", us);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long & l)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%ld", l);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned long & ul)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%lud", ul);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long long & ll)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%I64d", ll);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%I64ud", ull);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const char & c)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%c", c);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const unsigned char & uc)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%hhu", uc);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const float & f)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%f", f);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const double & d)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%lf", d);
	return *this;
}

SpaceGameEngine::File & SpaceGameEngine::File::operator<<(const long double & ld)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFile, "%Lf", ld);
	return *this;
}

bool SpaceGameEngine::File::GetLine(String& str)
{
	if ((m_FileMode&FileMode::Read) != 0)
	{
		str.clear();
		char _char = std::fgetc(m_pFile);
		while (_char != EOF)
		{
			if (_char == '\r' || _char == '\n' || _char == '\r\n')
				break;
			str += _char;
			_char = std::fgetc(m_pFile);
		}

		if (_char == EOF)
		{
			m_IfFileReadOver = true;

			if (str.empty())
				return false;
		}
		return true;
	}
	else
		return false;
}

SpaceGameEngine::Vector<SpaceGameEngine::String> SpaceGameEngine::GetDirectoryName(const String & filepath)
{
	if (filepath.empty())
		return Vector<String>();

	Vector<String> re;
	String buffer;
	int index = 0;

	char c = ' ';
	while (c == ' ')
		c = filepath[index++];
	while (index <= filepath.length())
	{
		if (c != '/')
		{
			buffer += c;
		}
		else
		{
			re.push_back(buffer);
			buffer.clear();
		}
		c = filepath[(index++) % filepath.length()];
	}
	return re;
}

void SpaceGameEngine::CheckAndCreateDirectory(const String & str)
{
	auto folder = GetDirectoryName(str);
	String buffer;
	for (int i = 0; i<folder.size(); i++)
	{
		if (folder[i] == "." || folder[i] == "..")
		{
			buffer += folder[i] + "/";
		}
		else
		{
			buffer += folder[i] + "/";
			if (_access(buffer.c_str(), 0) == -1)
				_mkdir(buffer.c_str());
		}
	}
}