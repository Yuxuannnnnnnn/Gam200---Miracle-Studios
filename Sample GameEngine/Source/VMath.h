///////////////////////////////////////////////////////////////////////////////////////
///
///	\file VMath.h
///	Typedefs the DirectX Extension math library and provides some utility functions.
///
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////
#pragma once //Makes sure this header is only included once

//Include our math headers
#include <d3dx9.h>
#include <cmath>
#include "Serialization.h"

typedef D3DXVECTOR2 Vec2;
typedef D3DXVECTOR3 Vec3;
typedef D3DXVECTOR4 Vec4;
typedef D3DXMATRIXA16 Mat4;

namespace Framework
{
	//Extended serialization operators of compound math types.
	inline void StreamRead(ISerializer& stream,Vec2& v)
	{
		StreamRead(stream,v.x);
		StreamRead(stream,v.y);
	}

	inline void StreamRead(ISerializer& stream,Vec3& v)
	{
		StreamRead(stream,v.x);
		StreamRead(stream,v.y);
		StreamRead(stream,v.z);
	}

	inline void StreamRead(ISerializer& stream,Vec4& v)
	{
		StreamRead(stream,v.x);
		StreamRead(stream,v.y);
		StreamRead(stream,v.z);
		StreamRead(stream,v.w);
	}


	inline float Dot(const Vec2& a, const Vec2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	inline float LengthSquared(const Vec2& a)
	{
		return a.x * a.x + a.y * a.y;
	}

	inline float Normalize(Vec2& a)
	{
		float len = sqrt( LengthSquared(a) );	
		a.x /= len;
		a.y /= len;
		return len;
	}

	template< typename RefType >
	void SafeRelease( RefType& interfacePtr )
	{
		if( interfacePtr ) interfacePtr->Release();
		interfacePtr = NULL;
	}

	template< typename RefType >
	void SafeDelete( RefType& objectPtr )
	{
		if( objectPtr ) delete objectPtr;
		objectPtr = NULL;
	}

	typedef unsigned int uint;
}
