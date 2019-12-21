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

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"
/*

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
