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
#include "stdafx.h"
#include "MetaData.h"

SpaceGameEngine::MetaData::MetaData(const String & type_name, size_t size, const MemberVaiableContainer& member_var, const ConstructorType& constructor, const CopyActionType& copy_action, const InheritanceRelationContainer& inheritance_relation)
	:
	m_TypeName(type_name), m_Size(size), m_MemberVariable(member_var), m_Constructor(constructor), m_CopyAction(copy_action), m_DirectInheritanceRelation(inheritance_relation), m_AllInheritanceRelation(inheritance_relation)
{
	for (auto i : m_DirectInheritanceRelation)
	{
		m_AllInheritanceRelation.insert(i.second.m_pMetaData->m_AllInheritanceRelation.begin(), i.second.m_pMetaData->m_AllInheritanceRelation.end());
	}
}

SpaceGameEngine::MetaDataManager & SpaceGameEngine::GetMetaDataManager()
{
	static GlobalVariable<MetaDataManager> g_MetaDataManager;
	return g_MetaDataManager.Get();
}

const SpaceGameEngine::MetaData * SpaceGameEngine::MetaDataManager::GetMetaData(const String & type_name)
{
	auto iter = m_Content.find(type_name);
	if (iter != m_Content.end())
		return iter->second;
	else
		return nullptr;
}

SpaceGameEngine::MetaDataManager::MetaDataManager()
{

}

void SpaceGameEngine::MetaDataManager::InsertMetaData(const MetaData & metadata)
{
	m_Content.insert(std::make_pair(metadata.m_TypeName, &metadata));
}

SpaceGameEngine::MetaObject::MetaObject(void * ptr, MetaDataPtr pmetadata)
{
	if (ptr == nullptr)
	{
		THROWERROR("meta object can not be nullptr");
	}
	if (m_pMetaData == nullptr)
	{
		THROWERROR("meta object's metatype can not be nullptr");
	}
	m_pContent = ptr;
	m_pMetaData = pmetadata;
}

SpaceGameEngine::String SpaceGameEngine::MetaObject::GetTypeName() const
{
	return m_pMetaData->m_TypeName;
}

const SpaceGameEngine::MetaData & SpaceGameEngine::MetaObject::GetMetaData() const
{
	return *m_pMetaData;
}

SpaceGameEngine::MetaObject SpaceGameEngine::ConstructByTypeName(const String & type_name)
{
	auto meta = GetMetaDataManager().GetMetaData(type_name);
	if (meta)
		return meta->m_Constructor();
	else
	{
		THROWERROR("do not have this type");
	}
}

void SpaceGameEngine::CopyByMetaObject(const MetaObject & dst, const MetaObject & src)
{
	if (dst.GetTypeName() == src.GetTypeName())
	{
		auto meta = GetMetaDataManager().GetMetaData(src.GetTypeName());
		if (meta)
			return meta->m_CopyAction(dst, src);
		else
		{
			THROWERROR("do not have this type");
		}
	}
	else
	{
		THROWERROR("can not copy between different type's metaobject");
	}
}

SpaceGameEngine::MetaObject SpaceGameEngine::MemberVariableMetaData::CastToMetaObject(const MetaObject& obj)const
{
	if (obj.GetTypeName() == m_ClassTypeName)
		return MetaObject((void*)((size_t)obj.m_pContent + m_Offset), m_pMetaData);
	else
	{
		THROWERROR("can not get this metaobject");
		return MetaObject(nullptr, nullptr);
	}
}

SpaceGameEngine::MetaObject SpaceGameEngine::FatherTypeMetaData::CastToMetaObject(const MetaObject & obj) const
{
	if (obj.GetTypeName() == m_ChildTypeName)
		return MetaObject((void*)((size_t)obj.m_pContent + m_Offset), m_pMetaData);
	else
	{
		THROWERROR("can not get this metaobject");
		return MetaObject(nullptr, nullptr);
	}
}
