#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(SpaceGameEngineTest)
	{
	public:
		TEST_METHOD(TestUnitTest)
		{
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(TestThrowError)
		{
			ThrowError("Test ThrowError");
		}

		TEST_METHOD(TestAsset)
		{
			MeshForModelFileAsset asset;
			asset.InitFromFile("./Source/UnitTest/TestData/test.model");
			Assert::AreEqual((int)asset.m_Vertices.size(), 8);
		}

		TEST_METHOD(TestAABB)
		{
			Vector<XMFLOAT3> pos =
			{ {1,1,1},
			{1,0,0},
			{1,0,1},
			{1,1,0},
			{0,0,0}
			};

			AABB aabb = GetAxisAlignedBoundingBox(pos);

			Assert::AreEqual(aabb==AABB({ 0,0,0 }, { 1, 1, 1 }),true);
		}
	};
}