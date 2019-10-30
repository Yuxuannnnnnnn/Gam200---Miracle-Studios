///////////////////////////////////////////////////////////////////////////////////////
//
//	ResourceManager.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
	_GraphicResources.clear();
	//_GraphicAllocater.~ObjectAllocator();
}

ResourceManager::GraphicPointer ResourceManager::GetGraphicResource(std::string file)
{
	GraphicMap::iterator it = _GraphicResources.find(file);

	if (it != _GraphicResources.end())
		return it->second;

	return NewGraphicResource(file);
}

ResourceManager::GraphicPointer ResourceManager::NewGraphicResource(std::string file)
{
	
	GraphicPointer newResource; //= reinterpret_cast<GraphicPointer>(_GraphicAllocater.Allocate());

	// how to create graphic resource

	_GraphicResources.insert(std::pair<std::string, GraphicPointer>(file, newResource));

	return newResource;
}