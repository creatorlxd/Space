#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <Windows.h>
#include <algorithm>

using namespace std;

namespace MyUnitTest
{
	namespace SystemColorId
	{
		const short Blue = 1;
		const short Green = 2;
		const short LightBlue = 3;
		const short Red = 4;
		const short Purple = 5;
		const short Yellow = 6;
	}
	void SetColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);
	

	enum UnitTestResult
	{
		Unkown = 0,
		Pass = 1,
		Fail = -1
	};

	struct UnitTestMethod
	{
		UnitTestMethod();
		UnitTestMethod(const string& name, function<UnitTestResult()> action);

		string m_Name;
		function<UnitTestResult()> m_Content;
		static const function<UnitTestResult()> m_NullContent;
		UnitTestResult m_Result;
	};

	bool RunUnitTestMethod(UnitTestMethod& method);

#define TEST_METHOD(name,action)\
UnitTestMethod(#name,[&]()->UnitTestResult{{action}return UnitTestResult::Pass;})

#define TEST_METHOD_BEGIN(name)\
UnitTestMethod(#name,[&]()->UnitTestResult{{

#define TEST_METHOD_END }return UnitTestResult::Pass;})

	struct UnitTestGroup
	{
		string m_Name;
		vector<UnitTestMethod> m_Content;

		UnitTestGroup(const string& name, const vector<UnitTestMethod>& list);
	};

	bool RunUnitTestMethodInGroup(UnitTestGroup& group);
	bool RunUnitTestMethodInGroup(const string& name, UnitTestGroup& group);

#define TEST_GROUP(name,content)\
UnitTestGroup(#name,content);

#define TEST_GROUP_BEGIN(name)\
UnitTestGroup name(#name,{

#define TEST_GROUP_END });

	class UnitTestManager
	{
	public:
		void AddUnitTestGroup(const UnitTestGroup& group);
		void ListUnitTest();
		void RunAllUnitTest();
		void RunUnitTestMethod(const string& group_name,const string& name="");
	private:
		unordered_map<string, UnitTestGroup> m_Content;
	};

	inline void TestFailedWithNoMethod();

	inline void TestSuccess();

	UnitTestManager& GetUnitTestManager();

	void RunUnitTestManager();
}