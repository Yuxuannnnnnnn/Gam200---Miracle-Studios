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
#include "ResourceSystem.h"

#include "../stb_image/stb_image.h"
#include <string>

ResourceManager::ResourceManager(bool editer) :
	_editerMode{ editer }
{

}

ResourceManager::~ResourceManager()
{
	ClearAllResources();
}
void ResourceManager::AddTexture2DResourceList(const NamePathMap& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewTexture2DResource(NamePath{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddTexture2DResourceList(list);
	}

}

void ResourceManager::AddShaderResourceList(const NamePairMap& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewShaderResource(NamePair{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddShaderResourceList(list);
	}
}

void ResourceManager::AddFontResourceList(const NamePathMap& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewFontResource(NamePath{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddFontResourceList(list);
	}
}

void ResourceManager::AddAudioResourceList(const NamePathMap& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewAudioResource(NamePath{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddAudioResourceList(list);
	}
}

void ResourceManager::AddLoopAudioResourceList(const NamePathMap& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewLoopAudioResource(NamePath{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddLoopAudioResourceList(list);
	}
}

void ResourceManager::AddAnimationResourceList(const NamePathMap& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewAnimationResource(NamePath{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddAnimationResourceList(list);
	}
}

void ResourceManager::AddPrototypeResourceList(const NamePathMap_unordered& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewPrototypeResource(NamePath{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddPrototypeResourceList(list);
	}
}

void ResourceManager::AddSceneList(const NamePathMap_unordered& list)
{
	if (_editerMode)
	{
		for (auto& it : list)
			AddNewScene(NamePath{ it.first, it.second });
	}
	else
	{
		MyResourceSystem.AddPrototypeResourceList(list);
	}
}

bool ResourceManager::AddNewTexture2DResource(const NamePath& list)
{
	if (MyResourceSystem.GetTexture2DResource(list.first) || MyResourceSystem.AddNewTexture2DResource(list)) // check resource created before?
	{
		if (_editerMode)
		{
			_mainContainer._Texture2DMap.insert(std::pair<std::string, Texture2D*>(list.first, MyResourceSystem.GetTexture2DResource(list.first)));
			_mainContainer._Texture2DList.insert(list);
		}

		return true;
	}


	return false;
}

bool ResourceManager::AddNewShaderResource(const NamePair& list)
{
	if (MyResourceSystem.GetShaderResource(list.first) || MyResourceSystem.AddNewShaderResource(list)) // check resource created before?
	{
		if (_editerMode)
		{
			_mainContainer._ShaderMap.insert(std::pair<std::string, Shader*>(list.first, MyResourceSystem.GetShaderResource(list.first)));
			_mainContainer._ShaderList.insert(list);
		}

		return true;
	}

	return false;
}

bool ResourceManager::AddNewFontResource(const NamePath& list)
{
	if (MyResourceSystem.GetFontResource(list.first) || MyResourceSystem.AddNewFontResource(list)) // check resource created before?
	{
		if (_editerMode)
		{
			FontRenderer* font = MyResourceSystem.GetFontResource(list.first);

			_mainContainer._FontMap.insert(std::pair<std::string, FontRenderer*>(list.first, font));
			_mainContainer._FontList.insert(list);

			GetFontCharacterMap().insert({ font->GetCharacterMapId(), MyResourceSystem.GetFontCharacterMap()[font->GetCharacterMapId()] });
		}

		return true;
	}

	return false;
}

bool ResourceManager::AddNewAudioResource(const NamePath& list)
{
	if (MyResourceSystem.GetSoundResource(list.first) || MyResourceSystem.AddNewAudioResource(list)) // check resource created before?
	{
		if (_editerMode)
		{
			_mainContainer._AudioMap.insert(std::pair<std::string, Sound*>(list.first, MyResourceSystem.GetSoundResource(list.first)));
			_mainContainer._AudioList.insert(list);
		}

		return true;
	}

	return false;
}

bool ResourceManager::AddNewLoopAudioResource(const NamePath& list)
{
	if (MyResourceSystem.GetLoopSoundResource(list.first) || MyResourceSystem.AddNewLoopAudioResource(list)) // check resource created before?
	{
		if (_editerMode)
		{
			_mainContainer._LoopAudioMap.insert(std::pair<std::string, Sound*>(list.first, MyResourceSystem.GetLoopSoundResource(list.first)));
			_mainContainer._LoopAudioList.insert(list);
		}

		return true;
	}

	return false;
}

bool ResourceManager::AddNewAnimationResource(const NamePath& list)
{
	if (MyResourceSystem.GetAnimationResource(list.first) || MyResourceSystem.AddNewAnimationResource(list)) // check resource created before?
	{
		if (_editerMode)
		{
			_mainContainer._AnimationMap.insert(std::pair<std::string, Animation*>(list.first, MyResourceSystem.GetAnimationResource(list.first)));
			_mainContainer._AnimationList.insert(list);
		}

		return true;
	}


	return false;
}

bool ResourceManager::AddNewPrototypeResource(const NamePath& list)
{
	if (MyResourceSystem.GetPrototypeResource(list.first) || MyResourceSystem.AddNewPrototypeResource(list)) // check resource created before?
	{
		if (_editerMode)
		{
			_mainContainer._PrototypeMap.insert(std::pair<std::string, GameObject*>(list.first, MyResourceSystem.GetPrototypeResource(list.first)));
			_mainContainer._PrototypeList.insert(list);
		}

		return true;
	}

	return false;
}

bool ResourceManager::AddNewScene(const NamePath& list)
{
	if (MyResourceSystem.AddNewScene(list)) // check resource created before?
	{
		if (_editerMode)
			_mainContainer._SceneList.insert(list);

		return true;
	}

	return false;
}

Texture2D* ResourceManager::GetTexture2DResource(const std::string& name)
{
	if (_editerMode)
	{
		if (_mainContainer._Texture2DMap.find(name) != _mainContainer._Texture2DMap.end())
			return _mainContainer._Texture2DMap[name];

		return nullptr;
	}

	return MyResourceSystem.GetTexture2DResource(name);
}

Shader* ResourceManager::GetShaderResource(const std::string& name)
{
	if (_editerMode)
	{
		if (_mainContainer._ShaderMap.find(name) != _mainContainer._ShaderMap.end())
			return _mainContainer._ShaderMap[name];

		return nullptr;
	}

	return MyResourceSystem.GetShaderResource(name);
}

FontRenderer* ResourceManager::GetFontResource(const std::string& name)
{
	if (_editerMode)
	{
		if (_mainContainer._FontMap.find(name) != _mainContainer._FontMap.end())
			return _mainContainer._FontMap[name];

		return nullptr;
	}

	return MyResourceSystem.GetFontResource(name);
}

Sound* ResourceManager::GetSoundResource(const std::string& name)
{
	if (_editerMode)
	{
		if (_mainContainer._AudioMap.find(name) != _mainContainer._AudioMap.end())
			return _mainContainer._AudioMap[name];

		return nullptr;
	}

	return MyResourceSystem.GetSoundResource(name);
}

Sound* ResourceManager::GetLoopSoundResource(const std::string& name)
{
	if (_editerMode)
	{
		if (_mainContainer._LoopAudioMap.find(name) != _mainContainer._LoopAudioMap.end())
			return _mainContainer._LoopAudioMap[name];

		return nullptr;
	}

	return MyResourceSystem.GetLoopSoundResource(name);
}

Animation* ResourceManager::GetAnimationResource(const std::string& name)
{
	if (_editerMode)
	{
		if (_mainContainer._AnimationMap.find(name) != _mainContainer._AnimationMap.end())
			return _mainContainer._AnimationMap[name];

		return nullptr;
	}

	return MyResourceSystem.GetAnimationResource(name);
}

GameObject* ResourceManager::GetPrototypeResource(const std::string& name)
{
	if (_editerMode)
	{
		if (_mainContainer._PrototypeMap.find(name) != _mainContainer._PrototypeMap.end())
			return _mainContainer._PrototypeMap[name];

		return nullptr;
	}

	return MyResourceSystem.GetPrototypeResource(name);
}

FontCharacterMap& ResourceManager::GetFontCharacterMap()
{
	if (_editerMode)
		return _mainContainer._fontCharacterMaps;

	return MyResourceSystem.GetFontCharacterMap();
}

void ResourceManager::ClearAllResources()
{
	_mainContainer._Texture2DMap.clear();
	_mainContainer._ShaderMap.clear();
	_mainContainer._FontMap.clear();
	_mainContainer._AudioMap.clear();
	_mainContainer._LoopAudioMap.clear();
	_mainContainer._AnimationMap.clear();
	_mainContainer._PrototypeMap.clear();

	_mainContainer._Texture2DList.clear();
	_mainContainer._ShaderList.clear();
	_mainContainer._FontList.clear();
	_mainContainer._AudioList.clear();
	_mainContainer._LoopAudioList.clear();
	_mainContainer._AnimationList.clear();
	_mainContainer._PrototypeList.clear();

	_mainContainer._fontCharacterMaps.clear();

	if (!_editerMode)
		MyResourceSystem.ClearAllResources();
}
