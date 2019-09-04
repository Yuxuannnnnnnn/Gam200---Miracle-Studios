///////////////////////////////////////////////////////////////////////////////////////
//
//	DebugDraw.cpp
//
//	Authors: Chris Peters 
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "DebugDraw.h"

namespace Framework
{
	Drawer Drawer::Instance;

	void Drawer::MoveTo(Vec2 v)
	{
		WritePosition = v;
	}

	void Drawer::SetColor(Vec4 color)
	{
		Flush();
		Color = color;
	}

	void Drawer::LineTo(Vec2 newPosition)
	{
		LineSegment seg = {WritePosition,newPosition};
		LineSegments.push_back( seg );
		++SegmentsDrawn;
		WritePosition = newPosition;
	}

	void Drawer::Flush()
	{
		if( SegmentsDrawn > 0 )
		{
			LineSet set = { Color , SegmentsDrawn };
			Sets.push_back( set );
			SegmentsDrawn = 0;
		}
	}

	void Drawer::Clear()
	{
		SegmentsDrawn = 0;
		Sets.clear();
		LineSegments.clear();
	}

	void Drawer::DrawSegment(Vec2 start,Vec2 end)
	{
		MoveTo(start);
		LineTo(end);;
	}

	void  Drawer::DrawCircle(Vec2 center, float radius)
	{
		const unsigned numberOfSegments = 16;
		const float increment = 2.0f * (D3DX_PI) / float(numberOfSegments);

		float theta = 0.0f;
		MoveTo( center + radius * Vec2(cosf(theta), sinf(theta)) );
		for (unsigned i = 1; i <= numberOfSegments; ++i)
		{
			LineTo( center + radius * Vec2(cosf(increment*i), sinf(increment*i)) );
		}
	}

	void  Drawer::DrawBox(Vec2 center,float size)
	{
		float halfSize = size / 2.0f;
		MoveTo( center + Vec2(halfSize,halfSize) );
		LineTo( center + Vec2(halfSize,-halfSize) );
		LineTo( center + Vec2(-halfSize,-halfSize) );
		LineTo( center + Vec2(-halfSize,halfSize)  );
		LineTo( center + Vec2(halfSize,halfSize)  );
	}


}