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

#include "../stb_image/stb_image.h"
#include <string>

ResourceManager::~ResourceManager()
{
	for (auto it : _Texture2DMap)
		stbi_image_free(it.second->_buffer);

	_Texture2DMap.clear();
}

unsigned char* ResourceManager::GetTexture2DResource(std::string file, int& width, int& height, int& bpp)
{
	Texture2D_Resource* result = nullptr;

	Texture2DMap::iterator it = _Texture2DMap.find(file);

	if (it != _Texture2DMap.end())
		result = it->second;
	else
		result = NewGraphicResource(file);
		
	width = result->_width;
	height = result->_height;
	bpp = result->_bpp;
	return result->_buffer;
}

Texture2D_Resource* ResourceManager::NewGraphicResource(std::string file)
{
	Texture2D_Resource* newResource = reinterpret_cast<Texture2D_Resource*>(_Texture2DAllocater.Allocate());

	stbi_set_flip_vertically_on_load(1);
	newResource->_buffer = stbi_load(file.c_str(), &newResource->_width, &newResource->_height, &newResource->_bpp, 4);

	_Texture2DMap.insert(std::pair<std::string, Texture2D_Resource*>(file, newResource));

	return newResource;
}


int ResourceManager::GetShaderResource(std::string vert, std::string frag, char*& vertexCode, char*& fragmentCode)
{
	Shader_Resource* result = nullptr;

	ShaderMap::iterator it = _ShaderMap.find(vert);

	if (it != _ShaderMap.end())
		result = it->second;
	else
		result = NewShaderResource(vert.c_str(), frag.c_str());


	return result->_success;
}

Shader_Resource* ResourceManager::NewShaderResource(std::string vert, std::string frag)
{
	Shader_Resource* newResource = reinterpret_cast<Shader_Resource*>(_ShaderAllocater.Allocate());
	
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vert);
		fShaderFile.open(frag);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		newResource->_success = 0;
		//std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	newResource->_vertexCode = vertexCode;
	newResource->_fragmentCode = fragmentCode;
	
	_ShaderMap.insert(std::pair<std::string, Shader_Resource*>(vert, newResource));

	return newResource;
}