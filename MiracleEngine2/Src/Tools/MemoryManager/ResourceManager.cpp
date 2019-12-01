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
#include <string>

ResourceManager::~ResourceManager()
{

}

void ResourceManager::ClearCurrentResources()
{

}

void ResourceManager::AddTexture2DResourceList(NamePathMap list)
{

}

void ResourceManager::AddShaderResourceList(NamePairMap list)
{

}

void ResourceManager::AddFontResourceList(NamePathMap list)
{

}

void ResourceManager::AddAudioResourceList(NamePathMap list)
{

}

void ResourceManager::AddAnimationResourceList(NamePathMap list)
{

}

void ResourceManager::AddNewTexture2DResource(NamePath list)
{

}

void ResourceManager::AddNewShaderResource(NamePair list)
{

}

void ResourceManager::AddNewFontResource(NamePath list)
{

}

void ResourceManager::AddNewAudioResource(NamePath list)
{

}

void ResourceManager::AddNewAnimationResource(NamePath list)
{

}


Texture2D* ResourceManager::GetTexture2DResource(std::string& name)
{
	return nullptr;
}

Shader* ResourceManager::GetShaderResource(std::string& name)
{
	return nullptr;
}

FontRenderer* ResourceManager::GetFontResource(std::string& name)
{
	return nullptr;
}

Sound* ResourceManager::GetSoundResource(std::string& name)
{
	return nullptr;
}

Animation* ResourceManager::GetAnimationResource(std::string& name)
{
	return nullptr;
}

