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
	ClearCurrentResources();
}

void ResourceManager::ClearCurrentResources()
{
	for (auto it : _Texture2DMap)
	{
		//unload
		it.second->unload();

		_Texture2DAllocater.Free(it.second);
	}

	for (auto it : _ShaderMap)
	{
		//unload
		it.second->unload();

		_ShaderAllocater.Free(it.second);
	}

	for (auto it : _FontMap)
	{
		//unload
		it.second->unload();

		_FontAllocater.Free(it.second);
	}

	for (auto it : _AudioMap)
	{
		//unload
		it.second->unload();

		_AudioAllocater.Free(it.second);
	}

	for (auto it : _AnimationMap)
	{
		//unload
		it.second->unload();

		_AnimationAllocater.Free(it.second);
	}

	_Texture2DMap.clear();
	_ShaderMap.clear();
	_FontMap.clear();
	_AudioMap.clear();
	_AnimationMap.clear();

	_Texture2DList.clear();
	_ShaderList.clear();
	_FontList.clear();
	_AudioList.clear();
	_AnimationList.clear();
}

void ResourceManager::AddTexture2DResourceList(NamePathMap list)
{
	for (auto& it : list)
		AddNewTexture2DResource(it);
}

void ResourceManager::AddShaderResourceList(NamePairMap list)
{
	for (auto it : list)
		AddNewShaderResource(it);
}

void ResourceManager::AddFontResourceList(NamePathMap list)
{
	for (auto it : list)
		AddNewFontResource(it);
}

void ResourceManager::AddAudioResourceList(NamePathMap list)
{
	for (auto it : list)
		AddNewAudioResource(it);
}

void ResourceManager::AddAnimationResourceList(NamePathMap list)
{
	for (auto it : list)
		AddNewAnimationResource(it);
}

bool ResourceManager::AddNewTexture2DResource(NamePath list)
{
	Texture2D* newTexture2D = (Texture2D*)_Texture2DAllocater.Allocate();

	// load
	if (newTexture2D->load(list.second))
	{
		_Texture2DMap.insert(std::pair<std::string, Texture2D*>(list.first, newTexture2D));
		_Texture2DList.insert(list);
		return true;
	}

	return false;
}

bool ResourceManager::AddNewShaderResource(NamePair list)
{
	Shader* newShader = (Shader*)_ShaderAllocater.Allocate();

	// load
	if (newShader->load(list.second.first, list.second.second))
	{
		_ShaderMap.insert(std::pair<std::string, Shader*>(list.first, newShader));
		_ShaderList.insert(list);
		return true;
	}

	return false;
}

bool ResourceManager::AddNewFontResource(NamePath list)
{
	FontRenderer* newFont = (FontRenderer*)_FontAllocater.Allocate();

	// load
	if (newFont->load(list.second))
	{
		_FontMap.insert(std::pair<std::string, FontRenderer*>(list.first, newFont));
		_FontList.insert(list);
		return true;
	}

	return false;
}

bool ResourceManager::AddNewAudioResource(NamePath list)
{
	Sound* newSound = (Sound*)_AudioAllocater.Allocate();

	// load
	if (newSound->load(list.second, 0))
	{
		_AudioMap.insert(std::pair<std::string, Sound*>(list.first, newSound));
		_AudioList.insert(list);
		return true;
	}

	return false;
}

bool ResourceManager::AddNewAnimationResource(NamePath list)
{
	Animation* newAnimation = (Animation*)_AnimationAllocater.Allocate();

	// load
	if (newAnimation->load(list.second))
	{
		_AnimationMap.insert(std::pair<std::string, Animation*>(list.first, newAnimation));
		_AnimationList.insert(list);
		return true;
	}

	return false;
}


Texture2D* ResourceManager::GetTexture2DResource(std::string name)
{
	if (_Texture2DMap.find(name) != _Texture2DMap.end())
		return _Texture2DMap[name];

	return nullptr;
}

Shader* ResourceManager::GetShaderResource(std::string name)
{
	if (_ShaderMap.find(name) != _ShaderMap.end())
		return _ShaderMap[name];

	return nullptr;
}

FontRenderer* ResourceManager::GetFontResource(std::string name)
{
	if (_FontMap.find(name) != _FontMap.end())
		return _FontMap[name];

	return nullptr;
}

Sound* ResourceManager::GetSoundResource(std::string name)
{
	if (_AudioMap.find(name) != _AudioMap.end())
		return _AudioMap[name];

	return nullptr;
}

Animation* ResourceManager::GetAnimationResource(std::string name)
{
	if (_AnimationMap.find(name) != _AnimationMap.end())
		return _AnimationMap[name];

	return nullptr;
}

std::string ResourceManager::GetTexture2DResourcePath(std::string name)
{
	return _Texture2DList[name];
}

std::pair<std::string, std::string> ResourceManager::GetShaderResourcePath(std::string name)
{
	return _ShaderList[name];
}

std::string ResourceManager::GetFontResourcePath(std::string name)
{
	return _FontList[name];
}

std::string ResourceManager::GetSoundResourcePath(std::string name)
{
	return _AudioList[name];
}

std::string ResourceManager::GetAnimationResourcePath(std::string name)
{
	return _AnimationList[name];
}

ResourceManager::NamePathMap ResourceManager::GetTexture2DList()
{
	return _Texture2DList;
}

ResourceManager::NamePairMap ResourceManager::GetShaderList()
{
	return _ShaderList;
}

ResourceManager::NamePathMap ResourceManager::GetFontList()
{
	return _FontList;
}

ResourceManager::NamePathMap ResourceManager::GetSoundList()
{
	return _AudioList;
}

ResourceManager::NamePathMap ResourceManager::GetAnimationlist()
{
	return _AnimationList;
}