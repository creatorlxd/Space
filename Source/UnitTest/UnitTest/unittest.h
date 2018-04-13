#pragma once
#include "ThirdParty\MyUnitTest\include\MyUnitTest.h"
#include "SpaceGameEngine.h"

#pragma comment(lib,"MyUnitTest.lib")
#pragma comment(lib,"Space.lib")

using namespace MyUnitTest;
using namespace SpaceGameEngine;

class TestData;

template<>
class Connection<TestData> :public ConnectionCore<TestData>
{
public:
	OnNotifyAction<> OnNotifyTest;
	OnNotifyAction<> OnNotifyTest2;
	CONNECTION_CONSTRUCTOR(TestData, OnNotifyTest(*this), OnNotifyTest2(*this));
};

class TestData :public Data<TestData>
{
public:
	int a;
	void run()
	{
		DATA_NOTIFY(OnNotifyTest,());
	}
};

TEST_GROUP_BEGIN(CommonTest)
{
	TEST_METHOD_BEGIN(TestTimer)
	{
		Timer test_timer;
		test_timer.Init();
		Sleep(1000);
		test_timer.Tick();
		std::cout << test_timer.GetTotalTime() << std::endl;
		test_timer.Tick();
		std::cout << test_timer.GetDeltaTime() << std::endl;

		test_timer.Stop();
		Sleep(1500);
		test_timer.Start();
		std::cout << test_timer.GetPausedTime() << std::endl;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestCurrent)
	{
		class TestClass:public CurrentObject<TestClass>
		{
		public:
			TestClass() :CurrentObject<TestClass>(this) {}
			int test;
		};
		TestClass tc;
		auto pcurrent = TestClass::GetCurrentObject();
		if (&tc == pcurrent)
			return UnitTestResult::Pass;
		else
			return UnitTestResult::Fail;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestConfigFile)
	{
		ConfigFile cf;
		cf.InitFromFile("../TestData/test.configfile");
		cout << cf.GetConfigTable("test").GetConfigValue("a").AsInt() << endl;
		cout << cf.GetConfigTable("test").GetConfigValue("b").AsInt() << endl;
		cout << cf.GetConfigTable("test").GetConfigValue("str").AsString() << endl;
		cout << cf.GetConfigTable("test").GetConfigValue("float").AsFloat() << endl;
		cout << cf.GetConfigTable("test").GetConfigValue("double").AsDouble() << endl;
		cout << cf.GetConfigTable("test").GetConfigValue("char").AsChar() << endl;
		cout << cf.GetConfigTable("test2").GetConfigValue("a").AsDouble() << endl;
		cout << cf.GetConfigTable("test2").GetConfigValue("str").AsString() << endl;
		cout << boolalpha << cf.GetConfigTable("test2").GetConfigValue("testbool").AsBool() << endl;
		cf.GetConfigTable("test2").GetConfigValue("testbool").Set(false);

		cf.GetConfigTable("test").GetConfigValue("float").Set(1.23f);
		cf.SaveToFile("../TestData/test2.configfile");
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestDAC)
	{
		TestData test;
		Connection<TestData> pc(&test);
		pc.OnNotifyTest = []() {cout << "test notify1" << endl; };
		test.run();
		test.NotifyConnection();
	}
	TEST_METHOD_END
}
TEST_GROUP_END