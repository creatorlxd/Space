#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{	
	class Controller :public SpaceGameEngine::Component			//camera for test
	{
	public:
		static SpaceGameEngine::ComponentManager::NewComponent<Controller> NewComponent;
		Controller()
		{
			m_TypeName = "Controller";
		}
		void Start()
		{

		}
		void Run(float DeltaTime)
		{
			if (Game::GetMainGame()->m_KeyboardDevice.IfPressDown(KEY(W)))
				CameraComponent::GetMainCamera()->GoForward(0.1f);
			if (Game::GetMainGame()->m_KeyboardDevice.IfPressDown(KEY(S)))
				CameraComponent::GetMainCamera()->GoForward(-0.1f);
			if (Game::GetMainGame()->m_KeyboardDevice.IfPressDown(KEY(A)))
				CameraComponent::GetMainCamera()->GoRight(-0.1f);
			if (Game::GetMainGame()->m_KeyboardDevice.IfPressDown(KEY(D)))
				CameraComponent::GetMainCamera()->GoRight(0.1f);
			if (Game::GetMainGame()->m_KeyboardDevice.IfPressDown(KEY(LSHIFT)))
				CameraComponent::GetMainCamera()->GoUp(-0.1f);
			if (Game::GetMainGame()->m_KeyboardDevice.IfPressDown(KEY(SPACE)))
				CameraComponent::GetMainCamera()->GoUp(0.1f);

			DIMOUSESTATE mousestate = Game::GetMainGame()->m_MouseDevice.GetMouseState();
			TransformComponent* transform = dynamic_cast<TransformComponent*>(CameraComponent::GetMainCamera()->GetFatherObject()->GetComponent("TransformComponent"));
			XMFLOAT3 rotation = transform->GetRotation();
			if (mousestate.lX > 0 && mousestate.rgbButtons[0])
				rotation.y += 0.01f;
			if (mousestate.lX<0 && mousestate.rgbButtons[0])
				rotation.y += -0.01f;
			if (mousestate.lY>0 && mousestate.rgbButtons[0])
				rotation.x += 0.01f;
			if (mousestate.lY<0 && mousestate.rgbButtons[0])
				rotation.x += -0.01f;

			/*if (mousestate.lX > 0)
			rotation.y += 0.02f;
			if (mousestate.lX < 0)
			rotation.y += -0.02f;
			if (mousestate.lY > 0)
			rotation.x += 0.02f;
			if (mousestate.lY < 0)
			rotation.x += -0.02f;*/

			int weight = Game::GetMainGame()->m_Window.GetWindowWidth();
			int height = Game::GetMainGame()->m_Window.GetWindowHeight();
			//Game::GetMainGame()->m_Window.SetCursorPosition(weight/2,height/2);
			//Game::GetMainGame()->m_Window.ChangeIfShowCursor(false);
			transform->SetRotation(rotation);
		}
	};
	REGISTERCOMPONENTCLASS(Controller);

	TEST_CLASS(SpaceGameEngineTest)
	{
	public:
		TEST_METHOD(TestThrowError)
		{
			ThrowError("Test ThrowError");
		}

		TEST_METHOD(TestRender)
		{
			m_Game.Init(GetModuleHandle(0), HINSTANCE(), "", 0);
			//write your init code here
			//code for test
			CreateTestObject("Test");
			CreateTestObject("Test2")->GetComponent<TransformComponent>()->SetPosition(XMFLOAT3(0, 50, 0));
			TestClone();
			Object* Walker = ObjectManager::NewObject();
			Walker->AddComponent(Controller::NewComponent());
			Walker->SetRootComponent("Controller");
			REGISTEROBJECT(Walker);
			m_Game.m_Window.SetWindow();
			m_Game.SetScene(&g_Scene);
			//-------------------------
			m_Game.StartRunGame();

		}

	private:
		Game m_Game;
		Scene g_Scene;
		const std::string AssetFolder = "/Source/UnitTest/TestData/";

		Object* CreateTestObject(const std::string& name)
		{
			Object* Test = ObjectManager::NewObject();
			Test->AddComponent(TransformComponent::NewComponent());
			Test->AddComponent(MeshComponent::NewComponent());
			Test->SetRootComponent(STRING(TransformComponent));
			Test->GetComponent(STRING(MeshComponent))->InitFromFile(AssetFolder+"test.model", MeshComponent::ModelFileMode);
			Test->GetRootComponent()->InitFromFile(AssetFolder+"position.txt", TransformComponent::ForRenderingMode);
			Test->GetComponent(STRING(MeshComponent))->Attach(Test->GetRootComponent());
			//Test->InitFromFile("test.assetlist");
			RegisterObject(name, Test);
			return Test;
		}

		void TestClone()
		{
			Object* Test2 = CloneObject(g_Scene.FindObject("Test"));
			Test2->GetComponent<TransformComponent>()->SetPosition(XMFLOAT3(50, 0, 0));
		}
	};
}