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

#include "../stb_image/stb_image.h"

ResourceManager::~ResourceManager()
{
	for (auto it : _Texture2DMap)
		stbi_image_free(it.second->_buffer);

	_Texture2DMap.clear();
}

unsigned char* ResourceManager::GetTexture2DResource(std::string file, int& width, int& height, int& bpp)
{
	Texture2D_Resource* result = nullptr;

	Texture2DMap::iterator it = _Texture2DMap.find(file);

	if (it != _Texture2DMap.end())
		result = it->second;
	else
		result = NewGraphicResource(file);
		
	width = result->_width;
	height = result->_height;
	bpp = result->_bpp;
	return result->_buffer;
}

Texture2D_Resource* ResourceManager::NewGraphicResource(std::string file)
{
	Texture2D_Resource* newResource = reinterpret_cast<Texture2D_Resource*>(_Texture2DAllocater.Allocate());

	stbi_set_flip_vertically_on_load(1);
	newResource->_buffer = stbi_load(file.c_str(), &newResource->_width, &newResource->_height, &newResource->_bpp, 4);

	_Texture2DMap.insert(std::pair<std::string, Texture2D_Resource*>(file, newResource));

	return newResource;
}