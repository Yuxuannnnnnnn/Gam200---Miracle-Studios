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

class Texture2D_Resource
{
public:
	Texture2D_Resource() : 
		_buffer{nullptr},
		_width{0},
		_height{0},
		_bpp{0}
	{}
		
	unsigned char* _buffer;
	int _width;
	int _height;
	int _bpp;
};

#endif
