#pragma once
#include "ThirdParty\MyUnitTest\include\MyUnitTest.h"
#include "SpaceGameEngine.h"

#define REQUIRE(x) \
if(!(x)) \
{ \
	std::cout<<"in file:"<<__FILE__<<" in function:"<<__FUNCTION__<<" in line: "<<__LINE__<<" unit test require error"<<std::endl;\
	return UnitTestResult::Fail;\
}

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
	META_DATA_BEGIN(test_md)
		MEMBER_VAR_BEGIN
			MEMBER_VAR(test_md, int, a, false),
			MEMBER_VAR(test_md, int, b),
			MEMBER_VAR(test_md, int, c, true, false)
		MEMBER_VAR_END
		META_DATA_FUNCTION(test_md)
		INHERITANCE_BEGIN
		INHERITANCE_END
	META_DATA_END(test_md); 
	test_md& operator = (const test_md& tg)
	{
		CopyByMetaData(*this, tg);
		return *this;
	}
};

class test_md2
{
public:
	test_md2& operator = (const test_md2& tm)
	{
		CopyByMetaData(*this, tm);
		return *this;
	}
	test_md2()
	{
		pa = nullptr;
	}
	int* pa;
	META_DATA_BEGIN(test_md2)
		MEMBER_VAR_BEGIN
		MEMBER_VAR(test_md2,int*,pa)
		MEMBER_VAR_END
		META_DATA_FUNCTION(test_md2)
		INHERITANCE_BEGIN
		INHERITANCE_END
	META_DATA_END(test_md2);
};

