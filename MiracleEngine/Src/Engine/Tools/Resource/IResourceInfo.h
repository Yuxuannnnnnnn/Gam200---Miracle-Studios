///////////////////////////////////////////////////////////////////////////////////////
//
//	IResourceInfo.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _IRESOURCE_INFORMATION_H
#define _IRESOURCE_INFORMATION_H
#include "SystemGraphics/FontRenderer.h"
#include "SystemAnimation/Animation.h"
#include "SystemAudio/Sound.h"
#include "SystemGraphics/Texture2D.h"
#include "SystemGraphics/Shader.h"
#include "GameObject/GameObject.h"

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"


typedef std::pair<std::string, std::string> NamePath;
typedef std::map<std::string, std::string> NamePathMap;
typedef std::unordered_map<std::string, std::string> NamePathMap_unordered;

typedef std::pair<std::string, std::string> VertFrag;

typedef std::pair<std::string, std::pair<std::string, std::string>> NamePair;
typedef std::unordered_map<std::string, std::pair<std::string, std::string>> NamePairMap;

typedef std::unordered_map<std::string, Texture2D*> Texture2DMap;
typedef std::unordered_map<std::string, Shader*> ShaderMap;
typedef std::unordered_map<std::string, FontRenderer*> FontMap;
typedef std::unordered_map<std::string, Sound*> AudioMap;
typedef std::unordered_map<std::string, Animation*> AnimationMap;
typedef std::unordered_map<std::string, GameObject*> PrototypeMap;

typedef std::unordered_map<size_t, std::unordered_map<GLchar, Character>> FontCharacterMap;

struct ResourceContainer 
{
	Texture2DMap _Texture2DMap;
	ShaderMap _ShaderMap;
	FontMap _FontMap;
	AudioMap _AudioMap;
	AudioMap _LoopAudioMap;
	AnimationMap _AnimationMap;
	PrototypeMap _PrototypeMap;

	NamePathMap _Texture2DList;
	NamePairMap _ShaderList;
	NamePathMap _FontList;
	NamePathMap _AudioList;
	NamePathMap _LoopAudioList;
	NamePathMap _AnimationList;
	NamePathMap _PrototypeList;

	NamePathMap_unordered _SceneList;


	FontCharacterMap _fontCharacterMaps;
};


class IResourceStructure
{
public:
	ResourceContainer _mainContainer;

	virtual ~IResourceStructure() {}
	
	virtual void AddTexture2DResourceList(const NamePathMap& list) = 0;
	virtual void AddShaderResourceList(const NamePairMap& list) = 0;
	virtual void AddFontResourceList(const NamePathMap& list) = 0;
	virtual void AddAudioResourceList(const NamePathMap& list) = 0;
	virtual void AddLoopAudioResourceList(const NamePathMap& list) = 0;
	virtual void AddAnimationResourceList(const NamePathMap& list) = 0;
	virtual void AddPrototypeResourceList(const NamePathMap_unordered& list) = 0;
	virtual void AddSceneList(const NamePathMap_unordered& list) = 0;

	virtual bool AddNewTexture2DResource(const NamePath& list) = 0;
	virtual bool AddNewShaderResource(const NamePair& list) = 0;
	virtual bool AddNewFontResource(const NamePath& list) = 0;
	virtual bool AddNewAudioResource(const NamePath& list) = 0;
	virtual bool AddNewLoopAudioResource(const NamePath& list) = 0;
	virtual bool AddNewAnimationResource(const NamePath& list) = 0;
	virtual bool AddNewPrototypeResource(const NamePath& list) = 0;
	virtual bool AddNewScene(const NamePath& list) = 0;


	virtual Texture2D* GetTexture2DResource(const std::string& name);
	virtual Shader* GetShaderResource(const std::string& name);
	virtual FontRenderer* GetFontResource(const std::string& name);
	virtual Sound* GetSoundResource(const std::string& name);
	virtual Sound* GetLoopSoundResource(const std::string& name);
	virtual Animation* GetAnimationResource(const std::string& name);
	virtual GameObject* GetPrototypeResource(const std::string& name);

	std::string&						 GetTexture2DResourcePath(const std::string& name);
	std::pair<std::string, std::string>& GetShaderResourcePath(const std::string& name);
	std::string&						 GetFontResourcePath(const std::string& name);
	std::string&						 GetSoundResourcePath(const std::string& name);
	std::string&						 GetLoopSoundResourcePath(const std::string& name);
	std::string&						 GetAnimationResourcePath(const std::string& name);
	std::string&						 GetPrototypeResourcePath(const std::string& name);
	std::string&						 GeScenePath(const std::string& name);

	NamePathMap& GetTexture2DList();
	NamePairMap& GetShaderList();
	NamePathMap& GetFontList();
	NamePathMap& GetSoundList();
	NamePathMap& GetLoopSoundList();
	NamePathMap& GetAnimationList();
	NamePathMap& GetPrototypeList();
	NamePathMap_unordered& GetSceneList();

	Texture2DMap& GetTexture2DMap();
	ShaderMap& GetShaderMap();
	FontMap& GetFontMap();
	AudioMap& GetSoundMap();
	AudioMap& GetLoopSoundMap();
	AnimationMap& GetAnimationMap();
	PrototypeMap& GetPrototypeMap();

	virtual FontCharacterMap& GetFontCharacterMap();
};

#endif
