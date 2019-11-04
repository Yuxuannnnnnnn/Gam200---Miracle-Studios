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
	typedef std::unordered_map<std::string, Shader_Resource*> ShaderMap;

private:
	Texture2DMap _Texture2DMap;
	ShaderMap _ShaderMap;
	ObjectAllocator<Texture2D_Resource> _Texture2DAllocater;
	ObjectAllocator<Texture2D_Resource> _ShaderAllocater;

public:
	ResourceManager() {};
	virtual ~ResourceManager();

	unsigned char* GetTexture2DResource(std::string file, int& width, int& height, int& bpp);
	int GetShaderResource(std::string vert, std::string frag, char*& vertexCode, char*& fragmentCode);

	//No replication of class object
	ResourceManager(const ResourceManager& rhs) = delete;
	ResourceManager& operator= (const ResourceManager& rhs) = delete;
private:
	Texture2D_Resource* NewGraphicResource(std::string file);
	Shader_Resource* NewShaderResource(std::string vert, std::string frag);

};

#endif
