#pragma once
#include "ThirdParty\MyUnitTest\include\MyUnitTest.h"
#include "SpaceGameEngine.h"
#include "Game/Asset/Include/MaterialAsset.h"
#include "Game/Asset/Include/LightAsset.h"

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
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestLightAsset)
	{
		auto la = GetAssetByFileName<LightAsset>("../TestData/test.light");
		/*TestData:test.light
		0 0 0 0
		0.7 0.7 0.7 1
		0.7 0.7 0.7 8
		0 0 -10
		100
		0 0 1
		8
		0 1 0
		2
		*/
		Light l = la->m_Content;
		if (l.m_Ambient == XMFLOAT4(0, 0, 0, 0) && l.m_Diffuse == XMFLOAT4(0.7, 0.7, 0.7, 1) && l.m_Specular == XMFLOAT4(0.7, 0.7, 0.7, 8)
			&& l.m_Position == XMFLOAT3(0, 0, -10) && l.m_Range == (100) && l.m_Direction == XMFLOAT3(0, 0, 1)
			&& l.m_SpotLightOption == 8.0f&&l.m_LightOption == XMFLOAT3(0, 1, 0) && l.m_Type == 2)
			return UnitTestResult::Pass;
		else
			return UnitTestResult::Fail;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestVector)
	{
		try {
			int ti[8] = { 1,2,3,4,5,6,7,8 };
			Vector<int> vi(ti, ti + 8);
			for (auto i : vi)
			{
				cout << i << endl;
			}
		}
		catch (...)
		{
			return UnitTestResult::Fail;
		}
	}
	TEST_METHOD_END
}
TEST_GROUP_END