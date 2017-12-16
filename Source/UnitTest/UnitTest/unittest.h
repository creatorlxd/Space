#pragma once
#include "ThirdParty\MyUnitTest\include\MyUnitTest.h"
#include "SpaceGameEngine.h"

#pragma comment(lib,"MyUnitTest.lib")
#pragma comment(lib,"Space~v1.0.lib")

using namespace MyUnitTest;

TEST_GROUP_BEGIN(SpaceGameEngineTest)
{
	TEST_METHOD_BEGIN(TestThrowError)
	{
		ThrowError("space game engine test");
	}
	TEST_METHOD_END
}
TEST_GROUP_END