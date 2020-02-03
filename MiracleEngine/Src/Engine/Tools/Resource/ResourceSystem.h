#ifndef _RESOURCE_SYSTEM_H
#define _RESOURCE_SYSTEM_H

#include <unordered_map>
#include <string>

#include "../ISingleton.h"
#include "IResourceInfo.h"
#include "Tools/Memory/ObjectAllocator.h"


//For Editor, Assets
class ResourceSystem final : public IResourceStructure, public ISingleton<ResourceSystem>
{
private:
	ObjectAllocator<Texture2D> _Texture2DAllocater;
	ObjectAllocator<Shader> _ShaderAllocater;
	ObjectAllocator<FontRenderer> _FontAllocater;
	ObjectAllocator<Sound> _AudioAllocater;
	ObjectAllocator<Sound> _LoopAudioAllocater;
	ObjectAllocator<Animation> _AnimationAllocater;
public:
	ResourceSystem();
	virtual ~ResourceSystem();

	//No replication of class object
	ResourceSystem(const ResourceSystem& rhs) = delete;
	ResourceSystem& operator= (const ResourceSystem& rhs) = delete;

	void AddTexture2DResourceList(const NamePathMap& list);
	void AddShaderResourceList(const NamePairMap& list);
	void AddFontResourceList(const NamePathMap& list);
	void AddAudioResourceList(const NamePathMap& list);
	void AddLoopAudioResourceList(const NamePathMap& list);
	void AddAnimationResourceList(const NamePathMap& list);
	void AddPrototypeResourceList(const NamePathMap_unordered& list);
	void AddSceneList(const NamePathMap_unordered& list);

	bool AddNewTexture2DResource(const NamePath& list);
	bool AddNewShaderResource(const NamePair& list);
	bool AddNewFontResource(const NamePath& list);
	bool AddNewAudioResource(const NamePath& list);
	bool AddNewLoopAudioResource(const NamePath& list);
	bool AddNewAnimationResource(const NamePath& list);
	bool AddNewPrototypeResource(const NamePath& list);
	bool AddNewScene(const NamePath& list);

	void ClearAllResources();
};

#define MyResourceSystem ResourceSystem::GetInstance()

#endif
