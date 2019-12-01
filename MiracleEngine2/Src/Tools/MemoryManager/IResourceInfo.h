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
#include "GraphicsSystem/FontRenderer.h"
#include "Animation/Animation.h"
#include "Audio/Sound.h"
#include "GraphicsSystem/Texture2D.h"
#include "GraphicsSystem/Shader.h"

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"


//void Load_Sound(Sound* sound);




/*
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
*/


#endif
