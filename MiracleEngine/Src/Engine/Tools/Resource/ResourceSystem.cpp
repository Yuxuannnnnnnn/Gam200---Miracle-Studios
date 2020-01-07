#include "PrecompiledHeaders.h"
#include "ResourceSystem.h"

ResourceSystem::ResourceSystem()
{
}

ResourceSystem::~ResourceSystem()
{
	ClearAllResources();
}

void ResourceSystem::AddTexture2DResourceList(NamePathMap list)
{
	for (auto it : list)
		AddNewTexture2DResource(NamePath{ it.first, it.second });
}

void ResourceSystem::AddShaderResourceList(NamePairMap list)
{
	for (auto it : list)
		AddNewShaderResource(NamePair{ it.first, it.second });
}

void ResourceSystem::AddFontResourceList(NamePathMap list)
{
	for (auto it : list)
		AddNewFontResource(NamePath{ it.first, it.second });
}

void ResourceSystem::AddAudioResourceList(NamePathMap list)
{
	for (auto it : list)
		AddNewAudioResource(NamePath{ it.first, it.second });
}

void ResourceSystem::AddAnimationResourceList(NamePathMap list)
{
	for (auto it : list)
		AddNewAnimationResource(NamePath{ it.first, it.second });
}

void ResourceSystem::AddPrototypeResourceList(NamePathMap_unordered list)
{
	for (auto it : list)
		AddNewPrototypeResource(NamePath{ it.first, it.second });
}


bool ResourceSystem::AddNewTexture2DResource(NamePath list)
{
	Texture2D* newTexture2D = (Texture2D*)_Texture2DAllocater.Allocate();

	// load
	if (newTexture2D->load(list.second))
	{
		_mainContainer._Texture2DMap.insert(std::pair<std::string, Texture2D*>(list.first, newTexture2D));
		_mainContainer._Texture2DList.insert(list);
		return true;
	}

	return false;
}

bool ResourceSystem::AddNewShaderResource(NamePair list)
{
	Shader* newShader = (Shader*)_ShaderAllocater.Allocate();

	// load
	if (newShader->load(list.second.first, list.second.second))
	{
		_mainContainer._ShaderMap.insert(std::pair<std::string, Shader*>(list.first, newShader));
		_mainContainer._ShaderList.insert(list);
		return true;
	}

	return false;
}

bool ResourceSystem::AddNewFontResource(NamePath list)
{
	FontRenderer* newFont = (FontRenderer*)_FontAllocater.Allocate();

	// load
	if (newFont->load(list.second))
	{
		_mainContainer._FontMap.insert(std::pair<std::string, FontRenderer*>(list.first, newFont));
		_mainContainer._FontList.insert(list);
		return true;
	}

	return false;
}

bool ResourceSystem::AddNewAudioResource(NamePath list)
{
	Sound* newSound = (Sound*)_AudioAllocater.Allocate();

	// load
	if (newSound->load(list.second, 0))
	{
		_mainContainer._AudioMap.insert(std::pair<std::string, Sound*>(list.first, newSound));
		_mainContainer._AudioList.insert(list);
		return true;
	}

	return false;
}

bool ResourceSystem::AddNewAnimationResource(NamePath list)
{
	Animation* newAnimation = (Animation*)_AnimationAllocater.Allocate();

	// load
	if (newAnimation->load(list.second))
	{
		_mainContainer._AnimationMap.insert(std::pair<std::string, Animation*>(list.first, newAnimation));
		_mainContainer._AnimationList.insert(list);
		return true;
	}

	return false;
}

bool ResourceSystem::AddNewPrototypeResource(NamePath list)
{
	GameObject* temp = new GameObject();
	Serialiser FilePath(list.second);

	temp->Serialise(FilePath);	//Serialise a gameobject with fileName

	//insert into the prototype list
	_mainContainer._PrototypeMap.insert(std::pair <std::string, GameObject*>(list.first, temp));
	_mainContainer._PrototypeList.insert(list);

	return true;
}

void ResourceSystem::ClearAllResources()
{
	for (auto it : _mainContainer._Texture2DMap)
	{
		//unload
		it.second->unload();

		_Texture2DAllocater.Free(it.second);
	}

	for (auto it : _mainContainer._ShaderMap)
	{
		//unload
		it.second->unload();

		_ShaderAllocater.Free(it.second);
	}

	for (auto it : _mainContainer._FontMap)
	{
		//unload
		it.second->unload();

		_FontAllocater.Free(it.second);
	}

	for (auto it : _mainContainer._AudioMap)
	{
		//unload
		it.second->unload();

		_AudioAllocater.Free(it.second);
	}

	for (auto it : _mainContainer._AnimationMap)
	{
		//unload
		it.second->unload();

		_AnimationAllocater.Free(it.second);
	}

	for (auto it : _mainContainer._PrototypeMap)
	{
		//Destory Prototype gameobject
		it.second->DestoryGameObject();
	}

	_mainContainer._Texture2DMap.clear();
	_mainContainer._ShaderMap.clear();
	_mainContainer._FontMap.clear();
	_mainContainer._AudioMap.clear();
	_mainContainer._AnimationMap.clear();
	_mainContainer._PrototypeMap.clear();

	_mainContainer._Texture2DList.clear();
	_mainContainer._ShaderList.clear();
	_mainContainer._FontList.clear();
	_mainContainer._AudioList.clear();
	_mainContainer._AnimationList.clear();
	_mainContainer._PrototypeList.clear();

	_mainContainer._fontCharacterMaps.clear();
}