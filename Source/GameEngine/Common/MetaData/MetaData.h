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
		void* m_pContent;
		MetaDataPtr m_pMetaData;
	public:
		MetaObject(void* ptr, MetaDataPtr pmetadata);

		template<typename T>
		T* Cast() const;

		String GetTypeName() const;

		const MetaData& GetMetaData()const;
	};

	using ConstructorType = std::function<MetaObject()>;
	using CopyActionType = std::function<void(const MetaObject&, const MetaObject&)>;

	template<typename T>
	inline const MetaData& GetMetaData();

	struct MemberVariableMetaData
	{
		MetaDataPtr m_pMetaData = nullptr;
		String m_VariableName = "";
		size_t m_Size = 0;
		size_t m_Offset = 0;
		bool m_IfPointer = false;
		bool m_IfCopy = true;

		/*
		ptr is the pointer of type which this member variable belong to
		ptr can not be nullptr
		*/
		MetaObject CastToMetaObject(void* ptr)const;
	};

	using MemberVaiableContainer = Map<String, MemberVariableMetaData>;
	using InheritanceRelationContainer = Map<String, MetaDataPtr>;

	struct MetaData
	{
		String m_TypeName;
		size_t m_Size;
		MemberVaiableContainer m_MemberVariable;
		ConstructorType m_Constructor;
		CopyActionType m_CopyAction;
		InheritanceRelationContainer m_DirectInheritanceRelation;
		InheritanceRelationContainer m_AllInheritanceRelation;

		MetaData(const String& type_name, size_t size, const MemberVaiableContainer& member_var, const ConstructorType& constructor, const CopyActionType& copy_action, const InheritanceRelationContainer& inheritance_relation);
	};

	template<typename T>
	inline CopyActionType GetCopyAction(const std::function<void(T&, T&)>& func)
	{
		return [func](const MetaObject& dst, const MetaObject& src)
		{
			if (dst.GetTypeName() == GetMetaData<T>().m_TypeName&&src.GetTypeName() == GetMetaData<T>().m_TypeName)
			{
				func(*dst.Cast<T>(), *src.Cast<T>());
			}
			else
				THROWERROR("can not copy between two different type metaobject");
		};
	}

	template<typename T>
	inline CopyActionType GetDefaultCopyAction()
	{
		return GetCopyAction<T>([](T& dst,T& src) {dst = src; });
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
			static GlobalVariable<MetaDataFactory<T>> g_MetaDataFactory(typeid(T).name(), sizeof(T), MemberVaiableContainer(), [] {return CastToMetaObject(MemoryManager::New<T>()); }, GetDefaultCopyAction<T>(), InheritanceRelationContainer());
			return g_MetaDataFactory.Get();
		}
	};

	template<typename T>
	inline const MetaData& GetMetaData()
	{
		return GetMetaDataCore<T, IfTypeHaveGetMetaDataMethod<T>::Result>::Get();
	}

	template<typename T>
	inline String GetTypeName()
	{
		return GetMetaData<T>().m_TypeName;
	}

	template<typename T>
	inline T * SpaceGameEngine::MetaObject::Cast() const
	{
		if (m_pContent)
		{
			if (MetaObject::GetTypeName() == SpaceGameEngine::GetTypeName<T>())
			{
				return (T*)m_pContent;
			}
			else
			{
				//if t is the base of metaobject's type
				auto iter = m_pMetaData->m_AllInheritanceRelation.find(SpaceGameEngine::GetTypeName<T>());
				if (iter != m_pMetaData->m_AllInheritanceRelation.end())
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
	inline MetaObject CastToMetaObject(T* ptr)
	{
		if (ptr)
		{
			return MetaObject(ptr, &GetMetaData<T>());
		}
		else
		{
			THROWERROR("Can not get meta object by nullptr");
			return MetaObject(ptr, &GetMetaData<T>());
		}
	}

	MetaObject CastToMetaObject(const String& type_name, void* ptr);

	/*
	type_name must be typeof(type).name() or GetMetaData<type>.m_TypeName
	*/
	MetaObject ConstructByTypeName(const String& type_name);
	/*
	type_name must be typeof(type).name() or GetMetaData<type>.m_TypeName
	*/
	void CopyByTypeName(const String& type_name, const MetaObject& dst, const MetaObject& src);

	/*
	two meta object must be the same type
	*/
	void CopyByMetaObject(const MetaObject& dst, const MetaObject& src);

	template<typename T>
	inline void CopyByMetaData(T& dst,T& src)
	{
		static const MetaData& metadata = T::GetMetaDataCore();
		for (auto& i : metadata.m_MemberVariable)
		{
			if (i.second.m_IfCopy)
			{
				CopyByMetaObject(i.second.CastToMetaObject(&dst), i.second.CastToMetaObject(&src));
			}
		}
	}

#define COPY_BY_METADATA(type,dst,src) CopyByMetaData<type>(const_cast<type&>(dst), const_cast<type&>(src));
#define METADATA_BEGIN(type) \
static const SpaceGameEngine::MetaData& GetMetaDataCore() \
{\
	static SpaceGameEngine::GlobalVariable<SpaceGameEngine::MetaDataFactory<type>> g_##type##MetaData(typeid(type).name(),sizeof(type),\

#define MEMBER_VAR_BEGIN SpaceGameEngine::MemberVaiableContainer({
#define MEMBER_VAR_END }),
#define METADATA_FUNCTION(type) [] {return SpaceGameEngine::CastToMetaObject(SpaceGameEngine::MemoryManager::New<type>()); },SpaceGameEngine::GetDefaultCopyAction<type>(),
#define INHERITANCE_BEGIN SpaceGameEngine::InheritanceRelationContainer({
#define INHERITANCE_END })
#define METADATA_END(type) );\
return g_##type##MetaData.Get();\
}\
virtual inline const SpaceGameEngine::MetaData& GetMetaData(){return type::GetMetaDataCore();}\
virtual inline SpaceGameEngine::MetaObject CastToMetaObject(){return SpaceGameEngine::MetaObject((void*)this,&type::GetMetaData());}\
inline static const SpaceGameEngine::MetaData& sm_MetaData=type::GetMetaDataCore();

#define MEMBER_VAR(belong_type,mem_type,mem_name,...) \
std::make_pair(#mem_name,MemberVariableMetaData{&SpaceGameEngine::GetMetaData<typename std::decay<mem_type>::type>(),#mem_name,sizeof(mem_type),offsetof(belong_type,mem_name),std::is_pointer<mem_type>::value,##__VA_ARGS__})
}