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
#include "MemoryManager/AllocatorForSTL.hpp"
#include "GlobalVariable.h"
#include "Error.h"

namespace SpaceGameEngine
{
	struct MetaData;

	using MetaDataPtr = const MetaData*;

	/*
	use SFINAE to check if a type have static GetMetaDataCore() and non-static GetMetaData() method
	*/
	template<typename T>
	struct IfTypeHaveGetMetaDataMethod
	{
		template<typename U>
		static constexpr decltype(U::GetMetaDataCore(), std::declval<U>().GetMetaData(), bool()) Match(int)
		{
			return true;
		}

		template<typename U>
		static constexpr bool Match(...)
		{
			return false;
		}
		static constexpr bool Result = Match<T>(0);
	};

	struct MetaObject
	{
		String m_TypeName = "";
		void* m_pContent = nullptr;
	};

	using ConstructorType = std::function<MetaObject()>;
	using CopyActionType = std::function<void(const MetaObject&, const MetaObject&)>;
	using ToStringActionType = std::function<String(const MetaObject&)>;

	template<typename T>
	inline const MetaData& GetMetaData();

	struct MemberVariableMetaData
	{
		String m_TypeName = "";
		MetaDataPtr m_pMetaData = nullptr;
		String m_VariableName = "";
		size_t m_Size = 0;
		size_t m_Offset = 0;
	};

	struct MetaData
	{
		String m_TypeName = "";
		Map<String, MemberVariableMetaData> m_MemberVariable;
		ConstructorType m_Constructor = []() {return MetaObject{ "",nullptr }; };
		CopyActionType m_CopyAction = [](const MetaObject&, const MetaObject&) {};
		ToStringActionType m_ToStringAction = [](const MetaObject&) {return ""; };
		Map<String, MetaDataPtr> m_DirectInheritanceRelation;
		Map<String, MetaDataPtr> m_AllInheritanceRelation;

		MetaData(const String& type_name, const Map<String, MemberVariableMetaData>& member_var, const ConstructorType& constructor, const CopyActionType& copy_action, const ToStringActionType& to_string_action, const Map<String, MetaDataPtr>& inheritance_relation);
	};

	template<typename T>
	inline CopyActionType GetCopyAction(const std::function<void(T&, T&)>& func)
	{
		return [func](const MetaObject& dis, const MetaObject& src)
		{
			if (dis.m_TypeName == GetMetaData<T>().m_TypeName&&src.m_TypeName == GetMetaData<T>().m_TypeName)
			{
				func(*(T*)dis.m_pContent, *(T*)src.m_pContent);
			}
			else
				THROWERROR("can not copy between two different type metaobject");
		};
	}

	template<typename T>
	inline CopyActionType GetDefaultCopyAction()
	{
		return GetCopyAction([](T& dis, T& src) {dis = src; });
	}

	template<typename T>
	inline String ToString(const T& obj)
	{
		return std::to_string(obj);
	}

	template<typename T>
	inline ToStringActionType GetToStringAction(const std::function<String(T&)>& func)
	{
		return [func](const MetaObject& obj)->String
		{
			if (obj.m_TypeName == GetMetaData<T>.m_TypeName)
			{
				return func(*(T*)obj.m_pContent);
			}
			else
				THROWERROR("this function can not be call by this type of metaobject");
		};
	}

	template<typename T>
	inline ToStringActionType GetDefaultToStringAction()
	{
		return GetToStringAction(ToString<T>);
	}

	class MetaDataManager
	{
	public:
		friend class MemoryManager;
		friend struct StdAllocatorInterface;
		template<typename T>
		friend struct MetaDataFactory;

		/*
		find the metadata in manager by typename
		if not find
		return nullptr
		*/
		const MetaData* GetMetaData(const String& type_name);
	private:
		MetaDataManager();
		/*
		insert the meta data to the manager
		meta data must be a globalvariable
		*/
		void InsertMetaData(const MetaData& metadata);
	private:
		HashMap<String, const MetaData*> m_Content;
	};

	MetaDataManager& GetMetaDataManager();

	template<typename T>
	struct MetaDataFactory :public MetaData
	{
		template<typename... Arg>
		MetaDataFactory(Arg&&... arg) :MetaData(std::forward<Arg>(arg)...)
		{
			GetMetaDataManager().InsertMetaData(*this);
		}
	};

	template<typename T, bool b>
	struct GetMetaDataCore
	{
		static const MetaData& Get()
		{
			return MetaData();
		}
	};

	template<typename T>
	struct GetMetaDataCore<T, true>
	{
		static const MetaData& Get()
		{
			return T::GetMetaDataCore();
		}
	};

	template<typename T>
	struct GetMetaDataCore<T, false>
	{
		static const MetaData& Get()
		{
			static GlobalVariable<MetaDataFactory<T>> g_MetaDataFactory(typeid(T).name(), {}, [] {return MemoryManager::New<T>(); }, GetDefaultCopyAction<T>(), GetDefaultToStringAction<T>(), {});
			return g_MetaDataFactory.Get();
		}
	};

	template<typename T>
	inline const MetaData& GetMetaData()
	{
		return GetMetaDataCore<T, IfTypeHaveGetMetaDataMethod<T>::Result>::Get();
	}
}