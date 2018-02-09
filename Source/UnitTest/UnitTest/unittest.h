#pragma once
#include "ThirdParty\MyUnitTest\include\MyUnitTest.h"
#include "SpaceGameEngine.h"
#include "Game/Asset/Include/MaterialAsset.h"
#include "Game/Asset/Include/LightAsset.h"
#include "Math/Octree/Include/Octree.h"

#pragma comment(lib,"MyUnitTest.lib")
#pragma comment(lib,"Space.lib")

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
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestOctree)
	{
		Octree<XMFLOAT3, int> test;
		test.InsertData(std::make_pair(XMFLOAT3{ 1,1,1 }, 0));
		test.InsertData(std::make_pair(XMFLOAT3{ 0,0,0 }, 1));
		test.BuildTree();
		test.BuildTreeWithSpaceLimit({ {-5,-5,-5} ,{5,5,5} });
		test.DeleteData(1);
		auto tp = test.FindOctreeNode({ 0,0,0 });
		auto content = test.GetContent();
		for (auto i : content)
			cout << i << endl;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestXMVector)
	{
		XMFLOAT3 test{ 0,0,0 };
		XMVECTOR vbuff = XMLoadFloat3(&test);
		XMMATRIX mat = XMMatrixTranslation(1, 1, 1);
		vbuff = XMVector3Transform(vbuff, mat);
		XMStoreFloat3(&test, vbuff);
		/*cout << test.x << " " << test.y << " " << test.z << endl;*/
		XMFLOAT3 except{ 1,1,1 };
		if (test != except)
			return UnitTestResult::Fail;
	}
	TEST_METHOD_END
}
TEST_GROUP_END