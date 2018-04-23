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
	private:
		String m_TypeName;
		void* m_pContent;
		MetaDataPtr m_pMetaData;
	private:
		MetaObject(const String& type_name, void* ptr, MetaDataPtr pmetadata);
	public:
		template<typename T>
		friend MetaObject GetMetaObject(T* ptr);

		template<typename T>
		T* Cast() const;

		String GetTypeName() const;
	};

	using ConstructorType = std::function<MetaObject()>;
	using CopyActionType = std::function<void(const MetaObject&, const MetaObject&)>;

	template<typename T>
	inline const MetaData& GetMetaData();

	struct MemberVariableMetaData
	{
		String m_TypeName = "";
		MetaDataPtr m_pMetaData = nullptr;
		String m_VariableName = "";
		size_t m_Size = 0;
		size_t m_Offset = 0;
		bool m_IfPointer = false;
	};

	struct MetaData
	{
		String m_TypeName;
		size_t m_Size;
		Map<String, MemberVariableMetaData> m_MemberVariable;
		ConstructorType m_Constructor;
		CopyActionType m_CopyAction;
		Map<String, MetaDataPtr> m_DirectInheritanceRelation;
		Map<String, MetaDataPtr> m_AllInheritanceRelation;

		MetaData(const String& type_name, size_t size, const Map<String, MemberVariableMetaData>& member_var, const ConstructorType& constructor, const CopyActionType& copy_action, const Map<String, MetaDataPtr>& inheritance_relation);
	};

	template<typename T>
	inline CopyActionType GetCopyAction(const std::function<void(T&, T&)>& func)
	{
		return [func](const MetaObject& dis, const MetaObject& src)
		{
			if (dis.GetTypeName() == GetMetaData<T>().m_TypeName&&src.GetTypeName() == GetMetaData<T>().m_TypeName)
			{
				func(*dis.Cast<T>(), *src.Cast<T>());
			}
			else
				THROWERROR("can not copy between two different type metaobject");
		};
	}

	template<typename T>
	inline CopyActionType GetDefaultCopyAction()
	{
		return GetCopyAction<T>([](T& dis, T& src) {dis = src; });
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
			static GlobalVariable<MetaDataFactory<T>> g_MetaDataFactory(typeid(T).name(), sizeof(T), Map<String, MemberVariableMetaData>(), [] {return GetMetaObject(MemoryManager::New<T>()); }, GetDefaultCopyAction<T>(), Map<String, MetaDataPtr>());
			return g_MetaDataFactory.Get();
		}
	};

	template<typename T>
	inline const MetaData& GetMetaData()
	{
		return GetMetaDataCore<T, IfTypeHaveGetMetaDataMethod<T>::Result>::Get();
	}

	template<typename T>
	inline T * SpaceGameEngine::MetaObject::Cast() const
	{
		static const MetaData& metadata = GetMetaData<T>();
		if (m_pContent)
		{
			if (m_TypeName == metadata.m_TypeName)
			{
				return (T*)m_pContent;
			}
			else
			{
				//if t is the base of metaobject's type
				auto iter = m_pMetaData->m_AllInheritanceRelation.find(metadata.m_TypeName);
				if (iter != m_pMetaData->m_AllInheritanceRelation.cend())
				{
					return (T*)m_pContent;
				}
				else
				{
					THROWERROR("can't do this cast");
					return nullptr;
				}
			}
		}
		else
		{
			THROWERROR("meta object can not be nullptr");
			return nullptr;
		}
	}

	template<typename T>
	inline MetaObject GetMetaObject(T* ptr)
	{
		if (ptr)
		{
			return MetaObject(typeid(T).name(), ptr, &GetMetaData<T>());
		}
		else
		{
			THROWERROR("Can not get meta object by nullptr");
			return MetaObject(typeid(T).name(), ptr, &GetMetaData<T>());
		}
	}

	/*
	type_name must be typeof(type).name() or GetMetaData<type>.m_TypeName
	*/
	MetaObject ConstructByTypeName(const String& type_name);
	/*
	type_name must be typeof(type).name() or GetMetaData<type>.m_TypeName
	*/
	void CopyByTypeName(const String& type_name,MetaObject& dis,MetaObject& src);

	template<typename T>
	inline String GetTypeName()
	{
		return typeid(T).name();
	}
}