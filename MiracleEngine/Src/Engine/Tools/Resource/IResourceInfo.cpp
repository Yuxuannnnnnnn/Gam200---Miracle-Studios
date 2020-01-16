#include "PrecompiledHeaders.h"
#include "IResourceInfo.h"

Texture2D* IResourceStructure::GetTexture2DResource(const std::string& name)
{
	if (_mainContainer._Texture2DMap.find(name) != _mainContainer._Texture2DMap.end())
		return _mainContainer._Texture2DMap[name];

	return nullptr;
}

Shader* IResourceStructure::GetShaderResource(const std::string& name)
{
	if (_mainContainer._ShaderMap.find(name) != _mainContainer._ShaderMap.end())
		return _mainContainer._ShaderMap[name];

	return nullptr;
}

FontRenderer* IResourceStructure::GetFontResource(const std::string& name)
{
	if (_mainContainer._FontMap.find(name) != _mainContainer._FontMap.end())
		return _mainContainer._FontMap[name];

	return nullptr;
}

Sound* IResourceStructure::GetSoundResource(const std::string& name)
{
	if (_mainContainer._AudioMap.find(name) != _mainContainer._AudioMap.end())
		return _mainContainer._AudioMap[name];

	return nullptr;
}

Animation* IResourceStructure::GetAnimationResource(const std::string& name)
{
	if (_mainContainer._AnimationMap.find(name) != _mainContainer._AnimationMap.end())
		return _mainContainer._AnimationMap[name];

	return nullptr;
}

GameObject* IResourceStructure::GetPrototypeResource(const std::string& name)
{
	if (_mainContainer._PrototypeMap.find(name) != _mainContainer._PrototypeMap.end())
		return _mainContainer._PrototypeMap[name];

	return nullptr;
}

std::string& IResourceStructure::GetTexture2DResourcePath(const std::string& name)
{
	return _mainContainer._Texture2DList[name];
}

std::pair<std::string, std::string>& IResourceStructure::GetShaderResourcePath(const std::string& name)
{
	return _mainContainer._ShaderList[name];
}

std::string& IResourceStructure::GetFontResourcePath(const std::string& name)
{
	return _mainContainer._FontList[name];
}

std::string& IResourceStructure::GetSoundResourcePath(const std::string& name)
{
	return _mainContainer._AudioList[name];
}

std::string& IResourceStructure::GetAnimationResourcePath(const std::string& name)
{
	return _mainContainer._AnimationList[name];
}

std::string& IResourceStructure::GetPrototypeResourcePath(const std::string& name)
{
	return _mainContainer._PrototypeList[name];
}

std::string& IResourceStructure::GeScenePath(const std::string& name)
{
	return _mainContainer._SceneList[name];
}

NamePathMap& IResourceStructure::GetTexture2DList()
{
	return _mainContainer._Texture2DList;
}

NamePairMap& IResourceStructure::GetShaderList()
{
	return _mainContainer._ShaderList;
}

NamePathMap& IResourceStructure::GetFontList()
{
	return _mainContainer._FontList;
}

NamePathMap& IResourceStructure::GetSoundList()
{
	return _mainContainer._AudioList;
}

NamePathMap& IResourceStructure::GetAnimationList()
{
	return _mainContainer._AnimationList;
}

NamePathMap& IResourceStructure::GetPrototypeList()
{
	return _mainContainer._PrototypeList;
}

NamePathMap_unordered& IResourceStructure::GetSceneList()
{
	return _mainContainer._SceneList;
}

Texture2DMap& IResourceStructure::GetTexture2DMap()
{
	return _mainContainer._Texture2DMap;
}

ShaderMap& IResourceStructure::GetShaderMap()
{
	return _mainContainer._ShaderMap;
}

FontMap& IResourceStructure::GetFontMap()
{
	return _mainContainer._FontMap;
}

AudioMap& IResourceStructure::GetSoundMap()
{
	return _mainContainer._AudioMap;
}

AnimationMap& IResourceStructure::GetAnimationMap()
{
	return _mainContainer._AnimationMap;
}

PrototypeMap& IResourceStructure::GetPrototypeMap()
{
	return _mainContainer._PrototypeMap;
}

FontCharacterMap& IResourceStructure::GetFontCharacterMap()
{
	return _mainContainer._fontCharacterMaps;
}