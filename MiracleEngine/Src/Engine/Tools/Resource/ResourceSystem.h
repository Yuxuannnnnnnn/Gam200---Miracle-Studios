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
	ObjectAllocator<Animation> _AnimationAllocater;
public:
	ResourceSystem();
	virtual ~ResourceSystem();

	//No replication of class object
	ResourceSystem(const ResourceSystem& rhs) = delete;
	ResourceSystem& operator= (const ResourceSystem& rhs) = delete;

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

	void ClearAllResources();
};

#define MyResourceSystem ResourceSystem::GetInstance()

#endif
