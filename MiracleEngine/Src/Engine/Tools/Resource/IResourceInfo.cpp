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
Sound* IResourceStructure::GetLoopSoundResource(const std::string& name)
{
	if (_mainContainer._LoopAudioMap.find(name) != _mainContainer._LoopAudioMap.end())
		return _mainContainer._LoopAudioMap[name];

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
	if (_mainContainer._Texture2DList.find(name) != _mainContainer._Texture2DList.end())
		return _mainContainer._Texture2DList[name];

	std::string temp;

	return temp;
}

std::pair<std::string, std::string>& IResourceStructure::GetShaderResourcePath(const std::string& name)
{
	if (_mainContainer._ShaderList.find(name) != _mainContainer._ShaderList.end())
		return _mainContainer._ShaderList[name];

	std::pair<std::string, std::string> temp;

	return temp;
}

std::string& IResourceStructure::GetFontResourcePath(const std::string& name)
{
	if (_mainContainer._FontList.find(name) != _mainContainer._FontList.end())
		return _mainContainer._FontList[name];

	std::string temp;

	return temp;
}

std::string& IResourceStructure::GetSoundResourcePath(const std::string& name)
{
	if (_mainContainer._AudioList.find(name) != _mainContainer._AudioList.end())
		return _mainContainer._AudioList[name];

	std::string temp;

	return temp;
}
std::string& IResourceStructure::GetLoopSoundResourcePath(const std::string& name)
{
	if (_mainContainer._LoopAudioList.find(name) != _mainContainer._LoopAudioList.end())
		return _mainContainer._LoopAudioList[name];

	std::string temp;

	return temp;
}


std::string& IResourceStructure::GetAnimationResourcePath(const std::string& name)
{
	if (_mainContainer._AnimationList.find(name) != _mainContainer._AnimationList.end())
		return _mainContainer._AnimationList[name];

	std::string temp;

	return temp;
}

std::string& IResourceStructure::GetPrototypeResourcePath(const std::string& name)
{
	if (_mainContainer._PrototypeList.find(name) != _mainContainer._PrototypeList.end())
		return _mainContainer._PrototypeList[name];

	std::string temp;

	return temp;
}

std::string& IResourceStructure::GeScenePath(const std::string& name)
{
	if (_mainContainer._SceneList.find(name) != _mainContainer._SceneList.end())
		return _mainContainer._SceneList[name];

	std::string temp;

	return temp;
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

NamePathMap& IResourceStructure::GetLoopSoundList()
{
	return _mainContainer._LoopAudioList;
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

AudioMap& IResourceStructure::GetLoopSoundMap()
{
	return _mainContainer._LoopAudioMap;
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