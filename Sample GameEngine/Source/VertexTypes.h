///////////////////////////////////////////////////////////////////////////////
///
///	\file VertexTypes.h
///	Text based concrete serializer class.
///
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

//Our custom FVF, which describes our custom vertex structure.
#define VERTEX2D_FVF (D3DFVF_XYZ|D3DFVF_TEX1)
#define LINE_FVF (D3DFVF_XYZ)

namespace Framework
{
	///A structure for our custom vertex type.
	struct Vertex2D
	{
		Vec3 Position; //The position of the vertex relative to other vertices.
		float tu, tv;   //The texture coordinates used to map the texture to the vertex.
	};

}

