#include "unittest.h"

UNIT_TEST_METHOD(TestUnitTest, "Common")
{
	REQUIRE(1 == 1);
	UNIT_TEST_SUCCESS;
}

//UNIT_TEST_METHOD(TestUnitTestFail, "Common")
//{
//	REQUIRE(0 == 1);
//	UNIT_TEST_SUCCESS;
//}

//UNIT_TEST_METHOD(TestThrowError, "Common")
//{
//	THROW_ERROR("test throw error");
//	UNIT_TEST_SUCCESS;
//}

class TestSubject;

OBSERVER_RESPOND_LIST_BEGIN(TestSubject)
	RespondFunction<> m_RespondTest;
OBSERVER_RESPOND_LIST_END;

class TestSubject :public SpaceGameEngine::Subject<TestSubject>
{
public:
	void Test()
	{
		SUBJECT_NOTIFY(TestSubject, m_RespondTest);
	}
};

UNIT_TEST_METHOD(TestObserver, "Common")
{
	int test_a = 0;
	int test_b = 0;
	TestSubject* ptestsubject = new TestSubject;
	SpaceGameEngine::Observer<TestSubject> testob(ptestsubject);
	SpaceGameEngine::Observer<TestSubject>* ptestob = new SpaceGameEngine::Observer<TestSubject>(ptestsubject);
	testob.m_RespondSubjectRelease = [&test_a]()->void {
		test_a = 1;
	};
	ptestob->m_RespondTest = [&]()->void {
		test_b = 1;
	};
	ptestsubject->Test();
	REQUIRE(testob.GetSubject());
	delete ptestob;
	delete ptestsubject;
	REQUIRE(testob.GetSubject() == nullptr);
	REQUIRE(test_a == 1);
	REQUIRE(test_b == 1);
	UNIT_TEST_SUCCESS;
}

UNIT_TEST_MAIN;