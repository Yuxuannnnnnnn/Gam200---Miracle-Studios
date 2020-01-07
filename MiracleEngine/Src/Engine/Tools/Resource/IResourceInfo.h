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
	AnimationMap _AnimationMap;
	PrototypeMap _PrototypeMap;

	NamePathMap _Texture2DList;
	NamePairMap _ShaderList;
	NamePathMap _FontList;
	NamePathMap _AudioList;
	NamePathMap _AnimationList;
	NamePathMap _PrototypeList;

	FontCharacterMap _fontCharacterMaps;
};


class IResourceStructure
{
public:
	ResourceContainer _mainContainer;

	virtual ~IResourceStructure() {}
	
	virtual void AddTexture2DResourceList(NamePathMap list) = 0;
	virtual void AddShaderResourceList(NamePairMap list) = 0;
	virtual void AddFontResourceList(NamePathMap list) = 0;
	virtual void AddAudioResourceList(NamePathMap list) = 0;
	virtual void AddAnimationResourceList(NamePathMap list) = 0;
	virtual void AddPrototypeResourceList(NamePathMap_unordered list) = 0;

	virtual bool AddNewTexture2DResource(NamePath list) = 0;
	virtual bool AddNewShaderResource(NamePair list) = 0;
	virtual bool AddNewFontResource(NamePath list) = 0;
	virtual bool AddNewAudioResource(NamePath list) = 0;
	virtual bool AddNewAnimationResource(NamePath list) = 0;
	virtual bool AddNewPrototypeResource(NamePath list) = 0;

	virtual Texture2D* GetTexture2DResource(std::string name);
	virtual Shader* GetShaderResource(std::string name);
	virtual FontRenderer* GetFontResource(std::string name);
	virtual Sound* GetSoundResource(std::string name);
	virtual Animation* GetAnimationResource(std::string name);
	virtual GameObject* GetPrototypeResource(std::string name);

	std::string							GetTexture2DResourcePath(std::string name);
	std::pair<std::string, std::string> GetShaderResourcePath(std::string name);
	std::string							GetFontResourcePath(std::string name);
	std::string							GetSoundResourcePath(std::string name);
	std::string							GetAnimationResourcePath(std::string name);
	std::string							GetPrototypeResourcePath(std::string name);

	NamePathMap& GetTexture2DList();
	NamePairMap& GetShaderList();
	NamePathMap& GetFontList();
	NamePathMap& GetSoundList();
	NamePathMap& GetAnimationList();
	NamePathMap& GetPrototypeList();

	Texture2DMap& GetTexture2DMap();
	ShaderMap& GetShaderMap();
	FontMap& GetFontMap();
	AudioMap& GetSoundMap();
	AnimationMap& GetAnimationMap();
	PrototypeMap& GetPrototypeMap();

	virtual FontCharacterMap& GetFontCharacterMap();
};

#endif
