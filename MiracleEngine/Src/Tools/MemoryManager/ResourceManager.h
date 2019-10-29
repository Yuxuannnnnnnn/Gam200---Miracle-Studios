///////////////////////////////////////////////////////////////////////////////////////
//
//	ResourceManager.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>

#include "../ISingleton.h"
#include "ObjectAllocator.h"


class grapic {};

class ResourceManager final : public ISingleton<ResourceManager>
{
public:
	typedef grapic* GraphicPointer;
	typedef std::unordered_map<std::string, GraphicPointer> GraphicMap;

private:
	GraphicMap _GraphicResources;
	//ObjectAllocator<grapic, sizeof(grapic)> _GraphicAllocater;

public:
	ResourceManager() {};
	virtual ~ResourceManager();

	GraphicPointer GetGraphicResource(std::string file);


	//No replication of class object
	ResourceManager(const ResourceManager& rhs) = delete;
	ResourceManager& operator= (const ResourceManager& rhs) = delete;
private:
	GraphicPointer NewGraphicResource(std::string file);

};

#endif
