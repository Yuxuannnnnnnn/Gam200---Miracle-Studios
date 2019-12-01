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

size_t Texture2D_Resource::_idCount = 0;
size_t Shader_Resource::_idCount = 0;
size_t Font_Resource::_idCount = 0;

ResourceManager::~ResourceManager()
{
	for (auto it : _bufferList)
		stbi_image_free(it);
	
	for (auto it : _FontMap)
	{
		// Destroy FreeType once we're finished
		FT_Done_Face(it.second->_face);
		FT_Done_FreeType(it.second->_ft);
	}

	for (auto it : _AudioMap)
		FMOD_Sound_Release(it.second->_sound);

	_characterList.clear();
	_bufferList.clear();
	_vertexCodeList.clear();
	_fragmentCodeList.clear();

	_Texture2DMap.clear();
	_ShaderMap.clear();
	_FontMap.clear();
	_AudioMap.clear();
}

void ResourceManager::AddTexture2DResourceList(NamePath list)
{
	_Texture2DList = list;

	for (auto it : _Texture2DList)
		NewGraphicResource(it.second);
}

void ResourceManager::AddShaderResourceList(NamePath list)
{
	_ShaderList = list;

	/*for (auto it : _ShaderList)
		GetShaderResource(it.second);*/
}

void ResourceManager::AddFontResourceList(NamePath list)
{
	_FontList = list;

	for (auto it : _FontList)
		(void)GetFontResource(it.second);
}

void ResourceManager::AddAudioResourceList(NamePath list)
{
	_AudioList = list;

	/*for (auto it : _AudioList)
		GetAudioResource(it.second); */
}

void ResourceManager::AddAnimationResourceList(NamePath list)
{
	_AnimationList = list;
	Animation* resource = new Animation();
	for (auto& filePath : _AnimationList)
	{
		//std::cout << filePath.second<<std::endl;
		resource->Serialise(filePath.second);
		_AnimationMap.insert(std::pair<std::string, Animation*>(filePath.second, resource));
	}

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
	return _bufferList[result->_uId];
}

int ResourceManager::GetShaderResource(std::string vert, std::string frag, const char*& vertexCode, const char*& fragmentCode)
{
	Shader_Resource* result = nullptr;

	ShaderMap::iterator it = _ShaderMap.find(vert);

	if (it != _ShaderMap.end())
		result = it->second;
	else
		result = NewShaderResource(vert.c_str(), frag.c_str());

	if (result->_success)
	{
		vertexCode = _vertexCodeList[result->_uId].c_str();
		fragmentCode = _fragmentCodeList[result->_uId].c_str();
	}

	return result->_success;
}

std::map<GLchar, Character> ResourceManager::GetFontResource(std::string file)
{
	Font_Resource* result = nullptr;

	FontMap::iterator it = _FontMap.find(file);

	if (it != _FontMap.end())
		result = it->second;
	else
		result = NewFontResource(file);

	return _characterList[result->_uId];
}

FMOD_SOUND* ResourceManager::GetAudioResource(std::string file, FMOD_SYSTEM* system, FMOD_MODE mode)
{
	Audio_Resource* result = nullptr;

	AudioMap::iterator it = _AudioMap.find(file);

	if (it != _AudioMap.end())
		result = it->second;
	else
		result = NewAudioResource(file, system, mode);

	return result->_sound;
}

Texture2D_Resource* ResourceManager::NewGraphicResource(std::string file)
{
	Texture2D_Resource* newResource = reinterpret_cast<Texture2D_Resource*>(_Texture2DAllocater.Allocate());

	stbi_set_flip_vertically_on_load(1);
	unsigned char* buffer = stbi_load(file.c_str(), &newResource->_width, &newResource->_height, &newResource->_bpp, 4);

	_bufferList.push_back(buffer);
	newResource->_uId = newResource->_idCount++;

	_Texture2DMap.insert(std::pair<std::string, Texture2D_Resource*>(file, newResource));

	return newResource;
}

Shader_Resource* ResourceManager::NewShaderResource(std::string vert, std::string frag)
{
	Shader_Resource* newResource = reinterpret_cast<Shader_Resource*>(_ShaderAllocater.Allocate());
	newResource->_success = 1;

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

		_vertexCodeList.push_back(vertexCode);
		_fragmentCodeList.push_back(fragmentCode);
		newResource->_uId = newResource->_idCount++;
	}
	catch (std::ifstream::failure e)
	{
		newResource->_success = 0;
		//std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	_ShaderMap.insert(std::pair<std::string, Shader_Resource*>(vert, newResource));

	return newResource;
}

Font_Resource* ResourceManager::NewFontResource(std::string file)
{
	Font_Resource* newResource = reinterpret_cast<Font_Resource*>(_FontAllocater.Allocate());

	std::map<GLchar, Character> temp;

	if (FT_Init_FreeType(&newResource->_ft) != 0) {
		std::cout << "Couldn't initialize FreeType library\n";

	}

	if (FT_New_Face(newResource->_ft, file.c_str(), 0, &newResource->_face) != 0) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	}


	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(newResource->_face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(newResource->_face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			newResource->_face->glyph->bitmap.width,
			newResource->_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			newResource->_face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(newResource->_face->glyph->bitmap.width, newResource->_face->glyph->bitmap.rows),
			glm::ivec2(newResource->_face->glyph->bitmap_left, newResource->_face->glyph->bitmap_top),
			(GLuint)newResource->_face->glyph->advance.x
		};
		temp.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	_characterList.push_back(temp);
	newResource->_uId = newResource->_idCount++;

	_FontMap.insert(std::pair<std::string, Font_Resource*>(file, newResource));

	return newResource;
}

Audio_Resource* ResourceManager::NewAudioResource(std::string file, FMOD_SYSTEM* system, FMOD_MODE mode)
{
	Audio_Resource* newResource = reinterpret_cast<Audio_Resource*>(_AudioAllocater.Allocate());

	FMOD_System_CreateSound(system, file.c_str(), mode, NULL, &newResource->_sound);
	newResource->_mode = mode;

	_AudioMap.insert(std::pair<std::string, Audio_Resource*>(file, newResource));

	return newResource;
}