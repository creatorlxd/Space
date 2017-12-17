#pragma once
#include "ThirdParty\MyUnitTest\include\MyUnitTest.h"
#include "SpaceGameEngine.h"
#include "Game/Asset/Include/MaterialAsset.h"

#pragma comment(lib,"MyUnitTest.lib")
#pragma comment(lib,"Space~v1.0.lib")

using namespace MyUnitTest;

TEST_GROUP_BEGIN(SpaceGameEngineTest)
{
	TEST_METHOD_BEGIN(TestThrowError)
	{
		ThrowError("space game engine test");
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestMaterialAsset)
	{
		auto ma = GetAssetByFileName<MaterialAsset>("../TestData/test.material");
		/*TestData:test.material
		0 0 0 0
		0.7 0.7 0.7 1
		0.7 0.7 0.7 8
		*/
		Material m = ma->m_Content;
		if (m.m_Ambient == XMFLOAT4(0, 0, 0, 0) && m.m_Diffuse == XMFLOAT4(0.7, 0.7, 0.7, 1) && m.m_Specular == XMFLOAT4(0.7, 0.7, 0.7, 8))
			return UnitTestResult::Pass;
		else
			return UnitTestResult::Fail;
	}
	TEST_METHOD_END
}
TEST_GROUP_END