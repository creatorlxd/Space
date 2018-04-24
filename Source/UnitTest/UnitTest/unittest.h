#pragma once
#include "ThirdParty\MyUnitTest\include\MyUnitTest.h"
#include "SpaceGameEngine.h"

#pragma comment(lib,"MyUnitTest.lib")
#pragma comment(lib,"Space.lib")

using namespace MyUnitTest;
using namespace SpaceGameEngine;

struct test_md
{
public:
	test_md(int _a, int _b, int _c) :
		a(_a), b(_b), c(_c) {}
	test_md() :test_md(0, 0, 0) {}
	int a, b, c;
	METADATA_BEGIN(test_md)
		MEMBER_VAR_BEGIN
			MEMBER_VAR(test_md, int, a, false),
			MEMBER_VAR(test_md, int, b),
			MEMBER_VAR(test_md, int, c)
		MEMBER_VAR_END
		METADATA_FUNCTION(test_md)
		INHERITANCE_BEGIN
		INHERITANCE_END
	METADATA_END(test_md); 
	test_md& operator = (const test_md& tg)
	{
		COPY_BY_METADATA(test_md, *this, tg);
		/*auto& re = const_cast<test_md&>(*this);
		CopyByMetaData(re, tg);*/
		return *this;
	}
};

class test_md2:public test_md
{
	test_md2& operator = (const test_md2& tm)
	{
		test_md::operator=(tm);
		return *this;
	}
};

class TestData;

CONNECTION_BEGIN(TestData)
	OnNotifyAction<void()> m_OnNotifyTest;
CONNECTION_END;

class TestData :public Data<TestData>
{
public:
	int a;
	void run()
	{
		DATA_NOTIFY(Data<TestData>, m_OnNotifyTest);
	}
};

class TestData2;

CONNECTION_BEGIN(TestData2)
	OnNotifyAction<void(int, float)> m_OnNotifyTest2;
CONNECTION_END;

class TestData2 :public TestData, public Data<TestData2>
{
public:
	void run()
	{
		DATA_NOTIFY(Data<TestData>, m_OnNotifyTest);
		DATA_NOTIFY(Data<TestData2>, m_OnNotifyTest2,0,0.0f);
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
		pc.m_OnNotifyTest = []() {cout << "test on notify" << endl; };
		test.run();
		TestData2 test2;
		Connection<TestData> pc2_1(&test2);
		Connection<TestData2> pc2_2(&test2);
		pc2_1.m_OnNotifyTest = []() {cout << "test on notify ---pc2_1" << endl; };
		pc2_2.m_OnNotifyTest2 = [](int i, float f) {cout << i << " " << f << endl; };
		test2.run();
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestMetaData)
	{
		auto meta = GetMetaData<string>();
		auto ptr1 = ConstructByTypeName(GetTypeName<string>()).Cast<string>();
		auto ptr2 = ConstructByTypeName(GetTypeName<string>()).Cast<string>();
		*ptr1 = "test";
		CopyByTypeName(GetTypeName<string>(),CastToMetaObject(ptr2), CastToMetaObject(ptr1));
		MemoryManager::Delete(ptr1);
		MemoryManager::Delete(ptr2);
		auto meta2 = test_md::GetMetaDataCore();
		test_md t1, t2(1,2,3);
		auto meta3 = t1.sm_MetaData;
		CopyByMetaObject(t1.CastToMetaObject(), t2.CastToMetaObject());
	}
	TEST_METHOD_END
}
TEST_GROUP_END