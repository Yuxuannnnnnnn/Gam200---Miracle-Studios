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

	void AddTexture2DResourceList(const NamePathMap& list);
	void AddShaderResourceList(const NamePairMap& list);
	void AddFontResourceList(const NamePathMap& list);
	void AddAudioResourceList(const NamePathMap& list);
	void AddAnimationResourceList(const NamePathMap& list);
	void AddPrototypeResourceList(const NamePathMap_unordered& list);
	void AddSceneList(const NamePathMap_unordered& list);

	bool AddNewTexture2DResource(const NamePath& list);
	bool AddNewShaderResource(const NamePair& list);
	bool AddNewFontResource(const NamePath& list);
	bool AddNewAudioResource(const NamePath& list);
	bool AddNewAnimationResource(const NamePath& list);
	bool AddNewPrototypeResource(const NamePath& list);
	bool AddNewScene(const NamePath& list);

	Texture2D* GetTexture2DResource(const std::string& name) override;
	Shader* GetShaderResource(const std::string& name) override;
	FontRenderer* GetFontResource(const std::string& name) override;
	Sound* GetSoundResource(const std::string& name) override;
	Animation* GetAnimationResource(const std::string& name) override;
	GameObject* GetPrototypeResource(const std::string& name) override;

	FontCharacterMap& GetFontCharacterMap() override;

	void ClearAllResources();
};

#endif
