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
#include "Tools/Memory/ObjectAllocator.h"



//For GamePlay Resource
class ResourceManager final : public IResourceStructure
{
	bool _editerMode;
public:
	ResourceManager(bool editer = false);
	virtual ~ResourceManager();

	//No replication of class object
	ResourceManager(const ResourceManager& rhs) = delete;
	ResourceManager& operator= (const ResourceManager& rhs) = delete;

	void AddTexture2DResourceList(NamePathMap list);
	void AddShaderResourceList(NamePairMap list);
	void AddFontResourceList(NamePathMap list);
	void AddAudioResourceList(NamePathMap list);
	void AddAnimationResourceList(NamePathMap list);
	void AddPrototypeResourceList(NamePathMap_unordered list);

	bool AddNewTexture2DResource(NamePath list);
	bool AddNewShaderResource(NamePair list);
	bool AddNewFontResource(NamePath list);
	bool AddNewAudioResource(NamePath list);
	bool AddNewAnimationResource(NamePath list);
	bool AddNewPrototypeResource(NamePath list);

	Texture2D* GetTexture2DResource(std::string name) override;
	Shader* GetShaderResource(std::string name) override;
	FontRenderer* GetFontResource(std::string name) override;
	Sound* GetSoundResource(std::string name) override;
	Animation* GetAnimationResource(std::string name) override;
	GameObject* GetPrototypeResource(std::string name) override;

	FontCharacterMap& GetFontCharacterMap() override;

	void ClearAllResources();
};

#endif
