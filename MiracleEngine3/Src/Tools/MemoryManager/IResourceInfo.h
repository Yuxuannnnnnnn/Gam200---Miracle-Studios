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

#include "../Dep/fmod/inc/fmod.h"
#include "../Dep/fmod/inc/fmod_errors.h"
#include "../Dep/fmod/inc/fmod.hpp"

class Texture2D_Resource
{
public:
	Texture2D_Resource() : 
		_uId{ 0 },
		_width{0},
		_height{0},
		_bpp{0}
	{}

	static size_t _idCount;
		
	size_t _uId; // _bufferId
	int _width;
	int _height;
	int _bpp;
};

class Shader_Resource
{
public:
	Shader_Resource() :
		_uId{ 0 },
		_success{ 1 }
	{}

	static size_t _idCount;

	size_t _uId; // _vertexCodeId, _fragmentCodeID
	int _success;
};

class Font_Resource
{
public:
	Font_Resource() :
		_uId{ 0 },
		_ft{ nullptr },
		_face{ nullptr }
	{}

	static size_t _idCount;

	size_t _uId; // _characterId
	FT_Library _ft;
	FT_Face _face;
};

class Audio_Resource
{
public:
	Audio_Resource() :
		_sound{ nullptr },
		_mode{0}
	{}

	FMOD_SOUND* _sound;
	FMOD_MODE _mode;
};

#endif