struct test_md3 :public test_md2, public test_md
{
public:
	META_DATA_BEGIN(test_md3)
		MEMBER_VAR_BEGIN
		MEMBER_VAR_END
		META_DATA_FUNCTION(test_md3)
		INHERITANCE_BEGIN
		INHERITANCE(test_md3,test_md2),
		INHERITANCE(test_md3,test_md)
		INHERITANCE_END
	META_DATA_END(test_md3);
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
		REQUIRE(cf.GetConfigTable("test").GetConfigValue("a").AsInt()==2);
		REQUIRE(cf.GetConfigTable("test").GetConfigValue("b").AsInt()==3);
		REQUIRE(cf.GetConfigTable("test").GetConfigValue("str").AsString()=="test str");
		REQUIRE(cf.GetConfigTable("test").GetConfigValue("float").AsFloat()==1.3f);
		REQUIRE(cf.GetConfigTable("test").GetConfigValue("double").AsDouble()==3.1415926);
		REQUIRE(cf.GetConfigTable("test").GetConfigValue("char").AsChar()=='c');
		REQUIRE(cf.GetConfigTable("test2").GetConfigValue("a").AsDouble()==2.3);
		REQUIRE(cf.GetConfigTable("test2").GetConfigValue("str").AsString()=="");
		REQUIRE(cf.GetConfigTable("test2").GetConfigValue("testbool").AsBool()==true);
		REQUIRE(cf.GetConfigTable("test2").GetConfigValue("str2").AsString()=="test;");
		REQUIRE(cf.GetConfigTable("test2").GetConfigValue("char").AsChar()==';');

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
		auto meta = GetMetaData<String>();
		auto ptr1 = ConstructByTypeName(GetTypeName<String>()).Cast<String>();
		auto ptr2 = ConstructByTypeName(GetTypeName<String>()).Cast<String>();
		*ptr1 = "test";
		CopyByMetaObject(MetaObject(ptr2), MetaObject(ptr1));
		auto meta2 = test_md::GetMetaDataCore();
		test_md t1, t2(1,2,3);
		auto meta3 = GetMetaData<test_md2>();
		auto meta4 = GetMetaData<test_md3>();
		CopyByMetaObject(t1.CastToMetaObject(), t2.CastToMetaObject());
		auto ptr3 = ConstructByTypeName(GetTypeName<test_md3>()).Cast<test_md3>();
		auto ptr4 = (test_md*)ptr3;
		auto ptr5 = GetMetaData<test_md3>().m_DirectInheritanceRelation.find(GetTypeName<test_md>())->second.CastToMetaObject(ptr3->CastToMetaObject());
		MemoryManager::Delete(ptr1);
		MemoryManager::Delete(ptr2);
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestSerialize)
	{
		{
			test_md3 tmd3_n1;
			tmd3_n1.a = 3;
			tmd3_n1.b = 2;
			tmd3_n1.c = 1;
			test_md3 tmd3;
			tmd3.a = 1;
			tmd3.b = 2;
			tmd3.c = 3;
			tmd3.pa = &tmd3_n1.a;
			TextFileSerializeInterface tfsi_o("../TestData/test_serialize.txt", SerializeInterface::IOFlag::Output);
			TextFileSerializeInterface tfsi_o2("../TestData/test_serialize2.txt", SerializeInterface::IOFlag::Output);
			Serialize(tmd3_n1, tfsi_o2);
			Serialize(tmd3, tfsi_o);
			String str = "test\ntest";
			GetMetaDataManager().GetMetaData(GetTypeName<String>())->m_SerializeAction(MetaObject(&str), tfsi_o);
			const Vector<int> test_vec{ 4,5,6 };
			GetMetaDataManager().GetMetaData(GetTypeName<Vector<int>>())->m_SerializeAction(MetaObject(&test_vec), tfsi_o);
			Map<String, int> test_map{ {"1",1},{"2",2} };
			Serialize(test_map, tfsi_o);
			HashMap<String, int> test_hashmap{ { "3",3 },{ "4",4 } };
			Serialize(test_hashmap, tfsi_o);
			Deque<int> test_deque{ 1,2,3,4,5,6 };
			Serialize(test_deque, tfsi_o);
			Queue<int> test_queue;
			test_queue.push(5);
			test_queue.push(4);
			test_queue.push(3);
			test_queue.push(2);
			test_queue.push(1);
			GetMetaDataManager().GetMetaData(GetTypeName<Queue<int>>())->m_SerializeAction(MetaObject(&test_queue), tfsi_o);
			Stack<char> test_stack;
			test_stack.push('a');
			test_stack.push('b');
			test_stack.push('c');
			Serialize(test_stack, tfsi_o);
			List<float> test_list{ 1.0f,2.0f,3.0f };
			Serialize(test_list, tfsi_o);
			ForwardList<bool> test_forward_list{ true,false,true };
			Serialize(test_forward_list, tfsi_o);
			Set<double> test_set{ 11,12,13 };
			Serialize(test_set, tfsi_o);
			int** ppa = &tmd3.pa;
			Serialize(ppa, tfsi_o2);
		}
		{
			test_md3 tmd3_n1, tmd3_1;
			TextFileSerializeInterface tfsi_i("../TestData/test_serialize.txt", SerializeInterface::IOFlag::Input);
			TextFileSerializeInterface tfsi_i2("../TestData/test_serialize2.txt", SerializeInterface::IOFlag::Input);
			Serialize(tmd3_1, tfsi_i);
			Serialize(tmd3_n1, tfsi_i2);
			auto ptmd_int = &tmd3_n1.a;
			String str;
			GetMetaDataManager().GetMetaData(GetTypeName<String>())->m_SerializeAction(MetaObject(&str), tfsi_i);
			Vector<int> test_vec;
			GetMetaDataManager().GetMetaData(GetTypeName<Vector<int>>())->m_SerializeAction(MetaObject(&test_vec), tfsi_i);
			Map<String, int> test_map;
			Serialize(test_map, tfsi_i);
			HashMap<String, int> test_hashmap;
			Serialize(test_hashmap, tfsi_i);
			Deque<int> test_deque;
			Serialize(test_deque, tfsi_i);
			Queue<int> test_queue;
			GetMetaDataManager().GetMetaData(GetTypeName<Queue<int>>())->m_SerializeAction(MetaObject(&test_queue), tfsi_i);
			Stack<char> test_stack;
			Serialize(test_stack, tfsi_i);
			auto test_stack_top = test_stack.top();
			List<float> test_list;
			Serialize(test_list, tfsi_i);
			ForwardList<bool> test_forward_list;
			Serialize(test_forward_list, tfsi_i);
			Set<double> test_set;
			Serialize(test_set, tfsi_i);
			int** ppa;
			int** ppa_2 = &tmd3_1.pa;
			Serialize(ppa, tfsi_i2);
		}
		{
			test_md3 tmd3_n1;
			tmd3_n1.a = 3;
			tmd3_n1.b = 2;
			tmd3_n1.c = 1;
			test_md3 tmd3;
			tmd3.a = 1;
			tmd3.b = 2;
			tmd3.c = 3;
			tmd3.pa = &tmd3_n1.a;
			BinaryFileSerializeInterface bfsi_o("../TestData/test_serialize.bin", SerializeInterface::IOFlag::Output);
			BinaryFileSerializeInterface bfsi_o2("../TestData/test_serialize2.bin", SerializeInterface::IOFlag::Output);
			Serialize(tmd3_n1, bfsi_o2);
			Serialize(tmd3, bfsi_o);
			String str = "test\ntest";
			GetMetaDataManager().GetMetaData(GetTypeName<String>())->m_SerializeAction(MetaObject(&str), bfsi_o);
			const Vector<int> test_vec{ 4,5,6 };
			GetMetaDataManager().GetMetaData(GetTypeName<Vector<int>>())->m_SerializeAction(MetaObject(&test_vec), bfsi_o);
			Map<String, int> test_map{ { "1",1 },{ "2",2 } };
			Serialize(test_map, bfsi_o);
			HashMap<String, int> test_hashmap{ { "3",3 },{ "4",4 } };
			Serialize(test_hashmap, bfsi_o);
			Deque<int> test_deque{ 1,2,3,4,5,6 };
			Serialize(test_deque, bfsi_o);
			Queue<int> test_queue;
			test_queue.push(5);
			test_queue.push(4);
			test_queue.push(3);
			test_queue.push(2);
			test_queue.push(1);
			GetMetaDataManager().GetMetaData(GetTypeName<Queue<int>>())->m_SerializeAction(MetaObject(&test_queue), bfsi_o);
			Stack<char> test_stack;
			test_stack.push('a');
			test_stack.push('b');
			test_stack.push('c');
			Serialize(test_stack, bfsi_o);
			List<float> test_list{ 1.0f,2.0f,3.0f };
			Serialize(test_list, bfsi_o);
			ForwardList<bool> test_forward_list{ true,false,true };
			Serialize(test_forward_list, bfsi_o);
			Set<double> test_set{ 11,12,13 };
			Serialize(test_set, bfsi_o);
			int** ppa = &tmd3.pa;
			Serialize(ppa, bfsi_o2);
		}
		{
			test_md3 tmd3_n1, tmd3_1;
			BinaryFileSerializeInterface bfsi_i("../TestData/test_serialize.bin", SerializeInterface::IOFlag::Input);
			BinaryFileSerializeInterface bfsi_i2("../TestData/test_serialize2.bin", SerializeInterface::IOFlag::Input);
			Serialize(tmd3_1, bfsi_i);
			Serialize(tmd3_n1, bfsi_i2);
			auto ptmd_int = &tmd3_n1.a;
			String str;
			GetMetaDataManager().GetMetaData(GetTypeName<String>())->m_SerializeAction(MetaObject(&str), bfsi_i);
			Vector<int> test_vec;
			GetMetaDataManager().GetMetaData(GetTypeName<Vector<int>>())->m_SerializeAction(MetaObject(&test_vec), bfsi_i);
			Map<String, int> test_map;
			Serialize(test_map, bfsi_i);
			HashMap<String, int> test_hashmap;
			Serialize(test_hashmap, bfsi_i);
			Deque<int> test_deque;
			Serialize(test_deque, bfsi_i);
			Queue<int> test_queue;
			GetMetaDataManager().GetMetaData(GetTypeName<Queue<int>>())->m_SerializeAction(MetaObject(&test_queue), bfsi_i);
			Stack<char> test_stack;
			Serialize(test_stack, bfsi_i);
			auto test_stack_top = test_stack.top();
			List<float> test_list;
			Serialize(test_list, bfsi_i);
			ForwardList<bool> test_forward_list;
			Serialize(test_forward_list, bfsi_i);
			Set<double> test_set;
			Serialize(test_set, bfsi_i);
			int** ppa;
			int** ppa_2 = &tmd3_1.pa;
			Serialize(ppa, bfsi_i2);
		}
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestWindow)
	{
		Window test_window;
		test_window.SetWindowTitle("TestWindow");
		test_window.SetWindowSize(800, 600);
		test_window.StartRun(GetModuleHandle(0));
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestFile)
	{
		File file;
		file.Open("../TestData/testfile.txt", FileMode::Read);
		char c;
		file >> c;
		FilePosition fp = file.GetBeginPosition();
		size_t size = file.GetSize();
		auto string = file.GetAllContentAsText();
		char* buffer = new char[30];
		file.GetAllContentAsBinary(buffer);
		file.Close();

		c = ' ';
		memset(buffer, 0, sizeof(char) * 30);

		file.Open("../TestData/testfile.txt", FileMode::Read | FileMode::Binary);
		file >> c;
		char c2;
		file >> c2;
		size = file.GetSize();
		file.GetAllContentAsBinary(buffer);
		string = file.GetAllContentAsText();
		file.Close();

		delete[] buffer;
	}
	TEST_METHOD_END
}
TEST_GROUP_END;
TEST_GROUP_BEGIN(MathTest)
{
	TEST_METHOD_BEGIN(TestVector2D)
	{
		Vector2D v2d1(1.0f, 1.0f), v2d2(1.0f, 2.0f);
		Vector2D v2d3 = v2d1 + v2d2;
		bool if_different = (v2d1 != v2d2);
		return UnitTestResult::Pass;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestVector3D)
	{
		Vector3D v3d1(1.0f, 1.0f, 1.0f), v3d2(1.0f, 2.0f, 3.0f);
		Vector3D v3d3 = XMVectorAdd(v3d1, v3d2);
		bool if_different = (v3d1 != v3d2);
		return UnitTestResult::Pass;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestVector4D)
	{
		Vector4D v4d1(1.0f, 1.0f, 1.0f, 1.0f), v4d2(1.0f, 2.0f, 3.0f, 0.f);
		Vector4D v4d3 = XMVectorAdd(v4d1, v4d2);
		bool if_different = (v4d1 != v4d2);
		return UnitTestResult::Pass;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestMatrix3D)
	{
		Matrix3D m1(XMMatrixIdentity());
		Matrix3D m2(XMMatrixIdentity());
		m2._31 = 1;
		m2._32 = 1;
		Matrix3D m3 = (XMMATRIX)m1 * m2;
		Vector3D v1(1, 2, 1);
		Vector2D ans = XMVector3TransformCoord(v1, m3);
		return UnitTestResult::Pass;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestMatrix4D)
	{
		Matrix4D m1(XMMatrixIdentity()), m2(XMMatrixIdentity());
		m2._41 = 1;
		m2._42 = 1;
		Matrix4D m3 = (XMMATRIX)m1 * m2;
		Vector2D v1(1, 2);
		Vector2D ans = XMVector2TransformCoord(v1, m3);
		return UnitTestResult::Pass;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestAABB)
	{
		AABB aabb1({ 0,0,0 }, { 1,1,1 }), aabb2({ -1,-1,-1 }, { 0,0,0 });
		bool b1 = (aabb1 == aabb2);
		bool b2 = (aabb1 != aabb2);
		return UnitTestResult::Pass;
	}
	TEST_METHOD_END,
	TEST_METHOD_BEGIN(TestPlane)
	{
		Plane plane({ 0,1,0 }, { 0,1,5 }, { 5,1,5 });
		plane = NormalizePlane(plane);
		return UnitTestResult::Pass;
	}
	TEST_METHOD_END
}
TEST_GROUP_END;
TEST_GROUP_BEGIN(RenderTest)
{
	TEST_METHOD_BEGIN(TestRenderTarget)
	{
		Window* pWindow = MemoryManager::New<Window>();
		RenderInterface* pRenderInterface = MemoryManager::New<DX11RenderInterface>();
		//test
		pWindow->SetWindowTitle("TestWindow");
		pWindow->SetWindowSize(800, 600);
		RenderTarget render_target(ViewPort(0, 0, pWindow->GetWindowWidth(), pWindow->GetWindowHeight()));
		Connection<Window> WindowConnection = pWindow;
		Connection<RenderInterface> RenderInterfaceConnection = pRenderInterface;
		WindowConnection.m_OnStartAction = [&]() {
			pRenderInterface->Init();
		};
		WindowConnection.m_OnRunAction = [&]() {
			pRenderInterface->BeginRender(render_target);
			pRenderInterface->EndRender(render_target);
		};
		WindowConnection.m_OnResizeAction = [&]() {
			pRenderInterface->ResizeRenderTarget(render_target, ViewPort(0, 0, pWindow->GetWindowWidth(), pWindow->GetWindowHeight()));
		};
		WindowConnection.m_OnReleaseAction = [&]() {

		};
		RenderInterfaceConnection.m_OnStartAction = [&]() {
			pRenderInterface->InitRenderTarget(render_target, pWindow->GetHwnd());
		};
		RenderInterfaceConnection.m_OnReleaseAction = [&]() {
			pRenderInterface->ReleaseRenderTarget(render_target);
		};
		//----
		pWindow->StartRun(GetModuleHandle(0));
		MemoryManager::Delete(pWindow);
		MemoryManager::Delete(pRenderInterface);
	}
	TEST_METHOD_END
}
TEST_GROUP_END;