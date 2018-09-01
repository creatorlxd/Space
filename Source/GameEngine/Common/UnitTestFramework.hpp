/*
Copyright 2018 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once
#include "Def.h"
#include "Error.h"
#include "GlobalVariable.h"

namespace SpaceGameEngine
{
	enum class UnitTestResult :uint8_t
	{
		Unkown = 0,
		Success = 1,
		Fail = 2
	};

	inline String UnitTestResultToString(UnitTestResult result)
	{
		return (result == UnitTestResult::Success ? "Success" : (result == UnitTestResult::Fail ? "Fail" : "Unkown"));
	}

	class UnitTestManager;

	class UnitTestMethod
	{
	public:
		friend class UnitTestManager;
		inline UnitTestMethod(const String& name, const std::function<UnitTestResult()>& func, const Vector<String>& group_name) : m_Name(name), m_Result(UnitTestResult::Unkown), m_Content(func), m_GroupName(group_name)
		{}
		inline void Run()
		{
			std::cout << "test " << m_Name << " ";
			m_Result = m_Content();
			std::cout << UnitTestResultToString(m_Result) << std::endl;
		}
		inline UnitTestResult GetResult()
		{
			return m_Result;
		}
	private:
		String m_Name;
		std::function<UnitTestResult()> m_Content;
		UnitTestResult m_Result;
		Vector<String> m_GroupName;
	};

	class UnitTestGroup
	{
	public:
		friend class UnitTestManager;
		inline void Run()
		{
			for (auto i : m_Content)
			{
				i->Run();
			}
		}
	private:
		Vector<UnitTestMethod*> m_Content;
	};

	class UnitTestManager
	{
	public:
		inline void RunAllUnitTestMethod()
		{
			for (auto i : m_Content)
			{
				i.second->Run();
			}
		}

		inline void RunUnitTestGroup(const String& name)
		{
			GetGroup(name).Run();
		}

		inline void RunUnitTestMethod(const String& name)
		{
			auto iter = m_Content.find(name);
			if (iter == m_Content.end())
			{
				THROW_ERROR("can not find the unit test method called " + name);
				return;
			}
			else
			{
				iter->second->Run();
			}
		}

		template<typename... Args>
		inline void AddUnitTestMethod(Args&&... args)
		{
			UnitTestMethod* ptr = MemoryManager::New<UnitTestMethod>(std::forward<Args>(args)...);
			m_Content.insert(std::make_pair(ptr->m_Name, ptr));
			for (const auto& i : ptr->m_GroupName)
			{
				GetGroup(i).m_Content.push_back(ptr);
			}
		}
		
		//for macro to use
		struct DefineUnitTestMethod
		{
			template<typename... Args>
			DefineUnitTestMethod(UnitTestManager& manager, Args&&... args)
			{
				manager.AddUnitTestMethod(std::forward<Args>(args)...);
			}
		};

		/*
		return -1 if have failed unit test method
		*/
		inline int PrintResult()
		{
			m_TotalTestSize = 0;
			m_FailTestSize = 0;
			for (auto i : m_Content)
			{
				if (i.second)
				{
					if (i.second->GetResult() != UnitTestResult::Unkown)
					{
						m_TotalTestSize += 1;
					}
					if (i.second->GetResult() == UnitTestResult::Fail)
					{
						m_FailTestSize += 1;
					}
				}
				else
					THROW_ERROR("Unit Test Method can not be nullptr");
			}
			std::cout << "total run unit test method size: " << m_TotalTestSize << std::endl;
			std::cout << "failed unit test method size: " << m_FailTestSize << std::endl;
			if (m_FailTestSize == 0)
				return 0;
			else
				return -1;
		}

		inline int InteractionModel()
		{
			String cmd;
			while (cmd != "exit")
			{
				std::cin >> cmd;
				if (cmd == "list")
				{
					for (auto i : m_Content)
					{
						std::cout << i.first << '\t' << UnitTestResultToString(i.second->GetResult()) << std::endl;
					}
					continue;
				}
				if (cmd == "run_all")
				{
					RunAllUnitTestMethod();
					PrintResult();
					continue;
				}
				if (cmd == "run_group")
				{
					String name;
					std::cin >> name;
					RunUnitTestGroup(name);
					PrintResult();
					continue;
				}
				if (cmd == "run_method")
				{
					String name;
					std::cin >> name;
					RunUnitTestMethod(name);
					PrintResult();
					continue;
				}
				if (cmd == "clear")
				{
					system("cls");
					continue;
				}
			}
			return PrintResult();
		}

		inline ~UnitTestManager()
		{
			for (auto i : m_Content)
			{
				MemoryManager::Delete(i.second);
			}
			for (auto i : m_Group)
			{
				MemoryManager::Delete(i.second);
			}
		}
	private:
		inline UnitTestGroup& GetGroup(const String& name)
		{
			auto iter = m_Group.find(name);
			if (iter == m_Group.end())
			{
				UnitTestGroup* ptr = MemoryManager::New<UnitTestGroup>();
				m_Group.insert(std::make_pair(name, ptr));
				return *ptr;
			}
			else
			{
				return *iter->second;
			}
		}
	private:
		Map<String,UnitTestMethod*> m_Content;
		Map<String, UnitTestGroup*> m_Group;
		uint64_t m_TotalTestSize = 0, m_FailTestSize = 0;
	};

	inline UnitTestManager& GetUnitTestManager()
	{
		static GlobalVariable<UnitTestManager> g_UnitTestManager;
		return g_UnitTestManager.Get();
	}

	inline int UnitTestMain(int argc,char** argv)
	{
		if (argc == 1)
		{
			return GetUnitTestManager().InteractionModel();
		}
		if (argc == 2)
		{
			if (String(argv[1]) == "-all")
			{
				GetUnitTestManager().RunAllUnitTestMethod();
				return GetUnitTestManager().PrintResult();
			}
			else
			{
				THROW_ERROR("unkown argument");
				return -1;
			}
		}
		if (argc >= 3)
		{
			for (int i = 1; i < argc; i += 2)
			{
				String option(argv[i]);
				if (option == "-group")
				{
					GetUnitTestManager().RunUnitTestGroup(String(argv[i + 1]));
				}
				else if (option == "-method")
				{
					GetUnitTestManager().RunUnitTestMethod(String(argv[i + 1]));
				}
				else
				{
					THROW_ERROR("unkown argument");
					return -1;
				}
			}
			return GetUnitTestManager().PrintResult();
		}
		THROW_ERROR("unkown argument");
		return -1;
	}

#define UNIT_TEST_METHOD(name,...) SpaceGameEngine::UnitTestResult UnitTestMethod##name();inline SpaceGameEngine::UnitTestManager::DefineUnitTestMethod name(SpaceGameEngine::GetUnitTestManager(),#name,UnitTestMethod##name,SpaceGameEngine::Vector<SpaceGameEngine::String>{__VA_ARGS__});SpaceGameEngine::UnitTestResult UnitTestMethod##name()
#define UNIT_TEST_MAIN int main(int argc,char** argv){return SpaceGameEngine::UnitTestMain(argc,argv);}
#define REQUIRE(x) \
if(!(x)) \
{ \
	std::cout<<"in file:"<<__FILE__<<" in function:"<<__FUNCTION__<<" in line: "<<__LINE__<<" unit test method require error"<<std::endl;\
	return SpaceGameEngine::UnitTestResult::Fail;\
}
#define UNIT_TEST_SUCCESS return SpaceGameEngine::UnitTestResult::Success;
#define UNIT_TEST_FAIL return SpaceGameEngine::UnitTestResult::Fail;
}