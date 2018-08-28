#include "unittest.h"

UNIT_TEST_METHOD(TestUnitTest, "Common")
{
	REQUIRE(1 == 1);
}

//UNIT_TEST_METHOD(TestUnitTestFail, "Common")
//{
//	REQUIRE(0 == 1);
//}

UNIT_TEST_MAIN;