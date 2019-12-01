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
#include "ObjectAllocator.h"

class ResourceManager final : public ISingleton<ResourceManager>
{
public:
	typedef std::unordered_map<std::string, std::string> NamePath;

	typedef std::unordered_map<std::string, Texture2D_Resource*> Texture2DMap;
	typedef std::unordered_map<std::string, Shader_Resource*> ShaderMap;
	typedef std::unordered_map<std::string, Font_Resource*> FontMap;
	typedef std::unordered_map<std::string, Audio_Resource*> AudioMap;

private:
	Texture2DMap _Texture2DMap;
	ShaderMap _ShaderMap;
	FontMap _FontMap;
	AudioMap _AudioMap;

	ObjectAllocator<Texture2D_Resource> _Texture2DAllocater;
	ObjectAllocator<Shader_Resource> _ShaderAllocater;
	ObjectAllocator<Font_Resource> _FontAllocater;
	ObjectAllocator<Audio_Resource> _AudioAllocater;

	std::vector<std::map<GLchar, Character>> _characterList;
	std::vector<unsigned char*> _bufferList;
	std::vector<std::string> _vertexCodeList;
	std::vector<std::string> _fragmentCodeList;

	NamePath _Texture2DList;
	NamePath _ShaderList;
	NamePath _FontList;
	NamePath _AudioList;

public:
	ResourceManager() {};
	virtual ~ResourceManager();

	//No replication of class object
	ResourceManager(const ResourceManager& rhs) = delete;
	ResourceManager& operator= (const ResourceManager& rhs) = delete;

	void AddTexture2DResourceList(NamePath list);
	void AddShaderResourceList(NamePath list);
	void AddFontResourceList(NamePath list);
	void AddAudioResourceList(NamePath list);

	unsigned char* GetTexture2DResource(std::string file, int& width, int& height, int& bpp);
	int GetShaderResource(std::string vert, std::string frag, const char*& vertexCode, const char*& fragmentCode);
	std::map<GLchar, Character> GetFontResource(std::string file);
	FMOD_SOUND* GetAudioResource(std::string file, FMOD_SYSTEM* system, FMOD_MODE mode);

private:
	Texture2D_Resource* NewGraphicResource(std::string file);
	Shader_Resource* NewShaderResource(std::string vert, std::string frag);
	Font_Resource* NewFontResource(std::string file);
	Audio_Resource* NewAudioResource(std::string file, FMOD_SYSTEM* system, FMOD_MODE mode);
};

#endif
