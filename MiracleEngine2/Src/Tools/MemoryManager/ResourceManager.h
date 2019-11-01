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
#include "IResourceInfo.h"
#include "ObjectAllocator.h"

class ResourceManager final : public ISingleton<ResourceManager>
{
public:
	typedef std::unordered_map<std::string, Texture2D_Resource*> Texture2DMap;

private:
	Texture2DMap _Texture2DMap;
	ObjectAllocator<Texture2D_Resource> _Texture2DAllocater;

public:
	ResourceManager() {};
	virtual ~ResourceManager();

	unsigned char* GetTexture2DResource(std::string file, int& width, int& height, int& bpp);

	//No replication of class object
	ResourceManager(const ResourceManager& rhs) = delete;
	ResourceManager& operator= (const ResourceManager& rhs) = delete;
private:
	Texture2D_Resource* NewGraphicResource(std::string file);

};

#endif
