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
	typedef std::pair<std::string, std::string> NamePath;
	typedef std::unordered_map<std::string, std::string> NamePathMap;

	typedef std::pair<std::string, std::pair<std::string, std::string>> NamePair;
	typedef std::unordered_map<std::string, std::pair<std::string, std::string>> NamePairMap;

	typedef std::unordered_map<std::string, Texture2D*> Texture2DMap;
	typedef std::unordered_map<std::string, Shader*> ShaderMap;
	typedef std::unordered_map<std::string, FontRenderer*> FontMap;
	typedef std::unordered_map<std::string, Sound*> AudioMap;
	typedef std::unordered_map<std::string, Animation*> AnimationMap;

	typedef std::unordered_map<size_t, std::unordered_map<GLchar, Character>> FontCharacterMap;

	FontCharacterMap _fontCharacterMaps;
private:
	Texture2DMap _Texture2DMap;
	ShaderMap _ShaderMap;
	FontMap _FontMap;
	AudioMap _AudioMap;
	AnimationMap _AnimationMap;

	ObjectAllocator<Texture2D> _Texture2DAllocater;
	ObjectAllocator<Shader> _ShaderAllocater;
	ObjectAllocator<FontRenderer> _FontAllocater;
	ObjectAllocator<Sound> _AudioAllocater;
	ObjectAllocator<Animation> _AnimationAllocater;

	NamePathMap _Texture2DList;
	NamePairMap _ShaderList;
	NamePathMap _FontList;
	NamePathMap _AudioList;
	NamePathMap _AnimationList;

public:
	ResourceManager() {};
	virtual ~ResourceManager();

	//No replication of class object
	ResourceManager(const ResourceManager& rhs) = delete;
	ResourceManager& operator= (const ResourceManager& rhs) = delete;

	void ClearCurrentResources();

	void AddTexture2DResourceList(NamePathMap list);
	void AddShaderResourceList(NamePairMap list);
	void AddFontResourceList(NamePathMap list);
	void AddAudioResourceList(NamePathMap list);
	void AddAnimationResourceList(NamePathMap list);

	bool AddNewTexture2DResource(NamePath list);
	bool AddNewShaderResource(NamePair list);
	bool AddNewFontResource(NamePath list);
	bool AddNewAudioResource(NamePath list);
	bool AddNewAnimationResource(NamePath list);

	Texture2D* GetTexture2DResource(std::string name);
	Shader* GetShaderResource(std::string name);
	FontRenderer* GetFontResource(std::string name);
	Sound* GetSoundResource(std::string name);
	Animation* GetAnimationResource(std::string name);

	std::string GetTexture2DResourcePath(std::string name);
	std::pair<std::string, std::string> GetShaderResourcePath(std::string name);
	std::string GetFontResourcePath(std::string name);
	std::string GetSoundResourcePath(std::string name);
	std::string GetAnimationResourcePath(std::string name);

	NamePathMap GetTexture2DList();
	NamePairMap GetShaderList();
	NamePathMap GetFontList();
	NamePathMap GetSoundList();
	NamePathMap GetAnimationlist();
};

#define MyResourceManager ResourceManager::GetInstance()

#endif
