#include"stdafx.h"
#include "../Include/Mesh.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(MeshComponent);

SpaceGameEngine::MeshComponent::MeshComponent()
{

}

void SpaceGameEngine::MeshComponent::Release()
{
	
}

SpaceGameEngine::MeshComponent::~MeshComponent()
{
	Release();
}

void SpaceGameEngine::MeshComponent::WriteInVertexBuffer(DefaultVertex* pVertices)
{
	
}

void SpaceGameEngine::MeshComponent::WriteInIndexBuffer(WORD* pIndices)
{
	
}

void SpaceGameEngine::MeshComponent::InitFromMemory(int VertexSize, int IndexSize, DefaultVertex * pVertices, WORD * pIndices)
{
	
}

void SpaceGameEngine::MeshComponent::InitFromFile(const std::string & filename, int mode)
{
	
}

void SpaceGameEngine::MeshComponent::Run(float DeltaTime)
{
	
}
